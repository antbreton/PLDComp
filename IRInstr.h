//
// Created by lucah on 30/03/2017.
//

#ifndef PLDCOMP_IRINSTR_H
#define PLDCOMP_IRINSTR_H

#include <iostream>
#include <string>
#include <vector>
#include "General.h"
class BasicBlock;
class CFG;

class IRInstr {
public:
    IRInstr();
    ~IRInstr();
    std::string genererAssembleur();
private:
    int mnemoniqueAction; // Les mnemoniques du tableau
    CFG* cfg;
    // TODO : Liste des parametres (les reg, const et label du tableau))

};



#endif //PLDCOMP_IRINSTR_H
