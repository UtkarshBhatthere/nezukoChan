#include "ram.h"

int main() {
    ram myRam(0, 2048, 2048);
    myRam[1024] = 205; //setting value.
    
    std::cout << (int)myRam[1024] << "\n";

    return 0;
}