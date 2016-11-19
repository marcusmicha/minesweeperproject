#include "header.h"


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
