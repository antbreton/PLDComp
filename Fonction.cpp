#include "Fonction.h"
#include "Structure.h"
#include "General.h"
#include "Structure.h"
#include <iostream>


// Réalisation de Bloc --------
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


void Bloc::setRecursifBlocAncestorToAll(Bloc * ancetre)
{
	// On set l'ancetre de ce bloc
	this->ancetre=ancetre;
	
	// On set l'ancetre de ses fils
	// Pour cela on parcours la liste des fils et si on trouve un bloc on set l'ancetre
	for(int i=0; i<instrs->size(); i++)
	{
		if( Bloc * b = dynamic_cast<Bloc*>((*instrs)[i]) )
		{
			b->setRecursifBlocAncestorToAll(this);
		}
		
		else if( StructureControle * stru = dynamic_cast<BlocIf*>((*instrs)[i]) )
		{
			stru->setRecursifBlocAncestorToAll(this);
		}
	}
}
// ---------------------------


// Cette méthode retourne l'identifiable identifié par l'id en paramètre. Si elle ne trouve rien dans la table de symbole de ce bloc, elle regarde dans la table de son ancetre direct. 
Identifiable * Bloc::getIdentifiableIfExist(string id)
{
		// On regarde dans la table courante s'il existe
		if(tableSymboles->count(id) >0) 	// si l'id existe
		{
				return tableSymboles->at(id); // on retourne l'identifiable associé
		}
		else if(ancetre != NULL) 			// Sinon on regarde s'il y a un bloc père
		{
				return ancetre->getIdentifiableIfExist(id); // on regarde si le père connait l'identifiant
		}		
		
		// S'il n'y a pas de père (CAD => on est sur une racine) et que l'on a rien trouvé, on retourne NULL
		return NULL;
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




// Réalisation de fonction ----------
bool Fonction::testReturn() {	
	if(type!="VOID")
	{
		if( bloc != NULL)
		{
			return bloc->testReturn(false);	//recherche dans le bloc
		}
		return true; //pas de bloc, c'est une déclaration
	}
	else if( bloc != NULL)
	{
		return bloc->testReturn(true);	//recherche dans le bloc
	}
	return true; //pas de bloc, c'est une déclaration
	
}

// ------------------------------
