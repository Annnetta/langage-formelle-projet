//******************************************************************************
#ifndef FA_TYPES_H
#define FA_TYPES_H
//******************************************************************************

#include <vector>
#include <set>
#include <map>

////////////////////////////////////////////////////////////////////////////////

const unsigned int ASCII_A = 97;
const unsigned int ASCII_Z = ASCII_A + 26;
const bool         DEBUG = false;

typedef size_t                              etat_t;
typedef unsigned char                       symb_t;
typedef std::set<etat_t>                    etatset_t;
typedef std::vector<std::vector<etatset_t>> trans_t;
typedef std::vector<etatset_t>              epsilon_t;
typedef std::map<etatset_t, etat_t>         map_t;

////////////////////////////////////////////////////////////////////////////////

struct sAutoNDE{
  // caractéristiques
  size_t nb_etats;
  size_t nb_symbs;
  size_t nb_finaux;

  etat_t initial;
  // état initial

  etatset_t finaux;
  // états finaux : un tableau dynamique comme vector<int>

  trans_t trans;
  // matrice de transition : trans_t est une structure dynamique 3D 
  //comme vector< vector< set<int> > >
 
  
  epsilon_t epsilon; 
  // transitions spontanées : epsilon_t est une structure dynamique 2D 
  //comme vector< set<int> >
};

//******************************************************************************
#endif // FA_TYPES_H
//******************************************************************************
