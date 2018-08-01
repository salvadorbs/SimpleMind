#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "print.h"

char arrayColors[] = "ROYGBW"; //Red, Orange, Yellow, Green, Blue, White
const int intColors = 6; //Sei colori disponibili

int askColors(void)
{
	int c;
	
	//Recupera il numero digitato dal giocatore
	scanf("%d",&c);
	
	//Liberiamo il buffer input
	fflush(stdin);
		
	//Controlla il numero min e max di colori
	//Se c è fuori range (3 < c < 10), allora segnala l'errore al giocatore e cambia il valore di c in -1
	if ((c > MAXDIFF) || (c < MINDIFF))
	{
		c = -1;
		printErrorColors();
	}

	return c;
}

int askDifficulty()
//Restituisce la lunghezza della stringa da generare
{
	int diff;

	//Chiede quanto lunga la stringa dei colori
	//E lo chiede finchè ha un numero valido per la generazione del codice
	do
	{
		printColors();
		diff = askColors();
	}
	while (diff == -1);

	return diff;
}

void genSecretCode(char *secretCode, int lenght)
{
	int i;
	
	//Inizializzo la funzione per la generazione di numeri casuali
	srand(time(NULL));
	
	//Generazione del codice segreto di lunghezza lenght
	//In base alla funzione rand(), ad ogni iterazione viene chiamata la funzione rand() e il risultato modulato con il numero dei colori disponibili
	//Quindi in base al valore random, viene scelta una posizione (quindi un colore) di arrayColors
    for (i = 0; i < lenght; i++)
        secretCode[i] = arrayColors[(rand() % intColors)];
		
    //Se l'array non risulta completamente popolato, aggiungo un terminatore alla stringa
	if (lenght < MAXDIFF - 1)
		secretCode[lenght] = '\0'; 
    
	//DEBUG
	#if DEBUG
		printf("Debug: stringa colori generata = %s ", secretCode);
		printf("\n\n");
	#endif
}

int non_blank(void) {
   char value;

   while ((value = getchar()) != EOF && value == ' ') {}

   return value;
}

int ConvertColor(char Letter)
{
	//roygbw
	switch (Letter) {
		case 'R':
			return 0;
		case 'O':
			return 1;
		case 'Y':
			return 2;
		case 'G':
			return 3;
		case 'B':
			return 4;
		case 'W':
			return 5;
		default:
			return -1;
	}
}

void askUserCode(char *guess, int lenght) 
{
	char discard;
	int retry, i;
	
	do {
		i = retry = 0;
		//Prende un solo carattere alla volta e lo analizza
		char letter;
		while (i < lenght) {
			//La funzione non_blank() recupera la lettera digitata dal giocatore grazie a getChar()
			//ed evita di tener conto dei possibili spazi inseriti dal giocatore
			letter = non_blank();
			if (isalpha(letter)) {
				guess[i] = letter;
				//Se l'utente ha immesso un carattere in minuscolo, lo rendiamo maiuscolo
				//In quanto la lettera in maiuscolo è diversa dalla stessa lettera in minuscolo
				//E il gioco genera una stringa con lettere in maiuscolo
				if (islower(letter))
					guess[i] -= 32;
				
				//Controlla se è stato immesso un colore e non un carattere a caso con la funzione strchr() 
				//Con strchr() controllo che il carattere corrente si trovi in arrayColors
				//Se lo trova il puntatore del carattere ricercato, altrimenti restituisce null 
				//(che renderebbe vera la condizione dell'if, grazie all'operatore NOT = !)
				if (!strchr(arrayColors, guess[i])) {
					printIncorrectCode();
					retry = i = lenght;   //ricomincio da capo
				}
				else
					i++;
			}
		} 
		
		//flush buffer input
		while ((discard = getchar()) != '\n' && discard != EOF) {}
   } while (retry);
}

int MatchCodes(int length, char *userCode, char *secretCode)
//Restituisce i blackpegs trovati
{
	//blackPegs = lettere giuste al giusto posizionamento
	//whitePegs = lettere giuste al posizionamento errato
	int i, j, blackPegs = 0, whitePegs = 0;
	int countColors[intColors];
	
	//Inizializzo countColors, settando i valori a 0 (false)
	for (i = 0; i < intColors; i++) {
		countColors[i] = 0;
	}

	//Inizio il controllo dell'userCode (iterando userCode con un ciclo for), trovando i blackPegs e costruendo una mappa basilare dei colori non giusti
	//Mappa = conteggio dei colori trovati
	
	//Se trova il colore al giusto posto, aumenta blackPegs
	//Dato che l'utente può mettere lo stesso colore più volte (es. "rrrb") e 
	//può capitare che venga generato una stringa con gli stessi colori in misura minore (es. "abrr")
	//devo poter conteggiare i whitePegs senza che l'algoritmo segnali la lettera nel posto sbagliato più volte del necessario
	//quindi uso una mappa basilare countColors, in cui conteggio i colori trovati
	for (i = 0; i < length; i++) {
		if (userCode[i] == secretCode[i])
			blackPegs++;
	    else
	    	countColors[ConvertColor(userCode[i])]++;
	}
	
	#if DEBUG
		//Controllo countColors stampando a video
		printf("Stampata a video dell'array countColors (possibili whitePegs): \n");
		for (i = 0; i < intColors; i++) {
			printf("index %d (%c): %d\n", i, arrayColors[i], countColors[i]);
		}
	#endif
	
	//Ora cerco i whitePegs, basandomi su countColors e naturalmente evitando i colori già trovati come blackPegs
	//Tramite l'iterazione del secretCode, controllo se ogni colore è già stato trovato e conteggiato (basta che non sia 0)
	//nel precedente ciclo
	for (i = 0; i < length; i++) {
		j = ConvertColor(secretCode[i]);
		if ((secretCode[i] != userCode[i]) && countColors[j]) 
		{
			whitePegs++;
			//Elimino il singolo colore trovato dal conteggio, altrimenti se l'utente avrà messo un solo colore
			//l'algoritmo segnalerà lo stesso colore più volte del necessario (ogni volta che verrà trovato nel secretCode)
			countColors[j]--;
		}
	}

	if (blackPegs != length)
		printf("Sbagliato. Ci sono %d lettere giuste al posto giusto e %d lettere giuste al posto sbagliato\n", blackPegs, whitePegs);
		
	return blackPegs;
}

int startGame(int length, char *secretCode)
//Restituisce un numero 0 o 1, indicando rispettivamente perso o vinto
{
	int i, isCorrectCode;
	char code[length];
	
	for (i = 0; i < 10; i++) {
		printCode(i);
		
		askUserCode(code, length);
		
		//MatchCodes() restituisce i blackpegs trovati
		//Confrontati con la lunghezza del codice, se sono uguali il giocatore ha scoperto il codice e quindi ritorna 1
		//Altrimenti itera un altra volta
		isCorrectCode = (MatchCodes(length, code, secretCode) == length);
		if (isCorrectCode)
			return isCorrectCode;
	}

	return 0;
}
