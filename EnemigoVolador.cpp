#include "EnemigoVolador.hpp"
#include "EstadoJuego.hpp"
#include "Player.hpp"

namespace Crazy
{
    EnemigoVolador::EnemigoVolador(float posx, float posy) {
        sprite.CambiarTextura(_juego->recursos.GetTextura("Enemigo-Volador"));
        sprite.CambiarTextRect(0,0,50,40);
        sprite.CambiarOrigen(50/2,40/2);
        sprite.CambiarPosicion(posx, posy);
        sprite.EscalarProporcion(1.5,1.5);
        vida=20.0;
        posinix=sprite.GetX();
        posiniy=sprite.GetY();
        //contadorSpriteCorrer=0;
        rojo=false;
        SetDireccion(true);
        velocidad=2.7;
        alcancex=600;
        alcancey=400;
        movimiento=400;
        danyo=5;
        direccionSubir=false;
        _arma=NULL;
        puntos = 125/EstadoJuego::Instance()->getNumNivel()+125;
    }

    EnemigoVolador::EnemigoVolador(const EnemigoVolador& orig) {
    }

    EnemigoVolador::~EnemigoVolador() {
    }
    void EnemigoVolador::ModificarSpriteCorrer(){
        switch (contadorSpriteCorrer){
            case 0:
                sprite.CambiarTextRect(0,0,50,40);
                sprite.CambiarOrigen(50/2,40/2);
            break;
            case 1:
                sprite.CambiarTextRect(50,20,70,20);
                sprite.CambiarOrigen(70/2,20/2);
            break;
            case 2:
                sprite.CambiarTextRect(120,20,70,20);
                sprite.CambiarOrigen(70/2,20/2);
            break;
            case 3:
                sprite.CambiarTextRect(190,20,50,40);
                sprite.CambiarOrigen(50/2,40/2);
            break;
        }
        contadorSpriteCorrer++;
        if(contadorSpriteCorrer==4)
            contadorSpriteCorrer=0;
    }
    
    void EnemigoVolador::Update(int Posx, int Posy, Player* p){
        float x=sprite.GetX();
        float y=sprite.GetY();
        float diferenciax=Posx-x;
        float diferenciay=Posy-y;
        if(diferenciax<1200 && diferenciay<1200 && diferenciax>-1200 && diferenciay>-1200){
            if(abs(diferenciax)<alcancex && abs(diferenciay)<alcancey){
                if(Posx>x  && Posx-x>30)
                {
                    if(direccionIzq)
                        SetDireccion(false);

                    Mover(velocidad,0);
                }
                else if(Posx<x && x-Posx>30){
                    if(!direccionIzq)
                        SetDireccion(true);
                    Mover(-velocidad,0);
                }
                if(Posy>y)
                    Mover(0,velocidad/2);
                else 
                    Mover(0, -velocidad/2);
                if(tAtaque.GetSegundos()>1.0){
                    tAtaque.ReiniciarSegundos();
                    if(p->GetSprite().Interseccion2(sprite)){
                        p->RecibirDanyo(danyo);
                    }
                }

            }
            else{
                if(direccionIzq){
                    if(posinix-x>movimiento)
                        SetDireccion(false);
                    else{
                        Mover(-velocidad,0);
                    }
                }
                else{
                    if(x-posinix>movimiento){
                        SetDireccion(true);
                    }else{
                        Mover(velocidad,0);
                    }
                    if(tDesp.GetSegundos()>0.1){
                        ModificarSpriteCorrer();
                        tDesp.restart();

                    }
                }
                if(direccionSubir){
                    if(posiniy-y>40)
                        direccionSubir=false;
                    else{
                        Mover(0,-velocidad);
                    }
                }else{
                    if(y-posiniy>40)
                        direccionSubir=true;
                    else{
                        Mover(0,velocidad);
                    }
                }
            }
            if(tDesp.GetSegundos()>0.1){
                    ModificarSpriteCorrer();
                    tDesp.ReiniciarSegundos();
            }
            if(rojo && relojrojo.GetSegundos()<=0.2)
                sprite.CambiarColorRojo();
            else if(rojo && relojrojo.GetSegundos()>0.2){
                rojo=false;
                sprite.Parpadear(false);
            }
        }
    }
    
    void EnemigoVolador::Dibujar(){
        _juego->_ventana->DibujarSprite(sprite);
    }
    
    void EnemigoVolador::ModificarSprite(){
        
    }
    
    void EnemigoVolador::ModificarSpriteAtaque1(){
        
    }
    void EnemigoVolador::Update(int Posx, int Posy){
        
    }
    
    void EnemigoVolador::Mover(float x, float y){
        float sumx, sumy;
        if(x==0)
            sumx=0;
        else if(x>0)
            sumx=x+70/2+10;
        else
            sumx=x-70/2-10;
        if(y==0)
            sumy=0;
        else if(y>0)
            sumy=y+40/2;
        else
            sumy=y-40/2;
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()+sumy))
            sprite.Mover(x,y);
        else
            SetDireccion(!direccionIzq);
    }
}

