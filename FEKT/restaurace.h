#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "stdafx.h"

#pragma warning(disable:4996)
using namespace std;
typedef struct Rest {
	int ID;
	int hodnoceni;
	std::string komentar = "xxxxxxxxxxxxxxx";
	std::string jmeno = "xxxxxxxxxxxxxxx";
	Rest* Dalsi;
} sRest;

sRest* Seznam = NULL;
void Pridat(sRest** Seznam, std::string komentar, std::string jmeno, int hodnoceni, int ID = 0);
void Odebrat(sRest** Seznam, int ID);
void Uloz(sRest* Seznam);
void Upravit(sRest** Seznam, int ID, std::string jmeno, std::string komentar, int hodnoceni);
void Nacti(sRest** Seznam);
