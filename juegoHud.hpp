/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juegoHud.hpp
 * Author: fv
 *
 * Created on March 24, 2018, 12:14 PM
 */

#ifndef JUEGOHUD_HPP
#define JUEGOHUD_HPP
//#include <Box2D/Box2D/Box2D.h>
//#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Player;
class Enemigo;
class Hud;
class JuegoHud{
public:
    JuegoHud();
    //JuegoHud(const JuegoHud& orig);
    virtual ~JuegoHud();
    sf::Texture establecerTexturas(sf::String direccion);
    void loop(sf::RenderWindow &window);
    Player* getPlayer();
    vector<Enemigo*> getEnemigos();
    
private:
    Hud *hud;
    Player *jugador;
    vector<Enemigo*>enemigos;
    sf::Clock *reloj;
    sf::Clock *relojDesplazamiento;
    sf::Time *tiempo;
    sf::Time *tiempoDesplazamiento;
    bool pararSalto;
    
    //box2D
    sf::Texture fondo;
    sf::Sprite spriteFondo;
    
};

#endif /* JUEGOHUD_HPP */

