//******************************************************************************

#include <iostream>
#include <cassert>

#include "Equivalence.h"


////////////////////////////////////////////////////////////////////////////////

std::string Automate2ExpressionRationnelle(sAutoNDE at){
  //TODO définir cette fonction

  std::string sr;

  return sr;
}

////////////////////////////////////////////////////////////////////////////////


bool comparer_retour(const sAutoNDE& a1, const sAutoNDE& a2, string mot){
	if (Accept(a1, mot) ==Accept(a2, mot)){return true;}
	return false;

}


////////////////////////////////////////////////////////////////////////////////

bool print_str(const sAutoNDE& a1, const sAutoNDE& a2, string str,std::string prefix,const int n, const int length){
	
    if (length == 1){

		for (int j = 0; j < n; j++){

			if (comparer_retour(a1, a2, prefix + str[j])==false){return false;}
			cout << prefix + str[j]<< "  est accepte(non accepte) par deux automates? : " << ((comparer_retour(a1, a2, prefix + str[j]))? "Oui" : "Non") << endl;
        }
    }

    else{

        for (int i = 0; i < n; i++){
        	
        	if (print_str(a1, a2, str, prefix+str[i], n, length-1)==false){return false;}
    
       	}

    
    }
    return true;

}

////////////////////////////////////////////////////////////////////////////////

bool PseudoEquivalent(const sAutoNDE& a1, const sAutoNDE& a2, unsigned int word_size_max) {
 
	cout<<"nb_symbs a1--  "<<a1.nb_symbs<<endl;
	cout<<"nb_symbs a2--  "<<a2.nb_symbs<<endl;

	string symboles="";

	//si les symboles ne sont pas les memes -> false
	if(a1.nb_symbs!=a2.nb_symbs){return false;}
	
	else{

		//afficher tous les symboles
		for (unsigned int i=0; i<a1.nb_symbs; i++){
			symboles=symboles+char(i+'a');
		}
		cout<<"les symboles sont "<<symboles<<endl;

		//verifier mot vide
		cout << "Mot vide est accepte? : " << (comparer_retour(a1, a2, " ")? "Oui": "Non") << endl;
		if ((comparer_retour(a1, a2, " "))==false){return false;}


		//verifier autres combinaisons
		for (int k = 1; k <= int(word_size_max); k++){
			if((print_str(a1, a2, symboles,"", a1.nb_symbs, k))==false) {			
				cout<<"Automates ne sont pas pseudoEquivalents." << endl;
				return false;}  
		}

	}
	//sinon -> true
	cout<<"Automates sont pseudoEquivalents." << endl;
  	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2) {

//	- même nombre d'états
//   - même état initial
//   - mêmes états finaux
//   - même table de transition à un renommage des états près

	//etape 1 :Minimiser 2 automates
  sAutoNDE min_a1;
  sAutoNDE min_a2;


  cout<<"-----AUTOMATE 1 ------"<<endl;
  min_a1=Minimize(a1);
  //min_a1=a1;

  cout<<"----- AUTOMATE 2 ------"<<endl;
  min_a2=Minimize(a2);
  //min_a2=a2; 


  	//etape 2: le meme nbre de symboles
  if(min_a1.nb_symbs != min_a2.nb_symbs){
  	cout<<"Le nombre de symboles est different"<<endl;
  	return false;
  }


  //etape 3: même nombre d'états
  if(min_a1.nb_etats!=min_a2.nb_etats){
  	cout<<"Le nombre d'etats est different "<<endl;
  	return false;
  }


  //etape 4: même état initial
  if(min_a1.initial!= min_a2.initial){
  	cout<<"N'ont pas le meme etat initial  "<<endl;
  	return false;
  }


  //etape 5: mêmes nombre des etats finaux
  if(min_a1.nb_finaux!=min_a2.nb_finaux){
  	cout<<"N'ont pas le meme nbre des etats finaux  "<<endl;
  	return false;
  }
  else{

	set<etat_t>::iterator iter_f;
  	for(iter_f=min_a1.finaux.begin(); iter_f!=min_a1.finaux.end(); iter_f++){ //on parcourt tout les etat d'etats finaux
		if(min_a2.finaux.find(*iter_f)==min_a2.finaux.end()) {
			cout<<"N'ont pas les memes etats finaux"<<endl;
			return false;

		}
  	}
  }

 

  //etape 6: même table de transition 


	cout<<"trans"<<min_a1.trans<<endl;
 

	for (size_t i=0; i<min_a1.trans.size(); i++ ){
		for (size_t sym=0; sym<min_a1.trans[i].size(); sym++){
				
			set<etat_t>::iterator iter1, iter2;
			iter1=min_a1.trans[i][sym].begin();
			iter2=min_a2.trans[i][sym].begin();

			if(*iter1==*iter2){
				cout<<"etat "<<i<< " ok"<<endl;
			}

			else{
				cout<<"etat "<<i<<" par symbole "<<char(sym+ASCII_A)<<"  ne correspond pas avec 2eme automate"<<endl;
				return false;
			}
				
		}		
	}
	  				
	

  return true;
}


//******************************************************************************

