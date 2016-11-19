#include "header.h"


/// Boucle gérant le jeu
int boucleJeu(t_case** tab, int* flagcount, param* param_partie) {
    int quitter = 0, perdu = 0, gagne = 0;
    char key = 'x';
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
    if(quitter == 1){
        gotoligcol(param_partie->nombre_colonnes + 8,5);
        printf("A bientot !\n");
        return 1;
    }
    else if (perdu == 1){
        system("cls");
        gotoligcol(0,0);
        affichTabFin(tab, param_partie);
        gotoligcol(param_partie->nombre_colonnes + 8,5);
        printf("Perdu !! \n");
    }
    else if (gagne == 1){
        gotoligcol(param_partie->nombre_colonnes + 8,5);
        printf("Bien Joue !!\n");
    }

    gotoligcol(0, param_partie->nombre_lignes + 2);
    printf("Appuyez sur Entrer pour revenir au menu");

    while(key!='\r') key = getch();

    return quitter;
}

/// Action a effectuer en fonction de la touche rentrée au clavier
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
            case '2' :
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

/// GOTOLIGCOL
void gotoligcol(int lig,int col){
    COORD coord_xy;
    coord_xy.X = lig;
    coord_xy.Y = col;

    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord_xy );
}

/// Découvre une case et les case alentours si '0' sur la case actuelle
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
        /// Si la case possède une mine, on renvoie 1 pour dire que la partie est perdue !
        if (tab[i][j].mine==9)
            return 1;

        /// Pour regarder si la case possède des mines autour d'elle, alors
        else
        {
            if (i!=0) // Si on est sur la ligne tout en haut, on ne prend pas en compte les cases d'au dessus, donc si i!=0, on les prend en compte
            {
                /// Si on est pas sur la ligne du haut on regarde si il y a une mine au dessus
                if (tab[i-1][j].mine==9) n_mines_autour++; // si il y a une mine dans la case au dessus, on incrémente n_mines_autour

                /// Si on est pas dans le coin en haut a gauche on regarde si il y a une mine au dessus à gauche
                if (j!=0)
                {
                    if (tab[i-1][j-1].mine==9) n_mines_autour++;
                }
                /// Si on est pas dans le coin en haut a droite on regarde si il y a une mine au dessus à droite
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
                /// Si on est pas dans le coin en bas a droite on regarde si il y a une mine en dessous à droite
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

        /// La case est ouverte et possède n nombre de mines autour
        tab[i][j].mine = n_mines_autour;
        tab[i][j].ouverte = 1;

        /// Si la case ne possède aucune mine autour d'elle, alors on ouvre les 8 cases autour d'elle
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

/// Gestion des drapeaux (décompte)
void countFlag(param* p, int flagcount){
	int nbflagrestant;
	nbflagrestant = p->nombre_mines - flagcount;
	printf("Il vous reste %d flags\n", nbflagrestant);
}

/// Gestion des drapeaux (flag sur case ou non)
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
void affichTabFin(t_case** tab, param* p){
    int i, j;
    for(i = 0; i< p->nombre_lignes; i++){
        for(j = 0; j< p->nombre_colonnes; j++){
                if (tab[i][j].mine == 9)
                    printf("M");
               else
                    printf("/");
            }
        printf("\n");
    }
}

