#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	
	this->dicoRegTmp = new map<string, IRVar*>();
	
	Bloc* bloc = fonctionDuCFG->getBloc();

	BasicBlock* newBasicBlock = new BasicBlock(this, bloc, fonctionDuCFG->getIdentifiant());

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
  		cout << "CFG:genererAssembleur" << endl;
		codeAssembleur += (*ite)->genererAssembleur();
		ite++;
  	}
	
	// EPILOGUE
	codeAssembleur += gen_epilogue();

	return codeAssembleur;
}


void CFG::genererIR()
{

	cout<< "CFG::genererIR" << endl;
	list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;

  	while (ite != listeBasicBlocks.end()) 
  	{
  		blocCourant = (*ite);
		(*ite)->genererIR();
		/*
		cout << "POINTEUR CFG " << *ite << endl;
		if((*ite) != blocCourant)
		{
			cout << endl << "BLOC COURANT MODIFIE" << endl << endl;
			blocCourant->genererIR();
		}
		*/
		ite++;
  	}
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
	

	cout << endl << "GEN_PROLOGUE" << endl;

	std::map<string, IRVar*>* dico = this->getDicoRegTmp();
	std::map<string, IRVar*>::iterator it;
	
	int j = 1;
	if(dico->size() != 0){

		codeAssembleur += "    subq    $"+ to_string(8*dico->size()) +", %rsp \r\n";

	

		for(it=dico->begin(); it!=dico->end(); ++it)
		{
			it->second->setOffset(8*j);
			j++;
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
	fonctionDuCFG->getBloc()->constructor_tableVariables(); //8 octets par variable
	int taille = 8*fonctionDuCFG->getBloc()->tableVariables->size();
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
		std::string nomRegistreVirtuel = "!r" + to_string(nbRegVirt) ;
        IRVar* maVar = new IRVar(nomRegistreVirtuel);
        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));
        return nomRegistreVirtuel;
}




// GETTER / SETTER

int CFG::getNbRegVirtuels()
{
	return nbRegVirtuels;
}
