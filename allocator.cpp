#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <memory>
#include <cstddef>

template<typename T>
struct my_allocator {
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    size_t max_elements;
    char* memory_pool = nullptr;
    size_t used = 0;

    my_allocator(const my_allocator& other) : max_elements(other.max_elements), used(other.used) {
        if (other.memory_pool) {
            memory_pool = static_cast<char*>(std::malloc(max_elements * sizeof(T)));
            if (!memory_pool) {
                throw std::bad_alloc();
            }
        }
    }

    template<typename U>
    struct rebind {
        using other = my_allocator<U>;
    };

    template<typename U>
    my_allocator(const my_allocator<U>& other) : max_elements(other.max_elements), used(other.used) {
        memory_pool = static_cast<char*>(std::malloc(max_elements * sizeof(T)));
        if (!memory_pool) {
            throw std::bad_alloc();
        }
    }

    my_allocator(size_t n) : max_elements(n) {
        memory_pool = static_cast<char*>(std::malloc(max_elements * sizeof(T)));
        if (!memory_pool) {
            throw std::bad_alloc();
        }
    }

    my_allocator() : max_elements(0), memory_pool(nullptr) {}

    ~my_allocator() {
        if (memory_pool) {
            std::free(memory_pool);
        }
    }

    T* allocate(size_t n) {
        if (used + n * sizeof(T) > max_elements * sizeof(T)) {
            printf("Bad alloc!");
            throw std::bad_alloc();
        }
        T* p = reinterpret_cast<T*>(memory_pool + used);
        used += n * sizeof(T);
        return p;
    }

    void deallocate(T* p, std::size_t n) {}

    template<typename U, typename ...Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T* p) {
        p->~T();
    }
};

template <typename T, typename Allocator = std::allocator<T>>
class MyList {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    using NodeAllocatorTraits = std::allocator_traits<NodeAllocator>;

    Node* head = nullptr;
    NodeAllocator allocator;

public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit Iterator(Node* node) : current(node) {}

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }

        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return !(*this == other); }

    private:
        Node* current;
    };

    MyList() = default;
    MyList(const Allocator& alloc) : allocator(alloc) {}

    ~MyList() {
        clear();
    }

    void push_front(const T& value) {
        Node* newNode = NodeAllocatorTraits::allocate(allocator, 1);
        NodeAllocatorTraits::construct(allocator, newNode, value);

        newNode->next = head;
        head = newNode;
    }

    bool empty() const {
        return head == nullptr;
    }

    size_t size() const {
        size_t count = 0;
        Node* current = head;
        while (current) {
            ++count;
            current = current->next;
        }
        return count;
    }

    void clear() {
        while (head) {
            Node* nextNode = head->next;
            NodeAllocatorTraits::destroy(allocator, head);
            NodeAllocatorTraits::deallocate(allocator, head, 1);
            head = nextNode;
        }
    }

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};

int factorial(int i)
{
    if (i==0) return 1;
    else return i*factorial(i-1);
}

int main() {
    // создание стандартного аллокатора
    std::map<int, int> norm_map;

    for(int i = 0; i < 10; i++){
        norm_map[i] = factorial(i);
    }

    // использование собственного аллокатора с мапой

    size_t n = 10;
    my_allocator<std::pair<const int, int>> alloc(n);

    auto m = std::map<int, int, std::less<int>, my_allocator<std::pair<const int, int>>
    >(std::less<int>(), alloc);

    for(int i = 0; i < 9; i++){
        m[i] = factorial(i);
        std::cout << i << "\t" << m[i] << std::endl;
    }

//    try {
//        m[10] = factorial(10);
//        std::cout << "Don't work!" << std::endl;
//    } catch (const std::bad_alloc&) {
//        std::cout << "Work!" << std::endl;
//    }

    // свой контейнер

    MyList<int> list1;
    for(size_t i = 0; i < 10; i++){
        list1.push_front(i);
    }

//    for (auto i = list1.begin(); i != list1.end(); ++i) {
//        std::cout << *i << " ";
//    }

    // свой контейнер со своим аллокатором

    my_allocator<int> alloc2(n);
    MyList<int, my_allocator<int>> list2(alloc2);

    for(int i = 0; i < 10; i++){
        list2.push_front(i);
    }

    for (auto i = list2.begin(); i != list2.end(); ++i) {
        std::cout << *i << " ";
    }

//    try {
//        list2.push_front(10);
//        std::cout << "Don't work!" << std::endl;
//    } catch (const std::bad_alloc&) {
//        std::cout << "Work!" << std::endl;
//    }

    return 0;
}