#ifndef _FONCTION_H
#define _FONCTION_H

#include "General.h"
#include <string> 
#include <list>
#include <vector>
#include <iostream>


 
using namespace std;
 
class Variable;


class Bloc : public Instruction  {
	public:
		Bloc();
		virtual ~Bloc() {}
		void AjouterInstr (Instruction* instr) {instrs->push_back(instr);};
		vector<Instruction*>* instrs;
		void Afficher () {
			cerr<<"BEGIN_BLOC - nb instr : "<<instrs->size()<< " - tableSymb size : "<< tableSymboles->size() <<endl;
			for(int i=0;i<instrs->size();i++)
			{
				(*instrs)[i]->Afficher();
			}
			cerr<<"END_BLOC"<<endl;
		}
				void ajouterListeVariable(vector<Variable*>* listeVariable);
	private :
		map<string,Identifiable*>* tableSymboles;
};

class ParamDeclar {
	public:
		ParamDeclar(vector<Variable*>* params): params(params) {}
		vector<Variable*>* params;
};


/*
>>>>>>> Nico5
class Prototype {
	public:
		Prototype(string* type, vector<*>* params, Identifiant* identifiant) : type(type), params(params), identifiant(identifiant) {}
		string* type;
		vector<*>* params;
		Identifiant* identifiant;
		void Afficher() {
			cerr<<"PROTOTYPE"<<endl<<"	";
			cerr<<*type<<" ";
			identifiant->Afficher();
			for(int i=0;i<params->size();i++)
			{
				(*params)[i]->Afficher();
				cerr<<" ";
			}
			cerr<<endl;
		}
};*/




class Fonction : public InstructionProgramme, public Identifiable {
	public:
		Fonction(string type, string id, vector<Variable*>* s, Bloc* bloc = NULL): Identifiable(id), type(type), s(s), bloc(bloc) {}
		Bloc* bloc;
		string type;
		vector<Variable*>* s;
		virtual ~Fonction() {}
		void Afficher () {
			cerr<<"FONCTION"<<endl<<"	";
			cerr<<type<<" "<<id<<" ";
			cerr<<"SIZE : "<<s->size();
			for(int i=0;i<s->size();i++)
			{
				(*s)[i]->Afficher();

				cerr<<" ";
			}

			cerr<<endl;
			bloc->Afficher();
		}
		void RajouterBloc (Bloc* bloc){
			this->bloc=bloc;
			
		}

		
};




#endif
