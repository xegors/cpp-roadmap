# Shop Catalog — план проекта

Каркас для параграфов 2.5 (составные типы) + 2.6 (ссылки, указатели, const)
с небольшим забеганием в 2.7 (функции).

Правило: каждый `.cpp` — отдельная программа с `main()`. Проект растёт
по задачам: каждая задача — свой файл `task-NN-*.cpp`, который ты пишешь сам.
Финальная сборка — `shop.cpp` из лучших кусков (тоже сам).

## Разбивка на задачи

- [ ] **01 — struct + enum (2.5).** `Category`, `Product`, designated initializers,
      `sizeof`/выравнивание. Файл: `task-01-struct-enum.cpp`.
      Детали — в `task-01.md`.
- [ ] **02 — печать через const-ссылки (2.6).** `vector<Product>`, вывод списка
      только через `for (const auto& p : ...)`, без копий.
      Файл: `task-02-print-const-ref.cpp`.
- [ ] **03 — поиск указателями (2.6, упор).** `Product* find(...)`,
      `const Product* findConst(...)`, `nullptr`, `->`, `*`,
      `const Product*` vs `Product* const`.
      Файл: `task-03-find-pointer.cpp`.
- [ ] **04 — изменение через ссылки/указатели (2.6).** `buy` (через `Product*`),
      `discount` (через `for (auto& ...)`), `remove`.
      Файл: `task-04-mutate-ref.cpp`.
- [ ] **05 — pair/tuple + structured binding (2.5).** `stats` возвращает
      `pair`/`tuple`, распаковка `auto [total, qty] = ...`, `std::get<>`.
      Файл: `task-05-stats-pair-tuple.cpp`.
- [ ] **06 — финал: dangling + const-аудит + CLI-цикл.** Собрать `shop.cpp`
      с командами `add/list/find/buy/discount/stats/remove/exit`,
      прокомментировать одно место с висячей ссылкой и как его избежали.
      Файл: `shop.cpp`.

Решения здесь не лежат — только постановки. Пишешь код сам.
