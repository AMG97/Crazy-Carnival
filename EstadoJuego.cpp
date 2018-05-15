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
        for (int i=0; i < _enemigos.size(); i++)
        {
            Enemigo *tmp= _enemigos[i];
            _enemigos.erase(_enemigos.begin()+i);
            delete tmp;
            _enemigos[i]=NULL;
        }
    }
    
    void EstadoJuego::Init()
    {
        _mundo = new b2World(b2Vec2(0.0, 9.8));
        
        _input = new Input();
        _level = new Nivel();
        _level->cargarNivel(1);
        //TO DO If jugador = 1, espadachina; if jugador = 2, tipo duro ... jugador 4
        _jugador = new Player("Espadachina");
        _hud = new Hud();
        Enemigo* e = new Enemigo(0);
        Enemigo* e2 = new Enemigo(1);
        _enemigos.push_back(e);
        _enemigos.push_back(e2);
        
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
                _hud->ElixirEncontrado();
            }
            
            if (_input->Q())
            {
                _juego->_ventana->Cerrar();
            }
        }
        
        if (_input->Der())
            {
               if(_jugador->GetPosX()<_level->getCamara()->getX()+_level->getCamara()->getWidth()/2-50){
                    _jugador->SetVelocidad(6.0f);
                    if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2() && _jugador->GetEstado()!=_jugador->GetSaltar())
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
                    if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2()&& _jugador->GetEstado()!=_jugador->GetSaltar())
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
                if(_jugador->GetEstado()!=_jugador->GetSaltar() && _jugador->GetVelocidadSalto()==0 && _jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2())
                {
                    _jugador->SetEstado(_jugador->GetSaltar());
                    _jugador->SetVelocidadSalto(-14.0f);
                }
            }
           
        
        
            if (_input->RatonIzq())
            {
                if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2())
                {
                    _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                    _jugador->SetEstado(_jugador->GetAtaque1());
                }
                //cout << "Angulo"<<_jugador->GetAngulo()<<endl;
            }
            
            if (_input->RatonDer())
            {
                if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2() && (_jugador->AtaqueEspecialActivado() || _jugador->GetTAtque2()<4))
                {
                    _jugador->SetAngulo(_input->GetPosicionRatonX(),_input->GetPosicionRatonY());
                    _jugador->SetEstado(_jugador->GetAtaque2());
                    if(_jugador->AtaqueEspecialActivado()){
                        _hud->Parpadear(false);
                        _hud->EnfriamientoVacio();
                    }
                        
                }
            }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        // Si el personaje esta saltando
        
        /*if ((_jugador->GetEstado() == _jugador->GetSaltarDer())
            || (_jugador->GetEstado() == _jugador->GetSaltarIzq()))
        {
            
            // Suelo
            /*if (_jugador->GetYAhora() == _jugador->GetPosY())
            {
                _jugador->SetEstado(_jugador->GetReposo());
            }*/
        //}
        if(_jugador->GetEstado()!=_jugador->GetAtaque1() && _jugador->GetEstado()!=_jugador->GetAtaque2())
        {
            
            if(_input->GetPosicionRatonX()<_jugador->GetSprite().GetX() && !_jugador->getDireccion())
            {
                _jugador->CambiarDireccion();
            }
            else if(_input->GetPosicionRatonX()>_jugador->GetSprite().GetX() && _jugador->getDireccion()){
                _jugador->CambiarDireccion();
            }
                
        }
        _jugador->Update(_enemigos);
        _jugador->GetArma()->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY(),_enemigos,_jugador,_level);
        _level->setPosCamara(_jugador->GetPosX(), _jugador->GetPosY());
        for(int i=0;i<_enemigos.size();i++){
            if(_enemigos[i]->GetVida()<=0){
                Enemigo *tmp=_enemigos[i];
                _enemigos.erase(_enemigos.begin()+i);
                delete tmp;
            }
            else{
            _enemigos[i]->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY());
            _enemigos[i]->GetArma()->Update(_enemigos[i]->GetSprite().GetX(),_enemigos[i]->GetSprite().GetY(),_jugador);
            }
        }
        
        _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
        _hud->ModificarEnfriamiento(_jugador->GetEnfriamiento(),_jugador->GetTotalEnfriamiento());
        if(_jugador->AtaqueEspecialActivado())
        {
            _jugador->SetAtaqueEspecial(true);
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
        _level->draw("Delante");
        
        if(relojAtaqueEspecial.GetSegundos() >= 0.1 && _jugador->GetAtaqueEspecial())
        {
            if(_hud->GetAtaqueEspecial())
            {
                _hud->Parpadear(true);
            }
            else
            {
                _hud->Parpadear(false);
            }
            relojAtaqueEspecial.ReiniciarSegundos();
        }
        
        _hud->Dibujar();
        
        for(int i=0;i<_enemigos.size();i++){
            _enemigos[i]->Dibujar();
            
        }
        
        _jugador->ModificarSprite();
        _jugador->Dibujar();
                
        _juego->_ventana->Mostrar();
    }
    
    void EstadoJuego::Pausar()
    {
        _juego->maquina.Anyadir(new EstadoPausa(), false);
    }
    
    void EstadoJuego::Reanudar()
    {
        cout << "REANUDADO";
    }

    b2World* EstadoJuego::GetMundo() {
        return _mundo;
    }

    void EstadoJuego::SetMundo(b2World* world) {
        _mundo = world;
    }


}