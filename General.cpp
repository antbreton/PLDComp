#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "IR/CFG.h"
#include "IR/IRInstr.h"
#include <iostream>
#include "Structure.h"

 
using namespace std;

// Méthodes utils
string getTabPrefix(int n)
{
	string tab ="";
	for(int i=0; i<n; i++)
	{
		tab+="\t";
	}
	return tab;
}

// Réalisation Programme ----
Programme::Programme()
{
	fonctions = new vector<Fonction*>();
	bloc 			= new Bloc();
}
bool Programme::checkIDs()
{
	int echec = 0;
	
	for(int i =0; i<fonctions->size(); i++)
	{
		if((*fonctions)[i]->getBloc() != NULL)
			if(!(*fonctions)[i]->getBloc()->checkIDs())
				echec++;
	}
	
	return (echec==0);
}
void Programme::Afficher (int nbtab) 
{
	cout<< endl << endl << endl <<"PROGRAMME // tableSymb size : "<< bloc->getTableSymboles()->size();
	for(int i=0;i<fonctions->size();i++)
	{
		(*fonctions)[i]->Afficher(1);
	}
	cout<<endl<<"END_PROGRAMME"<<endl;
}

void Programme::ajouterListeVariable(vector<Variable*>* listeVariable)
{
	bloc->ajouterListeVariable(listeVariable);
}


// This method set the ancestor
void Programme::setRecursifBlocAncestorToAll()
{
	for(int i=0;i<fonctions->size();i++)
	{
		(*fonctions)[i]->getBloc()->setRecursifBlocAncestorToAll(this->bloc);
	}
}
// --------------------------


pair<bool,string> Programme::testReturn() {
	bool allOK=true;
	pair<bool,string> valeursRetour;
	
	for(int i=0;i<fonctions->size();i++)
	{
		bool tmp = (*fonctions)[i]->testReturn();
		if(!tmp){
			valeursRetour.second = (*fonctions)[i]->id;
			allOK=false;
			break;
		}
	}
	valeursRetour.first = allOK;
	//cout <<"RESULT RETURN :"<<allOK<<endl;
	return valeursRetour;
}

bool Programme::testMain(){
	bool mainFind=false;
	for(int i=0;i<fonctions->size();i++)
	{
		if((*fonctions)[i]->id=="main"){
			mainFind=true;;
			break;
		}
	}
	
	return mainFind;
	
}
std::vector<Fonction*> Programme::getFonctions() 
{
	return *fonctions;
}

 	// Réalisation Variable


Variable::Variable(string id):Identifiable(id), initialisation (false)
{

}

Variable::Variable(string type, string id):Identifiable(id), type(type), initialisation (false)
{
	cerr<< "type : "<<type<<" id : "<<id<<endl;;
}

Variable::Variable(string type, string id, Expression * expr):Identifiable(id), type(type), expr(expr),initialisation (true)
{
	
}
// ----------------------------------

// Réalisation Noeud ----------------
Bloc * Instruction::getParentBloc()
{
	Instruction * currAncetre = ancetre;
	
	while(currAncetre != NULL) // tant qu'il y a un parent
	{
		if(Bloc * bloc = dynamic_cast<Bloc*>(currAncetre) )
		{
			return bloc;
		}
	} 
	
	return NULL;
}
// ----------------------------------

// Réalisation d'Identifiant --------
bool Identifiant::checkExists()
{
	//cout << endl << "checking if "<< (*id) << " exists..." <<endl;
	Bloc * c = getParentBloc();
	
	if(c == NULL)
	{
		//	cout << endl << "pas de bloc père"<<endl;
			return false;
	}
	else
	{
		Identifiable * identifiable = c->getIdentifiableIfExist(*id);
		if(identifiable == NULL)
			return false;
	}
	
	return true;
}

bool Identifiant::checkIDs(Bloc * b)
{
//	cout << "[checking ID " << (*id)<< "]";
	Identifiable * identifiable = b->getIdentifiableIfExist(*id);
	if(identifiable == NULL)
	{
		cout << endl<< "Erreur de résolution de portée : '"<< (*id) << "' est inconnue dans ce scope.";
		return false;
	}
		
	return true;
}
// ----------------------------------


// Réalisation Affectation ---------

bool Affectation::checkIDs(Bloc *c)
{
	identifiant->checkIDs(c);
	valeur->checkIDs(c);
	
	//TODO RETURN;
}

