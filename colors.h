#define MAXDIFF	10
#define MINDIFF	3

#define DEBUG 0

int MatchCodes(int length, char *userCode, char *secretCode);

int askDifficulty(void);

void genSecretCode(char *secretCode, int lenght);

int startGame(int length, char *secretCode);
