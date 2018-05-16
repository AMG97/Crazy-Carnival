#pragma once

namespace Crazy
{
    class Estado 
    {
    public:
        virtual void Vaciar() = 0;
        virtual void Init() = 0;
        virtual void ManejarEventos() = 0;
        virtual void Actualizar(float tiempoActual) = 0;
        virtual void Dibujar(float tiempoActual) = 0;
        
        virtual void Pausar() { }
        virtual void Reanudar() { }
    };
}