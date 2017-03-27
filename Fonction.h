#ifndef _FONCTION_H
#define _FONCTION_H

#include "General.h"
#include <string> 
#include <list>
 
using namespace std;
 


class Bloc : public InstructionV  {
	public:
		Bloc() {}
		virtual ~Bloc() {}
};

class Type {
	public:
		Type() {}
		virtual ~Type() {}
};

class ParametreDeclar {
	public:	
		ParametreDeclar(Type type, string identifiant): type(type), identifiant(identifiant) {}
		Type type;
		string identifiant;
		virtual ~ParametreDeclar() {}
};

class Prototype {
	public:
		Prototype(Type type, list<ParametreDeclar> param, string identifiant): type(type), identifiant(identifiant), param(param) {}
		Type type;
		string identifiant;
		list<ParametreDeclar> param;
		virtual ~Prototype() {}
};

class Fonction {
	public:
		Fonction(Prototype proto, Bloc bloc): proto(proto), bloc(bloc) {}
		Prototype proto;
		Bloc bloc;
		virtual ~Fonction() {}
};




#endif
