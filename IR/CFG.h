#ifndef PLDCOMP_CFG_H
#define PLDCOMP_CFG_H

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "../General.h"
#include "../Fonction.h"
#include "BasicBlock.h"
#include "IRVar.h"

class IR;

class CFG {
	public:
		CFG(Fonction* fonction);
		~CFG();
		
		std::string genererAssembleur();
		void addBasicBlock(BasicBlock* newBasicBlock);
		int calculeTaille ();
		int getTaille() {return taille;};
		void setTaille(int a) {taille = a;};
		std::string creerNouveauRegistre();
		std::string creerNouveauRegistre(int nbRegVirt);
		BasicBlock* getBlockCourant() {return this->blocCourant;}
		void setBlockCourant(BasicBlock* blocC) {blocCourant = blocC;}
		int getNbRegVirtuels();
		void incrementerNbRegVirtuels(){ this->nbRegVirtuels++; }
		std::string gen_prologue();
		std::string gen_epilogue();
		std::map<string, IRVar*>* getDicoRegTmp() const {return dicoRegTmp;}
		

	private:
		std::list<BasicBlock* > listeBasicBlocks;
		Fonction* fonctionDuCFG;
		int nbRegVirtuels;
		std::map<string, IRVar*>* dicoRegTmp; // Table des symboles : On stockera ici nos registres virtuels
		BasicBlock* blocCourant;
		int taille;


};
#endif //PLDCOMP_CFG_H