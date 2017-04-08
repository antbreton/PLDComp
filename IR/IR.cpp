#include "IR.h"
using namespace std;


// Constructeur et Destructeur
IR::IR(Programme* programme)
{
	vector<Fonction*>::iterator fonction;
	
	// Pour chaque fonction dans le programme (donc chaque AST), on cree son CFG.
	// et on l'ajoute a la liste.
	vector<Fonction*> listeDeFonctions = programme->getFonctions();
	
	// On recupere le nom de la toute premiere fonction
	premiereFctNom = listeDeFonctions[0]->getIdentifiant();
	
	for(fonction = listeDeFonctions.begin() ; fonction != listeDeFonctions.end() ; ++fonction)
	{
		CFG* newCFG = new CFG(*fonction);
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

void IR::genererIR(){
	cout << "IR::genererIR" << endl;

	list<CFG*>::iterator ite;
	for(ite=listeCFG.begin();ite!=listeCFG.end();ite++)
	{
	  (*ite)->genererIR();
	}	
}
// Parcours les CFGs du programme et en genere le code assembleur.
string IR::genererAssembleur() 
{
		string codeAssembleur;
		
		// Code assembleur de début de fichier
		codeAssembleur += ".text        \r\n";
		codeAssembleur += ".globl "+premiereFctNom+" \r\n";
		codeAssembleur += ".type "+premiereFctNom+", @function\r\n";
		codeAssembleur += "\r\n";
		
		// On itere pour chaque CFG
		list<CFG*>::iterator ite;
		for(ite=listeCFG.begin();ite!=listeCFG.end();ite++)
		{
		  codeAssembleur += (*ite)->genererAssembleur();
		}
		
		// Ecriture dans main.s
		ofstream fichier("main.s", ios::out | ios::trunc);	
		if(fichier)
        {
			fichier << codeAssembleur << endl;
			fichier.close();
        }
		
		return codeAssembleur;	
}

// Ajoute un CFG à la liste des CFGs
void IR::addCFG(CFG* cfg) 
{
	this->listeCFG.push_back(cfg);
}



// GETTER / SETTER
