#include "biblioJeu2D.h"

#include <SFML/Graphics.hpp>

static const int CAPACITE_GRILLE{ 100 };
static const int TAILLE_CELLULE{ 30 };
static const sf::Color COULEUR_VIDE{ sf::Color(0, 0, 0, 255) };

static int hauteurGrille{ 0 };
static int largeurGrille{ 0 };
static sf::RenderWindow* fenetreSFML{ nullptr };
static sf::Color** couleurs{ nullptr };
static sf::Clock horloge{ };

bool InitialiserFenetre(int largeur, int hauteur, const std::string & titreFenetre)
{
    if (largeur > CAPACITE_GRILLE || hauteur > CAPACITE_GRILLE)
    {
        return false;
    }

    largeurGrille = largeur;
    hauteurGrille = hauteur;

	couleurs = new sf::Color* [largeurGrille];
    for (int i = 0; i < largeurGrille; ++i)
    {
        couleurs[i] = new sf::Color[hauteurGrille];
    }

    for (int i = 0; i < largeurGrille; ++i)
    {
        for (int j = 0; j < hauteurGrille; ++j)
        {
            couleurs[i][j] = COULEUR_VIDE;
        }
    }

    const int largeurFenetre = largeurGrille * TAILLE_CELLULE;
    const int hauteurFenetre = hauteurGrille * TAILLE_CELLULE;
    fenetreSFML = new sf::RenderWindow(sf::VideoMode(largeurFenetre, hauteurFenetre), titreFenetre);
	horloge = sf::Clock();
    return true;
}

void ColorerCellule(int x, int y, int r, int g, int b)
{
    couleurs[x][y] = sf::Color(r, g, b, 255);
}

void DessinerGrille()
{
    for (int i = 0; i < largeurGrille; ++i)
    {
        for (int j = 0; j < hauteurGrille; ++j)
        {
            sf::RectangleShape square(sf::Vector2f(TAILLE_CELLULE, TAILLE_CELLULE));
            square.setPosition(1.f * i * TAILLE_CELLULE, 1.f * j * TAILLE_CELLULE);
            square.setFillColor(couleurs[i][j]);
            fenetreSFML->draw(square);
        }
    }
}

bool FenetreEstActive()
{
    if (fenetreSFML == nullptr || !fenetreSFML->isOpen())
    {
        return false;
    }

    sf::Event evenement;
    while (fenetreSFML->pollEvent(evenement))
    { 
        if (evenement.type == sf::Event::Closed)
        {
            fenetreSFML->close();
            return false;
        }
    }

    fenetreSFML->clear(COULEUR_VIDE);
    DessinerGrille();
    fenetreSFML->display();

    return true;
}

int TempsEcouleMicrosecondes()
{
    return static_cast<int>(horloge.restart().asMicroseconds());
}

bool FlecheHautEstAppuyee() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Up); }
bool FlecheBasEstAppuyee() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Down); }
bool FlecheDroiteEstAppuyee() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Right); }
bool FlecheGaucheEstAppuyee() { return sf::Keyboard::isKeyPressed(sf::Keyboard::Left); }
