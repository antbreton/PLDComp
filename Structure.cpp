#ifndef _STRUCTURE_CPP
#define _STRUCTURE_CPP
#include "Structure.h"
#include "IR/BasicBlock.h"

std::string BlocIf::construireIR(CFG *cfg){

	exprCondition→ConstruireIR(cfg);
	testBB = cfg→currentBB
	thenBB = new BasicBlock(cfg, instrv);
	elseBB = new BasicBlock(cfg, blocElse);
	afterIfBB = new BasicBlock(cfg);
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
	beforeWhileBB = cfg→currentBB
	bodyBB = new BasicBlock(cfg);
	testBB = new BasicBlock(cfg);
	cfg→currentBB = testBB ;
	exprCondition→ConstruireIR(cfg);
	bodyBB = new BasicBlock(cfg, instrv);
	afterWhileBB = new BasicBlock(cfg);
	afterWhileBB→succCond = beforeWhileBB→succCond ;
	afterWhileBB→succIncond = beforeWhileBB→succIncond ;
	testBB→succCond = bodyBB ;
	testBB→succIncond = afterWhileBB ;
	bodyBB→succCond = testBB ;
	bodyBB→succIncond = NULL;
	cfg→currentBB = afterWhileBB;
	
}



#endif
