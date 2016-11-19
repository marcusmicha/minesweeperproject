#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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

/// Initialisation de la partie
/// Initialisation d'une case
void initCase(t_case *pt_case, int pos_x, int pos_y, int flag, int mine, int ouverte);

/// Allocation dynamique de la mémoire pour le tableau
t_case** creerTab(int n_ligne, int n_col);

/// Initialisation d'un tableau
void initTab(t_case** tab, int n_ligne, int n_col, int mines);

/// Affichage du menu et retour des paramètres de la partie
void menu(param* param_partie);



/// Fonctions de Test
/// Affichage des données d'une case
void affichCase(t_case *pt_case);

/// Affichage des données d'un tableau
void affichTabData(t_case** tab, int n_ligne, int n_col);

/// Affichage matrice de jeuBETA
void affichTabBETA(t_case** tab, param* p);




/// Découverte d'une case : renvoie 0 si la case est deja ouverte, renvoie 1 si il y a une mine, renvoie 2 si tout c'est déroulé normalement
int decouvreCase(t_case** tab, int i, int j, int n_ligne, int n_col);

/// Affichage matrice de jeu
void affichTab(t_case** tab, param* p);

/// GOTOLIGCOL
void gotoligcol(int x,int y);

/// Gestion de la position du curseur et du clavier
int actionClavier(t_case** tab, int *i, int *j, int* flagcount, param* param_partie);

/// Clear Buffer pour getchar
void clearBuffer();

/// (Ré)initialisation de l'affichage de jeu
void initAffich(t_case** tab, param* param_partie, int flagcount);
#endif // HEADER_H_INCLUDED
