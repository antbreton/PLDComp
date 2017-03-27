#ifndef _STRUCTURE_H
#define _STRUCTURE_H
#include "General.h"
#include <iostream>

class StructureControle : public InstructionV {
	public:
		StructureControle(InstructionV * instrv): instrv(instrv){}
		virtual ~StructureControle() {}	
		InstructionV* instrv;
		void Afficher ();
};
class BlocIf : public StructureControle {
	public:
		BlocIf(Expression * expr, InstructionV * instrv, InstructionV * blocElse = NULL):StructureControle(instrv), exprCondition(expr), blocElse(blocElse){}
		Expression* exprCondition;
		InstructionV * blocElse;
		void Afficher () {
			cout<<"BLOC_IF ( "; exprCondition->Afficher(); cout<<" ) {"<<endl;
			instrv->Afficher();
			cout<<"}"<<endl;	
			if(blocElse!=NULL)
			{
				blocElse->Afficher();
			}
		}
};

class BlocWhile : public StructureControle {
	public:
		BlocWhile(Expression * expr, InstructionV * instrv):StructureControle(instrv), exprCondition(expr) {}
		Expression* exprCondition;
		void Afficher () {
			cout<<"BLOC_WHILE ( "; exprCondition->Afficher(); cout<<" ) {"<<endl;
			instrv->Afficher();
			cout<<"}"<<endl;	
		}
};

class BlocFor : public StructureControle {
	public:
		BlocFor(Expression * exprInit, Expression * exprCondition, Expression * exprIncrementation, InstructionV * instrv):StructureControle(instrv), exprInit(exprInit), exprCondition(exprCondition), exprIncrementation(exprIncrementation) {}
		Expression* exprInit;
		Expression* exprCondition;
		Expression* exprIncrementation;
		void Afficher () {
			cout<<"BLOC_FOR ( "; exprInit->Afficher(); cout<<", "; exprCondition->Afficher(); cout<<", "; exprIncrementation->Afficher(); cout<<") {"<<endl;
			instrv->Afficher();
			cout<<"}"<<endl;	
		}
};


#endif
