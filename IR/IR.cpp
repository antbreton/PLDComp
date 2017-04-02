#include "IR.h"
using namespace std;


// Constructeur et Destructeur
IR::IR(Programme* programme)
{
	vector<Fonction*>::iterator fonction;
	
	// En supposant un getFonctions dans programme
	
	// Pour chaque fonction dans le programme (donc chaque AST), on cree son CFG.
	for(fonction = programme->getFonctions().begin() ; fonction != programme->getFonctions().end() ; fonction++)
	{
		CFG* newCFG = new CFG(fonction);
		this->addCFG(newCFG);
	}
}

IR::~IR()
{
	list<CFG*>::iterator ite;
	for(ite = listeCFG.begin(); ite!=listeCFG.end(); ++ite)
	{
	   delete *ite;
	}
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
