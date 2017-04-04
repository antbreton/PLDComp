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
class Bloc;
class CFG;
class Affectation;
// ---- méthodes Utils --------

// Cette méthode crée une string de préfixes
string getTabPrefix(int n);

// ---- méthodes Utils --------
/*
class Noeud
{
	public :
		Noeud * ancetre;
		Bloc * getParentBloc();
		virtual test();
};
*/
class declarationGrammaire {
	public:
		declarationGrammaire (){};
		vector <Variable*>*  variables;
		Affectation* affectation;
		
};

class Identifiable {
		public : 
			Identifiable(string id):id(id){ cout <<endl<<endl<<endl<< "APLE CONSTR avec "<<id;}
			string id;	
			string getIdentifiant() { cout << "getid:" <<id<<endl; return id;}
			virtual ~Identifiable(){}
};


class Instruction {
	public:
		Instruction() {}
		virtual ~Instruction() {}
		virtual void Afficher(int nbtab) = 0;
		Bloc * getParentBloc();
		void setAncetre(Instruction * ancetre, string id = "") {/* DEBUG*/cout << "[a:"<<ancetre<<", c:"<<this<<" "<<id; this->ancetre = ancetre; cout <<"]"<<endl;}
	protected:
		Instruction * ancetre;

};

class Expression : public Instruction{
	public:
		Expression(){isInline = 0;}
		virtual ~Expression() {}
		std::string construireIR(CFG* cfg);
		void setIsInline(int v) {isInline =v;}
		virtual void Afficher(int nbtab) { 
				if(isInline)
				{
					nbtab++;
					string tab = getTabPrefix(nbtab);
					cout << endl << tab;
				}
		}
		virtual bool checkIDs(Bloc * b) { return true; }
	private :
		int isInline;
};


class Identifiant : public Expression {
	public:
		Identifiant(string * id):Expression(),id(id){}
		// TODO : Attribut public
		string * id;
		string* getId() { return this->id; }
		void Afficher(int nbtab) {
			Expression::Afficher(nbtab);
			cout<<"ID ";
			cout<<*id<<" ";
		}
		bool checkIDs(Bloc * b);
		// vérifie que l'identifiant utilisé exist bien dans une des tables de symbole du context courant
		bool checkExists();
};
class RetourExpr : public Instruction {
	public:
	RetourExpr(Expression * expr = NULL):Instruction(), expr(expr){}
	Expression * expr;
	void Afficher(int nbtab) {
		nbtab++;
		string tab = getTabPrefix(nbtab);
		
		cout<<tab<<"RETURN ";
		if(expr!=NULL)
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
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
        // TODO : Pk char en public ?
		char c;
		void Afficher (int nbtab) {
			 cout<<"CARACTERE"<< c;
		 }
};

class Programme {
	public:
		Programme();
		virtual ~Programme() {}
		void ajouterFonction(Fonction* fonc) {fonctions->push_back(fonc);}
		void Afficher (int nbtab);
		bool checkIDs();
		// Cette méthode ajoute la liste de variable passée en paramètre à la table de symbole du programme
		void ajouterListeVariable(vector<Variable*>* listeVariable);
		void setRecursifBlocAncestorToAll();
		pair<bool,string> testReturn();
		bool testMain();
		Bloc * getBloc() { return bloc; }
		std::vector<Fonction*> getFonctions();
	private :
		Bloc * bloc; // Ce bloc corresponds au contexte du programme, il contiends simplement la table de symbole.
		vector<Fonction*> *fonctions; //
};

class Not : public Expression {
	public: 
		Not(Expression * membre):Expression(), membre(membre) {}
	private:
		Expression * membre;
		bool checkIDs(Bloc *b) { return membre->checkIDs(b); }
		 void Afficher (int nbtab) {
			 Expression::Afficher(nbtab);
			 cout<<"NOT ";
			 membre->Afficher(nbtab);
		 }
};

class ExpreOpeBinaire : public Expression {
	public:
		ExpreOpeBinaire(Expression * membreG, Expression * membreD):Expression(), membreGauche(membreG), membreDroit(membreD) {}
		virtual bool checkIDs(Bloc * b) { bool mg = membreGauche->checkIDs(b); bool md = membreDroit->checkIDs(b); return mg && md; }
		Expression* getMembreGauche() { return membreGauche; }
		Expression* getMembreDroit() { return membreDroit; }
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
};

class AppelFonction : public Expression {
public:
	AppelFonction():Expression() {this->parametres = new std::vector<Expression *>();}
	void ajouterParametre(Expression * expression) {parametres->push_back(expression);}
	void setParametres(std::vector<Expression*>* liste_expressions) {this->parametres = liste_expressions;}
	void setIdentifiant(Identifiant* id) {this->identifiant = id;}
	std::vector<Expression*>* getParametres() { return this->parametres;}
	Identifiant* getIdentifiant() { return this->identifiant;}
	virtual ~AppelFonction() {delete this->parametres; }
	bool checkIDs(Bloc *b) { int echec = 0; for(int i=0;i<parametres->size();i++){	if(!(*parametres)[i]->checkIDs(b)) echec++;		}	return (echec == 0); }	
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
	Expression* getValeur() { return this->valeur; }
	Identifiant* getIdentifiant(){ return this->identifiant; }
	void Afficher (int nbtab) {
		Expression::Afficher(nbtab);
		cout<<"AFFECTATION ";
		identifiant->Afficher(nbtab);
		cout<<" = ";
		valeur->Afficher(nbtab);
		cout<<" ";		
	}

private:
	bool checkIDs(Bloc *c);
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
