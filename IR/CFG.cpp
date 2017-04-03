#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	
	// On parcours la fonction pour recuperer tous les parametres des instructions
	// et on cree les variable IR correspondantes.
	//vector<string> listeParametres = fonctionDuCFG->getVariables();
	/*
	vector<string>::iterator ite;
    for(ite = listeParametres.begin(); ite!=listeParametres.end(); ++ite)
    {
       
	}
	*/
	
	// On cree le basicBlock correspondants au bloc de la fonction
	// et on l'ajoute au CFG
	BasicBlock* newBasicBlock = new BasicBlock(this, fonctionDuCFG->getBloc(), fonctionDuCFG->getIdentifiant()+"_bb");
	this->addBasicBlock(newBasicBlock);
	nbRegVirtuels = 0;
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
		
	// TODO : Chopper la taille de la pile (et l'avoir calculer avant ...)
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
	  // addq ou subq ? Depend de la pile ? 
	  //codeAssembleur += "    subq    $"+ (TaillePile + multiple de 16) +", %rsp \r\n";
	codeAssembleur += "\r\n";
	  
	
	//Offset pour chaque variable
	int i = 1;
	std::map<string, IRVar*>* dico = getDicoRegTmp();
	for(map<string, IRVar*>::iterator it = dico->begin(); it != dico->end(); it++)
	{
 		it->second->setOffset(8*i);
 		
 		string instructionASM = "movq $" + to_string(it->second->getValeur()) + ", -" + to_string(it->second->getOffset())  +"(%rbp)\r\n";
 		codeAssembleur += instructionASM;
 		i++;
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
	
	int taille = 8*getNbRegVirtuels(); //8 octets par variable

	return taille;
}

std::string CFG::creerNouveauRegistre() {
        std::string nomRegistreVirtuel = "!r" + this->nbRegVirtuels ;
        this->nbRegVirtuels++;
        IRVar* maVar = new IRVar(nomRegistreVirtuel);
        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));
}




// GETTER / SETTER

int CFG::getNbRegVirtuels()
{
	return nbRegVirtuels;
}
