# Практическое занятие 0
## Адреса, переменные, массивы и алгоритмы на массивах

### Часть 0: Введение в трансляцию и компиляцию на языке C
  
**Транслятор** – программа, обеспечивающая перевод написанного нами исходного кода на внутренний язык компьютера.
Компьютор воспринимает лишь программы , написанные на машинном языке. 

Обычно выделяют трансляторы двух типов:

**Интерпретатор** -  обеспечивает поочередный перевод каждого оператора исходной программы на машинный языки и 
немедленное выполнение его с одновременной проверкой правильности.
Известные интерпретируемые языки программирования - Python, Java.

Второй вид транслятора – **компилятор**.
В отличии от интерпретатора он осуществляет сначала перевод всей исходной программы на машинный язык,
одновременно проверяя ее правильность.
Также в полученную программу компилятор включает подпрограммы и функции, которые связываются со всей программой.
Этот этап называется **компановкой(линковкой)** и обеспечивается еще одной специальной программой - **компановщиком (linker)**.
Результатом работы компилятора является исполняемый файл.

### Часть 1: Что происходит внутри IDE: как код на языке программирования трансформируется в машинный код

Как происходит процесс создания исполняемого файла:

1. Компилятор отдельно переводит в машинный код каждый файл с исходным кодом (.c)
2. В результате появляются так называемые объектные файлы (.o, для каждого файла .c)
3. Далее все объектные файлы машинного кода + внешние библиотеки соединяются в один исполняемый файл с помощью компановщика (linker).
   
