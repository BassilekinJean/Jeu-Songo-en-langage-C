#if !defined(FONCTION_BASSILEKIN_H)
#define FONCTION_BASSILEKIN_H

#define CASE_NUMBER 7
#define PLAYER_NUMBER 2

typedef struct joueur
{
    int score;
    int plateau[CASE_NUMBER];
}joueur;

int  check_victoireBA(joueur *j, int cp);
int  estVideBA(joueur *j, int cp);
int  prisesBA(joueur *j, int current_player, int p, int nbp);
int  verifier_captureBA(joueur *j, int current_player, int p, int nbp);
void distributionBA(joueur *joueurs, int current_player);
void afficher_plateauBA(joueur* j);
void initialisationBA(joueur *j);

#endif // FONCTION_BASSILEKIN_H