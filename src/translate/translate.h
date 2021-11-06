#include <cmath>
#include "../num/num.h"
#include "../str/str.h"

#ifndef RGZ_1_TRANSLATE_H
#define RGZ_1_TRANSLATE_H

Num_chunk translate_chars_to_num_chunk(char *chars, int chars_len);

char *translate_num_chunk_to_chars(Num_chunk num_chunk);

Num *translate_str_to_num(Str *str);

Str *translate_num_to_str(Num *num);

#endif // RGZ_1_TRANSLATE_H
