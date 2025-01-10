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
        unsorted_map();
        unsorted_map(const std::initializer_list<value_type>& il);
        ~unsorted_map();

        // Element addition
        iterator push_back(const value_type& val);
        iterator push_back(const key_type& key, const mapped_type& val);
        iterator push_back(const std::initializer_list<value_type>& il);
        iterator push_back(const unsorted_map<key_type, mapped_type, D>& map);
        iterator insert(const value_type& val, const size_type pos);
        iterator insert(const key_type& key, const mapped_type& val, const size_type pos);
        iterator insert(const std::initializer_list<value_type> il, const size_type pos);
        iterator insert(const unsorted_map<key_type, mapped_type> map, const size_type pos);

        // Element access
        iterator at(const size_type pos) { return pos < size_ ? iterator(&data_[pos]) : throw std::out_of_range("Out of range"); }
        auto at(const key_type key);  // return type : std::pair<iterator, size_type>
        auto all(const key_type key);  // return type : std::vector<std::pair<iterator, size_type>>
        pointer data() { return data_; }
        iterator operator[](const size_type pos) { at(pos); }
        auto operator[](const key_type key) { at(key); }

        // Element management
        void clear();
        void erase(key_type key);
        void swap(size_type from, size_type to);
        unsorted_map<key_type, mapped_type, D> copy();
        unsorted_map<key_type, mapped_type, D> move();
        
        // Memory related members
        size_type size() { return size_; }
        size_type capacity() { return capacity_; }
        allocator_type get_allocator() { return allocator_; }
        bool reserve(size_type min_capacity);
        bool shrink();
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

    private:
        allocator_type allocator_;
        size_type size_;
        size_type capacity_;
        pointer data_;
};

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::unsorted_map() : capacity_(D), size_(0), data_(allocator_traits::allocate(allocator_, capacity_)) {}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::unsorted_map(const std::initializer_list<value_type>& il) {
    capacity_ = D;
    size_ = 0;

    if (capacity_ < il.size())
        capacity_ = ((il.size() / D) + 1) * D;

    data_ = allocator_traits::allocate(allocator_, capacity_);

    size_type counter = 0;
    for (auto elem : il) {
        allocator_traits::construct(allocator_, data_ + counter, elem);
        size_++;
        counter++;
    }
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::~unsorted_map() {
    for (size_type i = 0; i < size_; i++)
        allocator_traits::destroy(allocator_, data_ + i);

    allocator_traits::deallocate(allocator_, data_, capacity_);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::push_back(const value_type& val) {
    bool success = true;
    
    if (size_ == capacity_)
        success = reserve(capacity_ + 1);
    
    if (success) {
        allocator_traits::construct(allocator_, data_ + size_, val);
        return iterator(&data_[size_++]);
    }
    else
        return iterator(data_ + size_);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::push_back(const key_type& key, const mapped_type& val) {
    value_type v = std::make_pair<>(key, val);
    return push_back(v);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::push_back(const std::initializer_list<value_type>& il) {
    bool success = true;

    if ((size_ + il.size()) > capacity_)
        success = reserve(size_ + il.size());

    if (success) {
        for (auto elem : il) {
            allocator_traits::construct(allocator_, data_ + size_, elem);
            size_++;
        }
        return iterator(&data_[size_ - il.size()]);
    }    
    else
        return iterator(data_ + size_);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::push_back(const unsorted_map<key_type, mapped_type, D>& map) {
    bool success = true;

    if ((size_ + map.size_) > capacity_)
        success = reserve(size_ + map.size_);

    if (success) {
        for (auto elem : map) {
            allocator_traits::construct(allocator_, data_ + size_, elem);
            size_++;
        }
        return iterator(&data_[size_ - map.size_]);
    }
    else
        return iterator(data_ + size_);
}

template <Keyable K, class V, size_t D> 
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const value_type &val, const size_type pos) {
    bool success = true;

    if (size_ == capacity_)
        success = reserve(size_ + 1);

    if (success) {
        size_++;
        for (size_type i = size_; i > pos; --i) {
            allocator_traits::construct(allocator_, data_ + i, data_[i-1]);
        }
        allocator_traits::construct(allocator_, data_ + pos, val);

        return iterator(data_ + pos);
    }

    return iterator(data_ + size_);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const key_type &key, const mapped_type &val, const size_type pos) {
    value_type v = std::make_pair<>(key, val);
    return insert(v, pos);
}

template <Keyable K, class V, size_t D>
inline unsorted_map<K, V, D>::iterator unsorted_map<K, V, D>::insert(const std::initializer_list<value_type> il, const size_type pos) {
    bool success = true;

    if ((size_ + il.size()) > capacity_)
        success = reserve(size_ + il.size());

    for (size_type )

    return iterator(data_ + size_);
}

template <Keyable K, class V, size_t D>
inline auto unsorted_map<K, V, D>::at(const key_type key) {
    for (size_type i = 0; i < size_; i++)
        if (data_[i].first == key)
            return std::make_pair<>(iterator(&data_[i]), i);

    return std::make_pair<>(iterator(data_ + size_), npos);
}

template <Keyable K, class V, size_t D>
inline auto unsorted_map<K, V, D>::all(const key_type key) {
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
inline bool unsorted_map<K, V, D>::shrink() {
    return resize(size_);
}

template <Keyable K, class V, size_t D>
inline bool unsorted_map<K, V, D>::resize(size_type new_capacity) {
    if (new_capacity < size_)
        return false;

    pointer new_data = allocator_traits::allocate(allocator_, new_capacity);
    for (size_type i = 0; i < size_ ; i++) {
        allocator_traits::construct(allocator_, new_data + i, std::move(data_[i]));
        allocator_traits::destroy(allocator_, data_ + i);
    }

    if (size_ != 0) {
        allocator_traits::deallocate(allocator_, data_, capacity_);
    }

    data_ = new_data;
    capacity_ = new_capacity;
    return true;
}

#endif
