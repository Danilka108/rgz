#include <cstring>

#ifndef RGZ_1_STR_H
#define RGZ_1_STR_H

struct Str
{
    size_t len;
    char *chars;
};

Str *create_str(size_t);

void update_str(Str **, Str *);

void concat_str(Str **, Str *);

Str *get_str_slice(Str *, size_t, size_t);

int validate_str(Str *);

#endif //RGZ_1_STR_H
