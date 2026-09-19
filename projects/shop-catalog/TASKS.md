# Shop Catalog — план и статус проекта

Учебный проект: каталог товаров. Каркас для параграфов 2.5 (составные типы)
+ 2.6 (ссылки, указатели, const) с небольшим забеганием в 2.7 (функции).

Правило: каждый `.cpp` — отдельная программа с `main()`, общего хедера нет —
типы (`ECategory`, `TProduct`) копируются из задачи в задачу. Проект растёт
по задачам: каждая задача — свой файл `task-NN-*.cpp`. Финальная сборка —
`shop.cpp` из лучших кусков.

Все шесть задач выполнены, файлы решений в репозитории: 01–05 — отдельные
файлы `task-NN-*.cpp`, финальная сборка — `shop.cpp`.

## Задача 01 — struct + enum ✅

Файл: `task-01-struct-enum.cpp`. Темы: 2.5 — `enum class`, `struct`,
designated initializers, `sizeof`/выравнивание.

- `enum class ECategory` (4 значения), `struct TProduct`
  (`Name`, `Price = 0.0`, `Qty = 0`, `Cat`).
- В `main()`: агрегатная и designated-инициализация, правка поля через точку,
  `static_cast` категории туда-обратно, `sizeof` полей и структуры
  с комментарием про выравнивание.
- Только `<iostream>`, `<string>`; весь код в `main()`.

Проверка:

```bash
clang++ -std=c++20 -O2 -o /tmp/task01 projects/shop-catalog/task-01-struct-enum.cpp && /tmp/task01
```

## Задача 02 — печать через const-ссылки ✅

Файл: `task-02-print-const-ref.cpp`. Темы: 2.6 — `vector`, range-for,
`const auto&`, копии vs ссылки.

- `vector<TProduct>` из 3–4 товаров, печать только через
  `for (const auto& p : catalog)` в виде `Name | Price | Qty | Cat-as-int`.
- Правка одного поля вне цикла печати + повторный вывод.
- Плюс `<vector>` к инклудам задачи 01; весь код в `main()`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task02 projects/shop-catalog/task-02-print-const-ref.cpp && /tmp/task02
```

## Задача 03 — поиск указателями ✅

Файл: `task-03-find-pointer.cpp`. Темы: 2.6 (упор) + первое забегание
в 2.7 — `TProduct*`, `const TProduct*`, `nullptr`, `->`, `*`.

- Функции (сигнатуры обязательны):
  ```cpp
  TProduct* FindByName(std::vector<TProduct>& catalog, const std::string& name);
  const TProduct* FindByNameConst(const std::vector<TProduct>& catalog, const std::string& name);
  ```
  Возврат `&catalog[i]` при совпадении, иначе `nullptr`.
- В `main()`: поиск существующего (доступ через `->`) и несуществующего
  (`not found`), вызов const-версии (доступ через `(*p).`),
  комментарий про `const TProduct*` vs `TProduct* const`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task03 projects/shop-catalog/task-03-find-pointer.cpp && /tmp/task03
```

## Задача 04 — изменение через ссылки/указатели ✅

Файл: `task-04-mutate-ref.cpp`. Темы: 2.6 — мутация через `TProduct*`
и `auto&`, `erase`, инвалидация указателей.

- Функции (сигнатуры обязательны):
  ```cpp
  bool Buy(std::vector<TProduct>& catalog, const std::string& name, int n);
  void Discount(std::vector<TProduct>& catalog, double pct);
  bool RemoveByName(std::vector<TProduct>& catalog, const std::string& name);
  ```
  `Buy` — через `FindByName` с проверками `nullptr` и `qty >= n`;
  `Discount` — `for (auto& p : catalog)`, `p.Price *= (1 - pct / 100.0)`;
  `RemoveByName` — через `catalog.erase(catalog.begin() + i)`.
- В `main()`: успех/отказ `Buy`, цены до/после скидки 10%, размер вектора
  до/после удаления; печать — только `const auto&`.
- Комментарий: почему после `erase`/`push_back` нельзя пользоваться
  ранее взятым `TProduct*`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task04 projects/shop-catalog/task-04-mutate-ref.cpp && /tmp/task04
```

## Задача 05 — pair/tuple + structured binding ✅

Файл: `task-05-stats-pair-tuple.cpp`. Темы: 2.5 — `pair`/`tuple`,
распаковка `auto [total, qty] = ...`, `std::get<>`.

- `enum class ECategory` и `struct TProduct` из задачи 03; `vector<TProduct>`
  из 3–4 товаров с designated initializers.
- Функция `Stats(const std::vector<TProduct>&)` возвращает
  `std::pair<double, int>` — сумма `Price * Qty` и общий `Qty`;
  в `main()` распаковка `auto [total, qty] = Stats(catalog);`
  и вывод в одну строку.
- Оба способа доступа: structured binding и `std::get<0>` / `std::get<1>`.
- Комментарий: `tuple` тоже распаковывается structured binding'ом
  (`auto [a, b, c] = tuple`), `pair` — его частный случай.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task05 projects/shop-catalog/task-05-stats-pair-tuple.cpp && /tmp/task05
```

## Задача 06 — финал: dangling + const-аудит + CLI-цикл ✅

Файл: `shop.cpp`. Темы: 2.7 — висячие ссылки/указатели, const-аудит,
CLI-цикл.

- В один файл собраны лучшие куски 01–05: `enum class ECategory`,
  `struct TProduct`, печать через `const auto&`, `FindByName` (задача 03),
  `Buy`/`Discount`/`RemoveByName` (задача 04), `Stats` (задача 05).
- `while (std::cin >> cmd)`: команды `add/list/find/buy/discount/stats/remove/exit`;
  `add` и `find`/`buy`/`remove` поддерживают многословные названия товаров.
- Комментарий про инвалидацию указателя: после `push_back`/`erase` ранее
  взятые `TProduct*` могут стать dangling — товар всегда достаётся заново
  через `FindByName`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/shop projects/shop-catalog/shop.cpp && /tmp/shop
```
