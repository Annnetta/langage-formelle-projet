//******************************************************************************
#ifndef EQUIVALENCE_H
#define EQUIVALENCE_H
//******************************************************************************

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>

#include "Accept.h"
#include "FA_types.h"
#include "FA_tools.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

std::string Automate2ExpressionRationnelle(sAutoNDE at);

////////////////////////////////////////////////////////////////////////////////

//Fctn qui verifie si le retour de deux automates est le meme
bool comparer_retour(const sAutoNDE& a1, const sAutoNDE& a2, string mot);

////////////////////////////////////////////////////////////////////////////////

//Fctn recursive qui genere est verifie toutes les cobinaisons des mots
bool print_str(const sAutoNDE& a1, const sAutoNDE& a2, string str,std::string prefix,const int n, const int length);

////////////////////////////////////////////////////////////////////////////////

// détermine la pseudo équivalence par comparaison de tous les mots de Sigma* de longueur < à word_size_max
bool PseudoEquivalent(const sAutoNDE& a1, const sAutoNDE& a2, unsigned int word_size_max);

////////////////////////////////////////////////////////////////////////////////

// détermine l'équivalence par "égalité" des automates :
//   - même nombre d'états
//   - même état initial
//   - mêmes états finaux
//   - même table de transition
// à un renommage des états près
bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2);

//******************************************************************************
#endif // EQUIVALENCE_H
//******************************************************************************
