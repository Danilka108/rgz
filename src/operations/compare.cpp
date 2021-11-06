#include "compare.h"

Comparison_flags compare_unsigned_nums(Num *a_num, Num *b_num)
{
    if (a_num->len > b_num->len) return Comparison_flags::bigger;
    if (a_num->len < b_num->len) return Comparison_flags::smaller;
    
    for (int i = 0; i < a_num->len && i < b_num->len; i++) {
        if (a_num->chunks[i] > b_num->chunks[i]) return Comparison_flags::bigger;
        if (a_num->chunks[i] < b_num->chunks[i]) return Comparison_flags::smaller;
    }
    
    return Comparison_flags::equal;
}
