#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //pour tolower() et toupper()
#include "tp3.h"

// Création nouvel élément
t_mot* creerMot(char* mot) {
    // Allocation de la structure t_mot
    t_mot* nouveau = (t_mot*)malloc(sizeof(t_mot));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour un mot.\n");
        exit(EXIT_FAILURE);
    }

    // Allocation et copie du mot
    if (mot == NULL) {
        printf("Erreur : le mot fourni est NULL.\n");
        free(nouveau);
        exit(EXIT_FAILURE);
    }
    nouveau->mot = (char*)malloc((strlen(mot) + 1) * sizeof(char)); // +1 pour le caractère nul \n
    if (nouveau->mot == NULL) {
        printf("Erreur d'allocation mémoire pour le contenu du mot.\n");
        free(nouveau);
        exit(EXIT_FAILURE);
    }
    strcpy(nouveau->mot, mot);

    // Initialisation du reste
    nouveau->nombre_occurences = 1;
    nouveau->suivant = NULL;

    return nouveau;
}
/* ====== FIN creerMot ====== */

// Fonction interne pour mettre un mot en minuscules
void mettreEnMinuscules(char* mot) {
    for (int i = 0; mot[i] != '\0'; i++) {
        mot[i] = tolower(mot[i]);
    }
}
/* ====== FIN mettreEnMinuscules ====== */

// Ajout mot dans une liste
t_mot* ajouterMot(t_mot* liste, char* mot) {
    // 1. Convertir le mot en minuscules
    mettreEnMinuscules(mot);

    // 2. Si la liste est vide, création directe
    if (liste == NULL) {
        return creerMot(mot);
    }

    t_mot* courant = liste;
    t_mot* precedent = NULL; //Toujours garder en mémoire le précédent pour pouvoir insérer au bon endroit

    // 3. Parcourir la liste pour trouver la position
    while (courant != NULL) {
        int cmp = strcmp(mot, courant->mot);

        if (cmp == 0) {
            // Mot déjà présent : on incrémente
            courant->nombre_occurences++;
            return liste; // La tête ne change pas
        } else if (cmp < 0) {
            // On doit insérer avant courant
            t_mot* nouveau = creerMot(mot);

            if (precedent == NULL) {
                // Insertion en tête
                nouveau->suivant = liste;
                return nouveau; // La nouvelle tête de liste
            } else {
                // Insertion au milieu
                precedent->suivant = nouveau;
                nouveau->suivant = courant;
                return liste;
            }
        }

        // Avancer dans la liste car cmp > 0
        // On garde en mémoire le précédent pour l'insertion
        // et on avance le courant
        precedent = courant;
        courant = courant->suivant;
    }

    // 4. Si on arrive ici, insertion à la fin
    t_mot* nouveau = creerMot(mot);
    precedent->suivant = nouveau;

    return liste;
}
/* ====== FIN ajouterMot ====== */


// Retrait occurence mot d'une liste
t_mot* retirerMot(t_mot* liste, char* mot) {
    if (liste == NULL) {
        // Liste vide : rien à faire
        return NULL;
    }

    mettreEnMinuscules(mot);

    t_mot* courant = liste;
    t_mot* precedent = NULL; // Toujours garder en mémoire le précédent pour pouvoir supprimer au bon endroit

    while (courant != NULL) {
        int cmp = strcmp(mot, courant->mot);

        if (cmp == 0) {
            // Mot trouvé
            courant->nombre_occurences--;

            if (courant->nombre_occurences == 0) {
                // Suppression physique du mot

                if (precedent == NULL) {
                    // Suppression en tête
                    liste = courant->suivant;
                } else {
                    // Suppression au milieu / fin
                    precedent->suivant = courant->suivant;
                }

                // Libération mémoire
                free(courant->mot);
                free(courant);
            }

            return liste; // Dans tous les cas, on retourne la tête
        }

        // Sinon on continue à avancer
        precedent = courant;
        courant = courant->suivant;
    }

    // Mot pas trouvé : on retourne la liste inchangée
    return liste;
}
/* ====== FIN retirerMot ====== */


