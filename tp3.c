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
