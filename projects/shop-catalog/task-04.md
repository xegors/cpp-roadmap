# Задача 04 — изменение через ссылки/указатели

Файл решения: `task-04-mutate-ref.cpp` (создаёшь сам, здесь только постановка).
Темы: параграф 2.6 — мутация через `Product*` и `auto&`, `erase` у вектора,
инвалидация указателей.

## Что сделать

1. Скопируй `Category`, `Product`, `findByName` из задачи 03.
2. Напиши три функции:
   ```cpp
   bool buy(std::vector<Product>& catalog, const std::string& name, int n);
   void discount(std::vector<Product>& catalog, double pct);
   bool removeByName(std::vector<Product>& catalog, const std::string& name);
   ```
   - `buy`: найди через `findByName`, проверь `nullptr` и `qty >= n`,
     вычти `n` из `p->qty`, верни `true/false`;
   - `discount`: пройди `for (auto& p : catalog)` (именно mutable-ссылка),
     `p.price *= (1 - pct / 100.0)`;
   - `removeByName`: найди индекс циклом, удали через
     `catalog.erase(catalog.begin() + i)`, верни `true/false`.
3. В `main()`:
   - создай `catalog` из 3–4 товаров;
   - вызови `buy` для существующего (успех) и для отсутствующего / с большим `n` (отказ);
   - вызови `discount` на 10% и покажи цены до/после;
   - вызови `removeByName` и покажи размер вектора до/после;
   - печать списка — как в задаче 02, через `const auto&`.
4. В комментарии одной строкой: почему после `erase`/`push_back` нельзя
   пользоваться ранее взятым `Product*`.

## Требования

- `#include <iostream>`, `#include <string>`, `#include <vector>`. Больше ничего.
- Все три функции обязательны, сигнатуры — как выше.
- Печать — только `const auto&`; мутация — только `Product*` / `auto&`.
- Один файл с `main()`.

## Проверка

```bash
clang++ -std=c++20 -O2 -Wall -Wextra -o /tmp/task04 projects/shop-catalog/task-04-mutate-ref.cpp && /tmp/task04
```

Приёмка:
- [ ] компилируется без варнингов;
- [ ] `buy` с `nullptr`-проверкой и проверкой `qty`, `discount` через `auto&`, `remove` через `erase`;
- [ ] в выводе видны успех/отказ `buy`, цены до/после скидки, размер до/после удаления;
- [ ] есть коммент про инвалидацию указателя.

## Подсказки (не решение)

- `buy` возвращает `bool`, чтобы в `main` напечатать `ok` / `fail`.
- `discount` ничего не возвращает — меняет на месте.
- Указатель бери заново после каждого `erase`/`push_back`, не храни его между операциями.

Когда будет готово — кидай файл, разберём и дам задачу 05.
