# yadro_cpp_intern_task

## Задачи
- [x] Определить интерфейс для работы с устройством типа лента

- [ ] Внешний конфигурационный файл

- [ ] Класс, который реализует интерфейс ленты, посредством файла
- [x] Алгоритм сортировки данных с входной ленты на выходную
- [ ] Консольное приложение должно принимать на вход имя входного и выходного файлов, производить сортировку
- [ ] Юнит-тесты
- [ ] Фиксация, сколько времени было потрачено эмулирующий сортировки(информация о времени работы каждой операции передаётся через внешний конфиг)


## Первые идеи, которые приходят в голову:


- Сортировка слиянием

Необходимо будет две временные ленты. Мы будем читать K чисел с входной ленты, сортировать их в оперативной памяти
и записывать их на временные ленты по очереди. Т.е. Первые K отсортированных чисел мы запишем на первую ленту,
а вторые K отсортированных чисел мы запшием на вторую ленту. Потом будем mergit их на выходной ленте.

Выходная лента будет состоять из отсортированных подмассивов длинны 2k. Мы будем читать по 2k чисел, записывать их
по очередно на первую и вторую временные ленты. Снова будем мерджить их на выходной ленте. Тогда выходная лента будет
состоять из отсортированных подмассивов длинны 4k. И так будем повторять до тех пор, пока не отсортируем всю ленту.

На входной ленте у нас будет 1 проход.

На временных лентах будет logN проходов.

На выходной ленте будет logN проходов.

- Сортировка подсчётом

Подсчитаем количество сколько раз встречается каждое число и восстанановим отсортированный массив. Чисел у нас 2 ^ 32,
т.е.4 байта каждое, всего таких может встретиться N/4, если N у нас 16 ТБ = 2 ^ 44 байт, то нам нужно уметь хранить 2 ^ 32 чисел
размерностью 2^42. Получается очень грустно.
Update: возможно я ошибаюсь в подсчётах, но если это не так, сообщите мне пожалуйста об этом.

- Сортировка выбором

Выбирать с ленты K самых больших чисел за проход по ленте и записать их на выходную ленту. Потом выбрать K самых больших чисел, 
меньших чем самое маленькое в прошлой выборке. Всего проходов по ленте будет: N/K. Проблемы ещё будут, если в ленте есть число,
которое встречается больше чем K раз.

## Сборка

``` bash
mkdir build
cd build
cmake ../src
make
```

## Запуск

``` bash
./yadro_task
```

## Конфигурация

Из настройки пока доступно только указание число элементов во входной ленте и число элементов, которые помещаются в оперативную память. Указываются они в main.cpp.



