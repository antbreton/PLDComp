#include "General.h"
#include "Fonction.h"
#include "Structure.h"
#include "IR/IR.h"
#include "test.tab.h"

extern int yydebug;

using namespace std;

void passe1(Programme* programme);
void passe2(Programme* programme);

int main(void) {
   //yydebug = 1;
	Programme* programme = new Programme();
	yyparse(&programme);
	bool error = false;
	cout << "%%%Frontend%%%" << endl;
	programme->Afficher(0);
	
	
	passe1(programme);
	passe2(programme);
	
		


	
	// PASSE 4 qui check les IDs
//	cout <<endl << "PASSE 4";
	if(!programme->checkIDs())
		{
			error = true;
		}
	cout << endl<<"%%%Backend%%%" << endl;

	IR* ir = new IR(programme);
	
	cout << "Fin de l'analyse du programme" << endl;
	return 0;
}


void passe1(Programme* programme) { //test return;
	pair<bool,string> valeursRetour = programme->testReturn();
	if(!valeursRetour.first)
	{
		cout<<"Erreur semantique : erreur de return dans : "<<valeursRetour.second<<endl;
	}	
	
}

void passe2(Programme* programme) { // test main
	bool mainFind = programme->testMain();
	if(!mainFind) 
	{
		cout<<"Erreur semantique : fonction main introuvable"<<endl;
	} 
	
	
}
