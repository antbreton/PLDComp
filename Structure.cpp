#include "Structure.h"

// Réalisation bloc if ----------
BlocIf::BlocIf(Expression * expr, Instruction * instrv, Instruction * blocElse):StructureControle(instrv), exprCondition(expr), blocElse(blocElse)
{

}

void BlocIf::setRecursifBlocAncestorToAll(Bloc * bloc)
{
		StructureControle::setRecursifBlocAncestorToAll(bloc);
		
		// On gère le bloc else
		// Si l'instruction de la structure est un bloc, on la setRecursivement
		if( Bloc * b = dynamic_cast<Bloc*>(bloc) )
		{
			b->setRecursifBlocAncestorToAll(b);
		}	// Si c'est une structure de controle on la set Récursivement
		else if( StructureControle * stru = dynamic_cast<BlocIf*>(instrv) )
		{
			stru->setRecursifBlocAncestorToAll(bloc);
		}
}
// -------------------------------

// Réalisation StructureControle
void StructureControle::setRecursifBlocAncestorToAll(Bloc * bloc)
{
		// Si l'instruction de la structure est un bloc, on la setRecursivement
		if( Bloc * b = dynamic_cast<Bloc*>(instrv) )
		{
			b->setRecursifBlocAncestorToAll(bloc);
		}	// Si c'est une structure de controle on la set Récursivement
		else if( StructureControle * stru = dynamic_cast<BlocIf*>(instrv) )
		{
			stru->setRecursifBlocAncestorToAll(bloc);
		}
}
