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

Все постановки задач проекта консолидированы в
`projects/shop-catalog/TASKS.md`.

## Как компилировать и запускать

Нужен `clang++` с поддержкой `C++20`. Каждый файл собирается отдельно:

```
clang++ -O2 -std=c++20 -Wall -Wextra task.cpp -o task && ./task
```

Пример:

```
clang++ -O2 -std=c++20 -Wall -Wextra tasks/yandex-handbook/first-steps/two-sum.cpp -o two-sum && ./two-sum
```

## Окружение

Для сборки нужен `clang++`, для чекера стиля — `clang-format` (обычно идут
в пакете `clang`). Опционально `clangd` для автодополнения и format-on-save
в редакторах.

Настройки уже в репозитории:

- `.vscode/` — VS Code: format-on-save через clangd (расширение
  `llvm-vs-code-extensions.vscode-clangd`), 4 пробела, стрип трейлинг-пробелов;
- `.clangd` + `.editorconfig` — фоллбэк-флаги clangd (`-std=c++20`)
  и настройки отступов для любых редакторов.

## Стиль кода

Код пишется в **Yandex C++ Style**:

https://github.com/yandex/CMICOT/blob/master/CPP_STYLE_GUIDE.md

Главное: отступ 4 пробела без табов, скобки 1TBS, тела функций и операторов
всегда с новой строки, функции и поля типов с большой буквы, типы с префиксами
`T`/`E` (`TProduct`, `ECategory`), локальные переменные — строчные, `nullptr`
вместо `NULL`/`0`. Форматирование — через `.clang-format` (лимит строки 100
колонок); полная шпаргалка и правила именования — в `AGENTS.md`.

Вместо внутреннего инструмента Яндекса `ya style` используется локальный
чекер (та же идея: clang-format + проверка именования):

```
tools/style-check.py              # проверка всего репозитория
tools/style-check.py <файл.cpp...>  # точечная проверка
tools/style-check.py --fix        # автоформатирование (clang-format -i)
```

Чекер проверяет соответствие `.clang-format`, табы и концевые пробелы,
префиксы `T`/`E` у типов и регистр функций/полей. Для nvim можно повесить
сохранение на `clang-format`: `autocmd BufWritePre *.cpp silent! exec '!clang-format -i %'`.

## Прогресс

Учебник (`tasks/yandex-handbook`): `first-steps` (2), `types` (2), `cond-and-loops` (7),
`vectors-and-strings` (6), `functions` (6).

Проект `shop-catalog`: все задачи 01–06 выполнены, файлы решений лежат
в репозитории (01–05 — отдельные `task-NN-*.cpp`, финальная сборка — `shop.cpp`;
постановки — в `TASKS.md`).

## Лицензия

MIT, см. файл [LICENSE](LICENSE).
