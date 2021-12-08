#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NUM_CHUNK_LEN 9
#define NUM_MAX_LEN 1024

#define STR_FORMAT "%1023s"

enum class Comparison_flags {
  smaller,
  equal,
  bigger,
};

enum class Operations {
  multiply = '*',
  sum = '+',
  subtract = '-',
  divide = '/'
};

enum class Signs {
  positive,
  negative,
};

typedef long long int Num_chunk;

typedef struct {
  size_t len;
  Signs sign;
  Num_chunk *chunks;
} Num;

struct Str {
  size_t len;
  char *chars;
};

Num *create_num(size_t, Signs = Signs::positive);

Num *create_num_from_num_chunk(Num_chunk);

Num *copy_num(Num *);

void update_num(Num **, Num *);

void concat_num(Num **, Num *);

void trim_num_zeros(Num **);

Num *get_num_slice(Num *, size_t, size_t);

void add_zero_chunks_to_num(Num **, size_t);

Comparison_flags compare_nums(Num *, Num *);

Comparison_flags compare_unsigned_nums(Num *, Num *);

size_t get_num_chunk_len(Num_chunk);

size_t get_nums_delta_len(Num *, Num *);

Str *create_str(size_t);

void update_str(Str **, Str *);

void concat_str(Str **, Str *);

Str *get_str_slice(Str *, size_t, size_t);

int validate_str(Str *);

Num_chunk translate_str_to_num_chunk(Str *);

Str *translate_num_chunk_to_str(Num_chunk);

Num *translate_str_to_num(Str *);

Str *translate_num_to_str(Num *);

Str *scan_str();

Num *scan_num();

void print_num(Num *);

Operations scan_operation();

Num *sum_nums(Num *, Num *, Signs = Signs::positive);

Num *sum_unsigned_nums(Num *, Num *);

Num *subtract_unsigned_nums(Num *, Num *);

Num *multiply_nums(Num *, Num *);

Num *multiply_unsigned_nums(Num *, Num *);

Num *multiply_unsigned_num_to_num_chunk(Num *num, Num_chunk num_chunk);

Num *divide_num(Num *, Num *);

Num *divide_unsigned_num(Num *, Num *);

void update_remainder(Num **, Num *, size_t, size_t);

Num *divide_unsigned_remainder(Num **, Num *);

Num *divide_num(Num *, Num *);

Num *divide_unsigned_num(Num *, Num *);

void update_remainder(Num **, Num *, size_t, size_t);

Num *divide_unsigned_remainder(Num **, Num *);

void choose_operation();

int main() {
  choose_operation();
  return 0;
}

Num *create_num(size_t len, Signs sign) {
  auto num = new Num;

  num->len = len;
  num->sign = sign;
  num->chunks = new Num_chunk[len];

  return num;
}

Num *create_num_from_num_chunk(Num_chunk num_chunk) {
  auto new_num =
      create_num(1, num_chunk < 0 ? Signs::negative : Signs::positive);
  new_num->chunks[0] = num_chunk;

  return new_num;
}

Num *copy_num(Num *num) {
  auto new_num = create_num(num->len, num->sign);
  for (size_t i = 0; i < num->len; i++)
    new_num->chunks[i] = num->chunks[i];

  return new_num;
}

void update_num(Num **num, Num *new_value) {
  delete *num;
  *num = new_value;
}

void concat_num(Num **num, Num *num_addition) {
  auto new_num = create_num((*num)->len + num_addition->len, (*num)->sign);

  for (size_t i = 0; i < new_num->len; i++) {
    if (i < (*num)->len)
      new_num->chunks[i] = (*num)->chunks[i];
    else
      new_num->chunks[i] = num_addition->chunks[i - (*num)->len];
  }

  update_num(num, new_num);
}

