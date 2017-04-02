//
// Created by lucah on 30/03/2017.
//

#ifndef PLDCOMP_CFG_H
#define PLDCOMP_CFG_H

#include <iostream>
#include <string>
#include <vector>
#include "General.h"


class BasicBlock;

// A CFG represente une fonction, contenant un BasicBlock de depart, un de fin
class CFG {
public:
    CFG(Fonction * f);
    ~CFG();
    std::string genererAssembleur();
    void addBasicBlock(BasicBlock* bb);

private:
    vector<BasicBlock* > listeBasicBlocks;
    // TODO : Table des symboles
    Fonction * fonction;


};
#endif //PLDCOMP_CFG_H