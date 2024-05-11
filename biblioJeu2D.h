#pragma once

#include <string>

// La taille de la grille est en nombre de cellules (gros pixels)
bool InitialiserFenetre(int largeurNbCellules, int hauteurNbCellules, const std::string& titreFenetre);

// x est dans l'intervalle [0, largeurNbCellules - 1]
// y est dans l'intervalle [0, hauteurNbCellules - 1]
// r, g et b sont dans l'intervalle [0, 255]
void ColorerCellule(int x, int y, int r, int g, int b);

// Appeler cette fonction pour afficher les cellules colorées à l'écran, une fois par frame (chaque itération de jeu).
bool FenetreEstActive();

// Produit le nombre de microsecondes écoulés depuis le dernier appel à la routine.
int TempsEcouleMicrosecondes();

// Indique si les flèches du clavier sont appuyées.
bool FlecheHautEstAppuyee();
bool FlecheBasEstAppuyee();
bool FlecheDroiteEstAppuyee();
bool FlecheGaucheEstAppuyee();
