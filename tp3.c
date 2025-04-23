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
void afficherMots(t_mot *liste){
    char i = 'a'; // initialiser le compteur i pour parcourir les lettres de l'alphabet
    t_mot *j = liste; // pointeur pour parcourir la liste de mots
    int debut = 1; // pour vérifier si un mot a déjà été affiché pour la lettre en cours

    // Parcours de la liste
    while (j != NULL) {
        // On vérifie si la première lettre du mot correspond à la lettre en cours
        if (j->mot[0] == i) {
            // Si c'est la première fois qu'on rencontre cette lettre, on affiche la lettre
            if (debut) {
                printf("%c --- %s [%d]\n", toupper(i), j->mot, j->nombre_occurences);
                debut = 0; // on a déjà affiché un mot pour cette lettre
            } else {
                // Sinon, on affiche simplement le mot
                printf("  --- %s [%d]\n", j->mot, j->nombre_occurences);
            }
        }
        // Si le mot ne commence pas par la lettre courante, on passe à la lettre suivante
        if (j->mot[0] > i) {
            i++; // on passe à la lettre suivante
            debut = 1; // on réinitialise le début pour la nouvelle lettre
        }
        j = j->suivant; // on passe au mot suivant dans la liste
    }
}
/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot *fusionner(t_mot *listeA, t_mot *listeB){
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN fusionner ====== */


// Import fichier de mots dans une liste
// Définition de constantes
#define TAILLE_NOM_FICHIER 100
#define TAILLE_LIGNE 100

t_mot* importerFichier(t_mot* liste) {
    char nom_base[TAILLE_NOM_FICHIER];
    char nom_fichier[TAILLE_NOM_FICHIER + 5]; // 4 pour ".txt" + 1 pour '\0'

    printf("Entrez le nom du fichier (sans extension) : ");
    scanf("%s", nom_base);

    // On construit le nom complet
    snprintf(nom_fichier, sizeof(nom_fichier), "%s.txt", nom_base);

    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier '%s'.\n", nom_fichier);
        return liste;
    }

    char ligne[TAILLE_LIGNE];

    while (fgets(ligne, sizeof(ligne), fichier)) {
        // Nettoyer \n ou \r éventuels
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




// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}
