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
        enfriamiento = 0.0f;
        caida=0;
        lastpared=0;
        invulnerable=false;
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
        if(!invulnerable){
            ModificarVida(-danyo);
            rojo=true;
            relojrojo.ReiniciarSegundos();
            //ModificarEnfriamiento(danyo * 0.75f);
        }
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
    
    short int Player::GetMorir(){
        return MORIR;
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

    void Player::setElixir(bool v) {
        elixir = v;
    }
    
    bool Player::getElixir(){
        return elixir;
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
    
    int Player::GetLastPared() {
        return lastpared;
    }
    void Player::tparedRestart() {
        tpared.ReiniciarSegundos();
    }
    
    float Player::Gettpared(){
        return tpared.GetSegundos();
    }
    int Player::getContadorInvulnerable()
    {
        return contadorInvulnerable;
    }
    void Player::AumentarContadorInvulnerable()
    {
        if(tInvulnerable.GetSegundos() >= 1){
            contadorInvulnerable++;
            tInvulnerable.ReiniciarSegundos();
        }
    }
    
    bool Player::isAttacking() {
        return atacando;
    }
    void Player::setInvulnerable(bool esInvulnerable)
    {
        tInvulnerable.ReiniciarSegundos();
        invulnerable = esInvulnerable;
        if(invulnerable)
            sprite.CambiarColorAmarillo();
        else
        {
            sprite.CambiarColorBlanco();
            contadorInvulnerable = 0;
        }
    }
    bool Player::getInvulnerable()
    {
        return invulnerable;
    }


}