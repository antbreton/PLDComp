#ifndef _Fonction_H
#define _Fonction_H

class Fonction {
	public:
		Fonction(Prototype proto, Bloc bloc): proto(proto), bloc(bloc) {}
		Prototype proto;
		Bloc bloc;
};

class Prototype {
	public:
		Prototype(Type type, List<ParametreDeclar> param, String identifiant): type(type), identifiant(identifiant), param(param) {}
		Type type;
		String identifiant;
		List<ParametreDeclar> param;
};

class ParametreDeclar {
	public:	
		ParametreDeclar(Type type, String identifiant): type(type), identifiant(identifiant) {}
		Type type;
		String identifiant;
};

#endif