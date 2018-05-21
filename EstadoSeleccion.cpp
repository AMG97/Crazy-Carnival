#include "EstadoSeleccion.hpp"

namespace Crazy
{
    EstadoSeleccion::EstadoSeleccion()
    {
        _juego = Juego::Instance();
    }
    
    EstadoSeleccion* EstadoSeleccion::_pinstance=0;
    
    EstadoSeleccion* EstadoSeleccion::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoSeleccion();
        }
        return _pinstance;
    }
    
    void EstadoSeleccion::Vaciar()
    {
        _pinstance=0;
    }
        
    EstadoSeleccion::~EstadoSeleccion()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoSeleccion::Init()
    {
        _input = new Input();
        opcion = P1;
        contadorSpriteReposo = 0;
        
        modoNormal = true;
        modoContrarreloj = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_titulo.CambiarTexto("Elige personaje");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 75);
        
        p1.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        p1.CambiarTextRect(0*60, 0*80, 60, 80);
        p1.CambiarOrigen(p1.GetAncho()/2, p1.GetAlto()/2);
        p1.CambiarPosicion((_juego->GetAncho()/2)-150, t_titulo.GetY()+200);
        p1.EscalarProporcion(1.5, 1.5);
        
        p2.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        p2.CambiarTextRect(0*60, 0*80, 60, 80);
        p2.CambiarOrigen(p2.GetAncho()/2, p2.GetAlto()/2);
        p2.CambiarPosicion(p1.GetX()+300, t_titulo.GetY()+200);
        p2.EscalarProporcion(1.5, 1.5);
        
        t_modo.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_modo.CambiarTexto("Dificultad");
        t_modo.CambiarTamanyo(48);
        t_modo.CentrarOrigen();
        t_modo.CambiarPosicion((_juego->GetAncho()/2), p2.GetY()+100);
        
        t_normal.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_normal.CambiarTexto("Normal");
        t_normal.CambiarTamanyo(48);
        t_normal.CentrarOrigen();
        t_normal.CambiarPosicion((_juego->GetAncho()/3), t_modo.GetY()+60);
        
        t_pesadilla.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_pesadilla.CambiarTexto("Pesadilla");
        t_pesadilla.CambiarTamanyo(48);
        t_pesadilla.CentrarOrigen();
        t_pesadilla.CambiarPosicion((2*_juego->GetAncho()/3), t_modo.GetY()+60);
        
        t_modoC.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_modoC.CambiarTexto("Contrarreloj");
        t_modoC.CambiarTamanyo(48);
        t_modoC.CentrarOrigen();
        t_modoC.CambiarPosicion((_juego->GetAncho()/2), t_pesadilla.GetY()+100);
        
        t_si.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_si.CambiarTexto("Si");
        t_si.CambiarTamanyo(48);
        t_si.CentrarOrigen();
        t_si.CambiarPosicion((_juego->GetAncho()/3), t_modoC.GetY()+60);
        
        t_no.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_no.CambiarTexto("No");
        t_no.CambiarTamanyo(48);
        t_no.CentrarOrigen();
        t_no.CambiarPosicion((2*_juego->GetAncho()/3), t_modoC.GetY()+60);
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.Rotar(90.0f);
        CambiarFlecha(p1);
        flecha.CambiarColorRojo();
        flecha.Escalar(50.0f, 50.0f); // Escalar al 50%
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        t_jugar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_jugar.CambiarTexto("Jugar");
        t_jugar.CambiarTamanyo(50);
        t_jugar.CentrarOrigen();
        t_jugar.CambiarPosicion(924, (_juego->GetAlto()-100));
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
        
        flechaJugar.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaJugar.CambiarOrigen();
        flechaJugar.CambiarPosicion(964, t_atras.GetY()-30);
        flechaJugar.Escalar(70.0f, 70.0f); // Escalar al 70%
        
        flechaM.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaM.CambiarOrigen();
        flechaM.CambiarPosicion(60, t_atras.GetY()-30);              // Cambiar
        flechaM.Escalar(70.0f, 70.0f); // Escalar al 70%
        flechaM.CambiarColorRojo();
        CambiarFlecha(flechaM, t_normal);
        
        flechaMC.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaMC.CambiarOrigen();
        flechaMC.CambiarPosicion(60, t_atras.GetY()-30);              // Cambiar
        flechaMC.Escalar(70.0f, 70.0f); // Escalar al 70%
        flechaMC.CambiarColorRojo();
        CambiarFlecha(flechaMC, t_no);
    }
    
    void EstadoSeleccion::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->BackSpace()
                || _input->Escape())
            {
                Atras();
            }
            
            /*if (_input->Izq()) {
                opcion--;
                if (opcion < P1)
                {
                    opcion = P2;
                }
            }
            
            if (_input->Der()) {
                opcion++;
                if (opcion > P2)
                {
                    opcion = P1;
                }
            }*/
        } else {
            // Color rojo/blanco del texto
            _input->RatonSobre(t_atras);
            _input->RatonSobre(t_jugar);
            _input->RatonSobre(t_normal);
            _input->RatonSobre(t_pesadilla);
            _input->RatonSobre(t_si);
            _input->RatonSobre(t_no);
            
            if (_input->RatonSobre(p1))
            {
                CambiarFlecha(p1);
                opcion = P1;
            }
            if (_input->RatonSobre(p2))
            {
                CambiarFlecha(p2);
                opcion = P2;
            }
            /*if (_input->RatonSobre(p3))
            {
                CambiarFlecha(p3);
                opcion = P3;
            }
            if (_input->RatonSobre(p4))
            {
                CambiarFlecha(p4);
                opcion = P4;
            }*/
            
            // Clic sobre texto
            if (_input->RatonIzq()) {
                if(_input->IsTextoClicked(t_atras))
                {
                    Atras();
                }
                
                if(_input->IsTextoClicked(t_jugar))
                {
                    Jugar();
                }
                
                if (_input->IsTextoClicked(t_normal))
                {
                    CambiarFlecha(flechaM, t_normal);
                    modoNormal = true;
                }
                if (_input->IsTextoClicked(t_pesadilla))
                {
                    CambiarFlecha(flechaM, t_pesadilla);
                    modoNormal = false;
                }
                if (_input->IsTextoClicked(t_si))
                {
                    CambiarFlecha(flechaMC, t_si);
                    modoContrarreloj = true;
                }
                if (_input->IsTextoClicked(t_no))
                {
                    CambiarFlecha(flechaMC, t_no);
                    modoContrarreloj = false;
                }
            }
        }
    }
    
    void EstadoSeleccion::Actualizar(float tiempoActual)
    {
        switch (opcion)
        {
            case P1:
                CambiarFlecha(p1);
                break;
            case P2:
                CambiarFlecha(p2);
                break;
            /*case P3:
                CambiarFlecha(p3);
                break;
            case P4:
                CambiarFlecha(p4);
                break;*/
        }
    }
    
    void EstadoSeleccion::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        Animar();
        _juego->_ventana->DibujarSprite(p1);
        _juego->_ventana->DibujarSprite(p2);
        _juego->_ventana->DibujarSprite(flecha);
        _juego->_ventana->DibujarTexto(t_modo);
        _juego->_ventana->DibujarTexto(t_normal);
        _juego->_ventana->DibujarTexto(t_pesadilla);
        _juego->_ventana->DibujarSprite(flechaM);
        _juego->_ventana->DibujarTexto(t_modoC);
        _juego->_ventana->DibujarTexto(t_si);
        _juego->_ventana->DibujarTexto(t_no);
        _juego->_ventana->DibujarSprite(flechaMC);
        _juego->_ventana->DibujarTexto(t_atras);
        _juego->_ventana->DibujarSprite(flechaAtras);
        _juego->_ventana->DibujarTexto(t_jugar);
        _juego->_ventana->DibujarSprite(flechaJugar);

        _juego->_ventana->Mostrar();
    }
    
    void EstadoSeleccion::Atras()
    {
        _juego->maquina.Eliminar();
    }
    
    void EstadoSeleccion::CambiarFlecha(SpriteM personaje)
    {
        flecha.CambiarPosicion(personaje.GetX(),personaje.GetY()-personaje.GetAlto()/2);
    }
    
    void EstadoSeleccion::CambiarFlecha(SpriteM &f, Texto texto)
    {
        f.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoSeleccion::Animar()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(opcion)
            {
                case P1:
                    p1.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    p1.CambiarOrigen(60/2,80/2);
                    break;
                case P2:
                    p2.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    p2.CambiarOrigen(60/2,80/2);
                    break;
                /*case P3:
                    break;
                case P4:
                    break;*/
            }
            
            contadorSpriteReposo++;
            if(contadorSpriteReposo == 8)
            {
                contadorSpriteReposo = 0;
            }
            relojAnim.ReiniciarSegundos();
        }
    }
    
    /*void EstadoSeleccion::Player4()
    {
        EstadoJuego::Instance(); // Creamos el puntero
        EstadoJuego::Instance()->Personaje("x", modoNormal, modoContrareloj);
        CambiarEstadoMaquina();
    }*/
    void EstadoSeleccion::Jugar()
    {
        EstadoJuego::Instance(); // Creamos el puntero
        switch(opcion)
        {
            case P1:
                EstadoJuego::Instance()->Personaje("Espadachina",1, modoNormal, modoContrarreloj);
                break;
            case P2:
                EstadoJuego::Instance()->Personaje("Espadachina",1, modoNormal, modoContrarreloj); //MAMBO
                break;
            /*case P3:
                EstadoJuego::Instance()->Personaje("x", modoNormal, modoContrarreloj);
                break;
            case P4:
                EstadoJuego::Instance()->Personaje("x", modoNormal, modoContrarreloj);
                break;*/
        }
        CambiarEstadoMaquina();
    }
    void EstadoSeleccion::CambiarEstadoMaquina()
    {
        // Cambiamos de estado la maquina
        cout<<"Modo normal: " << modoNormal << " Modo contrarreloj: " << modoContrarreloj <<endl;
        _juego->maquina.Anyadir(EstadoJuego::Instance(), true);
    }
}