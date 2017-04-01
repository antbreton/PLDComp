#ifndef PLDCOMP_CFG_H
#define PLDCOMP_CFG_H

#include <iostream>
#include <string>
#include <vector>
#include "General.h"
class BasicBlock;

class CFG {
	public:
		CFG();
		~CFG();
		
		std::string genererAssembleur();
		void addBasicBlock(BasicBlock* newBasicBlock);

	private:
		std::list<BasicBlock* > listeBasicBlocks;
		// TODO : Table des symboles
		Programme * programme;


};
#endif //PLDCOMP_CFG_H