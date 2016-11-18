#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define COL_MIN 5
#define COL_MAX 35
#define LIG_MIN 5
#define LIG_MAX 25



/// Définition de la structure d'une case
typedef struct cases{
    int pos_x; // position x dans la matrice
    int pos_y; // position y dans la matrice
    int flag; // drapeau present (1) ou non (0)
    int mine; // nombre de mines autour : de 0 à 8, 9 pour une mine sur la case
    int ouverte; // case découverte (1) ou non (0)
}t_case;

/// Définition de la structure dans laquelle sont rangés les paramètres de la partie
typedef struct parametres{
    int nombre_lignes;
    int nombre_colonnes;
    int nombre_mines;
}param;

/// Initialisation d'une case
void initCase(t_case *pt_case, int pos_x, int pos_y, int flag, int mine, int ouverte);

/// Allocation dynamique de la mémoire pour le tableau
t_case** creerTab(int n_ligne, int n_col);

/// Initialisation d'un tableau
void initTab(t_case** tab, int n_ligne, int n_col);

/// Affichage des données d'une case
void affichCase(t_case *pt_case);

/// Affichage des données d'un tableau
void affichTabData(t_case** tab, int n_ligne, int n_col);

param* menu(param* param_partie);


#endif // HEADER_H_INCLUDED
