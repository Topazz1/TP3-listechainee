
## notes

### **Fonction creerMot**

→ **Demande classique** : juste initialiser les champs d’une structure s_mot :

- Allouer dynamiquement un char* pour le mot ;
- copier le mot (déjà transformé en minuscules si besoin) ;
- initialiser le compteur d’occurrence à 1 ;
- initialiser le pointeur suivant à NULL.

> 🚨 **Problématique : S’occuper du stockage de lexiques.**
>
> Le sujet impose de gérer **au moins deux lexiques**, donc il est nécessaire de structurer notre code pour manipuler plusieurs listes de t_mot.
>
> - Créer une structure **s_lexique** qui contient :
>     - un **char*** pour le nom du lexique (optionnel mais recommandé pour l’interface) ;
>     - un **t_mot*** (pointeur vers le premier mot du lexique) ;
>     - un **struct s_lexique* suivant** pour gérer une liste chaînée de lexiques.
> - Implémenter un menu permettant la création de lexiques avec deux options :
>     - **À partir d’un fichier** : utiliser *importerFichier*.
>     - **À partir d’un mot** : créer un **t_mot*** avec *creerMot* et l’inclure dans un nouveau lexique.
> - À prévoir :
>     - **creerLexique(char *nom)** → crée un lexique vide.
>     - **afficherLexiques()** → affiche tous les lexiques créés avec un identifiant pour sélection.
>     - Gestion d’un lexique vide.
>         - (Optionnel) Attribution automatique de noms (Lexique 1, Lexique 2, etc.).

### **Fonction ajouterMot**

→ Étapes à suivre :

- Créer une **copie du mot en minuscules** (transformation ASCII directe).
- Chercher si le mot est déjà présent :
    - Si oui → incrémenter *nombre_occurences* ;
    - Si non → l’insérer en **ordre alphabétique** dans la liste.

> 🚨 **Problématique : Insertion ordonnée et complexité.**
>
> - Il faut comparer les mots un à un (**ordre lexicographique**) ;
> - L’ajout peut être :
>     - En tête ;
>     - En milieu (entre deux mots) ;
>     - En fin.
>
> ➕ Prévoir une fonction **insererEnOrdre(t_mot* debut, t_mot* nouveau)** pour factoriser.
>
> ⚠️ **Ne pas oublier :**
>
> - Gérer le cas où la liste est **vide** ;
> - Utiliser strcmp ou une fonction maison avec gestion stricte de la **casse**. (idée : utilisation du code ASCII pour s’occuper de la casse)

### **Fonction retirerMot**

→ Étapes :

- Trouver le mot dans la liste ;
- Décrémenter son nombre_occurences ;
- Si le compteur atteint 0, **supprimer le mot** de la liste.

> 🚨 **Problématique : Suppression dans une liste simplement chaînée**
>
> - On a besoin de **garder un pointeur vers l’élément précédent** ;
> - Gérer le cas où le mot à retirer est **le premier de la liste** ;
> - Gérer les suppressions successives si besoin.
>
> 🧼 Appeler **free()** pour :
>
> - **le mot** (la chaîne de caractères) ;
> - la structure **t_mot**.

### **Fonction afficherMots**

→ Affiche tous les mots du lexique, regroupés par initiale.

Format attendu :

```
A --- abeille [1]
      arbre [3]
      avion [1]
B --- bateau [1]
      bulle [2]
```

### **Fonction fusionner**

→ Intégrer les mots de listeB dans listeA, en incrémentant les occurrences si doublon.

→ À la fin : **listeB doit être vide et libérée**.

> 🚨 **Problématique : Complexité **
> Il faut que ce soit en O(n).

### **Fonction importerFichier**

→ Ouvre un fichier texte, lit ligne par ligne et ajoute chaque mot dans la liste.

> 🚨 **Problématique : Gestion du fichier et robustesse**
>
> À vérifier :
>
> - Si le fichier existe (test FILE *f = fopen(...)) ;
> - Si une ligne est vide (strlen(mot) == 0) ;
> - Conserver le lexique actuel (ajout, pas écrasement) ;
> - Nettoyage de chaque ligne (\n, \r, etc.) ;
> - Ne pas oublier de fermer le fichier avec fclose(f).
>
> ➕ Utiliser fgets() pour lire chaque ligne.

### **Interface – menu principal**

Menu demandé :

1. Afficher un lexique
2. Ajouter un mot dans un lexique
3. Retirer un mot d’un lexique
4. Fusionner deux lexiques
5. Charger un fichier dans un lexique
6. Quitter

> 🚨 **Problématique : Sélection de lexique + flexibilité utilisateur**
>
> - Créer une **liste chaînée de lexiques** pour tous les gérer.
> - Chaque action doit :
>     - Lister les lexiques existants (afficherLexiques()) ;
>     - Demander à l’utilisateur de choisir un identifiant (de chaque lexique);
>     - Appliquer l’action sur le lexique sélectionné.
>
> ➕ Rajouter une **option 0. Créer un lexique** en début de programme :
>
> - Nommer les lexiques (facultatif mais ergonomique).
>
> 🧼 À la fin : **libérer tous les lexiques et mots alloués dynamiquement.**
