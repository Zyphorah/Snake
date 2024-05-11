#pragma once

#include <string>

// La taille de la grille est en nombre de cellules (gros pixels)
bool InitialiserFenetre(int largeurNbCellules, int hauteurNbCellules, const std::string& titreFenetre);

// x est dans l'intervalle [0, largeurNbCellules - 1]
// y est dans l'intervalle [0, hauteurNbCellules - 1]
// r, g et b sont dans l'intervalle [0, 255]
void ColorerCellule(int x, int y, int r, int g, int b);

// Appeler cette fonction pour afficher les cellules color�es � l'�cran, une fois par frame (chaque it�ration de jeu).
bool FenetreEstActive();

// Produit le nombre de microsecondes �coul�s depuis le dernier appel � la routine.
int TempsEcouleMicrosecondes();

// Indique si les fl�ches du clavier sont appuy�es.
bool FlecheHautEstAppuyee();
bool FlecheBasEstAppuyee();
bool FlecheDroiteEstAppuyee();
bool FlecheGaucheEstAppuyee();