void trim_num_zeros(Num **num) {
  auto new_num = create_num((*num)->len, (*num)->sign);

  for (size_t i = 0, j = 0, is_insignificant_zeros = 1; i < (*num)->len; i++) {
    if ((*num)->chunks[i] == 0 && is_insignificant_zeros)
      continue;
    is_insignificant_zeros = 0;

    new_num->chunks[j++] = (*num)->chunks[i];
    new_num->len = j;
  }

  update_num(num, new_num);
}

Num *get_num_slice(Num *num, size_t slice_start, size_t slice_end) {
  auto slice = create_num(slice_end - slice_start, num->sign);

  for (size_t i = slice_start, j = 0; i < slice_end && i < num->len; i++) {
    slice->chunks[j++] = num->chunks[i];
    slice->len = j;
  }

  return slice;
}

void add_zero_chunks_to_num(Num **num, size_t zero_chunks_count) {
  auto new_num = create_num((*num)->len + zero_chunks_count, (*num)->sign);

  for (size_t i = 0; i < new_num->len; i++) {
    if (i < (*num)->len)
      new_num->chunks[i] = (*num)->chunks[i];
    else
      new_num->chunks[i] = 0;
  }

  update_num(num, new_num);
}

Comparison_flags compare_unsigned_nums(Num *a_num, Num *b_num) {
  if (a_num->len > b_num->len)
    return Comparison_flags::bigger;
  if (a_num->len < b_num->len)
    return Comparison_flags::smaller;

  for (size_t i = 0; i < a_num->len && i < b_num->len; i++) {
    if (a_num->chunks[i] > b_num->chunks[i])
      return Comparison_flags::bigger;
    if (a_num->chunks[i] < b_num->chunks[i])
      return Comparison_flags::smaller;
  }

  return Comparison_flags::equal;
}

Comparison_flags compare_nums(Num *a_num, Num *b_num) {
  auto zero = create_num_from_num_chunk(0);

  if (a_num->sign == b_num->sign)
    return compare_unsigned_nums(a_num, b_num);

  if (compare_unsigned_nums(a_num, zero) == Comparison_flags::equal &&
      compare_unsigned_nums(b_num, zero) == Comparison_flags::equal)
    return Comparison_flags::equal;

  return a_num->sign == Signs::negative ? Comparison_flags::smaller
                                        : Comparison_flags::bigger;
}

size_t get_num_chunk_len(Num_chunk num_chunk) {
  size_t len = 1;

  while (num_chunk /= 10)
    len++;

  return len;
}

size_t get_nums_delta_len(Num *a_num, Num *b_num) {
  size_t a_num_first_chunk_len = get_num_chunk_len(a_num->chunks[0]);
  size_t b_num_first_chunk_len = get_num_chunk_len(b_num->chunks[0]);
  return a_num_first_chunk_len - b_num_first_chunk_len +
         NUM_CHUNK_LEN * (a_num->len - b_num->len);
}

Str *create_str(size_t len) {
  auto str = new Str;
  str->len = len;
  (*str).chars = new char[len];

  return str;
}

void update_str(Str **str, Str *new_value) {
  delete *str;
  *str = new_value;
}

void concat_str(Str **str, Str *str_addition) {
  auto new_str = create_str((*str)->len + str_addition->len);

  for (size_t i = 0; i < new_str->len; i++) {
    if (i < (*str)->len)
      new_str->chars[i] = (*str)->chars[i];
    else
      new_str->chars[i] = str_addition->chars[i - (*str)->len];
  }

  update_str(str, new_str);
}

Str *get_str_slice(Str *str, size_t slice_start, size_t slice_end) {
  auto new_str = create_str(slice_end - slice_start);

  for (size_t j = 0, i = slice_start; i < slice_end && i < str->len; i++) {
    new_str->chars[j++] = str->chars[i];
    new_str->len = j;
  }

  return new_str;
}

int validate_str(Str *str) {
  size_t validation_start = 0;

  if ((str->chars[0] == '-' || str->chars[0] == '+') && str->len == 1)
    return 0;

  if (str->chars[0] == '-' || str->chars[0] == '+')
    validation_start++;

  if (str->chars[validation_start] == '0' && str->len - validation_start > 1)
    return 0;

  for (size_t i = validation_start; i < str->len; i++) {
    if (str->chars[i] >= '0' && str->chars[i] <= '9')
      continue;
    return 0;
  }

  return 1;
}

