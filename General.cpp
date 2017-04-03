#include "General.h"
#include "Expression.h"
#include "Fonction.h"
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

string Not::construireIR() {
	cerr << "TODO : Construire IR : Classe Not" << endl;
}

std::string OperateurOR::construireIR() {
	cerr << "TODO : Construire IR : Classe OperatorOR" << endl;
}

std::string OperateurAND::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurAND" << endl;
}

std::string OperateurSup::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurSup" << endl;
}

std::string OperateurInf::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurInf" << endl;
}

std::string OperateurSupEgal::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurSupEgal" << endl;
}

std::string OperateurInfEgal::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurInfEgal" << endl;
}

std::string OperateurEgal::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurEgal" << endl;
}

std::string OperateurDifferent::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurDifferent" << endl;
}

std::string OperateurPlus::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurPlus" << endl;
}

std::string OperateurMoins::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurMoins" << endl;
}

std::string OperateurMultiplier::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurMultiplier" << endl;
}

std::string OperateurModulo::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurModulo" << endl;
}

std::string OperateurDivise::construireIR() {
	cerr << "TODO : Construire IR : Classe OperateurDivise" << endl;
}

std::string AppelFonction::construireIR() 
{
	return "";
}
