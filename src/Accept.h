//******************************************************************************
#ifndef ACCEPT_H
#define ACCEPT_H
//******************************************************************************
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>

#include "FA_types.h"
#include "FA_tools.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at);

////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e);

////////////////////////////////////////////////////////////////////////////////

void Fermeture_recurif(const sAutoNDE& at, etatset_t& e);

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c);

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str);

///////////////////////////////////////////////////////////////////////////////

bool ExisteEtatFinal (const sAutoNDE& at, const etatset_t& e);

//******************************************************************************
#endif // ACCEPT_H
//******************************************************************************
