#include "divide.hpp"

Num *divide_num(Num *dividend, Num *divisor)
{
    auto zero = create_num_from_num_chunk(0);
    
    if (compare_unsigned_nums(divisor, zero) == Comparison_flags::equal)
    {
        printf("Ошибка! Нельзя делить на нуль.");
        exit(EXIT_SUCCESS);
    }
    
    if (compare_unsigned_nums(dividend, zero) == Comparison_flags::equal)
        return zero;
    
    if (compare_unsigned_nums(dividend, divisor) == Comparison_flags::smaller)
        return zero;
    
    delete zero;
    
    auto num = divide_unsigned_num(dividend, divisor);
    num->sign = dividend->sign == divisor->sign ? Signs::positive : Signs::negative;
    
    return num;
}

Num *divide_unsigned_num(Num *dividend, Num *divisor)
{
    auto one = create_num_from_num_chunk(1);
    auto zero = create_num_from_num_chunk(0);
    
    auto quotient = create_num_from_num_chunk(0);
    auto remainder = create_num_from_num_chunk(0);
    
    size_t slice_start = 0;
    size_t slice_end = divisor->len;
    
    Comparison_flags comparison;
    do
    {
        update_remainder(&remainder, dividend, slice_start, slice_end);
        
        if (compare_unsigned_nums(remainder, zero) == Comparison_flags::equal)
        {
            concat_num(&quotient, zero);
            slice_start = slice_end;
            slice_end += 1;
            continue;
        }
        
        comparison = compare_unsigned_nums(divisor, remainder);
        
        if (comparison == Comparison_flags::bigger && slice_end >= dividend->len)
        {
            add_zero_chunks_to_num(&quotient, 1);
            break;
        }
        
        if (comparison == Comparison_flags::bigger)
        {
            slice_start = slice_end;
            slice_end++;
            continue;
        }
        
        if (comparison == Comparison_flags::equal)
        {
            concat_num(&quotient, one);
            update_num(&remainder, zero);
            
            slice_start = slice_end;
            slice_end++;
            continue;
        }
        
        concat_num(&quotient, divide_unsigned_remainder(&remainder, divisor));
        trim_num_zeros(&remainder);
        
        slice_start = slice_end;
        slice_end++;
    } while (slice_end <= dividend->len);
    
    delete zero;
    delete one;
    delete remainder;
    
    return quotient;
}

void update_remainder(Num **remainder, Num *dividend, size_t slice_start, size_t slice_end)
{
    auto zero = create_num_from_num_chunk(0);
    
    auto dividend_slice = get_num_slice(
            dividend,
            slice_start,
            slice_end < dividend->len ? slice_end : dividend->len
    );
    
    if (compare_unsigned_nums(*remainder, zero) == Comparison_flags::equal)
        update_num(remainder, dividend_slice);
    else
        concat_num(remainder, dividend_slice);
    
    delete zero;
}

Num *divide_unsigned_remainder(Num **remainder, Num *original_divisor)
{
    auto zero = create_num_from_num_chunk(0);
    ssize_t delta_len = get_nums_delta_len(*remainder, original_divisor);
    auto additional_zeros = create_num_from_num_chunk(pow(10, delta_len));
    
    auto divisor = multiply_nums(original_divisor, additional_zeros);
    auto dividend = copy_num(*remainder);
    auto quotient = create_num_from_num_chunk(0);
    
    do
    {
        auto subtract = sum_nums(dividend, divisor, Signs::negative);
        
        if (compare_nums(subtract, zero) == Comparison_flags::smaller)
        {
            update_num(&additional_zeros, create_num_from_num_chunk(pow(10, --delta_len)));
            update_num(&divisor, multiply_nums(original_divisor, additional_zeros));
            
            delete subtract;
            continue;
        }
        
        update_num(&quotient, sum_nums(quotient, additional_zeros));
        update_num(&dividend, subtract);
    } while (delta_len >= 0);
    
    update_num(remainder, dividend);
    
    delete divisor;
    delete zero;
    delete additional_zeros;
    
    return quotient;
}
