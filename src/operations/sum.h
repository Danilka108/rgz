#include <math.h>
#include "../num/num.h"
#include "../config.h"
#include "compare.h"

#ifndef RGZ_1_SUM_H
#define RGZ_1_SUM_H

Num *sum_unsigned_nums(Num *max_num, Num *min_num);

Num *subtract_unsigned_nums(Num *max_num, Num *min_num);

Num *sum_nums(Num *a_num, Num *b_num, Signs sign = Signs::positive);

#endif //RGZ_1_SUM_H
