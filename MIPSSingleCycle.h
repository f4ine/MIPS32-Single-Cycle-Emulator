#include <inttypes.h>

class MIPSSingleCycle
{
public:
	unsigned char memory[0x1000]; /* 4096 (4K) addressable bytes
										 in the Harris microarchitecture the instruction ROM and data RAM
										 are physically separate and may be composed of different memory chips
										 so address decoding hardware is needed to map memory according to MIPS
										 architecture. But in most computers code is loaded from a ROM, flash, etc..
										 and loaded into RAM, in this case at starting address 0x004000000*/

	uint32_t instruction;
	uint32_t pc;
	int32_t r[32];
	uint32_t ra;
	int32_t signImm;
	unsigned char opcode;
	unsigned char func;
	unsigned char rs;
	unsigned char rt;
	unsigned char rd;

	void Fetch();
	void Decode();
	void Execute();

public:

	void Reset();
	void EmulateCycle();

};


void MIPSSingleCycle::Reset() {
	pc = 0x100; // code starting address 2048;
	for (int i = 0; i < 32; i++) {
		r[i] = 0;
	}
	for (int i = 0; i < 4096; i++) {
		memory[i] = 0;
	}

	// For Testing:
	memory[0x100] = 0b00100000; memory[0x101] = 0b00000001; memory[0x102] = 0b11111111; memory[0x103] = 0b11111100;
	memory[0x104] = 0b10101100; memory[0x105] = 0b00000001; memory[0x106] = 0b00000000; memory[0x107] = 0b00000000;
	memory[0x108] = 0b10001100; memory[0x109] = 0b00011110; memory[0x10A] = 0b00000000; memory[0x10B] = 0b00000000;
	memory[0x10C] = 0b00100011; memory[0x10D] = 0b11011110; memory[0x10E] = 0b00000000; memory[0x10F] = 0b00000100;
	memory[0x110] = 0b00100000; memory[0x111] = 0b00000001; memory[0x112] = 0b00000000; memory[0x113] = 0b00000000;
	memory[0x114] = 0b00001000; memory[0x115] = 0b00000000; memory[0x116] = 0b00000000; memory[0x117] = 0b00000000;

}

void MIPSSingleCycle::EmulateCycle() {
	Fetch();
	Decode();
	Execute();
}

void MIPSSingleCycle::Fetch() {
	instruction = (memory[pc] << 24) | (memory[pc + 1] << 16) | (memory[pc + 2] << 8) | memory[pc + 3];
	pc = pc + 4;
}

void MIPSSingleCycle::Decode() {
	opcode = instruction >> 26;
	func = instruction & 0x2F;

	rs = (instruction & 0x03E00000) >> 21;
	rt = (instruction & 0x001F0000) >> 16;
	rd = (instruction & 0x0000F800) >> 11;

	// Sign extension of immediate field
	uint32_t signBit = ((instruction & 0x0000FFFF) >> 15);
	if (signBit == 1) {
		signImm = ((instruction & 0x0000FFFF) | 0xFFFF0000);
	}
	else {
		signImm = (instruction & 0x0000FFFF);
	}
}

void MIPSSingleCycle::Execute() {

	switch (opcode)
	{
		case 0: // R-type opcode 000000
			switch (func)
			{
				case 32:	
					r[rd] = r[rs] + r[rt];
				break;

				case 33:
					r[rd] = (uint32_t)r[rs] + (uint32_t)r[rt];
				break;

				case 34:
					r[rd] = r[rs] - r[rt];
				break;

				case 35:
					r[rd] = (uint32_t)r[rs] - (uint32_t)r[rt];
				break;

				// There are more R-type instructions to be added in

			}
		break;

		case 2:		// j
			pc = ((instruction & 0x02FFFFFF) << 2) + 0x100; // program (word address) in immediate field
															// + program base address
		break;

		case 3:		// jal
			ra = pc;	// pc incremented already in Fetch()
			pc = ((instruction & 0x02FFFFFF) << 2) + 0x100;
		break;

		case 4:		// beq
			if (r[rs] == r[rt]) {
				pc = pc + signImm;
			}
		break;

		case 5:		// bne
			if (r[rs] != r[rt]) {
				pc = pc + signImm;
			}
		break;

		case 6:		// blez
			if (r[rs] <= 0) {
				pc = pc + signImm;
			}
		break;

		case 7:		// bgtz
			if (r[rs] > 0) {
				pc = pc + signImm;
			}
		break;

		case 8:		// addi
			r[rt] = r[rs] + signImm;
		break;

		case 9:		// addiu
			r[rt] = r[rs] + (uint32_t)signImm;
		break;

		case 10:		// slti
			if (r[rs] < signImm) r[rt] = 1;
			else r[rt] = 0;
		break;

		case 11:		//sltiu
			if ((uint32_t)r[rs] < (uint32_t)(signImm)) r[rt] = 1;
			else r[rt] = 0;
		break;

		case 12:		// andi
			r[rt] = r[rs] & signImm;
		break;

		case 13:		// ori
			r[rt] = r[rs] | signImm;
		break;

		case 14:		// xori
			r[rt] = r[rs] ^ signImm;
		break;

		case 15:		// lui
			r[rt] = (instruction & 0x0000FFFF) << 16;
		break;

		case 35:		// lw
			r[rt] = (memory[rs + signImm] << 24) | (memory[rs + signImm + 1] << 16)
				| (memory[rs + signImm + 2] << 8) | (memory[rs + signImm + 3]);
		break;

		case 43:		// sw
			memory[rs + signImm] = r[rt] >> 24;
			memory[rs + signImm + 1] = (r[rt] >> 16) & 0x000000FF;
			memory[rs + signImm + 2] = r[rt] >> 8 & 0x000000FF;
			memory[rs + signImm + 3] = r[rt] & 0x000000FF;
	}

}

