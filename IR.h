//
// Created by lucah on 01/04/2017.
//

#ifndef PLDCOMP_IR_H
#define PLDCOMP_IR_H


#include "CFG.h"

class IR {
public:
    IR(); // L'AST du programme en entree
    ~IR();
    void ajouterCFG();
private:
    // La liste des fonctions du code
    vector<CFG*> listeCFG;
};


#endif //PLDCOMP_IR_H
