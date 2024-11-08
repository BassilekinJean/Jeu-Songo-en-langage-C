#include "fonction_bassilekin.h"
#include <stdio.h>
#include <stdlib.h>

void initialisationBA(joueur *j){

    for (size_t i = 0; i < 7; i++)
    {
        j[0].plateau[i] = 5;
    }
    for (int w = 6; w >= 0; w--)
    {
        j[1].plateau[w] = 5; 
    }
}

int estVideBA(joueur *j, int current_player){
    int cpt = 0;
    for (int i = 1; i < CASE_NUMBER-1; i++){ 
        if (j[current_player].plateau[i] != 0)
            cpt += 1;
    }
    if (cpt == 0)
        return 1;
    else
        return 0;
    return 0;
}

void afficher_plateauBA(joueur *j){
    printf("\n___________________________\n");
    for (size_t i = 0; i < 7; i++)
    {
        printf("%d | ", j[0].plateau[i]);
    }
    printf("\n___________________________\n");
    for (int w = 6; w >= 0; w--)
    {
        printf("%d | ", j[1].plateau[w]);
    }
    printf("\n___________________________\n");
}

int verifier_captureBA(joueur *j, int current_player, int p, int nbp){
    int saut = p - (CASE_NUMBER - nbp);
    int next_player = (current_player + 1) % PLAYER_NUMBER;

    // Vérifier si des graines ont été distribuées dans les cases du joueur suivant
    if (saut > 0) {
        // Vérifier si chaque case du joueur suivant contient au moins une graine
        for (int i = 0; i < saut; i++) {
            // Vérifier si le nombre de graines dans la case est compris entre 2 et 4
            if (j[next_player].plateau[i] >= 2 && j[next_player].plateau[i] <= 4) { 
                return 1; // Capture possible
            }
        }
    }
    return 0; // Aucune capture possible
}

int prisesBA(joueur* j, int current_player, int position_actuel, int nb_pierre){

    int saut = position_actuel - (CASE_NUMBER - nb_pierre);
    int next_player = (current_player + 1) % PLAYER_NUMBER;
    int capture = 0;

    // Vérifier si des graines ont été distribuées dans les cases du joueur suivant
    if (saut > 0) {
        // Vérifier si chaque case du joueur suivant contient au moins une graine
        for (int i = 0; i < saut; i++) {
            // Vérifier si le nombre de graines dans la case est compris entre 2 et 4
            if (j[next_player].plateau[i] >= 2 && j[next_player].plateau[i] <= 4) {
                // Capture des graines si la condition est remplie
                j[current_player].score += j[next_player].plateau[i];
                j[next_player].plateau[i] = 0; // Supprimer les graines capturées
                capture++;
            }
        }
    }
    return capture; // Retourner le nombre de captures
}

void distributionBA(joueur *joueurs, int current_player){

    int nombre_de_graine;
    int position_case;
    int saut = 0;
    int next_player = (current_player+1) % PLAYER_NUMBER;    

    do {
        printf("\nEntrez la position de la case (1 à 7): ");
        scanf("%d", &position_case);

        if (position_case < 1 || position_case > CASE_NUMBER) {
            printf("Position de case invalide. Veuillez entrer une valeur entre 1 et 7.\n");
            getchar();
            system("clear");
        } else if (position_case == 7 && (joueurs[current_player].plateau[CASE_NUMBER - 1] == 1 || 
                   (joueurs[0].plateau[CASE_NUMBER - 1] == 2 && 
                    (verifier_captureBA(joueurs, current_player, position_case, nombre_de_graine) != 1 ||
                     estVideBA(joueurs, current_player) != 1)))) {
            printf("Mouvement invalide.\n");
            getchar();
            system("clear");
        } else {
            break; // Sortir de la boucle si l'entrée est valide
        }
    } while (1);
    do {
        printf("Entrez le nombre de pierres à déplacer (1 à 5): ");
        scanf("%d", &nombre_de_graine);

        if (nombre_de_graine < 1 || nombre_de_graine > 5 || nombre_de_graine > joueurs[current_player].plateau[position_case - 1]) {
            printf("Nombre de graines invalide. Veuillez entrer une valeur entre 1 et 5 et inférieure ou égale au nombre de graines dans la case.\n");
            getchar();
            system("clear");
        } else {
            break; // Sortir de la boucle si l'entrée est valide
        }
    } while (1);
    saut = position_case - (CASE_NUMBER - nombre_de_graine);
    joueurs[current_player].plateau[position_case - 1] -= nombre_de_graine;
    if (saut > 0)
    {
        if (position_case != 7){
            for (int i = position_case; i <= position_case + (saut -1); i++){
                joueurs[current_player].plateau[i] +=1; 
            }
            for (int j = 0; j < saut; j++){
                joueurs[next_player].plateau[j] += 1;
            }
        }
        for (int j = 0; j < nombre_de_graine; j++){
            joueurs[next_player].plateau[j] += 1;
        } 
    }else
    {
        for (int i = position_case; i < (position_case + nombre_de_graine); i++){
            joueurs[current_player].plateau[i] +=1;
        } 
    }
    //prises(joueurs, current_player, position_case, nombre_de_graine);
}
int check_victoireBA(joueur *j, int current_player) {
    // Vérifier si le joueur actuel a plus de 35 points
    if (j[current_player].score > 35) {
        return current_player + 1; // Le joueur actuel a gagné
    }
    // Vérifier si le nombre total de graines sur le plateau est inférieur à 10
    int total_graines = 0;
    for (int i = 0; i < PLAYER_NUMBER; i++) {
        for (int k = 0; k < CASE_NUMBER; k++) {
            total_graines += j[i].plateau[k];
        }
    }
    if (total_graines < 10) {
        // Trouver le joueur avec le score le plus élevé
        int joueur_gagnant = 0;
        int score_max = j[0].score + total_graines;
        for (int i = 1; i < PLAYER_NUMBER; i++) {
            int score_joueur = j[i].score + total_graines;
            if (score_joueur > score_max) {
                joueur_gagnant = i;
                score_max = score_joueur;
            }
        }
        return joueur_gagnant + 1; // Le joueur avec le score le plus élevé a gagné
    }
    return 0; // Aucun joueur n'a gagné
}