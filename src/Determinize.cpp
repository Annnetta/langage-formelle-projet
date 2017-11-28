//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////
//fctn recursive qui va regarder chaque etat d'automate, 
//et si il n'existe pas ->va ajouter jusqu'a l'automate ne devient deterministe. 
/*
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

*/


string toStringEtatset(etatset_t e){
    string str = "{";

    for(etatset_t::iterator it = e.begin(); it != e.end(); it++){
        stringstream ss;
        if(it != e.begin()){
            str += ",";
        }
        ss << *it;
        str += ss.str();
    }
    str += "}";
    return str;
}


sAutoNDE Determinize(const sAutoNDE& at){
	cout << at;
    sAutoNDE rAutoD; // automate déterminisé

    if(!EstDeterministe(at)){
        map_t corespEtat; // fait la correspondance entre le numéro d'état dans rAutoD, et les états qu'il représente dans at
        map_t fermeture; // pas très utile, seulement pour l'affichage (Pas obligatoire)
        rAutoD.nb_symbs = at.nb_symbs;
        rAutoD.nb_finaux = 0;

          //////////////////////////////////////////////////////////////////////////////////////////
         ////                             Les epsilon Fermeture                                ////
        //////////////////////////////////////////////////////////////////////////////////////////
        cout << "Epsilon-fermeture:" << endl;
        for(size_t i=0; i < at.nb_etats; i++){
            etatset_t tmp; // contient l'état dont on doit calculer la fermeture
            tmp.insert(i);
            Fermeture(at, tmp);
            pair<std::map<etatset_t,etat_t>::iterator,bool> res; // permet d'avoir un retour sur la méthode insert
            res = fermeture.insert(pair<etatset_t, etat_t>(tmp, i));
            cout << "   E(" << i << ") = " << tmp;
            // si cette fermeture existe déjà, on ne rajoute pas d'état dans l'automate final
            if(!res.second){
                cout << " = E(" << res.first->second << ")"; // map_t fermeture sert seulement à cet affichage, n'est pas très utile
            }
            else if(i == at.initial){
                corespEtat.insert(pair<etatset_t, etat_t>(tmp, 0)); // on ajoute seulement l'état initial
                // seulement l'élément initial est testé si final, les autres états seront testés après(Pour éviter aussi que la poubelle sooit ajoutée en final dans certains cas)
                if(ExisteEtatFinal (at, tmp)){
                    rAutoD.finaux.insert(0); // ajoute l'état actuel comme final
                }
                // l'état initial de M' est la e-fermeture de l'état initial de M
                // si la e-fermeture de M est déja dans la map, l'état initial de M' à l'état déjà dans la map
                // sinon l'état init de M' est le nouvel état ajouté, le retour de l'insert permet de réaliser cette condition
                rAutoD.initial = 0;
            }
            cout << endl;
        }

          //////////////////////////////////////////////////////////////////////////////////////////
         ////                             Delta                                                ////
        //////////////////////////////////////////////////////////////////////////////////////////
        map_t tmpMap1 = corespEtat;	// map temporaire permettant d'enregistrer les états dès qu'on se déplace dans l'automate
        map_t tmpMap2;
        string str = ""; 			// contiendra des infos sur les transisions, sera affichée à la fin de la fonction

        while(!tmpMap1.empty()){
            for(map_t::iterator itM = tmpMap1.begin(); itM != tmpMap1.end(); itM++){
                for(size_t i=0; i < rAutoD.nb_symbs; i++){
                    pair<std::map<etatset_t,etat_t>::iterator,bool> res;
                    etatset_t deltaRes = Delta(at, itM->first, (char)(i+ASCII_A));
                    res = corespEtat.insert(pair<etatset_t, etat_t>(deltaRes, corespEtat.size()));
                    // on enregistre la transition et redimentionnement dynamique de la liste des transitions
                    // itM->second : numéro de l'état d'où on vient
                    // i : le caractère de transition
                    // res.first->second : l'état ou l'on va
                    if(itM->second >= rAutoD.trans.size()){
                        int taillePre = rAutoD.trans.size();
                        rAutoD.trans.resize(itM->second+1);
                        for(size_t j=taillePre; j < rAutoD.trans.size(); j++){
                            rAutoD.trans[j].resize(at.nb_symbs); // laisse la place pour tout les symboles
                        }
                        rAutoD.trans[itM->second][i].insert(res.first->second);
                    }
                    else{
                        rAutoD.trans[itM->second][i].insert(res.first->second);
                    }
                    str += "   delta(";
                    str += toStringEtatset(itM->first);
                    str += ", ";
                    str += (char)(i+ASCII_A);
                    str += ") = ";
                    str += toStringEtatset(res.first->first);
                    str += "\n";
                    if(res.second){ // si on a un nouvel ensemble
                        tmpMap2.insert(pair<etatset_t, etat_t>(deltaRes, res.first->second));
                        if(ExisteEtatFinal (at, deltaRes)){
                            rAutoD.finaux.insert(res.first->second);
                        }
                    }
                }
            }
            tmpMap1 = tmpMap2;
            tmpMap2.clear();
        }

        rAutoD.nb_etats = corespEtat.size();
        rAutoD.nb_finaux = rAutoD.finaux.size();
        cout << endl << "Nouveau etats (" << rAutoD.nb_etats << ") :" << endl;
        for(map_t::iterator itM = corespEtat.begin(); itM != corespEtat.end(); itM++){
            cout << "   " << itM->second << " : " << itM->first;
            if(itM->second == rAutoD.initial){
                cout << " (initial)";
            }
            if(rAutoD.finaux.find(itM->second) != rAutoD.finaux.end()){
                cout << " (final)";
            }
            cout << endl;
        }

        cout << endl << "Nouvelles transitions : " << endl;
        cout << str << endl; // affiche les transitions
        rAutoD.epsilon.resize(rAutoD.nb_etats); // prend de la place, mais simplifie s'il faut faire des oprérations sur les epsilon après
        return rAutoD;
    }
    cout << "L'automate est deja deterministe." << endl;
    return at;
}
