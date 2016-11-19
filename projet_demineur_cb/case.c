#include "header.h"

/// Initialisation d'une case
void initCase(t_case *pt_case, int pos_x, int pos_y, int flag, int mine, int ouverte){
    pt_case->pos_x = pos_x;
    pt_case->pos_y = pos_y;
    pt_case->flag = flag;
    pt_case->mine = mine;
    pt_case->ouverte = ouverte;
}

/// Allocation dynamique de la m�moire pour le tableau
t_case** creerTab(int n_ligne, int n_col){
    int i=0;
    t_case** tab;

    tab = (t_case**)malloc(n_ligne*sizeof(t_case*));
    for(i=0; i<n_ligne; i++) tab[i] =(t_case*)malloc(n_col*sizeof(t_case));

    return tab;
}

/// Initialisation du tableau
void initTab(t_case** tab, int n_ligne, int n_col, int mines){
    srand(time(NULL)); // R�initialisation pour le random

    int i,j;
    t_case* pt_case = NULL;

    /// On initialise tout le tableau : chaque case n'a pas de mine ni de flag et n'est pas d�couverte
    for(i=0; i<n_ligne; i++)
    {
        for(j=0; j<n_col; j++)
        {
            pt_case = &(tab[i][j]);
            initCase(pt_case, i, j, 0, 0, 0);
        }
    }

    /// On attribue les mines al�atoirement dans la matrice
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

/// Affichage des donn�es d'une case
void affichCase(t_case* pt_case){
    printf("x = %d\n",pt_case->pos_x);
    printf("y = %d\n",pt_case->pos_y);
    if (pt_case->flag == 1) printf("Flag : Oui\n"); // si flag = 1 : flag sur la case
    else printf("Flag : Non\n"); // si flag = 0 : pas de flag sur la case
    if (pt_case->mine != 9) printf("Nombre de mines autour = %d\n", pt_case->mine); // si nombre entre 0 et 8 : nombre de mines autour
    else printf("Mine sur la case !\n"); // si nombre = 9 : mine sur la case
}

/// Affichage des donn�es du tableau
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

int decouvreCase(t_case** tab, int i, int j, int n_ligne, int n_col, int *nb_a_decouvrir) {
    int n_mines_autour = 0;

    /// Si la case est en dehors du tableau (i/j < 0, i>=nb_ligne, j>=nb_colonnes) alors on ne fait rien
    if ((i<0) || (j<0) || (i>=n_ligne) || (j>=n_col))
        return 0;

    /// Si la case est deja ouverte on ne fait rien
    if (tab[i][j].ouverte==1)
        return 0;

    else
    {
        /// Si la case poss�de une mine, on renvoie 1 pour dire que la partie est perdue !
        if (tab[i][j].mine==9)
            return 1;

        /// Pour regarder si la case poss�de des mines autour d'elle, alors
        else
        {
            if (i!=0) // Si on est sur la ligne tout en haut, on ne prend pas en compte les cases d'au dessus, donc si i!=0, on les prend en compte
            {
                /// Si on est pas sur la ligne du haut on regarde si il y a une mine au dessus
                if (tab[i-1][j].mine==9) n_mines_autour++; // si il y a une mine dans la case au dessus, on incr�mente n_mines_autour

                /// Si on est pas dans le coin en haut a gauche on regarde si il y a une mine au dessus � gauche
                if (j!=0)
                {
                    if (tab[i-1][j-1].mine==9) n_mines_autour++;
                }
                /// Si on est pas dans le coin en haut a droite on regarde si il y a une mine au dessus � droite
                if  (j!=(n_col-1))
                {
                    if (tab[i-1][j+1].mine==9) n_mines_autour++;
                }
            }

            if (i!=(n_ligne-1))
            {
                /// Si on est pas sur la ligne du bas on regarde si il y a une mine en dessous
                if (tab[i+1][j].mine==9) n_mines_autour++;

                /// Si on est pas dans le coin en bas a gauche on regarde si il y a une mine en dessous a gauche
                if (j!=0)
                {
                    if (tab[i+1][j-1].mine==9) n_mines_autour++;
                }
                /// Si on est pas dans le coin en bas a droite on regarde si il y a une mine en dessous � droite
                if  (j!=(n_col-1))
                {
                    if (tab[i+1][j+1].mine==9) n_mines_autour++;
                }
            }

            /// Si on est pas sur la colonne de gauche on regarde si il y a une mine a gauche
            if (j!=0)
            {
                if (tab[i][j-1].mine==9) n_mines_autour++;
            }

            /// Si on est pas sur la colonne de droite on regarde si il y a une mine a droite
            if (j!=(n_col-1))
            {
                if (tab[i][j+1].mine==9) n_mines_autour++;
            }
        }

        /// La case est ouverte et poss�de n nombre de mines autour
        tab[i][j].mine = n_mines_autour;
        tab[i][j].ouverte = 1;

        /// Si la case ne poss�de aucune mine autour d'elle, alors on ouvre les 8 cases autour d'elle
        if (tab[i][j].mine==0)
        {
            decouvreCase(tab,i-1,j-1,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i-1,j,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i-1,j+1,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i,j+1,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i+1,j+1,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i+1,j,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i+1,j-1,n_ligne,n_col, nb_a_decouvrir);
            decouvreCase(tab,i,j-1,n_ligne,n_col, nb_a_decouvrir);
        }
    }
    (*nb_a_decouvrir)--;
    return 2;
}



void menu(param* param_partie){

    /// On initialise les variables n�cessaires
    int ok=0, mines_min, mines_max;
    char choix;

    /// On initialise les valeurs � -1 pour les conditions de parties personnalis�es
    param_partie->nombre_mines=-1;
    param_partie->nombre_lignes=-1;
    param_partie->nombre_colonnes=-1;

    /// On affiche le menu avec les diff�rentes options possibles
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


    do {
        //do {
            printf("\nVotre choix : ");
            choix= getchar();
            clearBuffer();
            printf("%c\n", choix);
            //scanf("%d", &choix);
        //} while((choix<=0) || (choix>=6));

        switch (choix)
        {
            /// Cas '1' : partie facile : 10x10 et 15 mines
            case '1' :
                param_partie->nombre_colonnes=10;
                param_partie->nombre_lignes=10;
                param_partie->nombre_mines=15;
                ok=1;
                break;

            /// Cas '2' : partie moyenne : 15x15 et 45 mines
            case '2' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=45;
                ok=1;
                break;

            /// Cas '3' : partie difficile : 20x20 et 80 mines
            case '3' :
                param_partie->nombre_colonnes=15;
                param_partie->nombre_lignes=15;
                param_partie->nombre_mines=80;
                ok=1;
                break;

            /// Cas '4' : partie personnalis�e
            case '4' :

                /// L'utilisateur rentre le nombre de colonnes souhait�es
                printf("\nVeuillez rentrer le nombre de colonnes (min %d et max %d) : ", COL_MIN, COL_MAX);
                while(param_partie->nombre_colonnes < COL_MIN || param_partie->nombre_colonnes > COL_MAX)
                {
                    scanf("%d", &param_partie->nombre_colonnes);
                    if (param_partie->nombre_colonnes < COL_MIN || param_partie->nombre_colonnes > COL_MAX) // On blinde pour avoir une bonne valeur
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }

                /// L'utilisateur rentre le nombre de lignes souhait�es
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

                /// L'utilisateur rentre le nombre de mines souhait�es
                printf("\nVeuillez rentrer le nombre de mines entre %d et %d: ", mines_min, mines_max);
                while(  param_partie->nombre_mines < mines_min || param_partie->nombre_mines > mines_max)
                {
                    scanf("%d", &param_partie->nombre_mines);
                    if (param_partie->nombre_mines < mines_min || param_partie->nombre_mines > mines_max)
                        printf("Valeur invalide, veuillez rerentrer une valeur : ");
                }
                ok=1;
                break;

            /// Cas '5' : on quitte la partie
            case '5' :
                exit(0);// on renvoie le pointeur NULL. On prendra en compte le ponteur null pour quitter le programme dans le main.

            /// Autres cas : la valeur rentr�e n'est pas valide
            default :
                printf("Le choix ne correspond pas a un choix propose, veuillez reessayer.\n"); // on demande � l'utilisateur de re rentrer une valeur
                break; // on ne met pas la variable 'ok' � 1, donc on ne sort pas de la boucle.
        }
    } while (ok == 0);

}

/// Clear Buffer pour getchar
void clearBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


/// Affichage matrice de jeu
void affichTab(t_case** tab, param* p){
    int i, j;
    for(i = 0; i< p->nombre_lignes; i++){
        for(j = 0; j< p->nombre_colonnes; j++)
            if(tab[i][j].ouverte == 0){
                if(tab[i][j].flag == 1)
                    printf("F");
                else
                    printf("X");
            }
            else{
                if (tab[i][j].mine == 9)
                    printf("M");
                if (tab[i][j].mine >= 1 && tab[i][j].mine <=8)
                    printf("%d", tab[i][j].mine);
                if (tab[i][j].mine == 0)
                    printf(" ");
            }
        printf("\n");
    }

}

/// Affichage matrice de jeuBETA
void affichTabBETA(t_case** tab, param* p){
    int i, j;
    for(i = 0; i< p->nombre_lignes; i++){
        for(j = 0; j< p->nombre_colonnes; j++){
                if (tab[i][j].mine == 9)
                    printf("M");
                if (tab[i][j].mine >= 1 && tab[i][j].mine <=8)
                    printf("%d", tab[i][j].mine);
                if (tab[i][j].mine == 0)
                    printf(" ");
            }
        printf("\n");
    }
}

/// GOTOLIGCOL
void gotoligcol(int lig,int col)

{
    COORD coord_xy;
    coord_xy.X = lig;
    coord_xy.Y = col;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord_xy );
}

