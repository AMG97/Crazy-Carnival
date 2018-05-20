#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Common/b2Math.h"
#include <map>
#include <iostream>
using namespace std;

namespace Motor
{
    /// Un vector de 2 dimensiones
    struct vector2f : private b2Vec2{
        vector2f():b2Vec2(){}
        vector2f(b2Vec2 vector){
            x = vector.x;
            y = vector.y;
        }
        vector2f(float dimX, float dimY):b2Vec2((float32)dimX, (float32)dimY){}
        virtual ~vector2f(){}
        
        ///Usado para poner a 0 el vector
        void setZero(){SetZero();}
        ///Set de las coordenadas pasadas 
        void set(float dimX, float dimY){Set((float32)dimX, (float32)dimY);}
        ///Invierte el vector
        vector2f operator -() const { vector2f v; v.set(-x, -y); return v; }
        ///Sumar un vector a otro
        void operator += (const vector2f& v){x += v.x; y += v.y;}
        ///Restar un vector a otro
        void operator -= (const vector2f& v){x -= v.x; y -= v.y;}
        ///Multipliar el vector por un escalar
        void operator *= (float a){x *= a; y *= a;}
        ///Devuelve la longitud (la normal?)
        float length() const{return Length();}
        /// Get the length squared. For performance, use this instead of
	/// b2Vec2::Length (if possible).
        float lengthSquared() const{return LengthSquared();}
        /// Convert this vector into a unit vector. Returns the length.
        float normalizar(){return (float)Normalize();}
        ///Devuelve la primera posicion del vector
        float getX(){return (float)x;}
        ///Devuelve la segunda posicion del vector
        float getY(){return (float)y;}
        ///Modifica la primera posicion del vector
        void setX(float n){x = (float32)n;}
        ///Modifica la segunda posicion del vector
        void setY(float n){y = (float32)n;}
        /// Does this vector contain finite coordinates?
        bool isValid() const{return IsValid();}
        /// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
        vector2f skew() const{return skew();}
        
        ///Convierte el vector a Vector de Box2D
        b2Vec2 convertTob2(){return b2Vec2(x, y);}
        
        ///Imprime por consola los valores del vector separados por un espacio
        void print(){
            std::cout<<x<<" "<<y<<std::endl;
        }
    };
    
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
        void CambiarColorRojo();
        void CambiarColorBlanco();
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
        bool InterseccionContiene(SpriteM s);
        ///A este no le afecta la colisión de pixel
        bool InterseccionContieneSP(SpriteM s);
        bool Interseccion(SpriteM s);
        ///A este no le afecta la colision de pixel
        bool InterseccionSP(SpriteM s);
        bool InterseccionPixel(SpriteM* s);
    };
    
    class Camara
    {
    public:
        static Camara* Instance();
        ~Camara();
        ///Hay que pasarle un vector de centro, un vector para el tamaño y uno para los límites del mapa
        void CrearCamara(vector2f centro, vector2f tam, vector2f limits);
        sf::View& GetCamara();
        void setTam(float x, float y);
        void mover(int x, int y);
        void setCentro(int x, int y);
        void limitar(int* x, int* y);
        void toggleStatic();
        
        int getX();
        int getY();
        float getHeight();
        float getWidth();
        bool staticCam;
        

    private:
        Camara() {};
        Camara(const Camara &);
        Camara &operator=(const Camara &);
        static Camara* _pinstance2;
        vector2f limit;
        
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
        void DibujarTexto(Texto txt, Camara* camara);
        void DibujarTexto(Texto txt);
        void DibujarSprite(SpriteM sprite, Camara* camara);
        void DibujarSprite(SpriteM sprite);
        void SetCamaraPorDefecto();
        void setCamara(Camara &camara);
        void setBackground(int r, int g, int b);
        void setBackground2(int r, int g, int b,int a);
        sf::Image Capturar();
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
            short int MouseMoved;
            short int Resized;
        };
        
        Input();
        float GetPosicionRatonX();
        float GetPosicionRatonY();
        void Reescalar();
        
        Eventos Evento();
        short int GetTipoEvento();
        bool RatonPulsado(sf::Mouse::Button boton);
        bool TeclaPulsada(sf::Keyboard::Key key);
        bool IsTextoClicked(Texto& object);
        bool RatonSobre(Texto& object);
        bool RatonSobre(SpriteM& object);
        
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
        bool F9();
        
    private:
        Ventana* _ventana;
        Camara* _camara;
        Eventos eventos;
    };
    
}