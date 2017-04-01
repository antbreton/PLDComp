#ifndef PLDCOMP_IR_IR_H
#define PLDCOMP_IR_IR_H

#include <iostream>
#include <string>
#include <list>
#include "General.h"
#include "CFG.h"


class IR {
	public:
		IR(Programme* programme);
		~IR();;
		
		std::string genererAssembleur();
		void addCFG(CFG* cfg);
		
	private:
		list<CFG *> listeCFG;

};



#endif //PLDCOMP_IR_IR_H