int actionClavier(t_case** tab, int *i, int *j, int* flagcount, param* param_partie, int* nb_a_decouvrir, int* perdu){
    char key = 'u';
    int quitter = 0;

    while(key == 'u')
    {
        key = getch();

        switch (key)
        {
            case '8' :
                if(*i>0)
                {
                    (*i)--;
                    gotoligcol(*j, *i);
                }
                break;
            case '5' :
                if(*i<(param_partie->nombre_lignes - 1))
                {
                    (*i)++;
                    gotoligcol(*j, *i);
                }
                break;
            case '4' :
                if(*j>0)
                {
                    (*j)--;
                    gotoligcol(*j, *i);
                }
                break;
            case '6' :
                if(*j<(param_partie->nombre_colonnes - 1))
                {
                    (*j)++;
                    gotoligcol(*j, *i);
                }
                break;
            case ' ' :
                modifFlag(tab, *i, *j, flagcount, param_partie);
                initAffich(tab, param_partie, *flagcount);
                gotoligcol(*j, *i);
                break;
            case '\r' :
                *perdu = decouvreCase(tab, *i, *j, param_partie->nombre_lignes, param_partie->nombre_colonnes, nb_a_decouvrir);
                initAffich(tab, param_partie, *flagcount);
                gotoligcol(*j, *i);
                break;
            case 'q' :
                quitter = 1;
        }
    }
    return quitter;
}

