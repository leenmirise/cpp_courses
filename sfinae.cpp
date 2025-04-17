#include <iostream>
#include <cstdint>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>
#include <string>

// Проверка, что все типы в кортеже одинаковы
template <typename... Types>
struct AllSameTypes : std::true_type {};

template <typename T1, typename T2, typename... Rest>
struct AllSameTypes<T1, T2, Rest...>
        : std::conditional_t<
                std::is_same_v<T1, T2>,
                AllSameTypes<T2, Rest...>,
                std::false_type
        > {};

// Реализация для контейнеров (vector, list и т. д.)

template <typename Container>
auto PrintIpAddress(const Container& container) -> decltype(
container.begin(),
        container.end(),
        std::enable_if_t<
                !std::is_same_v<Container, std::string> &&
                !std::is_convertible_v<Container, const char*>
        >()
) {
    auto it = container.begin();
    if (it != container.end()) {
        std::cout << *it;
        ++it;
    }
    for (; it != container.end(); ++it) {
        std::cout << "." << *it;
    }
    std::cout << "\n";
}

// Реализация для целочисленных типов

template <typename IntegerType>
std::enable_if_t<std::is_integral_v<IntegerType>, void>
PrintIpAddress(IntegerType value) {
    const auto* byte_ptr = reinterpret_cast<const uint8_t*>(&value);
    for (size_t i = sizeof(IntegerType); i > 0; --i) {
        if (i != sizeof(IntegerType)) {
            std::cout << ".";
        }
        std::cout << static_cast<int>(byte_ptr[i - 1]);
    }
    std::cout << "\n";
}

// Реализация для строк

template <typename StringType>
std::enable_if_t<
        std::is_convertible_v<StringType, std::string>,
        void
>
PrintIpAddress(const StringType& str) {
    std::cout << str << "\n";
}

// Реализация для кортежей

template <size_t Index = 0, typename... TupleArgs>
std::enable_if_t<Index == sizeof...(TupleArgs), void>
PrintTupleElements(const std::tuple<TupleArgs...>&) {}

template <size_t Index = 0, typename... TupleArgs>
std::enable_if_t<Index < sizeof...(TupleArgs), void>
PrintTupleElements(const std::tuple<TupleArgs...>& tuple) {
    if constexpr (Index > 0) {
        std::cout << ".";
    }
    std::cout << std::get<Index>(tuple);
    PrintTupleElements<Index + 1>(tuple);
}

template <typename... TupleArgs>
void PrintIpAddress(const std::tuple<TupleArgs...>& tuple) {
    static_assert(
            AllSameTypes<TupleArgs...>::value,
            "Ошибка: элементы кортежа должны быть одного типа!"
    );
    PrintTupleElements(tuple);
    std::cout << "\n";
}

int main() {
    PrintIpAddress(int8_t{-1});                     // 255
    PrintIpAddress(int16_t{0});                     // 0.0
    PrintIpAddress(int32_t{2130706433});            // 127.0.0.1
    PrintIpAddress(int64_t{8875824491850138409});   // 123.45.67.89.101.112.131.41
    PrintIpAddress(std::string{"Hello, World!"});   // Hello, World!
    PrintIpAddress(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
    PrintIpAddress(std::list<short>{400, 300, 200, 100}); // 400.300.200.100
    PrintIpAddress(std::make_tuple(123, 456, 789, 0));    // 123.456.789.0

    return 0;
}