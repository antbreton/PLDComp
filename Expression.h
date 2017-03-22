#ifndef _EXPRESSION_H
#define _EXPRESSION_H

class Expression {
	public:
		Expression(){}
		virtual ~Expression() {}	
};

class VAL : Expression {
	public:
		VAL(int valeur):Expression(), valeur(valeur) {}
		const int valeur;
};

class CARACTERE : Expression {
	public:
		CARACTERE():Expression() {}
		const char c;
};

class OperateurUnaire : Expression {
	public:
		OperateurUnaire(Expression * membre):Expression(), membre(membre) {}
	private:
		Expression * membre;
};

#endif
