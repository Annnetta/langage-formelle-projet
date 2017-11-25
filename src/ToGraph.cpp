//******************************************************************************

#include "ToGraph.h"

////////////////////////////////////////////////////////////////////////////////



bool ToGraph(sAutoNDE& at, std::string path){
  	// ouvrir le fichier
  	//definir openmode pour ecriture et merge() si deja existe
    std::ofstream file(path.c_str(), std::ios::out | std::ios::trunc);
    if(!file){
		return false;
	}

	file<<"digraph finite_state_machine {"<<endl;
	file<<"\trankdir=LR;" << endl; //noeuds seront dessinees du gauche a droit

	file<<"\tsize=\"10,10\""<<endl<<endl; //dimension de l'image


	//tous les etats finaux sont ds double cercle
	file<<"\tnode [shape = doublecircle]; "; 
	for(etatset_t::iterator it=at.finaux.begin(); it!=at.finaux.end(); it++){
		file<<*it<<" ";
	}
	file << ";"<< endl;

	// etat initial
	file<<"\tnode [shape = point ]; q;"<<endl;

	//etats restants
	file<<"\tnode [shape = circle];"<<endl<<endl;

	//fleche pour etat initial
	file<<"\tq -> "<<at.initial<<";"<<endl;

	//fleches pour les autres etats sauf epsilon
	for(size_t i=0; i < at.trans.size(); i++){	//on parcourt tout les etats 
		for(size_t j=0; j < at.trans[i].size(); j++){ //on parcourt tout les transitions de cet etat
			for(etatset_t::iterator iter = at.trans[i][j].begin(); iter != at.trans[i][j].end(); iter++){
				file << "\t" << i << " -> " <<  *iter << " [label = \"" << (char)(j+ASCII_A) << "\"];" << endl;
			}
		}
	}
	file<<endl;

	//fleches pour epsion-transitions
	for(size_t i=0; i < at.epsilon.size(); i++){	//on parcourt tout les etats 
		for(etatset_t::iterator iter = at.epsilon[i].begin(); iter != at.epsilon[i].end(); iter++){
			file << "\t" << i << " -> " <<  *iter << " [label = \"ε\"];" << endl;
		}
		
	}

	file << "}";
	file.close();	//fermer le fichier

  return true;
}

//******************************************************************************
