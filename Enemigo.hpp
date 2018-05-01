/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.hpp
 * Author: fv
 *
 * Created on May 1, 2018, 8:23 PM
 */

#ifndef ENEMIGO_HPP
#define ENEMIGO_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Arma;
class Enemigo {
public:
    Enemigo();
    Enemigo(const Enemigo& orig);
    virtual ~Enemigo();
    void update(sf::Vector2f posplayer);
    void draw(sf::RenderWindow& window);
    void modificarSpriteCorrer();
    void modificarSpriteAtaque1();
    void setDireccion(bool direccion);
private:
    sf::Texture texturaEnemigo;
    sf::Sprite enemigo;
    sf::Vector2f alcance;
    float angulo;
    float velocidad;
    sf::Vector2f posini;
    sf::Vector2f pos;
    int contadorSpriteCorrer;
    int contadorSpriteAtaque1;
    float vida;
    bool Ataque1;
    bool direccionIzquierda;
    Arma* arma;
    float movimiento;
    sf::Clock tAtaque;
    sf::Clock tDesp;
};

#endif /* ENEMIGO_HPP */

