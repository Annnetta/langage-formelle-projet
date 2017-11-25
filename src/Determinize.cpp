//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////
//fctn recursive qui va regarder chaque etat d'automate, 
//et si il n'existe pas ->va ajouter jusqu'a l'automate ne devient deterministe. 
void Determinize_recursive(const sAutoNDE& atND, sAutoNDE & atD, map_t& m, const etatset_t& e_set, etat_t& e){
	
	etatset_t etat_ferme = e_set;
	
	//Fermeture de l'état initial
	if(e == 0){
		Fermeture(atND, etat_ferme);
	}
	
	//on va parcourir le map, si le cas(etat) deja existe ->rien faire, sinon-> "calculer" et ajouter
	std::map<etatset_t, etat_t>::const_iterator it = m.find(etat_ferme);
	
	//Si ne contient pas le cas actuel
	if(!(it != m.end())){
		
		//ajouter nouveau etat ds le map
		m.insert(std::pair<etatset_t, etat_t>(etat_ferme,e));
		
		//incrementer etape a traiter
		e++;
		//on parcourt tout les symboles d'atomate Non deterministe
		for(unsigned int i = 0 ; i < atND.nb_symbs ; i++){

			char lettre=char(i+ASCII_A);
			
			etatset_t etats_delta = Delta(atND, etat_ferme, lettre);
			
			Fermeture(atND, etats_delta);
			
			Determinize_recursive(atND, atD, m, etats_delta, e);
			
			//Mettre a jour tout les parametres d'automate deterministe
			atD.trans.resize(m.size());
			for(auto &it : atD.trans){
				it.resize( atD.nb_symbs );
			}
			atD.trans[ m.find(etat_ferme)->second ][i].insert(m.find(etats_delta)->second);
			for(auto etat : etats_delta){

				//Ajouter l'état ds etats finaux
				if(atND.finaux.count(etat)){
					atD.finaux.insert(m.find(etats_delta)->second);
				}
			}
			
		}
	}
}
	




sAutoNDE Determinize(const sAutoNDE& at){
	
	
	sAutoNDE r;
	map_t map; 
	etat_t etape=0;
	etatset_t init;

	if(!EstDeterministe(at)){
		r.nb_symbs=at.nb_symbs;
		r.initial=0; 
		init.insert(at.initial);
		//on appele la fctn recursive Determinize_recursive
		Determinize_recursive(at, r, map, init, etape);
		//changement de nbre d'etats finaux et etats
		r.nb_etats=map.size();
		r.nb_finaux=r.finaux.size();
		return r;
	}


	cout << "L'automate est deja deterministe." << endl;
    return at;

}