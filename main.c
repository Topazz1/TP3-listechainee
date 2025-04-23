#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //pour tolower() et toupper()
#include "tp3.h"

int main() {
    char choixMenu = '0' ;
    
    t_lexique* listeLexiques = NULL; // Liste chaînée de tous les lexiques
    t_lexique* dernierLexique = NULL; // Pour ajouter à la fin rapidement

    do {

        printf("\n========================================");
        printf("\n  [0] Créer un nouveau lexique");
        printf("\n  [1] Afficher un lexique");
        printf("\n  [2] Ajouter un mot dans un lexique");
        printf("\n  [3] Retirer un mot d'un lexique");
        printf("\n  [4] Fusionner deux lexiques");
        printf("\n  [5] Charger un fichier dans un lexique");
        printf("\n  [6] Quitter");
        printf("\n========================================");
        printf("\n(?) Votre choix : ");
    choixMenu = getchar();
    while (choixMenu == '\n') { // tant qu'on lit des '\n', on continue à lire car getchar() lit le buffer d'entrée
        choixMenu = getchar();
    }
    viderBuffer();

        switch (choixMenu) {
            case '0' : {
                    printf("\n\n\t(!) Création d'un nouveau lexique\n\n");
                
                    // Demander le nom du lexique
                    char nomLexique[100];
                    printf("(?) Entrez le nom du nouveau lexique : ");
                    fgets(nomLexique, sizeof(nomLexique), stdin);
                    nomLexique[strcspn(nomLexique, "\r\n")] = '\0'; // Nettoyage du \n
                
                    // Créer un nouveau lexique vide
                    t_lexique* nouveauLexique = creerLexique(nomLexique);
                
                    // Demander comment initialiser : par fichier ou par mot
                    char choixInitialisation;
                    printf("\n(!) Initialiser le lexique :\n");
                    printf("[1] À partir d'un mot\n");
                    printf("[2] À partir d'un fichier\n");
                    printf("\n(?) Votre choix : ");
                    choixInitialisation = getchar();
                    viderBuffer();
                
                    if (choixInitialisation == '1') {
                        // Initialisation par mot
                        char mot[100];
                        printf("(?) Entrez le premier mot du lexique : ");
                        fgets(mot, sizeof(mot), stdin);
                        mot[strcspn(mot, "\r\n")] = '\0'; // Nettoyage du \n
                        mettreEnMinuscules(mot);
                
                        // Créer le premier mot et l'attacher au lexique
                        nouveauLexique->mots = creerMot(mot);
                    }
                    else if (choixInitialisation == '2') {
                        // Initialisation par fichier
                        nouveauLexique->mots = importerFichier(nouveauLexique->mots);
                    }
                    else {
                        printf("(!!) Choix invalide. Lexique créé vide.\n");
                    }
                
                    // Maintenant il faudrait rajouter le lexique à la liste de tous les lexiques
                    if (listeLexiques == NULL) {
                        listeLexiques = nouveauLexique;
                        dernierLexique = nouveauLexique;
                    } else {
                        dernierLexique->suivant = nouveauLexique;
                        dernierLexique = nouveauLexique;
                    }
                
                    printf("(!) Le lexique '%s' a été créé avec succès.\n", nomLexique);
                    break;
                }
            case '1' : {
                    printf("\n\n\t(!) Affichage d'un lexique\n\n");
                
                    if (listeLexiques == NULL) {
                        printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                        break;
                    }
                
                    // Demander à l'utilisateur de choisir un lexique
                    t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                
                    if (lexiqueChoisi == NULL) {
                        printf("(!!) Aucun lexique sélectionné.\n");
                        break;
                    }
                
                    printf("\n (!) Mots du lexique '%s' :\n", lexiqueChoisi->nom);
                
                    if (lexiqueChoisi->mots == NULL) {
                        printf("(!!) Le lexique est vide\n");
                    } else {
                        afficherMots(lexiqueChoisi->mots);
                    }
                    break;
                }
            case '2' : {
                    printf("\n\n\t(!) Ajouter un mot dans un lexique\n\n");
                
                    if (listeLexiques == NULL) {
                        printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                        break;
                    }
                
                    // Demander à l'utilisateur de choisir un lexique
                    t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                
                    if (lexiqueChoisi == NULL) {
                        printf("(!!) Aucun lexique sélectionné.\n");
                        break;
                    }
                
                    // Demander le mot à ajouter
                    char mot[100];
                    printf("(?) Entrez le mot à ajouter : ");
                    fgets(mot, sizeof(mot), stdin);
                    mot[strcspn(mot, "\r\n")] = '\0'; // Nettoyage du \n
                
                    if (strlen(mot) == 0) {
                        printf("(!!) Mot vide, aucune action réalisée.\n");
                        break;
                    }
                
                    // Ajouter le mot dans le lexique choisi
                    lexiqueChoisi->mots = ajouterMot(lexiqueChoisi->mots, mot);
                
                    printf("(!) Le mot '%s' a été ajouté au lexique '%s'.\n", mot, lexiqueChoisi->nom);
                
                    break;
                }
            case '3' : {
                    printf("\n\n\t(!) Retirer un mot d'un lexique\n\n");
                
                    if (listeLexiques == NULL) {
                        printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                        break;
                    }
                
                    // Demander à l'utilisateur de choisir un lexique
                    t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                
                    if (lexiqueChoisi == NULL) {
                        printf("(!!) Aucun lexique sélectionné.\n");
                        break;
                    }
                
                    if (lexiqueChoisi->mots == NULL) {
                        printf("(!!) Le lexique '%s' est vide. Aucun mot à retirer.\n", lexiqueChoisi->nom);
                        break;
                    }
                
                    // Demander le mot à retirer
                    char mot[100];
                    printf("(?) Entrez le mot à retirer : ");
                    fgets(mot, sizeof(mot), stdin);
                    mot[strcspn(mot, "\r\n")] = '\0'; // Nettoyage du \n
                
                    if (strlen(mot) == 0) {
                        printf("(!!) Mot vide, aucune action réalisée.\n");
                        break;
                    }
                
                    // Retirer le mot du lexique choisi
                    t_mot* nouvelleListe = retirerMot(lexiqueChoisi->mots, mot);
                
                    if (nouvelleListe == lexiqueChoisi->mots) {
                        // Cas où la liste reste identique (mot non trouvé ou juste décrémenté)
                        printf("(!) Le mot '%s' a été décrémenté dans le lexique '%s' (ou déjà retiré si non existant).\n", mot, lexiqueChoisi->nom);
                    } else {
                        // Cas où la tête a changé
                        lexiqueChoisi->mots = nouvelleListe;
                        printf("(!) Le mot '%s' a été retiré du lexique '%s'.\n", mot, lexiqueChoisi->nom);
                    }
                
                    break;
                }
            case '4' :
                printf("\n\n\t<Faire Fusionner deux lexiques>\n\n");
                break;
            case '5' :
                printf("\n\n\t<Faire Charger un fichier dans un lexique>\n\n");
                break;
        }
    } while (choixMenu != '6');


    printf("\n\n*** FIN DU PROGRAMME ***\n");

    return 0;
}
