#include <iostream>
#include <string>
#include <clocale>
#include "biblioJeu2D.h"

using namespace std;

enum Direction
{
    Haut,
    Bas,
    Gauche,
    Droite
};

struct Position
{
    int x{ 0 }, y{ 0 };
};

struct ParametresJeu
{
    const int largeur{ 20 };
    const int hauteur{ 25 };
    const string nomFenetre{ "Jeu Snake" };
};

struct teste
{
    int teste{};
};

struct RGB
{
    int rouge{ 0 };
    int vert{ 0 };
    int bleu{ 0 };
};

void GenererCouleurAleatoire(RGB& couleur) 
{
    couleur.rouge = rand() % 206 + 50; 
    couleur.vert = rand() % 206 + 50;
    couleur.bleu = rand() % 206 + 50;
}

void DessinerSnake(Position positionsSnake[], int longueurSnake)
{
    const int capacity{ 3 };
    RGB couleur;

    for (int i = 0; i < longueurSnake; i++)
    {
        if (i == 0)
        {
            ColorerCellule(positionsSnake[i].x, positionsSnake[i].y, 255, 255, 255);
        }
        else
        {
            GenererCouleurAleatoire(couleur);
            ColorerCellule(positionsSnake[i].x, positionsSnake[i].y,couleur.rouge, couleur.vert,couleur.bleu);
        }
    }
}

void EffacerDernierePosition(Position positionsSnake[], int longueurSnake, Position& dernierePosition)
{
    if (longueurSnake > 0)
    {
        ColorerCellule(positionsSnake[longueurSnake - 1].x, positionsSnake[longueurSnake - 1].y, 0, 0, 0);
        dernierePosition.x = positionsSnake[longueurSnake - 1].x;
        dernierePosition.y = positionsSnake[longueurSnake - 1].y;
    }
}

void GererInputUtilisateur(Direction& directionActuelle)
{
    if (FlecheHautEstAppuyee())
    {
        directionActuelle = Haut;
    }
    else if (FlecheBasEstAppuyee())
    {
        directionActuelle = Bas;
    }
    else if (FlecheDroiteEstAppuyee())
    {
        directionActuelle = Droite;
    }
    else if (FlecheGaucheEstAppuyee())
    {
        directionActuelle = Gauche;
    }
}

void AgrandirSnake(Position& dernierePosition, Position positionsSnake[], int& longueurSnake, int& cyclesSnake)
{
    if (cyclesSnake == 4)
    {
        positionsSnake[longueurSnake] = dernierePosition;
        longueurSnake++;
        cyclesSnake = 0;
    }
    cyclesSnake++;
}

void TeleporterSnake(Position& position, const ParametresJeu& parametres)
{
    if (position.x >= parametres.largeur)
    {
        position.x = 0;
    }
    else if (position.x < 0)
    {
        position.x = parametres.largeur - 1;
    }

    if (position.y >= parametres.hauteur)
    {
        position.y = 0;
    }
    else if (position.y < 0)
    {
        position.y = parametres.hauteur - 1;
    }
}

void DeplacerSnake(Direction directionActuelle, Position positionsSnake[], int& longueurSnake, int& cyclesSnake, const ParametresJeu& parametres)
{
    Position dernierePosition;
    EffacerDernierePosition(positionsSnake, longueurSnake, dernierePosition);

    for (int i = longueurSnake - 1; i > 0; --i)
    {
        positionsSnake[i] = positionsSnake[i - 1];
    }

    switch (directionActuelle)
    {
    case Haut:
        positionsSnake[0].y -= 1;
        break;
    case Bas:
        positionsSnake[0].y += 1;
        break;
    case Gauche:
        positionsSnake[0].x -= 1;
        break;
    case Droite:
        positionsSnake[0].x += 1;
        break;
    }

    AgrandirSnake(dernierePosition, positionsSnake, longueurSnake, cyclesSnake);
    TeleporterSnake(positionsSnake[0], parametres);
}

bool VerifierCollision(Position positionsSnake[], int longueurSnake)
{
    for (int i = 1; i < longueurSnake; i++)
    {
        if ((positionsSnake[0].x == positionsSnake[i].x && positionsSnake[0].y == positionsSnake[i].y))
        {
            return true;
        }
    }
    return false;
}

bool ActualiserSnake(Direction directionActuelle, Position positionsSnake[], int& cyclesSnake, int& longueurSnake, const ParametresJeu& parametres)
{
    DeplacerSnake(directionActuelle, positionsSnake, longueurSnake, cyclesSnake, parametres);

    return VerifierCollision(positionsSnake, longueurSnake);
}

void GenererSnake(Position positionsSnake[], const ParametresJeu& parametres)
{
    positionsSnake[0].x = rand() % (parametres.largeur - 5 - 4) + 4;
    positionsSnake[0].y = rand() % (parametres.hauteur - 5 - 4) + 4;

    for (int i = 1; i < 4; i++)
    {
        positionsSnake[i] = positionsSnake[0];
    }
}

void InitialiserJeu(Position positionsSnake[], ParametresJeu& parametres)
{
    InitialiserFenetre(parametres.largeur, parametres.hauteur, parametres.nomFenetre);
    GenererSnake(positionsSnake, parametres);
}
Direction DirectionAleatoire()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int valeurAleatoire = rand() % 4;

    switch (valeurAleatoire)
    {
    case 0:
        return Haut;
    case 1:
        return Bas;
    case 2:
        return Gauche;
    case 3:
        return Droite;
    default:
        return Droite;
    }
}
bool ExecuterJeu(Position positionsSnake[], int& longueurSnake, ParametresJeu& parametres)
{
    Direction directionActuelle = DirectionAleatoire();
   
    int tempsEcoule{ 0 };
    int cyclesSnake{ 0 };

    while (FenetreEstActive())
    {
        tempsEcoule += TempsEcouleMicrosecondes();
        GererInputUtilisateur(directionActuelle);

        if (tempsEcoule >= 250000)
        {
            if (!ActualiserSnake(directionActuelle, positionsSnake, cyclesSnake, longueurSnake, parametres))
            {
                DessinerSnake(positionsSnake, longueurSnake);
                tempsEcoule = 0;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

void TerminerJeu(int longueurSnake)
{
    cout << "Game Over: Nombre de points " << longueurSnake << endl;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    setlocale(LC_ALL, "");

    Position positionsSnake[1000];
    int longueurSnake{ 3 };
    ParametresJeu parametres;
    InitialiserJeu(positionsSnake, parametres);

    if (!ExecuterJeu(positionsSnake, longueurSnake, parametres))
    {
        TerminerJeu(longueurSnake);
    }
    return 0;
}