#include "General.h"
#include "Expression.h"
#include <iostream>


 
using namespace std;
// Réalisation Declaration
 Declaration::Declaration(string type, Val * taille ,Identifiant * id):Instruction(), type(type), id(id)
{
	//cerr<<"     TEST       "<<type<<id;
	//id->Afficher();
	this->taille = -1;
	identifiants = new vector<Identifiant*>();
	if(taille != NULL)
		this->taille = taille->valeur;
	identifiants->push_back(id);
}		
	
	
	// Réalisation Programme
	
Programme::Programme()
{
	instructions = new vector<InstructionProgramme*>();
}