Num_chunk translate_str_to_num_chunk(Str *str) {
  Num_chunk num_chunk = 0;

  for (size_t i = 0; i < str->len; i++) {
    int char_as_int = str->chars[i] - '0';
    num_chunk += (Num_chunk)(char_as_int * pow(10, str->len - (i + 1)));
  }

  return num_chunk;
}

Str *translate_num_chunk_to_str(Num_chunk num_chunk) {
  auto num_chunk_len = get_num_chunk_len(num_chunk);
  auto str = create_str(NUM_CHUNK_LEN);

  for (size_t i = 0; i < NUM_CHUNK_LEN - num_chunk_len; i++)
    str->chars[i] = '0';

  for (int i = NUM_CHUNK_LEN - num_chunk_len; i < NUM_CHUNK_LEN; i++)
    str->chars[i] =
        '0' + num_chunk / (Num_chunk)pow(10, NUM_CHUNK_LEN - i - 1) % 10;

  return str;
}

Num *translate_str_to_num(Str *str) {
  auto num = create_num(ceil((double)str->len / NUM_CHUNK_LEN));

  for (size_t i = 1; i <= num->len; i++) {
    ssize_t chunk_start = str->len - i * NUM_CHUNK_LEN;
    ssize_t chunk_len =
        chunk_start < 0 ? chunk_start + NUM_CHUNK_LEN : NUM_CHUNK_LEN;
    chunk_start = chunk_start < 0 ? 0 : chunk_start;

    auto str_slice = get_str_slice(str, chunk_start, chunk_start + chunk_len);
    num->chunks[num->len - i] = translate_str_to_num_chunk(str_slice);

    delete str_slice;
  }

  return num;
}

Str *translate_num_to_str(Num *num) {
  Str *str = nullptr;

  for (int i = 0; i < num->len; i++) {
    Str *num_chunk_as_str = translate_num_chunk_to_str(num->chunks[i]);

    if (str == nullptr)
      str = num_chunk_as_str;
    else
      concat_str(&str, num_chunk_as_str);
  }

  return str;
}

Str *scan_str() {
  auto str = create_str(NUM_MAX_LEN);
  scanf(STR_FORMAT, str->chars);
  str->len = strlen(str->chars);

  if (!validate_str(str)) {
    printf("Ошбика! Значение не действительно.");
    exit(EXIT_FAILURE);
  }

  return str;
}

Num *scan_num() {
  auto str = scan_str();
  auto sign = Signs::positive;
  Num *num;

  if (str->chars[0] == '-' || str->chars[0] == '+') {
    sign = str->chars[0] == '-' ? Signs::negative : Signs::positive;
    str->chars++;
    str->len--;
  }

  num = translate_str_to_num(str);
  num->sign = sign;

  delete str;
  return num;
}

void print_num(Num *num) {
  auto str = translate_num_to_str(num);

  int start = 0;
  while (str->chars[start] == '0' && start < num->len * NUM_CHUNK_LEN - 1)
    start++;

  if (num->sign == Signs::negative)
    printf("-");

  auto end = create_str(1);
  end->chars[0] = '\0';

  concat_str(&str, end);

  printf("%s", str->chars + start);

  delete str;
}

Operations scan_operation() {
  char operation;
  printf("Выберите операцию (+, -, *, /): ");
  scanf("%c", &operation);

  switch (operation) {
  case (char)(Operations::multiply):
    return Operations::multiply;
  case (char)(Operations::sum):
    return Operations::sum;
  case (char)(Operations::subtract):
    return Operations::subtract;
  case (char)(Operations::divide):
    return Operations::divide;
  default:
    printf("Ошибка! Данная операция не определена.");
    exit(EXIT_FAILURE);
  }
}

