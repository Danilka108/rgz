#include "multiply.hpp"

Num *multiply_num_and_num_chunk(Num *num, Num_chunk num_chunk)
{
    Num *multiply_num = create_num(1 + num->len);
    
    Num_chunk buffer = 0;
    for (int i = num->len - 1; i >= 0; i--)
    {
        Num_chunk multiply = num->chunks[i] * num_chunk + buffer;
        auto divider = (Num_chunk) pow(10, NUM_CHUNK_LEN);
        multiply_num->chunks[i + 1] = (Num_chunk) multiply % divider;
        buffer = (Num_chunk) multiply / divider;
    }
    
    multiply_num->chunks[0] = buffer;
    
    return multiply_num;
}

Num *multiply_unsigned_nums(Num *max_num, Num *min_num)
{
    Num *num = create_num_from_num_chunk(0);
    
    for (int i = min_num->len - 1; i >= 0; i--)
    {
        Num *multiply_num = multiply_num_and_num_chunk(max_num, min_num->chunks[i]);
        
        add_zeros_to_num(&multiply_num, min_num->len - i - 1);
        
        update_num(&num, sum_nums(multiply_num, num));
        delete multiply_num;
    }
    
    return num;
}

Num *multiply_nums(Num *a_num, Num *b_num)
{
    if (a_num->chunks[0] == 0 || b_num->chunks[0] == 0)
        return create_num_from_num_chunk(0);
    
    auto comparison = compare_unsigned_nums(a_num, b_num);
    auto max_num = comparison == Comparison_flags::bigger ? a_num : b_num;
    auto min_num = comparison == Comparison_flags::smaller ? a_num : b_num;
    
    auto num = multiply_unsigned_nums(max_num, min_num);
    
    num = get_num_slice(num, 0, num->len);
    num->sign = a_num->sign == b_num->sign ? Signs::positive : Signs::negative;
    
    return num;
}
