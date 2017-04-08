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


BasicBlock::BasicBlock(CFG* cfg, Bloc* blocAdd, string label)
{

	cout << "BasicBlock constructeur" << endl;
	cfg->setBlockCourant(this);
	this->bloc= blocAdd;
	this->cfg = cfg;
	this-> label = label;
	estDernierBlocIf = false;
	
	listeInstructionsIR = new vector<IRInstr*>();
	listeInstructionsAST = new vector<Instruction*>();

	if(bloc != NULL)
	{
		listeInstructionsAST = bloc->getInstructions();
	}
	else {
		estVide=true;
	}
			
}


BasicBlock::~BasicBlock()
{

}


// Methodes


void BasicBlock::genererIR()
{
	cout << "BasicBlock genererIR" << endl;
	vector<Instruction*>:: iterator ite;


	for(ite = listeInstructionsAST->begin(); ite!=listeInstructionsAST->end(); ++ite)
	{
		cfg->setBlockCourant(this);
		cout << "------ FOR ----------" << endl;
		
		if(Expression* e = dynamic_cast<Expression*>(*ite))
		{
			cout << "------ IF ----------" << endl;
			e->construireIR(cfg);
		} 
		else if (StructureControle* s = dynamic_cast<StructureControle*>(*ite))
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

		}
		else if (Bloc* b = dynamic_cast<Bloc*>(*ite))
		{
			cout << "INSTRUCTION DE TYPE BLOC" << endl;
		}
	}	 
}


// Genere le code assembleur du bloc, pour cela on appelle chaque methode genererAssembleur
// de chaque Instruction IR.
string BasicBlock::genererAssembleur() {
	
    string codeAssembleur;
	cout << "BasicBlock genererAssembleur" << endl;
  
    vector<IRInstr *>::iterator ite = listeInstructionsIR->begin();

	if (label.compare("main")) // TODO etendre a toute fonciton
    {
		codeAssembleur = label + ":\r\n";
	}
	
	
    while(ite != listeInstructionsIR->end()) {
      codeAssembleur += (*ite)->genererAssembleur();
      ite++;
    }
	
	// On Gere les sauts
    
    if(succIncond != NULL) {
		
		  if(succCond != NULL && jumpInstr != "") 
		  {
			int varOffset = this->getCFG()->getVariableReg(jumpInstr)->getOffset();
			string offsetDestEgal = "-"+to_string(varOffset)+"(%rbp)";
			
			codeAssembleur += "    cmpq    $1, "+offsetDestEgal+" \r\n";
			codeAssembleur += "    je      "+succCond->getLabel()+" \r\n"; // Jump si egal : then
			codeAssembleur += "    jmp     "+succIncond->getLabel()+" \r\n"; // Jump classique : else
			
		  } 
		  else 
		  {
			codeAssembleur += "    jmp     "+succIncond->getLabel()+" \r\n";
		  }
		  codeAssembleur += " \r\n";
	}
	
	
	// ON genere les deux successeurs.
	//****************************************************************

    if(succCond != NULL)
    {
		codeAssembleur += succCond->genererAssembleur();	
	} 
	
	// Bloc ELSE
	if (succIncond != NULL){
		
		if(!this->getSuccIncond()->getEstVide())
		{
			codeAssembleur += succIncond->genererAssembleur();
		}
		else // Si il est vide
		{
			if(this->getEstDernierBlocIf()) // et que c'est le dernier bloc on genere le bloc After
			{
				codeAssembleur += succIncond->genererAssembleur();
			}
		}

	}
	
	//****************************************************************
	

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
	cout << "BasicBlock : estVarMappee " << endl;

    if(this->mappingVarReg.count(nomVariable) == 0) {
        return false;
    }

	cout << "BasicBlock : estVarMappee 2" << endl;
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
