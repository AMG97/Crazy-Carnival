/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.hpp
 * Author: fv
 *
 * Created on March 24, 2018, 12:01 PM
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Hud;
class JuegoHud;
class Player {
public:
    static Player* Instance();
    Player();
    Player(const Player& orig);
    virtual ~Player();
    void update(sf::Clock *clock);
    void draw(sf::RenderWindow& window);
    void modificarSprite();
    void modificarSpriteReposo();
    sf::Sprite getSprite();
    void setEstadoPersonaje(int direccion);
    sf::FloatRect getGlobalBounds();
    void actualizarFisica();
    
    //Estas sí son de player
    int getEstadoPersonaje();
    void setVelocidadSalto(float altura);
    float getVelocidadSalto();
    void setVelocidad(float modificacionVelocidad);
    float getVelocidad();
    float getEnfriamiento();
    float getTotalEnfriamiento();
    
    b2Body *getCuerpo();
    void recibirDanyo(float danyo);
    void curar(float cura);
    void addPoints(int puntos);
    void setPoints(int puntos);
    int getPuntos();
    void setEnfriamiento(float cooldown);
    void addEnfriamiento(float cooldown);
    bool getElixir();
    void setElixir(bool e);
    bool changeGodMode();

protected:
    static Player* pinstance;
    
    JuegoHud *juego;
    //Hud *hud;
    bool elegirSprite;
    sf::Texture texturaPj;
    sf::Sprite personaje;
    int estadoPersonaje;
    int contadorSpriteReposo;
    int contadorSpriteCorrer;
    int contadorSpriteSalto;
    int puntuacion;
    //bool direccionIzquierda;
    float static vida;
    float static enfriamiento;
    float static totalVida;
    float static totalEnfriamiento;
    bool elixir, godMode;
    sf::Vector2f velocidad;
    b2World *mundo;
    b2Body *jugador;
    b2BodyDef jugadorDef;
    b2Fixture *fixJugador;
    b2FixtureDef fixJugadorDef;
    b2PolygonShape shapeJugador;
};

#endif /* PLAYER_HPP */

