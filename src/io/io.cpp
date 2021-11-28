#include "io.hpp"

Str *scan_str()
{
    auto str = create_str(NUM_MAX_LEN);
    scanf(STR_FORMAT, str->chars);
    str->len = strlen(str->chars);
    
    if (!validate_str(str))
    {
        printf("Ошбика! Значение не действительно.");
        exit(EXIT_FAILURE);
    }
    
    return str;
}

Num *scan_num()
{
    auto str = scan_str();
    auto sign = Signs::positive;
    Num *num;
    
    if (str->chars[0] == '-' || str->chars[0] == '+')
    {
        sign = str->chars[0] == '-' ? Signs::negative : Signs::positive;
        str->chars++;
        str->len--;
    }
    
    num = translate_str_to_num(str);
    num->sign = sign;
    
    delete str;
    return num;
}

void print_num(Num *num)
{
    auto str = translate_num_to_str(num);
    
    int start = 0;
    while (str->chars[start] == '0' && start < num->len * NUM_CHUNK_LEN - 1)
        start++;
    
    if (num->sign == Signs::negative) printf("-");
    
    auto end = create_str(1);
    end->chars[0] = '\0';
    
    concat_str(&str, end);
    
    printf("%s", str->chars + start);
    
    delete str;
}

Operations scan_operation()
{
    char operation;
    printf("Выберите операцию (+, -, *, /): ");
    scanf("%c", &operation);
    
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
            printf("Ошибка! Данная операция не определена.");
            exit(EXIT_FAILURE);
    }
}

