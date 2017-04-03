#ifndef PLDCOMP_IR_IRVAR_H
#define PLDCOMP_IR_IRVAR_H

#include <iostream>
#include <string>

class IRVar {
public:
	IRVar(std::string nom) : nom(nom){}// Ajouter le type et le nom plus tard
	~IRVar();

private:
	int type; // Mettre une enum de types ?
	std::string nom; // Le nom de la variable
	int offset; // TODO : Quentin et Nathan en parlaient
};

#endif // PLD_COMP_IR_IRVAR_H