string Expression::construireIR(CFG* cfg) {
	if(OperateurAND* opeAnd = dynamic_cast<OperateurAND*>(this)) {
		
		cerr << "IR : OperateurAnd" << endl;
		
		// Operande 1
		string regGauche = opeAnd->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeAnd->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_AND, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurAnd" << endl;

		return regResultat;

	} else if(OperateurOR* opeOr = dynamic_cast<OperateurOR*>(this)) {
		
		cerr << "IR : OperateurOr" << endl;
		
		// Operande 1
		string regGauche = opeOr->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeOr->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_OR, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurOR" << endl;

		return regResultat;

	} else if(OperateurSup* opeSup = dynamic_cast<OperateurSup*>(this)) {
		
		cerr << "IR : OperateurSup" << endl;
		
		// Operande 1
		string regGauche = opeSup->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeSup->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_GT, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurSup" << endl;

		return regResultat;
		
	} else if(OperateurInf* opeInf = dynamic_cast<OperateurInf*>(this)) {
		cerr << "IR : OperateurInfEgal" << endl;
		// Operande 1
		string regGauche = opeInf->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeInf->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_LT, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurInf" << endl;
		
		return regGauche;

	} else if(OperateurSupEgal* opeSupEgal = dynamic_cast<OperateurSupEgal*>(this)) {
		
		cerr << "IR : OperateurSupEgal" << endl;
		
		// Operande 1
		string regGauche = opeSupEgal->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeSupEgal->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_GE, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurSupEgal" << endl;

		return regResultat;

	} else if(OperateurInfEgal* opeInfEgal = dynamic_cast<OperateurInfEgal*>(this)) {
		cerr << "IR : OperateurInfEgal" << endl;	
		// Operande 1
		string regGauche = opeInfEgal->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opeInfEgal->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_LE, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurInfEgal" << endl;
		
		return regGauche;

	} else if(OperateurEgal* opeEgal = dynamic_cast<OperateurEgal*>(this)) {
		cerr << "IR : OperateurEgal" << endl;
		// Operande 1
		string regGauche = opeEgal->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opeEgal->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_EQ, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurEgal" << endl;
		
        return regGauche;
        
	} else if(OperateurDifferent* opeDiff = dynamic_cast<OperateurDifferent*>(this)) {
		
		cerr << "IR : OperateurDiff" << endl;
		
		// Operande 1
		string regGauche = opeDiff->getMembreGauche()->construireIR(cfg);
		// Operande 2
		string regDroit = opeDiff->getMembreDroit()->construireIR(cfg);
		// Destination
		string regResultat = cfg->creerNouveauRegistre();

		BasicBlock* blocCourant = cfg->getBlockCourant();

		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CMP_DIFF, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurDifferent" << endl;

		return regResultat;
		
	} else if(OperateurPlus* opePlus = dynamic_cast<OperateurPlus*>(this)) {

		cerr << "IR : OperateurPlus" << endl;
		// Operande 1
		string regGauche =opePlus->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opePlus->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		
		vector<std::string> params;
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::ADD, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR : OperateurPlus" << endl;

		return regResultat;

	} else if(OperateurMoins* opeMoins = dynamic_cast<OperateurMoins*>(this)) {

		cout << "IR : OperateurMoins" << endl;
		
		// Operande 1
		string regGauche = opeMoins->getMembreGauche()->construireIR(cfg);

		// Operande 2
		string regDroit = opeMoins->getMembreDroit()->construireIR(cfg);

		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::SUB, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR :  OperateurMoins" << endl;
		
		return regResultat;

	} else if(OperateurMultiplier* opeMult = dynamic_cast<OperateurMultiplier*>(this)) {
		
		cout << "IR : OperateurMultiplier" << endl;

		// Operande 1
		string regGauche = opeMult->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opeMult->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::MUL, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);
		
		cerr << "Fin IR :  OperateurMultiplier" << endl;
		
		return regResultat;

	} else if(OperateurModulo* opeMod = dynamic_cast<OperateurModulo*>(this)) {
		
		cout << "IR : OperateurModulo" << endl;

		// Operande 1
		string regGauche = opeMod->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opeMod->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		// On utilisera l'appel assembleur DIV ou IDIV et on recupera DX ou EDX le reste
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::MOD, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);
		
		cerr << "Fin IR :  OperateurModulo" << endl;
		
		return regResultat;

	} else if(OperateurDivise* opeDiv = dynamic_cast<OperateurDivise*>(this)) {
	
		cout << "IR : OperateurDivise" << endl;

		// Operande 1
		string regGauche = opeDiv->getMembreGauche()->construireIR(cfg);
		
		// Operande 2
		string regDroit = opeDiv->getMembreDroit()->construireIR(cfg);
		
		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Operande 1 - Operande 2
		// On utilisera l'appel assembleur DIV ou IDIV et on recupera DX ou EDX le reste
		params.push_back(regResultat);
		params.push_back(regGauche);
		params.push_back(regDroit);

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::DIV_, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);
		
		cerr << "Fin IR :  OperateurDivise" << endl;
		
		return regResultat;


	} else if(dynamic_cast<Val*>(this)) {
		
		cout<< "IR Val" << endl;

		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Source
		params.push_back(reg);
		params.push_back(to_string( static_cast<Val*>(this)->valeur) );
		
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR :  Val" << endl;

		return reg;

	} else if(dynamic_cast<Caractere*>(this)) {
		
		cout<< "IR Caractere" << endl;

		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Source
		params.push_back(reg);
		params.push_back(to_string((int)(static_cast<Caractere*>(this)->c )));
		
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Construire IR : Classe Caractere" << endl;


		return reg;

	} else if(Not* opeNot = dynamic_cast<Not*>(this)) {
		
		cout << "IR : Not" << endl;
		
		string regExprCourante = opeNot->getExpression()->construireIR(cfg);

		// Destination
		string regResultat = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		
		// Destination - Expression Courante 
		params.push_back(regResultat);
		params.push_back(regExprCourante);
		
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::NOT_, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR :  Not" << endl;
		
		return regResultat;

	} else if(Identifiant* identifiant = dynamic_cast<Identifiant*>(this)) {

		cout << "IR Identifiant" << endl;
		
		BasicBlock* blocCourant = cfg->getBlockCourant();
		string nomVariable = *identifiant->getId();
		string reg = "";
		
		// Si ce n'est pas une variables mappée et que c'est pas un parametre, on ajoute une variable mappee
		if(!blocCourant->estVarMappee(nomVariable) && !blocCourant->getCFG()->estUnParametre(nomVariable))
		{
			cout << "VALEUR NON MAPPEE : " << nomVariable << endl;
			blocCourant->ajouterVariableMappee(cfg, nomVariable);
		}
		
		// Si c'est un paramètre, la destination sera l'offset du registre de ce parametre
		if(blocCourant->getCFG()->estUnParametre(nomVariable))
		{
			int regOffset = blocCourant->getCFG()->getVariable(nomVariable)->getOffset();
			cout << "nomvariable " <<  nomVariable << endl;
			cout << "reg offset " <<  regOffset << endl;
			reg = to_string(regOffset) + "(%rbp)";
		}
		else {	// Registre virtuel de l'identifiant
			reg = "!r" + to_string(blocCourant->getValeurMappee(nomVariable));
		}
		
		cout << "Fin IR : Identifiant" << endl;

		return reg;

	} else if(AppelFonction* appelFonction = dynamic_cast<AppelFonction*>(this)) {
		
		cout << "IR AppelFonction" << endl;
		
		string reg = "";
		string nomFonction = *appelFonction->getIdentifiant()->getId();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		
		if(nomFonction == "putchar")
		{
			vector<Expression *>::iterator i = appelFonction->getParametres()->begin() ;
			Expression *expr = *i;
			string inputVar = expr->construireIR(cfg);
			
			vector<string> params;
			params.push_back("%edi");
			params.push_back(inputVar);
			IRInstr *instr = new IRInstr(IRInstr::Mnemonique::WMEM_SR, blocCourant,params);
			blocCourant->ajouterInstrIR(instr);
			
			vector<string> params2;
			params2.push_back("putchar");
			params2.push_back("inutilisee");
			IRInstr *instr2 = new IRInstr(IRInstr::Mnemonique::CALL,blocCourant,params2);
			blocCourant->ajouterInstrIR(instr2);
		}
		else 
		{
			reg = cfg->creerNouveauRegistre();
			BasicBlock* blocCourant = cfg->getBlockCourant();
			vector<std::string> params;
			
			// Label et destination
			params.push_back(*appelFonction->getIdentifiant()->getId());
			params.push_back(reg);
			
			vector<Expression*>* listeParametresFonction = appelFonction->getParametres();
			for(int i = 0; i < listeParametresFonction->size(); i++)
			{
				Expression* expI = (*listeParametresFonction)[i]; 
				string regI = expI->construireIR(cfg);

				if(Identifiant* identifiant = dynamic_cast<Identifiant*>(expI)) {
					
					string regValIdent = cfg->creerNouveauRegistre();
					
					vector<std::string> paramsI;
					paramsI.push_back(regValIdent);
					paramsI.push_back(regI);
					IRInstr* nouvelleInstrI = new IRInstr(IRInstr::Mnemonique::RMEM, blocCourant, paramsI);
					blocCourant->ajouterInstrIR(nouvelleInstrI);
					
					// Parametre de la fonction
					params.push_back(regValIdent);	
				} 
				else
				{
					params.push_back(regI);	
				}
				
			}

			IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CALL, blocCourant, params);
			blocCourant->ajouterInstrIR(nouvelleInstr);
		}

		cerr << "Fin IR :  AppelFonction" << endl;
		return reg;
		
		

	} else if(Affectation* affectation = dynamic_cast<Affectation*>(this)) {

		cout << "IR : Affectation" << endl;

		BasicBlock* blocCourant = cfg->getBlockCourant();
		string nomVariable = *affectation->getIdentifiant()->getId();
		string reg;

		if(!blocCourant->estVarMappee(nomVariable)){
			blocCourant->ajouterVariableMappee(cfg, nomVariable);
			cerr << "Affectation :: La variable " << nomVariable << " n existe pas : On la cree" << endl;
		} else {
			cerr << "Affectation :: La variable " << nomVariable << " existe  : Valeur : " 
				 << to_string(blocCourant->getValeurMappee(nomVariable))	 << endl;
		}
		
		// Si c'est un parametre, dans ce cas on reprend le registre où il est placé. 
		if(blocCourant->getCFG()->estUnParametre(nomVariable))
		{
			int regOffset = blocCourant->getCFG()->getVariable(nomVariable)->getOffset();
			cout << "nomvariable " <<  nomVariable << endl;
			cout << "reg offset " <<  regOffset << endl;
			reg = to_string(regOffset) + "(%rbp)";
		}
		else 
		{
			reg = "!r" + to_string(blocCourant->getValeurMappee(nomVariable));
		}

			string reg2; 

			if(Val* v = dynamic_cast<Val*>(affectation->getValeur()))
			{
				reg2 = to_string(v->valeur);
			} else if (Caractere* car = dynamic_cast<Caractere*>(affectation->getValeur()))
			{
				//reg2 = car->c;
				reg2 = to_string((int)(static_cast<Caractere*>(car)->c ));
			}
			else {
				reg2 = affectation->getValeur()->construireIR(cfg);
			}

			vector<std::string> params;
			
			params.push_back(reg); // Destination
			params.push_back(reg2); // Source
			
			IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::WMEM, blocCourant, params);
			blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR :  Affectation" << endl;

		return reg;

	} else {
		return "Inconnu";
	}
}

