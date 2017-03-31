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
		
		void Afficher (int nbtab) {
			string tab = getTabPrefix(nbtab);
			cout<<endl<<tab<<"BEGIN_BLOC // nb instr : "<<instrs->size()<< " - tableSymb size : "<< tableSymboles->size();
			for(int i=0;i<instrs->size();i++)
			{
				(*instrs)[i]->Afficher(nbtab);
			}
			cout<<endl<<tab<<"END_BLOC";
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

class Fonction : public Identifiable {
	public:
		Fonction(string type, string id, vector<Variable*>* s, Bloc* bloc = NULL): Identifiable(id), type(type), s(s), bloc(bloc) {}
		Bloc* bloc;
		string type;
		vector<Variable*>* s;
		virtual ~Fonction() {}
		void Afficher (int nbtab) {
			string tab = getTabPrefix(nbtab);
			
			cout<<endl<<tab<<"FONCTION"<<"	";
			cout<<type<<" "<<id<<" ";
			cout<<"// size : "<<s->size();
			
			for(int i=0;i<s->size();i++)
			{
				(*s)[i]->Afficher(nbtab);

				cout<<" ";
			}
			if(bloc != NULL)
				bloc->Afficher(nbtab);
		}
		void RajouterBloc (Bloc* bloc){
			this->bloc=bloc;
			
		}
};




#endif
