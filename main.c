#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

int main() {
    char choixMenu = '0' ;

    do {
        printf("\n========================================");
        printf("\n  [1] Afficher un lexique");
        printf("\n  [2] Ajouter un mot dans un lexique");
        printf("\n  [3] Retirer un mot d'un lexique");
        printf("\n  [4] Fusionner deux lexiques");
        printf("\n  [5] Charger un fichier dans un lexique");
        printf("\n  [6] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        viderBuffer();

        switch (choixMenu) {
            case '1' :
                printf("\n\n\t<Faire Afficher un lexique>\n\n");
                break;
            case '2' :
                printf("\n\n\t<Faire Ajouter un mot dans un lexique>\n\n");
                break;
            case '3' :
                printf("\n\n\t<Faire Retirer un mot d'un lexique>\n\n");
                break;
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
