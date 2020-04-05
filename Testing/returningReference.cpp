#include <iostream>
#include <vector>
#include <cstdint>

class ram
{
private:
	std::vector<uint8_t> ram_internal;
	/* Many systems use mirroring in rams i.e. although the ram may be of  **
	** smaller size it would be mapped on a larger address area. Hence the **
	** memory location is mirrored for the same location on the actual mem **
	** to multiple addressess.											   */
	using addr = uint16_t;
	addr ram_start_addr;
	addr ram_end_addr;
	addr ram_size;

public:
	
	ram(addr start, addr end, addr size)
	{
		// Setting Ram mirroring params.
		ram_start_addr = start;
		ram_end_addr = end;
		ram_size = size;		// In Bytes.

		// Reserving space for ram.
		ram_internal.reserve(ram_size);

		for (auto& x : ram_internal) {
			if (x != 0)
				std::cout << "Found a non zero element\n";
			else
				std::cout << "Vector is Clear\n";
		}

	}

	uint8_t& operator[](const addr address) {

		return ram_internal[address];
	}

};

int main(){
    ram myRam(0, 2048, 2048);
    myRam[1024] = 205; //setting value.
    std::cout << (int)myRam[1024] << "\n" ;
    return 0;
}