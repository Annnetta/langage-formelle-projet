//******************************************************************************

#include "Accept.h"

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
	
		for (size_t symb=0; symb<at.trans[etat].size(); symb++){
			if(at.trans[etat][symb].size()!=1){
				return false;
			}
		}
	}

  //sinon
  	return true;
}



////////////////////////////////////////////////////////////////////////////////



void Fermeture_recurisif(const sAutoNDE& at, etatset_t& e){
//fctn recursive qui prend plus de calcule que iteratif
  
  etatset_t copy=e; //on copie l'ensemble des etats e dans copy

  etatset_t::iterator iter;
  //il faut parcourir tout les etats de transitions spontanées epsilon
  for (size_t i=0; i<at.epsilon.size(); i++ ){
  	//si ensemble de epsilon n'est pas vide ET cet etat existe dans l'ensemble des etats e, il faut ajouter cet element ds e
  	if((e.count(i)!=0) && (!at.epsilon[i].empty())){
  		for(iter=at.epsilon[i].begin(); iter!=at.epsilon[i].end(); iter++){
  			if(e.count(*iter)==0) { e.insert(*iter);}//n'existe->ajouter
  		}
  }
}
	//si il n'y a aucune difference entre ensemble des etats initials (copy) et (e)->finir
 	//sinon->continuer la recursion
  if(copy!=e) {Fermeture(at, e);}
  
	
}



////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e){
//fctn iteratif qui prend mains de calcule que recursif
  
  etatset_t copy=e; //on copie l'ensemble des etats e dans copy, sera change chaque fois
  etatset_t::iterator iter;
  	
  do{
  	etatset_t inter; //liste intermediaire pour epsilon transitions 
  	//il faut parcourir tout les etats de transitions spontanées epsilon
  	for (size_t i=0; i<at.epsilon.size(); i++ ){
  	//si ensemble de epsilon n'est pas vide ET cet etat existe dans l'ensemble des etats e, il faut ajouter cet element ds e
	  	if((e.count(i)!=0) && (!at.epsilon[i].empty())){
	  		for(iter=at.epsilon[i].begin(); iter!=at.epsilon[i].end(); iter++){
	  			if(e.insert(*iter).second){ //si n'existe->ajouter
	  				inter.insert(*iter);
	  			}
	  		}
	  	}
	}

	copy=inter; //pour calculer de nouveau avec nouveaux etats
	}while(!copy.empty());
  
	
}





////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c){
  
	
	etatset_t r;	//liste des etats de delta
	size_t numero_symb=c-ASCII_A;	//numero de symbole c comptant a partir de lettre a
	if(at.nb_symbs<numero_symb){
		return r; 	//il n'y a pas de transitions avec symbole c
	}

	else{
			for (size_t i=0; i<at.trans.size(); i++ ){
				if((e.count(i)!=0) && (!at.trans[i][numero_symb].empty())){   	///si ensemble n'est pas vide ET transition c existe
	  				set<etat_t>::iterator iter;
	  				for(iter=at.trans[i][numero_symb].begin(); iter!=at.trans[i][numero_symb].end(); iter++){
						r.insert(*iter);
						}
				}		
			
			}
			
	}
	Fermeture(at,r);
	return r;

}
	
	
////////////////////////////////////////////////////////////////////////////////
/*fctn qui verifie si etatset_t e contient les etats finaux d'automate*/
bool ExisteEtatFinal (const sAutoNDE& at, const etatset_t& e){
	
	set<etat_t>::iterator iter_e;
	set<etat_t>::iterator iter_f;
	for(iter_f=at.finaux.begin(); iter_f!=at.finaux.end(); iter_f++){ //on parcourt tout les etat d'etats finaux
		iter_e=e.find(*iter_f); //on  verifie si e contient au moins 1 element de etats finaux
		if(iter_e!=e.end()) {
			//cout<<"found?"<<*iter_e<<endl; //si oui->true
			return true;
		}
	}	//pas trouvee
	return false;
	
}
/*Tests ExisteEtatFinal
pour automate AND2 (etats finaux 0 et 2)
ExisteEtatFinal(automate,{1,3})=>false
ExisteEtatFinal(automate,{0,2})=>true
ExisteEtatFinal(automate,{0,3})=>true
*/


///////////////////////////////////////////////////////////////////////////////
bool Accept(const sAutoNDE& at, std::string str){
  
	etatset_t inter;
	inter.insert(at.initial); //on met ds etat intermediaire inter etat initial
	int k=0;
	Fermeture(at, inter);
	while(str[k]!='\0'){
		//for(unsigned int i=0; i<=str.length(); i++){
		inter= Delta(at, inter, str[k]);
        // si inter est vide, alors il n y a pas aucune transition =>false
	        if(inter.empty()){
	            return false;
	        }
	        k++;	
	}
	//si inter bien contient un des etat final=>accepter le mot
	if(ExisteEtatFinal(at, inter)){return true;}
	
  	return false;	//sinon
  	
}

