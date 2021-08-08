#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Company.h"
#include "AirportManager.h"
#include "General.h"
#include "main.h"
#include "myMacros.h"
//#define DETAIL_PRINT


const char* str[eNofOptions] = { "Add Flight", "Add Airport",
"PrintCompany", "Print all Airports",
	"Print flights between origin-destination",
"Sort Flights", "Search Flight" };

int main(int argc, char* argv[])
{
	char* myManagerFile = "";
	char* myCompanyFile = "";
	if (argc == 2) {
		myManagerFile = (char*)malloc(sizeof(char)*(strlen(argv[1]) + 1));
		strcpy(myManagerFile, argv[1]);
		myCompanyFile = (char*)malloc(sizeof(char)*(strlen(argv[2]) + 1));
		strcpy(myCompanyFile, argv[2]);
	}
	AirportManager	manager;
	Company			company;
	initManagerAndCompany(&manager, &company, myManagerFile, myCompanyFile);


	int option;
	int stop = 0;

	do
	{
		option = menu();
		switch (option)
		{
		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;


		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case ePrintCompany:
		{
			char* myChar;
			myChar = combiningStrings(company.name, "Hachi", "Babait", "Ba", "Olam", NULL);
		#ifdef DETAIL_PRINT
			printf(myChar);
			printCompany(&company);
		#else

			printf(myChar);
			printf(" has %d flights", company.flightCount);
			
		#endif // DETAIL_PRINT

			free(myChar);
			break;
		}
		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightOrigDest:
			printFlightsCount(&company);
			break;

		case eSortFlights:
			sortFlight(&company);
			break;

		case eSearchFlight:
			findFlight(&company);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	if (argc > 1)
		saveManagerToFile(&manager, myManagerFile);
	saveCompanyToFile(&company, myCompanyFile);

	freeManager(&manager);
	freeCompany(&company);

	system("pause");
	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);

	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int initManagerAndCompany(AirportManager* pManager, Company* pCompany, char* fileNameManager, char* fileNameCompany)
{
	int res = initManager(pManager, fileNameManager);
	if (!res)
	{
		printf("error init manager\n");
		return 0;
	}

	if (res == FROM_FILE)
		return initCompanyFromFile(pCompany, pManager, fileNameCompany);
	else
		initCompany(pCompany, pManager);
	return 1;
}