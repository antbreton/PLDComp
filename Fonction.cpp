#include "Fonction.h"
#include "General.h"
#include <iostream>

Bloc::Bloc() : Instruction()
{
	instrs = new vector <Instruction*>();
	tableSymboles = new map<string,Identifiable*>(); 
}



void Bloc::ajouterListeVariable(vector<Variable*>* listeVariable)
{
	 /* On ajoute la variable dans la table des symboles */	 
	 for(int i =0; i<listeVariable->size();i++)
	 {
	 		// On construit la pair avec la valeur courante du vecteur
	 		std::pair<string,Identifiable*> pairCourante((*listeVariable)[i]->getIdentifiant(), (*listeVariable)[i]);
	 		
	 		// On ajoute la pair courante 
	 		tableSymboles->insert(pairCourante); 
	 }
}

vector<Instruction*>* Bloc::getInstructions()
{
	return this->instrs;
}

void Bloc::AjouterInstr(Instruction* instr) 
{
	instrs->push_back(instr);
}

/*
int Bloc::compterNbVariable () 
{
	int nbVar = 0;

	
	//Parcours de la table des symboles pour recuperer les variables du bloc
	for(map<string,Identifiable*>::iterator it = tableSymboles->begin(); it != tableSymboles->end(); it++)
	{
		if(dynamic_cast<Variable*>(it->second))
		{
			nbVar++;
		}
	}

	//Parcours récursif des Blocs
	for(vector<Instruction*>::iterator it = instrs->begin(); it != instrs->end(); it++){
		if(Bloc* b = dynamic_cast<Bloc*>(*it))
		{ 
			nbVar += b->compterNbVariable();
		}
	}
	

	//nbVar = tableVariables->size();

	return nbVar;
}
*/
void Bloc::constructor_tableVariables(){
	//1: parcours de la table des symboles, on recupere les Identifiable de type Variable
	for(map<string,Identifiable*>::iterator it = tableSymboles->begin(); it != tableSymboles->end(); it++)
	{
		if(Variable* v = dynamic_cast<Variable*>(it->second))
		{
			std::pair<string, Variable*> pairAdded (v->getIdentifiant(), v);
			tableVariables->insert(pairAdded);
			
		}
	}


	//2: appel recursif
	for(vector<Instruction*>::iterator it = instrs->begin(); it != instrs->end(); it++){
		if(Bloc* b = dynamic_cast<Bloc*>(*it))
		{ 
			tableVariables->insert(b->tableVariables->begin(),b->tableVariables->end()); 
		}
	}
}

Bloc* Fonction::getBloc()
{
	return this->bloc;
}









