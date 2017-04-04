#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	
	this->dicoRegTmp = new map<string, IRVar*>();
	
	Bloc* bloc = fonctionDuCFG->getBloc();

	BasicBlock* newBasicBlock = new BasicBlock(this, bloc, fonctionDuCFG->getIdentifiant()+"_bb");

	this->addBasicBlock(newBasicBlock);
	
	nbRegVirtuels = 0;
	calculeTaille();
}

CFG::~CFG()
{
    list<BasicBlock*>::iterator ite;
    for(ite = listeBasicBlocks.begin(); ite!=listeBasicBlocks.end(); ++ite)
    {
        delete *ite;
	}
}



// Methodes

// Ajoute un BasicBlock au CFG
void CFG::addBasicBlock(BasicBlock* newBasicBlock)
{
	this->listeBasicBlocks.push_back(newBasicBlock);
}

// Parcours le CFG et en genere le code assembleur.
string CFG::genererAssembleur() {
		
	string codeAssembleur;

	// PROLOGUE
	codeAssembleur += gen_prologue();


	// CORPS
	// Pour chaque basicBlock dans le CFG on genere son code assembleur.
  	list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;

  	while (ite != listeBasicBlocks.end()) 
  	{
		codeAssembleur += (*ite)->genererAssembleur();
		ite++;
  	}
	
	// EPILOGUE
	codeAssembleur += gen_epilogue();

	return codeAssembleur;
}

std::string CFG::gen_prologue()
{
	string codeAssembleur;
	
	string label = listeBasicBlocks.front()->getLabel();
	string insLabel = label + ":\r\n";

	codeAssembleur += insLabel;
	codeAssembleur += "\r\n";
	codeAssembleur += "    pushq   %rbp \r\n";
	codeAssembleur += "    movq    %rsp, %rbp \r\n";  
	
	//Offset pour chaque variable
	/*
	int i = 1;
	std::map<string, IRVar*>* dico = this->getDicoRegTmp();
	std::map<string, IRVar*>::iterator it;
	
	// Si il y a au moins une instruction dans le programme
	if(dico != NULL)
	{

		for(it=dico->begin(); it!=dico->end(); ++it)
		{
			it->second->setOffset(8*i);
			string instructionASM = "movq $" + to_string(it->second->getValeur()) + ", -" + to_string(it->second->getOffset())  +"(%rbp)\r\n";
			codeAssembleur += instructionASM;
			i++;
		}
	}

	*/
	cout << endl << "GEN_PROLOGUE" << endl;
	int i = 1;
	if(taille != 0)
	{
		codeAssembleur += "    subq    $"+ to_string(taille) +", %rsp \r\n";

		std::map<string, Variable*>* table = fonctionDuCFG->getBloc()->tableVariables;
		cout << "apres getbloc" << endl;
		std::map<string, Variable*>::iterator it;
		for(it= table->begin(); it != table->end(); it++)
		{
			cout << "dans for" << endl;
			string key = it->first;
			cout << key << endl;
			dicoRegTmp->find(key)->second->setOffset(8*i);
			cout << "apres setoffset" << endl;
			if(dicoRegTmp->find(key)->first==""){cout << "lol" << endl;}
			cout << "apres setoffset" << endl;
			if(dicoRegTmp->find(key)->second==NULL){cout << "lol" << endl;}
		cout << to_string(dicoRegTmp->find(key)->second->getOffset()) << endl;
			cout << "test passe" << endl;
			string instructionASM = "movq $" + to_string(dicoRegTmp->find(key)->second->getValeur()) + ", -" + to_string(dicoRegTmp->find(key)->second->getOffset())  +"(%rbp)\r\n";
			cout << "apres instrASM" << endl;
			codeAssembleur += instructionASM;
			i++;
		}
	}


	return codeAssembleur;
}

std::string CFG::gen_epilogue()
{
	string codeAssembleur;

	  codeAssembleur += "\r\n";
	  codeAssembleur += "    leave\r\n";
	  codeAssembleur += "    ret\r\n";
	  codeAssembleur += "\r\n";

	 return codeAssembleur;
}


int CFG::calculeTaille()
{
	cout << endl << "calculeTaille debut" << endl;
	fonctionDuCFG->getBloc()->constructor_tableVariables(); //8 octets par variable
	int taille = 8*fonctionDuCFG->getBloc()->tableVariables->size();
	cout << endl << "calculeTaille fin" << endl;
	setTaille(taille);
	return taille;
}

std::string CFG::creerNouveauRegistre() {
        string nomRegistreVirtuel = "!r" + to_string(this->nbRegVirtuels) ;
        this->nbRegVirtuels++;

        IRVar* maVar = new IRVar(nomRegistreVirtuel);

        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));

        return nomRegistreVirtuel;
}

std::string CFG::creerNouveauRegistre(int nbRegVirt) {
		std::string nomRegistreVirtuel = "!r" + nbRegVirt ;
        IRVar* maVar = new IRVar(nomRegistreVirtuel);
        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));
        return nomRegistreVirtuel;
}




// GETTER / SETTER

int CFG::getNbRegVirtuels()
{
	return nbRegVirtuels;
}
