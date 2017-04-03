#include "IRInstr.h"
using namespace std;


// Constructeur et Destructeur
IRInstr::IRInstr(CFG* cfg, int mnemonique, vector<string> parametres)
{
	this->cfg = cfg;
    this->mnemonique = mnemonique;
	this->parametres = parametres;
}

IRInstr::~IRInstr()
{

}



// Methodes


string IRInstr::genererAssembleur() {
    //TODO : Pour chaque mnemonique different, generer le code assembleur associe à l'instruction IR ... 

}



// GETTER / SETTER

CFG* IRInstr::getCFG() {
    return cfg;
}

int IRInstr::getMnemonique() {
  return this->mnemonique;
}