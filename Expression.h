#ifndef _EXPRESSION_H
#define _EXPRESSION_H

#include "General.h"
#include <vector>
#include <string>
#include <iostream>


class Expression : public InstructionV {
	public:
		Expression(){}
		virtual ~Expression() {}	
};


class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
		 int valeur;
		 void Afficher () {
			 cout<<"VALEUR"<< valeur<<endl;
		 }
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
		char c;
		void Afficher () {
			 cout<<"CARACTERE"<< c<<endl;
		 }
};

class Not : public Expression {
	public:
		Not(Expression * membre):Expression(), membre(membre) {}
	private:
		Expression * membre;
		 void Afficher () {
			 cout<<"NOT ";
			 membre->Afficher();
			 cout<<endl;
		 }
};

class ExpreOpeBinaire : public Expression {
	public:
		ExpreOpeBinaire(Expression * membreG, Expression * membreD):Expression(), membreGauche(membreG), membreDroit(membreD) {}
	protected:
		Expression * membreGauche;
		Expression * membreDroit;
		
};


class OperateurOR : public ExpreOpeBinaire {
	public:
		OperateurOR(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
			void Afficher () {
			 cout<<"OR ";
			 membreGauche->Afficher();
			 cout<<" || ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurAND : public ExpreOpeBinaire {
public:
	OperateurAND(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cout<<"AND ";
			 membreGauche->Afficher();
			 cout<<" && ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurSup : public ExpreOpeBinaire {
public:
	OperateurSup(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cout<<"SUP ";
			 membreGauche->Afficher();
			 cout<<" > ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurInf : public ExpreOpeBinaire {
public:
	OperateurInf(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cout<<"INF ";
			 membreGauche->Afficher();
			 cout<<" < ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurSupEgal : public ExpreOpeBinaire {
public:
	OperateurSupEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cout<<"SUPEGAL ";
			 membreGauche->Afficher();
			 cout<<" >= ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurInfEgal : public ExpreOpeBinaire {
public:
	OperateurInfEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cout<<"INFEGAL ";
			 membreGauche->Afficher();
			 cout<<" <= ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurEgal : public ExpreOpeBinaire {
public:
	OperateurEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"EGAL ";
			 membreGauche->Afficher();
			 cout<<" == ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurDifferent : public ExpreOpeBinaire {
public:
	OperateurDifferent(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"DIFF ";
			 membreGauche->Afficher();
			 cout<<" != ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurPlus : public ExpreOpeBinaire {
public:
	OperateurPlus(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"ADD ";
			 membreGauche->Afficher();
			 cout<<" + ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurMoins : public ExpreOpeBinaire {
public:
	OperateurMoins(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"MOINS ";
			 membreGauche->Afficher();
			 cout<<" - ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurMultiplier : public ExpreOpeBinaire {
public:
	OperateurMultiplier(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"MULT ";
			 membreGauche->Afficher();
			 cout<<" * ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurModulo : public ExpreOpeBinaire {
public:
	OperateurModulo(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"MODULO ";
			 membreGauche->Afficher();
			 cout<<" % ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class OperateurDivise : public ExpreOpeBinaire {
public:
	OperateurDivise(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cout<<"DIVISE ";
			 membreGauche->Afficher();
			 cout<<" / ";
			 membreDroit->Afficher();
			 cout<<endl;
		 }
};

class AppelFonction : public Expression {
public:
	AppelFonction():Expression() {this->parametres = new std::vector<Expression *>();}
	void ajouterParametre(Expression * expression) {parametres->push_back(expression);}
	void setParametres(std::vector<Expression*>* liste_expressions) {this->parametres = liste_expressions;}
	void setIdentifiant(std::string* id) {this->identifiant = id;}
	virtual ~AppelFonction() {delete this->parametres; }
	void Afficher () {
		cout<<"APPEL FONCTION"<<endl;
		cout<<identifiant<<"(";
		for(int i=0;i<parametres->size();i++)
		{
			cout<<(*parametres)[i]<<", ";
		}
		cout<<endl;
		
	}
private:
	std::vector<Expression *> *parametres;
	std::string* identifiant;
};

class Affectation : public Expression {
public:
	Affectation():Expression() {}
	void setValeur(Expression* expression) {this->valeur = expression;}
	void setIdentifiant(std::string* id) {this->identifiant = id;}
	void Afficher () {
		cout<<"AFFECTATION";
		cout<< *identifiant <<" = "<< valeur<<endl;		
	}

private:
	std::string* identifiant;
	Expression* valeur;
};
#endif
