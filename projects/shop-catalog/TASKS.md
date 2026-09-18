# Shop Catalog — план и статус проекта

Учебный проект: каталог товаров. Каркас для параграфов 2.5 (составные типы)
+ 2.6 (ссылки, указатели, const) с небольшим забеганием в 2.7 (функции).

Правило: каждый `.cpp` — отдельная программа с `main()`, общего хедера нет —
типы (`Category`, `Product`) копируются из задачи в задачу. Проект растёт
по задачам: каждая задача — свой файл `task-NN-*.cpp`. Финальная сборка —
`shop.cpp` из лучших кусков.

Все шесть задач выполнены. Файлы решений 01–04 лежат в репозитории;
файлы решений 05–06 в репозиторий не добавлялись.

## Задача 01 — struct + enum ✅

Файл: `task-01-struct-enum.cpp`. Темы: 2.5 — `enum class`, `struct`,
designated initializers, `sizeof`/выравнивание.

- `enum class Category` (4 значения), `struct Product`
  (`name`, `price = 0.0`, `qty = 0`, `cat`).
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

- `vector<Product>` из 3–4 товаров, печать только через
  `for (const auto& p : catalog)` в виде `name | price | qty | cat-as-int`.
- Правка одного поля вне цикла печати + повторный вывод.
- Плюс `<vector>` к инклудам задачи 01; весь код в `main()`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task02 projects/shop-catalog/task-02-print-const-ref.cpp && /tmp/task02
```

## Задача 03 — поиск указателями ✅

Файл: `task-03-find-pointer.cpp`. Темы: 2.6 (упор) + первое забегание
в 2.7 — `Product*`, `const Product*`, `nullptr`, `->`, `*`.

- Функции (сигнатуры обязательны):
  ```cpp
  Product* findByName(std::vector<Product>& catalog, const std::string& name);
  const Product* findByNameConst(const std::vector<Product>& catalog, const std::string& name);
  ```
  Возврат `&catalog[i]` при совпадении, иначе `nullptr`.
- В `main()`: поиск существующего (доступ через `->`) и несуществующего
  (`not found`), вызов const-версии (доступ через `(*p).`),
  комментарий про `const Product*` vs `Product* const`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task03 projects/shop-catalog/task-03-find-pointer.cpp && /tmp/task03
```

## Задача 04 — изменение через ссылки/указатели ✅

Файл: `task-04-mutate-ref.cpp`. Темы: 2.6 — мутация через `Product*`
и `auto&`, `erase`, инвалидация указателей.

- Функции (сигнатуры обязательны):
  ```cpp
  bool buy(std::vector<Product>& catalog, const std::string& name, int n);
  void discount(std::vector<Product>& catalog, double pct);
  bool removeByName(std::vector<Product>& catalog, const std::string& name);
  ```
  `buy` — через `findByName` с проверками `nullptr` и `qty >= n`;
  `discount` — `for (auto& p : catalog)`, `p.price *= (1 - pct / 100.0)`;
  `removeByName` — через `catalog.erase(catalog.begin() + i)`.
- В `main()`: успех/отказ `buy`, цены до/после скидки 10%, размер вектора
  до/после удаления; печать — только `const auto&`.
- Комментарий: почему после `erase`/`push_back` нельзя пользоваться
  ранее взятым `Product*`.

Проверка:

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task04 projects/shop-catalog/task-04-mutate-ref.cpp && /tmp/task04
```

## Задача 05 — pair/tuple + structured binding ✅

Файл решения в репозиторий не добавлялся. Темы: 2.5 — `stats` возвращает
`pair`/`tuple`, распаковка `auto [total, qty] = ...`, `std::get<>`.
Плановый файл: `task-05-stats-pair-tuple.cpp`.

## Задача 06 — финал: dangling + const-аудит + CLI-цикл ✅

Файл решения в репозиторий не добавлялся. Собрать `shop.cpp` с командами
`add/list/find/buy/discount/stats/remove/exit`, прокомментировать одно место
с висячей ссылкой и как его избежали. Плановый файл: `shop.cpp`.
