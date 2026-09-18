# cpp-roadmap

Личная практика C++: решения задач из Яндекс-учебника по C++ и небольшие учебные проекты.
Каждый `.cpp`-файл — отдельная самодостаточная программа со своим `main()`: без билд-системы,
общих заголовков и внешних зависимостей.

## Структура

```
tasks/
  yandex-handbook/
    first-steps/         # базовый ввод-вывод
    types/               # преобразования типов, арифметика
    cond-and-loops/      # ветвления, циклы
    vectors-and-strings/ # векторы и строки
    functions/           # функции
projects/
  shop-catalog/          # учебный проект: каталог товаров (struct, enum, ссылки, указатели)
```

Постановки задач проекта лежат рядом с кодом в `*.md`-файлах
(например, `projects/shop-catalog/TASKS.md`).

## Как компилировать и запускать

Нужен `clang++` с поддержкой `C++20`. Каждый файл собирается отдельно:

```
clang++ -O2 -std=c++20 -Wall -Wextra task.cpp -o task && ./task
```

Пример:

```
clang++ -O2 -std=c++20 -Wall -Wextra tasks/yandex-handbook/first-steps/two-sum.cpp -o two-sum && ./two-sum
```

## Прогресс

Учебник (`tasks/yandex-handbook`): `first-steps` (2), `types` (2), `cond-and-loops` (7),
`vectors-and-strings` (6), `functions` (2).

Проект `shop-catalog`: задачи 01–04 готовы, 05–06 — в планах (см. `TASKS.md`).

## Стиль кода

Единый минимум зафиксирован в `.clang-format` (отступ 4 пробела, лимит строки 100).
В остальном стиль может слегка различаться между файлами — при правках
подстраивайся под стиль конкретного файла.

## Лицензия

MIT, см. файл [LICENSE](LICENSE).
