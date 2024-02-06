#include <exception>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int u32;

struct Mem
{
    static const u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void initialize()
    {
        for ( u32 i = 0; i < MAX_MEM; i++ )
        {
            Data[i] = 0;
        }
    };

    Byte operator[]( u32 Address ) const
    {
        // assert here Address is < MAX_MEM
        return Data[Address];
    } 
};

struct CPU
{

    Word PC; // program counter
    Word SP; // stack pointer

    Byte A, X, Y; // registers

    // status flags
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    void Reset( Mem& memory )
    {
        PC = 0xFFFC;
        SP = 0x0100;
        D = 0;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.initialize();
    };

    Byte FetchByte( u32& Cycles, Mem& memory )
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    void Execute( u32 Cycles, Mem& memory )
    {
        while ( Cycles > 0 )
        {
            Byte Ins = FetchByte( Cycles, memory );
        }
    };
};

void myFunction() {
  std::cout << "Stack Overflow" << std::endl;
  myFunction();
}

int main()
{
    Mem mem;
    CPU cpu;
    cpu.Reset( mem );
    cpu.Execute( 2, mem );
    std::cout << "Hello There" << std::endl;
    myFunction();
    return 0;
}
