#include "sum.h"

Num *sum_unsigned_nums(Num *max_num, Num *min_num)
{
    int delta_len = max_num->len - min_num->len;
    
    Num *num = create_num(max_num->len + 1);
    
    Num_chunk buffer = 0;
    for (int i = max_num->len - 1; i >= 0; i--)
    {
        Num_chunk sum = max_num->chunks[i] + buffer;
        if (i >= delta_len) sum += min_num->chunks[i - delta_len];
        
        num->chunks[i + 1] = sum % (Num_chunk) pow(10, NUM_CHUNK_LEN);
        buffer = sum / (Num_chunk) pow(10, NUM_CHUNK_LEN);
    }
    
    num->chunks[0] = buffer;
    
    return num;
}

Num *subtract_unsigned_nums(Num *max_num, Num *min_num)
{
    int delta_len = max_num->len - min_num->len;
    
    Num *num = create_num(max_num->len);
    
    Num_chunk buffer = 0;
    for (int i = max_num->len - 1; i >= 0; i--)
    {
        Num_chunk subtract = max_num->chunks[i] + buffer;
        if (i >= delta_len) subtract -= min_num->chunks[i - delta_len];
        
        if (subtract < 0 && i != 0)
        {
            buffer = -1;
            subtract += (Num_chunk) pow(10, NUM_CHUNK_LEN);
        }
        
        num->chunks[i] = subtract;
    }
    
    return num;
}

Num *sum_nums(Num *a_num, Num *b_num, Signs sign)
{
    Num *zero = create_num(1, Signs::positive);
    zero->chunks[0] = 0;
    
    b_num->sign = sign == b_num->sign
                  ? Signs::positive
                  : Signs::negative;
    
    Comparison_flags comparison = compare_unsigned_nums(a_num, b_num);
    Num *max_num = comparison == Comparison_flags::bigger ? a_num : b_num;
    Num *min_num = comparison == Comparison_flags::smaller ? a_num : b_num;
    
    Num *sum = max_num->sign == min_num->sign
               ? sum_unsigned_nums(max_num, min_num)
               : comparison == Comparison_flags::equal
                 ? zero
                 : (delete zero, subtract_unsigned_nums(max_num, min_num));
    
    sum = get_num_slice(sum, 0, sum->len);
    
    return sum;
}