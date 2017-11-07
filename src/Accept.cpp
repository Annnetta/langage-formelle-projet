//******************************************************************************

#include <iostream>
#include <algorithm>

#include "Accept.h"
#include "FA_tools.h"

////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at){
  //Automate n'est pas deterministe si: 1) il contient e-transitions
	for(size_t i=0; i<at.epsilon.size(); i++){
		if(!at.epsilon[i].empty()){
			return false;
		}
	}

  //2) si on a plus de deux transitions de l'etat pour la meme lettre 
  //(quand nbre de transitions >nbre de lettres)
	for (size_t etat=0; etat<at.trans.size(); etat++){
	
		for (size_t symb=0; symb<at.trans.size(); symb++){
			if(at.trans[etat][symb].size()!=1){
				return false;
			}
		}
	}

  //sinon
  	return true;
}

////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e){
  //TODO définir cette fonction


}

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c){
  //TODO définir cette fonction
	etatset_t r;
/*
	for (size_t symb=0; symb<at.trans.size(); symb++){
			if(at.trans[e][c].size()!=1){
				
		}

*/
	return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str){
  //TODO définir cette fonction

  return false;
}

//******************************************************************************
