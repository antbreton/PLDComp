#include "CFG.h"

using namespace std;


// Constructeur et Destructeur
CFG::CFG(Fonction* fonction)
{
	fonctionDuCFG = fonction;
	this->dicoRegTmp = new map<string, IRVar*>();
	Bloc* bloc = fonctionDuCFG->getBloc();
	
	if(bloc != NULL) { 
	
	cout << "CFG CONSTRUCTEUR" << endl;
	
	// ***************
	// Ajout des paramètres dans les variables
	// ****************
	
	vector<Variable*>* params = fonctionDuCFG->getVariables();
	vector<Variable *>::iterator ite = params->begin() ;
	
	while ( ite != params->end() ) 
	{
		Variable *v = (*ite);
		IRVar* var = new IRVar(v->getType(), v->getIdentifiant(), 0);
		this->addVariable(var);
		ite++;
	}
	
	// ***************
	
	// On recupere la taille total des parametres
	taillePileParam = this->giveOffsets();
		
	BasicBlock* newBasicBlock = new BasicBlock(this, bloc, fonctionDuCFG->getIdentifiant());
	this->addBasicBlock(newBasicBlock);
	
	cout << "CFG CONSTRUCTEUR FIN" << endl;
	nbRegVirtuels = 0;
	
	if(bloc != NULL)
	{
		calculeTaille();
	}
	}
	cout << "CFG CONSTRUCTEUR FIN" << endl;
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
	
	cout << "CFG::genererAssembleur" << endl;
	string codeAssembleur;

	// PROLOGUE
	codeAssembleur += gen_prologue();
cout << "CFG::genererAssembleur 2" << endl;

	// CORPS
	// Pour chaque basicBlock dans le CFG on genere son code assembleur.
  	list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;

  	while (ite != listeBasicBlocks.end()) 
  	{
		codeAssembleur += (*ite)->genererAssembleur();
		ite++;
  	}
	cout << "CFG::genererAssembleur 3" << endl;
	// EPILOGUE
	codeAssembleur += gen_epilogue();

	return codeAssembleur;
}


void CFG::genererIR()
{
	list<BasicBlock *>::iterator ite = listeBasicBlocks.begin() ;

  	while (ite != listeBasicBlocks.end()) 
  	{
		(*ite)->genererIR();
		ite++;
  	}
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
	

	std::map<string, IRVar*>* dico = this->getDicoRegTmp();
	std::map<string, IRVar*>::iterator it;
	
	// ON attribut les offsets aux variables autres que celles des parametres.
	int j = 1;
	if(dico->size() != 0){

		codeAssembleur += "    subq    $"+ to_string(8*dico->size()+taillePileParam) +", %rsp \r\n";

		for(it=dico->begin(); it!=dico->end(); ++it)
		{
			it->second->setOffset(8*j + taillePileParam);
			j++;
		}
	}
	
	// ***************************************
	// Gestion des paramètres
	// ***************************************
	
	vector<Variable*>* params = fonctionDuCFG->getVariables();
	vector<Variable *>::iterator ite = params->begin() ;
	
	while ( ite != params->end() ) {
		
		// On rechoppe les IRVar liées aux parametres de la fonction
        int position = std::distance(params->begin(), ite);
        Variable* v = (*ite);
        IRVar *var = this->getVariable(v->getIdentifiant());		
        
		// On met les registres spéciaux dedans. Ainsi ces registres speciaux sont les registres pour les parametres de la fonction. 
		// Cf IRInstr.cpp 
        switch(position) {
          case 0: codeAssembleur += "    mov    %rdi, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
          case 1: codeAssembleur += "    mov    %rsi, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
          case 2: codeAssembleur += "    mov    %rdx, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
          case 3: codeAssembleur += "    mov    %rcx, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
          case 4: codeAssembleur += "    mov    %r8, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
          case 5: codeAssembleur += "    mov    %r9, "+to_string(var->getOffset())+"(%rbp) \r\n"; break;
        }
        
        ite++;
	}
	codeAssembleur += "\r\n";

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
	fonctionDuCFG->getBloc()->constructor_tableVariables(); //8 octets par variable

	int taille = 8*fonctionDuCFG->getBloc()->tableVariables->size();
	cout << "Debut calcul taille 3" << endl;
	setTaille(taille);
	return taille;
}

std::string CFG::creerNouveauRegistre() {
        string nomRegistreVirtuel = "!r" + to_string(this->nbRegVirtuels) ;
        this->nbRegVirtuels++;

        IRVar* maVar = new IRVar(nomRegistreVirtuel);

        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));

        return nomRegistreVirtuel;
}

std::string CFG::creerNouveauRegistre(int nbRegVirt) {
		std::string nomRegistreVirtuel = "!r" + to_string(nbRegVirt) ;
        IRVar* maVar = new IRVar(nomRegistreVirtuel);
        this->dicoRegTmp->insert(std::pair<std::string, IRVar*>(nomRegistreVirtuel, maVar));
        return nomRegistreVirtuel;
}


// Ajoute un parametre à la map des Parametres.
void CFG::addVariable(IRVar* var) {
    this->variableMap.insert(pair<string,IRVar*> (var->getNom(), var));
}


// GETTER / SETTER

int CFG::getNbRegVirtuels()
{
	return nbRegVirtuels;
}

IRVar* CFG::getVariable(string nom) 
{
    map<string,IRVar*>::iterator varIte;
    varIte = variableMap.find(nom);
    return (varIte->second);
}

IRVar* CFG::getVariableReg(string nom) 
{
    map<string,IRVar*>::iterator varIte;
    varIte = dicoRegTmp->find(nom);
    return (varIte->second);
}

// Permet d'attribuer les offsets à toutes les variables des PARAMETRES.
int CFG::giveOffsets() 
{
    int offset = -8;
    int tailleTotale = 0;
    
    map<std::string,IRVar*>::iterator ite = variableMap.begin() ;
    while ( ite != variableMap.end() ) {
        ite->second->setOffset(offset);

        string type = ite->second->getType();
		
		// Dans notre cas pour l'instant tout les types font 8 bytes. 
		// Ils ne sont pas encore gérés.
		if(type == "INT32") {
			offset -= 8;
			tailleTotale += 8;
		} else if(type == "INT64") {
			offset -= 8;
			tailleTotale += 8;
		} else if(type == "CHAR") {
			offset -= 8;
			tailleTotale += 8;
		} else {
			offset -= 8;
			tailleTotale += 8;
		}
        
        ite++;
    }
    
    return tailleTotale;
    
}

// Renvoi si la variable est un parametre ou non.
bool CFG::estUnParametre(string nomVariable)
{
	map<string,IRVar*>::iterator varIte;
    varIte = variableMap.find(nomVariable);
	if(varIte != variableMap.end())
	{
		return true;
	}
    else {
		return false;
	}
}
