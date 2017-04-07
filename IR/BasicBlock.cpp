#include "BasicBlock.h"
#include "../Structure.h"
using namespace std;


// Constructeur et Destructeur
BasicBlock::BasicBlock(std::string label)
{
	
}


BasicBlock::BasicBlock(CFG* cfg)
{
	cfg->setBlockCourant(this);
	this->cfg = cfg;

	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();
}


BasicBlock::BasicBlock(CFG* cfg, Bloc* bloc, string label)
{

	this->cfg = cfg;
	this-> label = label;

	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

	if(bloc != NULL)
	{
		listeInstructionsAST = bloc->getInstructions();
	}
}


BasicBlock::~BasicBlock()
{

}


// Methodes


void BasicBlock::genererIR()
{
	vector<Instruction*>:: iterator ite;


	for(ite = listeInstructionsAST->begin(); ite!=listeInstructionsAST->end(); ++ite)
	{
		cfg->setBlockCourant(this);
		cout << "------ FOR ----------" << endl;
		
		if(Expression* e = dynamic_cast<Expression*>(*ite))
		{
			cout << "------ IF ----------" << endl;
			e->construireIR(cfg);
		} else if (StructureControle* s = dynamic_cast<StructureControle*>(*ite))
		{
			cout << "INSTRUCTION STRUCTURE DE CONTROLE" << endl;
			s->construireIR(cfg);

			if(succCond != nullptr){
				cout << "succCond non NULL" << endl;
				succCond->genererIR();
			}

			if (succIncond != nullptr){
					cout << "succIncond non NULL" << endl;
					succIncond->genererIR();
			}


		} else if (Bloc* b = dynamic_cast<Bloc*>(*ite))
		{
			cout << "INSTRUCTION DE TYPE BLOC" << endl;
		}
	}	 
}

// Genere le code assembleur du bloc, pour cela on appelle chaque methode genererAssembleur
// de chaque Instruction IR.
string BasicBlock::genererAssembleur() {
    string codeAssembleur;

    //cfg->setBlockCourant(this);

    
    vector<IRInstr *>::iterator ite = listeInstructionsIR->begin();

	if (label.compare("main")) // TODO etendre a toute fonciton
    {
		codeAssembleur = label + ":\r\n";
	}

    while(ite != listeInstructionsIR->end()) {
      codeAssembleur += (*ite)->genererAssembleur();
      ite++;
    }
    if (jumpIRIntr != NULL)
    {
		codeAssembleur += jumpIRIntr->genererAssembleur();
	}

    //if(succCond != nullptr && label != "blocIF"){
    if(succCond != nullptr)
    {
		cout << "succCond assembleur" << endl;
		codeAssembleur += succCond->genererAssembleur();	
	} 

	if (succIncond != nullptr){
		cout << "succIncond assembleur" << endl;
		codeAssembleur += succIncond->genererAssembleur();
	}
  
    return codeAssembleur;
}


// Ajoute une instruction IR à la liste du bloc
void BasicBlock::ajouterInstrIR(IRInstr *instruction) {
	listeInstructionsIR->push_back(instruction);
}

void BasicBlock::ajouterInstrIRJump(IRInstr *instruction) {
	jumpIRIntr = instruction;
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