Num *sum_nums(Num *a_num, Num *b_num, Signs sign) {
  auto zero = create_num_from_num_chunk(0);

  auto b_num_copy = copy_num(b_num);
  b_num_copy->sign =
      b_num_copy->sign == sign ? Signs::positive : Signs::negative;

  auto comparison = compare_unsigned_nums(a_num, b_num);

  if (a_num->sign != b_num_copy->sign &&
      comparison == Comparison_flags::equal) {
    delete b_num_copy;
    return zero;
  }

  delete zero;

  auto max_num = comparison == Comparison_flags::bigger ? a_num : b_num_copy;
  auto min_num = comparison == Comparison_flags::smaller ? a_num : b_num_copy;

  auto sum = max_num->sign == min_num->sign
                 ? sum_unsigned_nums(max_num, min_num)
                 : subtract_unsigned_nums(max_num, min_num);

  sum->sign = max_num->sign;

  trim_num_zeros(&sum);

  delete b_num_copy;
  return sum;
}

Num *sum_unsigned_nums(Num *max_num, Num *min_num) {
  auto delta_len = max_num->len - min_num->len;

  auto num = create_num(max_num->len + 1);

  Num_chunk buffer = 0;
  for (ssize_t i = max_num->len - 1; i >= 0; i--) {
    Num_chunk sum = max_num->chunks[i] + buffer;
    if (i >= delta_len)
      sum += min_num->chunks[i - delta_len];

    num->chunks[i + 1] = sum % (Num_chunk)pow(10, NUM_CHUNK_LEN);
    buffer = sum / (Num_chunk)pow(10, NUM_CHUNK_LEN);
  }

  num->chunks[0] = buffer;

  return num;
}

Num *subtract_unsigned_nums(Num *max_num, Num *min_num) {
  size_t delta_len = max_num->len - min_num->len;

  auto num = create_num(max_num->len);

  Num_chunk buffer = 0;
  for (ssize_t i = max_num->len - 1; i >= 0; i--) {
    Num_chunk subtract = max_num->chunks[i] + buffer;
    if (i >= delta_len)
      subtract -= min_num->chunks[i - delta_len];

    if (subtract < 0 && i != 0) {
      buffer = -1;
      subtract += (Num_chunk)pow(10, NUM_CHUNK_LEN);
    }

    num->chunks[i] = subtract;
  }

  return num;
}

Num *multiply_nums(Num *a_num, Num *b_num) {
  auto zero = create_num_from_num_chunk(0);

  if (compare_unsigned_nums(a_num, zero) == Comparison_flags::equal)
    return zero;

  if (compare_unsigned_nums(b_num, zero) == Comparison_flags::equal)
    return zero;

  delete zero;

  auto comparison = compare_unsigned_nums(a_num, b_num);
  auto max_num = comparison == Comparison_flags::bigger ? a_num : b_num;
  auto min_num = comparison == Comparison_flags::smaller ? a_num : b_num;

  auto num = multiply_unsigned_nums(max_num, min_num);

  trim_num_zeros(&num);
  num->sign = a_num->sign == b_num->sign ? Signs::positive : Signs::negative;

  return num;
}

Num *multiply_unsigned_nums(Num *max_num, Num *min_num) {
  Num *num = create_num_from_num_chunk(0);

  for (ssize_t i = min_num->len - 1; i >= 0; i--) {
    Num *multiply_num =
        multiply_unsigned_num_to_num_chunk(max_num, min_num->chunks[i]);

    add_zero_chunks_to_num(&multiply_num, min_num->len - i - 1);
    update_num(&num, sum_nums(multiply_num, num));

    delete multiply_num;
  }

  return num;
}

Num *multiply_unsigned_num_to_num_chunk(Num *num, Num_chunk num_chunk) {
  auto multiply_num = create_num(1 + num->len);

  Num_chunk buffer = 0;
  for (ssize_t i = num->len - 1; i >= 0; i--) {
    Num_chunk multiply = num->chunks[i] * num_chunk + buffer;

    auto divider = (Num_chunk)pow(10, NUM_CHUNK_LEN);
    multiply_num->chunks[i + 1] = (Num_chunk)multiply % divider;
    buffer = (Num_chunk)multiply / divider;
  }

  multiply_num->chunks[0] = buffer;

  return multiply_num;
}

