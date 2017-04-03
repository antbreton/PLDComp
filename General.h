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
class CFG;

// ---- méthodes Utils --------

// Cette méthode crée une string de préfixes
string getTabPrefix(int n);

// ---- méthodes Utils --------


class Identifiable {
		public : 
			Identifiable(string id):id(id){}
			string id;	
			string getIdentifiant() {return id;}
			virtual ~Identifiable(){}
};


class Instruction {
	public:
		Instruction() {}
		virtual ~Instruction() {}
		virtual void Afficher(int nbtab) = 0;
};

class Expression : public Instruction {
	public:
		Expression(){}
		virtual ~Expression() {isInline = 0;}
		
		void setIsInline(int v) {isInline =v;}
		virtual void Afficher(int nbtab) { 
				if(isInline)
				{
					nbtab++;
					string tab = getTabPrefix(nbtab);
					cout << endl << tab;
				}
		}
	private :
		int isInline;
};


class Identifiant : public Expression {
	public:
		Identifiant(string * id):Expression(),id(id){}
		string * id;
		void Afficher(int nbtab) {
			Expression::Afficher(nbtab);
			cout<<"ID ";
			cout<<*id<<" ";
		}
};
class RetourExpr : public Instruction {
	public:
	RetourExpr(Expression * expr):Instruction(), expr(expr){}
	Expression * expr;
	void Afficher(int nbtab) {
		nbtab++;
		string tab = getTabPrefix(nbtab);
		
		cout<<tab<<"RETURN ";
		expr->Afficher(nbtab);
	}
};

class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
        // TODO : Pk val en public ?
        int valeur;
		void Afficher (int nbtab) {
			 cout<<"VAL "<< valeur<<" ";
		 }
		std::string construireIR(CFG* cfg);
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
        // TODO : Pk char en public ?
		char c;
		void Afficher (int nbtab) {
			 cout<<"CARACTERE"<< c;
		 }
		 std::string construireIR(CFG* cfg);
};

class Programme {
	public:
		Programme();
		virtual ~Programme() {}
		void ajouterFonction(Fonction* fonc) {fonctions->push_back(fonc);}
		void Afficher (int nbtab);
		
		// Cette méthode ajoute la liste de variable passée en paramètre à la table de symbole du programme
		void ajouterListeVariable(vector<Variable*>* listeVariable){} /* TODO */
		std::vector<Fonction*> getFonctions();
	private :
		map<string,Identifiable*>* tableSymboles; // Cet attribut correspond à la table de symbole : mapping entre un identifiant et un identifiable
		vector<Fonction*> *fonctions; // /* TODO Virer IntructionProgramme */
};

class Not : public Expression {
	public:
		Not(Expression * membre):Expression(), membre(membre) {}
	 	std::string construireIR(CFG* cfg);
	private:
		Expression * membre;
		 void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"NOT ";
			 membre->Afficher(nbtab);
		 }
};

class ExpreOpeBinaire : public Expression {
	public:
		ExpreOpeBinaire(Expression * membreG, Expression * membreD):Expression(), membreGauche(membreG), membreDroit(membreD) {}
		virtual std::string construireIR(CFG* cfg) = 0;
	protected:
		Expression * membreGauche;
		Expression * membreDroit;
		
};


class OperateurOR : public ExpreOpeBinaire {
	public:
		OperateurOR(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
			void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"OR ";
			 membreGauche->Afficher(nbtab);
			 cout<<" || ";
			 membreDroit->Afficher(nbtab);
		 }
		std::string construireIR(CFG* cfg);
};

class OperateurAND : public ExpreOpeBinaire {
public:
	OperateurAND(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"AND ";
			 membreGauche->Afficher(nbtab);
			 cout<<" && ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurSup : public ExpreOpeBinaire {
public:
	OperateurSup(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"SUP ";
			 membreGauche->Afficher(nbtab);
			 cout<<" > ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurInf : public ExpreOpeBinaire {
public:
	OperateurInf(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"INF ";
			 membreGauche->Afficher(nbtab);
			 cout<<" < ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurSupEgal : public ExpreOpeBinaire {
public:
	OperateurSupEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"SUPEGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" >= ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurInfEgal : public ExpreOpeBinaire {
public:
	OperateurInfEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
		void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"INFEGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" <= ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurEgal : public ExpreOpeBinaire {
public:
	OperateurEgal(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"EGAL ";
			 membreGauche->Afficher(nbtab);
			 cout<<" == ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurDifferent : public ExpreOpeBinaire {
public:
	OperateurDifferent(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"DIFF ";
			 membreGauche->Afficher(nbtab);
			 cout<<" != ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurPlus : public ExpreOpeBinaire {
public:
	OperateurPlus(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"ADD ";
			 membreGauche->Afficher(nbtab);
			 cout<<" + ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurMoins : public ExpreOpeBinaire {
public:
	OperateurMoins(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"MOINS ";
			 membreGauche->Afficher(nbtab);
			 cout<<" - ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurMultiplier : public ExpreOpeBinaire {
public:
	OperateurMultiplier(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"MULT ";
			 membreGauche->Afficher(nbtab);
			 cout<<" * ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurModulo : public ExpreOpeBinaire {
public:
	OperateurModulo(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"MODULO ";
			 membreGauche->Afficher(nbtab);
			 cout<<" % ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class OperateurDivise : public ExpreOpeBinaire {
public:
	OperateurDivise(Expression * membreG, Expression * membreD):ExpreOpeBinaire(membreG, membreD) {}
	void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"DIVISE ";
			 membreGauche->Afficher(nbtab);
			 cout<<" / ";
			 membreDroit->Afficher(nbtab);
		 }
	std::string construireIR(CFG* cfg);
};

class AppelFonction : public Expression {
public:
	AppelFonction():Expression() {this->parametres = new std::vector<Expression *>();}
	void ajouterParametre(Expression * expression) {parametres->push_back(expression);}
	void setParametres(std::vector<Expression*>* liste_expressions) {this->parametres = liste_expressions;}
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	virtual ~AppelFonction() {delete this->parametres; }
	void Afficher (int nbtab) {
		Expression::Afficher(nbtab);
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
		Expression::Afficher(nbtab);
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
