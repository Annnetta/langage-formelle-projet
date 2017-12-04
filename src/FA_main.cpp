//******************************************************************************

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>


#include "FA_types.h"
#include "FA_tools.h"

// première partie du projet
#include "Accept.h"
#include "Determinize.h"
#include "ToGraph.h"

// seconde partie du projet

#include "ExpressionRationnelle.h"
#include "parser.hpp"

#include "Minimize.h"
#include "Equivalence.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void test(){
  
  /*int size=3;
  sAutoNDE at1,at2;
  string ato1="AND2";
  string ato2="AND2";
  FromFile(at1, "exemples/" + ato1 + ".txt");
  FromFile(at2, "exemples/" + ato2 + ".txt");
  bool res=PseudoEquivalent(at1, at2, size);
  cout << " PseudoEquivalent?? : " <<(res? "Oui" : "Non") << endl;
  */

/*
  sAutoNDE at1;
  string ato1="ANDE7";
  FromFile(at1, "exemples/" + ato1 + ".txt");
  cout<<at1<<endl;
  cout<<"nb_etats--  "<<at1.nb_etats<<endl;
  cout<<"nb_symbs--  "<<at1.nb_symbs<<endl;
  cout<<"nb_finaux-  "<<at1.nb_finaux<<endl;
  cout<<"finaux init sont  "<<at1.finaux<<endl;
  Minimize(at1);
  
*/

  int nb_total = 17;
   //tester tout les automates
   string liste[] = {"AD1","AD2","AND1","AND2","AND3","AND4","AND5","AND6","AND7","AND8","ANDE1","ANDE2","ANDE3","ANDE4","ANDE5","ANDE6","ANDE7"};

   string reponse;
   bool i=true;

   

   while(i){
      cout<<"Donnez-moi le numero d'automate a tester de 0 a "<<nb_total-1<<endl;
      cout<<"Pour sortir tapez N"<<endl;
      cin>>reponse;
      //system("clear");

      int reponse_int=atoi(reponse.c_str());
      if(reponse.compare("N")!=0 && (reponse_int>=0) && (reponse_int<nb_total)){
        sAutoNDE automate;
        cout<<"---------------"<<endl;
        FromFile(automate, "exemples/" + liste[reponse_int] + ".txt");

        cout<<automate<<endl;
        cout<<"nb_etats--  "<<automate.nb_etats<<endl;
        cout<<"nb_symbs--  "<<automate.nb_symbs<<endl;
        cout<<"nb_finaux-  "<<automate.nb_finaux<<endl;
        cout<<"finaux init sont  "<<automate.finaux<<endl;
        Minimize(automate);

        
        cout<<"----------------------"<<endl;
        cout<<automate<<endl;
        }

      else if (reponse.compare("N")==0){
        i=false;
      }

      else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"Reessayez. Ce numero est inconnu!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
      }
     
    }
    cout<<"##################"<<endl;
    cout<<"#     Bye Bye    #"<<endl;
    cout<<"##################"<<endl;
    
}






//cette fctn est appele si "tester" est passe en parametre dans programme
// ./ndet tester

