#include <stdio.h>
#include <stdlib.h>


	using Byte = unsigned char;  // 8 bit
	using Word = unsigned short; //
	using u32 = unsigned int;

struct Memory{
  static constexpr u32 MAX_MEM = 1024*64;
  Byte Data[MAX_MEM];
  void initialize(){
      for(u32 i=0;i<MAX_MEM;i++){
        Data[i]=0;
      }
    }
};

struct CPU{

	Word PC; // Program Counter register
	Word SP; // Stack Pointer register

	Byte A,X,Y;

	Byte C : 1;
	Byte Z : 1;
	Byte I : 1;
	Byte D : 1; // decimal status flag.
	Byte B : 1;
	Byte V : 1;
	Byte N : 1;

	void reset(Memory& memory){
    PC = 0xFFFC;
    C=Z=I=B=V=N=D=0;
    SP = 0x0100;
    A = X = Y = 0;
    memory.initialize();
	}
};

int main(){
  Memory mem;
	CPU cpu;
	cpu.reset(mem);
	return 0;
}
