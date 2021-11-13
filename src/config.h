#ifndef RGZ_1_CONFIG_H
#define RGZ_1_CONFIG_H

#define NUM_CHUNK_LEN 9
#define NUM_MAX_LEN 1024

#define STR_FORMAT "%1023s"

enum class Comparison_flags
{
    smaller,
    equal,
    bigger,
};

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
    divide = '/'
};

enum class Signs
{
    positive,
    negative,
};

#endif //RGZ_1_CONFIG_H
