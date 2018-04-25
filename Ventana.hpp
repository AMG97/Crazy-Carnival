#pragma once
using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Motor
{
    class Ventana : public sf::RenderWindow
    {
    public:
        static Ventana* Instance();
        ~Ventana();
        
        void CrearVentana(int ancho, int alto, string titulo);
        bool EstaAbierta();
        void Limpiar();
        void Mostrar();
        void Cerrar();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
    };
}