//******************************************************************************

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "Minimize.h"

////////////////////////////////////////////////////////////////////////////////


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

  size_t clEquiAvant=classeEquiv.size(); //pour verifier apres la boucle si qqch est change
  cout<<"nb des classes" << clEquiAvant<<endl;

  cout<<"transitions sont"<<at_det.trans<<endl;
  //do{
  	etatset_t vide;
  	//vide.clear();
  	clEquiAvant=classeEquiv.size(); //resize le nbre de classes

  	vector<etatset_t>nouveauxClasses;
  	vector<etatset_t> nouvClassesFin;
    vector<etatset_t> nouvClassesNonFin;
  	//nouvClassesFin=fin;
  	//nouvClassesNonFin=non_fin;

  	for (size_t i=0; i<at_det.trans.size(); i++ ){
  		for (size_t symb=0; symb<at.trans[i].size(); symb++){


  			vide.clear();
  			
  			//si i est dans le classe d'equiv pour les  etats finaux:
  			if ((at_det.finaux.find(i)) != at_det.finaux.end()){
  				
  				etatset_t::iterator iter;
  				iter=at_det.trans[i][symb].begin(); 

  				cout<<*iter<<endl;
  				cout<<"lettre "<<char(symb+ASCII_A)<<" "<< *iter<</*at_det.trans[i][symb]<<*/endl;
  				
  				
  				if((fin.find(*iter)) != fin.end()){
  					cout<<"bien ds classe final"<<endl;
  				}
  				else{
  					cout<<"Pas ds finaux -> separer"<<endl;
  					fin.erase(i);
  					vide.insert(i);
  					nouvClassesFin.push_back(vide);
  				}
  				
  			}


  			//si i est dans le classe d'equiv pour les  etats NON-finaux:
			else if ((at_det.finaux.find(i)) == at_det.finaux.end()){
  				
  				etatset_t::iterator iter;
  				iter=at_det.trans[i][symb].begin(); 

  				cout<<*iter<<endl;
  				cout<<"lettre "<<char(symb+ASCII_A)<<" "<< *iter<</*at_det.trans[i][symb]<<*/endl;
  				
  				
  				if((non_fin.find(*iter)) != non_fin.end()){
  					cout<<"bien ds classe NONfinal"<<endl;
  				}
  				else{
  					cout<<"Pas ds NONfinaux -> separer"<<endl;
  					non_fin.erase(i);
  					vide.insert(i);
  					nouvClassesNonFin.push_back(vide);

  				}
  				
  			}

  			

  			
			/*if(at.trans[i][symb].size()!=1){
				return false;
			}*/
		}
  	}

  	nouvClassesFin.push_back(fin);
  	nouvClassesNonFin.push_back(non_fin);

  	cout<<" nouvClassesFin  "<<nouvClassesFin<<endl;
  	cout<<" nouvClassesNonFin  "<<nouvClassesNonFin<<endl;
			

  //} while(clEquiAvant<classeEquiv.size()); //si on a obtenu le meme nombre de classes -> finir la boucle




  




  return at_min;
}


//******************************************************************************

