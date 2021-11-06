#include "translate.h"

Num_chunk translate_chars_to_num_chunk(char *chars, int chars_len)
{
    Num_chunk num_chunk = 0;
    
    for (int i = 0; i < chars_len; i++)
    {
        int char_as_int = chars[i] - '0';
        num_chunk += (Num_chunk) (char_as_int * pow(10, chars_len - (i + 1)));
    }
    
    return num_chunk;
}

char *translate_num_chunk_to_chars(Num_chunk num_chunk)
{
    int num_chunk_len = get_num_chunk_len(num_chunk);
    char *chars = new char[NUM_CHUNK_LEN];
    
    if (num_chunk_len < NUM_CHUNK_LEN)
        for (int i = 0; i < NUM_CHUNK_LEN - num_chunk_len; i++)
            chars[i] = '0';
    
    for (int i = NUM_CHUNK_LEN - num_chunk_len; i < NUM_CHUNK_LEN; i++)
        chars[i] = '0' + num_chunk / (Num_chunk) pow(10, NUM_CHUNK_LEN - i - 1) % 10;
    
    return chars;
}

Num *translate_str_to_num(Str *str)
{
    Num *num = create_num((int) ceil((double) str->len / NUM_CHUNK_LEN));
    
    for (int i = 1; i <= num->len; i++)
    {
        int chunk_start = str->len - i * NUM_CHUNK_LEN;
        int chunk_len =
                chunk_start < 0 ? chunk_start + NUM_CHUNK_LEN : NUM_CHUNK_LEN;
        chunk_start = chunk_start < 0 ? 0 : chunk_start;
        
        num->chunks[num->len - i] =
                translate_chars_to_num_chunk((*str).chars + chunk_start, chunk_len);
    }
    
    return num;
}

Str *translate_num_to_str(Num *num)
{
    Str *str = create_str(num->len * NUM_CHUNK_LEN);
    
    for (int i = 0; i < num->len; i++)
    {
        char *chars = translate_num_chunk_to_chars(num->chunks[i]);
        
        for (int j = 0; j < NUM_CHUNK_LEN; j++)
        {
            str->chars[i * NUM_CHUNK_LEN + j] = chars[j];
        }
        
        delete[] chars;
    }
    
    return str;
}