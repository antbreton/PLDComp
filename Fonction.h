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
			cout<<"BLOC"<<endl;
			for(int i=0;i<instrs->size();i++)
			{
				(*instrs)[i]->Afficher();
				cout<<";";
			}
			cout<<endl;
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
		Prototype(string* type, vector<Declaration*>* params, string* identifiant) : type(type), params(params), identifiant(identifiant) {}
		string* type;
		vector<Declaration*>* params;
		string* identifiant;
		void Afficher() {
			cout<<"PROTOTYPE"<<endl;;
			cout<<*type<<" "<<*identifiant;
			for(int i=0;i<params->size();i++)
			{
				(*params)[i]->Afficher();
				cout<<",";
			}
			cout<<endl;
		}
};



class Fonction : public InstructionProgramme {
	public:
		Fonction(Prototype* proto, Bloc* bloc = NULL): proto(proto), bloc(bloc) {}
		Prototype* proto;
		Bloc* bloc;
		virtual ~Fonction() {}
		void Afficher () {
			cout<<"FONCTION";
			proto->Afficher();
			bloc->Afficher();
		}
};




#endif
