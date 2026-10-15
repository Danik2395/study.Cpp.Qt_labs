#pragma once
#include <algorithm>
#include <stdexcept>

class Patrol
{
    int number = 0;

public:
    Patrol() = default;

    void check(int value)
    {
        static constexpr int divisors[]{13, 17, 11, 7};

        bool is_multiple = false;
        auto check_val = [value, &is_multiple](int divisor)
        {
            if (value % divisor != 0) return;

            is_multiple = true;
        };

        std::ranges::for_each(divisors, check_val);

        if (!is_multiple) throw std::invalid_argument("Not a multiple of 13, 17, 11 or 7.");

        number = value;
    }

    int get_number() const
    {
        return number;
    }
};
