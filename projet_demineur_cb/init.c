#include "header.h"

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
void initTab(t_case** tab, int n_ligne, int n_col, int mines){
    srand(time(NULL)); // Réinitialisation pour le random

    int i,j;
    t_case* pt_case = NULL;

    /// On initialise tout le tableau : chaque case n'a pas de mine ni de flag et n'est pas découverte
    for(i=0; i<n_ligne; i++)
    {
        for(j=0; j<n_col; j++)
        {
            pt_case = &(tab[i][j]);
            initCase(pt_case, i, j, 0, 0, 0);
        }
    }

    /// On attribue les mines aléatoirement dans la matrice
    while (mines > 0)
    {
        i = rand()%n_ligne;
        j = rand()%n_col;

        pt_case = &(tab[i][j]);
        if(pt_case->mine!=9)
        {
            pt_case->mine = 9;
            mines--;
        }
    }
}

/// Affichage du menu
void menu(param* param_partie){

    /// On initialise les variables nécessaires
    int ok=0, mines_min, mines_max, coul_texte, coul_fond;
    char choix;

    /// On initialise les valeurs à -1 pour les conditions de parties personnalisées
    param_partie->nombre_mines=-1;
    param_partie->nombre_lignes=-1;
    param_partie->nombre_colonnes=-1;



    do {
        coul_texte=-1;
        coul_fond=-1;
        /// On affiche le menu avec les différentes options possibles
        printf("##########################################\n");
        printf("#              Bienvenue !!              #\n");
        printf("#                                        #\n");
        printf("# 0. Regles du jeu                       #\n");
        printf("# 1. Reglage des couleurs du jeu         #\n");
        printf("# 2. Partie facile (10x10 | 15 mines)    #\n");
        printf("# 3. Partie normale (15x15 | 45 mines)   #\n");
        printf("# 4. Partie difficile (20x20 | 80 mines) #\n");
        printf("# 5. Partie personnalisee                #\n");
        printf("# 6. Quitter                             #\n");
        printf("#                                        #\n");
        printf("##########################################\n");

        printf("\nVotre choix : ");
        choix= getch();
        //printf("%c\n", choix);
            //scanf("%d", &choix);
        //} while((choix<=0) || (choix>=6));

        switch (choix)
        {
            /// Cas '0' : on affiche les regles du jeu
            case '0' :
                system("cls");
                gotoligcol(0,0);
                printf("Regles du jeu :\n\nLe but du jeu est de trouver ou se trouvent toutes les mines dans le quadrillage. Pour cela, il faut ouvrir les cases une par une. Lorsqu'une case est ouverte, alors ");
                printf("la case affiche le nombre de mines presentes dans les cases adjacentes.   Si il n'y a aucune mine autour, toutes les cases autour sont alors ouvertes.    Le joueur a la possibilite ");
                printf("de poser un drapeau sur la case pour signaler une    bombe. La partie est gagnée lorsque toutes les cases ne possédant pas de bombes sont ouvertes.\n");
                printf("Aller vers le haut : touche 8\nAller vers le bas : touche 2\nAller vers la gauche : touche 4\nAller vers la droite : touche 6\nOuvrir une case : touche Entrer\n");
                printf("Poser un drapeau : touche Espace\nQuitter la partie en cours : touche q\n\n");
                break;

            /// Cas '1' : Réglage des couleurs du jeu
            case '1' :
                printf("Couleurs :\nNoir : 0\nBleu fonce : 1\n2 : Vert\n3 : Bleu-gris\n4 : Marron\n5 : Violet\n6 : Kaki\n7 : Gris clair\n8 : Gris\n9 : Bleu\n10 : Vert fluo\n11 : Turquoise\n12 : Rouge\n13 : Rose fluo\n14 : Jaune fluo\n15 : Blanc\n\n");
                printf("Quelle couleur souhaitez vous pour le texte ? : ");
                while(coul_texte < 0 || coul_texte> 15)
                {
                    scanf("%d", &coul_texte);
                    if (coul_texte < 0 || coul_texte> 15) // On blinde pour avoir une bonne valeur
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }
                printf("Quelle couleur souhaitez vous pour le fond ? : ");
                while(coul_fond < 0 || coul_fond> 15)
                {
                    scanf("%d", &coul_fond);
                    if (coul_fond < 0 || coul_fond> 15) // On blinde pour avoir une bonne valeur
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }
                color(coul_texte, coul_fond);
                system("cls");
                break;

            /// Cas '2' : partie facile : 10x10 et 15 mines
            case '2' :
                param_partie->nombre_colonnes=10;
                param_partie->nombre_lignes=10;
                param_partie->nombre_mines=15;
                ok=1;
                break;

            /// Cas '3' : partie moyenne : 15x15 et 45 mines
            case '3' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=45;
                ok=1;
                break;

            /// Cas '4' : partie difficile : 20x20 et 80 mines
            case '4' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=80;
                ok=1;
                break;

            /// Cas '5' : partie personnalisée
            case '5' :

                system("cls");
                gotoligcol(0,0);

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

            /// Cas '6' : on quitte la partie
            case '6' :
                system("cls");
                printf("A Bientot !\n");
                exit(0);// on renvoie le pointeur NULL. On prendra en compte le ponteur null pour quitter le programme dans le main.

            /// Autres cas : la valeur rentrée n'est pas valide
            default :
                system("cls");
                printf("Le choix ne correspond pas a un choix propose, veuillez reessayer.\n\n");
                break; // on ne met pas la variable 'ok' à 1, donc on ne sort pas de la boucle.
        }
    } while (ok == 0);

}

/// (Ré)Initialisation de l'affichage après le menu
void initAffich(t_case** tab, param* param_partie, int flagcount){
    system("cls");
    gotoligcol(0,0);
    affichTab(tab, param_partie);
    gotoligcol(param_partie->nombre_colonnes + 8,5);
    countFlag(param_partie, flagcount);
    gotoligcol(0, param_partie->nombre_lignes + 2);
}
