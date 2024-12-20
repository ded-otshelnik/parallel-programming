# Задание 7. Продвинутое использование технологии MPI

## Задания

## Требования

+ Количество процессов должно устанавливаться через *sbatch*, программная установка количества не допускается (если иначе невозможно)
+ Время* выполнения последовательной и параллельной версий должно быть записано и выведено на stdout.
+ Для проверки корректности работы запустить программу на 2, 4, 8, 16 потоках, причем количество потоков не должно быть программно установлено.
+ Желательно разделение программы на несколько файлов .c и заголовочный файл .h.
+ Если задача позволяет, разрешается использовать OpenMP в связке с MPI, но, в первую очередь, должна использоваться технология MPI.

\* таймеры обычно ставят в ту часть кода, которая параллелится, инициализацию и прочие служебные конструкции не учитывают при измерении времени.

## Пояснение к запуску

Рекомендуется изучить [гайд по суперкомпьютеру](supercomputer-guide.md), поскольку запуск программ на MPI требует некоторой предварительной подготовки. При запуске программы обратите внимание на параметр ```--mem-per-cpu```, которая регулирует выделяемую память под каждый процесс.

## Варианты

1. Реализовать программу, которая решает судоку для сетки N x N (9x9 или 16x16).
2. Дан текстовый файл. Реализовать параллельную программу ```caesar```, которая шифрует текст и записывает его в новый файл по следующему правилу: каждая буква в тексте смещается циклически на *n* позиций в алфавите (если *n*=3, то 'a' -> 'd', 'b' -> 'e', и т.д.) с таким же регистром. Предусмотреть возможность дешифровки полученного текста.
3. Реализовать программу, которая при помощи метода Монте-Карло для оценки экстремумов некоторой функции двух переменных $f(x, y)$ на области $D = \{(x, y): x \in [x_0, x_1], y \in [y_0, y_1]\}$.
4. Пусть есть $N_{acc}$ банковских аккаунтов ($N_{proc} \leq N_{acc}$) вида:

   ```c
   struct bank_account{
        char* fullname;
        float balance;
   }
   ```

   В некоторый рандомный момент времени *$t_n$* поток берет и переводит какую-то сумму с банковского аккаунта на случайный другой. Реализовать программу, эмулирующую работу банка со следующими условиями:
   1. Программа не должна допускать взаимной блокировки процессов.
   2. Информация о переводах с одного аккаунта на другой должна быть выведены на stdout.
   3. Общая сумма денег на всех аккаунтах не должна изменяться со временем и должна выводится с некоторой регулярностью.
   4. Баланс на банковском аккаунте не должен быть отрицательным.
   5. Длительность перерыва между переводами сделать рандомным, но относительно небольшим.
   6. Время работы ограничить 1 минутой.
5. Реализовать **пайплайн** (поток обработки данных; пример пайплайна: 1-й процесс генерирует данные, 2-й обрабатывает данные, 3-й сохраняет результат) для параллельного возведения матрицы $A$ в степень $N$ (для простоты, $N \leq 10$), используя неблокирующий способ передачи сообщений.
6. Пусть есть структура данных ***двунаправленная очередь (deque)***, размер которой ограничен числом *N*. Реализовать параллельную двунаправленную очередь с соответствующими функциями (add / addLast, remove / removeFirst, peek / peekFirst, etc.) для работы процессов в парадигме  "master-worker".
7. Пусть есть структура данных ***очередь с приоритетами (priority_queue)*** такая, что элементы в ней упорядочены **натуральным образом** (по факту, задан некоторый способ упорядочения структуры данных). Реализовать параллельную очередь с приоритетами с cоответствующими функциями (add, remove, peek, etc.) для работы процессов в парадигме "master-worker".
