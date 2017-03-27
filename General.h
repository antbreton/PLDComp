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

class InstructionProgramme // Cette classe est dérivée par decls et fonction
{
	public :
		InstructionProgramme() {}
		bool compiler(); // TODO devront être virtuelles pure
		void afficher(); //	""
};

/** Déclaration Class */
class Declaration : public Instruction, public InstructionProgramme
{
	public :
		Declaration(string type, Val * taille);
		virtual ~Declaration() {}
		void ajouterIdentifiant(string id) {identifiants->push_back(id);}
		void addAllIdentifiants(std::vector<string>* identifiants) { this->identifiants->insert(this->identifiants->end(), identifiants->begin(), identifiants->end());}
		void affiche () {
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
		void ajouterInstruction(InstructionProgramme* instr) {instructions->push_back(instr);}
		void affiche () {
			// ici il faut appeler le affiche de chaque element de la futur dequeu
		}
	private :
		vector<InstructionProgramme*> *instructions;
};





#endif
