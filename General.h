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


// ---- méthodes Utils --------

// Cette méthode crée une string de préfixes
string getTabPrefix(int n);

// ---- méthodes Utils --------


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
		virtual void Afficher(int nbtab) = 0;
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
		virtual void Afficher(int nbtab) {}
};


class Identifiant : public Expression {
	public:
		Identifiant(string * id):Expression(),id(id){}
		string * id;
		void Afficher(int nbtab) {

			cout<<"ID ";
			cout<<*id<<" ";
		}
};
class RetourExpr : public Instruction {
	public:
	RetourExpr(Expression * expr):Instruction(), expr(expr){}
	Expression * expr;
	void Afficher(int nbtab) {
		cout<<"RETURN ";
		expr->Afficher(nbtab);
	}
};

class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
		int valeur;
		void Afficher (int nbtab) {
			 cout<<"VAL "<< valeur<<" ";
		 }
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
		char c;
		void Afficher (int nbtab) {
			 cout<<"CARACTERE"<< c;
		 }
};

/* TODO enelver InstructionProgramme vu que maintenant on a plus que des fonctions comme instruction */
class InstructionProgramme // Cette classe est dérivée par decls et fonction
{
	public :
		InstructionProgramme() {}
		bool compiler(); // TODO devront être virtuelles pure
		virtual void Afficher(int nbtab){} //	""
};

class Programme {
	public:
		Programme();
		virtual ~Programme() {}
		void ajouterInstruction(InstructionProgramme* instr) {instructions->push_back(instr);}
		void Afficher (int nbtab) {
			cout<< endl << endl << endl <<"PROGRAMME // tableSymb size : "<< tableSymboles->size() <<endl<<"	";
			for(int i=0;i<instructions->size();i++)
			{
				(*instructions)[i]->Afficher(1);
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
		 void Afficher (int nbtab) {
			 cout<<"NOT ";
			 membre->Afficher(nbtab);
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
			void Afficher (int nbtab) {
			 cout<<"OR ";
			 membreGauche->Afficher(nbtab);
			 cout<<" || ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurAND : public ExpreOpeBinaire {
public:
	OperateurAND(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 cout<<"AND ";
			 membreGauche->Afficher(nbtab);
			 cout<<" && ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurSup : public ExpreOpeBinaire {
public:
	OperateurSup(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 cout<<"SUP ";
			 membreGauche->Afficher(nbtab);
			 cout<<" > ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurInf : public ExpreOpeBinaire {
public:
	OperateurInf(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 cout<<"INF ";
			 membreGauche->Afficher(nbtab);
			 cout<<" < ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurSupEgal : public ExpreOpeBinaire {
public:
	OperateurSupEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 cout<<"SUPEGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" >= ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurInfEgal : public ExpreOpeBinaire {
public:
	OperateurInfEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 cout<<"INFEGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" <= ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurEgal : public ExpreOpeBinaire {
public:
	OperateurEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"EGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" == ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurDifferent : public ExpreOpeBinaire {
public:
	OperateurDifferent(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"DIFF ";
			 membreGauche->Afficher(nbtab);
			 cout<<" != ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurPlus : public ExpreOpeBinaire {
public:
	OperateurPlus(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"ADD ";
			 membreGauche->Afficher(nbtab);
			 cout<<" + ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurMoins : public ExpreOpeBinaire {
public:
	OperateurMoins(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"MOINS ";
			 membreGauche->Afficher(nbtab);
			 cout<<" - ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurMultiplier : public ExpreOpeBinaire {
public:
	OperateurMultiplier(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"MULT ";
			 membreGauche->Afficher(nbtab);
			 cout<<" * ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurModulo : public ExpreOpeBinaire {
public:
	OperateurModulo(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"MODULO ";
			 membreGauche->Afficher(nbtab);
			 cout<<" % ";
			 membreDroit->Afficher(nbtab);
		 }
};

class OperateurDivise : public ExpreOpeBinaire {
public:
	OperateurDivise(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 cout<<"DIVISE ";
			 membreGauche->Afficher(nbtab);
			 cout<<" / ";
			 membreDroit->Afficher(nbtab);
		 }
};

class AppelFonction : public Expression {
public:
	AppelFonction():Expression() {this->parametres = new std::vector<Expression *>();}
	void ajouterParametre(Expression * expression) {parametres->push_back(expression);}
	void setParametres(std::vector<Expression*>* liste_expressions) {this->parametres = liste_expressions;}
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	virtual ~AppelFonction() {delete this->parametres; }
	void Afficher (int nbtab) {
		cout<<"APPEL FONCTION ";
		identifiant->Afficher(nbtab);
		for(int i=0;i<parametres->size();i++)
		{
			(*parametres)[i]->Afficher(nbtab);
		}		
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
	void Afficher (int nbtab) {
		cout<<"AFFECTATION ";
		identifiant->Afficher(nbtab);
		cout<<" = ";
		valeur->Afficher(nbtab);
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
		void Afficher(int nbtab)
		{
			cout<<"VAR "<<type<<" "<<id;	
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
