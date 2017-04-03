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

string Not::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe Not" << endl;
    return "";
    
}

std::string OperateurOR::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperatorOR" << endl;
    return "";
}

std::string OperateurAND::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurAND" << endl;
    return "";
}

std::string OperateurSup::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurSup" << endl;
    return "";
}

std::string OperateurInf::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurInf" << endl;
    return "";
}

std::string OperateurSupEgal::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurSupEgal" << endl;
    return "";
}

std::string OperateurInfEgal::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurInfEgal" << endl;
    return "";
}

std::string OperateurEgal::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurEgal" << endl;
    return "";
}

std::string OperateurDifferent::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurDifferent" << endl;
    return "";
}

std::string OperateurPlus::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurPlus" << endl;
    return "";
}

std::string OperateurMoins::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurMoins" << endl;
    return "";
}

std::string OperateurMultiplier::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurMultiplier" << endl;
    return "";
}

std::string OperateurModulo::construireIR(CFG* cfg) {
	cerr << "TODO : Construire IR : Classe OperateurModulo" << endl;
    return "";
}

std::string OperateurDivise::construireIR(CFG* cfg) {
	// TODO : Caster l'expression selon son type
    //string reg1 = membreGauche->construireIR(cfg);
	//string reg2 = membreDroit->construireIR(cfg);

	//string reg3 = creerNouveauRegistre();

	//string ir = reg3 + " <- " + reg1 + " / " + reg2;
	//cfg->ajouterInstruction(ir);

	cerr << "TODO : Construire IR : Classe OperateurDivise" << endl;

    return "";
}

std::string Caractere::construireIR(CFG* cfg) {
	// Creation d'un registre temporaire
	// TODO : Gerer typage, i.e comment savoir si la variable est un INT_32, char, etc..

	string reg = cfg->creerNouveauRegistre();
	//cfg->ajouterInstruction( reg + " <- constant");
    cerr << "TODO : Construire IR : Classe Caractere" << endl;

	return reg;
}

std::string Val::construireIR(CFG* cfg) {
	// Creation d'un registre temporaire
	string reg = cfg->creerNouveauRegistre();
	BasicBlock* blocCourant = cfg->getBlockCourant();
	vector<std::string> params;
	params.push_back(reg);
	params.push_back(to_string(this->valeur));
	IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
	blocCourant->ajouterInstrIR(nouvelleInstr);
    cerr << "Construire IR : Classe Val" << endl;

    return reg;
}