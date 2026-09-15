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

std::pair<double, int> stats(const std::vector<Product>& catalog) {
    double total = 0.0;
    int qty = 0;
    for (const auto& p : catalog) {
        total += p.price * p.qty;
        qty += p.qty;
    }
    return {total, qty};
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

    auto [total, qty] = stats(catalog);
    std::cout << "Total value: " << total << ", Total qty: " << qty << '\n';

    std::cout << "Via std::get<0>: " << std::get<0>(stats(catalog)) << '\n';
    std::cout << "Via std::get<1>: " << std::get<1>(stats(catalog)) << '\n';

    // Structured binding works with pair/tuple/array
    // auto [t, q, n] = tuple_would_fail; // нельзя так, тут 2 элемента

    return 0;
}