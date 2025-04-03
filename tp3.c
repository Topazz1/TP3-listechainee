#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

// Création nouvel élément
t_mot *creerMot(char *mot) {
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN creerMot ====== */

// Ajout mot dans une liste
t_mot *ajouterMot(t_mot *liste, char *mot) {
    char i = 'a'; // initialiser le compteur i pour parcourir les lettres de l'alphabet
    t_mot *j = liste; // pointeur pour parcourir la liste de mots
    int debut = 1; // pour vérifier si un mot a déjà été affiché pour la lettre en cours

    // Parcours de la liste
    while (j != NULL) {
        // On vérifie si la première lettre du mot correspond à la lettre en cours
        if (j->mot[0] == i) {
            // Si c'est la première fois qu'on rencontre cette lettre, on affiche la lettre
            if (debut) {
                printf("%c --- %s [%d]\n", toupper(i), j->mot, j->nombre_occurence);
                debut = 0; // on a déjà affiché un mot pour cette lettre
            } else {
                // Sinon, on affiche simplement le mot
                printf("  --- %s [%d]\n", j->mot, j->nombre_occurence);
            }
        }
        // Si le mot ne commence pas par la lettre courante, on passe à la lettre suivante
        if (j->mot[0] > i) {
            i++; // on passe à la lettre suivante
            debut = 1; // on réinitialise le début pour la nouvelle lettre
        }
        j = j->suivant; // on passe au mot suivant dans la liste
    }
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN  ====== */


// Retrait occurence mot d'une liste
t_mot *retirerMot(t_mot *liste, char *mot) {
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN ajouterMot ====== */


// Affichage mots d'un lexique
void afficherMots(t_mot *liste){
    // à remplacer par le code la fonction
}
/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot *fusionner(t_mot *listeA, t_mot *listeB){
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN fusionner ====== */


// Import fichier de mots dans une liste
t_mot *importerFichier(t_mot *liste){
    return NULL; // à remplacer par le code la fonction
}
/* ====== FIN importerFichier ====== */




// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}
