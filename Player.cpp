#include "Player.hpp"
#include "Motor.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Player::Player(string textura)
    {
        totalVida = 60.0f;
        vida = totalVida;
        enfriamiento = 0.0f;
        totalEnfriamiento = 30.0f;
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
        
        
        sprite.CambiarTextura(_juego->recursos.GetTextura(textura));
        sprite.CambiarTextRect(0*60, 0*80, 60, 80);
        sprite.CambiarOrigen(sprite.GetAncho()/2, sprite.GetAlto()/2);
        
        posIniX = 240;
        posIniY =  EstadoJuego::Instance()->_level->getAltura()*48-48*3-2-sprite.GetAlto();
        
        sprite.CambiarPosicion(posIniX, posIniY);
        _arma=new Arma(2,sprite.GetX(),sprite.GetY());
        sprite.EscalarProporcion(1.5, 1.5);
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
    
    void Player::ModificarSprite()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(estado)
            {
                case CORRER:
                    sprite.CambiarTextRect(contadorSpriteCorrer*65, 1*80, 60, 80);
                    sprite.CambiarOrigen(60/2,80/2);
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
                    if((contadorSpriteSalto==0 && velSalto>-9 ) || (contadorSpriteSalto==1 && EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+48*2)) || (contadorSpriteSalto==2 && velSalto>11))
                        contadorSpriteSalto++;
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
    
    void Player::Reposo(int n){
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
    
    void Player::Dibujar()
    {
        _juego->_ventana->DibujarSprite(sprite);
        _arma->Dibujar();
    }
    
    void Player::Update(vector<Enemigo*> e)
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
                if(sprite.Interseccion2(e[j]->GetSprite()))
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
        if(estado==SALTO && (EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) || EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()))){
            if((EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && lastpared!=1) ||
                (EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()) && lastpared!=2)){
                    if(lastpared==0){
                        if(EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()))
                            lastpared=1;
                        else
                            lastpared=2;
                    }else if(lastpared==1)
                        lastpared=2;
                    else
                        lastpared=1;
                    estado=DESLIZARSE;
                    if((EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && direccionIzq==false) || (EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY()) && direccionIzq==true))
                        CambiarDireccion();
            }
        }
        if((estado==DESLIZARSE) && (velSalto==0 && EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+60)
           ||(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+48,sprite.GetY()) && !EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()-48,sprite.GetY())))){
            if(velSalto==0 && EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+60)){
                estado=REPOSO;
                lastpared=0;
                contadorSpriteSalto=0;
            }
            else
                estado=SALTO;
        }
        
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



}