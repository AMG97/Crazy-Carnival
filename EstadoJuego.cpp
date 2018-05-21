#include "EstadoJuego.hpp"
#include "Hud.hpp"
namespace Crazy
{
    EstadoJuego::EstadoJuego()
    {
        _juego = Juego::Instance();
    }
    
    EstadoJuego* EstadoJuego::_pinstance=0;
    
    EstadoJuego* EstadoJuego::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoJuego();
        }
        return _pinstance;
    }
    
    void EstadoJuego::Vaciar()
    {
        _pinstance=0;
    }
    
    EstadoJuego::~EstadoJuego()
    {
        delete _input;
        _input = NULL;
        delete _hud;
        _hud = NULL;
        delete _jugador;
        _jugador = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoJuego::Personaje(string jugador, bool modoNormal, bool modoContrarreloj)
    {
        texturaJugador = jugador;
        normal = modoNormal;
        contrarreloj = modoContrarreloj;
        
        // TODO: manejar esto:
        // modoNormal y modoContrareloj
    }
    
    void EstadoJuego::Init()
    {
        _mundo = new b2World(b2Vec2(0.0, 9.8));
        
        _input = new Input();
        _level = new Nivel();
        lvl_n=1;
        _level->cargarNivel(lvl_n);
        if(texturaJugador=="Espadachina")
            _jugador = new Espadachina(1);
        else
            _jugador=new Pistolero(5);//Las armas del pistolero son: 5 la primera y las recompesas 6,7 y 8
        _hud = new Hud(contrarreloj);
        
        teclaPulsada = false;
        
        //_level->setPosCamara(_jugador->GetPosX(), _jugador->GetPosY());
        
        /*reloj = new sf::Clock();
        relojAtaqueEspecial = new sf::Clock();
        relojDesplazamiento = new sf::Clock();
        tiempo = new sf::Time();
        tiempoAtaqueEspecial = new sf::Time();
        tiempoDesplazamiento = new sf::Time();*/
        inercia = false;
        contador = 0;
    }
    
    void EstadoJuego::ManejarEventos()
    {
        short int evento = _input->GetTipoEvento();
        short int estado=_jugador->GetEstado();
        // Pulsar tecla
        if (evento == _input->Evento().KeyPressed)
        {
            if (_input->P() ||
                _input->Escape())
            {
                Pausar();
            }
            
            // Pruebas
            if (_input->D())
            {
                _jugador->Curar(6);
                _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
                
                cout << "Curar\n"<<endl;
                cout <<_jugador->GetVida()<<", "<<_jugador->GetTotalVida()<<endl;
            }
            
            if (_input->C())
            {
                _jugador->RecibirDanyo(3);
                if(_jugador->AtaqueEspecialActivado())
                {
                    _jugador->SetAtaqueEspecial(true);
                }
                
                _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
                _hud->ModificarEnfriamiento(_jugador->GetEnfriamiento(),_jugador->GetTotalEnfriamiento());
                cout <<_jugador->GetEnfriamiento()<<", "<<_jugador->GetEnfriamiento()<<endl;
            }
            
            if (_input->F())
            {
                _jugador->SetAtaqueEspecial(false);
                _hud->Parpadear(false);
                _jugador->SetEnfriamiento(0.0f);
                _hud->EnfriamientoVacio();
            }
            
            if (_input->R())
            {
                _hud->ModoContrarreloj();
            }
            
            if (_input->E())
            {
                if(_hud->getElixir())
                {
                    _hud->ElixirEncontrado(false);
                }
                else
                {
                    _hud->ElixirEncontrado(true);
                }    
            }
            
            if (_input->Q())
            {
                _juego->_ventana->Cerrar();
            }
            
            if (_input->F9()) _level->toggleFreeCamera();
        }
        if(!_level->isCamFree()){
            if (_input->Der())
            {
               if(_jugador->GetPosX()<_level->getCamara()->getX()+_level->getCamara()->getWidth()/2-50){
                    _jugador->SetVelocidad(6.0f);
                    if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2() && estado!=_jugador->GetSaltar() && estado!=_jugador->GetDeslizarse())
                    {
                        if(_input->GetPosicionRatonX()<_jugador->GetPosX())
                            _jugador->SetEstado(_jugador->GetCorrerAtras());
                        else
                            _jugador->SetEstado(_jugador->GetCorrer());
                    }
               }
            }

            if (_input->Izq())
            {
                if(_jugador->GetPosX()>_level->getCamara()->getX()-_level->getCamara()->getWidth()/2+50){
                    _jugador->SetVelocidad(-6.0f);
                    if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2()&& estado!=_jugador->GetSaltar()&& estado!=_jugador->GetDeslizarse())
                    {
                        if(_input->GetPosicionRatonX()>_jugador->GetPosX())
                            _jugador->SetEstado(_jugador->GetCorrerAtras());
                    else
                        _jugador->SetEstado(_jugador->GetCorrer());
                    }
                }
            }

            if(_input->Arriba())
            {
                if(estado==_jugador->GetDeslizarse() && _jugador->Gettpared()>0.1){
                    if(_jugador->GetLastPared()==1){
                        _jugador->SetVelocidad(-6.0f);
                    }else
                        _jugador->SetVelocidad(6.0f);
                    _jugador->SetVelocidadSalto(-8);
                    _jugador->tparedRestart();
                }
                else if(estado!=_jugador->GetSaltar() && _jugador->GetVelocidadSalto()==0 && estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2())
                {
                    _jugador->SetEstado(_jugador->GetSaltar());
                    _jugador->SetVelocidadSalto(-14.0f);
                    _jugador->tparedRestart();
                }
            }

            if(_input->GetPosicionRatonX()>=_level->getCamara()->getX()-_level->getCamara()->getWidth()/2 && _input->GetPosicionRatonX()<=_level->getCamara()->getX()+_level->getCamara()->getWidth()/2 && _input->GetPosicionRatonY()>=_level->getCamara()->getY()-_level->getCamara()->getHeight()/2 && _input->GetPosicionRatonY()<=_level->getCamara()->getY()+_level->getCamara()->getHeight()/2){
                if (_input->RatonIzq())
                {
                    if(texturaJugador=="Espadachina"){
                        if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2() && estado!=_jugador->GetDeslizarse())
                        {
                            _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                            _jugador->SetEstado(_jugador->GetAtaque1());
                        }
                    }else{
                        if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2() && estado!=_jugador->GetDeslizarse() && _jugador->GetTAtaque1()>1)
                        {
                            _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                            _jugador->SetEstado(_jugador->GetAtaque1());
                        }
                    }

                }

                if (_input->RatonDer())
                {
                    if(texturaJugador=="Espadachina"){
                        if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2() && (_jugador->AtaqueEspecialActivado() || _jugador->GetTAtque2()<4))
                        {
                            _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                            _jugador->SetEstado(_jugador->GetAtaque2());
                            if(_jugador->AtaqueEspecialActivado()){
                                _hud->Parpadear(false);
                                _hud->EnfriamientoVacio();
                            }

                        }
                    }else if(estado!=_jugador->GetAtaque1() && estado!=_jugador->GetAtaque2() && (_jugador->AtaqueEspecialActivado() || _jugador->GetTAtque2()<2.5)){
                       _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                            _jugador->SetEstado(_jugador->GetAtaque2());
                            if(_jugador->AtaqueEspecialActivado()){
                                _hud->Parpadear(false);
                                _hud->EnfriamientoVacio();
                            } 
                    }
                }
            }
        }else{
            if(_input->Der())_level->getCamara()->mover(20,0);
            if(_input->Izq())_level->getCamara()->mover(-20,0);
            if(_input->Arriba())_level->getCamara()->mover(0,-20);
            if(_input->Abajo())_level->getCamara()->mover(0,20);
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        
        if(_jugador->GetVida()<=0 || _hud->getContador() >= 180){
            if(_jugador->getElixir() && _hud->getContrarreloj() && _hud->getContador() >= 150)
            {
                _jugador->SetVida(_jugador->GetTotalVida());
                _jugador->SetEnfriamiento(0.0);
                _hud->aumentarTiempo(60);
                _hud->ElixirEncontrado(false);
            }
            else if(_jugador->getElixir() && _hud->getContrarreloj() && _hud->getContador() >= 120)
            {
                _jugador->SetVida(_jugador->GetTotalVida());
                _jugador->SetEnfriamiento(0.0);
                _hud->aumentarTiempo(30);
                _hud->ElixirEncontrado(false);
            }
            else if(_jugador->getElixir())
            {
                _jugador->SetVida(_jugador->GetTotalVida());
                _jugador->SetEnfriamiento(0.0);
                _hud->ElixirEncontrado(false);
            }
            else{
                _juego->maquina.Anyadir(EstadoMuerte::Instance(), true);
            }
        }
                
        if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2() && _jugador->GetEstado()!=_jugador->GetDeslizarse())
        {
            
            if(_input->GetPosicionRatonX()<_jugador->GetSprite().GetX() && !_jugador->getDireccion())
            {
                _jugador->CambiarDireccion();
            }
            else if(_input->GetPosicionRatonX()>_jugador->GetSprite().GetX() && _jugador->getDireccion()){
                _jugador->CambiarDireccion();
            }
                
        }
        
        _level->setPosCamara(_jugador->GetPosX(), _jugador->GetPosY());
        
        _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
        _hud->ModificarEnfriamiento(_jugador->GetEnfriamiento(),_jugador->GetTotalEnfriamiento());
        if(_jugador->AtaqueEspecialActivado())
        {
            _hud->SetAtaqueEspecial(true);
        }else
            _hud->SetAtaqueEspecial(false);
        if(contrarreloj && relojContrarreloj.GetSegundos()>=1)
        {
            _hud->CambiarTexturaContador();
            relojContrarreloj.ReiniciarSegundos();
        }
        
        
    }
    
    void EstadoJuego::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        _level->update();
        _level->draw("Fondo");
        _level->draw("Trasera");
        _level->draw("Collisionable");
        _level->draw("Objetos");
        
        if(relojAtaqueEspecial.GetSegundos() >= 0.1 && _jugador->GetAtaqueEspecial() && _hud->GetAtaqueEspecial())
        {
            _hud->Parpadear(true);
            relojAtaqueEspecial.ReiniciarSegundos();
        }
        
        _hud->Dibujar();
        
        
        _jugador->ModificarSprite();
        _jugador->Dibujar();
        _level->draw("Delante");
                
        _juego->_ventana->Mostrar();
    }
    
    void EstadoJuego::Pausar()
    {
        cout << "Juego pausado"<<endl;
        _juego->maquina.Anyadir(EstadoPausa::Instance(), false);
    }
    
    void EstadoJuego::Reanudar()
    {
        cout << "Juego reanudado"<<endl;
    }

    b2World* EstadoJuego::GetMundo() {
        return _mundo;
    }

    void EstadoJuego::SetMundo(b2World* world) {
        _mundo = world;
    }
        Nivel* EstadoJuego::GetNivel() {
            return _level;
    }

    unsigned short int EstadoJuego::getNumNivel() {
        return lvl_n; 
    }

}