#include <iostream>
#include <string>

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

int main() {
    Product chickenBreast = {"Local Chicken Breast", 499.9, 15, Category::Food};
    Product basicCameraBody = {
        .name = "Olympus OM-D E-M1 Mark ii",
        .price = 24999.9,
        .qty = 10,
        .cat = Category::Tech
    };

    basicCameraBody.price = 20000.0;
    
    std::cout << "Enum -> int: " << static_cast<int>(chickenBreast.cat) << '\n';
    Category bike = static_cast<Category>(1);
    std::cout << "int -> Enum -> int: " << static_cast<int>(bike) << '\n';

    std::cout << sizeof(Category) << '\n';  // тут размер должен быть 4 байта
    std::cout << sizeof(chickenBreast.name) << '\n'; // 32 
    std::cout << sizeof(chickenBreast) << '\n';  // 32 + 8 + 4 + 4 = 48
    /*
        в прошлом примере арифметика уже дает 48 байт информации, 
        что делится на 8 - значит уже выровнено.
    */
}