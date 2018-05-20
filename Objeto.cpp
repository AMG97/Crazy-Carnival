
#include "Objeto.hpp"
#include "EstadoJuego.hpp"

Objeto::Objeto(int tileX,int tileY,SpriteM* sp,int puntos) {
    p_value = puntos; valor=0;
    _sprite = sp;
    position.set(tileX, tileY);
       
    
}

Objeto::Objeto(const Objeto& orig) {
}

Objeto::~Objeto() {
}

bool Objeto::colision(){
    _pl_instance = EstadoJuego::Instance()->_jugador;

    if(_pl_instance!=0 && _sprite!=0){        
        if(_sprite->InterseccionContiene(_pl_instance->GetSprite())){
            _pl_instance->addPuntuacion(p_value);
            objectEffect();
            return true;
        }
    }
    return false;
}

SpriteM* Objeto::getSprite() {
    return _sprite;
}

sf::FloatRect Objeto::getBound() {
    return _sprite->getGlobalBounds();
}

void OBJ_Reloj::objectEffect() {    
    if(_pl_instance!=0){
        _pl_instance->SetEnfriamiento(0);
    }
}

void OBJ_HP::objectEffect() {   
    if(_pl_instance!=0){
        valor = _pl_instance->GetTotalVida()/2;
        _pl_instance->Curar(valor);
    }
}

void OBJ_Elixir::objectEffect() {    
    if(_pl_instance!=0){
        _pl_instance->SetElixir(true);
    }
}

void OBJ_Star::objectEffect() {

}

vector2f Objeto::getPosition() {
    return position;
}

OBJ_HP::OBJ_HP(int tileX, int tileY, SpriteM* sp, int puntos) : Objeto(tileX, tileY, sp, puntos) {
}


