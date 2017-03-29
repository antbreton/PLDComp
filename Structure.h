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
		virtual void Afficher (){}
};
class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, Instruction * instrv, Instruction * blocElse = NULL):StructureControle(instrv), exprCondition(expr), blocElse(blocElse){}
		Expression* exprCondition;
		Instruction * blocElse;
		void Afficher () {
			cerr<<"BLOC_IF ( "; exprCondition->Afficher(); cerr<<" ) {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
			if(blocElse!=NULL)
			{
				blocElse->Afficher();
			}
		}
};

class BlocWhile : public StructureControle {
	public:
		BlocWhile(Expression * expr, Instruction * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
		void Afficher () {
			cerr<<"BLOC_WHILE ( "; exprCondition->Afficher(); cerr<<" ) {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
		}
};

class BlocFor : public StructureControle {
	public:
		BlocFor(Expression * exprInit, Expression * exprCondition, Expression * exprIncrementation, Instruction * instrv):StructureControle(instrv), exprInit(exprInit), exprCondition(exprCondition), exprIncrementation(exprIncrementation) {}
		Expression* exprInit;
		Expression* exprCondition;
		Expression* exprIncrementation;
		void Afficher () {
			cerr<<"BLOC_FOR ( "; exprInit->Afficher(); cerr<<", "; exprCondition->Afficher(); cerr<<", "; exprIncrementation->Afficher(); cerr<<") {"<<endl;
			instrv->Afficher();
			cerr<<"}"<<endl;	
		}
};


#endif
