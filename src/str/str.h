#ifndef RGZ_1_STR_H
#define RGZ_1_STR_H

struct Str
{
    int len;
    char *chars;
};

Str *create_str(int len);

#endif //RGZ_1_STR_H
