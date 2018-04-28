/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: fv
 *
 * Created on March 25, 2018, 3:40 AM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "player.hpp"
#include "hud.hpp"
#include "juegoHud.hpp"
#include "Juego.hpp"

#include "fsMath.hpp"
#include "fsWorld.hpp"
#include "fsBody.hpp"


using namespace std;
/*
 * 
 */
int main() {

     //Variables HUD
    Hud *hud = new Hud();
    JuegoHud *juego = new JuegoHud();
    sf::Clock reloj;
    sf::Time tiempo;
    
    fs::fsVec2 gravedad(0,-9.8);
    fs::fsWorld mundo(gravedad);
    
    fs::fsBody body();
    
    //body.getAngle();
    
    
    b2Body cuerpo(NULL, &mundo);
    //cout<<  <<endl;
    
    //Pruebas HUD
    Crazy::Juego::Instance();
    Crazy::Juego::Instance()->Iniciar();
    sf::RenderWindow ventanaJuego(sf::VideoMode(640,480), "Crazy Carnival");
    
    juego->loop(ventanaJuego);
    
    return 0;
}

