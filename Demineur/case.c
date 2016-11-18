#include "header.h"
/// Clear Buffer
void clearBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/// Initialisation d'une case
void initCase(t_case *pt_case, int pos_x, int pos_y, int flag, int mine, int ouverte){
    pt_case->pos_x = pos_x;
    pt_case->pos_y = pos_y;
    pt_case->flag = flag;
    pt_case->mine = mine;
    pt_case->ouverte = ouverte;
}

/// Allocation dynamique de la mémoire pour le tableau
t_case** creerTab(int n_ligne, int n_col){
    int i=0;
    t_case** tab;

    tab = (t_case**)malloc(n_ligne*sizeof(t_case*));
    for(i=0; i<n_ligne; i++) tab[i] =(t_case*)malloc(n_col*sizeof(t_case));

    return tab;
}

/// Initialisation du tableau
void initTab(t_case** tab, int n_ligne, int n_col){
    int i,j;
    t_case* pt_case = NULL;

    for(i=0; i<n_ligne; i++)
    {
        for(j=0; j<n_col; j++)
        {
            pt_case = &(tab[i][j]);
            initCase(pt_case, i, j, 0,1,0);
        }
    }
}

/// Affichage des données d'une case
void affichCase(t_case* pt_case){
    printf("x = %d\n",pt_case->pos_x);
    printf("y = %d\n",pt_case->pos_y);
    if (pt_case->flag == 1) printf("Flag : Oui\n"); // si flag = 1 : flag sur la case
    else printf("Flag : Non\n"); // si flag = 0 : pas de flag sur la case
    if (pt_case->mine != 9) printf("Nombre de mines autour = %d\n", pt_case->mine); // si nombre entre 0 et 8 : nombre de mines autour
    else printf("Mine sur la case !\n"); // si nombre = 9 : mine sur la case
}

/// Affichage des données du tableau
void affichTabData(t_case** tab, int n_ligne, int n_col){
    int i,j;
    printf("\n\nLe tableaux est :\n");
    for(i=0; i<n_ligne; i++){
        for(j=0;j<n_col;j++){
            printf("\nLigne %d Colonne %d :\n", i+1, j+1);
            affichCase(&tab[i][j]);
        }
    }
}

param* menu(param* param_partie){

    /// On initialise les variables nécessaires
    int ok=0, mines_min, mines_max;
    char choix;

    /// On initialise les valeurs à -1 pour les conditions de parties personnalisées
    param_partie->nombre_mines=-1;
    param_partie->nombre_lignes=-1;
    param_partie->nombre_colonnes=-1;

    /// On affiche le menu avec les différentes options possibles
    printf("##########################################\n");
    printf("#              Bienvenue !!              #\n");
    printf("#                                        #\n");
    printf("# 1. Partie facile (10x10 | 15 mines)    #\n");
    printf("# 2. Partie normale (15x15 | 45 mines)   #\n");
    printf("# 3. Partie difficile (20x20 | 80 mines) #\n");
    printf("# 4. Partie personnalisee                #\n");
    printf("# 5. Quitter                             #\n");
    printf("#                                        #\n");
    printf("##########################################\n");
    printf("\nVotre choix : ");

    do {
        
        choix = getchar();
        clearBuffer();

        switch (choix)
        {
            /// Cas 1 : partie facile : 10x10 et 15 mines
            case '1' :
                param_partie->nombre_colonnes=10;
                param_partie->nombre_lignes=10;
                param_partie->nombre_mines=15;
                ok=1;
                break;

            /// Cas 2 : partie moyenne : 15x15 et 45 mines
            case '2' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=45;
                ok=1;
                break;

            /// Cas 3 : partie difficile : 20x20 et 80 mines
            case '3' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=80;
                ok=1;
                break;

            /// Cas 4 : partie personnalisée
            case '4' :

                /// L'utilisateur rentre le nombre de colonnes souhaitées
                printf("\nVeuillez rentrer le nombre de colonnes (min %d et max %d) : ", COL_MIN, COL_MAX);
                while(param_partie->nombre_colonnes < COL_MIN || param_partie->nombre_colonnes > COL_MAX)
                {
                    scanf("%d", &param_partie->nombre_colonnes);
                    if (param_partie->nombre_colonnes < COL_MIN || param_partie->nombre_colonnes > COL_MAX) // On blinde pour avoir une bonne valeur
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }

                /// L'utilisateur rentre le nombre de lignes souhaitées
                printf("\nVeuillez rentrer le nombre de lignes (min %d et max %d) : ", LIG_MIN, LIG_MAX);
                while(param_partie->nombre_lignes < LIG_MIN || param_partie->nombre_lignes> LIG_MAX)
                {
                    scanf("%d", &param_partie->nombre_lignes);
                    if (param_partie->nombre_lignes < LIG_MIN || param_partie->nombre_lignes > LIG_MAX) // blindage
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }

                /// On calcule le nombre de mines min et max en fonction de la taille de la matrice
                mines_min = (int) (param_partie->nombre_colonnes * param_partie->nombre_lignes) * 0.05; //minimum 1 mine pour 20 cases
                mines_max = (int) (param_partie->nombre_colonnes * param_partie->nombre_lignes) * 0.4;  //maximum 2 mines pour 5 cases

                /// L'utilisateur rentre le nombre de mines souhaitées
                printf("\nVeuillez rentrer le nombre de mines entre %d et %d: ", mines_min, mines_max);
                while(  param_partie->nombre_mines < mines_min || param_partie->nombre_mines > mines_max)
                {
                    scanf("%d", &param_partie->nombre_mines);
                    if (param_partie->nombre_mines < mines_min || param_partie->nombre_mines > mines_max)
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }
                ok=1;
                break;

            /// Cas 5 : on quitte la partie
            case 5 :
                return NULL; // on renvoie le pointeur NULL. On prendra en compte le ponteur null pour quitter le programme dans le main.

            /// Autres cas : la valeur rentrée n'est pas valide
            default :
                printf("Le choix ne correspond pas a un choix propose, veuillez reessayer.\n"); // on demande à l'utilisateur de re rentrer une valeur
                break; // on ne met pas la variable 'ok' à 1, donc on ne sort pas de la boucle.
        }
    } while (ok == 0);

    /// on renvoie le pointeur sur la structure comprenant les paramètres de la partie
    return param_partie;

}
