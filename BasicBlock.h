#ifndef PLDCOMP_BASICBLOCK_H
#define PLDCOMP_BASICBLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "IRInstr.h"
#include "CFG.h"

class BasicBlock {
public:
    BasicBlock(CFG* cfg, BasicBlock* blocParent);
    ~BasicBlock();
    std::string genererAssembleur();

private:
	std::vector<IRInstr * > listeInstructions;
    BasicBlock* succCond; // Son successeur conditionnel
    BasicBlock* succIncond; // Son sucesseur inconditionnel
    CFG* cfg;
};



#endif // PLDCOMP_BASICBLOCK_H