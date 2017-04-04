#include "CFG.h"
using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	this->dicoRegTmp = NULL;
	if(fonctionDuCFG->getBloc() == NULL) 
	{cout << "bloc null skdfj" << endl;
	}
	Bloc* bloc = fonctionDuCFG->getBloc();
	if(bloc == NULL) 
	{cout << "bloc null skdfj" << endl;
	}
	cout << sizeof(bloc) << endl;
	BasicBlock* newBasicBlock = new BasicBlock(this, bloc, fonctionDuCFG->getIdentifiant()+"_bb");
	cout << "test"<<endl;
	this->addBasicBlock(newBasicBlock);
	
	nbRegVirtuels = 0;
}

CFG::~CFG()
{
    list<BasicBlock*>::iterator ite;
    for(ite = listeBasicBlocks.begin(); ite!=listeBasicBlocks.end(); ++ite)
    {
        delete *ite;
	}
}



// Methodes

// Ajoute un BasicBlock au CFG
void CFG::addBasicBlock(BasicBlock* newBasicBlock)
{
	this->listeBasicBlocks.push_back(newBasicBlock);
}

// Parcours le CFG et en genere le code assembleur.
string CFG::genererAssembleur() {
		
	// TODO : Chopper la taille de la pile (et l'avoir calculer avant ...)
	string codeAssembleur;

	// PROLOGUE
	codeAssembleur += gen_prologue();


	// CORPS
	// Pour chaque basicBlock dans le CFG on genere son code assembleur.
  	list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;
  	while (ite != listeBasicBlocks.end()) 
  	{
		codeAssembleur += (*ite)->genererAssembleur();
		ite++;
  	}
	
	// EPILOGUE
	codeAssembleur += gen_epilogue();

	return codeAssembleur;
}

std::string CFG::gen_prologue()
{
	string codeAssembleur;
	
	string label = listeBasicBlocks.front()->getLabel();
	string insLabel = label + ":\r\n";

	codeAssembleur += insLabel;
	codeAssembleur += "\r\n";
	codeAssembleur += "    pushq   %rbp \r\n";
	codeAssembleur += "    movq    %rsp, %rbp \r\n";
	  // addq ou subq ? Depend de la pile ? 
	codeAssembleur += "    subq    $"+ to_string(this->calculeTaille()) +", %rsp \r\n";
	codeAssembleur += "\r\n";
	  
	
	//Offset pour chaque variable
	int i = 1;
	std::map<string, IRVar*>* dico = this->getDicoRegTmp();
	std::map<string, IRVar*>::iterator it;
	cout << "La probleme est la" << endl;
	
	// Si il y a au moins une instruction dans le programme
	if(dico != NULL)
	{
		cout << "Le dico n'est pas null" << endl;
		for(it=dico->begin(); it!=dico->end(); ++it)
		{
			cout << "probleme resolu ? " << endl;
			it->second->setOffset(8*i);
			string instructionASM = "movq $" + to_string(it->second->getValeur()) + ", -" + to_string(it->second->getOffset())  +"(%rbp)\r\n";
			codeAssembleur += instructionASM;
			i++;
		}
	}
	cout << "La probleme est la 2 " << endl;
	return codeAssembleur;
}

std::string CFG::gen_epilogue()
{
	string codeAssembleur;

	  codeAssembleur += "\r\n";
	  codeAssembleur += "    leave\r\n";
	  codeAssembleur += "    ret\r\n";
	  codeAssembleur += "\r\n";

	 return codeAssembleur;
}


int CFG::calculeTaille()
{
	
	int taille = 8*getNbRegVirtuels(); //8 octets par variable

	return taille;
}

std::string CFG::creerNouveauRegistre() {
        string nomRegistreVirtuel = "!r" + to_string(this->nbRegVirtuels) ;
        this->nbRegVirtuels++;
		cout << "creerNewReg" << endl;
        IRVar* maVar = new IRVar(nomRegistreVirtuel);
		cout << maVar->getNom() << endl;

        this->dicoRegTmp->insert(make_pair(nomRegistreVirtuel, maVar));
		
		cout << "creerNewReg" << endl;
}




// GETTER / SETTER

int CFG::getNbRegVirtuels()
{
	return nbRegVirtuels;
}
