//******************************************************************************

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "Minimize.h"

////////////////////////////////////////////////////////////////////////////////
bool existe_ou_non ( vector <etatset_t> mon_set, int etat){

	etatset_t sans_parantheses;
	for(size_t i=0; i< mon_set.size(); i++){
		etatset_t::iterator iter;
		
	  		for(iter=mon_set[i].begin(); iter!=mon_set[i].end(); iter++){
	  			sans_parantheses.insert(*iter);
	  		}
  	}
  		cout<<"sans parantheses est "<<sans_parantheses<<endl;
  		if((sans_parantheses.find(etat)) != sans_parantheses.end()){
  			//deja existe
  			return false;
  		}
  	
	return true;

}


bool egalite (sAutoNDE at_det, etatset_t::iterator *iter, vector <etatset_t> mon_set){

    //on va regarder si il y a les memes transitions

    //si oui - > les joindre dans le meme etat
    //non- rien faire

    for (size_t i=0; i<at_det.trans.size(); i++ ){
  		//int count=0;
  		for (size_t symb=0; symb<at_det.trans[i].size(); symb++){
  			//count++;
  			//vide.clear();

  			etatset_t::iterator iter;
  			iter=at_det.trans[i][symb].begin(); 
  			cout<<"lettre "<<char(symb+ASCII_A)<<" "<< *iter<<endl;

  			for (size_t j=0; j<at_det.trans.size(); j++ ){
  			//int count=0;
  				for (size_t symb1=0; symb1<at_det.trans[j].size(); symb1++){
  					etatset_t::iterator iter2;
  					iter2=at_det.trans[j][symb1].begin(); 

  					if(*iter!=*iter2){
  						return false;
  					}
  				}
  			}
  		}
  	}
  	return true;
}

