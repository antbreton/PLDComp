#include "BasicBlock.h"
using namespace std;


// Constructeur et Destructeur
BasicBlock::BasicBlock()
{
	
}

BasicBlock::BasicBlock(CFG* cfg, Bloc* bloc) 
{
	this->cfg = cfg;
	
	// TODO : POur chaque instruction dans le bloc : 
	// On regarde son type, et selon celui-ci
	// on recupere le code IR associee (on appelle le getIR de chaque classe) 
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
void BasicBlock::ajouterInstrIR(IRInstr *instruction) {
    listeInstructionsIR.push_back(instruction);
}


// GETTER / SETTER

/*CFG* BasicBlock::getCFG() {
    return cfg;
}*/