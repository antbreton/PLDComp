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
			string getIdentifiant() {return id;}
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
			cout<<"ID ";
			cout<<*id<<" ";
		}
};
class RetourExpr : public Instruction {
	public:
	RetourExpr(Expression * expr):Instruction(), expr(expr){}
	Expression * expr;
	void Afficher() {
		cout<<"RETURN ";
		expr->Afficher();
	}
};

class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
		int valeur;
		void Afficher () {
			 cout<<"VAL "<< valeur <<endl;
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
			cout<<"DECLARATION ";
			cout<<type<<" ";
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
			cout<< endl << endl << endl <<"PROGRAMME - tableSymb size : "<< tableSymboles->size() <<endl<<"	";
			for(int i=0;i<instructions->size();i++)
			{
				(*instructions)[i]->Afficher();
			}
			cout<<"END_PROGRAMME"<<endl << endl << endl <<endl;
		}
		
		// Cette méthode ajoute la liste de variable passée en paramètre à la table de symbole du programme
		void ajouterListeVariable(vector<Variable*>* listeVariable){} /* TODO */
	private :
		map<string,Identifiable*>* tableSymboles; // Cet attribut correspond à la table de symbole : mapping entre un identifiant et un identifiable
		vector<InstructionProgramme*> *instructions; // /* TODO Virer IntructionProgramme */
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
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	virtual ~AppelFonction() {delete this->parametres; }
	void Afficher () {
		cout<<"APPEL FONCTION ";
		identifiant->Afficher();
		for(int i=0;i<parametres->size();i++)
		{
			(*parametres)[i]->Afficher();
		}
		cout<<endl;
		
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
		cout<<"AFFECTATION ";
		identifiant->Afficher();
		cout<<" = ";
		valeur->Afficher();
		cout<<" ";		
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
		void Afficher(){
		//	cout<<"VAR type : "<<type<<" id :"<<id;
			
			
			
			}
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
