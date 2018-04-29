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
#include <math.h>

using namespace std;

JuegoHud::JuegoHud() {
    hud = new Hud();
    jugador = new Player();
    reloj = new sf::Clock();
    relojAtaqueEspecial = new sf::Clock();
    relojDesplazamiento = new sf::Clock();
    tiempo = new sf::Time();
    tiempoAtaqueEspecial = new sf::Time();
    tiempoDesplazamiento = new sf::Time();
    inercia = false;
    contador = 0;
    
    fondo = this->establecerTexturas("/home/fv/NetBeansProjects/Crazy-Carnival/resources/MicroMachines-Fondo.png");
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
    
    //Bucle del juego (necesario para cargar la ventana)
    while (window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
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
                            if(jugador->getEnfriamiento() == jugador->getTotalEnfriamiento())
                            {
                                hud->setAtaqueEspecial(true);
                            }
                            break;
                        case sf::Keyboard::F:
                            hud->setAtaqueEspecial(false);
                            hud->dibujar(window, false);
                            hud->modificarEnfriamiento(-jugador->getTotalEnfriamiento());
                        case sf::Keyboard::R:
                            hud->modoContrarreloj();
                            break;
                        case sf::Keyboard::E:
                            hud->elixirEncontrado();
                            break;
                        
                        //Controles para mover el personaje
                        case sf::Keyboard::Left:
                            
                            jugador->setEstadoPersonaje(2);
                            if(tiempoDesplazamiento->asSeconds() >= 0.10)
                            {
                                relojDesplazamiento->restart();
                                jugador->modificarSpriteCorrer();
                            }
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->setVelocidad(-2.0);
                            jugador->update(relojDesplazamiento);
                            cout << "acelera izquierda" << endl;
                            break;
                        case sf::Keyboard::Right:
                            //while(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                            jugador->setEstadoPersonaje(1);
                            if(tiempoDesplazamiento->asSeconds() >= 0.10)
                            {
                                relojDesplazamiento->restart();
                                jugador->modificarSpriteCorrer();
                            }
                            *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                            jugador->setVelocidad(2.0);
                            jugador->update(relojDesplazamiento);
                            cout << "acelera derecha" << endl;//}
                            //jugador->update(reloj);
                            break;
                        case sf::Keyboard::Up:
                            contador = 0;  
                            if(jugador->getEstadoPersonaje() != 3 && jugador->getEstadoPersonaje() != 4)
                            {
                                if(jugador->getEstadoPersonaje() == 1 || jugador->getSprite().getScale().x > 0.0)
                                {
                                    jugador->setEstadoPersonaje(3);
                                }
                                else if(jugador->getEstadoPersonaje() == 2 || jugador->getSprite().getScale().x < 0.0)
                                {
                                    jugador->setEstadoPersonaje(4);
                                }
                                
                            }
                            jugador->update(reloj);
                            break;
                        
                    }
                    break;
                    
                //El jugador debe frenar salvo que se pulse alguna tecla de movimiento.
                //Igualmente, el lapso de tiempo de deceleración es mínimo.
                case sf::Event::KeyReleased:
                    while((jugador->getSprite().getPosition().y < 240 || jugador->getEstadoPersonaje() > 0)){
                        
                        if(jugador->getVelocidad() != 0.0 && (jugador->getEstadoPersonaje() != 3 || jugador->getEstadoPersonaje() != 4))
                        {
                            jugador->setVelocidad(0.0);
                        }
                                                
                        if(jugador->getEstadoPersonaje() == 3 || jugador->getEstadoPersonaje() == 4)
                        {
                            jugador->setVelocidadSalto(-20.0 + contador);
                            contador += 2;
                        }
                        this->render(window);
                        if(jugador->getCuerpo()->GetPosition().y >= 240 && jugador->getVelocidad() == 0.0)
                        {
                            jugador->setEstadoPersonaje(0);
                        }
                    }
                    //SE CAMBIARÁ CUANDO HAYAN PLATAFORMAS
                    if((int) jugador->getSprite().getPosition().y <= 250 || (int) jugador->getSprite().getPosition().y >= 235)
                    {
                        //jugador->setVelocidadSalto(0.0);
                        jugador->getCuerpo()->SetAngularVelocity((abs(jugador->getSprite().getPosition().y - 240)) * (-1));
                        jugador->update(reloj);
                        inercia = false;
                        cout << "no tiene sentido" << endl;
                    }
                    break;
            }
        }
        this->render(window);
    }
}
void JuegoHud::render(sf::RenderWindow &window){
    window.clear();
    jugador->update(reloj);
    jugador->actualizarFisica();
    window.draw(spriteFondo);
    if((int) tiempo->asSeconds() == 1)
    {
        reloj->restart();
        hud->cambiarTexturaContador();
    }
    if(tiempoDesplazamiento->asSeconds() >= 0.25 && (jugador->getEstadoPersonaje()) == 0)
    {
        jugador->modificarSpriteReposo();
        relojDesplazamiento->restart();
    }
    if(tiempoAtaqueEspecial->asSeconds() >= 0.1 && hud->getAtaqueEspecial())
    {
        if(hud->getSpriteRecipienteVida().getColor() != sf::Color(50, 125, 255, 255))
        {
            hud->dibujar(window, true);
        }
        else
        {
            hud->dibujar(window, false);
        }
        relojAtaqueEspecial->restart();
    }
    hud->draw(window);
    jugador->draw(window);
    window.display();
    *tiempo = reloj->getElapsedTime();
    *tiempoAtaqueEspecial = relojAtaqueEspecial->getElapsedTime();
    *tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
}
