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
		BasicBlock(CFG* cfg);
		~BasicBlock();
		
		std::string genererAssembleur();
		void ajouterInstrIR(IRInstr* instruction);
		void ajouterInstrIRJump(IRInstr* instruction);

		
		CFG* getCFG();
		std::string getLabel() {return label;};
		void setLabel(std::string label) {label = label;};
		bool estVarMappee(std::string nomVariable);
		void ajouterVariableMappee(CFG* cfg, std::string nomVariable);
		int getValeurMappee(std::string nomVariable);
		int nbVariables;

		BasicBlock* getSuccCond() {return succCond;};
		BasicBlock* getSuccIncond() {return succIncond;};
		void setSuccCond(BasicBlock* bb) {succCond = bb;};
		void setSuccIncond(BasicBlock* bb) {succIncond = bb;};

		std::vector<Instruction * >* getListeInstructionsAST() {return listeInstructionsAST; };
		void setListeInstructionAST(vector<Instruction*>* v) {listeInstructionsAST = v; };
		void genererIR();

		bool bbreak = false;
		map<std::string,int> getMapVarReg() {return mappingVarReg;};
		void setMapVarReg(map<std::string,int> mymap) {mappingVarReg = mymap;};

	private:
		std::vector<IRInstr * >* listeInstructionsIR;
		IRInstr* jumpIRIntr;
		std::vector<Instruction*>* listeInstructionsAST;
		BasicBlock* succCond; // Son successeur conditionnel
		BasicBlock* succIncond; // Son sucesseur inconditionnel
		map<std::string,int> mappingVarReg;
		CFG* cfg;
		std::string label;
};



#endif // PLDCOMP_BASICBLOCK_H