/// Gestion des drapeaux
void countFlag(param* p, int flagcount){
	int nbflagrestant;
	nbflagrestant = p->nombre_mines - flagcount;
	printf("Il vous reste %d flags\n", nbflagrestant);
}


void modifFlag(t_case** tab, int x, int y, int *flagcount, param* p){
	int nb_flag_restants = p->nombre_mines - (*flagcount);
	if((tab[x][y].ouverte !=1)&&((nb_flag_restants)>0)){
    	if(tab[x][y].flag == 1){
        	tab[x][y].flag = 0;
            (*flagcount)--;
    	}
    	else {
        	tab[x][y].flag = 1;
            (*flagcount)++;
    	}
	}
}

void initAffich(t_case** tab, param* param_partie, int flagcount)
{
    system("cls");
    gotoligcol(0,0);
    affichTab(tab, param_partie);
    gotoligcol(param_partie->nombre_colonnes + 8,5);
    countFlag(param_partie, flagcount);
    gotoligcol(0, param_partie->nombre_lignes + 2);
}


void boucleJeu(t_case** tab, int* flagcount, param* param_partie)
{
    int quitter = 0, perdu = 0, gagne = 0;
    int calc = ((param_partie->nombre_colonnes)*(param_partie->nombre_lignes)) - param_partie->nombre_mines;
    int x = (int) param_partie->nombre_lignes / 2;
    int y = (int) param_partie->nombre_colonnes / 2;


    int *nb_a_decouvrir;
    int* i;
    int* j;

    nb_a_decouvrir = &calc;
    i=&x;
    j=&y;

    gotoligcol(y,x);

    while ((quitter != 1) && (perdu != 1) && (gagne != 1))
    {
        quitter = actionClavier(tab, i, j, flagcount, param_partie, nb_a_decouvrir, &perdu);
        if((*nb_a_decouvrir)==0) gagne = 1;
    }

    gotoligcol(0, param_partie->nombre_lignes + 2);
    if(quitter == 1)
        printf("A bientot !\n");
    else if (perdu == 1)
        printf("Perdu !! ");
    else if (gagne == 1)
        printf("Bien Joue !!");

}
