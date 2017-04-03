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
	yyparse(&programme);
	cout<< "size : "<<programme->getFonctions().size()<<endl;;
	
	cout << "Partie IR - Backend" << endl;
	IR* ir = new IR(programme);

	cout << ir->genererAssembleur() << endl;
	
	cout << "Fin de l'analyse du programme" << endl;
	
	delete programme;
	delete ir;
	
	return 0;
}
