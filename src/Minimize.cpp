//******************************************************************************

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "Minimize.h"

////////////////////////////////////////////////////////////////////////////////




sAutoNDE Minimize(const sAutoNDE& at){
		
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

  etatset_t non_fin; //first
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
  if(!non_fin.empty()){
        classeEquiv.push_back(non_fin); 
    }
  classeEquiv.push_back(fin);
  //classeEquiv.push_back(non_fin);

  int nb_classes;
  int et=0;
  unsigned int nb_classes_avant;


    	//-----CLASSES D'EQUIVALENCE--//

    do{

      //Affichage de Classes d'Equivalence a chaque parcours//
        nb_classes = 0;
        cout << "Equivalence " << et << " : { ";
        et++;
        for(unsigned int j=0; j < classeEquiv.size(); j++){
            cout << classeEquiv[j] << " ";
        }
        cout << "}" <<endl;


        nb_classes_avant = classeEquiv.size();
        
        vector<etatset_t> set_de_classes; // on stoque ici les nouvelles classes a partir de la classe i
        vector<int> liste; //la liste ou on stoque les etats separes

        //on parcours tous les classesd'equivalence
        for(unsigned int i=0; i < classeEquiv.size(); i++){
            int nb_cl_cree = 0; // nb de classes crees
            
            //si la classe contient plus que 1 element, on parcourt tous les elements de cette classe. 
            if(classeEquiv[i].size() > 1){
                for(etatset_t::iterator it = classeEquiv[i].begin(); it != classeEquiv[i].end(); it++){
                    bool ajouter_etat = false;

                    for(unsigned int j=nb_classes; j < set_de_classes.size(); j++){

                        etatset_t::iterator iter = set_de_classes[j].begin(); 
                        unsigned int symb;
                        bool equiv = true; 
                        for(symb=0; equiv && symb < at_det.nb_symbs; symb++){
                            etatset_t::iterator iter1 = at_det.trans[*it][symb].begin();
                            etatset_t::iterator iter2 = at_det.trans[*iter][symb].begin();
                            for(unsigned int k=0; k < classeEquiv.size(); k++){ // On regarde quelles sont les clases des états d'arrivée
                                
                                //si deux etats ne sont pas dans la meme classe ->continuer avec un autre classe d'equivalence
                                if((classeEquiv[k].find(*iter1) == classeEquiv[k].end()) != (classeEquiv[k].find(*iter2) == classeEquiv[k].end())){
                                    equiv = false;
                                    break; break;
                                }
                            }
                        }
                        //si l'etat est bien ds classe j, onl'ajoute dans set des etats (nouveau)
                        if(equiv){ 
                            set_de_classes[j].insert(*it);
                            ajouter_etat = true;
                            break;
                        }
                    }


                    if(!ajouter_etat){ //creer nouvelle classe
                        etatset_t nouveau_class;
                        nouveau_class.insert(*it);
                        //le mettre dans le set des classes
                        set_de_classes.push_back(nouveau_class);
                        nb_cl_cree++;
                    }
                }
            }

            //si il y a qu'unseul element dans la clase
            else{
                set_de_classes.push_back(classeEquiv[i]);
                nb_cl_cree++;
            }
            nb_classes += nb_cl_cree;
        }

        //ilfaut vider la classe d'Equivalence pour nouvelle boucle
        classeEquiv.clear();

        //chaque etat separee on l'ajoute dans set de classes
        for(unsigned int j=0; j < liste.size(); j++){
            set_de_classes.push_back(classeEquiv[liste[j]]); 
        }

        classeEquiv = set_de_classes;

    }while(nb_classes_avant < classeEquiv.size()); //faire tant que le nbre de classes se differe en comparaison avec la classe d'equivalence precedente








	//----Construction d'un automate MINIMALE---//

    cout<<"equivalence finale est :{";
    for(unsigned int i=0; i<classeEquiv.size(); i++){
    	cout<<classeEquiv[i]<<" ";
    }
    cout<<"}"<<endl;

    //Mise a jour de tous les parametres pour automate minimale 

    //misa jour de symboles
    at_min.nb_symbs = at_det.nb_symbs;

    at_min.nb_etats = classeEquiv.size();

    at_min.epsilon.resize(at_min.nb_etats); 

    at_min.trans.resize(at_min.nb_etats);
    for(size_t i=0; i < at_min.nb_etats; i++){
        at_min.trans[i].resize(at_det.nb_symbs);
    }


    //on parcour chaque nouveau etat et on cherche l'information necessaire 
    //renommer les etats du debut; i  - etat de depart
    for(size_t i=0; i < classeEquiv.size(); i++){
        etatset_t::iterator iter = classeEquiv[i].begin(); 


        for(size_t symb=0; symb < at_det.nb_symbs; symb++){
        	// on cherche l'etat d'arrivee pour symbole symb d'etat i
            etatset_t::iterator etat_arrive = at_det.trans[*iter][symb].begin(); 
            //on parcourt encore une fois tous les etats pour trouver l'etat d'arrivee 
            for(size_t j=0; j < classeEquiv.size(); j++){
                if(classeEquiv[j].find(*etat_arrive) != classeEquiv[j].end()){
                    at_min.trans[i][symb].insert(j); 
                    break;
                }
            }
        }


        // ajouter les états finaux
        for(etatset_t::iterator it = at_det.finaux.begin(); it != at_det.finaux.end(); it++){
            if(classeEquiv[i].find(*it) != classeEquiv[i].end()){
                at_min.finaux.insert(i);
                break;
            }
        }

        //etat initial
        if(classeEquiv[i].find(at_det.initial) != classeEquiv[i].end()){
            at_min.initial = i;
        }

    }

    at_min.nb_finaux = at_min.finaux.size();

    cout<<"MINIMISE:"<<endl;
    cout<<at_min<<endl;
    return at_min;

}



//******************************************************************************
