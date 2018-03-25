/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:01 PM
 */

#include "player.h"

Player::Player() {
    //pruebas jugador, variables
    vida = 60.0;
    enfriamiento = 0.0;
    totalVida = vida;
    totalEnfriamiento = 30.0;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

