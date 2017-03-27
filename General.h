#ifndef _GENERAL_H
#define _GENERAL_H

#include <string> 
#include <vector>
 
using namespace std;

class Fonction;
class Val;


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

/** Déclaration Class */
class Declaration : public Instruction
{
	public :
		Declaration(string type, Val * taille);
		virtual ~Declaration() {}
		void ajouterIdentifiant(string id) {identifiants->push_back(id);}
		void setIdentifiants(std::vector<string>* identifiants) { this->identifiants = identifiants;}
	private :
		string type;
		int taille;
		vector<string>* identifiants;
};

class Programme {
	public:
		Programme();
		virtual ~Programme() {}
	private :
		vector<Declaration*> *decls;
		vector<Fonction*> *fonctions;
};





#endif
