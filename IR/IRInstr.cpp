#include <regex>
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
     
	  string codeAssembleur;
	  int nbParametres = this->params.size();
	  
	  // DE 3 à 8 car seulement 6 registres disponibles pour le call. Un par parametre de la fonction.
	  string parametre1 = "";
	  string parametre2 = "";
	  string parametre3 = "";
	  string parametre4 = "";
	  string parametre5 = "";
	  string parametre6 = "";
	  string parametre7 = "";
	  string parametre8 = "";

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
	  if(nbParametres >= 4) 
	  {
		parametre4 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 5) 
	  {
		parametre5 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 6) 
	  {
		parametre6 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 7) 
	  {
		parametre7 = *iteParam;
		iteParam++;
	  }
	  if(nbParametres >= 8) 
	  {
		parametre8 = *iteParam;
		iteParam++;
	  }


	  CFG* cfg = blocParent->getCFG();
	  map<string, IRVar*>* dicoRegTmp = cfg->getDicoRegTmp();
	  
	  // MODIFICATION
	  
	  // Si c'est un registre/variable :
	  // On cherche l'offset du parametre, et apres on y ajoute le (%rbp).
	  // Si c'est une constante :
	  // On ajoute un $ devant.
	  
	  if(parametre1[0] == '!' ) 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre1)->second;
		int varOffset = variableIR->getOffset();
		parametre1 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre1[0])) // Si c'est un entier
	  {
		  parametre1 = "$"+parametre1;
	  }
	  
	  if(parametre2[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre2)->second;
		int varOffset = variableIR->getOffset();
		cout << endl;
		// to_string est dans le C++11 sinon NumberToString
		parametre2 = "-"+to_string(varOffset)+"(%rbp)";
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
		parametre3 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre3[0]))
	  {
		  parametre3 = "$"+parametre3;
	  }
	  
	  if(parametre4[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre4)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre4 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre4[0]))
	  {
		  parametre4 = "$"+parametre4;
	  }
	  
	  if(parametre5[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre5)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre5 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre5[0]))
	  {
		  parametre5 = "$"+parametre5;
	  }
	  
	  if(parametre6[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre6)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre6 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre6[0]))
	  {
		  parametre6 = "$"+parametre3;
	  }
	  
	  if(parametre7[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre7)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre7 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre7[0]))
	  {
		  parametre7 = "$"+parametre7;
	  }
	  
	  if(parametre8[0] == '!') 
	  {
		IRVar* variableIR = dicoRegTmp->find(parametre8)->second;
		int varOffset = variableIR->getOffset();		
		// to_string est dans le C++11 sinon NumberToString
		parametre8 = "-"+to_string(varOffset)+"(%rbp)";
	  }
	  else if(isdigit(parametre8[0]))
	  {
		  parametre8 = "$"+parametre8;
	  }
	  
	  
	  switch(mnemoniqueAction) {
		case LDCONST :
		  //codeAssembleur += "    LDCONST\r\n";
		  codeAssembleur += "    movl   "+ parametre2 +", "+ parametre1 +"\r\n";
		  break;
		  
		case WMEM :
		//codeAssembleur += "    WMEM\r\n";
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		
		case WMEM_SR :
		//codeAssembleur += "    WMEM SR\r\n";
		  codeAssembleur += "    mov    "+parametre2+", "+parametre1+"\r\n";
		  break;

		case RMEM :
		//codeAssembleur += "    RMEM\r\n";
		  if(parametre1 !="-0(%rbp)"){ codeAssembleur += "    movq    "+ parametre1 +", %rax\r\n"; }
		  codeAssembleur += "    movq    "+ parametre2 +", %rdi\r\n";
		  codeAssembleur += "    movq    %rdi, %rax\r\n";
		  break;
		  
		case CALL :
		//codeAssembleur += "    CALL\r\n";
			if(parametre3 != "") { codeAssembleur += "    mov    "+parametre3+", %rdi \r\n"; }
			if(parametre4 != "") { codeAssembleur += "    mov    "+parametre4+", %rsi \r\n"; }
			if(parametre5 != "") { codeAssembleur += "    mov    "+parametre5+", %rdx \r\n"; }
			if(parametre6 != "") { codeAssembleur += "    mov    "+parametre6+", %rcx \r\n"; }
			if(parametre7 != "") { codeAssembleur += "    mov    "+parametre7+", %r8 \r\n"; }
			if(parametre8 != "") { codeAssembleur += "    mov    "+parametre8+", %r9 \r\n"; }
			codeAssembleur += "    call   "+ parametre1 +"\r\n";
			break;
		  
		case ADD :
		//codeAssembleur += "    ADD\r\n";
		  codeAssembleur += "    movq    "+ parametre2 +", %rax\r\n";
		  codeAssembleur += "    addq    "+ parametre3 +", %rax\r\n";
		  codeAssembleur += "    movq    %rax, "+ parametre1 +"\r\n";
		  break;
		  
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
		
		case CMP_EQ :
		  codeAssembleur += "    movq    "+parametre2+", %rax \r\n";
		  codeAssembleur += "    xor    "+parametre3+", %rax\r\n"; // bit a 1 si different, bit a 0 si egal.
		  codeAssembleur += "    cmpq   $0, %rax \r\n"; // Est ce que Rax est a 0, si c'est a 0 c'est egal
		  codeAssembleur += "    sete   %al \r\n";   // SETE = Set byte if equal ; AL is the lower 8 bits : Tous les bits de al passe a 1 si ils sont egaux
		  codeAssembleur += "    movzbq %al, %rax \r\n"; // MOV, zero extend, Byte to Long : On étend ça a tout le %rax.
		  codeAssembleur += "    movq    %rax, "+parametre1+" \r\n";
		  
		  
		  
		//  codeAssembleur += "	test	"+parametre1+", "+parametre2+"\r\n"; 
		  
		  break;
		  
		case CMP_LT :
		  codeAssembleur += "    movq    "+parametre2+", %rax \r\n";
		  codeAssembleur += "    cmp    "+parametre3+", %rax \r\n";
		  codeAssembleur += "    setl   %al  \r\n";  // SETL = Set byte if less
		  codeAssembleur += "    movzbl %al, %rax \r\n";
		  codeAssembleur += "    movq    %rax, "+parametre1+" \r\n";
		  break;
		  
		case CMP_LE :
		  codeAssembleur += "    movq    "+parametre2+", %rax \r\n";
		  codeAssembleur += "    cmp    "+parametre3+", %rax \r\n";
		  codeAssembleur += "    setle   %al  \r\n"; // SETLE  = Set byte if less or equal 
		  codeAssembleur += "    movzbl %al, %rax \r\n";
		  codeAssembleur += "    movq    %rax, "+parametre1+" \r\n";
		  break;

		case IF_ : // instruction apres la condition de test
			codeAssembleur += "    jne " + parametre1 + "\r\n";
			break;

		case THEN_ :
			codeAssembleur += "    jmp " + parametre1 + "\r\n";
			break;
		  
	  }
	  
	return codeAssembleur;

}



// GETTER / SETTER

IRInstr::Mnemonique IRInstr::getMnemonique() {
  return this->mnemoniqueAction;
}

