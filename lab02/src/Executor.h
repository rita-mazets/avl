
#ifndef RISCV_SIM_EXECUTOR_H
#define RISCV_SIM_EXECUTOR_H

#include "Instruction.h"

class Executor
{
public:
    void Execute(InstructionPtr& instr, Word ip)
    {
        /* YOUR CODE HERE */
        
        switch (instr->_type)
        {
            case IType::Csrr:
            {
                instr->_data = instr->_csrVal;
                 break;
            }
            case IType::Csrw:
            {
                instr->_data = instr->_src1Val;
                 break;
            }
            case IType::St:
            {
                instr->_data = instr->_src2Val;
                 break;
            }
            case IType::J:
            case IType::Jr:
            {
                instr->_data = ip + 4u;
                 break;
            }
            case IType::Auipc:
            {
                instr->_data = ip + instr->_imm.value();
                 break;
            }
            default:
            {
                instr->_data = CalcAlu(instr);
                 break;
            }
        }
        
        switch (instr->_type)
        {
            case IType::St:
            {
                instr->_addr =  CalcAlu(instr);
                 break;
            }
            case IType::Ld:
            {
                instr->_addr = instr->_data; 
                 break;
            }
            default:
            {
                instr->_addr =  0xdeadbeaf;
                 break;
            }
        }
        
        
        if (IsJump(instr, ip))
        {
            switch(instr->_type)
            {
                case IType::Br:
                case IType::J:
                {
                    instr->_nextIp =  ip + instr->_imm.value();
                    break;
                }
                case IType::Jr:
                {
                    instr->_nextIp = instr->_src1Val + instr->_imm.value();
                    break;
                }
            }
        }
        else instr->_nextIp = ip + 4u;
    }

private:
    /* YOUR CODE HERE */
    Word CalcAlu(const InstructionPtr& instr)
    {
        Word op1 = instr->_src1Val;
        Word op2 = instr->_imm.value_or(instr->_src2Val);
        switch (instr->_aluFunc)
        {
            case AluFunc::Add:
            {
                return op1 + op2;
            }
            case AluFunc::Sub:
            {
                return op1 - op2;
            }
            case AluFunc::And:
            {
                return op1 & op2;
            }
            case AluFunc::Or:
            {
                return op1 | op2;
            }
            case AluFunc::Xor:
            {
                return op1 ^ op2;
            }
            case AluFunc::Slt:
            {
                return static_cast<SignedWord>(op1) <
                       static_cast<SignedWord>(op2);
            }
            case AluFunc::Sltu:
            {
                return op1 < op2;
            }
            case AluFunc::Sll:
            {
                return op1 << (op2 % 32);
            }
            case AluFunc::Srl:
            {
                return op1 >> (op2 % 32);
            }
            case AluFunc::Sra:
            {
                return static_cast<SignedWord>(op1) >> (op2 % 32);
            }
            default:
            {
                return 0xdeadbeaf;
            }
        }
    }

    bool IsJump (const InstructionPtr& instr, Word ip)
    {
        bool isJump = false;
        switch(instr->_brFunc)
        {
            case BrFunc::Eq:
            {
                isJump = instr->_src1Val == instr->_src2Val;
                break;
            }
            case BrFunc::Neq:
            {
                isJump = instr->_src1Val != instr->_src2Val;
                break;
            }
            case BrFunc::Lt:
            {
                isJump = static_cast<SignedWord>(instr->_src1Val) <
                         static_cast<SignedWord>(instr->_src2Val);
                break;
            }
            case BrFunc::Ltu:
            {
                isJump = instr->_src1Val < instr->_src2Val;
                break;
            }
            case BrFunc::Ge:
            {
                isJump = static_cast<SignedWord>(instr->_src1Val) >=
                         static_cast<SignedWord>(instr->_src2Val);
                break;
            }
            case BrFunc::Geu:
            {
                isJump = instr->_src1Val >= instr->_src2Val;
                break;
            }
            case BrFunc::AT:
            {
                isJump = true;
                break;
            }
            case BrFunc::NT:
            {
                isJump = false;
                break;
            }
        }

        return isJump;
    }

};

#endif // RISCV_SIM_EXECUTOR_H
