#ifndef PLDCOMP_CFG_H
#define PLDCOMP_CFG_H

#include <iostream>
#include <string>
#include <vector>
#include "General.h"
#include "Fonction.h"
class BasicBlock;

class CFG {
	public:
		CFG(Fonction* fonction);
		~CFG();
		
		std::string genererAssembleur();
		void addBasicBlock(BasicBlock* newBasicBlock);

	private:
		std::list<BasicBlock* > listeBasicBlocks;
		Fonction* fonctionDuCFG;
		// TODO : Table des symboles


};
#endif //PLDCOMP_CFG_H