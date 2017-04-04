#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "IR/CFG.h"
#include "IR/IRInstr.h"
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
		cout << "Egal" << endl;
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
		
		cout<< "IR Val" << endl;

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
		
		cout<< "IR Caractere" << endl;
		
		// Creation d'un registre temporaire
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		cout<< "IR Caractere apres blockcourant" << endl;
		vector<std::string> params;
		params.push_back(reg);
		params.push_back(to_string((int)(static_cast<Caractere*>(this)->c )));
		cout<< "IR Caractere apres les pushback" << endl;
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		cout<< "IR Caractere apres creation nouvelleInstr" << endl;
		blocCourant->ajouterInstrIR(nouvelleInstr);
		cout<< "IR Caractere apres ajouterInstrIR" << endl;
		cerr << "Construire IR : Classe Caractere" << endl;

		return reg;

	} else if(dynamic_cast<Not*>(this)) {
		cerr << "TODO : Construire IR : Classe Not" << endl;
		return "";
	} else if(dynamic_cast<Identifiant*>(this)) {
		return "Identifiant";
	} else if(AppelFonction* appelFonction = dynamic_cast<AppelFonction*>(this)) {
		
		cout << "appel de fonction 1" << endl;
		string reg = cfg->creerNouveauRegistre();
		cout << "appel de fonction 2" << endl;
		BasicBlock* blocCourant = cfg->getBlockCourant();
		cout << "appel de fonction 3" << endl;
		vector<std::string> params;

		params.push_back(*appelFonction->getIdentifiant()->getId());
		params.push_back(reg);
		cout << "appel de fonction 4" << endl;
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
	} else if(Affectation* affectation = dynamic_cast<Affectation*>(this)) {

		cout << "Affectation" << endl;
		BasicBlock* blocCourant = cfg->getBlockCourant();
		string nomVariable = *affectation->getIdentifiant()->getId();
		string reg;

		if(!blocCourant->estVarMappee(nomVariable)){
			blocCourant->ajouterVariableMappee(cfg, nomVariable);
		} 
			// Registre leftValue
			reg = "!r" + blocCourant->getValeurMappee(nomVariable);

			//Registre rightValue
			string reg2 = 	affectation->getValeur()->construireIR(cfg);

			vector<std::string> params;
			params.push_back(reg); // Destination
			params.push_back(reg2); // Source
			IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::WMEM, blocCourant, params);
			blocCourant->ajouterInstrIR(nouvelleInstr);

			cerr << "Construire IR : Classe Affectation" << endl;

			return reg;

	} else {
		return "Inconnu";
	}
}
