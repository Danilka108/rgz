#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../config.h"
#include "../str/str.h"
#include "../num/num.h"
#include "../translate/translate.h"

#ifndef RGZ_1_IO_H
#define RGZ_1_IO_H

Validation_flags validate_str(Str *str);

Str *scan_str();

Num *scan_num();

void print_num(Num *num);

Operations scan_operation();

#endif //RGZ_1_IO_H
