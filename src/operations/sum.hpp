#include <cmath>
#include "../num/num.hpp"
#include "../config.hpp"

#ifndef RGZ_1_SUM_H
#define RGZ_1_SUM_H

Num *sum_nums(Num *, Num *, Signs = Signs::positive);

Num *sum_unsigned_nums(Num *, Num *);

Num *subtract_unsigned_nums(Num *, Num *);

#endif //RGZ_1_SUM_H
