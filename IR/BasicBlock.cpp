#include "BasicBlock.h"
using namespace std;


// Constructeur et Destructeur
BasicBlock::BasicBlock()
{
	
}

BasicBlock::BasicBlock(CFG* cfg, Bloc* bloc, string label) 
{
	this->cfg = cfg;
	this-> label = label;
	
	// TODO : POur chaque instruction dans le bloc : 
	// On regarde son type, et selon celui-ci
	// on recupere le code IR associee (on appelle le getIR de chaque classe)
	
	// On recupere la liste des instructions du bloc
	vector<Instruction*>* listeInstructions = bloc->getInstructions();
	
	// Pour chaque instruction, on regarde son type et selon celui-ci on appelle construireIR ou pas. 
	vector<Instruction*>* iterator:: ite = listeInstructions.begin() ;
	while (ite != listeInstructions.end()) 
	  {
			if (dynamic_cast<OperateurOR *>(*ite)) {
			
			// On cast
			OperateurOR *Ope = (OperateurOR *)*ite;
			
			
		  } else if (dynamic_cast<OperateurAND *>(*ite)) {
			
			
			
		  } else if (dynamic_cast<OperateurSup *>(*ite)) {
			
			
			
		  } else if (dynamic_cast<OperateurInf *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurSupEgal *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurInfEgal *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurEgal *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurDifferent *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurPlus *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurMoins *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurMultiplier *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurModulo *>(*ite)) {
			
			
			
		  }else if (dynamic_cast<OperateurDivise *>(*ite)) {
			
			
			
		  } else if (dynamic_cast<AppelFonction *>(*ite)) {
			
			AppelFonction *appel = (AppelFonction *)*ite;
			appel->contruireIR();
			
			
		  }else if (dynamic_cast<Affectation *>(*ite)) {
			
			
		  }
	  }
	
}

BasicBlock::~BasicBlock()
{

}



// Methodes

// Genere le code assembleur du bloc, pour cela on appelle chaque methode genererAssembleur
// de chaque Instruction IR.
string BasicBlock::genererAssembleur() {
    string codeAssembleur;
    
    vector<IRInstr *>::iterator ite = listeInstructionsIR.begin();
    while(ite != listeInstructionsIR.end()) {
      codeAssembleur += (*ite)->genererAssembleur();
      ite++;
    }
  
    return codeAssembleur;
}


// Ajoute une instruction IR à la liste du bloc
void BasicBlock::addInstrIR(IRInstr *instruction) {
    listeInstructionsIR.push_back(instruction);
}


// GETTER / SETTER

CFG* BasicBlock::getCFG() {
    return cfg;
}