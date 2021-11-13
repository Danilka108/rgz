#include "divide.hpp"

Num *divide_num(Num *dividend, Num *divider)
{
    Num *one = create_num_from_num_chunk(1);
    Num *zero = create_num_from_num_chunk(0);
    
    Num *quotient = create_num_from_num_chunk(0);
    Num *remainder = create_num_from_num_chunk(0);
    
    int slice_start = 0;
    int slice_end = divider->len;
    
    Comparison_flags comparison;
    
    do
    {
        Num *dividend_slice = get_num_slice(dividend, slice_start, slice_end < dividend->len ? slice_end :
                                                                   dividend->len);
        
        if (compare_unsigned_nums(remainder, zero) == Comparison_flags::equal)
            update_num(&remainder, dividend_slice);
        else
            concat_num(&remainder, dividend_slice);
        
        if (compare_unsigned_nums(remainder, zero) == Comparison_flags::equal)
        {
            concat_num(&quotient, zero);
            slice_start = slice_end;
            slice_end += 1;
            continue;
        }
        
        comparison = compare_unsigned_nums(divider, remainder);
        
        if (comparison == Comparison_flags::bigger)
        {
            if (slice_end >= dividend->len)
            {
                add_zeros_to_num(&quotient, 1);
                break;
            }
            
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
        
        concat_num(&quotient, divide_remainder(&remainder, divider));
        update_num(&remainder, get_num_slice(remainder, 0, remainder->len));
        
        slice_start = slice_end;
        slice_end++;
    } while (slice_end <= dividend->len);
    
    
    quotient->sign = dividend->sign == divider->sign
                     ? Signs::positive
                     : Signs::negative;
    
    return quotient;
}

Num *divide_remainder(Num **dividend, Num *divider)
{
    Num *zero = create_num_from_num_chunk(0);
    
    Num *dividend_copy = copy_num(*dividend);
    Num *divider_copy = copy_num(divider);
    
    Num *quotient = create_num_from_num_chunk(0);
    Num *remainder = create_num_from_num_chunk(0);
    
    int delta_len = get_nums_delta_len(*dividend, divider);
    int degree = (int) pow(10, delta_len);
    
    Num *additional_zeros = create_num_from_num_chunk(degree);
    update_num(&divider_copy, multiply_nums(divider, additional_zeros));
    
    do
    {
        auto comparison = compare_unsigned_nums(divider_copy, dividend_copy);
        
        if (comparison == Comparison_flags::bigger)
        {
            delta_len--;
            if (delta_len < 0) break;
            
            degree = (int) pow(10, delta_len);
            additional_zeros = create_num_from_num_chunk(degree);
            update_num(&divider_copy, multiply_nums(divider, additional_zeros));
            
            continue;
        }
        
        update_num(&quotient, sum_nums(quotient, additional_zeros));
        
        remainder = sum_nums(dividend_copy, divider_copy, Signs::negative);
        update_num(&dividend_copy, remainder);
    } while (delta_len >= 0);
    
    delete divider_copy;
    delete additional_zeros;
    delete zero;
    
    *dividend = remainder;
    return quotient;
}
