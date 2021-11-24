#include <cmath>
#include "../config.h"

#ifndef RGZ_1_NUM_H
#define RGZ_1_NUM_H

typedef long long int Num_chunk;

struct Num
{
    int len;
    Signs sign;
    Num_chunk *chunks;
};

Num *create_num(int, Signs = Signs::positive);

Num *create_num_from_num_chunk(Num_chunk);

Num *copy_num(Num *);

void update_num(Num **, Num *);

void concat_num(Num **, Num *);

Num *get_num_slice(Num *, int, int);

void add_zeros_to_num(Num **, int);

Comparison_flags compare_unsigned_nums(Num *, Num *);

int get_num_chunk_len(Num_chunk);

int get_nums_delta_len(Num *, Num *);

int get_num_len(Num *);

#endif //RGZ_1_NUM_H