// Affichage mots d'un lexique
void afficherMots(t_mot* liste) {
    if (liste == NULL) {
        printf("(Lexique vide)\n");
        return;
    }

    char derniereLettre = '\0'; // Pour suivre la dernière lettre affichée
    t_mot* courant = liste;

    while (courant != NULL) {
        char premiereLettre = tolower(courant->mot[0]); // On récupère la première lettre en minuscule

        if (premiereLettre != derniereLettre) {
            // Nouvelle lettre rencontrée
            printf("\n%c --- %s [%d]\n", toupper(premiereLettre), courant->mot, courant->nombre_occurences);
            derniereLettre = premiereLettre;
        } else {
            // Même lettre que précédemment
            printf("      %s [%d]\n", courant->mot, courant->nombre_occurences);
        }

        courant = courant->suivant;
    }

    printf("\n"); // Pour une jolie fin de liste
}
/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot* fusionner(t_mot* listeA, t_mot* listeB) {
    t_mot* result = NULL;
    t_mot* *lastPtr = &result;

    while (listeA != NULL && listeB != NULL) {
        int cmp = strcmp(listeA->mot, listeB->mot);

        if (cmp == 0) {
            // Mot en commun → fusionner les occurrences
            listeA->nombre_occurences += listeB->nombre_occurences;

            // Ajouter A à la nouvelle liste
            *lastPtr = listeA;
            lastPtr = &((*lastPtr)->suivant);

            // Avancer A et libérer B
            t_mot* tmpB = listeB;
            listeA = listeA->suivant;
            listeB = listeB->suivant;
            free(tmpB->mot);
            free(tmpB);
        }
        else if (cmp < 0) {
            // Mot de A vient avant → on le garde
            *lastPtr = listeA;
            lastPtr = &((*lastPtr)->suivant);
            listeA = listeA->suivant;
        }
        else {
            // Mot de B vient avant → on l'insère
            t_mot* suivantB = listeB->suivant;

            *lastPtr = listeB;
            lastPtr = &((*lastPtr)->suivant);

            listeB = suivantB;
        }
    }

    // Ajouter le reste de A ou de B
    if (listeA != NULL) {
        *lastPtr = listeA;
    } else {
        *lastPtr = listeB;
    }

    return result;
}
/* ====== FIN fusionner ====== */


// Import fichier de mots dans une liste
// Définition de constantes
#define TAILLE_NOM_FICHIER 100
#define TAILLE_LIGNE 100

t_mot* importerFichier(t_mot* liste) {
    char nom_base[100];
    char nom_fichier[105]; // 100 + ".txt" + \0

    printf("Entrez le nom du fichier (sans extension) : ");
    fgets(nom_base, sizeof(nom_base), stdin);
    nom_base[strcspn(nom_base, "\r\n")] = '\0'; // Nettoyage du \n

    snprintf(nom_fichier, sizeof(nom_fichier), "%s.txt", nom_base);

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", nom_fichier);
        return liste;
    }

    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Nettoyer \n
        ligne[strcspn(ligne, "\r\n")] = '\0';

        if (strlen(ligne) > 0) {
            liste = ajouterMot(liste, ligne);
        }
    }

    fclose(fichier);
    printf("Importation réussie depuis '%s'.\n", nom_fichier);
    return liste;
}
/* ====== FIN importerFichier ====== */


/* ====== Gestion des lexiques ====== */

// Fonctions de gestion des lexiques multiples
t_lexique* creerLexique(char* nom) {
    t_lexique* nouveau = (t_lexique*)malloc(sizeof(t_lexique));
    if (nouveau == NULL) {
        printf("Erreur d'allocation mémoire pour un lexique.\n");
        exit(EXIT_FAILURE);
    }

    // Allocation et copie du nom
    nouveau->nom = (char*)malloc((strlen(nom) + 1) * sizeof(char)); // +1 pour le caractère nul \n
    if (nouveau->nom == NULL) {
        printf("Erreur d'allocation mémoire pour le nom du lexique.\n");
        free(nouveau);
        exit(EXIT_FAILURE);
    }
    strcpy(nouveau->nom, nom);

    // Initialisation du reste
    nouveau->mots = NULL;
    nouveau->suivant = NULL;

    return nouveau;
}
/* ====== FIN creerLexique ====== */

// Fonction pour afficher les lexiques chacun attribué à un nombre que l'on peut choisir
void afficherLexiques(t_lexique* liste) {
    int i = 1;
    while (liste != NULL) {
        printf("%d. %s\n", i, liste->nom);
        liste = liste->suivant;
        i++;
    }
}
/* ====== FIN afficherLexiques ====== */

//Fonction pour choisir un lexique
t_lexique* choisirLexique(t_lexique* liste) {
    int choix;
    afficherLexiques(liste);
    printf("Choisissez un lexique (0 pour quitter) : ");
    scanf("%d", &choix);
    viderBuffer();

    if (choix == 0) {
        return NULL; // Quitter
    }

    // Parcourir la liste pour trouver le lexique choisi
    t_lexique* courant = liste;
    for (int i = 1; i < choix && courant != NULL; i++) {
        courant = courant->suivant;
    }

    if (courant == NULL) {
        printf("Choix invalide.\n");
        return NULL;
    }

    return courant;
}
/* ====== FIN choisirLexique ====== */




// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}

//fonction pour libérer la mémoire d'un lexique
void libererLexiques(t_lexique* liste) {
    while (liste != NULL) {
        // Libérer tous les mots du lexique
        t_mot* courantMot = liste->mots;
        while (courantMot != NULL) {
            t_mot* tmpMot = courantMot;
            courantMot = courantMot->suivant;

            free(tmpMot->mot);    // libérer la chaîne
            free(tmpMot);         // libérer la structure
        }

        // Libérer le nom du lexique
        free(liste->nom);

        // Passer au lexique suivant
        t_lexique* tmpLexique = liste;
        liste = liste->suivant;
        free(tmpLexique);
    }
}
/* ====== FIN libererLexiques ====== */