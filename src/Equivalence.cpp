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
  //TODO définir cette fonction

  return true;
}

//******************************************************************************
