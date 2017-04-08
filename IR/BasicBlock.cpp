#include "BasicBlock.h"
#include "../Structure.h"
using namespace std;


// Constructeur et Destructeur
BasicBlock::BasicBlock(std::string label)
{
	
}
BasicBlock::BasicBlock(CFG* cfg)
{

	this->cfg = cfg;
	cfg->addBasicBlock(this);
	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

}
BasicBlock::BasicBlock(CFG* cfg, Bloc* bloc, string label)
{

	this->cfg = cfg;
	this-> label = label;
	if(label != "blocIF" && label != "blocELSE"){
		cout << "NI IF NI ELSE" << endl;
		//cfg->addBasicBlock(this);
	}
	cout << "CREATION BLOC : " << label << endl;

	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

	if(bloc != NULL)
	{
		listeInstructionsAST = bloc->getInstructions();
		cout << "BasicBlock::listeInstructionsAST->size() " << listeInstructionsAST->size() << endl;
	}
	
}

BasicBlock::~BasicBlock()
{

}



// Methodes

void BasicBlock::genererIR()
{
	vector<Instruction*>:: iterator ite;

	cout << "BB:genererIR()::listeInstructionsAST->size()" << listeInstructionsAST->size() << endl;
	for(ite = listeInstructionsAST->begin(); ite!=listeInstructionsAST->end(); ++ite)
	{
		cfg->setBlockCourant(this);
		cout << "------ FOR ----------  " << label << endl;
		
		if(Expression* e = dynamic_cast<Expression*>(*ite))
		{
			cout << "------ IF ----------" << endl;
			e->construireIR(cfg);
			cout << "------ FIN IF ----------" << endl;
		} else if (StructureControle* s = dynamic_cast<StructureControle*>(*ite))
		{
			cout << "INSTRUCTION STRUCTURE DE CONTROLE" << endl;
			s->construireIR(cfg,ite);
		} else if (Bloc* b = dynamic_cast<Bloc*>(*ite))
		{
			cout << "INSTRUCTION DE TYPE BLOC" << endl;
		}



		if(bbreak) {
			cout << "BREAK"<<  label << endl;
			break;
		}

		cout << "------ FIN FOR ----------" << endl;
	}	

	if(succCond != nullptr){
		succCond->genererIR();
		if(succIncond != nullptr){
			succIncond->genererIR();
		}
	} 
}


// Genere le code assembleur du bloc, pour cela on appelle chaque methode genererAssembleur
// de chaque Instruction IR.
string BasicBlock::genererAssembleur() {
    string codeAssembleur;
    
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

    if(succCond != nullptr)
    {
		codeAssembleur += succCond->genererAssembleur();	
	} 

	if (succIncond != nullptr){
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
	  return 0;
    }
}