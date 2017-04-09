#ifndef PLDCOMP_IR_IRINSTR_H
#define PLDCOMP_IR_IRINSTR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "IRVar.h"

class BasicBlock;

using namespace std;

		
		
// Une instruction IR peut etre sous plusieurs formes : une addition (Menomique PLUS), une constante (Mnemonique CONST) etc
// Et selon chaque type d'instruction IR il faut reflechir au code donné en assembleur, cf cours page 20-24
class IRInstr {
	public:
		enum Mnemonique{
			LDCONST,
			ADD,
			SUB,
			MUL,
			DIV_,
			MOD,
			CMP_AND,
			CMP_OR,
			NOT_,
			RMEM,
			WMEM,
			WMEM_SR,
			CALL,
			CMP_EQ,
			CMP_LT, // Less than
			CMP_LE, // Less than or Equal
			CMP_GE,	// Greater than or equal
			CMP_GT, // Greater than
			CMP_DIFF, //Different
			IF_,
			THEN_,
			WHILE_
		};
		IRInstr(Mnemonique mnemonique, BasicBlock* blocParent, std::vector<std::string> params);
		~IRInstr();
		
		string genererAssembleur();
		Mnemonique getMnemonique();
		
	private:
		Mnemonique mnemoniqueAction; // Les mnemoniques du tableau
		BasicBlock* blocParent;
		std::vector<std::string> params;
		/**< For 3-op instrs: destination, operande1, operande2; 
			 for ldconst: destination, constante;  
			 For call: label, destination, params;  
			 for wmem and rmem: destination, source */ 

};



#endif //PLDCOMP_IR_IRINSTR_H
