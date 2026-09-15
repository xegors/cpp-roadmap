#include <iostream>
#include <vector>
#include <string>
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

Product* findByName(std::vector<Product>& catalog, const std::string& name) {
    for (auto& p : catalog) {
        if (name == p.name) return &p;
    }

    return nullptr;
}

bool buy(std::vector<Product>& catalog, const std::string& name, int n) {
    Product* p = findByName(catalog, name);
    if (p == nullptr || p->qty < n || n <= 0) return false;

    p->qty -= n;
    return true;
}

bool add(std::vector<Product>& catalog, const Product* p) {
    if (p->qty <= 0 || p->price <= 0 || p->name == "") return false;

    catalog.push_back(*p);
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
    
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "exit") {
            break;
        } 

        else if (cmd == "add") {
            std::string name, catStr;
            double price;
            int qty;
            if (std::cin >> name >> price >> qty >> catStr) {
                Category cat;
                if (catStr == "Food") cat = Category::Food;
                else if (catStr == "Bike") cat = Category::Bike; 
                else if (catStr == "Tech") cat = Category::Tech; 
                else cat = Category::Book;

                Product p = {name, price, qty, cat};
                if (add(catalog, &p)) std::cout << "Added.\n";
                else std::cout << "Error occured.\n";
            } else std::cout << "Error occured.\n";
        }

        else if (cmd == "list") {
            printCatalog(catalog);
        }

        else if (cmd == "find") {
            std::string name;
            if (std::cin >> name) {
                const Product* p = findByName(catalog, name);
                if (p == nullptr) std::cout << "Not found.\n";    
                else {
                    std::cout   << p->name  << " | " << p->price << " | " 
                                << p->qty << " | " << static_cast<int>(p->cat) << '\n';
                }
            } else std::cout << "Error occured.\n";
        }

        else if (cmd == "buy") {
            std::string name;
            int qty; 
            if (std::cin >> name >> qty) {
                if (buy(catalog, name, qty)) std::cout << name << " bought.\n";
                else std::cout << "Error occured.\n"; 
            } else std::cout << "Error occured.\n";
        }

        else if (cmd == "discount") {
            double pct;
            if (std::cin >> pct) {
                if (pct <= 0) std::cout << "Error occured.\n";
                else {
                    discount(catalog, pct);
                    std::cout << pct << "\% discount applied.\n";
                    printCatalog(catalog);
                }
            } else std::cout << "Error occured.\n";
        }

        else if (cmd == "stats") {
            auto [total, qty] = stats(catalog);
            std::cout << "Total: " << total << ", Total quantity: " << qty << '\n';
        }

        else if (cmd == "remove") {
            std::string name;
            if (std::cin >> name) {
                if (removeByName(catalog, name)) std::cout << name << " removed.\n";
                else std::cout << "Error occured.\n";
            } else std::cout << "Error occured.\n";
        } 

        else {
            std::cout << "Unknown command!\n";
        }
    }

    return 0;
}