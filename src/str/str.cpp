#include "str.hpp"

Str *create_str(size_t len)
{
    auto str = new Str;
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
    auto new_str = create_str((*str)->len + str_addition->len);
    
    for (size_t i = 0; i < new_str->len; i++)
    {
        if (i < (*str)->len) new_str->chars[i] = (*str)->chars[i];
        else new_str->chars[i] = str_addition->chars[i - (*str)->len];
    }
    
    update_str(str, new_str);
}

Str *get_str_slice(Str *str, size_t slice_start, size_t slice_end)
{
    auto new_str = create_str(slice_end - slice_start);
    
    for (size_t j = 0, i = slice_start; i < slice_end && i < str->len; i++)
    {
        new_str->chars[j++] = str->chars[i];
        new_str->len = j;
    }
    
    return new_str;
}

int validate_str(Str *str)
{
    size_t validation_start = 0;
    
    if ((str->chars[0] == '-' || str->chars[0] == '+') && str->len == 1)
        return 0;
    
    if (str->chars[0] == '-' || str->chars[0] == '+')
        validation_start++;
    
    if (str->chars[validation_start] == '0' && str->len - validation_start > 1) return 0;
    
    for (size_t i = validation_start; i < str->len; i++)
    {
        if (str->chars[i] >= '0' && str->chars[i] <= '9') continue;
        return 0;
    }
    
    return 1;
}
