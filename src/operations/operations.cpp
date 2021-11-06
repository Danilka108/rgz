#include "operations.h"

void choose_operation()
{
    Operations operation = scan_operation();
    
    printf("Введите число №1: ");
    Num *a_num = scan_num();
    printf("Введите число №2: ");
    Num *b_num = scan_num();
    
    Num *num;
    
    switch (operation)
    {
        case Operations::sum:
            num = sum_nums(a_num, b_num, Signs::positive);
            break;
        case Operations::subtract:
            num = sum_nums(a_num, b_num, Signs::negative);
            break;
        case Operations::multiply:
            num = multiply_nums(a_num, b_num);
            break;
    }
    
    print_num(num);
    
    delete a_num;
    delete b_num;
    delete num;
}
