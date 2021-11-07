#include <math.h>
#include "../num/num.h"
#include "../config.h"

#ifndef RGZ_1_SUM_H
#define RGZ_1_SUM_H

Num *sum_unsigned_nums(Num *, Num *);

Num *subtract_unsigned_nums(Num *, Num *);

Num *sum_nums(Num *, Num *, Signs = Signs::positive);

#endif //RGZ_1_SUM_H
