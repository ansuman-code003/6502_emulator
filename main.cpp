#include <stdio.h>
#include <stdlib.h>
using namespace std;

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;

struct Memory {
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];
	void Initialized()
	{
		for (u32 i = 0; i < MAX_MEM; i++) {
			Data[i] = 0;
		}
	}
	Byte operator[](u32 Address) const { return Data[Address]; } // read one slot i.e byte
	Byte& operator[](u32 Address) { return Data[Address]; }      //  write one slot i.e byte
};

struct CPU {

	Word PC; // Program Counter
	Word SP; // Stack Pointer

	Byte A, X, Y;
	Byte C : 1;
	Byte Z : 1;
	Byte I : 1;
	Byte D : 1;
	Byte B : 1;
	Byte V : 1;
	Byte N : 1;

	// opcodes
	static constexpr Byte INS_LDA_IM = 0xA9; // load data into accumulaotr immediately
	static constexpr Byte INS_LDA_ZP = 0xA5; // load data into accumulator zero-page

	void LDASetStatus()
	{
		Z = (A == 0);
		N = (A & 0b10000000) > 0;
	}

	void reset(Memory& mem)
	{
		PC = 0xFFFC;
		SP = 0x0100;
		D = 0;
		C = Z = I = D = B = V = N = 0;
		A = X = Y = 0;
		mem.Initialized();
	}

	Byte fetchByte(u32& ticks, Memory& mem)
	{
		Byte Data = mem[PC];
		PC++;
		ticks--;
		return Data;
	}

	Byte readByte(u32& ticks, Byte Address, Memory& mem)
	{
		Byte Data = mem[Address];
		ticks--;
		return Data;
	}

	void Execute(u32 ticks, Memory& mem)
	{
		while (ticks > 0) {
			Byte ins = fetchByte(ticks, mem);
			switch (ins) {

				case INS_LDA_IM: {
					Byte value = fetchByte(ticks, mem);
					A = value;
					LDASetStatus();
				} break;

				case INS_LDA_ZP: {
					Byte ZeroPageAddress = fetchByte(ticks, mem);
					A = readByte(ticks, ZeroPageAddress, mem);
					LDASetStatus();
				} break;

				default: {
					printf("Instruction not handled %d", ins);
				} break;
			}
		}
	}
};

int main()
{
	CPU cpu;
	Memory memory;
	cpu.reset(memory);

	memory[0xFFC] = CPU::INS_LDA_IM;
	memory[0xFFD] = 0x42;

	cpu.Execute(2, memory);
	return 0;
}
