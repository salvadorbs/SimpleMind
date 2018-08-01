#include "colors.h"
#include "print.h"
#include <time.h>

int main(int argc, char *argv[]) {
	int diff; //Servirà per la lunghezza del codice segreto
	int isCorrectCode;
	char secretCode[MAXDIFF];

	//Benvenuto e regole
	printHello();
	printLegenda();
	printLunghezzaStr();

	//Chiede quanto lunga la stringa dei colori
	//E lo chiede finchè ha un numero valido per la generazione del codice
	diff = askDifficulty();
	
	//Genera la stringa
	genSecretCode(secretCode, diff);

	//Inizia il gioco	
	isCorrectCode = startGame(diff, secretCode);
	
	if (isCorrectCode) 
		printWin();
	else
		printLost();

	//Saluto finale
	printBye();
	
	//Per evitare di chiudere la finestra
	getchar();
}
