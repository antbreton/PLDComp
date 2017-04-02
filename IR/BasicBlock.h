#ifndef PLDCOMP_BASICBLOCK_H
#define PLDCOMP_BASICBLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "IRInstr.h"
#include "CFG.h"
#include "../Fonction.h"

class BasicBlock {
	public:
		BasicBlock(); // Pour bloc vide, cf cours
		BasicBlock(CFG* cfg, Bloc* bloc);
		~BasicBlock();
		
		std::string genererAssembleur();
		void addInstrIR(IRInstr* instruction);
		
		CFG* getCFG();

	private:
		std::vector<IRInstr * > listeInstructionsIR;
		BasicBlock* succCond; // Son successeur conditionnel
		BasicBlock* succIncond; // Son sucesseur inconditionnel
		CFG* cfg;
};



#endif // PLDCOMP_BASICBLOCK_H