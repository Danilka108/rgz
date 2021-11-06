#include "num.h"

Num *create_num(int len, Signs sign)
{
    Num *num = new Num();
    num->len = len;
    num->sign = sign;
    
    (*num).chunks = new Num_chunk[len];
    
    return num;
}

Num *copy_num(Num *num)
{
    Num *new_num = create_num(num->len, num->sign);
    for (int i = 0; i < num->len; i++) new_num->chunks[i] = num->chunks[i];
    
    return new_num;
}

Num *get_num_slice(Num *num, int slice_start, int slice_end)
{
    Num *slice = create_num(slice_end - slice_start, num->sign);
    
    int is_insignificant_zero = 0;
    
    for (int i = slice_start, j = 0; i < slice_end && i < num->len; i++)
    {
        if (num->chunks[i] == 0 && i != num->len - 1 && is_insignificant_zero) continue;
        is_insignificant_zero = 0;
        
        slice->chunks[j++] = num->chunks[i];
        slice->len = j;
    }
    
    return slice;
}

int get_num_chunk_len(Num_chunk num_chunk)
{
    int len = 1;
    
    while (num_chunk /= 10) len++;
    
    return len;
}

Num *add_zeros_to_num(Num *num, int zeros_count)
{
    Num *new_num = create_num(num->len + zeros_count, num->sign);
    
    for (int i = 0; i < new_num->len; i++)
    {
        if (i < num->len) new_num->chunks[i] = num->chunks[i];
        else new_num->chunks[i] = 0;
    }
    
    return new_num;
}
