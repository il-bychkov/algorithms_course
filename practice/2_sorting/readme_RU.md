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