![image](https://github.com/il-bychkov/algorithms/assets/2277222/cf037240-1e2d-46d1-bbf2-98804e802462)

### Часть 2: Адреса и переменные

### **FULL LIVE CODING**

**Исходный код:** addresses.с

**Заметка:** В данном примере необходимо:
- напомнить, что страшные hex адреса это просто номера байт (возможно перевести один в десятичную систему и сказать - вот, это 9999999й байт)
- создать несколько переменных разных типов и показать как для них выделилась память
- показать размеры различных типов данных (в качестве примеров)
- показать адресную арифметику - добавление 1 к разным типам данных


**!!!ВАЖНО!!!:**
- в выводе посчитать и показать, что действительно адрес + 1 получается новый адрес
(адрес потенциального начала следующей переменной такого же типа)

```c 
#include <stdio.h>
int main()
{
    // Create 4 variables of different types
    int intVariable = 30;
    float floatVariable = 1.1;
    double doubleVariable = 1.1;
    char charVariable = 'c';
    
    printf("int start address = %p\n",&intVariable);
    printf("int size          = %lu\n",sizeof(int));
    // Int variable - address + 1 = address + one int
    printf("int end address   = %p\n\n",&intVariable + 1);

    printf("float start address = %p\n",&floatVariable);
    printf("float size          = %lu\n",sizeof(floatVariable));
    // Float variable - address + 1 = address + one float
    printf("float end   address = %p\n\n",&floatVariable + 1);

    printf("double start address = %p\n",&doubleVariable);
    printf("double size          = %lu\n",sizeof(doubleVariable));
    // Double variable - address + 1 = address + one double
    printf("double end address   = %p\n\n",&doubleVariable + 1);

    printf("char start address = %p\n",&charVariable);
    printf("char size          = %lu\n",sizeof(charVariable));
    // Char variable - address + 1 = address + one char
    printf("char end   address = %p\n\n",&charVariable + 1);
}
```

**Пример вывода:** addresses.c
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

### Часть 3: Адреса и массивы

### **FULL LIVE CODING**

**Исходный код:** addresses_arrays.c

**Заметка:** В данном примере необходимо:
- напомнить, что данные в массиве однотипны и располагаются в памяти последовательно
- создать массив переменных int
- с помощью цикла вывести информацию по всем элементам - смещение, значение, адрес
- пройтись по нескольким элементам вручную и показать что между ними правильное число байт (посмотреть разницу между адресами)


```c 
#include <stdio.h>

#define ARR_SIZE 10

int main()
{
    // Initialize an array
    int intArray[ARR_SIZE] = {10, 11, 12, 13 ,14 ,15 ,16 ,17, 18, 19};

    // Print an address of every array element
    for (int i = 0; i < ARR_SIZE; i++)
        printf("int array element shift = [%d] -  value stored = %d  - address = %p\n",i, intArray[i], &intArray[i]);
    return 0;
}
```

**Пример вывода:** addresses.c
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

### Часть 4: Массивы - вставка элемента + измерение производительности вставок - 

### **FULL LIVE CODING**

**Исходный код:** insert_element_alg.c

**Заметка:** В данном примере необходимо:
- напомнить: сложность операции вставки - в лучшем случае O(1), в худшем O(n), вставка возможна только если объем реально имеющихся данных в массиве меньше чем объем выделенной памяти
- напомнить: алгоритм вставки - начинаем с последнего элемента и копируем его вправо, далее смещаемся назад пока не дойдем до позиции вставки 
- набрать пример кода ниже
- показать функцию вывода массива и объяснить ее предназначение и устройство - избежать дублирования кода, несколько раз использовать одну и ту же функционльность

**!!!ВАЖНО!!!:**
- после первого запуска поменять несколько раз константы - позицию вставки и значение, перекомпилировать, запустить и показать разные варианты вставки


```c
#include <stdio.h>

#define ARR_SIZE 11


// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int main() 
{    
    // Initialize an array and variables - we assume the array has 1 free position at the end
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};    
    int insertIndex = 4;
    int insertValue = 42;
    
    // Print the initial array 
    printf("Initial array:\n");    
    printArray(array, ARR_SIZE);
  
    // Insert element - move affected elements one position right
    for(int i = ARR_SIZE - 1; i > insertIndex; i--) {
        array[i] = array[i - 1];
    }
    // Insert a new value
    array[insertIndex] = insertValue;
    
    // Print the resulting array
    printf("Array after inserting value %d at index %d \n", insertValue, insertIndex);
    printArray(array, ARR_SIZE);
   
    return 0;
}

```

**Пример вывода:** insert_element_alg.c
```bash
Initial array:
0 1 2 3 4 5 6 7 8 9 -1
Array after inserting value 42 at index 4
0 1 2 3 42 4 5 6 7 8 9
```

**Сценарий измерения производительности:**
- написан специальный код для экспериментов
- операция вставки будет рассмотрена для следующих позиций: начало массива, середина, конец
- для каждой позиции на одних и тех же данных будет произведено последовательно по несколько вставок (100 в параметрах), затем время суммируется
Это нужно для того чтобы нивелировать возможный задержки со стороны операционной системы - для 100 экспериментов средний результат (как и сумма) должны быть более устойчивы к случайным зависаниям по вине ОС

**!!!ВАЖНО!!!:**
- результаты работы кода должны быть такими: вставка в начало пропорциональна количеству элементов ~ O(n), в середину ~ n/2, в конец ~ O(1).
Запустить несколько раз подряд и показать разные замеры. Во всех должна соблюдаться иерархия выше, но не всегда результаты будут идеально в пропорции выше.
  
**Исходный код:** insert_element_perf.c
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void arrayInsert(int* array, int value, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Insert element - move affected elements one position right
        for(int j = ARR_SIZE - 1; j > position; j--) 
        {
            array[j] = array[j - 1];
        }
        // Insert a new value
        array[position] = value;
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: %d is inserted to index %d. Time of %d runs = %f seconds \n", value, position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main()
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++)
    {
        array[i] = rand();
    }    
    
    // Make 3 insertions - 0, middle and last positions
    int insertNumber = 42;    
    arrayInsert(array, insertNumber, 0);
    arrayInsert(array, insertNumber, ARR_SIZE / 2);
    arrayInsert(array, insertNumber, ARR_SIZE - 1);
    
}
```

**Пример вывода:** insert_element_perf.c
```bash
Experiment: 42 is inserted to index 0. Time of 100 runs = 0.078000 seconds
Experiment: 42 is inserted to index 250000. Time of 100 runs = 0.032000 seconds
Experiment: 42 is inserted to index 499999. Time of 100 runs = 0.000000 seconds
```

### Часть 5: Массивы - удаление элемента + измерение производительности удалений
**Исходный код:** delete_element_alg.c

**Заметка:** В данном примере необходимо:
- напомнить: сложность операции удаления в лучшем случае - в конце массива O(1), в худшем - в конце массива O(n)
- напомнить: алгоритм удаления - начинаем с элемента после удаляемого и последовательно копируем значения в предыдущую ячейку до конца массива
- напомнить: можно хранить длину актуального массива в переменной и использовать ее, тогда можно не трогать "удаленные ячейки"
- набрать пример кода ниже
- функцию вывода массива можно оставить из прошлого кода и не набирать заново

**!!!ВАЖНО!!!:**
- после первого запуска поменять несколько раз константы (позиция удаления), перекомпилировать, запустить и показать разные варианты удаления
  

```c
#include <stdio.h>

