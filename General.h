#ifndef _GENERAL_H
#define _GENERAL_H

#include <string> 
#include <vector>
#include <iostream>

 
using namespace std;

class Fonction;
class Val;


class Instruction {
	public:
		Instruction() {}
		virtual ~Instruction() {}
		void Afficher();
};

class InstructionV : public Instruction {
	public:
		InstructionV(){}
		virtual ~InstructionV() {}
};

/** Déclaration Class */
class Declaration : public Instruction
{
	public :
		Declaration(string type, Val * taille);
		virtual ~Declaration() {}
		void ajouterIdentifiant(string id) {identifiants->push_back(id);}
		void setIdentifiants(std::vector<string>* identifiants) { this->identifiants = identifiants;}
		void Affiche () {
			cout<<"DECLARATION"<<endl;;
			cout<<type<<endl;
			for(int i=0;i<identifiants->size();i++)
			{
				cout<<(*identifiants)[i]<<",";
			}
			cout<<endl;
		}
	private :
		string type;
		int taille;
		vector<string>* identifiants;
};

class Programme {
	public:
		Programme();
		virtual ~Programme() {}
		void Affiche () {
			// ici il faut appeler le affiche de chaque element de la futur dequeu
		}
	private :
		vector<Declaration*> *decls;
		vector<Fonction*> *fonctions;
};





#endif
