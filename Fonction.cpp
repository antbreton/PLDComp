#include "Fonction.h"
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