void tester(){
  
  int nb_total = 17;
   //tester tout les automates
   string liste[] = {"AD1","AD2","AND1","AND2","AND3","AND4","AND5","AND6","AND7","AND8","ANDE1","ANDE2","ANDE3","ANDE4","ANDE5","ANDE6","ANDE7"};

   string reponse;
   bool i=true;

   

   while(i){
      cout<<"Donnez-moi le numero d'automate a tester de 0 a "<<nb_total-1<<endl;
      cout<<"Pour sortir tapez N"<<endl;
      cin>>reponse;
      //system("clear");

      int reponse_int=atoi(reponse.c_str());
      //cout<<"votre reponse -'0'est"<<reponse-'0'<<endl;
      if(reponse.compare("N")!=0 && (reponse_int>=0) && (reponse_int<nb_total)){
        sAutoNDE automate;
        cout<<"---------------"<<endl;
        FromFile(automate, "exemples/" + liste[reponse_int] + ".txt");

        cout<<endl<<"on teste automate: "<< liste[reponse_int] << endl;
        cout << automate << endl;
        cout<<"------------------------------"<<endl;
        
        cout<<"    Essentiel de  "<<liste[reponse_int] <<endl;

        cout<<"nb_etats--  "<<automate.nb_etats<<endl;
        cout<<"nb_symbs--  "<<automate.nb_symbs<<endl;
        cout<<"nb_finaux-  "<<automate.nb_finaux<<endl;
        cout<<"initial---  "<<automate.initial<<endl;
        cout<<"finaux----  "<<automate.finaux<<endl;
        cout<<"trans-----  "<<automate.trans<<endl;
        cout<<"epsilon---  "<<automate.epsilon<<endl;

        cout<<"------------------------------"<<endl;


        //------------Deterministe?-----------

        cout << "Deterministe? : " << ((EstDeterministe(automate))? "Oui" : "Non") << endl;
        cout<<"------------------------------"<<endl;

        

	
        //------------Determiniser--------------
        cout << "Determiniser automate " << endl;
        sAutoNDE automateDet = Determinize(automate);
        cout << "automate determinise est " <<automateDet<<endl;
        cout<<"Verification avec fctn EstDeterministe"<<endl;

        cout <<"deterministe? "<< ((EstDeterministe(automateDet))? "Oui" : "Non")<< endl;
        cout<<"------------------------------"<<endl;



       
        //------------ExisteEtatFinal--------------

        etatset_t fin;
        fin.insert(1);
        fin.insert(0);
        cout << "Est-ce que ds le set" << fin << " il y a les etats finaux-->" << ((ExisteEtatFinal (automate, fin))? "Oui" : "Non") << endl;
        cout<<"------------------------------"<<endl;


	

         //------------Accept--------------
        cout << "Ces mots sont acceptes? "<< endl;

        cout << "Mot vide : " << ((Accept(automate, ""))? "Oui": "Non") << endl;
        cout << "Mot aaa  : " << ((Accept(automate, "aaa"))? "Oui": "Non")  << endl;
        cout << "Mot bbb  : " << ((Accept(automate, "bbb"))? "Oui": "Non")  << endl;
        cout << "Mot aba  : " << ((Accept(automate, "aba"))? "Oui": "Non")  << endl;
        cout << "Mot abb  : " << ((Accept(automate, "abb"))? "Oui": "Non")  << endl;
        cout << "Mot abab : " << ((Accept(automate,"abab"))? "Oui": "Non")  << endl;
        cout << "Mot bab  : " << ((Accept(automate, "bab"))? "Oui": "Non")  << endl;

        cout<<"------------------------------"<<endl;

	 //------------Delta--------------
        etatset_t delta;
        delta.insert(1);
        delta.insert(2);

        cout<<"Verification de Delta depuis des etats {1,2}}(comme exemple) et lettre 'a' et puis 'b'"<<endl;
        cout << "Delta(" << "{1,2}"<< ", a) = " << Delta(automate, delta, 'a') << endl;
        cout << "Delta(" << "{1,2}"<< ", b) = " << Delta(automate, delta, 'b') << endl;
        cout<<"------------------------------"<<endl;

	
        //------------Fermeture--------------
        etatset_t ferm;
        ferm.insert(1);
        ferm.insert(2);
        cout << "Fction fermeture pour etats" << ferm <<endl;

        Fermeture(automate, ferm);
        cout <<"le resultat est "<< ferm <<  endl;
        cout<<"------------------------------"<<endl;



        

      }

      else if (reponse.compare("N")==0){
        i=false;
      }

      else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"Reessayez. Ce numero est inconnu!"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!"<<endl;
      }
     
    }
    cout<<"##################"<<endl;
    cout<<"#     Bye Bye    #"<<endl;
    cout<<"##################"<<endl;
    
}


////////////////////////////////////////////////////////////////////////////////

