# Практическое занятие 1
## Задачи на массивы из контеста 0

### Обмены

Общий алгоритм работы:
- идем циклом с начала до середины массива (или с конца до середины), пусть индекс текущего элемента = $i$
- берем равноудаленные элементы $a_i$, $a_{n-i}$ и обмениваем их значения

  Обмен возможен через два подхода:
  - с использованием переменной-буфера
  - с использованием различных бинарных операций

При использовании бинарных операций нужно быть аккуратным:
- вычитание, сложение, умножение/деление - работают лишь в специфических случаях, когда их результат умещается в тип данных. Более того, применимы лишь к целочисленным типам.
- Исключающее ИЛИ (XOR) горазде более гибкий способ, работает всегда. Применим к различным типам данных.

Далее LIVE CODING:

```c 
#include <stdio.h>

int main() 
{

    int a = 42;
    int b = 800;

    printf("initial state\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
    // POTENTIAL PROBLEM: OVERFLOW
    a = a + b;
    b = a - b;
    a = a - b;

    printf("after add-sub-sub swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
    // least efficient
    // POTENTIAL PROBLEM: OVERFLOW
    a = a * b;
    b = a / b;
    a = a / b;

    printf("after mul-div-div swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works ONLY with integers and chars
    // POTENTIAL PROBLEM: OVERFLOW
    a = a - b;
    b = a + b;
    a = -a + b;

    printf("after sub-add-add swap\n");
    printf("a = %d, b = %d\n", a, b);

    // works with ANY data types
    // most efficient
    a = a ^ b;
    b = b ^ a;
    a = a ^ b;

    printf("after tripple xor swap\n");
    printf("a = %d, b = %d\n", a, b);

    return 0;
}
```
### Сумма двумерного массива


Общий алгоритм работы:
- выделяем место под хранение ответов - одномерные массивы размерами $n$ (для сумм строк) и $m$ (для сумм столбцов)
- организовываем проход по двумерному массиву, рассматривае элемент $a_{i,j}$
- каждый такой элемент участвует в сумме для $i$-й строки и $j$-го столбца
- увеличиваем накопленную сумму $i$-й строки на $a_{i,j}$ и накопленную сумму $j$-го столбца также на $a_{i,j}$

Далее LIVE CODING:
### Реализация 1 - тривиальная реализация
```c 
#include <stdio.h>
#include <stdint.h>

#define N_MAX 500
#define M_MAX 500

int main() 
{
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    // The most simple way is to allocate a big array, read all the number and then compute + print
    int64_t arr[N_MAX][M_MAX];

    // Two arrays to store our sums	
    int64_t sum_rows[N_MAX] = {0};
    int64_t sum_cols[M_MAX] = {0};		

    // Read the input array
    for(int i = 0; i < n; i++)	
    {
        for(int j = 0; j < m; j++)				
	{
            // lld - long long decimal IS IMPORTANT
	    scanf("%lld", &arr[i][j]);	
	}
    }

    // Now traverse the array and compute all the sums
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {	            
                sum_rows[i] += arr[i][j];
                sum_cols[j] += arr[i][j];            
        }
    }
	
    // Then just print the results

    printf("\n");
	
    for(int i = 0; i < n; i++)
    {
        // lld - long long decimal IS IMPORTANT	
        printf("%lld ", sum_rows[i]);
    }
    printf("\n");
    
    for(int i = 0; i < m; i++)
    {
        // lld - long long decimal IS IMPORTANT
        printf("%lld ", sum_cols[i]);
    }
    printf("\n");

    return 0;
}
```

### Реализация 2 - уменьшенное использование памяти
Изменения:
- основной алгоритм остается прежним
- убираем считывание исходных данных и хранение их в двумерном массиве
- сразу используем считываемый элемент для формирования сумм

Такой подход позволяет уменьшить затраты  времени и памяти программы.

```c 
#include <stdio.h>
#include <stdint.h>

#define N_MAX 500
#define M_MAX 500

int main() 
{
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);

    // Two arrays to store our sums
	
    int64_t sum_rows[N_MAX] = {0};
    int64_t sum_cols[M_MAX] = {0};

    // This algorithm does one single pass over all elements
    int64_t temp;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {		
            // Scanf current number and store it in int64_t variable. lld - long long decimal IS IMPORTANT	
            scanf("%lld", &temp);
            sum_rows[i] += temp;
            sum_cols[j] += temp;
        }
    }
	
    // Now just print all the sums computed

    printf("\n");
	
    for(int i = 0; i < n; i++)
    {
        // lld - long long decimal IS IMPORTANT	
        printf("%lld ", sum_rows[i]);
    }
    printf("\n");
    
    for(int i = 0; i < m; i++)
    {
        // lld - long long decimal IS IMPORTANT	
        printf("%lld ", sum_cols[i]);
    }
    printf("\n");

    return 0;
}
```

Пример сравнения работы двух реализаций

![image](https://github.com/il-bychkov/algorithms/assets/2277222/9c5f1bb3-7a08-481b-9ae7-ef0fcd594be5)

