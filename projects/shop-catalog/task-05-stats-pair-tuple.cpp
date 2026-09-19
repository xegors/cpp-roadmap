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

std::pair<double, int> Stats(const std::vector<TProduct>& catalog) {
    double overallSum = 0.0;
    int overallQty = 0;

    for (const auto& p : catalog) {
        overallQty += p.Qty;
        overallSum += p.Price * p.Qty;
    }

    return {overallSum, overallQty};
}

int main() {
    std::vector<TProduct> catalog = {
        {"Local Chicken Breast", 499.9, 15, ECategory::Food},
        {.Name = "Olympus OM-D E-M1 Mark III", .Price = 10990.0, .Qty = 2, .Cat = ECategory::Tech},
        {"Some Old Soviet Bike", 4990.0, 1, ECategory::Bike},
        {"Flush by Virginia Woolf", 700.0, 70, ECategory::Book}};

    auto [total, qty] = Stats(catalog);
    std::cout << "Total value: " << total << ", Total qty: " << qty << '\n';

    std::cout << "Via `std::get<0>`: " << std::get<0>(Stats(catalog)) << '\n';
    std::cout << "Via `std::get<1>`: " << std::get<1>(Stats(catalog)) << '\n';

    // Кортеж, как и пару можно распаковать с помощью structured binding.
    std::tuple<int, std::string, double> t = {1, "wow!", 3.1415};
    auto [a, b, c] = t;
    std::cout << a << " " << b << " " << c << '\n';
}