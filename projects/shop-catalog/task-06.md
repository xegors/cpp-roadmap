# Задача 06 — финал: dangling + const-аudit + CLI-цикл

Файл решения: `shop.cpp` (собственна collective best pieces from tasks 01–05).
Темы: параграф 2.7 — висячие ссылки/указатели, const-аудит, CLI-цикл.

## Что сделать

1. В один файл `shop.cpp` включи всё, что было написано в задачах 01–05:
   - `enum class Category` и `struct Product` (задача 01);
   - `vector<Product>`, печать через `const auto&` (задача 02);
   - Функции `findByName`, `findByNameConst` (задача 03);
   - Функции `buy`, `discount`, `removeByName` (задача 04);
   - Функция `stats` (задача 05).
2. Напиши `int main()` с `while`-циклом, который читает команду из `std::cin` и вызывает соответствующую функцию.
   Команды (все lowercase, без параметров — флаги добавь потом):
   - `add <название> <цена> <шт> <категория>` — добавить товар (используй designated init);
   - `list` — вывести весь каталог через `for (const auto& p : catalog)`;
   - `find <название>` — найти товар через `findByName`, показать `p->name` или `not found`;
   - `buy <название> <шт>` — купить через `buy(catalog, name, n)`;
   - `discount <процент>` — скидка через `discount(catalog, pct)`;
   - `stats` — статистика через `stats(catalog)` и вывод `auto [total, qty] = ...`;
   - `remove <название>` — удалить через `removeByName`;
   - `exit` — выйти из цикла.
3. Обязательно продемонстрируй **одно место с висячей ссылкой/указателем** и комментируй, как оно избегается (principle from tasks 04-05: после `erase`/`push_back` pointer могут инвалидироваться, их нужно брать заново через `findByName`).
4. Программа без внешних зависимостей: всё в одном `main()`, `#include <iostream>`, `<string>`, `<vector>`, `<utility>`.

## Требования

- Один файл `shop.cpp` со всем кодом из задач 01–05.
- `while (std::cin >> cmd)` — цикл команд.
- Все 7 команд реализованы минимально.
- Есть комментарий одной строкой про инвалидацию указателя/ссылки после контейнереопераций.
- `#include <iostream>`, `<string>`, `<vector>`, `<utility>`. Больше ничего.

## Проверка

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/shop projects/shop-catalog/shop.cpp && /tmp/shop
```

Приёмка:
- [ ] компилируется без варнингов;
- [ ] все команды работают (добавить 1 товар, list, find/buy/discount/stats/remove, exit);
- [ ] вывод видно и понятный;
- [ ] есть комментарий про dangling pointer/reference.

## Подсказки (не решение)

- `std::cin >> cmd` читает слово, остальное можно читать `std::getline` после `cin.ignore()`.
- Команды можно свитчить через `if/else if` или `switch` (для switch нужно приводить к `int` или использовать `enum`).
- После `removeByName` или `push_back` лучше вызывать `findByName`, чем хранить `Product*` себе.
- Для `stats` уже есть функция из задачи 05 — не нужно её повторять, можно juste call.

Когда будет готово — кидай файл, разберём и скажу, что дальше (если есть задача 07 или релиз).