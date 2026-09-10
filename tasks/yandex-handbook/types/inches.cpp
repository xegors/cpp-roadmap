#include <iostream>

int main(){
    using namespace std;

    double lengthInCM;
    cin >> lengthInCM;

    double lengthInIN = lengthInCM / 2.54;
    
    cout << lengthInIN;
}