void StructureControle::construireIR(CFG* cfg, vector<Instruction*>::iterator itCourant){
	if(BlocIf* blocPereIf = dynamic_cast<BlocIf*>(this))
	{	
		cerr << "IR : BlocIf" << endl;
		BasicBlock* testBB = cfg->getBlockCourant();
		testBB->bbreak = true;

		//Evaluation la condition de test
		blocPereIf->exprCondition->construireIR(cfg);

		//Creation de l'IR de jne si la condition n'est pas respecte : 
		//vers le blocElse ou vers le blocAfter si pas de Else
		vector<std::string> params;
		string labelAfter = "blocAfter_" + to_string(cfg->getNbBlocAfter());
		string labelElse = "blocELSE_" + to_string(cfg->getNbBlocELSE());
		cfg->incrementerNbBlocELSE();
		cfg->incrementerNbBlocAfter();
		
		

		if(blocPereIf->blocElse != nullptr)
		{
			params.push_back(labelElse);
		} else 
		{
			params.push_back(labelAfter);
		}
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::IF_, testBB, params);
		testBB->ajouterInstrIRJump(nouvelleInstr);
		


		//Creation du BB Then 
		Bloc* bIf = dynamic_cast<Bloc *>(blocPereIf->instrv);
		string blocIF = "blocIF_" + to_string(cfg->getNbBlocIF());
		BasicBlock* thenBB = new BasicBlock(cfg,bIf,blocIF);
		vector<std::string> params2;
		//--Ajout de l'instruction du jmp
		params2.push_back(labelAfter);
		IRInstr* nouvelleInstr2 = new IRInstr(IRInstr::Mnemonique::THEN_, thenBB, params2);
		thenBB->ajouterInstrIRJump(nouvelleInstr2);
		
		//Creation du BB Else
		BasicBlock* elseBB = nullptr;
		if(blocPereIf->blocElse != nullptr)
		{
			Bloc* bElse = dynamic_cast<Bloc *>(blocPereIf->blocElse);
			elseBB = new BasicBlock(cfg,bElse, labelElse);
		}

		//Creation du BB after
		BasicBlock* afterIfBB = new BasicBlock(cfg, NULL, labelAfter);
		//--On recupere les instructions dans le BB courant après le If-Then-else
		vector<Instruction*>* instrAstAfterBB = new vector<Instruction*>(); 
		vector<Instruction*>::iterator it;
		int i = 1;
		for(it=itCourant+1; it !=  testBB->getListeInstructionsAST()->end(); it++)
		{	
			instrAstAfterBB->push_back(*it);
		}
		afterIfBB->setListeInstructionAST(instrAstAfterBB);
		afterIfBB->setMapVarReg(testBB->getMapVarReg());

		//Gestion des successeurs
		afterIfBB->setSuccCond(testBB->getSuccCond());
		afterIfBB->setSuccIncond(testBB->getSuccIncond());


		testBB->setSuccCond(thenBB);
		testBB->setSuccIncond(elseBB);

		if(blocPereIf->blocElse == nullptr)
		{
			thenBB->setSuccCond(afterIfBB);
		} else {
			thenBB->setSuccCond(NULL);
			elseBB->setSuccCond(afterIfBB) ;
			elseBB->setSuccIncond(NULL) ;
		}

		thenBB->setSuccIncond(NULL);

		
		cfg->setBlockCourant(afterIfBB);

		cfg->incrementerNbBlocIF();

		cerr << "Fin IR : BlocIf" << endl;
	} 
	else if (BlocWhile* blocWhilePere = dynamic_cast<BlocWhile*>(this))
	{

		cerr <<  "IR : BlocWhile" << endl;

		BasicBlock * testBB = cfg->getBlockCourant();;
		testBB->bbreak = true;

		//On evalue l'expression
		blocWhilePere->exprCondition->construireIR(cfg);

		//--Ajout de l'instruction jge
		string labelAfter = "blocAfter";
		vector<std::string> params;
		params.push_back(labelAfter);
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::WHILE_, testBB, params);
		testBB->ajouterInstrIRJump(nouvelleInstr);

		//Creation du corps du while
		string labelWhile = "blocWhile";
		Bloc* bWhile = dynamic_cast<Bloc *>(blocWhilePere->instrv);
		BasicBlock* bodyBB = new BasicBlock(cfg,bWhile,labelWhile);
		//--Ajout de l'instruction de jmp pour retourner sur la condition de test
		vector<std::string> params2;
		params2.push_back(labelWhile); //TODO : il faut ajouter un label avant l'instruction cmp, ce parametre n'est pas bon
		IRInstr* nouvelleInstr2 = new IRInstr(IRInstr::Mnemonique::THEN_, bodyBB, params2);
		bodyBB->ajouterInstrIRJump(nouvelleInstr2);

		//Creation du bloc after
		BasicBlock * afterWhileBB = new BasicBlock(cfg);
		//--On recupere les instructions restantes du bloc courant 
		vector<Instruction*>* instrAstAfterBB = new vector<Instruction*>(); 
		vector<Instruction*>::iterator it;
		int i = 1;
		for(it=itCourant+1; it !=  testBB->getListeInstructionsAST()->end(); it++)
		{	
			instrAstAfterBB->push_back(*it);
		}
		afterWhileBB->setListeInstructionAST(instrAstAfterBB);



		//Gestion des successeurs
		afterWhileBB->setSuccCond(testBB->getSuccCond());
		afterWhileBB->setSuccIncond(testBB->getSuccIncond());
		
		testBB->setSuccCond(bodyBB);
		testBB->setSuccIncond(afterWhileBB);
		
		bodyBB->setSuccCond(testBB) ;
		bodyBB->setSuccIncond(NULL);

		cfg->setBlockCourant(afterWhileBB);

		cerr <<  "FIN IR : BlocWhile" << endl;
	}
}
