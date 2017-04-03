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

Bloc* Fonction::getBloc()
{
	return this->bloc;
}
