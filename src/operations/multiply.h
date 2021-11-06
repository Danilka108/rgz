#include "../num/num.h"
#include "compare.h"
#include "sum.h"
#include "../io/io.h"
#include <stdio.h>

#ifndef RGZ_1_MULTIPLY_H
#define RGZ_1_MULTIPLY_H

Num *multiply_num_to_num_chunk(Num *num, Num_chunk num_chunk);

Num *multiply_unsigned_nums(Num *max_num, Num *min_num);

Num *multiply_nums(Num *a_num, Num *b_num);

#endif //RGZ_1_MULTIPLY_H
