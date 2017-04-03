#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "IR/CFG.h"
#include <iostream>


 
using namespace std;

// Méthodes utils
string getTabPrefix(int n)
{
	string tab ="";
	for(int i=0; i<n; i++)
	{
		tab+="\t";
	}
	return tab;
}


// Réalisation Programme
Programme::Programme()
{
	fonctions = new vector<Fonction*>();
	tableSymboles = new map<string,Identifiable*>();
}
void Programme::Afficher (int nbtab) 
{
	cout<< endl << endl << endl <<"PROGRAMME // tableSymb size : "<< tableSymboles->size();
	for(int i=0;i<fonctions->size();i++)
	{
		(*fonctions)[i]->Afficher(1);
	}
	cout<<endl<<"END_PROGRAMME"<<endl;
}

std::vector<Fonction*> Programme::getFonctions() 
{
	return *fonctions;
}

 	// Réalisation Variable
Variable::Variable(string id):Identifiable(id), initialisation (false)
{

}
Variable::Variable(string type, string id):Identifiable(id), type(type), initialisation (false)
{
cerr<< "type : "<<type<<" id : "<<id<<endl;;
}

Variable::Variable(string type, string id, Expression * expr):Identifiable(id), type(type), expr(expr),initialisation (true)
{
	
}

string Expression::construireIR(CFG* cfg) {
	if(dynamic_cast<OperateurAND*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurAND" << endl;
		return "";
	} else if(dynamic_cast<OperateurOR*>(this)) {
		cerr << "TODO : Construire IR : Classe OperatorOR" << endl;
		return "";
	} else if(dynamic_cast<OperateurSup*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurSup" << endl;
		return "";
	} else if(dynamic_cast<OperateurInf*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurInf" << endl;
		return "";
	} else if(dynamic_cast<OperateurSupEgal*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurSupEgal" << endl;
		return "";
	} else if(dynamic_cast<OperateurInfEgal*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurInfEgal" << endl;
		return "";
	} else if(dynamic_cast<OperateurEgal*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurEgal" << endl;
		return "";
	} else if(dynamic_cast<OperateurDifferent*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurDifferent" << endl;
		return "";
	} else if(dynamic_cast<OperateurPlus*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurPlus" << endl;
		return "";
	} else if(dynamic_cast<OperateurMoins*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurMoins" << endl;
		return "";
	} else if(dynamic_cast<OperateurMultiplier*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurMultiplier" << endl;
		return "";
	} else if(dynamic_cast<OperateurModulo*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurModulo" << endl;
		return "";
	} else if(dynamic_cast<OperateurDivise*>(this)) {

		//string reg1 = membreGauche->getType()->construireIR(cfg);
		//string reg2 = membreDroit->construireIR(cfg);

		//string reg3 = creerNouveauRegistre();

		//string ir = reg3 + " <- " + reg1 + " / " + reg2;
		//cfg->ajouterInstruction(ir);

		cerr << "TODO : Construire IR : Classe OperateurDivise" << endl;

		return "";

	} else if(dynamic_cast<Val*>(this)) {

		// Creation d'un registre temporaire
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		params.push_back(reg);
		params.push_back(to_string( static_cast<Val*>(this)->valeur) );
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);
		cerr << "Construire IR : Classe Val" << endl;

		return reg;

	} else if(dynamic_cast<Caractere*>(this)) {

		// Creation d'un registre temporaire
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		params.push_back(reg);
		params.push_back(to_string((int)(static_cast<Caractere*>(this)->c )));
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Construire IR : Classe Caractere" << endl;

		return reg;

	} else if(dynamic_cast<Not*>(this)) {
		cerr << "TODO : Construire IR : Classe Not" << endl;
		return "";
	} else if(dynamic_cast<Identifiant*>(this)) {
		return "Identifiant";
	} else if(AppelFonction* appelFonction = dynamic_cast<AppelFonction*>(this)) {
		
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;

		params.push_back(*appelFonction->getIdentifiant()->getId());
		params.push_back(reg);
		
		vector<Expression*>* listeParametresFonction = appelFonction->getParametres();
		for(int i = 0; i < listeParametresFonction->size(); i++)
		{
			string regI = (*listeParametresFonction)[i]->construireIR(cfg);
			params.push_back(regI);
		}

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CALL, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Construire IR : Classe AppelFonction" << endl;

		return reg;
	} else {
		return "Inconnu";
	}
}
