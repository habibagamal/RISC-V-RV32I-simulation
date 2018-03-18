/*
 This is just a skeleton. It DOES NOT implement all the requirements.
 It only recognizes the "ADD" and "SUB" instructions and prints
 "Unknown Instruction" for all other instructions.

 References:
 (1) The risc-v ISA Manual ver. 2.1 @ https://riscv.org/specifications/
 (2) https://github.com/michaeljclark/riscv-meta/blob/master/meta/opcodes
 */
//hi
#include <iostream>
#include <fstream>
#include "stdlib.h"
#include <iomanip>
#include <string>
using namespace std;

struct instWord
{
    string instText;
    unsigned int instMachineCode;
    unsigned int rd, rs1, rs2, funct3, funct7, opcode;
    unsigned int I_imm, S_imm, B_imm, U_imm, J_imm;
};
int regs[32]={0};
unsigned int pc = 0x0;
char memory[8*1024];    // 8KB of memory located at address 0

void emitError(char *s)
{
    cout << s;
    exit(0);
}

void printPrefix(unsigned int instA, unsigned int instCode)
{
    cout << "0x" << hex << std::setfill('0') << std::setw(8) << instA << "\t0x" << hex << std::setw(8) << instCode;
}

void instAssembleExec(instWord&inst)
{
    //Generate instruction machine code

    //execute instruction
    if(inst.opcode == 0x33)// R Instructions
    {
        switch(inst.funct3)
        {
            case 0:
                if(inst.funct7 == 32)
                    regs[inst.rd] = regs[inst.rs1] - regs[inst.rs2];
                else
                    regs[inst.rd] = regs[inst.rs1] + regs[inst.rs2];
                break;
            default:
                cout << "\tUnknown R Instruction \n";
        }
    }
    else
    {
        cout << "\tUnknown Instruction \n";
    }

}

int main()
{
    ifstream inFile;
    ofstream outFile;
    instWord W;

    inFile.open("div.s");
    if(inFile.is_open())
    {
        pc = 0x0;
        while(!inFile.eof())
        {
            getline (inFile, W.instText);

            //parse(&W);        //parse instText into its instruction format fields
            //instAssembleExec(&W);        //Generate instruction machine code and execute instruction
            //printPrefix(pc, W.instMachineCode);
            //save machine code to an output file
            pc += 4;
        }

        inFile.close();

        // print out the registers values
        for(int i = 0; i < 32; i++)
            cout << "x" << dec << i << ": \t"<< "0x" << hex << std::setfill('0') << std::setw(8) << regs[i] << "\n";
    }
    else
        emitError("Cannot access input file\n");
}
