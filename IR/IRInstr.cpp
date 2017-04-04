#include <regex>
#include "IRInstr.h"
#include "BasicBlock.h"

//#include "CFG.h"
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
     
	  string codeAssembleur;
	  int nbParametres = this->params.size();
	  cout << "genererAssem IRinstr" << endl;
	  string parametre1 = "";
	  string parametre2 = "";
	  string parametre3 = "";

	  
	  vector<string>::iterator iteParam = params.begin();
	  if(nbParametres >= 1)
	  { 
		parametre1 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 2)
	  {
		parametre2 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 3) 
	  {
		parametre3 = *iteParam;
		iteParam++;
	  }

	  CFG* cfg = blocParent->getCFG();
	  map<string, IRVar*>* dicoRegTmp = cfg->getDicoRegTmp();
	  
	  // MODIFICATION
	  // Si c'est un registre/variable :
	  // On cherche l'offset du parametre, et apres on y ajoute le (%rbp).
	  // Si c'est une constante :
	  // On ajoute un $ devant.
	  // && parametre1[1] == 'r'
	  if(parametre1[0] == '!' ) 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre1)->second;
		int varOffset = variableIR->getOffset();
		parametre1 = to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre1[0])) // Si c'est un entier
	  {
		  parametre1 = "$"+parametre1;
	  }
	  
	  if(parametre2[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre2)->second;
		int varOffset = variableIR->getOffset();
		// to_string est dans le C++11 sinon NumberToString
		parametre2 = to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre2[0]))
	  {
		  parametre2 = "$"+parametre2;
	  }
	  
	  if(parametre3[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre3)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre3 = to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre3[0]))
	  {
		  parametre3 = "$"+parametre3;
	  }
	  
	  
	  switch(mnemoniqueAction) {
		case LDCONST :
		  codeAssembleur += "    movq   "+ parametre2 +", "+parametre1+"\r\n";
		  break;
		  
		case WMEM :
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		  
		case RMEM :
		  codeAssembleur += "    movq    "+ parametre1 +", %rax\r\n";
		  codeAssembleur += "    movq    "+ parametre2 +", %r10\r\n";
		  codeAssembleur += "    movq    %r10, (%rax)\r\n";
		  break;
		  
		case CALL :
		  codeAssembleur += "    call   "+ parametre1 +"\r\n";
		  break;
		  
		case ADD :
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    addq    "+ parametre3 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		  
		  
		/* 
		// les deux sont fait pour la suite
		case SUB :
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    subq    "+ parametre3 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		  
		case MUL :
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    imul   "+ parametre3 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		 */ 
		  
	  }
	  
	return codeAssembleur;

}



// GETTER / SETTER
/*
CFG* IRInstr::getCFG() {
    return cfg;
}
*/
IRInstr::Mnemonique IRInstr::getMnemonique() {
  return this->mnemoniqueAction;
}

