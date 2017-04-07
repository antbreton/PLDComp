#ifndef PLDCOMP_IR_IRVAR_H
#define PLDCOMP_IR_IRVAR_H

#include <iostream>
#include <string>

class IRVar {
public:
	IRVar(std::string nom) : nom(nom){}// Ajouter le type et le nom plus tard
	IRVar(std::string Type, std::string Nom, int unOffset):type(Type),nom(Nom),offset(unOffset) {} ;
	void setOffset(int offsetAdd) {this->offset = offsetAdd;};
	int getOffset() {return offset;};
	int getValeur() {return valeur;};
	std::string getType() {return type;};
	std::string getNom() {return nom;};
	~IRVar();

private:
	std::string type; // Mettre une enum de types ?
	std::string nom; // Le nom de la variable
	int offset; 
	int valeur;
};

#endif // PLD_COMP_IR_IRVAR_H