#include "../num/num.hpp"
#include "sum.hpp"
#include "multiply.hpp"

#ifndef RGZ_DIVIDE_H
#define RGZ_DIVIDE_H

Num *divide_num(Num *, Num *);

Num *divide_unsigned_num(Num *, Num *);

void update_remainder(Num **, Num *, size_t, size_t);

Num *divide_unsigned_remainder(Num **, Num *);

#endif //RGZ_DIVIDE_H
