#include <iostream>
#include <string>
#include <utility>
#include <vector>

enum class ECategory { Food, Bike, Tech, Book };

struct TProduct {
    std::string Name;
    double Price = 0.0;
    int Qty = 0;
    ECategory Cat;
};

// Helper: читает одну строку из cin после оператора >>
// пропускает лидирующие пробелы/переводы строки
std::string ReadLine() {
    std::string s;
    std::getline(std::cin >> std::ws, s);
    return s;
}

// --- FindByName (задача 03, один вариант) ---
TProduct* FindByName(std::vector<TProduct>& catalog, const std::string& name) {
    for (auto& p : catalog) {
        if (name == p.Name)
            return &p;
    }
    return nullptr;
}

// --- buy (задача 04) ---
// Теперь принимает уже найденный TProduct* — вызывающий код берет указатель
bool Buy(TProduct* p, int n) {
    if (p == nullptr || p->Qty < n || n <= 0)
        return false;
    p->Qty -= n;
    return true;
}

void Discount(std::vector<TProduct>& catalog, double pct) {
    for (auto& p : catalog) {
        p.Price *= (1 - pct / 100.0);
    }
}

bool RemoveByName(std::vector<TProduct>& catalog, const std::string& name) {
    for (size_t i = 0; i != catalog.size(); ++i) {
        if (catalog[i].Name == name) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

// --- stats (задача 05) ---
std::pair<double, int> Stats(const std::vector<TProduct>& catalog) {
    double overallSum = 0.0;
    int overallQty = 0;
    for (const auto& p : catalog) {
        overallQty += p.Qty;
        overallSum += p.Price * p.Qty;
    }
    return {overallSum, overallQty};
}

void PrintCatalog(const std::vector<TProduct>& catalog) {
    for (const auto& p : catalog) {
        std::cout << p.Name << " | " << p.Price << " | " << p.Qty << " | "
                  << static_cast<int>(p.Cat) << '\n';
    }
}

int main() {
    std::vector<TProduct> catalog = {
        {"Local Chicken Breast", 499.9, 15, ECategory::Food},
        {.Name = "Olympus OM-D E-M1 Mark III", .Price = 10990.0, .Qty = 2, .Cat = ECategory::Tech},
        {"Some Old Soviet Bike", 4990.0, 1, ECategory::Bike},
        {"Flush by Virginia Woolf", 700.0, 70, ECategory::Book}};

    // Комментарий про инвалидацию указателя (задача 04-05):
    // После push_back/erase указатели, взятые до этих операций,
    // могут стать dangling (указать на освобождённую память).
    // Всегда доставай товар заново через FindByName, не храним указатели между операциями.

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            PrintCatalog(catalog);
        } else if (cmd == "find") {
            std::string name = ReadLine();
            TProduct* p = FindByName(catalog, name);
            if (p != nullptr) {
                std::cout << p->Name << " | " << p->Price << " | " << p->Qty << " | "
                          << static_cast<int>(p->Cat) << '\n';
            } else {
                std::cout << "not found!\n";
            }
        } else if (cmd == "buy") {
            std::string line = ReadLine();
            // Парсим: последнее слово — qty, всё до него — имя
            size_t lastSpace = line.rfind(' ');
            if (lastSpace != std::string::npos) {
                std::string name = line.substr(0, lastSpace);
                int qty = std::stoi(line.substr(lastSpace + 1));
                TProduct* p = FindByName(catalog, name);
                if (Buy(p, qty)) {
                    std::cout << "All good!\n";
                } else {
                    std::cout << "Nah!\n";
                }
            } else {
                std::cout << "Error occured.\n";
            }
        } else if (cmd == "discount") {
            double pct;
            std::cin >> pct;
            Discount(catalog, pct);
            // показать цены до/после
            std::cout << "After discount:\n";
            PrintCatalog(catalog);
        } else if (cmd == "stats") {
            auto [total, qty] = Stats(catalog);
            std::cout << "Total: " << total << ", Total quantity: " << qty << '\n';
        } else if (cmd == "remove") {
            std::string name = ReadLine();
            std::cout << (RemoveByName(catalog, name) ? "Removed!\n" : "Not found!\n");
            // после remove указатели, взятые ранее, могут быть инвалидными — см. комментарий выше
        } else if (cmd == "add") {
            std::string line = ReadLine();
            // Парсим строку: "Local Chicken Breast 499.9 15 Food"
            // Последние 3 пробела разделяют cat, qty, price
            // Всё, что перед ними — название (может быть многословным)
            size_t p3 = line.rfind(' ');         // начало catStr
            size_t p2 = line.rfind(' ', p3 - 1); // начало qty
            size_t p1 = line.rfind(' ', p2 - 1); // начало price

            std::string catStr = line.substr(p3 + 1);
            int qty = std::stoi(line.substr(p2 + 1, p3 - p2 - 1));
            double price = std::stod(line.substr(p1 + 1, p2 - p1 - 1));
            std::string name = line.substr(0, p1);

            ECategory cat;
            if (catStr == "Food")
                cat = ECategory::Food;
            else if (catStr == "Bike")
                cat = ECategory::Bike;
            else if (catStr == "Tech")
                cat = ECategory::Tech;
            else if (catStr == "Book")
                cat = ECategory::Book;
            else
                cat = ECategory::Food; // default

            catalog.push_back({name, price, qty, cat});
            // после push_back старые pointers могут инвалидироваться — см. комментарий выше
            std::cout << "Added.\n";
        } else {
            std::cout << "Unknown command!\n";
        }
    }
    return 0;
}