#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "General.h"
#include "IR/IR.h"
#include <iostream>

using namespace std;

class Bloc;

class StructureControle : public Instruction {
	public:
		StructureControle(Instruction * instrv);
		virtual ~StructureControle() {}	
		Instruction* instrv;
		virtual void Afficher (int nbtab){}
		virtual void setRecursifBlocAncestorToAll(Bloc * bloc);
		bool testReturn(bool nullable);
		void construireIR(CFG* cfg, vector<Instruction*>::iterator itCourant);
		virtual bool checkIDs() {if(Bloc *b1 = dynamic_cast<Bloc *>(instrv))	return b1->checkIDs();	return true;}
};

class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, Instruction * instrv, Instruction * blocElse = NULL);
		Expression* exprCondition;
		Instruction * blocElse;
		virtual bool checkIDs();
		void setRecursifBlocAncestorToAll(Bloc * bloc);
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
		virtual bool checkIDs();
		BlocWhile(Expression * expr, Instruction * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
		void Afficher (int nbtab) {
			nbtab++;
			string tab = getTabPrefix(nbtab);
			
			cout<<endl<<tab<<"BLOC_WHILE ( "; exprCondition->Afficher(nbtab); cout<<" ) ";
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
			nbtab++;
			string tab = getTabPrefix(nbtab);
			
			cout<<endl<<tab<<"BLOC_FOR ( "; exprInit->Afficher(nbtab); cout<<", "; exprCondition->Afficher(nbtab); cout<<", "; exprIncrementation->Afficher(nbtab); cout<<")";
			instrv->Afficher(nbtab);
		}
};


#endif
