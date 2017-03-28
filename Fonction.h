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
};



class Fonction : public InstructionProgramme {
	public:
		Fonction(Prototype* proto, Bloc* bloc = NULL): proto(proto), bloc(bloc) {}
		Prototype* proto;
		Bloc* bloc;
		virtual ~Fonction() {}
		void Afficher () {
			cerr<<"FONCTION"<<endl<<"	";
			proto->Afficher();
			bloc->Afficher();
		}
};




#endif
