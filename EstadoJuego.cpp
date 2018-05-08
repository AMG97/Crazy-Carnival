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
    }
    
    void EstadoJuego::Init()
    {
        _input = new Input();
        _jugador = new Player();
        _hud = new Hud();
        teclaPulsada = false;
        
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
        cout<<"Pero Entras?"<<endl;
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada)
        {
            if (_input->GetTeclas().Pausar ||
                _input->GetTeclas().Escape)
            {
                Pausar();
            }
            
            if (_input->GetTeclas().RatonIzq)
            {
                cout << "Raton izquierda: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->GetTeclas().RatonDer)
            {
                cout << "Raton derecha: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->GetTeclas().D)
            {
                _jugador->Curar(6);
                _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
                
                cout << "Curar\n"<<endl;
                cout <<_jugador->GetVida()<<", "<<_jugador->GetTotalVida()<<endl;
            }
            
            if (_input->GetTeclas().C)
            {
                _jugador->RecibirDanyo(3);
                if(_jugador->AtaqueEspecialActivado())
                {
                    _jugador->SetAtaqueEspecial(true);
                }
                
                _hud->ModificarVida(_jugador->GetVida(),_jugador->GetTotalVida());
                _hud->ModificarEnfriamiento(_jugador->GetEnfriamiento(),_jugador->GetTotalEnfriamiento());
                
                cout << "Daño\n"<<endl;
                cout <<_jugador->GetEnfriamiento()<<", "<<_jugador->GetEnfriamiento()<<endl;
            }
            
            if (_input->GetTeclas().F)
            {
                _jugador->SetAtaqueEspecial(false);
                _hud->Parpadear(false);
                _jugador->SetEnfriamiento(0.0f);
                _hud->EnfriamientoVacio();
            }
            
            if (_input->GetTeclas().R)
            {
                _hud->ModoContrarreloj();
            }
            
            if (_input->GetTeclas().E)
            {
                _hud->ElixirEncontrado();
            }
            
            if (_input->GetTeclas().Abajo)
            {
                _hud->ElixirEncontrado();
            }
            
            if (_input->GetTeclas().Izq)
            {
                if(_jugador->GetEstadoPersonaje() != 3 || _jugador->GetEstadoPersonaje() != 4)
                {
                    //*tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                    _jugador->SetEstadoPersonaje(2);
                    _jugador->SetVelocidad(-2.0);
                    //this->Actualizar(relojDesplazamiento.GetSegundos());
                }
                else
                {
                    _jugador->SetVelocidad(-2.0);
                }
                //teclaPulsada = false;
            }
            teclaPulsada = false;
            if (_input->GetTeclas().Der)
            {
                if(_jugador->GetEstadoPersonaje() != 3 || _jugador->GetEstadoPersonaje() != 4)
                {
                    //*tiempoDesplazamiento = relojDesplazamiento->getElapsedTime();
                    _jugador->SetEstadoPersonaje(1);
                    _jugador->SetVelocidad(2.0);
                    //this->Actualizar(relojDesplazamiento.GetSegundos());
                }
                else
                {
                    _jugador->SetVelocidad(2.0);
                }
                //teclaPulsada = false;
            }
            teclaPulsada = false;
            if (_input->GetTeclas().Arriba)
            {
                contador = 0;  
                if(_jugador->GetEstadoPersonaje() != 3 && _jugador->GetEstadoPersonaje() != 4)
                {
                    if(_jugador->GetEstadoPersonaje() == 1 || _jugador->GetSpriteM().GeEscalarX() > 0.0)
                    {
                        _jugador->SetEstadoPersonaje(3);
                    }
                    else if(_jugador->GetEstadoPersonaje() == 2 || _jugador->GetSpriteM().GeEscalarX() < 0.0)
                    {
                        _jugador->SetEstadoPersonaje(4);
                    }
                }
            }
            cout<<"esto está bien"<<endl;
            teclaPulsada = false;
        }
        else
        {
            cout<<"esto está mal"<<endl;
            if(contador == 0 && (_jugador->GetEstadoPersonaje() == 4 || _jugador->GetEstadoPersonaje() == 3))
            {
                _jugador->SetVelocidadSalto(-36.0 + contador);
                this->Actualizar(relojDesplazamiento.GetSegundos());
                //this->Dibujar(relojDesplazamiento.GetSegundos());
                _jugador->ModificarSprite();
            }
            
            /*else if(contador == 0 && (_input->GetTeclas().Izq || _input->GetTeclas().Der))
            {
                _jugador->SetEstadoPersonaje(0);
                _jugador->SetVelocidad(0.0);
            }*/
            
            while(_jugador->GetSpriteM().GetY() < 360){
                if(_jugador->GetVelocidad() != 0.0 && _jugador->GetEstadoPersonaje() == 0)
                {
                    _jugador->SetVelocidad(0.0);
                }                     
                if(_jugador->GetEstadoPersonaje() == 3 || _jugador->GetEstadoPersonaje() == 4)
                {
                    _jugador->SetVelocidadSalto(-36.0 + contador);
                    if(contador - 36 == 10.0)
                    {
                        _jugador->ModificarSprite();
                    }
                    else if(contador - 36 == -10.0)
                    {
                        _jugador->ModificarSprite();
                    }
                    contador += 2;
                }
                /*else
                {
                    _jugador->SetVelocidad(0.0);
                }*/
                this->Actualizar(relojDesplazamiento.GetSegundos());
                this->Dibujar(relojDesplazamiento.GetSegundos());
                if(_jugador->GetCuerpo()->GetPosition().y >= 360 && (!_input->GetTeclas().Izq && !_input->GetTeclas().Der))
                {
                    _jugador->SetEstadoPersonaje(0);
                }
                else if(_jugador->GetCuerpo()->GetPosition().y >= 360 && _input->GetTeclas().Der)
                {
                    _jugador->SetEstadoPersonaje(1);
                }
                else if(_jugador->GetCuerpo()->GetPosition().y >= 360 && _input->GetTeclas().Izq)
                {
                    _jugador->SetEstadoPersonaje(2);
                }
            }
            //SE CAMBIARÁ CUANDO HAYAN PLATAFORMAS
            if((int) _jugador->GetSpriteM().GetY() <= 370 || (int) _jugador->GetSpriteM().GetY() >= 350)
            {
                cout<<_jugador->GetEstadoPersonaje()<<endl;
                if(reloj.GetSegundos() >= 0.1 && _jugador->GetEstadoPersonaje() == 0)
                {
                    _jugador->ModificarSprite();
                    reloj.restart();
                }
               
                if(_jugador->GetEstadoPersonaje() == 0)
                {
                    cout<<"entra"<<endl;
                    _jugador->SetVelocidad(0.0);
                }
                _jugador->GetCuerpo()->SetAngularVelocity((abs(_jugador->GetSpriteM().GetY() - 360)) * (-1));
                this->Actualizar(relojDesplazamiento.GetSegundos());
                this->Dibujar(relojDesplazamiento.GetSegundos());
                inercia = false;
            }
            
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        cout<<"falla"<<endl;
        if(tiempoActual >= 1/15)
        {
            _jugador->SetCuerpoDefinicionPosicion(_jugador->GetCuerpo()->GetPosition().x, _jugador->GetCuerpo()->GetPosition().y);
            _jugador->SetCuerpo();
            _jugador->Mover(_jugador->GetCuerpo()->GetPosition().x, _jugador->GetCuerpo()->GetPosition().y);
            relojDesplazamiento.ReiniciarSegundos();
        }
    }
    
    void EstadoJuego::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        
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
        _jugador->Dibujar();
        if(_jugador->GetEstadoPersonaje() == 1 || _jugador->GetEstadoPersonaje() == 2 &&  relojDesplazamiento.GetSegundos() >= 0.1)
        {
            _jugador->ModificarSprite();
        }
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
}