#include "IR.h"
using namespace std;


// Constructeur et Destructeur
IR::IR(Programme* programme)
{
	
}

IR::~IR()
{

}



// Methodes


// Parcours les CFGs du programme et en genere le code assembleur.
string IR::genererAssembleur() 
{
		string codeAssembleur;
	  
		// TODO : Peut etre un code special au debut d'un fichier assembleur .. 
	  
		list<CFG*>::iterator ite;
		for(ite=listeCFG.begin();ite!=listeCFG.end();ite++)
		{
		  codeAssembleur += (*ite)->genererAssembleur(); 
		}
	  
		return codeAssembleur;	
}

// Ajoute un CFG à la liste des CFGs
void IR::addCFG(CFG* cfg) 
{
	this->listeCFG.push_back(cfg);
}



// GETTER / SETTER
