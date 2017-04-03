#ifndef PLDCOMP_IR_IRINSTR_H
#define PLDCOMP_IR_IRINSTR_H

#include <iostream>
#include <string>
#include <vector>


class CFG;
class BasicBlock;
using namespace std;

/*
enum mnemoType {
    MNEMO_CONST = 500,
    MNEMO_PLUS = 501,
    MNEMO_MOINS = 502,
    MNEMO_MULT = 503,
    MNEMO_INF = 504,
    MNEMO_INFEQ = 505,
    MNEMO_SUP = 506,
    MNEMO_SUPEQ = 507,
    MNEMO_DEGAL = 508,
    MNEMO_CALL = 509,
    MNEMO_LECT = 510,
    MNEMO_ECR = 511,
    MNEMO_DIV = 512,
    MNEMO_ECREG = 513,
    MNEMO_NOTEQ = 514,
    MNEMO_MOD = 515,
    MNEMO_AND = 516,
    MNEMO_OR = 517,
    MNEMO_XOR = 518,
    MNEMO_DINF = 519,
    MNEMO_DSUP = 520,
    MNEMO_NOT = 521
};
*/


// Une instruction IR peut etre sous plusieurs formes : une addition (Menomique PLUS), une constante (Mnemonique CONST) etc
// Et selon chaque type d'instruction IR il faut reflechir au code donné en assembleur, cf cours page 20-24
class IRInstr {
	public:
		IRInstr(Mnemonique mnemonique, BasicBlock* blocParent, std::vector<std::string> params);
		~IRInstr();
		
		string genererAssembleur();
		Mnemonique getMnemonique();
		
		typedef enum {
        LDCONST,
        ADD,
        //sub,
        //mul,
        RMEM,
        WMEM,
        CALL,
        //cmp_eq,
        //cmp_lt,
        //cmp_le
    	} Mnemonique;
		
		
	private:
		Mnemonique mnemoniqueAction; // Les mnemoniques du tableau
		BasicBlock* blocParent;
		std::vector<std::string> params;  
		/**< For 3-op instrs: destination, operande1, operande2; 
			 for ldconst: destination, constante;  
			 For call: label, destination, params;  
			 for wmem and rmem: choose yourself ??? */ 

};



#endif //PLDCOMP_IR_IRINSTR_H