/*
sAutoNDE Minimize(const sAutoNDE& at){
    sAutoNDE r;
    sAutoNDE nwAuto; // automate at transformé s'il est non déterministe
    vector<etatset_t> equiCl; // les classes d'équivalence

    cout << "Minimize : " << endl;
    if(!EstDeterministe(at)){ // s'il n'est pas déterministe, on le déterminise
        nwAuto = Determinize(at);
    }
    else{
        nwAuto = at;
    }


    etatset_t first;
    for(unsigned int i=0; i < nwAuto.nb_etats; i++){
        if(nwAuto.finaux.find(i) == nwAuto.finaux.end()){ // insert tous les états non finaux
            first.insert(i);
        }
    }

    if(!first.empty()){
        equiCl.push_back(first); // ajoute la classe des non finaux
    }
    equiCl.push_back(nwAuto.finaux); // ajoute la classe des finaux
    unsigned int nbEquiClPre; // Permetra de savoir s'il y a le même nombre de classe entre la liste des classes i et i-1
    int nbClAdd; // nombre de classes déjà ajoutées
    int cpt = 0; // sert juste pour l'affichage (Conpte le numéro d'équivalence qu'on fait)
    




    do{
        nbClAdd = 0;
        cout << "Equivalence " << cpt << " : { ";
        cpt++;
        for(unsigned int d=0; d < equiCl.size(); d++){
            cout << equiCl[d] << " ";
        }
        cout << "}" <<endl;
        nbEquiClPre = equiCl.size();
        vector<etatset_t> nwListCl; // les nouvelle classes crées à partir de la classe i
        vector<int> listSingle; // contiendra la liste des indices des classes contenant un seul état, celle si ne peuvent être équivalentes à aucun état

        for(unsigned int i=0; i < equiCl.size(); i++){
            int nbClAddForCl = 0; // nombre de classes crées dans l'équivalence i pour une classe d'équivalence i-1
            if(equiCl[i].size() > 1){
                for(etatset_t::iterator it = equiCl[i].begin(); it != equiCl[i].end(); it++){
                    bool etatAdd = false;
                    for(unsigned int j=nbClAdd; j < nwListCl.size(); j++){
                        etatset_t::iterator curState = nwListCl[j].begin(); // On regarde seulement le premier état de la liste (car tous les états de cette liste sont équivalents)
                        unsigned int symb;
                        bool equiv = true; // Reste à vrai tant que l'état courrant est équivalent à l'état auquel on le compare
                        for(symb=0; equiv && symb < nwAuto.nb_symbs; symb++){
                            etatset_t::iterator etatArr1 = nwAuto.trans[*it][symb].begin();
                            etatset_t::iterator etatArr2 = nwAuto.trans[*curState][symb].begin();
                            for(unsigned int k=0; k < equiCl.size(); k++){ // On regarde quelles sont les clases des états d'arrivée
                                // Si les 2 états d'arrivés ne sont pas dans la même classe, alors on quitte la boucle pour tester avec le premier état de la classe suivante
                                if((equiCl[k].find(*etatArr1) == equiCl[k].end()) != (equiCl[k].find(*etatArr2) == equiCl[k].end())){
                                    equiv = false;
                                    break; break;
                                }
                            }
                        }
                        if(equiv){ // si l'état appartient à cette classe (classe j)
                            nwListCl[j].insert(*it);
                            etatAdd = true;
                            break;
                        }
                    }
                    if(!etatAdd){ // ajoute une nouvelle classe
                        etatset_t nwCl;
                        nwCl.insert(*it);
                        nwListCl.push_back(nwCl);
                        nbClAddForCl++;
                    }
                }
            }
            else{
                nwListCl.push_back(equiCl[i]);
                nbClAddForCl++;
            }
            nbClAdd += nbClAddForCl;
        }
        equiCl.clear();
        for(unsigned int j=0; j < listSingle.size(); j++){
            nwListCl.push_back(equiCl[listSingle[j]]); // on rajoute les classe contenant un seul état
        }
        equiCl = nwListCl;
    }while(nbEquiClPre < equiCl.size()); // s'il y a le même nombre de classe entre l'équivalence i et i-1 alors on ne peut pas en faire plus, on quitte






    cout << "Equivalence " << cpt << " : { ";
    for(unsigned int d=0; d < equiCl.size(); d++){
        cout << equiCl[d] << " ";
    }
    cout << "}" << endl;

    r.nb_symbs = nwAuto.nb_symbs;
    r.nb_etats = equiCl.size();
    r.epsilon.resize(r.nb_etats); // utile si on fait des opérations sur cet automate par la suite
    r.trans.resize(r.nb_etats);
    for(size_t i=0; i < r.nb_etats; i++){
        r.trans[i].resize(nwAuto.nb_symbs);
    }

    for(size_t i=0; i < equiCl.size(); i++){
        etatset_t::iterator fState = equiCl[i].begin(); // fState : premier état de la classe
        for(size_t symb=0; symb < nwAuto.nb_symbs; symb++){
            etatset_t::iterator arrState = nwAuto.trans[*fState][symb].begin(); // l'état d'arrivé en fonction de l'état fState et du symbole symb
            for(size_t j=0; j < equiCl.size(); j++){
                if(equiCl[j].find(*arrState) != equiCl[j].end()){
                    r.trans[i][symb].insert(j); // i numéro état de départ, j numéro état d'arrivée
                    break;
                }
            }
        }
        // ajoute les états finaux
        for(etatset_t::iterator it = nwAuto.finaux.begin(); it != nwAuto.finaux.end(); it++){
            if(equiCl[i].find(*it) != equiCl[i].end()){
                r.finaux.insert(i);
                break;
            }
        }
        if(equiCl[i].find(nwAuto.initial) != equiCl[i].end()){
            r.initial = i;
        }
    }
    r.nb_finaux = r.finaux.size();

    return r;
}
*/