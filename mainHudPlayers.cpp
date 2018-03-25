/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainHudPlayers.cpp
 * Author: fv
 *
 * Created on March 25, 2018, 3:40 AM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "hud.h"
#include "juegoHud.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

     //Variables HUD
    Hud *hud = new Hud();
    JuegoHud *juego = new JuegoHud();
    sf::Clock reloj;
    sf::Time tiempo;
    
    //Pruebas HUD
    sf::RenderWindow ventanaJuego(sf::VideoMode(640,480), "Crazy Carnival");
    
    juego->loop(ventanaJuego);
    
    return 0;
}

