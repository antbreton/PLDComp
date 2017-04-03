#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	
	// On cree le basicBlock correspondants au bloc de la fonction
	// et on l'ajoute au CFG
	BasicBlock* newBasicBlock = new BasicBlock(this, fonctionDuCFG->getBloc());
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
	  codeAssembleur += " TODO name:\r\n";
	  codeAssembleur += "\r\n";
	  codeAssembleur += "    pushq   %rbp \r\n";
	  codeAssembleur += "    movq    %rsp, %rbp \r\n";
	  // addq ou subq ? Depend de la pile ? 
	  //codeAssembleur += "    subq    $"+ (TaillePile + multiple de 16) +", %rsp \r\n";
	  codeAssembleur += "\r\n";
	  
	  //Offset pour chaque variable
	  int i = 1;
	  for(map<string, IRVar*>::iterator it = dicoRegTmp->begin(); it != dicoRegTmp->end(); it++)
	  {
	 		it->second->setOffset(8*i);
	 		
	 		string instructionASM = "movq $" + to_string(it->second->getValeur()) + ", -" + to_string(it->second->getOffset())  +"(%rbp)\r\n";
	 		codeAssembleur = instructionASM;
	 		i++;
	  }


	  // CORPS
	  // Pour chaque basicBlock dans le CFG on genere son code assembleur.
	  list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;
	  while (ite != listeBasicBlocks.end()) 
	  {
			codeAssembleur += (*ite)->genererAssembleur();
			ite++;
	  }
	  
	  // EPILOGUE
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

int CFG::getNbRegVirtuels(){
	return nbRegVirtuels;
}
