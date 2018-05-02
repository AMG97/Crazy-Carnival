#include "EstadoJuego.hpp"
#include "Hud.hpp"
namespace Crazy
{
    EstadoJuego::EstadoJuego()
    {
        _juego = Juego::Instance();
        _level = new Nivel();
        _level->cargarNivel(1);
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
        
    }
    
    void EstadoJuego::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada)
        {
            if (_input->GetTeclas().RatonIzq)
            {
                cout << "Raton izquierda: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->GetTeclas().RatonDer)
            {
                cout << "Raton derecha: " << _input->GetPosicionRatonX() << ", "<< _input->GetPosicionRatonY()<< endl;
            }
            
            if (_input->GetTeclas().Pausar ||
                _input->GetTeclas().Escape)
            {
                Pausar();
            }
            
            teclaPulsada = false;
        }
    }
    
    void EstadoJuego::Actualizar(float tiempoActual)
    {
        
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
        
        _hud->Dibujar();
        
        
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