//******************************************************************************
#ifndef DETERMINIZE_H
#define DETERMINIZE_H
//******************************************************************************
#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <set>
#include <string>

#include "FA_types.h"
#include "Accept.h"
#include "FA_tools.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at);

///////////////////////////////////////////////////////////////////////////////

void Determinize_recursive(const sAutoNDE& atND, sAutoNDE & atD, map_t& m, const etatset_t& e_set, etat_t& e);

//******************************************************************************
#endif // DETERMINIZE_H
//******************************************************************************
