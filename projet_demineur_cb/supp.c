#include "header.h"

/// Permet de changer la couleur de la console
void color(int texte,int fond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,fond*16+texte);
}
