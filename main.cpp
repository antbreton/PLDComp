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
	yyparse(&programme);
	
	cout << "%%%Frontend%%%" << endl;
	programme->Afficher(0);
	cout << "%%%Backend%%%" << endl;
	IR* ir = new IR(programme);
	
	cout << "Fin de l'analyse du programme" << endl;
	return 0;
}