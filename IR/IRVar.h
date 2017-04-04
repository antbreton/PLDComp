#ifndef PLDCOMP_IR_IRVAR_H
#define PLDCOMP_IR_IRVAR_H

#include <iostream>
#include <string>

class IRVar {
public:
	IRVar(std::string nom) : nom(nom){}// Ajouter le type et le nom plus tard
	void setOffset(int offset) {offset = offset;};
	int getOffset() {return offset;};
	int getValeur() {return valeur;};
	std::string getNom() {return nom;};
	~IRVar();

private:
	int type; // Mettre une enum de types ?
	std::string nom; // Le nom de la variable
	int offset; // TODO : Quentin et Nathan en parlaient
	int valeur;
};

#endif // PLD_COMP_IR_IRVAR_H