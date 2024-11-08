#include "fonction_bassilekin.h"
#include <stdio.h>
#include <stdlib.h>

int main(){

    joueur joueursBA[PLAYER_NUMBER];
    int current_playerBA = 1;/* joueur 1 correspond à 1 et joueur 2 à 0*/
    joueursBA[0].score = 0;
    joueursBA[1].score = 0;

    //page d'accueil
    printf("\n  \t\t======================================= ");
    printf("\n \t\t||    Bienvenue dans le jeu SONGO !    ||");
    printf("\n  \t\t=======================================\n");

    initialisationBA(joueursBA);
    afficher_plateauBA(joueursBA);
    printf("\nCLIQUER ENTRER POUR COMMENCER\n");
    getchar();

    while (1)
    {
        system("clear"); // Effacer l'écran
        afficher_plateauBA(joueursBA); // Afficher le plateau
        printf("\n_____________\n");
        printf("|SCORE %d : %d |\n",joueursBA[0].score,joueursBA[1].score);
        printf("--------------\n");
        current_playerBA = (current_playerBA + 1) % PLAYER_NUMBER;
        printf("\n\tTOUR DU JOUEUR %d\n", current_playerBA + 1);
        
        // Distribution des graines
        distributionBA(joueursBA, current_playerBA);
        // Vérification de la victoire
        int joueur_gagnantBA = check_victoireBA(joueursBA, current_playerBA);
        if (joueur_gagnantBA != 0) {
            system("clear");
            afficher_plateauBA(joueursBA);
            printf("\n _______________\n");
            printf("|SCORE %d : %d |\n",joueursBA[0].score,joueursBA[1].score);
            printf(" ---------------\n");
            printf("Le joueur %d a gagné !\n", joueur_gagnantBA);
            break; // Quitter la boucle de jeu
        }
        // Passer au joueur suivant
        current_playerBA = (current_playerBA + 1) % PLAYER_NUMBER;
    }
    return 0;
}
