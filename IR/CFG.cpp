#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	
	// On cree le basicBlock correspondants au bloc de la fonction
	// Pour cela on recupere le bloc de la fonction avec un getBloc (pas encore existant)
	/*
	BasicBlock* newBasicBlock = new BasicBlock(this, fonction->getBloc());
	this->addBasicBlock(newBasicBlock);
	*/
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



// GETTER / SETTER
