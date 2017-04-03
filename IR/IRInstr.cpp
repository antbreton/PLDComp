#include "IRInstr.h"
#include "BasicBlock.h"
using namespace std;


// Constructeur et Destructeur

IRInstr::IRInstr(Mnemonique mnemonique, BasicBlock* blocParent, std::vector<std::string> params)
{
	this->mnemoniqueAction = mnemonique;
	this->blocParent = blocParent;
	this->params = params;	

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

