#include "io.hpp"

Validation_flags validate_str(Str *str)
{
    for (int i = 0; i < str->len; i++)
    {
        if (i == 0 && str->chars[i] == '-' && str->len == 1)
            return Validation_flags::invalid;
        if (i == 0 && str->chars[i] == '-')
            continue;
        
        switch (str->chars[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                continue;
            default:
                return Validation_flags::invalid;
        }
    }
    
    return Validation_flags::valid;
}

Str *scan_str()
{
    Str *str = create_str(NUM_MAX_LEN);
    scanf(STR_FORMAT, str->chars);
    str->len = strlen(str->chars);
    
    if (validate_str(str) == Validation_flags::invalid)
    {
        printf("Ошбика. Значение не является валидным.");
        exit(0);
    }
    
    return str;
}

Num *scan_num()
{
    Str *str = scan_str();
    Num *num;
    
    if (str->chars[0] == '-')
    {
        str->chars += 1;
        str->len -= 1;
        
        num = translate_str_to_num(str);
        num->sign = Signs::negative;
    } else
    {
        num = translate_str_to_num(str);
        num->sign = Signs::positive;
    }
    
    delete str;
    return num;
}

void print_num(Num *num)
{
    Str *str = translate_num_to_str(num);
    
    int start = 0;
    while (str->chars[start] == '0' && start < num->len * NUM_CHUNK_LEN - 1)
        start++;
    
    if (num->sign == Signs::negative) printf("-");
    
    Str *end = create_str(1);
    end->chars[0] = '\0';
    
    concat_str(&str, end);
    
    printf("%s", str->chars + start);
    
    delete str;
}

Operations scan_operation()
{
    char operation;
    printf("Выберите операцию (+, -, *, /): ");
    scanf("%1s", &operation);
    
    switch (operation)
    {
        case (char) (Operations::multiply):
            return Operations::multiply;
        case (char) (Operations::sum):
            return Operations::sum;
        case (char) (Operations::subtract):
            return Operations::subtract;
        case (char) (Operations::divide):
            return Operations::divide;
        default:
            printf("Ошибка. Данная операция не определена.");
            exit(0);
    }
}

