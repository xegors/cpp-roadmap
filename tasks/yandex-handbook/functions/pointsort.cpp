#include <algorithm>
#include <iostream>
#include <vector>

int DistanceSquared(const std::pair<int, int>& point) {
    return point.first * point.first + point.second * point.second;
}

int main() {
    int amount;
    std::cin >> amount;
    std::vector<std::pair<int, int>> points(amount);

    for (int i = 0; i != amount; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    std::sort(points.begin(), points.end(),
              [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
                  return DistanceSquared(lhs) < DistanceSquared(rhs);
              });

    for (const auto& point : points) {
        std::cout << point.first << " " << point.second << '\n';
    }
}
