#ifndef PLDCOMP_IR_IRINSTR_H
#define PLDCOMP_IR_IRINSTR_H

#include <iostream>
#include <string>
#include <vector>


class CFG;

class IRInstr {
	public:
		IRInstr();
		~IRInstr();
		
		std::string genererAssembleur();
		CFG* getCFG();
		
	private:
		int mnemoniqueAction; // Les mnemoniques du tableau
		CFG* cfg;
		// TODO : Liste des parametres (les reg, const et label du tableau))

};



#endif //PLDCOMP_IR_IRINSTR_H
