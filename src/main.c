/**
* @mainpage
* # Загальне завдання
* 1. Розробити функцію.
*
* # Опис програми
* 2. Функціональне призначення
*  Програма призначена для разташування відьемних чисел вліво,  
*  додатніх вправо і нуль посередині.
* 3. Опис логічної структури
*    1) Щоб разташувати числа треба використовувати Бульбашку обратного виду.
*    2) Спочатку заповнюємо масив фіксованого розміру цілими числами.
*
* @author Shuriga Olexander.
* @date 23-dec-2020
*/

/**
* @file main.c
* Програма призначена для разташування відьемних чисел вліво,додатніх вправо і нуль посередині. 
* @author Shuriga Olexander
* @return Змінну з кількістю пар таких чисел.
* @version 0.1 
* date 23.12.2020 
*
*/

#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#define length_of_main_array 5
int function_of_filling_array(int, float*);

int main() {
    srand(time(NULL));
    float* main_array = (float*)malloc(length_of_main_array * sizeof(float));
    *main_array = function_of_filling_array(length_of_main_array, main_array);

    printf("\n");

    for (int i = 0; i < length_of_main_array; i++) {
        printf("\n%4f", main_array[i]);
    }

    printf("\n");
    printf("\n");

    float* ptr_One = main_array;
    float* ptr_Two = (main_array + length_of_main_array - 1);
    float* result_array = (float*)malloc(length_of_main_array * sizeof(float));

    /*
     |++|++|++|++|++|++|++|
      |   |             |
     ptr_One           ptr_Two
          |
         ptr_One + 1
    */

    /* Задача: положительные числа влево, отрицательные вправо и по середины нули */
    float element = 0;
    
    int n = length_of_main_array - 1;
    int i = 0;

    float* step_ptrOne = ptr_One;
    float* step_ptrTwo = ptr_Two;
    while (ptr_One != ptr_Two)
    {
        /* зафиксируем положение указателей */
        step_ptrOne = ptr_One;
        step_ptrTwo = ptr_Two;
        /* положительные числа влево */
        /* проверяем чтобы указатели находились в пределах границ массива */
        if (*ptr_One == 0) {
            float* tmp_step_ptrTwo = ptr_Two;
            /* предпросмотр для ptr_Two */
            if (*ptr_Two <= 0) {
                /* начинаем поиск слева направо 0 1 */
                /* проверяем чтобы указатели находились в пределах границ массива */
                while (ptr_Two != ptr_One && (element = *ptr_Two) <= 0) {
                    printf("[debug] --> 0 < %4f\n", *ptr_Two);
                    ptr_Two--;
                }
            }
            if (ptr_One != ptr_Two && *ptr_Two > 0) {
                float tmp = *ptr_Two;
                *ptr_Two = *ptr_One;
                *ptr_One = tmp;
                ptr_One = step_ptrOne;
                ptr_Two = step_ptrTwo;
                continue;
            } 
            /* откатываемся в предыдущее состояние */
            ptr_Two = tmp_step_ptrTwo;
        }
        /* проверяем чтобы указатели находились в пределах границ массива */
        while (ptr_One != ptr_Two && (element = *ptr_One) > 0) {
            printf("[debug] %4f > 0\n", *ptr_One);
            ptr_One++;
        }
        /* тут все элементы слева от ptr_One уже положительные */
        /* если все элементы уже отсортированы, выходим */
        if (ptr_One == ptr_Two)
        {
            printf("[debug] %4f 1=\n", *ptr_One);
            break;
        }
        /* отрицательные числа вправо */
        /* проверяем чтобы указатели находились в пределах границ массива */
        if (*ptr_Two == 0) {
            /* предпросмотр для ptr_One */
            float* tmp_step_ptrOne = ptr_One;
            if (*ptr_One > 0) {
                /* начинаем поиск справа налево -1 0 */
                /* проверяем чтобы указатели находились в пределах границ массива */
                while (ptr_One != ptr_Two && (element = *ptr_One) >= 0) {
                    printf("[debug] <-- %4f > 0\n", *ptr_One);
                    ptr_One++;
                }
            }
            if (ptr_One != ptr_Two && *ptr_One < 0) {
                float tmp = *ptr_Two;
                *ptr_Two = *ptr_One;
                *ptr_One = tmp;
                ptr_One = step_ptrOne;
                ptr_Two = step_ptrTwo;
                continue;
            }
            /* откатываемся в предыдущее состояние */
            ptr_One = tmp_step_ptrOne;
        }
        /* проверяем чтобы указатели находились в пределах границ массива */
        while (ptr_Two != ptr_One && (element = *ptr_Two) < 0) {
            printf("[debug] 0 < %4f\n", *ptr_Two);
            ptr_Two--;
        }
        /* тут все элементы справа от ptr_Two уже отрицательные, а сам элемент */
        /* если все элементы уже отсортированы, выходим */
        if (ptr_One == ptr_Two) {
            printf("[debug] %4f =2\n", *ptr_Two);
            break;
        }
        /* тут указатели еще не встретились */
        /* если один из элментов нужно переставить */
        printf("[debug] %4f [%ld] ? %4f [%ld] \n", *ptr_One, ptr_One - main_array, *ptr_Two, ptr_Two - main_array);
        /* -1 0 -> 0 -1 это будет гарантировать, что указатель ptr_Two будет сдвинут */
        /* 0 1 -> 1 0 это будет гарантировать, что указатель ptr_One будет сдвинут */ 
        /* повторяем цикл, так как состояние системы поменялось, указатели восстанавливаются */
        if (*ptr_One == 0 && *ptr_Two > 0)
        {
            float tmp = *ptr_Two;
            *ptr_Two = *ptr_One;
            *ptr_One = tmp;
            ptr_One = step_ptrOne;
            ptr_Two = step_ptrTwo;
            continue;
        }
        if (*ptr_One < 0 && *ptr_Two == 0)
        {
            float tmp = *ptr_Two;
            *ptr_Two = *ptr_One;
            *ptr_One = tmp;
            ptr_One = step_ptrOne;
            ptr_Two = step_ptrTwo;
            continue;
        }
        /* тут отдельный кейс на центральные элементы */
        while (ptr_One != ptr_Two && *ptr_One == 0 && *ptr_Two == 0) {
            ptr_One++;
        }
        while (ptr_Two != ptr_One && *ptr_One == 0 && *ptr_Two == 0) {
            ptr_Two--;
        }
        /* если все элементы уже отсортированы, выходим */
        if (ptr_One == ptr_Two) {
            printf("[debug] %4f 1=2\n", *ptr_Two);
            break;
        }
        if (step_ptrOne == ptr_One && step_ptrTwo == ptr_Two) {
            break;
        }
    }

    for (int i = 0; i < length_of_main_array; i++) {
        printf("\n%4f", main_array[i]);
    }

    printf("\n");
}



int function_of_filling_array(int length, float* mainArray) 
{
    for (int i = 0; i < length; i++) {
            *(mainArray + i) = (rand() % 10 + -3)/1.2 ;
    }
    return 0;
}