#ifndef _GENERAL_H
#define _GENERAL_H

#include <string> 
#include <vector>
#include <iostream>
#include <map>

 
using namespace std;

class Fonction;
class Val;
class Variable;

class Identifiable {
		public : 
			Identifiable(string id):id(id){}
			string id;	
};


class Instruction {
	public:
		Instruction() {}
		virtual ~Instruction() {}
		virtual void Afficher(){}
};
/*
class InstructionV : public Instruction {
	public:
		InstructionV(){}
		virtual ~InstructionV() {}
};*/

class Expression : public Instruction {
	public:
		Expression(){}
		virtual ~Expression() {}	
		virtual void Afficher() {}
};


class Identifiant : public Expression {
	public:
		Identifiant(string * id):Expression(),id(id){}
		string * id;
		void Afficher() {
			cerr<<"ID ";
			cerr<<*id<<" ";
		}
};
class RetourExpr : public Instruction {
	public:
	RetourExpr(Expression * expr):Instruction(), expr(expr){}
	Expression * expr;
	void Afficher() {
		cerr<<"RETURN ";
		expr->Afficher();
	}
};

class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
		int valeur;
		void Afficher () {
			 cerr<<"VAL "<< valeur <<endl;
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

/* TODO enelver InstructionProgramme vu que maintenant on a plus que des fonctions comme instruction */
class InstructionProgramme // Cette classe est dérivée par decls et fonction
{
	public :
		InstructionProgramme() {}
		bool compiler(); // TODO devront être virtuelles pure
		virtual void Afficher(){} //	""
};

/** Déclaration Class *//*
class Declaration : public Instruction, public InstructionProgramme
{
	public :
		Declaration(string type, Val * taille, Identifiant * id=NULL); //Je vois pas l'utilité du null
		virtual ~Declaration() {}
		void ajouterIdentifiant(Identifiant *id) {identifiants->push_back(id);}
		void addAllIdentifiants(std::vector<Identifiant*>* identifiants) { this->identifiants->insert(this->identifiants->end(), identifiants->begin(), identifiants->end());}
		void Afficher () {
			cerr<<"DECLARATION ";
			cerr<<type<<" ";
			for(int i=0;i<identifiants->size();i++)
			{
				(*identifiants)[i]->Afficher();
			}	
		}
	private :
		string type;
		Identifiant * id;
		int taille;
		vector<Identifiant*>* identifiants;
};*/


class Programme {
	public:
		Programme();
		virtual ~Programme() {}
		void ajouterInstruction(InstructionProgramme* instr) {instructions->push_back(instr);}
		void Afficher () {
			cerr<<"PROGRAMME"<<endl<<"	";
			for(int i=0;i<instructions->size();i++)
			{
				(*instructions)[i]->Afficher();
			}
			cerr<<"END_PROGRAMME"<<endl;
		}
		
		// Cette méthode ajoute la liste de variable passée en paramètre à la table de symbole du programme
		void ajouterListeVariable(vector<Variable*>* listeVariable){} /* TODO */
	private :
		map<string,Identifiable*>* tableSymboles; // Cet attribut correspond à la table de symbole : mapping entre un identifiant et un identifiable
		vector<InstructionProgramme*> *instructions;
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
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	virtual ~AppelFonction() {delete this->parametres; }
	void Afficher () {
		cerr<<"APPEL FONCTION ";
		identifiant->Afficher();
		for(int i=0;i<parametres->size();i++)
		{
			(*parametres)[i]->Afficher();
		}
		cerr<<endl;
		
	}
private:
	std::vector<Expression *> *parametres;
	Identifiant* identifiant;
};

class Affectation : public Expression {
public:
	Affectation():Expression() {}
	void setValeur(Expression* expression) {this->valeur = expression;}
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	void Afficher () {
		cerr<<"AFFECTATION ";
		identifiant->Afficher();
		cerr<<" = ";
		valeur->Afficher();
		cerr<<" ";		
	}

private:
	Identifiant* identifiant;
	Expression* valeur;
};

class Variable : public Identifiable
{
	public :
		Variable(string id);
		Variable(string type , string id);
		Variable(string type, string id, Expression * expr);
		void setValeur(Expression * expr){
			this->expr=expr;
		}
		void Afficher(){}
		string getType() {
				return type;
		}
		void setType(string type){
				this->type=type;
		}
	private:
		string type;
		bool initialisation;
		Expression * expr;
};

#endif
