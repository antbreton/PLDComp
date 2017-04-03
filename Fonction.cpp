#include "Fonction.h"
#include "Structure.h"
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

bool Bloc::testReturn(bool nullable){
	bool returnFind=false;
	for(int i=0; i<instrs->size();i++)
	{ //parcours les instructions de premier niveau
		if (Bloc* bloc = dynamic_cast<Bloc*>((*instrs)[i])) 
		{
			//cout<<"BLOC RECURSIF"<<endl;
			returnFind = bloc->testReturn(nullable);
		}
		else if(StructureControle* struc = dynamic_cast<StructureControle*>((*instrs)[i])) //on trouve une structure de controle;
		{
			//cout<<"STRUCTURE DE CONTROLE"<<endl;
			returnFind = struc->testReturn(nullable);
		}
		else if(RetourExpr* expr = dynamic_cast<RetourExpr*>((*instrs)[i])) //cherche un return
		{
			if(nullable)//y'a un return qui doit etre null
			{
				if( expr->expr == NULL)
					returnFind = true; 
				else
					returnFind = false;
			}
			else
			{
				if( expr->expr == NULL)
					returnFind = false; 
				else
					returnFind = true;
				
			}
			//cout<<"RETURN DU BLOC"<<endl;
		}
		else if (nullable) // il n'y a pas de return;
		{
			returnFind = true;
		}
	}
	if(instrs->size()==0 && nullable)
	{
		returnFind = true;
	}
	//cout<<"FIND :"<<returnFind<<endl;
	return returnFind;
}
