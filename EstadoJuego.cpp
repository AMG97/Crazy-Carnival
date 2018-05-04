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
        
        //TO DO If jugador = 1, espadachina; if jugador = 2, tipo duro ... jugador 4
        _jugador = new Player("Espadachina");
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
        short int evento = _input->GetTipoEvento();
        // Pulsar tecla
        if (evento == _input->Evento().KeyPressed)
        {
            if (_input->P() ||
                _input->Escape())
            {
                Pausar();
            }
            
            if (_input->Der())
            {
                _jugador->SetEstado(_jugador->GetCorrerDer());
                _jugador->CambiarDireccion();
                _jugador->SetVelocidad(4.0f);
                _jugador->Mover();
            }

            if (_input->Izq())
            {
                _jugador->SetEstado(_jugador->GetCorrerIzq());
                _jugador->CambiarDireccion();
                _jugador->SetVelocidad(-4.0f);
                _jugador->Mover();
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
                
                cout << "Daño\n"<<endl;
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
        
        // Soltar tecla
        if (evento == _input->Evento().KeyReleased)
        {
            _jugador->SetVelocidad(0.0);
            _jugador->SetEstado(_jugador->GetReposo());
        }
        
        // Pulsar raton
        if (evento == _input->Evento().MouseButtonPressed)
        {
            if (_input->RatonIzq())
            {
                cout << "Raton izquierda: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->RatonDer())
            {
                cout << "Raton derecha: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
        }
        
        // Soltar raton
        if (evento == _input->Evento().MouseButtonReleased)
        {
            
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        
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
}