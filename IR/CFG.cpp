#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG()
{
	
}

CFG::~CFG()
{

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
