#ifndef __UNSORTEDMAP_H__
#define __UNSORTEDMAP_H__

#include <iostream>
#include <initializer_list>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef> // For std::ptrdiff_t
#include <utility> // For std::pair
#include <vector>
#include <type_traits>
#include <ranges>

template<class T>
concept Keyable = (requires(T a, T b) {a == b;}) && (!std::is_integral<T>::value);

template<Keyable K, class V, size_t D = 100>
class unsorted_map
{
    public:
        class Iterator;
        class ConstIterator;

        using key_type = K;
        using mapped_type = V;
        using value_type = std::pair<const key_type, mapped_type>;
        using allocator_type = std::allocator<value_type>;
        using allocator_traits = std::allocator_traits<allocator_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using size_type = size_t;
        
        const size_type npos = -1;

        class Iterator {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = typename unsorted_map::value_type;
                using difference_type = std::ptrdiff_t;
                using pointer = value_type*;
                using reference = value_type&;

                Iterator(pointer ptr) : ptr_(ptr) {}
                reference operator*() const { return *ptr_; }
                pointer operator->() const { return ptr_; }
                iterator& operator++() { ++ptr_; return *this; }
                iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
                iterator& operator--() { --ptr_; return *this; }
                iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }
                bool operator==(const iterator& other) const = default;
                bool operator!=(const iterator& other) const = default;

                operator ConstIterator() const { return ConstIterator(ptr_); }

            private:
                pointer ptr_;
                friend class ConstIterator;
        };

        class ConstIterator {
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type = const unsorted_map::value_type;
                using difference_type = std::ptrdiff_t;
                using pointer = const value_type*;
                using reference = const value_type&;

                ConstIterator(pointer ptr) : ptr_(ptr) {}
                reference operator*() const { return *ptr_; }
                pointer operator->() const { return ptr_; }
                ConstIterator& operator++() { ++ptr_; return *this; }
                ConstIterator operator++(int) { ConstIterator tmp = *this; ++ptr_; return tmp; }
                ConstIterator& operator--() { --ptr_; return *this; }
                ConstIterator operator--(int) { ConstIterator tmp = *this; --ptr_; return tmp; }
                bool operator==(const ConstIterator& other) const = default;
                bool operator!=(const ConstIterator& other) const = default;

            private:
                pointer ptr_;
        };        
        
        // Constructors and destructors
        unsorted_map() : capacity_(D), size_(0), data_(allocator_traits::allocate(allocator_, capacity_)) {};
        unsorted_map(const std::initializer_list<value_type>& il);
        ~unsorted_map();

        // Element addition
        iterator insert(const value_type& val, const size_type pos);
        iterator insert(const key_type& key, const mapped_type& val, const size_type pos) { return insert(std::make_pair<>(key, val), pos); }
        iterator insert(const std::initializer_list<value_type>& il, const size_type pos);
        iterator insert(const unsorted_map<key_type, mapped_type, D>& map, const size_type pos);
        iterator push_back(const value_type& val) { return insert(val, size_); }
        iterator push_back(const key_type& key, const mapped_type& val) { return insert(key, val, size_); }
        iterator push_back(const std::initializer_list<value_type>& il) { return insert(il, size_); }
        iterator push_back(const unsorted_map<key_type, mapped_type, D>& map) { return insert(map, size_); }
        iterator push_front(const value_type& val) { return insert(val, 0); }
        iterator push_front(const key_type& key, const mapped_type& val) { return insert(key, val, 0); }
        iterator push_front(const std::initializer_list<value_type>& il) { return insert(il, 0); }
        iterator push_front(const unsorted_map<key_type, mapped_type, D>& map) { return insert(map, 0); }

        // Element access
        iterator at(const size_type pos) { return pos < size_ ? iterator(&data_[pos]) : iterator(data_ + size_); }
        auto at(const key_type& key);  // return type : std::pair<iterator, size_type>
        auto all(const key_type& key);  // return type : std::vector<std::pair<iterator, size_type>>
        pointer data() { return data_; }

        // Element management
        void clear();
        void erase(const size_type pos);
        void erase(const key_type& key);
        void erase_all(const key_type& key);
        void swap(const size_type from, const size_type to);
        unsorted_map<key_type, mapped_type, D> copy();
        unsorted_map<key_type, mapped_type, D> move();
        
        // Memory related members
        size_type size() { return size_; }
        size_type capacity() { return capacity_; }
        allocator_type get_allocator() { return allocator_; }
        bool reserve(size_type min_capacity);
        bool shrink() { return resize(size_); };
        bool resize(size_type new_capacity);

        // Iterators
        iterator begin() { return iterator(data_); }
        iterator end() { return iterator(data_ + size_); }

        reverse_iterator rbegin() { return reverse_iterator(data_ + size_); }
        reverse_iterator rend() { return reverse_iterator(data_); }

        const_iterator begin() const { return const_iterator(data_); }
        const_iterator end() const { return const_iterator(data_ + size_); }
        const_iterator cbegin() const { return const_iterator(data_); }
        const_iterator cend() const { return const_iterator(data_ + size_); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(data_); }
        const_reverse_iterator rend() const { return const_reverse_iterator(data_ + size_); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator(data_ + size_); }
        const_reverse_iterator crbend() const { return const_reverse_iterator(data_); }

        iterator last() { return iterator(data_ + size_ - 1); }
        const_iterator last() const { return const_iterator(data_ + size_ - 1); }

        bool gap_(size_type from, size_type length);

    private:
        allocator_type allocator_;
        size_type size_;
        size_type capacity_;
        pointer data_;

        
};

