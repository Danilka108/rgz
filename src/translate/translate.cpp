#include "translate.hpp"

Num_chunk translate_str_to_num_chunk(Str *str)
{
    Num_chunk num_chunk = 0;
    
    for (int i = 0; i < str->len; i++)
    {
        int char_as_int = str->chars[i] - '0';
        num_chunk += (Num_chunk) (char_as_int * pow(10, str->len - (i + 1)));
    }
    
    return num_chunk;
}

Str *translate_num_chunk_to_str(Num_chunk num_chunk)
{
    int num_chunk_len = get_num_chunk_len(num_chunk);
    Str *str = create_str(NUM_CHUNK_LEN);
    
    for (int i = 0; i < NUM_CHUNK_LEN - num_chunk_len; i++)
        str->chars[i] = '0';
    
    for (int i = NUM_CHUNK_LEN - num_chunk_len; i < NUM_CHUNK_LEN; i++)
        str->chars[i] = '0' + num_chunk / (Num_chunk) pow(10, NUM_CHUNK_LEN - i - 1) % 10;
    
    return str;
}

Num *translate_str_to_num(Str *str)
{
    Num *num = create_num(ceil((double) str->len / NUM_CHUNK_LEN));
    
    for (int i = 1; i <= num->len; i++)
    {
        int chunk_start = str->len - i * NUM_CHUNK_LEN;
        int chunk_len = chunk_start < 0 ? chunk_start + NUM_CHUNK_LEN : NUM_CHUNK_LEN;
        chunk_start = chunk_start < 0 ? 0 : chunk_start;
        
        Str *str_slice = get_str_slice(str, chunk_start, chunk_start + chunk_len);
        num->chunks[num->len - i] = translate_str_to_num_chunk(str_slice);
        
        delete str_slice;
    }
    
    return num;
}

Str *translate_num_to_str(Num *num)
{
    Str *str = nullptr;
    
    for (int i = 0; i < num->len; i++)
    {
        Str *num_chunk_as_str = translate_num_chunk_to_str(num->chunks[i]);
        
        if (str == nullptr) str = num_chunk_as_str;
        else concat_str(&str, num_chunk_as_str);
    }
    
    return str;
}