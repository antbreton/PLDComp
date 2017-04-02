//
// Created by lucah on 01/04/2017.
//

#include <iostream>
#include "BasicBlock.h"

BasicBlock::BasicBlock(CFG *cfg, BasicBlock *blocParent, std::string label) {
    this->cfg = cfg;
    this->labelDebut = label;
}

BasicBlock::~BasicBlock() {

}

