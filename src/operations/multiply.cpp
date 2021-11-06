#include "multiply.h"

Num *multiply_num_to_num_chunk(Num *num, Num_chunk num_chunk)
{
    Num *multiply_num = create_num(1 + num->len);
    
    Num_chunk buffer = 0;
    for (int i = num->len - 1; i >= 0; i--)
    {
        Num_chunk multiply = num->chunks[i] * num_chunk + buffer;
        Num_chunk divider = (Num_chunk) pow(10, NUM_CHUNK_LEN);
        multiply_num->chunks[i + 1] = (Num_chunk) multiply % divider;
        buffer = (Num_chunk) multiply / divider;
    }
    
    multiply_num->chunks[0] = buffer;
    multiply_num = get_num_slice(multiply_num, 0, multiply_num->len);
    
    return multiply_num;
}

Num *multiply_unsigned_nums(Num *max_num, Num *min_num)
{
    /*
    Num *num = create_num(1);
    num->chunks[0] = 0;
    
    for (int i = min_num->len - 1; i >= 0; i--)
    {
        Num *multiply_num = multiply_num_to_num_chunk(max_num, min_num->chunks[i]);
        multiply_num = add_zeros_to_num(multiply_num, i - min_num->len);
        
        printf("\nnum - ");
        print_num(multiply_num);
        printf("\n");
        num = sum_nums(multiply_num, num);
        delete multiply_num;
    }
    
    return num;
    */
}

Num *multiply_nums(Num *a_num, Num *b_num)
{
    /*
    if (a_num->chunks[0] == 0 || b_num->chunks[0] == 0)
    {
        Num *zero = create_num(1);
        zero->chunks[0] = 0;
        
        return zero;
    }
    
    Comparison_flags comparison = compare_unsigned_nums(a_num, b_num);
    Num *max_num = comparison == Comparison_flags::bigger ? a_num : b_num;
    Num *min_num = comparison == Comparison_flags::smaller ? a_num : b_num;
    
    Num *num = multiply_unsigned_nums(max_num, min_num);
    
    num = get_num_slice(num, 0, num->len);
    num->sign = a_num->sign == b_num->sign ? Signs::positive : Signs::negative;
    
    return num;
     */
}