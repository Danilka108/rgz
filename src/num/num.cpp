#include "num.hpp"

Num *create_num(int len, Signs sign)
{
    Num *num = new Num;
    
    num->len = len;
    num->sign = sign;
    num->chunks = new Num_chunk[len];
    
    return num;
}

Num *create_num_from_num_chunk(Num_chunk num_chunk)
{
    Num *new_num = create_num(1, num_chunk < 0 ? Signs::negative : Signs::positive);
    new_num->chunks[0] = num_chunk;
    
    return new_num;
}

Num *copy_num(Num *num)
{
    Num *new_num = create_num(num->len, num->sign);
    for (int i = 0; i < num->len; i++) new_num->chunks[i] = num->chunks[i];
    
    return new_num;
}

void update_num(Num **num, Num *new_value)
{
    delete *num;
    *num = new_value;
}

void concat_num(Num **num, Num *num_addition)
{
    Num *new_num = create_num((*num)->len + num_addition->len, (*num)->sign);
    
    for (int i = 0; i < new_num->len; i++)
    {
        if (i < (*num)->len) new_num->chunks[i] = (*num)->chunks[i];
        else new_num->chunks[i] = num_addition->chunks[i - (*num)->len];
    }
    update_num(num, new_num);
}

Num *get_num_slice(Num *num, int slice_start, int slice_end)
{
    Num *slice = create_num(slice_end - slice_start, num->sign);
    
    int is_insignificant_zero = num->chunks[0] == 0;
    
    for (int i = slice_start, j = 0; i < slice_end && i < num->len; i++)
    {
        if (num->chunks[i] == 0 && i != num->len - 1 && is_insignificant_zero) continue;
        is_insignificant_zero = 0;
        
        slice->chunks[j++] = num->chunks[i];
        slice->len = j;
    }
    
    return slice;
}

void add_zeros_to_num(Num **num, int zeros_count)
{
    Num *new_num = create_num((*num)->len + zeros_count, (*num)->sign);
    
    for (int i = 0; i < new_num->len; i++)
    {
        if (i < (*num)->len) new_num->chunks[i] = (*num)->chunks[i];
        else new_num->chunks[i] = 0;
    }
    
    update_num(num, new_num);
}

Comparison_flags compare_unsigned_nums(Num *a_num, Num *b_num)
{
    if (a_num->len > b_num->len) return Comparison_flags::bigger;
    if (a_num->len < b_num->len) return Comparison_flags::smaller;
    
    for (int i = 0; i < a_num->len && i < b_num->len; i++)
    {
        if (a_num->chunks[i] > b_num->chunks[i]) return Comparison_flags::bigger;
        if (a_num->chunks[i] < b_num->chunks[i]) return Comparison_flags::smaller;
    }
    
    return Comparison_flags::equal;
}

int get_num_chunk_len(Num_chunk num_chunk)
{
    int len = 1;
    
    while (num_chunk /= 10) len++;
    
    return len;
}

int get_nums_delta_len(Num *a_num, Num *b_num)
{
    int a_num_first_chunk_len = get_num_chunk_len(a_num->chunks[0]);
    int b_num_first_chunk_len = get_num_chunk_len(b_num->chunks[0]);
    return a_num_first_chunk_len - b_num_first_chunk_len + NUM_CHUNK_LEN * (a_num->len - b_num->len);
}
