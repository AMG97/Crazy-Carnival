#include "Enemigo.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Enemigo::Enemigo(int n) {
        sprite.CambiarTextura(_juego->recursos.GetTextura("Enemigo-Pistola1"));
        sprite.CambiarTextRect(0,0,70,80);
        sprite.CambiarOrigen(70/2,80/2+10);
        if(n==1)
            sprite.CambiarPosicion(600, EstadoJuego::Instance()->_level->getAltura()*48-48*3-2-sprite.GetAlto()+20);
        else 
            sprite.CambiarPosicion(1100, EstadoJuego::Instance()->_level->getAltura()*48-48*3-2-sprite.GetAlto()+20);
        _arma=new Arma(0,sprite.GetX(),sprite.GetY(),false);
        sprite.EscalarProporcion(1.5,1.5);
        vida=45.0;
        posinix=sprite.GetX();
        posiniy=sprite.GetY();
        contadorSpriteCorrer=0;
        contadorSpriteAtaque1=0;
        Ataque1=false;
        rojo=false;
        angulo=0;
        SetDireccion(true);
        velocidad=1.5;
        alcancex=400;
        alcancey=200;
        movimiento=300;
    }

    Enemigo::Enemigo(const Enemigo& orig) {
    }

    Enemigo::~Enemigo() {
    }
    
    void Enemigo::ModificarSpriteAtaque1(){
        sprite.CambiarTextRect(contadorSpriteAtaque1*70,80,70,80);
        contadorSpriteAtaque1++;
        if(contadorSpriteAtaque1==2){
            contadorSpriteAtaque1=0;
            _arma->Disparar(angulo);
            tAtaque.restart();
            Ataque1=false;
        }
    }
    
    void Enemigo::ModificarSpriteCorrer(){
        sprite.CambiarTextRect(contadorSpriteCorrer*70,0,70,80);
        contadorSpriteCorrer++;
        if(contadorSpriteCorrer==3){
            contadorSpriteCorrer=0;
        }
    }
    
    void Enemigo::SetDireccion(bool direccion)
    {
        if(!direccion && direccionIzq){
            CambiarDireccionDer();
        }
        else if(direccion && !direccionIzq){
            CambiarDireccionIzq();
        }
        direccionIzq=direccion;
    }
    
    void Enemigo::Update(int Posx, int Posy)
    {
        float x=sprite.GetX();
        float y=sprite.GetY();
        float diferenciax=Posx-x;
        float diferenciay=Posy-y;
        angulo=atan2(diferenciax,diferenciay)*180/3.14159;
        bool mov=false;
        if(abs(diferenciax)<alcancex && abs(diferenciay)<alcancey){
            if(Posx>x)
            {
                if(direccionIzq)
                    SetDireccion(false);
                if(Posx-x>movimiento/2)
                {
                    sprite.Mover(velocidad,0);
                    mov=true;
                }
            }
            else if(Posx<x){
                if(!direccionIzq)
                    SetDireccion(true);
                if(x-Posx>movimiento/2)
                {
                    sprite.move(-velocidad,0);
                    mov=true;
                }
            }
            if(tAtaque.GetSegundos()>2.5)
                Ataque1=true;
            if(tDesp.GetSegundos()>0.1){
                if(Ataque1){
                    ModificarSpriteAtaque1();
                    tDesp.ReiniciarSegundos();
                }
                else if(tAtaque.GetSegundos()<2 && mov && tDesp.GetSegundos()>0.2){
                    ModificarSpriteCorrer();
                    tDesp.ReiniciarSegundos();
                }
            }
        }else{
            if(direccionIzq){
                if(posinix-x>movimiento)
                    SetDireccion(false);
                else{
                    sprite.Mover(-velocidad,0);
                    if(tDesp.GetSegundos()>0.1){
                        if(Ataque1){
                            ModificarSpriteAtaque1();
                            tDesp.restart();
                        }
                        else if(tDesp.GetSegundos()>0.2){
                            ModificarSpriteCorrer();
                            tDesp.ReiniciarSegundos();
                        }
                    }
                }
        }
            else{
                if(x-posinix>movimiento){
                    SetDireccion(true);
                }else{
                    sprite.Mover(velocidad,0);
                }
                if(tDesp.GetSegundos()>0.1){
                    if(Ataque1){
                        ModificarSpriteAtaque1();
                        tDesp.restart();
                    }
                    else if(tDesp.GetSegundos()>0.2){
                        ModificarSpriteCorrer();
                        tDesp.restart();
                    }
                }
            }
        }
        if(rojo && relojrojo.GetSegundos()<=0.2)
            sprite.CambiarColorRojo();
        else if(rojo && relojrojo.GetSegundos()>0.2){
            rojo=false;
            sprite.Parpadear(false);
        }
    }
    
    void Enemigo::Dibujar(){
        _juego->_ventana->DibujarC(sprite);
        _arma->Dibujar();
    }
    
    void Enemigo::RecibirDanyo(float dan){
        vida-=dan;
        rojo=true;
        relojrojo.ReiniciarSegundos();
    }
    
    void Enemigo::ModificarSprite(){
        
    }
    
}
