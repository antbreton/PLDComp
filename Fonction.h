#ifndef _FONCTION_H
#define _FONCTION_H

#include <string> 
#include <list>
#include <vector>

 
using namespace std;
 
class Declaration;

class Bloc {
	public:
		Bloc() {}
		virtual ~Bloc() {}
};

class Type {
	public:
		Type() {}
		virtual ~Type() {}
};


class ParamDeclar {
	public:
		ParamDeclar(vector<Declaration*>* params): params(params) {}
		vector<Declaration*>* params;
};


class Prototype {
	public:
		Prototype(Type* type, vector<Declaration*>* params, string* identifiant) : type(type), params(params), identifiant(identifiant) {}
		Type* type;
		vector<Declaration*>* params;
		string* identifiant;
};



class Fonction {
	public:
		Fonction(Prototype* proto, Bloc* bloc = NULL): proto(proto), bloc(bloc) {}
		Prototype* proto;
		Bloc* bloc;
		virtual ~Fonction() {}
};




#endif