#include <iostream>
#include <string>

enum class ECategory { Food, Bike, Tech, Book };

struct TProduct {
    std::string Name;
    double Price = 0.0;
    int Qty = 0;
    ECategory Cat;
};

int main() {
    TProduct chickenBreast = {"Local Chicken Breast", 499.9, 15, ECategory::Food};
    TProduct basicCameraBody = {
        .Name = "Olympus OM-D E-M1 Mark III", .Price = 24999.9, .Qty = 10, .Cat = ECategory::Tech};

    basicCameraBody.Price = 20000.0;

    std::cout << "Enum -> int: " << static_cast<int>(chickenBreast.Cat) << '\n';
    ECategory bike = static_cast<ECategory>(1);
    std::cout << "int -> Enum -> int: " << static_cast<int>(bike) << '\n';

    std::cout << sizeof(ECategory) << '\n';          // тут размер должен быть 4 байта
    std::cout << sizeof(chickenBreast.Name) << '\n'; // 32
    std::cout << sizeof(chickenBreast) << '\n';      // 32 + 8 + 4 + 4 = 48
    /*
        в прошлом примере арифметика уже дает 48 байт информации,
        что делится на 8 - значит уже выровнено.
    */
}