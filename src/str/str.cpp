#include "str.h"

Str *create_str(int len)
{
    Str *str = new Str;
    str->len = len;
    (*str).chars = new char[len];
    
    return str;
}

void update_str(Str **str, Str *new_value)
{
    delete *str;
    *str = new_value;
}

void concat_str(Str **str, Str *str_addition)
{
    Str *new_str = create_str((*str)->len + str_addition->len);
    
    for (int i = 0; i < new_str->len; i++)
    {
        if (i < (*str)->len) new_str->chars[i] = (*str)->chars[i];
        else new_str->chars[i] = str_addition->chars[i - (*str)->len];
    }
    
    update_str(str, new_str);
}

Str *get_str_slice(Str *str, int slice_start, int slice_end)
{
    Str *new_str = create_str(slice_end - slice_start);
    
    for (int j = 0, i = slice_start; i < slice_end && i < str->len; i++)
    {
        new_str->chars[j++] = str->chars[i];
        new_str->len = j;
    }
    
    return new_str;
}
