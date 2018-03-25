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
#include "player.h"
#include "hud.h"
#include "juegoHud.h"

using namespace std;

JuegoHud::JuegoHud() {
    hud = new Hud();
    reloj = new sf::Clock();
    tiempo = new sf::Time();
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
    
   //Generamos la cámara
   /* sf::View camara (sf::Vector2f(coches[0]->getSpriteCoche().getPosition().x,
            coches[0]->getSpriteCoche().getPosition().y), sf::Vector2f(640, 480));*/

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
                            hud->modificarVida(-6);
                            break;
                        case sf::Keyboard::C:
                            hud->modificarVida(6);
                            break;
                        case sf::Keyboard::F:
                            hud->modificarEnfriamiento(-6);
                            break;
                        case sf::Keyboard::V:
                            hud->modificarEnfriamiento(6);
                            break;
                        case sf::Keyboard::E:
                            hud->modoContrarreloj();
                            break;
                        case sf::Keyboard::R:
                            hud->elixirEncontrado();
                            break;
                    }
            }
        }
        window.clear();
        hud->draw(window);
        if((int) tiempo->asSeconds() == 1)
        {
            cout << "entra" <<endl;
            reloj->restart();
            hud->cambiarTexturaContador();
        }    
        *tiempo = reloj->getElapsedTime();
        window.display();
    }
}