template <Keyable K, class V, size_t D>
unsorted_map<K, V, D>::unsorted_map(const std::initializer_list<value_type>& il) {
    capacity_ = D;
    size_ = 0;

    if (capacity_ < il.size()) {
        capacity_ = ((il.size() / D) + 1) * D;
    }

    data_ = allocator_traits::allocate(allocator_, capacity_);

    size_type counter = 0;
    for (auto elem : il) {
        allocator_traits::construct(allocator_, data_ + counter, elem);
        size_++;
        counter++;
    }
}

template <Keyable K, class V, size_t D>
unsorted_map<K, V, D>::~unsorted_map() {
    for (size_type i = 0; i < size_; i++) {
        allocator_traits::destroy(allocator_, data_ + i);
    }

    allocator_traits::deallocate(allocator_, data_, capacity_);
}

template <Keyable K, class V, size_t D> 
unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const value_type &val, const size_type pos) {
    if (pos > size_) {
        return end();
    }
    else {
        bool success = gap_(pos, 1);
        
        if (success) {            
            allocator_traits::construct(allocator_, data_ + pos, val);
            return iterator(&data_[pos]);
        }
        else {
            return end();
        }
    }
}

template <Keyable K, class V, size_t D>
unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const std::initializer_list<value_type>& il, const size_type pos) {
    if (pos > size_) {
        return end();
    }
    else {
        bool success = gap_(pos, il.size());
        if (success) {        
            for (size_type i = 0; i < il.size(); i++) {
                allocator_traits::construct(allocator_, data_ + pos + i, *(il.begin() + i));
            }
            return iterator(data_ + pos);
        }
        else {
            return end();
        }
    }
}

template <Keyable K, class V, size_t D>
unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const unsorted_map<key_type, mapped_type, D>& map, const size_type pos) {
    if (pos > size_) {
        return end();
    }
    else {
        bool success = gap_(pos, map.size_);
        if (success) {                
            for (size_type i = 0; i < map.size_; i++) {
                allocator_traits::construct(allocator_, data_ + pos + i, 
                    std::make_pair<>(map.data_[i].first, map.data_[i].second));
            }
            return iterator(data_ + pos);
        }
        else {
            return end();
        }
    }
}

template <Keyable K, class V, size_t D>
inline auto unsorted_map<K, V, D>::at(const key_type& key) {
    for (size_type i = 0; i < size_; i++) {
        if (data_[i].first == key) {
            return std::make_pair<>(iterator(&data_[i]), i);
        }
    }

    return std::make_pair<>(iterator(data_ + size_), npos);
}

template <Keyable K, class V, size_t D>
inline auto unsorted_map<K, V, D>::all(const key_type& key) {
    std::vector<std::pair<iterator, size_type>> out;
    for (size_type i = 0; i < size_; i++)
        if (data_[i].first == key) {
            std::pair<iterator, size_type> p = std::make_pair<>(&data_[i], i);
            out.push_back(p);
        }

    return out;
}

template <Keyable K, class V, size_t D>
inline void unsorted_map<K, V, D>::clear() {
    for (size_type i = 0; i < size_; i++)
        allocator_traits::destroy(allocator_, data_ + i);
    size_ = 0;
}

template <Keyable K, class V, size_t D>
inline bool unsorted_map<K, V, D>::reserve(size_type min_capacity) {
    if (min_capacity < size_)
        return false;

    size_type new_capacity = ((min_capacity / D) + 1) * D;
    return resize(new_capacity);
}

template <Keyable K, class V, size_t D>
bool unsorted_map<K, V, D>::resize(size_type new_capacity) {
    if (new_capacity < size_)
        return false;

    pointer new_data = allocator_traits::allocate(allocator_, new_capacity);
    for (size_type i = 0; i < size_ ; i++) {
        allocator_traits::construct(allocator_, new_data + i, data_[i]);
        allocator_traits::destroy(allocator_, data_ + i);
    }
    
    if (size_ != 0) {
        allocator_traits::deallocate(allocator_, data_, capacity_);
    }

    data_ = new_data;
    capacity_ = new_capacity;

    return true;
}

template <Keyable K, class V, size_t D>
bool unsorted_map<K, V, D>::gap_(size_type from, size_type length)
{
    bool success = true;

    if ((size_ + length) > capacity_) {
        success = reserve(size_ + length);
    }

    size_ = size_ + length;
    if (size_ <= length) {
        return true;
    }

    if (success) {
        if (from >= size_){
            return true;
        }
        else {
            for (size_type i = size_ - 1; i > from; i--) {
                allocator_traits::construct(allocator_, data_ + i, std::move(data_[i - length]));
                allocator_traits::destroy(allocator_, data_ + i - length);
            }
            return true;
        }
    }
    else {
        return false;
    }
}

#endif
