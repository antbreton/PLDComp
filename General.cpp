#include "General.h"
#include "Expression.h"

// Réalisation Declaration
 Declaration::Declaration(string type, Val * taille):Instruction(), type(type)
{
	this->taille = -1;
	identifiants = new vector<string>();
	if(taille != NULL)
		this->taille = taille->valeur;
}		
	
	
	// Réalisation Programme
	
Programme::Programme()
{
	decls = new vector<Declaration*>();
	fonctions = new vector<Fonction*> ();
}
