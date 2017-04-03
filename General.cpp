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

// Réalisation Programme ----
Programme::Programme()
{
	fonctions = new vector<Fonction*>();
	bloc 			= new Bloc();
}

void Programme::Afficher (int nbtab) 
{
	cout<< endl << endl << endl <<"PROGRAMME // tableSymb size : "<< bloc->getTableSymboles()->size();
	for(int i=0;i<fonctions->size();i++)
	{
		(*fonctions)[i]->Afficher(1);
	}
	cout<<endl<<"END_PROGRAMME"<<endl;
}

void Programme::ajouterListeVariable(vector<Variable*>* listeVariable)
{
	bloc->ajouterListeVariable(listeVariable);
}


// This method set the 
void Programme::setRecursifBlocAncestorToAll()
{
	for(int i=0;i<fonctions->size();i++)
	{
		(*fonctions)[i]->getBloc()->setRecursifBlocAncestorToAll(this->bloc);
	}
}
// --------------------------



pair<bool,string> Programme::testReturn() {
	bool allOK=true;
	pair<bool,string> valeursRetour;
	
	for(int i=0;i<fonctions->size();i++)
	{
		bool tmp = (*fonctions)[i]->testReturn();
		if(!tmp){
			valeursRetour.second = (*fonctions)[i]->id;
			allOK=false;
			break;
		}
	}
	valeursRetour.first = allOK;
	//cout <<"RESULT RETURN :"<<allOK<<endl;
	return valeursRetour;
}

bool Programme::testMain(){
	bool mainFind=false;
	for(int i=0;i<fonctions->size();i++)
	{
		if((*fonctions)[i]->id=="main"){
			mainFind=true;;
			break;
		}
	}
	
	return mainFind;
	
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
