#include <stdio.h>
#include "colors.h"

void printHello(void)
{
	printf("Benvenuto in Mastermind! In questo gioco bisogna scoprire un codice segreto formato da colori.\n\n"); 
}

void printLegenda(void)
{
	printf("In questa versione testuale, i colori sono rappresentati dalle loro iniziali inglese. \n\n"
			"Legenda:\n"
			"R = Red\n"
			"O = Orange\n"
			"Y = Yellow\n"
			"G = Green\n"
			"B = Blue\n"
			"W = White\n\n");
}

void printLunghezzaStr(void)
{
	printf("E' possibile scegliere da un minimo di 3 colori ad un massimo di 10 per la generazione del codice segreto. \n"
			"Il numero di tentativi massimo consentiti sono 10. Buon divertimento!\n\n");	
}

void printColors(void)
{
	printf("Quanti colori? (min %d, max %d)? ", MINDIFF, MAXDIFF);
}

void printCode(int numTry)
{
	printf("Tentativo numero %d = ", numTry + 1);
}

void printBye(void)
{
	printf("\nMasterMind 0.1 by Matteo Salvi");
}

void printWin(void)
{
	printf("Complimenti. Hai vinto!\n");	
}

void printLost(void)
{
	printf("Mi dispiace, hai perso. Hai esaurito i tuoi tentativi.\n");	
}

void printIncorrectCode(void)
{
	printf("Hai sbagliato ad inserire il codice. Ricordati che devi mettere i colori con le iniziali inglesi (ROYGBW). Riprova = ");	
}

void printErrorColors(void)
{
	printf("Errore! Hai inserito un numero di colori non consentito. Ricordati minimo 3 colori e massimo 9 colori!\n");
}

void printErrorUserCode(void)
{
	printf("Hai digitato un codice non valido.\n");
}