sAutoNDE Minimize(const sAutoNDE& at){
  //TODO définir cette fonction

  sAutoNDE at_min;
  sAutoNDE at_det;

  //automate doit etre deterministe

  cout <<"deterministe? "<< ((EstDeterministe(at))? "Oui" : "Non")<< endl;

  if(!(EstDeterministe(at))) {
  	at_det=Determinize(at);
  }
  else{
  	at_det=at;
  }

  cout<<"-------------------------"<<endl;
  cout << at_det;


  //on definit les classes d'equivalence
  vector <etatset_t> classeEquiv;

  etatset_t non_fin;
  etatset_t fin;


  //etats finaux sont:
  for(size_t i=0; i<at_det.nb_etats; i++){
  	if ((at_det.finaux.find(i)) != at_det.finaux.end()){ //n'existe pas ds finaux
  		fin.insert(i);
  	}
  }

  cout<<"finaux sont: "<<fin<<endl;
  

  //non-finaux
  for(size_t i=0; i<at_det.nb_etats; i++){
  	if ((at_det.finaux.find(i)) == at_det.finaux.end()){ //existe ds finaux
  		non_fin.insert(i);
  	}
  }

  cout<<"non finaux sont: "<<non_fin<<endl;

  //on les ajoute ds classeEquiv. {{finaux}, {non-finaux}}

  classeEquiv.push_back(fin);
  classeEquiv.push_back(non_fin);

  cout<<"Equivalence initiale: "<<classeEquiv<<endl;
 
  //ALGO pour bien construire et verifier les classes d'equivalences:

  //size_t clEquiAvant=classeEquiv.size(); //pour verifier apres la boucle si qqch est change
 // cout<<"nb des classes" << clEquiAvant<<endl;

  cout<<"transitions sont"<<at_det.trans<<endl;
  

	int et=0; 			//pour savoir combien de boucles on a fait
	int nb_classes=0;


	vector<etatset_t>nouveauxClasses;
  	vector<etatset_t> nouvClassesFin;
    vector<etatset_t> nouvClassesNonFin;
    etatset_t vide;





  do{
  	cout<<"==============================="<<endl;
  	et++;



// delete
  /*	vector<etatset_t>nouveauxClasses;
  	vector<etatset_t> nouvClassesFin;
    vector<etatset_t> nouvClassesNonFin;


  	etatset_t vide;

  	*/
  	//vide.clear();


  //	clEquiAvant=classeEquiv.size(); //resize le nbre de classes

  	
  	//nouvClassesFin=fin;
  	//nouvClassesNonFin=non_fin;

  	//int count=0;

  	for (size_t i=0; i<at_det.trans.size(); i++ ){
  		//int count=0;
  		for (size_t symb=0; symb<at_det.trans[i].size(); symb++){
  			//count++;
  			vide.clear();
  			
  			//si i est dans le classe d'equiv pour les  etats finaux:
  			if ((at_det.finaux.find(i)) != at_det.finaux.end()){
  				
  				etatset_t::iterator iter;
  				iter=at_det.trans[i][symb].begin(); 
  				cout<<"lettre "<<char(symb+ASCII_A)<<" "<< *iter<<endl;
  				
  				
  				if((fin.find(*iter)) != fin.end()){
  					cout<<"bien ds classe final"<<endl;
  				}
  				else{
  					
  					if(!fin.empty()){
  						cout<<"Pas ds finaux -> separer"<<endl;
  						fin.erase(i);
  						bool ajouter =existe_ou_non(nouvClassesFin,i);

	  					//if i n'est pas deja ds nouvClassesNonFin:
	  					if(ajouter==true){
		  					vide.insert(i);
	  						nouvClassesFin.push_back(vide);
		  				}
	  					//else {faire rien}
	  					
  					}
  				}
  				
  			}


  			//si i est dans le classe d'equiv pour les  etats NON-finaux:
			else if ((at_det.finaux.find(i)) == at_det.finaux.end()){
  				
  				etatset_t::iterator iter;
  				iter=at_det.trans[i][symb].begin(); 

  				cout<<*iter<<endl;
  				cout<<"lettre "<<char(symb+ASCII_A)<<" "<< *iter<<endl;
  				
  				
  				if((non_fin.find(*iter)) != non_fin.end()){
  					cout<<"bien ds classe NONfinal"<<endl;
  				}
  				else{
  					if(!non_fin.empty()){
	  					cout<<"Pas ds NONfinaux -> separer"<<endl;
	  					non_fin.erase(i);

	  					bool ajouter =existe_ou_non(nouvClassesNonFin,i);

	  					//if i n'est pas deja ds nouvClassesNonFin:
	  					if(ajouter==true){
		  					vide.insert(i);
		  					nouvClassesNonFin.push_back(vide);
		  				}
	  					//else {faire rien}

	  					
	  				}
  				}
  				
  			}
		}
  	}


  	//regarder le reste de fin et Non fin et les ajouter ds nouvClassesFin et nouvClassesNonFin
	
	/*
	if(!fin.empty()){
		
		nouvClassesFin.push_back(fin);
	
	}

  	if(!non_fin.empty()){
		nouvClassesNonFin.push_back(non_fin);
  	}
  	*/


  	//nouveauxClasses.insert(nouvClassesFin);
  	//nouveauxClasses.insert(nouvClassesNonFin);


  	cout<<"etape "<<et<<endl;
	cout<<" nouvClassesFin  "<<nouvClassesFin<<endl;
  	cout<<" nouvClassesNonFin  "<<nouvClassesNonFin<<endl;
	

  	//compter le nbre de classes
  	nb_classes=nouvClassesFin.size() + nouvClassesNonFin.size();
  	cout<<"nbre de classes NEW"<<nb_classes<<endl;

  	

  	//} while(clEquiAvant<classeEquiv.size()); //si on a obtenu le meme nombre de classes -> finir la boucle
	//}while((int)nb_classes<(int)clEquiAvant);
	}while(et<2);


	//-------------------fin WHILE----------------
	//regarder le reste de fin et Non fin et les ajouter ds nouvClassesFin et nouvClassesNonFin
	
	if(!fin.empty()){
		nouvClassesFin.push_back(fin);
	}

  	if(!non_fin.empty()){
  		nouvClassesNonFin.push_back(non_fin);
  	}

  	cout<<" !!!!!!!nouvClassesFin  "<<nouvClassesFin<<endl;
  	cout<<" !!!!!!!!!!nouvClassesNonFin  "<<nouvClassesNonFin<<endl;
	

		

  return at_min;
}



//******************************************************************************
