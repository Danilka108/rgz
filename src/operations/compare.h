#include "../config.h"
#include "../num/num.h"

#ifndef RGZ_1_COMPARE_H
#define RGZ_1_COMPARE_H

enum class Comparison_flags
{
    smaller,
    equal,
    bigger,
};

Comparison_flags compare_unsigned_nums(Num *a_num, Num *b_num);

#endif //RGZ_1_COMPARE_H
