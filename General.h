#ifndef _GENERAL_H
#define _GENERAL_H

//#include "Fonction.h"
#include <string> 
#include <vector>
#include <iostream>

 
using namespace std;

class Fonction;

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

class Declaration : public Instruction
{
	public :
		Declaration(string type):Instruction(), type(type){ identifiants = new vector<string>();}
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
		vector<string>* identifiants;
};

class Programme {
	public:
		Programme() { decls = new vector<Declaration>(); fonctions = new vector<Fonction> ();}
		virtual ~Programme() { delete(decls); delete(fonctions);}
		void Affiche () {
			printf("PROGRAMME");
			// ici il faut appeler le affiche de chaque element de la futur dequeu
		}
	private :
		vector<Declaration> *decls;
		vector<Fonction> *fonctions;
};





#endif
