#include "Player.hpp"
#include "Motor.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Player::Player()
    {
        ataqueEspecial = false;
        direccionIzq = false;
        Atacado2 = false;
        estado = REPOSO;
        contadorSpriteCorrer = 0;
        contadorSpriteReposo = 0;
        contadorSpriteSalto = 0;
        contadorSpriteAtaque1=0;
        contadorSpriteAtaque2=0;
        angulo=0;
        velSalto=0;
        velocidad=0;
        golpear=false;
        puntuacion = 0;
        elixir = false;
        rojo=false;
        caida=0;
        lastpared=0;
    }
    
    float Player::GetEnfriamiento()
    {
        return enfriamiento;
    }
    
    float Player::GetTotalEnfriamiento()
    {
        return totalEnfriamiento;
    }
    
    void Player::SetEnfriamiento(float e)
    {
        enfriamiento = e;
    }
    
    void Player::ModificarEnfriamiento(float modificador)
    {
        enfriamiento += modificador;
        if(enfriamiento > totalEnfriamiento)
        {
            enfriamiento = totalEnfriamiento;
        }
        else if(enfriamiento < 0.0)
        {
            enfriamiento = 0.0;
        }
    }
    
    bool Player::GetAtaqueEspecial()
    {
        return ataqueEspecial;
    }
    
    void Player::SetAtaqueEspecial(bool ataque)
    {
        ataqueEspecial = ataque;
    }
    
    bool Player::AtaqueEspecialActivado()
    {
        ataqueEspecial = false;
        if (enfriamiento == totalEnfriamiento)
        {
            ataqueEspecial = true;
        }
        return ataqueEspecial;
    }
    
    float Player::GetTAtque2()
    {
        if(!Atacado2)
            return 10000;
        else
            return tAtaque2.GetSegundos();
    }
    
    void Player::Curar(float cura){
        ModificarVida(cura);
    }
    
    void Player::RecibirDanyo(float danyo)
    {
        ModificarVida(-danyo);
        rojo=true;
        relojrojo.ReiniciarSegundos();
        //ModificarEnfriamiento(danyo * 0.75f);
        
    }
    
    short int Player::GetEstado()
    {
        return estado;
    }
    
    short int  Player::GetCorrer()
    {
        return CORRER;
    }
    short int  Player::GetCorrerAtras()
    {
        return CORRERATRAS;
    }
    
    short int  Player::GetSaltar()
    {
        return SALTO;
    }
    
    short int  Player::GetReposo()
    {
        return REPOSO;
    }
    
    short int Player::GetAtaque1(){
        return ATAQUE1;
    }
    
    short int Player::GetAtaque2(){
        return ATAQUE2;
    }
    
    short int Player::GetDeslizarse(){
        return DESLIZARSE;
    }
    
    void Player::SetEstado(short int est)
    {
        estado = est;
        if(estado==ATAQUE2 && AtaqueEspecialActivado())
            Atacado2=true;
    }
    
    float Player::GetVelocidadSalto()
    {
        return velSalto;
    }
    
    void Player::SetVelocidadSalto(float v)
    {
        velSalto=v;
    }
    
    bool Player::getDireccion(){
        return direccionIzq;
    }
    
    void Player::CambiarDireccion()
    {
        
        if(direccionIzq)
        {
            CambiarDireccionDer();
        }
        else
        {
            CambiarDireccionIzq();
        }
        _arma->CambiarDireccion();
    }
    
    void Player::Dibujar()
    {
        _juego->_ventana->DibujarSprite(sprite);
        _arma->Dibujar();
    }

    void Player::SetElixir(bool v) {
        elixir = v;
    }

    void Player::addPuntuacion(int puntos) {
        puntuacion += puntos;
    }

    int Player::getPuntuacion() {
        return puntuacion;
    }

    void Player::setPuntuacion(int puntos) {
        puntuacion = puntos;
    }
    
    void Player::MoverX(float x){
        float sumx;
        if(x==0)
            sumx=0;
        else if(x>0)
            sumx=x+70/2;
        else
            sumx=x-70/2;
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()+30) &&
           !EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()-30))
            sprite.Mover(x,0);
    }
    
    void Player::MoverY(){
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+sprite.GetAlto()/2) && velSalto==0){
            if(estado==DESLIZARSE)
                caida+=0.2;
            else
                caida+=0.4;
            sprite.Mover(0,caida);
        }else{
            if(caida!=0){
                caida=0;
                velSalto=0;
                sprite.CambiarPosicion(sprite.GetX(),floor(sprite.GetY()/48)*48+13);
            }
        }
        
        if((velSalto!=0 && estado!=DESLIZARSE) || (estado==DESLIZARSE && velSalto<0))
        {
            velSalto=velSalto+0.5;
        }
        if(velSalto>4)
            velSalto=4;
        if(sprite.GetY()-sprite.GetAlto()/2-20>0){
            if(velSalto<0 && EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()-sprite.GetAlto()/2+10)){
                velSalto=0;
            }
        }else{
            velSalto=0;
        }
        sprite.Mover(0,velSalto);
    }
    int Player::GetLastPared() {
        return lastpared;
    }
    void Player::tparedRestart() {
        tpared.ReiniciarSegundos();
    }
    
    float Player::Gettpared(){
        return tpared.GetSegundos();
    }
    bool Player::isAttacking() {
        return atacando;
    }



}