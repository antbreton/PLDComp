#ifndef PLDCOMP_IR_IR_H
#define PLDCOMP_IR_IR_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "CFG.h"


/*
	Classe la plus generale dans le traitement backend , elle recupere la liste des fonctions de programme, ainsi que sa liste de symbole,
	a partir de la elle va creer un CFG pour chaque fonction et l'ajouter a sa liste. Enfin elle va parcourir sa liste de CFG et lancer la generation 
	du code assembleur pour chaque CFG, ce qui evidemment creera le code assembleur du programme. 
*/
class IR {
	public:
		IR(Programme* programme);
		~IR();
		
		std::string genererAssembleur();
		void addCFG(CFG* cfg);
		ofstream fichier;
		
	private:
		list<CFG *> listeCFG;
		string premiereFctNom;

};



#endif //PLDCOMP_IR_IR_H