void Help(std::ostream& out, char *s){
  out << "Utilisation du programme " << s << " :" << std::endl ;
  out << "-acc ou -accept Input Word :\n\t détermine si le mot Word est accepté par l'automate Input" << std::endl;
  out << "-det ou -determinize Input Output [-g] :\n\t déterminise l'automate Input, écrit le résultat dans Output" << std::endl;
  out << "-aut2expr ou automate2expressionrationnelle Input :\n\t calcule l'expression rationnelle correspondant à l'automate Input et l'affiche sur la sortie standard" << std::endl;
  out << "-min ou -minimisation Input Output [-g] :\n\t construit l'automate standard correspondant à Input, écrit le résultat dans Output" << std::endl;
  out << "-pequ ou -pseudo_equivalent Input1 Intput2 size :\n\t détermine si les deux automates Input1 et Input2 sont pseudo-équivalents par comparaison mot par mot de longueur < à size" << std::endl;
  out << "-equ ou -equivalent Input1 Intput2 :\n\t détermine si les deux automates Input1 et Input2 sont équivalents par minimisation et comparaison des tables de transition" << std::endl;
  out << "-nop ou -no_operation Input Output [-g] :\n\t ne fait rien, recopie juste l'entrée dans Output" << std::endl;
  out << "-g :\n\t paramètre optionnel pour avoir une sortie au format Graphviz dans Output" << std::endl;
  out << "\nExemple '" << s << " -determinize auto.txt resultat -g" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[] ){
  if(argc == 2 && strcmp(argv[1], "tester") == 0){ //comparer si le mot donne est egale a "tester"
        tester();
    return EXIT_SUCCESS;
  }

  if(argc == 2 && strcmp(argv[1], "test") == 0){ //comparer si le mot donne est egale a "tester"
        test();
    return EXIT_SUCCESS;
  }
  

  if(argc < 3){
    Help(std::cout, argv[0]);
    return EXIT_FAILURE;
  }
  
  int pos;
  int act=-1;                 // pos et act pour savoir quelle action effectuer
  int nb_ifiles = 0;          // nombre de fichiers en entrée
  int nb_ofiles = 0;          // nombre de fichiers en sortie
  std::string str, in1, in2, out, acc, expr;
  sExpressionRationnelle er;
  unsigned int word_size_max; // pour la pseudo équivalence
  // chaines pour (resp.) tampon; fichier d'entrée Input1; fichier d'entrée Input2;
  // fichier de sortie et chaine dont l'acceptation est à tester 
  bool graphMode=false;     // sortie graphviz ?

  // options acceptées
  const size_t NBOPT = 8;
  std::string aLN[] = {"accept", "determinize", "automate2expressionrationnelle", "minimize", "pseudo-equivalent", "equivalent", "no_operation", "graph"};
  std::string aSN[] = {"acc", "det", "aut2expr", "min", "pequ", "equ", "nop", "g"};
  
  // on essaie de "parser" chaque option de la ligne de commande
  for(int i=1; i<argc; ++i){
    if (DEBUG) std::cerr << "argv[" << i << "] = '" << argv[i] << "'" << std::endl;
    str = argv[i];
    pos = -1;
    std::string* pL = find(aLN, aLN+NBOPT, str.substr(1));
    std::string* pS = find(aSN, aSN+NBOPT, str.substr(1));
    
    if(pL!=aLN+NBOPT)
      pos = pL - aLN;
    if(pS!=aSN+NBOPT)
      pos = pS - aSN;   
      
    if(pos != -1){
      // (pos != -1) <=> on a trouvé une option longue ou courte
      if (DEBUG) std::cerr << "Key found (" << pos << ") : " << str << std::endl;
      switch (pos) {
        case 0: //acc
          in1 = argv[++i];
          acc = argv[++i];
	  nb_ifiles = 1;
	  nb_ofiles = 0;
          break;
        case 1: //det
          in1 = argv[++i];
          out = argv[++i];
	  nb_ifiles = 1;
	  nb_ofiles = 1;
          break;
        case 2: //aut2expr
          in1 = argv[++i];
	  nb_ifiles = 1;
	  nb_ofiles = 0;
          break;
        case 3: //min
          in1 = argv[++i];
          out = argv[++i];
	  nb_ifiles = 1;
	  nb_ofiles = 1;
          break;
        case 4: //pequ
          in1 = argv[++i];
          in2 = argv[++i];
          word_size_max = atoi(argv[++i]);
	  nb_ifiles = 2;
	  nb_ofiles = 0;
          break;
        case 5: //equ
          in1 = argv[++i];
          in2 = argv[++i];
	  nb_ifiles = 2;
	  nb_ofiles = 0;
          break;
        case 6: //nop
          in1 = argv[++i];
          out = argv[++i];
	  nb_ifiles = 1;
	  nb_ofiles = 1;
          break;          
        case 7: //g
          graphMode = true;
          break;
        default:
          return EXIT_FAILURE;
        }
    }
    else{
      std::cerr << "Option inconnue "<< str << std::endl;
      return EXIT_FAILURE;
    }
    
    if(pos<7){
      if(act > -1){
        std::cerr << "Plusieurs actions spécififées"<< std::endl;
        return EXIT_FAILURE;
      }
      else
        act = pos;
    }    
  }
  
  if (act == -1){
    std::cerr << "Pas d'action spécififée"<< std::endl;
    return EXIT_FAILURE;
  }  

/* Les options sont OK, on va essayer de lire le(s) automate(s) at1 (et at2)
et effectuer l'action spécifiée. Atr stockera le résultat*/

  sAutoNDE at1, at2, atr;
  
  // lecture du des fichiers en entrée
  if ((nb_ifiles == 1 or nb_ifiles == 2) and !FromFile(at1, in1)){
    std::cerr << "Erreur de lecture " << in1 << std::endl;
    return EXIT_FAILURE;
  }  
  if (nb_ifiles ==2 and !FromFile(at2, in2)){
    std::cerr << "Erreur de lecture " << in2 << std::endl;
    return EXIT_FAILURE;
  }  
  
  switch(act) {
  case 0: //acc
    if (Accept(at1, acc)){
      std::cout << "'" << acc << "' est accepté : OUI\n";
    }
    else {
      std::cout << "'" << acc << "' est accepté : NON\n";
    }
    break;
  case 1: //det
    atr = Determinize(at1);
    break;
  case 2: //aut2expr
    expr =  Automate2ExpressionRationnelle(at1);
    //cout << "Expression rationnelle résultante (string) : " << expr << std::endl;
    er = lit_expression_rationnelle(expr);
    std::cout << "Expression rationnelle résultante (ASA)    : " << er << std::endl;
    break;
  case 3: //min
    atr =  Minimize(at1);
    break;
  case 4: //pseudo équivalence
    if (PseudoEquivalent(at1,at2,word_size_max)) {
      std::cout << "Après comparaison de tous les mots de longeur < à " << word_size_max << ", les deux automates sont pseudo-équivalents : OUI\n";
    }
    else {
      std::cout << "Après comparaison de tous les mots de longeur < à " << word_size_max << ", les deux automates sont pseudo-équivalents : NON\n";
    }
    break;
  case 5: //equ
    if (Equivalent(at1,at2)){
      std::cout << "les deux automates sont équivalents : OUI\n";
    }
    else {
      std::cout << "les deux automates sont équivalents : NON\n";
    }
    break;
  case 6: //nop
    atr = at1;
    break;
  default:
    return EXIT_FAILURE;
  }

  if (nb_ofiles == 1){
    // on affiche le résultat
    // cout << "Automate résultat :\n----------------\n";
    // cout << atr;

    // écriture dans un fichier texte
    std::ofstream f((out + ".txt").c_str(), std::ios::trunc); 
    if(f.fail())
      return EXIT_FAILURE;
    f << atr;    

    // génération d'un fichier graphviz
    if(graphMode){
      ToGraph(atr, out + ".gv");
      system(("dot -Tpng " + out + ".gv -o " + out + ".png").c_str());
    }
  }
  
  return EXIT_SUCCESS;
}



