#include "header.h"

int main()
{
    /// D�claration des variables

    //t_case new_case;
    t_case** tab;
    int n_ligne, n_col, n_mines, quitter = 0;
    int i,j;
    //int quitter=0;
    param* param_partie = (param*) malloc(sizeof(param));

    color(0,15);

    /// Initialisation

    srand(time(NULL)); // R�initialisation pour la fonction rand
    //int n_rand = rand()%10;

    /// Affichage du menu et choix des param�tres de la partie

    while(quitter != 1){
        system("cls");
        menu(param_partie);
        n_ligne = param_partie->nombre_lignes;
        n_col = param_partie->nombre_colonnes;
        n_mines = param_partie->nombre_mines;

        /// Affichage des param�tres de la partie

        //printf ("\n\nParametres de la partie :\nColonnes : %d\nLignes : %d\nMines : %d\n\n", param_partie->nombre_colonnes, param_partie->nombre_lignes, param_partie->nombre_mines);

        /// Affichage test d'une case / Cr�ation de la premi�re case

        //initCase(&new_case, 0, 0, 0, n_rand, 0); // Initialisation de la case � la position (0,0)
        //affichCase(&new_case);

        /// Creation de la matrice

        tab = creerTab(n_ligne, n_col);
        initTab(tab, n_ligne, n_col, n_mines);
        //affichTabData(tab, n_ligne, n_col);
        //affichTabBETA(tab, param_partie);
        //printf("\n");
        //decouvreCase(tab, 5, 5, param_partie->nombre_lignes, param_partie->nombre_colonnes);

        ///On clear l'�cran � l'aide de la fonction 'system("cls")'
        int flagcount = 0;
        //int i=5, j=5;
        initAffich(tab, param_partie, flagcount);

        boucleJeu(tab, &flagcount, param_partie);
        /// Lib�ration de la m�moire allou�e dynamiquement


        free(tab);



    }

    free(param_partie);



    return 0;
}
