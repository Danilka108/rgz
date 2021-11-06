#ifndef RGZ_1_CONFIG_H
#define RGZ_1_CONFIG_H

#define NUM_CHUNK_LEN 9
#define NUM_MAX_LEN 256

#define STR_FORMAT "%255s"
#define NUM_FORMAT "%lli"

enum class Validation_flags
{
    valid,
    invalid,
};

enum class Operations
{
    multiply = '*',
    sum = '+',
    subtract = '-',
};

enum class Signs
{
    positive,
    negative,
};

#endif //RGZ_1_CONFIG_H
