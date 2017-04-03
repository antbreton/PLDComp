#ifndef PLDCOMP_BASICBLOCK_H
#define PLDCOMP_BASICBLOCK_H

#include <iostream>
#include <string>
#include <vector>
#include "IRInstr.h"
#include "../Fonction.h"
#include "CFG.h"
//class CFG;
class BasicBlock {
	public:

		BasicBlock(std::string label);
		BasicBlock(CFG* cfg, Bloc* bloc, std::string label);
		~BasicBlock();
		
		std::string genererAssembleur();
		void ajouterInstrIR(IRInstr* instruction);
		
		CFG* getCFG();
		std::string getLabel() {return label;};
		void setLabel(std::string label) {label = label;};


	private:
		std::vector<IRInstr * > listeInstructionsIR;
		BasicBlock* succCond; // Son successeur conditionnel
		BasicBlock* succIncond; // Son sucesseur inconditionnel
		CFG* cfg;
		std::string label;
};



#endif // PLDCOMP_BASICBLOCK_H