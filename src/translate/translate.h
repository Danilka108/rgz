#include <cmath>
#include "../num/num.h"
#include "../str/str.h"

#ifndef RGZ_1_TRANSLATE_H
#define RGZ_1_TRANSLATE_H

Num_chunk translate_str_to_num_chunk(Str *);

Str *translate_num_chunk_to_str(Num_chunk);

Num *translate_str_to_num(Str *);

Str *translate_num_to_str(Num *);

#endif // RGZ_1_TRANSLATE_H
