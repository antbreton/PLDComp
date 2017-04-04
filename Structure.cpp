#include "Structure.h"
#include "Fonction.h"
#include "IR/BasicBlock.h"

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

bool BlocIf::checkIDs()
{
	bool blocIfRes = true;
	bool blocElseRes = true;
	
	if(Bloc *b1 = dynamic_cast<Bloc *>(instrv))
	{
		blocIfRes = b1->checkIDs();
	}
	if(Bloc *b = dynamic_cast<Bloc *>(blocElse))
	{
		blocElseRes = b->checkIDs();
	}
	
	return blocIfRes && blocElseRes;
}

// -------------------------------

// Réalisation StructureControle

StructureControle::StructureControle(Instruction * instrv): instrv(instrv)
{
	instrv->setAncetre(this," st ");
}

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

bool StructureControle::testReturn(bool nullable)
{
	bool returnFind=false;
	if(RetourExpr* expr = dynamic_cast<RetourExpr*>(instrv)) //cherche un return
	{
		if(nullable)//y'a un return qui doit etre null
		{
			if( expr->expr == NULL)
				returnFind = true; 
			else
				returnFind = false;
		}
		else
		{
			if( expr->expr == NULL)
				returnFind = false; 
			else
				returnFind = true;	
		}
	}
	else if ( StructureControle* struc = dynamic_cast<StructureControle*>(instrv) )
	{
		//cout<<"STRUC RECUSIF"<<endl;
		returnFind = struc->testReturn(nullable);
	}
	else if (Bloc* bloc = dynamic_cast<Bloc*>(instrv)) 
	{
		//cout<<"BLOC dans struc"<<endl;
		returnFind = bloc->testReturn(nullable);
	}
		
	return returnFind;	
}

// Réalisation BlocWhile
bool BlocWhile::checkIDs()
{
	bool exprRes = true;
	if(Bloc* bloc = dynamic_cast<Bloc *>(ancetre))
		 exprRes = exprCondition->checkIDs(bloc);	
		 
	return StructureControle::checkIDs() && exprRes;
}



/*
std::string BlocIf::construireIR(CFG *cfg){

	exprCondition→ConstruireIR(cfg);
	BasicBlock * testBB = new BasicBlock(cfg);
	testBB = cfg→currentBB
	BasicBlock * thenBB = new BasicBlock(cfg, instrv);
	BasicBlock * elseBB = new BasicBlock(cfg, blocElse);
	BasicBlock * afterIfBB = new BasicBlock(cfg);
	afterIfBB→succCond = testBB→succCond;
	afterIfBB→succIncond = testBB→succIncond;
	testBB→succCond = thenBB;
	testBB→succIncond = elseBB;
	thenBB→succCond = afterIfBB;
	thenBB→succIncond = NULL;
	elseBB→succCond = afterIfBB ;
	elseBB→succIncond = NULL ;
	cfg→currentBB = afterIfBB;



}
std::string BlocWhile::construireIR(CFG * cfg){
	BasicBlock * beforeWhileBB = cfg→currentBB
	//BasicBlock bodyBB = new BasicBlock(cfg);
	BasicBlock * testBB = new BasicBlock(cfg);
	cfg→currentBB = testBB ;
	exprCondition→ConstruireIR(cfg);
	BasicBlock * bodyBB = new BasicBlock(cfg, instrv);
	BasicBlock * afterWhileBB = new BasicBlock(cfg);
	afterWhileBB→succCond = beforeWhileBB→succCond ;
	afterWhileBB→succIncond = beforeWhileBB→succIncond ;
	testBB→succCond = bodyBB ;
	testBB→succIncond = afterWhileBB ;
	bodyBB→succCond = testBB ;
	bodyBB→succIncond = NULL;
	cfg→currentBB = afterWhileBB;
	
}

*/


