#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tp3.h"

int main() {
    char choixMenu = '0';
    
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
        while (choixMenu == '\n') {
            choixMenu = getchar();
        }
        viderBuffer();

        switch (choixMenu) {
            case '0': {
                printf("\n\n\t(!) Création d'un nouveau lexique\n\n");
                char nomLexique[100];
                printf("(?) Entrez le nom du nouveau lexique : ");
                fgets(nomLexique, sizeof(nomLexique), stdin);
                nomLexique[strcspn(nomLexique, "\r\n")] = '\0';

                t_lexique* nouveauLexique = creerLexique(nomLexique);

                char choixInitialisation;
                printf("\n(!) Initialiser le lexique :\n");
                printf("[1] À partir d'un mot\n");
                printf("[2] À partir d'un fichier\n");
                printf("\n(?) Votre choix : ");
                choixInitialisation = getchar();
                viderBuffer();

                if (choixInitialisation == '1') {
                    char mot[100];
                    printf("(?) Entrez le premier mot du lexique : ");
                    fgets(mot, sizeof(mot), stdin);
                    mot[strcspn(mot, "\r\n")] = '\0';
                    mettreEnMinuscules(mot);
                    nouveauLexique->mots = creerMot(mot);
                } else if (choixInitialisation == '2') {
                    nouveauLexique->mots = importerFichier(nouveauLexique->mots);
                } else {
                    printf("(!!) Choix invalide. Lexique créé vide.\n");
                }

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

            case '1': {
                printf("\n\n\t(!) Affichage d'un lexique\n\n");

                if (listeLexiques == NULL) {
                    printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                    break;
                }

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

            case '2': {
                printf("\n\n\t(!) Ajouter un mot dans un lexique\n\n");

                if (listeLexiques == NULL) {
                    printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                    break;
                }

                t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                if (lexiqueChoisi == NULL) {
                    printf("(!!) Aucun lexique sélectionné.\n");
                    break;
                }

                char mot[100];
                printf("(?) Entrez le mot à ajouter : ");
                fgets(mot, sizeof(mot), stdin);
                mot[strcspn(mot, "\r\n")] = '\0';

                if (strlen(mot) == 0) {
                    printf("(!!) Mot vide, aucune action réalisée.\n");
                    break;
                }

                lexiqueChoisi->mots = ajouterMot(lexiqueChoisi->mots, mot);
                printf("(!) Le mot '%s' a été ajouté au lexique '%s'.\n", mot, lexiqueChoisi->nom);
                break;
            }

            case '3': {
                printf("\n\n\t(!) Retirer un mot d'un lexique\n\n");

                if (listeLexiques == NULL) {
                    printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                    break;
                }

                t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                if (lexiqueChoisi == NULL) {
                    printf("(!!) Aucun lexique sélectionné.\n");
                    break;
                }

                if (lexiqueChoisi->mots == NULL) {
                    printf("(!!) Le lexique '%s' est vide. Aucun mot à retirer.\n", lexiqueChoisi->nom);
                    break;
                }

                char mot[100];
                printf("(?) Entrez le mot à retirer : ");
                fgets(mot, sizeof(mot), stdin);
                mot[strcspn(mot, "\r\n")] = '\0';

                if (strlen(mot) == 0) {
                    printf("(!!) Mot vide, aucune action réalisée.\n");
                    break;
                }

                t_mot* nouvelleListe = retirerMot(lexiqueChoisi->mots, mot);

                if (nouvelleListe == lexiqueChoisi->mots) {
                    printf("(!) Le mot '%s' a été décrémenté dans le lexique '%s'.\n", mot, lexiqueChoisi->nom);
                } else {
                    lexiqueChoisi->mots = nouvelleListe;
                    printf("(!) Le mot '%s' a été retiré du lexique '%s'.\n", mot, lexiqueChoisi->nom);
                }

                break;
            }

            case '4' : {
                printf("\n\n\t(!) Fusionner deux lexiques\n\n");
            
                if (listeLexiques == NULL || listeLexiques->suivant == NULL) {
                    printf("(!!) Il faut au moins deux lexiques pour effectuer une fusion.\n");
                    break;
                }
            
                // Choix du premier lexique (destination)
                printf("(!) Sélection du lexique receveur (A)\n");
                t_lexique* lexiqueA = choisirLexique(listeLexiques);
                if (lexiqueA == NULL) {
                    printf("(!!) Aucun lexique sélectionné.\n");
                    break;
                }
            
                // Choix du second lexique (à fusionner dans A)
                printf("\n(!) Sélection du lexique à fusionner dans le précédent (B)\n");
                t_lexique* lexiqueB = choisirLexique(listeLexiques);
                if (lexiqueB == NULL || lexiqueB == lexiqueA) {
                    printf("(!!) Lexique invalide ou identique au précédent.\n");
                    break;
                }
            
                // Fusion des mots
                lexiqueA->mots = fusionner(lexiqueA->mots, lexiqueB->mots);
                lexiqueB->mots = NULL; // la fusion a déjà tout libéré
            
                // Suppression de lexiqueB dans la liste chaînée
                if (listeLexiques == lexiqueB) {
                    // lexiqueB est en tête
                    listeLexiques = lexiqueB->suivant;
                } else {
                    // On cherche le lexique juste avant B
                    t_lexique* precedent = listeLexiques;
                    while (precedent->suivant != NULL && precedent->suivant != lexiqueB) {
                        precedent = precedent->suivant;
                    }
                    if (precedent->suivant == lexiqueB) {
                        precedent->suivant = lexiqueB->suivant;
                    }
                }
            
                // Libération mémoire du nom + de la structure de B
                free(lexiqueB->nom);
                free(lexiqueB);

                // Mettre à jour dernierLexique si nécessaire
                if (dernierLexique == lexiqueB) {
                    // On doit retrouver le nouveau dernier dans la liste
                    dernierLexique = listeLexiques;
                    if (dernierLexique != NULL) {
                        while (dernierLexique->suivant != NULL) {
                            dernierLexique = dernierLexique->suivant;
                        }
                    }
                }
            
                printf("(!) Fusion terminée. Le lexique a été intégré et l'ancien supprimé.\n");
                break;
            }

            case '5' : {
                printf("\n\n\t(!) Charger un fichier dans un lexique\n\n");
            
                if (listeLexiques == NULL) {
                    printf("(!!) Aucun lexique existant. Créez-en un d'abord.\n");
                    break;
                }
            
                // Choisir le lexique
                t_lexique* lexiqueChoisi = choisirLexique(listeLexiques);
                if (lexiqueChoisi == NULL) {
                    printf("(!!) Aucun lexique sélectionné.\n");
                    break;
                }
            
                // Importer les mots depuis le fichier
                lexiqueChoisi->mots = importerFichier(lexiqueChoisi->mots);
            
                printf("(!) Importation terminée dans le lexique '%s'.\n", lexiqueChoisi->nom);
                break;
            }

            case '6': {
                printf("\n\n*** Fin du programme. Merci d’avoir utilisé le gestionnaire de lexiques. ***\n");
                printf("(!) Libération de la mémoire...\n");
                // Libération mémoire
                libererLexiques(listeLexiques);

                return 0;
            }

            default:
                printf("(!!) Choix invalide. Veuillez réessayer.\n");
        }

    } while (choixMenu != '6');

    return 0;
}