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
		void genererIR();
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
		
		// params
		IRVar* getVariable(string nom);
		void addVariable(IRVar* var);
		int giveOffsets();
		bool estUnParametre(string nomVariable);
		
		list<BasicBlock* > getListeBasicBlocks() { return listeBasicBlocks;};
		Fonction* getFonction() {return fonctionDuCFG;};

		int getNbBlocIF() { return this->nbBlocIF; }
		int getNbBlocELSE() { return this->nbBlocELSE; }
		int getNbBlocAfter() { return this->nbBlocAfter; }

		void incrementerNbBlocIF() { this->nbBlocIF++; }
		void incrementerNbBlocELSE() { this->nbBlocELSE++; }
		void incrementerNbBlocAfter() { this->nbBlocAfter++; }

	private:
		std::list<BasicBlock* > listeBasicBlocks;
		Fonction* fonctionDuCFG;
		int nbRegVirtuels;
		std::map<string, IRVar*>* dicoRegTmp; // Table des symboles : On stockera ici nos registres virtuels
		//****
		std::map <string,IRVar*> variableMap; // Parametres
		//****
		BasicBlock* blocCourant;
		int taille;
		int taillePileParam;
		int nbBlocIF;
		int nbBlocELSE;
		int nbBlocAfter;


};
#endif //PLDCOMP_CFG_H