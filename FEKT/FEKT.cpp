
#include <stdlib.h>
#include <stdio.h>
#include "stdafx.h"
#include <string>
#include <ctype.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#pragma warning(disable:4996)
typedef struct Rest {
	int ID;
	int hodnoceni;
	std::string komentar = "xxxxxxxxxxxxxxx";
	std::string jmeno = "xxxxxxxxxxxxxxx";
	Rest *Dalsi;
} sRest;

sRest *Seznam = NULL;

void Pridat(sRest **Seznam, std::string komentar, std::string jmeno, int hodnoceni, int ID = 0)
{
	sRest *nRest = new sRest() /*(sRest*)malloc(sizeof(sRest))*/;

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
		sRest *cRest = *Seznam;
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
void Odebrat(sRest **Seznam, int ID)
{
	sRest *cRest = *Seznam;
	sRest *neRest = cRest;
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
	saveFile = fopen("rest.txt", "wb");*/
	std::ofstream saveFile;
	saveFile.open("rest.txt", std::ios::out);

	sRest *cRest = Seznam;
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
	sRest *cRest = *Seznam;
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
void Nacti(sRest **Seznam)
{
	std::ifstream savefile("rest.txt");
	std::string line;
	while (std::getline(savefile, line))
	{
		std::stringstream   linestream(line);
		std::string         ID,jmeno,komentar,hodnoceni;
		std::getline(linestream, ID, ';');
		std::getline(linestream, jmeno, ';');
		std::getline(linestream, komentar, ';');
		std::getline(linestream, hodnoceni, '\n');
		Pridat(Seznam, jmeno, komentar, std::stoi(hodnoceni), std::stoi(ID));
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int volba;
	Nacti(&Seznam);
	

	do {
		system("cls");
		system("color 06");
	noclear:
		printf("\nPrace s databazi restaracnich zarizeni\n");
		printf("Vyberte akci:\n (1)pridat\n (2)odebrat\n (3)upravit\n (4)zobrazit\n (5)vyhledat\n (6)setridit\n (0)konec \n");
		fflush(stdin);
		volba = getchar();
		fflush(stdin);

		switch (volba)
		{
		case '1':
		{
					float hodnoceni;
					std::string komentar, jmeno;
					printf("Zadejte jmeno: ");
					std::cin >> jmeno;
					printf("Zadejte hodnoceni: ");
					scanf("%d", &hodnoceni);
					printf("Zadejte komentar: ");
					std::cin >> komentar;
					fflush(stdin);
					Pridat(&Seznam, jmeno, komentar, hodnoceni);
		} break;

		case '2':
		{
			printf("Zorazeni parametru:\n ID, Jmeno, Komentar, Hodnoceni\n");
					sRest *cRest = Seznam;
					while (cRest != NULL)
					{
						std::cout << cRest->ID << "	" << cRest->jmeno << "	" << cRest->komentar << "	" << cRest->hodnoceni << "\n";
						cRest = cRest->Dalsi;
					}
					int ID = 0;
					printf("Zadejte ID k odstraneni, 0 pro zruseni akce");
					scanf("%d", &ID);
					fflush(stdin);
					if (ID != 0)
						Odebrat(&Seznam, ID);

		} break;

		case '3':
		{
					printf("Zorazeni parametru:\n ID, Jmeno, Komentar, Hodnoceni\n");
					sRest *cRest = Seznam;
					while (cRest != NULL)
					{
						std::cout << cRest->ID << "	" << cRest->jmeno << "	" << cRest->komentar << "	" << cRest->hodnoceni << "\n";
						cRest = cRest->Dalsi;
					}
					int ID = 0;
					int hodnotenie;
					std::string jmeno, komentar;
					fflush(stdin);
					printf("Zadejte ID k uprave, 0 pro zruseni akce\n");
					scanf("%d", &ID);
					if (ID == 0)
					{
						fflush(stdin); //cistenie buffru a prepisanie dat do konzole
						break;
					}
					
					printf("Zadejte jmeno: ");
					std::cin >> jmeno;
					
					printf("Zadejte komentar: ");
					std::cin >> komentar;
					printf("Zadejte hodnoceni ");
					scanf("%d", &hodnotenie);
					fflush(stdin);//cistenie buffru a prepisanie dat do konzole
					//float priemer = (((Seznam->hodnoceni) + hodnotenie) / 2);
					Upravit(&Seznam, ID, jmeno, komentar, hodnotenie);

		} break;

		case '4':
		{
					
			printf("Zorazeni parametru:\n ID, Jmeno, Komentar, Hodnoceni\n");
					sRest *cRest = Seznam;
					while (cRest != NULL)
					{
						//printf("%d	%d	%s	%s	\n", cPrevod->ID, cPrevod->castka, cPrevod->popis, cPrevod->jmeno);
						std::cout << cRest->ID << "	" << cRest->jmeno << "	" << cRest->komentar << "	" << cRest->hodnoceni << "\n";
						
						cRest = cRest->Dalsi;
					}
					
					
					getchar(); getchar();
		} break;
		case '5':
		{
					
					std::string kriterium;
					printf("Vyhledavani podle jmena.\n");
					
					fflush(stdout);
	
					{
						printf("Zadejte jmeno restaurace\n");
						std::cin >> kriterium;
						
						printf("Zorazeni parametru: ID, Jmeno, Komentar, Hodnoceni\n");
						sRest *cRest = Seznam;
						while (cRest != NULL)
						{
							if (cRest->jmeno.compare(kriterium)==0)
							{
								std::cout << cRest->ID << "	" << cRest->jmeno << "	" << cRest->komentar << "	" << cRest->hodnoceni << "\n";
								
							}
							cRest = cRest->Dalsi;
						}
						
						
						getchar(); getchar();
					}
					
		}break;
		case '6':
		{
					int razeni;
					printf("Podle ceho chcete radit? (1)jmeno (2)hodnoceni\n");
					scanf("%d", &razeni);
					if (razeni == 2)
					{
						bool neserazeno = true;
						while (neserazeno)
						{
							neserazeno = false;
							sRest *pRest = NULL;
							sRest *cRest = Seznam;
							sRest *neRest = cRest->Dalsi;
							while (neRest != NULL)
							{
								if (neRest->hodnoceni>(cRest->hodnoceni) )//radici podminka
								{
									neserazeno = true;
									if (cRest == Seznam)
									{
										cRest->Dalsi = neRest->Dalsi;
										neRest->Dalsi = cRest;
										Seznam = neRest;

										pRest = Seznam;
										cRest = pRest->Dalsi;
										neRest = cRest->Dalsi;
										continue;
									}
									else
									{
										cRest->Dalsi = neRest->Dalsi;
										neRest->Dalsi = cRest;
										pRest->Dalsi = neRest;

										pRest = neRest;
										neRest = cRest->Dalsi;
										continue;
									}
								}
								pRest = cRest;
								cRest = cRest->Dalsi;
								if (neRest == Seznam)
									cRest = Seznam;
								neRest = cRest->Dalsi;
							}
						}
					}
					else
					{
						bool neserazeno = true;
						while (neserazeno)
						{
							neserazeno = false;
							sRest *pRest = NULL;
							sRest *cRest = Seznam;
							sRest *neRest = cRest->Dalsi;
							while (neRest != NULL)
							{
								if (neRest->jmeno.compare(cRest->jmeno) > 0)//Radici podmimnka
								{
									neserazeno = true;
									if (cRest == Seznam)
									{
										cRest->Dalsi = neRest->Dalsi;
										neRest->Dalsi = cRest;
										Seznam = neRest;

										pRest = Seznam;
										cRest = pRest->Dalsi;
										neRest = cRest->Dalsi;
										continue;
									}
									else
									{
										cRest->Dalsi = neRest->Dalsi;
										neRest->Dalsi = cRest;
										pRest->Dalsi = neRest;

										pRest = neRest;
										neRest = cRest->Dalsi;
										continue;
									}
								}
								pRest = cRest;
								cRest = cRest->Dalsi;
								if (neRest == Seznam)
									cRest = Seznam;
								neRest = cRest->Dalsi;
							}
						}
					}
		} break;

		case '0':; break;

		default: printf("Chybne zadana akce! \n");
		}
	} while ((volba != '0'));
	Uloz(Seznam);
	return 0;
}