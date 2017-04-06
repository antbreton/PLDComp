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

	//TODO : faut-il maj ailleur de bloc courant ?

	this->cfg = cfg;
	this-> label = label;

	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

	if(bloc != NULL)
	{
		listeInstructionsAST = bloc->getInstructions();
	}

	/* AVANT CREATION BRANCHE
	cfg->setBlockCourant(this); 
	if(bloc!=NULL)
	{

		vector<Instruction*>* listeIntruc = bloc->getInstructions();
		vector<Instruction*>:: iterator ite;


		for(ite = listeIntruc->begin(); ite!=listeIntruc->end(); ++ite)
		{
			cout << "------ FOR ----------" << endl;
			
			if(Expression* e = dynamic_cast<Expression*>(*ite))
			{
				cout << "------ IF ----------" << endl;
				e->construireIR(cfg);
			} else if (StructureControle* s = dynamic_cast<StructureControle*>(*ite))
			{
				cout << "INSTRUCTION STRUCTURE DE CONTROLE" << endl;
				s->construireIR(cfg);
			}
		}	
	}
	*/
	// TODO : POur chaque instruction dans le bloc : 
	// On regarde son type, et selon celui-ci
	// on recupere le code IR associee (on appelle le getIR de chaque classe) 	
}

BasicBlock::BasicBlock(CFG* cfg, Instruction* instr)
{
	cout << "BB::BB(CFG, Instruction)" << endl;



	cfg->setBlockCourant(this);
	this->cfg = cfg;	
	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

	if(Bloc* b = dynamic_cast<Bloc*>(instr))
	{
		cout << "instruction est un bloc" << endl;
		listeInstructionsAST = b->getInstructions();

	}

	//listeInstructionsAST->push_back(instr);

	/*
	if(Expression* e = dynamic_cast<Expression*>(instr))
	{
		e->construireIR(cfg);
	}
	*/
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
				if (succIncond != nullptr){
					cout << "succIncond non NULL" << endl;
					succIncond->genererIR();
				}
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
    
    vector<IRInstr *>::iterator ite = listeInstructionsIR->begin();

    while(ite != listeInstructionsIR->end()) {
      codeAssembleur += (*ite)->genererAssembleur();
      ite++;
    }

    if(succCond != nullptr){
		cout << "succCond assembleur" << endl;
		codeAssembleur += succCond->genererAssembleur();
		
		if (succIncond != nullptr){
			cout << "succIncond assembleur" << endl;
			codeAssembleur += succIncond->genererAssembleur();
		}
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