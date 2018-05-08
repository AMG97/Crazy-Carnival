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
        opcion = ABANDONAR;
        teclaPulsada = false;
        abandonar = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Pausa");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 150);
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
        
        t_frase.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_frase.CambiarTamanyo(50);
        t_frase.CambiarPosicion((_juego->GetAncho()/2), t_titulo.GetY()+200);
        Abandonar();
        
        t_frase2.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_frase2.CambiarTamanyo(40);
        t_frase2.CambiarTexto("Perderas los progresos que no se hayan guardado.");
        t_frase2.CentrarOrigen();
    }
    
    void EstadoPausa::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->Enter()) {
                CambiarEstado();
            }
            
            if ((_input->BackSpace()) || (_input->Escape())){
               Atras();
            }
            
            if (abandonar) {
                if (_input->Arriba()) {
                    opcion--;
                    if (opcion < OP1)
                    {
                        opcion = OP2;
                    }
                }

                if (_input->Abajo()) {
                    opcion++;
                    if (opcion > OP2)
                    {
                        opcion = OP1;
                    }
                }
            }
        }
    }
    
    void EstadoPausa::Actualizar(float tiempoActual)
    {
        if (abandonar)
        {
            switch (opcion)
            {
                case OP1:
                    CambiarFlecha(t_op);
                    break;
                case OP2:
                    CambiarFlecha(t_op2);
                    break;
            }
        }
    }
    
    void EstadoPausa::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->Dibujar(t_titulo);
        _juego->_ventana->Dibujar(t_frase);
        _juego->_ventana->Dibujar(flecha);
        
        if (!abandonar)
        {
            _juego->_ventana->Dibujar(t_atras);
            _juego->_ventana->Dibujar(flechaAtras);
        }
        else
        {
            _juego->_ventana->Dibujar(t_op);
            _juego->_ventana->Dibujar(t_op2);
            _juego->_ventana->Dibujar(t_frase2);
        }
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoPausa::Atras()
    {
        if (abandonar)
        {
            abandonar = false;
            opcion = ABANDONAR;
            Abandonar();
        }
        else
        {
            _juego->maquina.Eliminar();
        }
    }
    
    void EstadoPausa::CambiarFlecha(Texto texto)
    {
        flecha.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoPausa::CambiarEstado()
    {
        switch (opcion)
        {
            case ABANDONAR:
                abandonar = true;
                opcion = OP1;
                Confirmar();
                break;
            case OP1:
                _juego->maquina.Eliminar();
                _juego->maquina.Anyadir(EstadoMenu::Instance());
                break;
            case OP2:
                abandonar = false;
                opcion = ABANDONAR;
                Abandonar();
                break;
        }
    }
    
    void EstadoPausa::Abandonar()
    {
        t_frase.CambiarTexto("Abandonar partida");
        t_frase.CentrarOrigen();
        CambiarFlecha(t_frase);
    }
    
    void EstadoPausa::Confirmar()
    {
        t_frase.CambiarTexto("Seguro que quieres salir?");
        t_frase.CentrarOrigen();
        
        t_op.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_op.CambiarTexto("Si");
        t_op.CambiarTamanyo(50);
        t_op.CentrarOrigen();
        t_op.CambiarPosicion((_juego->GetAncho()/2), t_frase.GetY()+75);
        CambiarFlecha(t_op);
        
        t_op2.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_op2.CambiarTexto("No");
        t_op2.CambiarTamanyo(50);
        t_op2.CentrarOrigen();
        t_op2.CambiarPosicion((_juego->GetAncho()/2), t_op.GetY()+75);
        
        t_frase2.CambiarPosicion((_juego->GetAncho()/2), t_op2.GetY()+100);
    }
}