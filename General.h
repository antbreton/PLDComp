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
		virtual void Afficher(){}
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
		virtual void Afficher(){} //	""
};

/** Déclaration Class */
class Declaration : public Instruction, public InstructionProgramme
{
	public :
		Declaration(string type, Val * taille);
		virtual ~Declaration() {}
		void ajouterIdentifiant(string id) {identifiants->push_back(id);}
		void addAllIdentifiants(std::vector<string>* identifiants) { this->identifiants->insert(this->identifiants->end(), identifiants->begin(), identifiants->end());}
		void Afficher () {
			cerr<<"DECLARATION"<<endl;;
			cerr<<type<<endl;
			for(int i=0;i<identifiants->size();i++)
			{
				cerr<<(*identifiants)[i]<<",";
			}
			cerr<<endl;
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
		void Afficher () {
			cerr<<"PROGRAMME"<<endl<<"	";
			for(int i=0;i<instructions->size();i++)
			{
				(*instructions)[i]->Afficher();
			}
		}
	private :
		vector<InstructionProgramme*> *instructions;
};





#endif