#define ARR_SIZE 10


// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int main()
{
    // Initialize an array and variables
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};    
    int deleteIndex = 4;
    int arrayActualLen = ARR_SIZE;
    
    // Print the initial array 
    printf("Initial array:\n");    
    printArray(array, ARR_SIZE);    
    
    // Delete element - move affected elements one position left
    for(int i = deleteIndex + 1; i < ARR_SIZE; i++)
    {
        array[i - 1] = array[i];
    }
    
    // Change the array's actual length
    arrayActualLen--;  
    
    // Print the resulting array
    printf("New array size = %d \n", arrayActualLen);
    printf("Array after deleting value at index %d \n", deleteIndex);
    printArray(array, arrayActualLen);

    return 0;
}
```

**Пример вывода:** delete_element_alg.c
```bash
Initial array:
0 1 2 3 4 5 6 7 8 9
New array size = 9
Array after deleting value at index 4
0 1 2 3 5 6 7 8 9
```

**Сценарий измерения производительности:**
- операция удаления будет рассмотрена для следующих позиций: начало массива, середина, конец
- для каждой позиции на одних и тех же данных будет произведено последовательно по несколько удалений (100 в параметрах), затем время суммируется
Это нужно для того чтобы нивелировать возможный задержки со стороны операционной системы - для 100 экспериментов средний результат (как и сумма) должны быть более устойчивы к случайным зависаниям по вине ОС

**!!!ВАЖНО!!!:**
- результаты работы кода должны быть такими: удаление из начала пропорционально количеству элементов ~ O(n), из середины середины ~ n/2, из конца ~ O(1).
Запустить несколько раз подряд и показать разные замеры. Во всех должна соблюдаться иерархия выше, но не всегда результаты будут идеально в пропорции выше.
  
**Исходный код:** delete_element_perf.c
  
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void arrayDelete(int* array, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Delete element - move affected elements one position left
        for(int i = position + 1; i < ARR_SIZE; i++)
        {
            array[i - 1] = array[i];
        }       
        // Here we do not need to make a variable for actual lenghtChange
        // since it is not used here, we need only the time
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Value at index %d is deleted. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main()
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
            
    // Make 3 deletions - 0, middle and last positions    
    arrayDelete(array, 0);
    arrayDelete(array, ARR_SIZE / 2);
    arrayDelete(array, ARR_SIZE - 1);
    

    return 0;
}
```

Output: delete_element_perf.c
```bash
Experiment: Value at index 0 is deleted. Time of 100 runs = 0.109000 seconds
Experiment: Value at index 250000 is deleted. Time of 100 runs = 0.047000 seconds
Experiment: Value at index 499999 is deleted. Time of 100 runs = 0.000000 seconds
```
### Часть 6: Массивы - поиск элемента + измерение производительности поиска
**Исходный код:** find_element_index_alg.c

**Заметка:** В данном примере необходимо:
- напомнить: сложность операции поиска в случае если мы ничего не знаем о данных = O(n), в лучшем случае можно найти за O(1)
- напомнить: алгоритм поиска - линейный поиск/linear search или полный перебор/brute force. Последовательно сравниваем искомый элемент со всеми элементами массива, пока не найдем или пока не кончится массив.
- набрать пример кода ниже
- функцию вывода массива можно оставить из прошлого кода и не набирать заново

**!!!ВАЖНО!!!:**
- после первого запуска поменять несколько раз константы (значение элемента для поиска, ПОПРОБОВАТЬ ЭЛЕМЕНТ, КОТОРОГО НЕТ), перекомпилировать, запустить и показать разные варианты поиска


```c
#include <stdio.h>

#define ARR_SIZE 10

// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++)
	{
        printf("%d ", arr[i]);
    }
	printf("\n");	
}

int main() 
{
	
	// Initialize an array and variables
    int array[ARR_SIZE] = {0, 11, 2, 33, 24, 5, 16, 37, 85, 99};	   
	// Target to find
    char elementToFind = 16;
	// Variable for resulting index, initialize it to some bad value to check if it is changed finally
    int indexFound = -1;
		
	// Print the initial array 
	printf("Initial array:\n");	
	printArray(array, ARR_SIZE);    
    
    // For loop to find the target value
    for(int i = 0; i < ARR_SIZE; i++) 
	{
		// If target is found - save index and leave
        if(array[i] == elementToFind) 
		{
            indexFound = i;
			break;
        }
    }
	
	// If this variable is not changed - element is     
	if (indexFound != -1)
        printf("Element %d is found at index %d \n", elementToFind, indexFound);
	else
		printf("Element %d is not found\n", elementToFind, indexFound);

    return 0;
}
```

