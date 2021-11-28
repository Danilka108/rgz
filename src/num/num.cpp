#include "num.hpp"

Num *create_num(size_t len, Signs sign)
{
    auto num = new Num;
    
    num->len = len;
    num->sign = sign;
    num->chunks = new Num_chunk[len];
    
    return num;
}

Num *create_num_from_num_chunk(Num_chunk num_chunk)
{
    auto new_num = create_num(1, num_chunk < 0 ? Signs::negative : Signs::positive);
    new_num->chunks[0] = num_chunk;
    
    return new_num;
}

Num *copy_num(Num *num)
{
    auto new_num = create_num(num->len, num->sign);
    for (size_t i = 0; i < num->len; i++) new_num->chunks[i] = num->chunks[i];
    
    return new_num;
}

void update_num(Num **num, Num *new_value)
{
    delete *num;
    *num = new_value;
}

void concat_num(Num **num, Num *num_addition)
{
    auto new_num = create_num((*num)->len + num_addition->len, (*num)->sign);
    
    for (size_t i = 0; i < new_num->len; i++)
    {
        if (i < (*num)->len) new_num->chunks[i] = (*num)->chunks[i];
        else new_num->chunks[i] = num_addition->chunks[i - (*num)->len];
    }
    
    update_num(num, new_num);
}

void trim_num_zeros(Num **num)
{
    auto new_num = create_num((*num)->len, (*num)->sign);
    
    for (size_t i = 0, j = 0, is_insignificant_zeros = 1; i < (*num)->len; i++)
    {
        if ((*num)->chunks[i] == 0 && is_insignificant_zeros) continue;
        is_insignificant_zeros = 0;
        
        new_num->chunks[j++] = (*num)->chunks[i];
        new_num->len = j;
    }
    
    update_num(num, new_num);
}

Num *get_num_slice(Num *num, size_t slice_start, size_t slice_end)
{
    auto slice = create_num(slice_end - slice_start, num->sign);
    
    for (size_t i = slice_start, j = 0; i < slice_end && i < num->len; i++)
    {
        slice->chunks[j++] = num->chunks[i];
        slice->len = j;
    }
    
    return slice;
}

void add_zero_chunks_to_num(Num **num, size_t zero_chunks_count)
{
    auto new_num = create_num((*num)->len + zero_chunks_count, (*num)->sign);
    
    for (size_t i = 0; i < new_num->len; i++)
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
    
    for (size_t i = 0; i < a_num->len && i < b_num->len; i++)
    {
        if (a_num->chunks[i] > b_num->chunks[i]) return Comparison_flags::bigger;
        if (a_num->chunks[i] < b_num->chunks[i]) return Comparison_flags::smaller;
    }
    
    return Comparison_flags::equal;
}

Comparison_flags compare_nums(Num *a_num, Num *b_num)
{
    auto zero = create_num_from_num_chunk(0);
    
    if (a_num->sign == b_num->sign) return compare_unsigned_nums(a_num, b_num);
    
    if (compare_unsigned_nums(a_num, zero) == Comparison_flags::equal &&
        compare_unsigned_nums(b_num, zero) == Comparison_flags::equal)
        return Comparison_flags::equal;
    
    return a_num->sign == Signs::negative ? Comparison_flags::smaller : Comparison_flags::bigger;
}

size_t get_num_chunk_len(Num_chunk num_chunk)
{
    size_t len = 1;
    
    while (num_chunk /= 10) len++;
    
    return len;
}

size_t get_nums_delta_len(Num *a_num, Num *b_num)
{
    size_t a_num_first_chunk_len = get_num_chunk_len(a_num->chunks[0]);
    size_t b_num_first_chunk_len = get_num_chunk_len(b_num->chunks[0]);
    return a_num_first_chunk_len - b_num_first_chunk_len + NUM_CHUNK_LEN * (a_num->len - b_num->len);
}