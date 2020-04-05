#pragma once

#include <vector>

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
		ram_size = size;		// Expects pure powers of 2 (2, 4, 8, 16, etc. bytes).

		// Resize vector with nulled values.
		ram_internal.resize(ram_size, 0);

	}

	uint8_t& operator[](const addr address) {
		if(address >= ram_start_addr && address <= ram_end_addr)
			return ram_internal[address & (ram_size - 1)];
	}

};

