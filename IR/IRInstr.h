#ifndef PLDCOMP_IR_IRINSTR_H
#define PLDCOMP_IR_IRINSTR_H

#include <iostream>
#include <string>
#include <vector>


class CFG;
class BasicBlock;

class IRInstr {
	public:
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
		IRInstr(Mnemonique mnemonique, BasicBlock* blocParent, std::vector<std::string> params);
		~IRInstr();
		std::string genererAssembleur();
		
		
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
