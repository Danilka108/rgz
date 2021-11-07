#ifndef RGZ_1_STR_H
#define RGZ_1_STR_H

struct Str
{
    int len;
    char *chars;
};

Str *create_str(int);

void update_str(Str **, Str *);

void concat_str(Str **, Str *);

Str *get_str_slice(Str *, int, int);

#endif //RGZ_1_STR_H
