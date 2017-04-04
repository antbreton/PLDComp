#ifndef _FONCTION_H
#define _FONCTION_H

#include <string> 
#include <list>
#include <vector>
#include <iostream>

#include "General.h"

 
using namespace std;
 
class Variable;


class Bloc : public Instruction  {
	public:
		Bloc();
		virtual ~Bloc() {}
		void AjouterInstr (Instruction* instr);
		vector<Instruction*>* instrs;
		bool checkIDs();
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
			
			// Cette méthode va récursivement ajouter ce bloc en ancetre de tous ses fils direct. Puis il va set l'ancetre du bloc courant.
			void setRecursifBlocAncestorToAll(Bloc * ancetre);
		Identifiable * getIdentifiableIfExist(string id);
		map<string,Identifiable*>* getTableSymboles() { return tableSymboles; }
			bool testReturn(bool nullable);

		vector<Instruction*>* getInstructions();
		int compterNbVariable();
		void constructor_tableVariables();
		map<string,Variable*>* tableVariables;


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
		Fonction(string type, string id, vector<Variable*>* s, Bloc* bloc = NULL);
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

		
		//Bloc* getBloc();
		vector<Variable*>* getVariables() { return this->s;}



		void RajouterBloc (Bloc* bloc);
		Bloc * getBloc() { return bloc; }
		bool testReturn();
};



#endif



