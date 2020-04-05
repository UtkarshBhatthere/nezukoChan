#include <iostream>
#include <vector>

bool func(uint8_t opcode) {
    std::vector<uint8_t> two_byte_NOP{ 0x1C, 0x3C, 0x5C, 0x7C, 0xDC, 0xFC };
	for (auto& x : two_byte_NOP) {
		if (opcode == x)
			return 1;
	}
    return 0;
}

int main() {
    uint8_t opcode = 0x7C;
    std::cout << func(opcode);

    return 0;
    
}