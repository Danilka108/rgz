#include "str.h"

Str *create_str(int len)
{
    Str *str = new Str;
    str->len = len;
    (*str).chars = new char[len];
    
    return str;
}
