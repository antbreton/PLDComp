#include "BasicBlock.h"
using namespace std;


// Constructeur et Destructeur
BasicBlock::BasicBlock(std::string label)
{
	
}

BasicBlock::BasicBlock(CFG* cfg, Bloc* bloc, string label)
{
	cfg->setBlockCourant(this);
	this->cfg = cfg;
	this-> label = label;

	listeInstructionsIR = new vector<IRInstr*>();

	if(bloc!=NULL)
	 {

		vector<Instruction*>* listeIntruc = bloc->getInstructions();
		vector<Instruction*>:: iterator ite;
		 
		for(ite = listeIntruc->begin(); ite!=listeIntruc->end(); ++ite)
		{
			
			if(Expression* e = dynamic_cast<Expression*>(*ite))
			{
				e->construireIR(cfg);
			}
		
		}
	
	}
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
    
    vector<IRInstr *>::iterator ite = listeInstructionsIR->begin();

    while(ite != listeInstructionsIR->end()) {
      codeAssembleur += (*ite)->genererAssembleur();
      ite++;
    }
  
    return codeAssembleur;
}


// Ajoute une instruction IR à la liste du bloc
void BasicBlock::ajouterInstrIR(IRInstr *instruction) {
	listeInstructionsIR->push_back(instruction);
}


// GETTER / SETTER

CFG* BasicBlock::getCFG() {
    return cfg;
}


bool BasicBlock::estVarMappee(std::string nomVariable) {
    if(this->mappingVarReg.count(nomVariable) == 0) {
        return false;
    }
    return true;
}

void BasicBlock::ajouterVariableMappee(CFG* cfg, std::string nomVariable) {
    int numeroRegistreVirtuel = cfg->getNbRegVirtuels();
    this->mappingVarReg.insert(std::pair<std::string, int>(nomVariable, numeroRegistreVirtuel));
    cfg->creerNouveauRegistre();

}

int BasicBlock::getValeurMappee(std::string nomVariable) {
    auto trouve = this->mappingVarReg.find(nomVariable);
    if(trouve != this->mappingVarReg.end()) {
      return trouve->second;
    } else {
      cerr << "BasicBlock::GetValeurMappee : mappingDe " + nomVariable + " non trouve" << endl; 
    }
}