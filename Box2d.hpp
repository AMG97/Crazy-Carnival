#pragma once

#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
using namespace std;

namespace Box2d
{
    class Mundo : public b2World
    {
    public:
        Mundo(b2Vec2& gravity){ };
        //Mundo(float x, float y);
        
    };
    class Cuerpo : public b2Body
    {
    public:
        Cuerpo(){};
    };
    class CuerpoDefinicion : public b2BodyDef
    {
    public:
        
    private:
        float posicionX;
        float posicionY;
    };
    class Fixture : public b2Fixture
    {
    };
    class FixtureDEfinicion : public b2FixtureDef
    {
    };
    class Forma : public b2PolygonShape
    {
    };
}
