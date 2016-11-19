#include "header.h"

int main()
{
    /// Déclaration des variables

    //t_case new_case;
    t_case** tab;
    int n_ligne, n_col, n_mines;
    param* param_partie = (param*) malloc(sizeof(param));

    /// Initialisation

    srand(time(NULL)); // Réinitialisation pour la fonction rand
    //int n_rand = rand()%10;

    /// Affichage du menu et choix des paramètres de la partie

    menu(param_partie);
    n_ligne = param_partie->nombre_lignes;
    n_col = param_partie->nombre_colonnes;
    n_mines = param_partie->nombre_mines;

    /// Affichage des paramètres de la partie

    printf ("\n\nParametres de la partie :\nColonnes : %d\nLignes : %d\nMines : %d\n\n", param_partie->nombre_colonnes, param_partie->nombre_lignes, param_partie->nombre_mines);

    /// Affichage test d'une case / Création de la première case

    //initCase(&new_case, 0, 0, 0, n_rand, 0); // Initialisation de la case à la position (0,0)
    //affichCase(&new_case);

    /// Creation de la matrice

    tab = creerTab(n_ligne, n_col);
    initTab(tab, n_ligne, n_col, n_mines);
    //affichTabData(tab, n_ligne, n_col);
    affichTabBETA(tab, param_partie);
    printf("\n");
    decouvreCase(tab, 5, 5, param_partie->nombre_lignes, param_partie->nombre_colonnes);

    ///On clear l'écran à l'aide de la fonction 'system("cls")'
    system("cls");
    affichTab(tab, param_partie);

    /// Libération de la mémoire allouée dynamiquement

    free(tab);
    free(param_partie);



    return 0;
}
