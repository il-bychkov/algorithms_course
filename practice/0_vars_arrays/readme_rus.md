# Практическое занятие 0 - Адреса, переменные, массивы и алгоритмы на массивах

### Часть 0: Введение в трансляцию и компиляцию на языке C
- Трансляция: компиляторы и интерпретаторы
- Что происходит внутри IDE: как код на языке программирования трансформируется в машинный код
### Часть 1: Адреса и переменные
**Исходный код:** addresses.с\
**Заметка:** В данном примере необходимо:
- создать несколько переменных разных типов и показать как для них выделилась память
- показать размеры различных типов данных (в качестве примеров)
- показать адресную арифметику - добавление 1 к разным типам данных\

**!!!ВАЖНО!!!:**
- в выводе посчитать и показать, что действительно адрес + 1 получается новый адрес
(адрес потенциального начала следующей переменной такого же типа)

```c 
#include <stdio.h>
int main()
{
    int intVariable = 30;
    float floatVariable = 1.1;
    double doubleVariable = 1.1;
    char charVariable = 'c';

    printf("int start address = %p\n",&intVariable);
    printf("int size          = %lu\n",sizeof(int));
    printf("int end address   = %p\n\n",&intVariable + 1);

    printf("float start address = %p\n",&floatVariable);
    printf("float size          = %lu\n",sizeof(floatVariable));
    printf("float end   address = %p\n\n",&floatVariable + 1);

    printf("double start address = %p\n",&doubleVariable);
    printf("double size          = %lu\n",sizeof(doubleVariable));
    printf("double end address   = %p\n\n",&doubleVariable + 1);

    printf("char start address = %p\n",&charVariable);
    printf("char size          = %lu\n",sizeof(charVariable));
    printf("char end   address = %p\n\n",&charVariable + 1);
}
```

Output: addresses.c
```bash
$ ./a.out 
int start address = 0x7ffeed9c5b4c
int size          = 4
int end address   = 0x7ffeed9c5b50

float start address = 0x7ffeed9c5b48
float size          = 4
float end   address = 0x7ffeed9c5b4c

double start address = 0x7ffeed9c5b40
double size          = 8
double end address   = 0x7ffeed9c5b48

char start address = 0x7ffeed9c5b3f
char size          = 1
char end   address = 0x7ffeed9c5b40
```

### Section 1: Addresses & arrays

Source: addresses.c

```c 
#include <stdio.h>
int main()
{
    const int arrLen = 10;
    int intArray[arrLen] = {10, 11, 12, 13 ,14 ,15 ,16 ,17, 18, 19};

    
    for (int i = 0; i < arrLen; i++)
        printf("int array element shift = [%d] -  value stored = %d  - address = %p\n",i, intArray[i], &intArray[i]);
    return 0;
}
```
Output: addresses.c
```bash
$ ./a.out 
int array element shift = [0] -  value stored = 10  - address = 0x7ffee9b45b20
int array element shift = [1] -  value stored = 11  - address = 0x7ffee9b45b24
int array element shift = [2] -  value stored = 12  - address = 0x7ffee9b45b28
int array element shift = [3] -  value stored = 13  - address = 0x7ffee9b45b2c
int array element shift = [4] -  value stored = 14  - address = 0x7ffee9b45b30
int array element shift = [5] -  value stored = 15  - address = 0x7ffee9b45b34
int array element shift = [6] -  value stored = 16  - address = 0x7ffee9b45b38
int array element shift = [7] -  value stored = 17  - address = 0x7ffee9b45b3c
int array element shift = [8] -  value stored = 18  - address = 0x7ffee9b45b40
int array element shift = [9] -  value stored = 19  - address = 0x7ffee9b45b44
```
