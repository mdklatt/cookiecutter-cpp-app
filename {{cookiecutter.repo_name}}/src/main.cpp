// Application entry point.
//
#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;


int main() {
    extern string greeting();  // greeting.cpp
    std::cout << greeting() << endl;
    return EXIT_SUCCESS;
}
