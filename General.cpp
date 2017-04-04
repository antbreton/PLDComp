#include "General.h"
#include "Expression.h"
#include "Fonction.h"
#include "IR/CFG.h"
#include "IR/IRInstr.h"
#include <iostream>


 
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
	if(dynamic_cast<OperateurAND*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurAND" << endl;
		return "";
	} else if(dynamic_cast<OperateurOR*>(this)) {
		cerr << "TODO : Construire IR : Classe OperatorOR" << endl;
		return "";
	} else if(dynamic_cast<OperateurSup*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurSup" << endl;
		return "";
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

	} else if(dynamic_cast<OperateurSupEgal*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurSupEgal" << endl;
		return "";
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
        
	} else if(dynamic_cast<OperateurDifferent*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurDifferent" << endl;
		return "";
	} else if(OperateurPlus* opePlus = dynamic_cast<OperateurPlus*>(this)) {

		cerr << "IR : OperateurPlus" << endl;
		// Operande 1
		string regGauche = opePlus->getMembreGauche()->construireIR(cfg);
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

		return regGauche;

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
		
		return regGauche;

	} else if(OperateurMultiplier* opeMult = dynamic_cast<OperateurMultiplier*>(this)) {
		
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
		
		cerr << "Construire IR : Classe OperateurMultiplier" << endl;
		
		return regGauche;

	} else if(dynamic_cast<OperateurModulo*>(this)) {
		cerr << "TODO : Construire IR : Classe OperateurModulo" << endl;
		return "";
	} else if(dynamic_cast<OperateurDivise*>(this)) {

		//string reg1 = membreGauche->getType()->construireIR(cfg);
		//string reg2 = membreDroit->construireIR(cfg);

		//string reg3 = creerNouveauRegistre();

		//string ir = reg3 + " <- " + reg1 + " / " + reg2;
		//cfg->ajouterInstruction(ir);

		cerr << "TODO : Construire IR : Classe OperateurDivise" << endl;

		return "";

	} else if(dynamic_cast<Val*>(this)) {
		
		cout<< "IR Val" << endl;

		// Creation d'un registre temporaire
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		params.push_back(reg);
		params.push_back(to_string( static_cast<Val*>(this)->valeur) );
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Fin IR :  Val" << endl;

		return reg;

	} else if(dynamic_cast<Caractere*>(this)) {
		
		cout<< "IR Caractere" << endl;
		
		// Creation d'un registre temporaire
		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;
		params.push_back(reg);
		params.push_back(to_string((int)(static_cast<Caractere*>(this)->c )));
		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::LDCONST, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

		cerr << "Construire IR : Classe Caractere" << endl;

		return reg;

	} else if(dynamic_cast<Not*>(this)) {
		
		cerr << "TODO : Construire IR : Classe Not" << endl;
		
		return "";
	
	} else if(Identifiant* identifiant = dynamic_cast<Identifiant*>(this)) {

		cout << "IR Identifiant" << endl;
		
		BasicBlock* blocCourant = cfg->getBlockCourant();
		string nomVariable = *identifiant->getId();

		if(!blocCourant->estVarMappee(nomVariable)){
			blocCourant->ajouterVariableMappee(cfg, nomVariable);
		}
			// Registre virtuel de l'identifiant
		string reg = "!r" + to_string(blocCourant->getValeurMappee(nomVariable));
		cout << reg << endl;
		cout << "Fin IR : Identifiant" << endl;

		return reg;

	} else if(AppelFonction* appelFonction = dynamic_cast<AppelFonction*>(this)) {
		
		cout << "IR AppelFonction" << endl;

		string reg = cfg->creerNouveauRegistre();
		BasicBlock* blocCourant = cfg->getBlockCourant();
		vector<std::string> params;

		params.push_back(*appelFonction->getIdentifiant()->getId());
		params.push_back(reg);
		vector<Expression*>* listeParametresFonction = appelFonction->getParametres();
		for(int i = 0; i < listeParametresFonction->size(); i++)
		{
			Expression* expI = (*listeParametresFonction)[i]; 
			string regI = expI->construireIR(cfg);

			if(Identifiant* identifiant = dynamic_cast<Identifiant*>(expI)) {
				cerr << "C'est une variable !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				
				string regValIdent = cfg->creerNouveauRegistre();
				
				vector<std::string> paramsI;
				paramsI.push_back(regValIdent);
				paramsI.push_back(regI);
				IRInstr* nouvelleInstrI = new IRInstr(IRInstr::Mnemonique::RMEM, blocCourant, paramsI);
				blocCourant->ajouterInstrIR(nouvelleInstrI);

				params.push_back(regValIdent);	
			} else {
				
				cerr << "regI" << regI << endl;
				params.push_back(regI);	
			}
			
		}

		IRInstr* nouvelleInstr = new IRInstr(IRInstr::Mnemonique::CALL, blocCourant, params);
		blocCourant->ajouterInstrIR(nouvelleInstr);

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
			// Registre leftValue
			// TODO : Dans le poly, il faut ici rajouter un offset
			reg = "!r" + to_string(blocCourant->getValeurMappee(nomVariable));

			//Registre rightValue
			//string reg2 = 	affectation->getValeur()->construireIR(cfg);

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
