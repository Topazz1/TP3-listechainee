#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

struct s_mot {
    char* mot;
    int nombre_occurences;
    struct mot* suivant;
};

typedef struct s_mot t_mot;


t_mot *creerMot(char *mot);

t_mot *ajouterMot(t_mot *liste, char *mot);

t_mot *retirerMot(t_mot *liste, char *mot);

void afficherMots(t_mot *liste);

t_mot *fusionner(t_mot *listeA, t_mot *listeB);

t_mot *importerFichier(t_mot *liste);


// fonction utile pour vider le tampon clavier
void viderBuffer() ;

#endif // TP3_H_INCLUDED
