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
			 cerr<<"VAL"<< valeur <<endl;
		 }
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
		char c;
		void Afficher () {
			 cerr<<"CARACTERE"<< c<<endl;
		 }
};

class Not : public Expression {
	public:
		Not(Expression * membre):Expression(), membre(membre) {}
	private:
		Expression * membre;
		 void Afficher () {
			 cerr<<"NOT ";
			 membre->Afficher();
			 cerr<<endl;
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
			 cerr<<"OR ";
			 membreGauche->Afficher();
			 cerr<<" || ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurAND : public ExpreOpeBinaire {
public:
	OperateurAND(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cerr<<"AND ";
			 membreGauche->Afficher();
			 cerr<<" && ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurSup : public ExpreOpeBinaire {
public:
	OperateurSup(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cerr<<"SUP ";
			 membreGauche->Afficher();
			 cerr<<" > ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurInf : public ExpreOpeBinaire {
public:
	OperateurInf(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cerr<<"INF ";
			 membreGauche->Afficher();
			 cerr<<" < ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurSupEgal : public ExpreOpeBinaire {
public:
	OperateurSupEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cerr<<"SUPEGAL ";
			 membreGauche->Afficher();
			 cerr<<" >= ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurInfEgal : public ExpreOpeBinaire {
public:
	OperateurInfEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher () {
			 cerr<<"INFEGAL ";
			 membreGauche->Afficher();
			 cerr<<" <= ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurEgal : public ExpreOpeBinaire {
public:
	OperateurEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"EGAL ";
			 membreGauche->Afficher();
			 cerr<<" == ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurDifferent : public ExpreOpeBinaire {
public:
	OperateurDifferent(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"DIFF ";
			 membreGauche->Afficher();
			 cerr<<" != ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurPlus : public ExpreOpeBinaire {
public:
	OperateurPlus(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"ADD ";
			 membreGauche->Afficher();
			 cerr<<" + ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurMoins : public ExpreOpeBinaire {
public:
	OperateurMoins(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"MOINS ";
			 membreGauche->Afficher();
			 cerr<<" - ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurMultiplier : public ExpreOpeBinaire {
public:
	OperateurMultiplier(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"MULT ";
			 membreGauche->Afficher();
			 cerr<<" * ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurModulo : public ExpreOpeBinaire {
public:
	OperateurModulo(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"MODULO ";
			 membreGauche->Afficher();
			 cerr<<" % ";
			 membreDroit->Afficher();
			 cerr<<endl;
		 }
};

class OperateurDivise : public ExpreOpeBinaire {
public:
	OperateurDivise(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher () {
			 cerr<<"DIVISE ";
			 membreGauche->Afficher();
			 cerr<<" / ";
			 membreDroit->Afficher();
			 cerr<<endl;
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
		cerr<<"APPEL FONCTION"<<endl;
		cerr<<identifiant<<"(";
		for(int i=0;i<parametres->size();i++)
		{
			cerr<<(*parametres)[i]<<", ";
		}
		cerr<<endl;
		
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
		cerr<<"AFFECTATION";
		cerr<< *identifiant <<" = "<< valeur<<endl;		
	}

private:
	std::string* identifiant;
	Expression* valeur;
};
#endif