**Пример вывода:** find_element_index_alg.c
```bash
Initial array:
0 11 2 33 24 5 16 37 85 99
Element 16 is found at index 6
```
**Сценарий измерения производительности:**
- операция поиска будет рассмотрена для следующих значений элементов массива: первый элемент, элемент со средним индексом и последний элемент
- для каждой позиции на одних и тех же данных будет произведено последовательно по несколько удалений (100 в параметрах), затем время суммируется
Это нужно для того чтобы нивелировать возможный задержки со стороны операционной системы - для 100 экспериментов средний результат (как и сумма) должны быть более устойчивы к случайным зависаниям по вине ОС

**!!!ВАЖНО!!!:**
- результаты работы кода должны быть такими: поиск совпадения в конце или отсутствие элемента ~ O(n), совпадение в середине ~ n/2, совпадение в начале ~ O(1).
Запустить несколько раз подряд и показать разные замеры. Во всех должна соблюдаться иерархия выше, но не всегда результаты будут идеально в пропорции выше.
  
**Исходный код:** find_element_index_perf.c
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void findElement(int* array, int target)
{
    // Start clock
    clock_t t = clock();       
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Actually this variable is used only to "save" answer        
        int indexFound = -1; 
        // For loop to find the target value
        for(int i = 0; i < ARR_SIZE; i++) 
        {
             // If target is found - save index and leave
             if(array[i] == target) 
             {
                 indexFound = i;
                 break;
             }
        }
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Element %d search . Time of %d runs = %f seconds \n", target, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main() 
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
    
    // Make 3 search requsts - first element array[0], middle element and last element    
    findElement(array, array[0]);
    findElement(array, array[ARR_SIZE / 2]);
    findElement(array, array[ARR_SIZE - 1]);
        
    return 0;
}
```

**Пример вывода:** find_element_index_perf.c
```bash
Experiment: Element 667933893 search . Time of 100 runs = 0.000000 seconds
Experiment: Element 2039841857 search . Time of 100 runs = 0.046000 seconds
Experiment: Element 537035320 search . Time of 100 runs = 0.094000 seconds
```
### Часть 7: Массив - получение элемнта по смещению + измерение производительности операции взятия по смещению

**Исходный код:** get_element_by_index_perf.c

**Сценарий измерения производительности:**
- операция взятия по смещению будет рассмотрена для следующих значений смещений: 0, средний индекс, последний индекс
- для каждой позиции на одних и тех же данных будет произведено последовательно по несколько операций чтения по смещению (100 в параметрах), затем время суммируется
Это нужно для того чтобы нивелировать возможный задержки со стороны операционной системы - для 100 экспериментов средний результат (как и сумма) должны быть более устойчивы к случайным зависаниям по вине ОС

**!!!ВАЖНО!!!:**
- результаты работы кода должны быть такими: для всех смещений время чтения данных должно быть константным = O(1).
Запустить несколько раз подряд и показать разные замеры. Иногда в разных замерах результат какого-то смещения может выбиваться, это огрехи измерений и задержки ОС.
В нормальном режиме значения должны быть очень близки.

```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void getElement(int* array, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Variable where we read the data from the array        
        int elementValue = 0;
        // Read element at the position        
        // Actually this variable it is not used
        // we need it only to read the value and compute total time
        elementValue = array[position];              
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Read value at index %d. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main() 
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
    
    // Make 3 reads - 0, middle and last positions    
    getElement(array, 0);
    getElement(array, ARR_SIZE / 2);
    getElement(array, ARR_SIZE - 1);
        
    return 0;
}

```

**Пример вывода:** get_element_by_index_perf.c
```bash
Experiment: Read value at index 0. Time of 100 runs = 0.000000 seconds
Experiment: Read value at index 250000. Time of 100 runs = 0.000000 seconds
Experiment: Read value at index 499999. Time of 100 runs = 0.000000 seconds
```
