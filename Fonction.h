#ifndef _FONCTION_H
#define _FONCTION_H

#include "General.h"
#include <string> 
#include <list>
#include <vector>
#include <iostream>


 
using namespace std;
 
class Declaration;


class Bloc : public InstructionV  {
	public:
		Bloc(Instruction* instr) {instrs = new vector <Instruction*>; this->AjouterInstr(instr);}
		virtual ~Bloc() {}
		void AjouterInstr (Instruction* instr) {instrs->push_back(instr);};
		vector<Instruction*>* instrs;
		void Afficher () {
			cerr<<"BEGIN_BLOC"<<endl;
			for(int i=0;i<instrs->size();i++)
			{
				(*instrs)[i]->Afficher();
			}
			cerr<<"END_BLOC"<<endl;
		}
		

};
/*
class Type {
	public:
		Type() {}
		virtual ~Type() {}
};
*/

class ParamDeclar {
	public:
		ParamDeclar(vector<Declaration*>* params): params(params) {}
		vector<Declaration*>* params;
};

/*
class Prototype {
	public:
		Prototype(string* type, vector<Declaration*>* params, Identifiant* identifiant) : type(type), params(params), identifiant(identifiant) {}
		string* type;
		vector<Declaration*>* params;
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


class Identifiable {
		public : 
			Identifiable(string id):id(id){}
			string id;
		
	
};

class Fonction : public InstructionProgramme, public Identifiable {
	public:
		Fonction(string type, string id, vector<Declaration*>* declarations, Bloc* bloc = NULL): Identifiable(id), type(type), declarations(declarations), bloc(bloc) {}
		Bloc* bloc;
		string type;
		vector<Declaration*>* declarations;
		virtual ~Fonction() {}
		void Afficher () {
			cerr<<"FONCTION"<<endl<<"	";
			cerr<<type<<" "<<id<<" ";
			for(int i=0;i<declarations->size();i++)
			{
				(*declarations)[i]->Afficher();
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
