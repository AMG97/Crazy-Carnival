/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: fv
 *
 * Created on March 24, 2018, 12:01 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    float curar(float vRecuperada);
    float danyo(float vPerdida);
protected:
    float vida;
    float enfriamiento;
    float totalVida;
    float totalEnfriamiento;
};

#endif /* PLAYER_H */

