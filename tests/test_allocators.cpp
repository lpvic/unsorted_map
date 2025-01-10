#include <memory>
#include <iostream>

int main()
{
    using allocator_type = std::allocator<int>;
    using allocator_traits = std::allocator_traits<allocator_type>;

    int* arr;
    allocator_type alloc;
    int counter = 0;
    int size = 10;
    int capacity = 20;

    arr = allocator_traits::allocate(alloc, capacity);

    for (auto i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 0})
    {
        allocator_traits::construct(alloc, arr + counter, i);
        counter++;
    }

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ", ";
    std::cout << std::endl;

    for (int i = size; i > 4; --i)
        allocator_traits::construct(alloc, arr + i, arr[i - 1]);
    size++;

    allocator_traits::construct(alloc, arr + 4, 12);

    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ", ";
    std::cout << std::endl;

    allocator_traits::deallocate(alloc, arr, 10);

}