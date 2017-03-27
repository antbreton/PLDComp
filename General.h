#ifndef _GENERAL_H
#define _GENERAL_H

#include "Fonction.h"
#include <string> 
#include <vector>
 
using namespace std;


class Instruction {
	public:
		Instruction() {}
		virtual ~Instruction() {}

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
	private :
		string type;
		vector<string>* identifiants;
};

class Programme {
	public:
		Programme() { decls = new vector<Declaration>(); fonctions = new vector<Fonction> ();}
		virtual ~Programme() { delete(decls); delete(fonctions);}
	private :
		vector<Declaration> *decls;
		vector<Fonction> *fonctions;
};





#endif