Num *divide_num(Num *dividend, Num *divisor) {
  auto zero = create_num_from_num_chunk(0);

  if (compare_unsigned_nums(divisor, zero) == Comparison_flags::equal) {
    printf("Ошибка! Нельзя делить на нуль.");
    exit(EXIT_FAILURE);
  }

  if (compare_unsigned_nums(dividend, zero) == Comparison_flags::equal)
    return zero;

  if (compare_unsigned_nums(dividend, divisor) == Comparison_flags::smaller)
    return zero;

  delete zero;

  auto num = divide_unsigned_num(dividend, divisor);
  num->sign =
      dividend->sign == divisor->sign ? Signs::positive : Signs::negative;

  return num;
}

Num *divide_unsigned_num(Num *dividend, Num *divisor) {
  auto one = create_num_from_num_chunk(1);
  auto zero = create_num_from_num_chunk(0);

  auto quotient = create_num_from_num_chunk(0);
  auto remainder = create_num_from_num_chunk(0);

  size_t slice_start = 0;
  size_t slice_end = divisor->len;

  do {
    update_remainder(&remainder, dividend, slice_start, slice_end);

    if (compare_unsigned_nums(remainder, zero) == Comparison_flags::equal) {
      concat_num(&quotient, zero);
      slice_start = slice_end;
      slice_end += 1;
      continue;
    }

    auto comparison = compare_unsigned_nums(divisor, remainder);

    if (comparison == Comparison_flags::bigger && slice_end >= dividend->len) {
      add_zero_chunks_to_num(&quotient, 1);
      break;
    }

    if (comparison == Comparison_flags::bigger) {
      slice_start = slice_end;
      slice_end++;
      continue;
    }

    if (comparison == Comparison_flags::equal) {
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

void update_remainder(Num **remainder, Num *dividend, size_t slice_start,
                      size_t slice_end) {
  auto zero = create_num_from_num_chunk(0);

  auto dividend_slice =
      get_num_slice(dividend, slice_start,
                    slice_end < dividend->len ? slice_end : dividend->len);

  if (compare_unsigned_nums(*remainder, zero) == Comparison_flags::equal)
    update_num(remainder, dividend_slice);
  else
    concat_num(remainder, dividend_slice);

  delete zero;
}

Num *divide_unsigned_remainder(Num **remainder, Num *original_divisor) {
  auto zero = create_num_from_num_chunk(0);
  ssize_t delta_len = get_nums_delta_len(*remainder, original_divisor);
  auto additional_zeros = create_num_from_num_chunk(pow(10, delta_len));

  auto divisor = multiply_nums(original_divisor, additional_zeros);
  auto dividend = copy_num(*remainder);
  auto quotient = create_num_from_num_chunk(0);

  do {
    auto subtract = sum_nums(dividend, divisor, Signs::negative);

    if (compare_nums(subtract, zero) == Comparison_flags::smaller) {
      update_num(&additional_zeros,
                 create_num_from_num_chunk(pow(10, --delta_len)));
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

void choose_operation() {
  auto operation = scan_operation();

  printf("Введите число №1: ");
  auto a_num = scan_num();
  printf("Введите число №2: ");
  auto b_num = scan_num();

  Num *num;

  switch (operation) {
  case Operations::sum:
    num = sum_nums(a_num, b_num);
    break;
  case Operations::subtract:
    num = sum_nums(a_num, b_num, Signs::negative);
    break;
  case Operations::multiply:
    num = multiply_nums(a_num, b_num);
    break;
  case Operations::divide:
    num = divide_num(a_num, b_num);
    break;
  }

  printf("Результат: ");
  print_num(num);

  delete a_num;
  delete b_num;
  delete num;
}
