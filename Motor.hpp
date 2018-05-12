#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
using namespace std;

namespace Motor
{
    
    class Reloj : public sf::Clock {
    public:
        Reloj() { };
        float ReiniciarMilisegundos();
        float ReiniciarSegundos();
        float GetSegundos();
        float GetMilisegundos();
    };
    
    class Texto : public sf::Text {
    public:
        Texto() { };
        void CambiarFuente(sf::Font& fuente);
        void CambiarTexto(string text);
        void CambiarTamanyo(int tam);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen(float x, float y);
        
        float GetOrigenX();
        float GetOrigenY();
        float GetAncho();
        float GetAlto();
        float GetTop();
        float GetLeft();
        float GetX();
        float GetY();
    };
    
    class Recursos
    {
    public:
        Recursos() {};
        ~Recursos() {};
        
        void CargarTextura(string nombre, string fichero);
        sf::Texture &GetTextura(string nombre);
        
        void CargarFuente(string nombre, string fichero);
        sf::Font &GetFuente(string nombre);
        
    private:
        map<string, sf::Texture> texturas;
        map<string, sf::Font> fuentes;
    };
    
    class SpriteM : public sf::Sprite {
    public:
        SpriteM() { };
        void CambiarTextura(sf::Texture &textura);
        void CambiarTextRect(int x, int y, int width, int height);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen();
        void CambiarOrigen(float x, float y);
        void CambiarColorRojo();
        void Rotar(float angulo);
        void Escalar(float x, float y);
        void EscalarProporcion(float x, float y);
        void Parpadear(bool parpadeo);
        
        float GetAncho();
        float GetAlto();
        float GetX();
        float GetY();
        void Mover(float v);
        void Mover(float x, float y);
        bool Interseccion1(SpriteM s);
        bool Interseccion2(SpriteM s);
    };
    
    class Camara
    {
    public:
        static Camara* Instance();
        ~Camara();
        void CrearCamara(float centroX, float centroY, float ancho, float alto);
        sf::View& GetCamara();
        void setTam(float x, float y);
        void mover(int x, int y);
        void setCentro(int x, int y);
        int getX();
        int getY();
        float getHeight();
        float getWidth();
        

    private:
        Camara() { };
        Camara(const Camara &);
        Camara &operator=(const Camara &);
        static Camara* _pinstance2;
        
        sf::View camara;
    };
    
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
        void DibujarB(SpriteM sprite, Camara& camara);
        void DibujarC(SpriteM sprite);
        void setCamara(Camara &camara);
        void setBackground(int r, int g, int b);
        sf::RenderWindow& GetVentana();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
        
        sf::RenderWindow window;
        sf::Color background;
    };
    
    class Input
    {
    public:
        struct Eventos {
            short int Closed;
            short int KeyPressed;
            short int KeyReleased;
            short int MouseButtonPressed;
            short int MouseButtonReleased;
        };
        
        Input();
        float GetPosicionRatonX();
        float GetPosicionRatonY();
        
        Eventos Evento();
        short int GetTipoEvento();
        bool RatonPulsado(sf::Mouse::Button boton);
        bool TeclaPulsada(sf::Keyboard::Key key);
        
        bool RatonDer();
        bool RatonIzq();
        bool Der();
        bool Izq();
        bool Arriba();
        bool Abajo();
        bool Escape();
        bool BackSpace();
        bool Enter();
        bool P();
        bool D();
        bool C();
        bool F();
        bool R();
        bool E();
        bool Q();
        
    private:
        Ventana* _ventana;
        Camara* _camara;
        Eventos eventos;
    };
}