#include "General.h"
#include "Fonction.h"
#include "Structure.h"
#include "IR/IR.h"
#include "test.tab.h"

extern int yydebug;

using namespace std;


int main(void) {
   //yydebug = 1;
	Programme* programme = new Programme();
	
	cout << "Partie Frontend" << endl;
	yyparse(programme);
	cout << "Résultat : " << programme << endl;
	
	cout << "Partie IR - Backend" << endl;
	IR* ir = new IR(programme);

	ir->genererAssembleur();
	
	cout << "Fin de l'analyse du programme" << endl;
	return 0;
}