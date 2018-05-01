/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juegoHud.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:14 PM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "hud.hpp"
#include "juegoHud.hpp"
#include "box.h"

using namespace std;

JuegoHud::JuegoHud() {
    hud = new Hud();
    jugador = new Player();
    reloj = new sf::Clock();
    relojDesplazamiento = new sf::Clock();
    tiempo = new sf::Time();
    tiempoDesplazamiento = new sf::Time();
    pararSalto = false;
    
    fondo = this->establecerTexturas("resources/MicroMachines-Fondo.png");
    spriteFondo.setTexture(fondo);
    spriteFondo.setOrigin(2000/2, 4000/2);
}

//JuegoHud::JuegoHud(const juegoHud& orig) {
//}

JuegoHud::~JuegoHud() {

}
sf::Texture JuegoHud::establecerTexturas(sf::String direccion)
{
    sf::Texture textura;
    if(!textura.loadFromFile(direccion))
    {    
        std::cerr << "Error al cargar el sprite";
        exit(0);
    }
    return textura;
}
void JuegoHud::loop(sf::RenderWindow &window){
    
    int i = 0;
    window.setFramerateLimit(60);
    
   //Generamos la cámara
   /* sf::View camara (sf::Vector2f(coches[0]->getSpriteCoche().getPosition().x,
            coches[0]->getSpriteCoche().getPosition().y), sf::Vector2f(640, 480));*/

    //Bucle del juego (necesario para cargar la ventana)
    while (window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            sf::Vector2i ratonpos;
            bool dire;
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                /*MIO*/
                case sf::Event::MouseButtonPressed:
                    switch(event.key.code){
                        case sf::Mouse::Left:
                            ratonpos=(sf::Mouse::getPosition(window));
                            if(jugador->getDireccion() && jugador->getSprite().getPosition().x<ratonpos.x){
                                jugador->setDireccion(false);
                            }else if(!jugador->getDireccion() && jugador->getSprite().getPosition().x>ratonpos.x){
                                jugador->setDireccion(true);
                            }
                            jugador->setAtaque1(true,ratonpos);
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->update(relojDesplazamiento);
                        break;
                        
                        case sf::Mouse::Right:
                            ratonpos=(sf::Mouse::getPosition(window));
                            if(jugador->getDireccion() && jugador->getSprite().getPosition().x<ratonpos.x){
                                jugador->setDireccion(false);
                            }else if(!jugador->getDireccion() && jugador->getSprite().getPosition().x>ratonpos.x){
                                jugador->setDireccion(true);
                            }
                            jugador->setAtaque2(true,ratonpos);
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->update(relojDesplazamiento);
                        break;
                    }
                    
                    
                //Se establecen las teclas del juego y su función
                case sf::Event::KeyPressed:
                    
                    switch (event.key.code){
                        case sf::Keyboard::Q:
                            window.close();
                            exit(0);
                            break;
                        
                        //Controles para probar HUD
                        case sf::Keyboard::D:
                            jugador->curar(6);
                            break;
                        case sf::Keyboard::C:
                            jugador->recibirDanyo(3);
                            break;
                        case sf::Keyboard::R:
                            hud->modoContrarreloj();
                            break;
                        case sf::Keyboard::E:
                            hud->elixirEncontrado();
                            break;
                        
                        //Controles para mover el personaje
                        case sf::Keyboard::Left:
                            //while(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                            //jugador->actualizarFisica();
                            if(jugador->getSprite().getScale().x > 0.0)
                            {
                                jugador->setDireccion(true);
                            }
                            if(tiempoDesplazamiento->asSeconds() >= 0.10)
                            {
                                relojDesplazamiento->restart();
                                if(!jugador->getAtaque1() && !jugador->getAtaque2())
                                    jugador->modificarSpriteCorrer();
                                else if(jugador->getAtaque1())
                                    jugador->modificarSpriteAtaque1();
                                else
                                    jugador->modificarSpriteAtaque2();
                            }
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->setVelocidad(-0.2);
                            jugador->update(relojDesplazamiento);
                            break;
                        case sf::Keyboard::Right:
                            //while(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            if(jugador->getSprite().getScale().x < 0.0)
                            {
                                jugador->setDireccion(false);
                            }
                            if(tiempoDesplazamiento->asSeconds() >= 0.10)
                            {
                                relojDesplazamiento->restart();
                                if(!jugador->getAtaque1() && !jugador->getAtaque2())
                                    jugador->modificarSpriteCorrer();
                                else if(jugador->getAtaque1())
                                    jugador->modificarSpriteAtaque1();
                                else
                                    jugador->modificarSpriteAtaque2();
                            }
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->setVelocidad(0.2);
                            jugador->update(relojDesplazamiento);
                            break;
                    }
                    break;
                    
                //El jugador debe frenar salvo que se pulse alguna tecla de movimiento.
                //Igualmente, el lapso de tiempo de deceleración es mínimo.
                case sf::Event::KeyReleased:
                    while((!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (jugador->getVelocidad() != 0.0 || jugador->getVelocidadSalto() != 0.0)){
                        if(jugador->getVelocidad() != 0.0)
                        {
                            jugador->setVelocidad(0.0);
                        }
                        if((int) jugador->getSprite().getPosition().y < 240)
                        {
                            if(jugador->getVelocidadSalto() < 5.0 && (int) jugador->getSprite().getPosition().y < 240)
                            {
                                jugador->setVelocidadSalto(0.6);
                            }                            
                        }
                        else if((int) jugador->getSprite().getPosition().y <= 242 || (int) jugador->getSprite().getPosition().y >= 238)
                        {
                            jugador->setVelocidadSalto(0.0);
                            jugador->getSprite().setPosition(jugador->getSprite().getPosition().x, 240);
                            pararSalto = false;
                            //cout << "no tiene sentido" << endl;
                        }
                        jugador->update(reloj);
                        window.clear();
                        jugador->actualizarFisica();
                        window.draw(spriteFondo);
                        hud->draw(window);
                        jugador->draw(window);
                        window.display();
                        //cout << "decelera" << endl;
                        //cout<<jugador->getVelocidadSalto()<<endl;
                    }
                        break;
            }
        }
        window.clear();
        jugador->update(reloj);
        jugador->actualizarFisica();
        window.draw(spriteFondo);
        hud->draw(window);
        jugador->draw(window);
        if((int) tiempo->asSeconds() == 1)
        {
            reloj->restart();
            hud->cambiarTexturaContador();
        }
        if(tiempoDesplazamiento->asSeconds() >= 0.1 && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        {
            relojDesplazamiento->restart();
            if(jugador->getAtaque1()){
                jugador->modificarSpriteAtaque1();
            }else if(jugador->getAtaque2()){
                jugador->modificarSpriteAtaque2();
            }
            else{
            jugador->modificarSpriteReposo();
            }
        }
        *tiempo = reloj->getElapsedTime();
        *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
        //cout<<jugador->getVelocidad()<<endl;
        window.display();
    }
}