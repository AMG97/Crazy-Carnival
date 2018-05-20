#include "Espadachina.hpp"
#include "Motor.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Espadachina::Espadachina(int arma)
    {
        totalVida = 60.0f;
        vida = totalVida;
        totalEnfriamiento = 30.0f;        
        sprite.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        sprite.CambiarTextRect(0*60, 0*80, 60, 80);
        sprite.CambiarOrigen(sprite.GetAncho()/2, sprite.GetAlto()/2);
        
        posIniX = 200;
        posIniY =  EstadoJuego::Instance()->_level->getAltura()*48-48*3-2-sprite.GetAlto();
        
        sprite.CambiarPosicion(posIniX, posIniY);
        _arma=new Arma(arma,sprite.GetX(),sprite.GetY());
        sprite.EscalarProporcion(1.5, 1.5);
    }
    
    void Espadachina::ModificarSprite()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(estado)
            {
                case CORRER:
                    sprite.CambiarTextRect(contadorSpriteCorrer*65, 1*80, 65, 80);
                    sprite.CambiarOrigen(65/2,80/2);
                    _arma->ModificarSprite(estado,contadorSpriteCorrer,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteCorrer++;
                    if(contadorSpriteCorrer == 6)
                    {
                        contadorSpriteCorrer = 0;
                    }
                    if(velocidad==0)
                    {
                        contadorSpriteCorrer=0;
                        Reposo(3);
                    }
                break;
                
                case CORRERATRAS:
                    sprite.CambiarTextRect(contadorSpriteCorrer*65, 1*80, 60, 80);
                    sprite.CambiarOrigen(60/2,80/2);
                    _arma->ModificarSprite(estado,contadorSpriteCorrer,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteCorrer--;
                    if(contadorSpriteCorrer == -1)
                    {
                        contadorSpriteCorrer = 5;
                    }
                    if(velocidad==0)
                    {
                        contadorSpriteCorrer=0;
                        Reposo(3);
                    }
                break;

                case SALTO:
                    sprite.CambiarTextRect(contadorSpriteSalto*65, 560, 65, 90);
                    sprite.CambiarOrigen(60/2,90/2);
                    _arma->ModificarSprite(estado,contadorSpriteSalto,sprite.GetX(),sprite.GetY(),angulo);
                    if((contadorSpriteSalto==0 && velSalto>-9 ) || (contadorSpriteSalto==1 && EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+48*2)))
                        contadorSpriteSalto++;
                    if(contadorSpriteSalto>1)
                        contadorSpriteSalto=1;
                    if(EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+60))
                    {
                        contadorSpriteSalto=0;
                        Reposo(3);
                        lastpared=0;
                    }
                        
                break;
                
                case DESLIZARSE:
                    sprite.CambiarTextRect(65, 560,65,90);
                    sprite.CambiarOrigen(60/2,90/2);
                    _arma->ModificarSprite(SALTO,1,sprite.GetX(),sprite.GetY(),angulo);
                break;

                case REPOSO:
                    sprite.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    sprite.CambiarOrigen(60/2,80/2);
                    _arma->ModificarSprite(estado,contadorSpriteReposo,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteReposo++;
                    if(contadorSpriteReposo == 8)
                    {
                        contadorSpriteReposo = 0;
                    }
                break;
                
                case ATAQUE1:
                        if(contadorSpriteAtaque1==0)
                        {
                            sprite.CambiarOrigen(100/2,90/2);
                            //sprite.Mover(0,-22);
                            golpear=true;
                        }
                        sprite.CambiarTextRect(contadorSpriteAtaque1*100, 160, 100, 80);
                        sprite.CambiarOrigen(100/2,80/2);
                        _arma->ModificarSprite(estado,contadorSpriteAtaque1,sprite.GetX(),sprite.GetY(),angulo);
                        contadorSpriteAtaque1++;                        
                        if(contadorSpriteAtaque1==6)
                        {
                            Reposo(1);
                        }
                break;
                
                case ATAQUE2:
                    if(contadorSpriteAtaque2==0)
                    {
                        sprite.CambiarOrigen(100/2, 80/2);
                        //sprite.Mover(0,-15);
                        if(AtaqueEspecialActivado())
                        {
                            ataqueEspecial=false;
                            enfriamiento=0.0f;
                            tAtaque2.ReiniciarSegundos();
                        }
                    }
                    sprite.CambiarTextRect(contadorSpriteAtaque2*100,360,100,80);
                    _arma->ModificarSprite(estado,contadorSpriteAtaque2,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteAtaque2++;
                    if(contadorSpriteAtaque2==3)
                    {
                        _arma->Disparar(angulo);
                    }
                    if(contadorSpriteAtaque2==9)
                    {
                        Reposo(2);
                    }
                    
                break;
                    
            }
            relojAnim.ReiniciarSegundos();
        }
    }
    
    void Espadachina::Reposo(int n){
        sprite.CambiarTextRect(0,0,60,80);
        sprite.CambiarOrigen(60/2,80/2);
        estado=REPOSO;
        if(n==1)
        {
            contadorSpriteAtaque1 = 0;
        }
        else if(n==2)
        {
            contadorSpriteAtaque2=0;
        }
        _arma->ModificarSprite(estado,0,sprite.GetX(),sprite.GetY(),0);
    }
    
    
    void Espadachina::Update(vector<Enemigo*> e)
    {
        MoverY();
        if(velocidad!=0){
            if(velocidad>0.1){
                if(lastpared!=0){
                    velocidad-=0.25f;
                }
                else
                    velocidad=velocidad-2.f;
            }
            else if(velocidad<0.1){
                if(lastpared!=0){
                    velocidad+=0.25f;
                }else
                velocidad=velocidad+2.f;
            }
        }
        if(abs(velocidad)<=0.5)
            velocidad=0;
        MoverX(velocidad);
        if(contadorSpriteAtaque1==3 && golpear){
            for(int j=0;j<e.size();j++){
                if(sprite.Interseccion(e[j]->GetSprite()))
                {
                    e[j]->RecibirDanyo(_arma->GetDanyo());
                    ModificarEnfriamiento(5);
                    golpear=false;
                }
            }
        }
        
        if(rojo && relojrojo.GetSegundos()<=0.2)
            sprite.CambiarColorRojo();
        else if(rojo && relojrojo.GetSegundos()>0.2){
            rojo=false;
            sprite.Parpadear(false);
        }
        EstadoJuego* ej=EstadoJuego::Instance();
        if(estado==SALTO && velSalto==0 && (ej->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) || ej->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()))){
            if((ej->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && lastpared!=1) ||
                (ej->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()) && lastpared!=2)){
                    if(lastpared==0){
                        if(ej->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()))
                            lastpared=1;
                        else
                            lastpared=2;
                    }else if(lastpared==1)
                        lastpared=2;
                    else
                        lastpared=1;
                    estado=DESLIZARSE;
                    if((ej->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && direccionIzq==false) || (ej->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()) && direccionIzq==true))
                        CambiarDireccion();
            }
        }
        if((estado==DESLIZARSE) && (velSalto==0 && ej->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+60)
           ||(!ej->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && !ej->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY())))){
            if(velSalto==0 && ej->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+60)){
                estado=REPOSO;
                lastpared=0;
                contadorSpriteSalto=0;
            }
            else
                estado=SALTO;
        }
        
    }


}