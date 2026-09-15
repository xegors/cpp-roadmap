#include <iostream>
#include <string>
#include <vector>
#include <utility>

enum class Category {
    Food,
    Bike,
    Tech,
    Book
};

struct Product {
    std::string name;
    double price = 0.0;
    int qty = 0;
    Category cat;
};

// Helper: читает одну строку из cin после оператора >>
// пропускает лидирующие пробелы/переводы строки
std::string readLine() {
    std::string s;
    std::getline(std::cin >> std::ws, s);
    return s;
}

// --- findByName (задача 03, один вариант) ---
Product* findByName(std::vector<Product>& catalog, const std::string& name) {
    for (auto& p : catalog) {
        if (name == p.name) return &p;
    }
    return nullptr;
}

// --- buy (задача 04) ---
// Теперь принимает уже найденный Product* — вызывающий код берет указатель
bool buy(Product* p, int n) {
    if (p == nullptr || p->qty < n || n <= 0) return false;
    p->qty -= n;
    return true;
}

void discount(std::vector<Product>& catalog, double pct) {
    for (auto& p : catalog) {
        p.price *= (1 - pct / 100.0);
    }
}

bool removeByName(std::vector<Product>& catalog, const std::string& name) {
    for (size_t i = 0; i != catalog.size(); ++i) {
        if (catalog[i].name == name) {
            catalog.erase(catalog.begin() + i);
            return true;
        }
    }
    return false;
}

// --- stats (задача 05) ---
std::pair<double, int> stats(const std::vector<Product>& catalog) {
    double overallSum = 0.0;
    int overallQty = 0;
    for (const auto& p : catalog) {
        overallQty += p.qty;
        overallSum += p.price * p.qty;
    }
    return {overallSum, overallQty};
}

void printCatalog(const std::vector<Product>& catalog) {
    for (const auto& p : catalog) {
        std::cout << p.name << " | " << p.price << " | " << p.qty << " | "
                  << static_cast<int>(p.cat) << '\n';
    }
}

int main() {
    std::vector<Product> catalog = {
        {
            "Local Chicken Breast",
            499.9,
            15,
            Category::Food
        },
        {
            .name = "Olympus OM-D E-M1 Mark III",
            .price = 10990.0,
            .qty = 2,
            .cat = Category::Tech
        },
        {
            "Some Old Soviet Bike",
            4990.0,
            1,
            Category::Bike
        },
        {
            "Flush by Virginia Woolf",
            700.0,
            70,
            Category::Book
        }
    };

    // Комментарий про инвалидацию указателя (задача 04-05):
    // После push_back/erase указатели, взятые до этих операций,
    // могут стать dangling (указать на освобождённую память).
    // Всегда доставай товар заново через findByName, не храним указатели между операциями.

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "exit") {
            break;
        } else if (cmd == "list") {
            printCatalog(catalog);
        } else if (cmd == "find") {
            std::string name = readLine();
            Product* p = findByName(catalog, name);
            if (p != nullptr) {
                std::cout << p->name << " | " << p->price << " | " << p->qty << " | "
                          << static_cast<int>(p->cat) << '\n';
            } else {
                std::cout << "not found!\n";
            }
        } else if (cmd == "buy") {
            std::string line = readLine();
            // Парсим: последнее слово — qty, всё до него — имя
            size_t lastSpace = line.rfind(' ');
            if (lastSpace != std::string::npos) {
                std::string name = line.substr(0, lastSpace);
                int qty = std::stoi(line.substr(lastSpace + 1));
                Product* p = findByName(catalog, name);
                if (buy(p, qty)) {
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
            discount(catalog, pct);
            // показать цены до/после
            std::cout << "After discount:\n";
            printCatalog(catalog);
        } else if (cmd == "stats") {
            auto [total, qty] = stats(catalog);
            std::cout << "Total: " << total << ", Total quantity: " << qty << '\n';
        } else if (cmd == "remove") {
            std::string name = readLine();
            std::cout << (removeByName(catalog, name) ? "Removed!\n" : "Not found!\n");
            // после remove указатели, взятые ранее, могут быть инвалидными — см. комментарий выше
        } else if (cmd == "add") {
            std::string line = readLine();
            // Парсим строку: "Local Chicken Breast 499.9 15 Food"
            // Последние 3 пробела разделяют cat, qty, price
            // Всё, что перед ними — название (может быть многословным)
            size_t p3 = line.rfind(' ');             // начало catStr
            size_t p2 = line.rfind(' ', p3 - 1);      // начало qty
            size_t p1 = line.rfind(' ', p2 - 1);      // начало price

            std::string catStr = line.substr(p3 + 1);
            int qty = std::stoi(line.substr(p2 + 1, p3 - p2 - 1));
            double price = std::stod(line.substr(p1 + 1, p2 - p1 - 1));
            std::string name = line.substr(0, p1);

            Category cat;
            if (catStr == "Food") cat = Category::Food;
            else if (catStr == "Bike") cat = Category::Bike;
            else if (catStr == "Tech") cat = Category::Tech;
            else if (catStr == "Book") cat = Category::Book;
            else cat = Category::Food; // default

            catalog.push_back({name, price, qty, cat});
            // после push_back старые pointers могут инвалидироваться — см. комментарий выше
            std::cout << "Added.\n";
        } else {
            std::cout << "Unknown command!\n";
        }
    }
    return 0;
}