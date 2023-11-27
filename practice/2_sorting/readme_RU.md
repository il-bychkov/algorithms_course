# Практическое занятие 2

## Сортировки

Примеры простых сортировок:
- Сортировка выбором (Selection Sort)
- Сортировка вставками (Insertion Sort)
- Сортировка пузырьком (Bubble Sort)

Общие черты описанных сортировок:
- в качестве входных данных принимается коллекция элементов и критерий сортировки
- основная идея - последовательное формирование и увеличение отсортированной части внутри исходной коллекции
- основными применяемыми операциями являются сравнения и перемещение элементов
- не требуют использования дополнительной информацию (например, о значениях элементов массивов)
- в худшем случае производительность деградирует до квадратичной сложности $O(n^2)$
- имеют констатнтую сложность по памяти $O(1)$

Из вышеперечисленных будут разобраны две сортировки - сортировка выбором (selection sort) и сортировка вставками (insertion sort).

### Сортировка выбором (selection sort)

Особенности алгоритма:
- в самом начале отсортированная часть содержит 0 элементов
- на каждом шаге находим минимальный/максимальный элемент из неотсортированной части коллекции
- меняем найденный минимальный/максимальный элемент с i-м элементом (где элементы в интервале $[0, i-1]$ - это отсортированная часть)
- алгоритм продолжает работу пока размер отсортированной части не станет равным размеру всего массива

Сложность по времени:
- Лучший случай: $O(n^2)$
- Хучший случай: $O(n^2)$
- Общая оценка : $\theta(n^2)$ - (растёт как $n^2$, так как во всех случаях мы делаем порядка $n^2$ операций)

Сложность по памяти:
- Лучший случай: $O(1)$
- Хучший случай: $O(1)$
- Общая оценка : $O(1)$ - используемый объем дополнительной памяти не зависит от входных данных



Реализация на C:

Источник - https://en.wikipedia.org/wiki/Selection_sort

```c 
int i,j;
int aLength; // initialise to a's length

for (i = 0; i < aLength-1; i++)
{
    int jMin = i;
    for (j = i+1; j < aLength; j++)
    {
        if (a[j] < a[jMin])
        {
            // Save index of the minimum element for the swap
            jMin = j;
        }
    }
    // If min element is not next to sorted part - we need to place it there, otherwise can do nothing
    if (jMin != i) 
    {
        // Inside function swap we swap values of i-th and jMin-th elements
        swap(a[i], a[jMin]);
    }
}
```
### Сортировка вставками

Особенности алгоритма:
- в самом начале отсортированная часть содержит 1 элемент (в отличие от сортировки выбором)
- на каждом шаге пытаемся расширить отсортированную часть за счёт следующего за ней элемента, для этого нужно найти его корректную позицию
- последовательно сравниваем новый элемент с предыдущим и меняем их местами если порядок в паре не соответствуют заданному критерию сортировки
- второй способ: просто сдвигаем вправо предыдущий элемент пока не найдем место для  нового, после делаем вставку нового
- алгоритм продолжает работу пока размер отсортированной части не станет равным размеру всего массива

До расширения отсортированной части:

![image](https://github.com/il-bychkov/algorithms/assets/2277222/a518dc3b-accf-4d06-9c88-689af88a3b7c)

После расширения отсортированной части:

![image](https://github.com/il-bychkov/algorithms/assets/2277222/32cea938-8013-450f-ade8-d3cd4846157a)

Источник: https://en.wikipedia.org/wiki/Insertion_sort


Сложность по времени:
- Лучший случай: $O(n)$ - если массив уже отсортирован алгоритм не сделает ни одного обмена, только $n$ сравнений
- Хучший случай: $O(n^2)$
  
Сложность по памяти:
- Лучший случай: $O(1)$
- Хучший случай: $O(1)$
- Общая оценка : $O(1)$ - используемый объем дополнительной памяти не зависит от входных данных



Пример реализации на C:

Источник: https://www.geeksforgeeks.org/c-program-for-insertion-sort/

**Заметка:**

Обратите внимание, в приведенной ниже реализации происходит только один обмен, когда мы нашли нужную позицию.
В остальных случаях предыдущий элемент просто копируется вправо (как в алгоритме вставки в массив).
Эта стратегия соответствует второму способу в описании алгоритма.

```c 
// C program for insertion sort
#include <math.h>
#include <stdio.h>
 
/* Function to sort an array 
   using insertion sort*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) 
    {
        key = arr[i];
        j = i - 1;
 
        /* Move elements of arr[0..i-1], 
           that are greater than key, 
           to one position ahead of 
           their current position */
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
 
// A utility function to print 
// an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
int main()
{
    int arr[] = {12, 11, 13, 5, 6};
    // Some trick to make "hardcoding" of the whole array more easy - no need to store size, we can compute it
    int n = sizeof(arr) / sizeof(arr[0]);
 
    insertionSort(arr, n);
    printArray(arr, n);
 
    return 0;
}
```

## Специальные сортировки

### Коротко о Make
Для реализации специальных мы поместим общий код в отдельные файлы.

В настоящих проектах на компилируемых языках как правило используются автоматизированные системы, которые можно настраивать для сборки проекта.

Одной из таких утилит является Make.
В случае с C++ Make помогает упростить управление процессами компиляции и линковки.

Адрес утилиты:
https://www.gnu.org/software/make/

Скачать можно тут:
https://gnuwin32.sourceforge.net/packages/make.htm

Простая статья на Хабре (была использована для описания ниже):
https://habr.com/ru/articles/211751/

Конфигурировать процесс сборки выполняемых файлов можно с помощью файлов специального формата, которые называются Makefile.

```
# Индентация осуществляется исключительно при помощи символов табуляции,
# каждой команде должен предшествовать отступ
<цели>: <реквизиты>
	<команда #1>
	...
	<команда #n>
```
**Цели** - что делаем (объектные файлы, исполняемые файлы)

**Реквизиты** - параметры для компиляторов/линковщиков

**Команды** - конкретные команды для создания файлов (например, вызов компилятора gcc)

**!!WARNING!!** - сделать тестовый запуск с двумя hello world файлами чтобы продемонстрировать простой Makefile ниже

Пример простого Makefile:
```make
main.o: main.c
        gcc -c -o main.o main.c
hello.o: hello.c
        gcc -c -o hello.o hello.c
hello: main.o hello.o
        gcc -o hello main.o hello.o
```
В данном случае у нас есть 2 файла - файл с функцией main и файл со вспомогательным кодом, использующимся внутри main.c.
Создаем три цели:

    - объектный файл main.o - скомпилированный машинный код, сделанный из main.c
    
    - объектный файл hello.o - скомпилированный машинный код, сделанный из hello.c
    
    - итоговый исполняемый файл hello - исполняемый файл, который можно запускать. Он образовался после компоновки (линковки) файлов main.o и hello.o.

Чтобы запустить сборку необходимо указать утилиту make и цель которую мы хотим собрать:
```bash
make hello
```
    

Пример Makefile из нашей секции со специальными сортировками:

**!!WARNING!!** - пройтись по Makefile, объяснить все

```make
.PHONY: help

all: utility_demo counting_sort bucket_sort qsort  # Build all targets

help: # Show help for each of the Makefile recipes.
	@printf "\n"
	@grep -E '^[a-z].*:.*'  Makefile | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done
	@printf "\n"

utility_demo: sorting.c utility_demo.c # Build avaliable utilities demo
	gcc sorting.c utility_demo.c -o utility_demo

counting_sort: sorting.c counting_sort.c # Build counting sort implementation
	gcc sorting.c counting_sort.c -o counting_sort

bucket_sort: sorting.c bucket_sort.c # Build bucket sort implementation
	gcc sorting.c bucket_sort.c -o bucket_sort

qsort:
	gcc qsort_hoar.c -o qsort_hoar
	gcc qsort_lomuto.c -o qsort_lomuto

clean: # Delete all builded files
	rm -f utility_demo counting_sort bucket_sort
```


### Сортировка подсчётом (counting sort)

Особенности алгоритма:
- использует дополнительные данные и ограничения - интервал значений (хотя за линейное время можно найти min, max) и требование на целочисленность элементов (на самом деле важно что их конечное количество)
- основная идея: подсчет количества вхождений каждого элемента коллекции, затем обход всех возможных значений и вывод тех, для которых их подсчитанное количество в исходной коллекции больше 0
- при оценке сложности добавляется параметр k - количество возможных уникальных значений элементов коллекции
- сортировка может существенно деградировать если значение k велико по сравнению с n

Сложность по времени:
- Лучший случай: $O(n)$ - множество допустимых значений элементов (его мощность = k) коллекции фиксировано и не зависит от n
- Общий случай: $O(n + k)$
  
Сложность по памяти:
- Общий случай: $\theta(n + k)$

**Пример реализации на C:**

Источник: counting_sort.c

Заметки:
- Объяснить что uint32_t - целочисленный тип из библиотеки. Для него всегда известен размер - 4 байта. 
Такое используется когда мы должны быть уверены в размере - например, иногда когда работаем с адресной арифметикой.
В int размер может быть разным в зависимости от компилятора и системы.
- показать код, показать функции из утилит, которые вызываются
- запустить весь код - показать замеры

```c
#include "sorting.h"

#define ARR_SIZE 10
#define LARGE_ARR_SIZE 100000
#define N_ITERATIONS   1000

// variant with prefix sum
// alg is stable, but slower than direct sorted array fill
void counting_sort_inc(uint32_t* array, size_t size) {
    uint32_t max_value = array[0];

    // search by largest element
    for (size_t i = 1; i < size; i++)
    {
        if(array[i] > max_value) {
            max_value = array[i];
        }
    }
    uint32_t count_array_size = max_value + 1;
    // allocate tmp arrays
    uint32_t* count_array = malloc(count_array_size * sizeof(uint32_t));
    uint32_t* sorted_array = malloc((size + 1) * sizeof(uint32_t));
    // clear count array
    for (size_t i = 0; i < count_array_size; i++)
    {
        count_array[i] = 0;
    }
    // count elements in unsorted array
    for (size_t i = 0; i < size; i++)
    {
        count_array[array[i]]++;
    }
    // calculate prefix sum
    for (size_t i = 1; i <= count_array_size - 1; i++) {
        count_array[i] += count_array[i - 1];
    }
    // fill sorted array
    // DO NOT USE size_t IN THIS CYCLE
    // or use with condition i != -1
    // i >= 0 works only with signed counter
    for (int i = size - 1; i >= 0; i--)
    {
        sorted_array[count_array[array[i]] - 1] = array[i];
        count_array[array[i]]--;
    }
    // copy sorted array
    for (size_t i = 0; i < size; i++)
    {
        array[i] = sorted_array[i];
    }

    free(count_array);
    free(sorted_array);
}

// variant vithout prefix sum
// bit faster, but not stable
void counting_sort_dec(uint32_t* array, size_t size) {
    uint32_t max_value = array[0];

    // search by largest element
    for (size_t i = 1; i < size; i++)
    {
        if(array[i] > max_value) {
            max_value = array[i];
        }
    }
    uint32_t count_array_size = max_value + 1;
    // allocate tmp arrays
    uint32_t* count_array = malloc(count_array_size * sizeof(uint32_t));
    // clear count array
    for (size_t i = 0; i < count_array_size; i++)
    {
        count_array[i] = 0;
    }
    // count elements in unsorted array
    for (size_t i = 0; i < size; i++)
    {
        count_array[array[i]]++;
    }
    // fill sorted array
    size_t result_array_index = size - 1;
    for (size_t i = 0; i < count_array_size; i++)
    {
        for (size_t j = count_array[i]; j > 0; j--)
        {
            array[result_array_index] = i;
            result_array_index--;
        }

    }

    free(count_array);
}

int main() {

    uint32_t array[ARR_SIZE];
    uint32_t array_sorted_ref[ARR_SIZE];

    // test sort smallest to largest
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    counting_sort_inc(array, ARR_SIZE);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    // test sort largest to smallest
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_dec(array_sorted_ref, ARR_SIZE);

    counting_sort_dec(array, ARR_SIZE);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    uint32_t large_array[LARGE_ARR_SIZE];


    clock_t t;
    double owerall_time_taken;

    printf("\ntest time smallest to largest\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 10);
        t = clock(); // hi-res clock counter
        counting_sort_inc(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-10, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        counting_sort_inc(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time largest to smallest\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 10);
        t = clock(); // hi-res clock counter
        counting_sort_dec(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-10, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        counting_sort_dec(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    return 0;
}

```

### Блочная сортировка (bucket sort)

Особенности алгоритма:
- основная идея: разбиваем числовой отрезок (между min-max, которые можно найти одним проходом) на равные подотрезки (корзины).
Считаем сколько чисел уместилось в каждую корзину и сортируем их простой сортировкой (вставки) или рекурсивно.

- не страдает необходимостью иметь конечный набор потенциальных значений в коллекции
- хорошо работает при равномерно распределенных входных значениях элементов
- как правило количество корзин выбирают линейно зависящим от n

  ![image](https://github.com/il-bychkov/algorithms/assets/2277222/626c464d-4d4d-490c-b801-0a735f00afb2)

  Источник: https://en.wikipedia.org/wiki/Bucket_sort


Сложность по времени:
- Лучший случай: $O(n)$ - хорошо распределенные данные, очень мало элементов в корзинах, $k~n, 2n, 3n$
- Худший случай: $O(n^2)$
  
Сложность по памяти:
- Общий случай: $\theta(n + k)$
- Худший случай: хранить в массивах $\theta(nk)$

**Пример реализации на C:**

Источник: bucket_sort.c

Заметки:
- показать код, показать функции из утилит, которые вызываются
- запустить весь код - показать замеры

```c
#include "sorting.h"

#define ARR_SIZE 10
#define LARGE_ARR_SIZE 10000
#define N_ITERATIONS   10

void insertion_sort(uint32_t* array, size_t size)
{
    size_t j;
    for (size_t i = 1; i < size; i++) {
        uint32_t key = array[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void bucket_sort(uint32_t* array, size_t size, uint32_t range_start, uint32_t range_end, size_t n_buckets) {
    uint32_t** buckets = malloc(n_buckets * sizeof(uint32_t*));
    size_t* buckets_size = malloc(n_buckets * sizeof(size_t));
    uint32_t* bucket_borders = malloc(n_buckets * sizeof(uint32_t));

    uint32_t bucket_range_step = (range_end - range_start) / n_buckets + 1;

    for (size_t i = 0; i < n_buckets; i++)
    {
        buckets[i] = malloc(size * sizeof(uint32_t));
        buckets_size[i] = 0;
        bucket_borders[i] = range_start + bucket_range_step * i;
    }

    for (size_t i = 0; i < size; i++)
    {
        size_t bucket_index = array[i] / bucket_range_step;
        buckets[bucket_index][buckets_size[bucket_index]] = array[i];
        buckets_size[bucket_index] += 1;
    }

    size_t output_array_offset = 0;

    for (size_t i = 0; i < n_buckets; i++)
    {
        insertion_sort(buckets[i], buckets_size[i]);

        for (size_t j = 0; j < buckets_size[i]; j++)
        {
            array[output_array_offset + j] = buckets[i][j];
        }

        output_array_offset += buckets_size[i];
    }
}

int main() {

    uint32_t array[ARR_SIZE];
    uint32_t array_sorted_ref[ARR_SIZE];

    // test sort smallest to largest 1 bucket
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 1);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);

    // test sort smallest to largest 2 buckets
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 2);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);

    // test sort smallest to largest 4 buckets
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 4);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    uint32_t large_array[LARGE_ARR_SIZE];


    clock_t t;
    double owerall_time_taken;

    printf("\ntest time 1 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 1);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time 2 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 2);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time 4 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 4);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    return 0;
}
```

### Поразрядная сортировка (radix sort)
### Сортировка слиянием (merge sort)
### Быстрая сортировка (quick sort)
