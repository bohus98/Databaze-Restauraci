#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "restaurace.h"
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
void Pridat(sRest** Seznam, std::string komentar, std::string jmeno, int hodnoceni, int ID = 0)
{
	sRest* nRest = new sRest() /*(sPrevod*)malloc(sizeof(sPrevod))*/;

	bool undefinedID = (ID == 0);
	if (undefinedID) ID = 1;
	nRest->ID = ID;
	(nRest->komentar) = komentar;
	(nRest->jmeno) = jmeno;
	nRest->hodnoceni = hodnoceni;
	nRest->Dalsi = NULL;

	if (*Seznam == NULL)
	{
		*Seznam = nRest;
	}
	else
	{
		sRest* cRest = *Seznam;
		while (cRest != NULL)
		{
			if (ID <= cRest->ID && undefinedID)
				ID = cRest->ID + 1;
			if (cRest->Dalsi == NULL)
			{
				nRest->ID = ID;
				cRest->Dalsi = nRest;
				break;
			}

			cRest = cRest->Dalsi;
		}
	}
}
void Odebrat(sRest** Seznam, int ID)
{
	sRest* cRest = *Seznam;
	sRest* neRest = cRest;
	while (neRest != NULL)
	{
		if (neRest->ID == ID)
		{
			if (neRest == *Seznam)
			{
				*Seznam = neRest->Dalsi;
				delete neRest;
				break;
			}
			cRest->Dalsi = neRest->Dalsi;
			delete neRest;
			break;
		}
		cRest = cRest->Dalsi;
		if (neRest == *Seznam)
			cRest = *Seznam;
		neRest = cRest->Dalsi;
	}
}
void Uloz(sRest* Seznam)
{
	/*FILE *saveFile;
	saveFile = fopen("rest.bin", "wb");*/
	std::ofstream saveFile;
	saveFile.open("rest.txt", std::ios::out);

	sRest* cRest = Seznam;
	while (cRest != NULL)
	{
		saveFile << cRest->ID << ";" << cRest->jmeno << ";" << cRest->komentar << ";" << cRest->hodnoceni << "\n";
		cRest = cRest->Dalsi;
	}
	/*fclose(saveFile);*/
	saveFile.close();
}
void Upravit(sRest** Seznam, int ID, std::string jmeno, std::string komentar, int hodnoceni)
{
	sRest* cRest = *Seznam;
	while (cRest != NULL)
	{
		if (cRest->ID == ID)
		{
			cRest->hodnoceni = hodnoceni;
			cRest->jmeno = jmeno;
			cRest->komentar = komentar;
			break;
		}

		cRest = cRest->Dalsi;
	}
}
void Nacti(sRest** Seznam)
{
	std::ifstream savefile("rest.txt");
	std::string line;
	while (std::getline(savefile, line))
	{
		std::stringstream   linestream(line);
		std::string         ID, jmeno, komentar, hodnoceni;
		std::getline(linestream, ID, ';');
		std::getline(linestream, jmeno, ';');
		std::getline(linestream, komentar, ';');
		std::getline(linestream, hodnoceni, '\n');
		Pridat(Seznam, jmeno, komentar, std::stoi(hodnoceni), std::stoi(ID));
	}
}