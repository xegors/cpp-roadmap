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
    double overallSum = 0.0;
    int overallQty = 0;

    for (const auto& p : catalog) {
        overallQty += p.qty;
        overallSum += p.price * p.qty;
    }

    return {overallSum, overallQty};
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

    std::cout << "Via `std::get<0>`: " << std::get<0>(stats(catalog)) << '\n';
    std::cout << "Via `std::get<1>`: " << std::get<1>(stats(catalog)) << '\n';

    // Кортеж, как и пару можно распаковать с помощью structured binding.
    std::tuple<int, std::string, double> t = {1, "wow!", 3.1415};
    auto [a, b, c] = t;
    std::cout << a << " " << b << " " << c << '\n';
}