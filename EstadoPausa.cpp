#include "EstadoPausa.hpp"

namespace Crazy
{
    EstadoPausa::EstadoPausa()
    {
        _juego = Juego::Instance();
    }
    
    EstadoPausa* EstadoPausa::_pinstance=0;
    
    EstadoPausa* EstadoPausa::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoPausa();
        }
        return _pinstance;
    }
    
    EstadoPausa::~EstadoPausa()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoPausa::Init()
    {
        _input = new Input();
        opcion = MENU;
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Pausa");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->ancho/2), 150);
        
        t_menu.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_menu.CambiarTexto("Menu");
        t_menu.CambiarTamanyo(50);
        t_menu.CentrarOrigen();
        t_menu.CambiarPosicion((_juego->ancho/2), t_titulo.GetY()+200);
        
        t_salir.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_salir.CambiarTexto("Salir");
        t_salir.CambiarTamanyo(50);
        t_salir.CentrarOrigen();
        t_salir.CambiarPosicion((_juego->ancho/2), t_menu.GetY()+75);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->alto-100));
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.CambiarColorRojo();
        flecha.CambiarPosicion(60, t_atras.GetY()-30);
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoPausa::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada) {
            if (_input->GetTeclas().BackSpace
                || _input->GetTeclas().Escape)
            {
                Atras();
            }
            
            if (_input->GetTeclas().Arriba) {
                opcion--;
                if (opcion < MENU)
                {
                    opcion = SALIR;
                }
            }

            if (_input->GetTeclas().Abajo) {
                opcion++;
                if (opcion > SALIR)
                {
                    opcion = MENU;
                }
            }
            
            if (_input->GetTeclas().Enter) {
                CambiarEstado();
            }
            teclaPulsada = false;
        }
    }
    
    void EstadoPausa::Actualizar(float tiempoActual)
    {
        switch (opcion)
        {
            case MENU:
                CambiarFlecha(t_menu);
                break;
            case SALIR:
                CambiarFlecha(t_salir);
                break;
        }
    }
    
    void EstadoPausa::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->Dibujar(t_titulo);
        _juego->_ventana->Dibujar(t_menu);
        _juego->_ventana->Dibujar(t_salir);
        _juego->_ventana->Dibujar(t_atras);
        _juego->_ventana->Dibujar(flecha);
        _juego->_ventana->Dibujar(flechaAtras);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoPausa::Atras()
    {
        _juego->maquina.Eliminar();
    }
    
    void EstadoPausa::CambiarFlecha(Texto texto)
    {
        flecha.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoPausa::CambiarEstado()
    {
        switch (opcion)
        {
            case MENU:
                _juego->maquina.Eliminar();
                _juego->maquina.Anyadir(new EstadoMenu());
                
                break;
            case SALIR:
                _input->CerrarVentana();
                break;
        }
    }
}