#include "choose_operation.hpp"

void choose_operation()
{
    auto operation = scan_operation();
    
    printf("Введите число №1: ");
    auto a_num = scan_num();
    printf("Введите число №2: ");
    auto b_num = scan_num();
    
    Num *num;
    
    switch (operation)
    {
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
