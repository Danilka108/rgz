#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "../config.hpp"
#include "../str/str.hpp"
#include "../num/num.hpp"
#include "../translate/translate.hpp"

#ifndef RGZ_1_IO_H
#define RGZ_1_IO_H

Str *scan_str();

Num *scan_num();

void print_num(Num *);

Operations scan_operation();

#endif //RGZ_1_IO_H
