#pragma once
using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Texto.hpp"
#include "SpriteM.hpp"

namespace Motor
{
    class Ventana
    {
    public:
        static Ventana* Instance();
        ~Ventana();
        
        void CrearVentana(int ancho, int alto, string titulo);
        bool EstaAbierta();
        void Limpiar();
        void Mostrar();
        void Cerrar();
        void Dibujar(Texto txt);
        void Dibujar(SpriteM sprite);
        sf::RenderWindow& GetVentana();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
        
        sf::RenderWindow window;
    };
}