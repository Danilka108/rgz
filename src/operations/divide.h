#include "../num/num.h"
#include "sum.h"
#include "multiply.h"

#ifndef RGZ_DIVIDE_H
#define RGZ_DIVIDE_H

Num *divide_num(Num *, Num *);

Num *divide_remainder(Num **dividend, Num *divider);

#endif //RGZ_DIVIDE_H
