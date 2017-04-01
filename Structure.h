#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "General.h"
#include <iostream>

using namespace std;

class StructureControle : public Instruction {
	public:
		StructureControle(Instruction * instrv): instrv(instrv){}
		virtual ~StructureControle() {}	
		Instruction* instrv;
		virtual void Afficher (int nbtab){}
};
class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, Instruction * instrv, Instruction * blocElse = NULL):StructureControle(instrv), exprCondition(expr), blocElse(blocElse){}
		Expression* exprCondition;
		Instruction * blocElse;
		void Afficher (int nbtab) {
			nbtab++;
			string tab = getTabPrefix(nbtab);
			
			cout<<endl<<tab<<"BLOC_IF ( "; 
			exprCondition->Afficher(nbtab);
			cout <<")" << endl;
			instrv->Afficher(nbtab);
			if(blocElse!=NULL)
			{
				cout<<endl<<tab<<"BLOC_ELSE"; 
				blocElse->Afficher(nbtab);
			}
		}
};

class BlocWhile : public StructureControle {
	public:
		BlocWhile(Expression * expr, Instruction * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
		void Afficher (int nbtab) {
			cout<<"BLOC_WHILE ( "; exprCondition->Afficher(nbtab); cout<<" ) ";
			instrv->Afficher(nbtab);
		}
};

class BlocFor : public StructureControle {
	public:
		BlocFor(Expression * exprInit, Expression * exprCondition, Expression * exprIncrementation, Instruction * instrv):StructureControle(instrv), exprInit(exprInit), exprCondition(exprCondition), exprIncrementation(exprIncrementation) {}
		Expression* exprInit;
		Expression* exprCondition;
		Expression* exprIncrementation;
		void Afficher (int nbtab) {
			cout<<"BLOC_FOR ( "; exprInit->Afficher(nbtab); cout<<", "; exprCondition->Afficher(nbtab); cout<<", "; exprIncrementation->Afficher(nbtab); cout<<")";
			instrv->Afficher(nbtab);
		}
};


#endif
