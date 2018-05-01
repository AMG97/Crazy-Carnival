namespace Crazy
{
    class Comportamiento
    {
    public:
        Comportamiento();
        float GetVida();
        float GetTotalVida();
        void SetVida(float v);
        
        void ModificarVida(float modificador);
        
    protected:
        float vida;
        float totalVida;
        float posicionInicial;
    };
}