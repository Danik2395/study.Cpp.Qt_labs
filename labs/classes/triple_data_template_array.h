#include <stdexcept>
#include <vector>
#include <concepts>
#include <algorithm>

namespace tripledataarray_detail
{
    template<typename T>
    concept TripleData = std::same_as<char, T> ||
                         std::same_as<int, T>  ||
                         std::same_as<double, T>;
}

template <tripledataarray_detail::TripleData T>
class TripleDataArray
{
    std::vector<T> data_vec;

public:
    TripleDataArray();
    TripleDataArray(std::vector<T> data_init) : data_vec(std::move(data_init)) {}

    void update_data(std::vector<T> data_update) { data_vec = std::move(data_update); }

    T get_result()
    {
        if (data_vec.empty()) throw std::runtime_error("get_result: data empty.");

        T result{};

        if constexpr (std::same_as<int, T>)
        {
            auto sum_data = [&result](T v){ result += v; };
            std::ranges::for_each(data_vec, sum_data);
        }
        else
        {
            result = *std::ranges::max_element(data_vec);
        }

        return result;
    }
};
