#include "Input.hpp"
namespace Motor
{
    Input::Input()
    {
        _ventana = Ventana::Instance();
        t.Arriba = false;
        t.Abajo = false;
        t.Enter = false;
        t.BackSpace = false;
        t.Escape = false;
    }
    
    void Input::CerrarVentana()
    {
        _ventana->Cerrar();
    }
    
    bool Input::BucleEventos()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_ventana->pollEvent(event))
        {
            switch(event.type)
            {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    CerrarVentana();
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        t.Escape=true;
                    } else {
                        t.Escape=false;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        t.Arriba=true;
                    } else {
                        t.Arriba=false;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        t.Abajo=true;
                    } else {
                        t.Abajo=false;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        t.Enter=true;
                    } else {
                        t.Enter=false;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
                        t.BackSpace=true;
                    } else {
                        t.BackSpace=false;
                    }
                    return true;
                break;
            }
        }
        return false;
    }
    
    Teclas Input::GetPressed()
    {
        return t;
    }
}