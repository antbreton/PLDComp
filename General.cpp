#include "General.h"
#include "Expression.h"
#include <iostream>


 
using namespace std;
// Réalisation Declaration
/*
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
	*/
	
	// Réalisation Programme
	
Programme::Programme()
{
	instructions = new vector<InstructionProgramme*>();
	tableSymboles = new map<string,Identifiable*>();
}


 	// Réalisation Variable
Variable::Variable(string id):Identifiable(id), initialisation (false)
{

}
Variable::Variable(string type, string id):Identifiable(id), type(type), initialisation (false)
{
cerr<< "type : "<<type<<" id : "<<id<<endl;;
}

Variable::Variable(string type, string id, Expression * expr):Identifiable(id), type(type), expr(expr),initialisation (true)
{
	
}
