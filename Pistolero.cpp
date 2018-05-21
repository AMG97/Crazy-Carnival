#include "Espadachina.hpp"
#include "Motor.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Pistolero::Pistolero(int arma)
    {
        totalVida = 60.0f;
        vida = totalVida;
        totalEnfriamiento = 35.0f;        
        sprite.CambiarTextura(_juego->recursos.GetTextura("Mambo"));
        sprite.CambiarTextRect(0,0,35,40);
        sprite.CambiarOrigen(sprite.GetAncho()/2, sprite.GetAlto()/2);
        
        posIniX = 200;
        posIniY =  EstadoJuego::Instance()->_level->getAltura()*48-48*3-28-sprite.GetAlto();
        
        sprite.CambiarPosicion(posIniX, posIniY);
        _arma=new Arma(arma,sprite.GetX(),sprite.GetY());
        sprite.EscalarProporcion(2.5, 2.5);
    }
    
    void Pistolero::ModificarSprite()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(estado)
            {
                case CORRER:
                    sprite.CambiarTextRect(contadorSpriteCorrer*35, 40, 35, 40);
                    if(contadorSpriteCorrer==0)
                        sprite.CambiarOrigen(35/2,40/2);
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
                    sprite.CambiarTextRect(contadorSpriteCorrer*35, 40, 35, 40);
                    if(contadorSpriteCorrer==0)
                        sprite.CambiarOrigen(35/2,40/2);
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
                    sprite.CambiarTextRect(contadorSpriteSalto*35, 120, 35, 45);
                    if(contadorSpriteSalto==0)
                        sprite.CambiarOrigen(35/2,45/2);
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
                    sprite.CambiarTextRect(70, 120,35,40);
                    sprite.CambiarOrigen(35/2,40/2);
                    _arma->ModificarSprite(SALTO,2,sprite.GetX(),sprite.GetY(),angulo);
                break;

                case REPOSO:
                    sprite.CambiarTextRect(contadorSpriteReposo*35, 0, 35, 40);
                    if(contadorSpriteReposo==0)
                        sprite.CambiarOrigen(35/2,40/2);
                    _arma->ModificarSprite(estado,contadorSpriteReposo,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteReposo++;
                    if(contadorSpriteReposo == 3)
                    {
                        contadorSpriteReposo = 0;
                    }
                break;
                
                case ATAQUE1:
                        if(contadorSpriteAtaque1==0)
                        {
                            sprite.CambiarOrigen(50/2,40/2);
                            golpear=true;
                        }
                        sprite.CambiarTextRect(contadorSpriteAtaque1*50, 80, 50, 40);
                        //sprite.CambiarOrigen(100/2,80/2);
                        _arma->ModificarSprite(estado,contadorSpriteAtaque1,sprite.GetX(),sprite.GetY(),angulo);
                        contadorSpriteAtaque1++;
                        if(contadorSpriteAtaque1==3 && tAtaque1.GetSegundos()>1)
                        {
                            _arma->Disparar(angulo);
                            cout<<tAtaque1.GetSegundos()<<endl;
                            tAtaque1.ReiniciarSegundos();
                        }                        
                        if(contadorSpriteAtaque1==5)
                        {
                            Reposo(1);
                        }
                break;
                
                case ATAQUE2:
                    if(contadorSpriteAtaque2==0)
                    {
                        sprite.CambiarOrigen(50/2, 40/2);
                        //sprite.Mover(0,-15);
                        if(AtaqueEspecialActivado())
                        {
                            ataqueEspecial=false;
                            enfriamiento=0.0f;
                            tAtaque2.ReiniciarSegundos();
                        }
                    }
                    sprite.CambiarTextRect(contadorSpriteAtaque2*50,80,50,40);
                    _arma->ModificarSprite(estado,contadorSpriteAtaque2,sprite.GetX(),sprite.GetY(),angulo);
                    contadorSpriteAtaque2++;
                    if(contadorSpriteAtaque2==3)
                    {
                        _arma->Disparar(angulo);
                        _arma->Disparar(angulo+5);
                        _arma->Disparar(angulo-5);
                    }
                    if(contadorSpriteAtaque2==5)
                    {
                        Reposo(1);
                    }
                    
                break;
                    
            }
            relojAnim.ReiniciarSegundos();
        }
    }
    
    void Pistolero::Reposo(int n){
        sprite.CambiarTextRect(0,0,35,40);
        sprite.CambiarOrigen(35/2,40/2);
        estado=REPOSO;
        if(n==1)
        {
            contadorSpriteAtaque1 = 0;
            contadorSpriteAtaque2= 0;
        }
        _arma->ModificarSprite(estado,0,sprite.GetX(),sprite.GetY(),0);
    }
    
    
    void Pistolero::Update(vector<Enemigo*> e)
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
        /*if(contadorSpriteAtaque1==3 && golpear){
            for(int j=0;j<e.size();j++){
                if(sprite.Interseccion(e[j]->GetSprite()))
                {
                    e[j]->RecibirDanyo(_arma->GetDanyo());
                    ModificarEnfriamiento(5);
                    golpear=false;
                }
            }
        }*/
        
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
    
    
    void Pistolero::MoverY(){
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
                sprite.CambiarPosicion(sprite.GetX(),floor(sprite.GetY()/48)*48+28);
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
    float Pistolero::GetTAtaque1() {
            return tAtaque1.GetSegundos();
    }



}

