#ifndef _EXPRESSION_H
#define _EXPRESSION_H

class Expression {
	public:
		Expression(){}
		virtual ~Expression() {}	
};

class Val : public Expression {
	public:
		Val(int valeur):Expression(), valeur(valeur) {}
		const int valeur;
};

class Caractere : public Expression {
	public:
		Caractere(char c):Expression(), c(c) {}
		char c;
};

class Not : public Expression {
	public:
		Not(Expression * membre):Expression(), membre(membre) {}
	private:
		Expression * membre;
};

#endif
