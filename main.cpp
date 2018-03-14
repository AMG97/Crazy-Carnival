#include <iostream>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include <sstream>
#include <ctime>
#include "box.h"
#include <stdio.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

const int PPM = 30;

using namespace std;

struct body
{
    b2BodyDef DEF;
    b2PolygonShape SHAPE;
    b2FixtureDef FIX;
    b2Body * BOD;
	sf::RectangleShape RECT;
};

//modifies to float by BHN
string floatToStr(float number);
float framesPS(sf::Clock &);

int main() {
    /*TiXmlDocument doc( "demo.xml" );
    doc.LoadFile();*/
    sf::RenderWindow app(sf::VideoMode(800,600,32),"Application");

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    body ground;
    ground.DEF.position.Set(400.0f/PPM,600.0f/PPM);
	ground.RECT = sf::RectangleShape(sf::Vector2f(8000,25));//100-50? is size?
	ground.RECT.setOrigin(4000,25);
	ground.RECT.setFillColor(sf::Color(200,75,20,255));
    ground.SHAPE.SetAsBox(4000.0f/PPM,25.0f/PPM);
    ground.BOD = world.CreateBody(&ground.DEF);
    ground.FIX.shape = &ground.SHAPE;
	ground.FIX.density = .7f;
	ground.FIX.friction = .9f;
    ground.BOD->CreateFixture(&ground.SHAPE,1.0f);

	//text stuff to appear on the page
	//added these guys BHN

    float timeStep = 1 / 180.0f;
	sf::Event Event = sf::Event();
    sf::Clock Clock;

    sf::Clock fpsClock;
    int frameNumber = 0;
    int lastFPSFrame = 0;
    string lastFPSDisplay;

    //int mouseXs = 0;
    //int mouseYs = 0;
    //int mouseXspeed = 0;
    //int mouseYspeed = 0;
    const int boxes = 400; //adding x boxes where?
    CBox good[boxes];
	int i = 0; 
    for(i; i < boxes; i++) {
		good[i].SetWorld(world);
	}
	//these next two are all me. redefining ground properties for walls BHN
	body leftWall;
    leftWall.DEF.position.Set(0.0f/PPM,-300/PPM);
	leftWall.RECT = sf::RectangleShape(sf::Vector2f(25,8000));//100-50? is size?
	leftWall.RECT.setOrigin(0,4000);
	leftWall.RECT.setFillColor(sf::Color(200,75,200,255));
    leftWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    leftWall.BOD = world.CreateBody(&leftWall.DEF);
    leftWall.FIX.shape = &leftWall.SHAPE;
	leftWall.FIX.density = .7f;
	leftWall.FIX.friction = .9f;
    leftWall.BOD->CreateFixture(&leftWall.SHAPE,1.0f);

	body rightWall;
    rightWall.DEF.position.Set(800.0f/PPM,-300/PPM);
	rightWall.RECT = sf::RectangleShape(sf::Vector2f(25,8000));//100-50? is size?
	rightWall.RECT.setOrigin(25,4000);
	rightWall.RECT.setFillColor(sf::Color(100,205,20,255));
    rightWall.SHAPE.SetAsBox(25.0f/PPM,4000.0f/PPM);
    rightWall.BOD = world.CreateBody(&rightWall.DEF);
    rightWall.FIX.shape = &rightWall.SHAPE;
	rightWall.FIX.density = .7f;
	rightWall.FIX.friction = .9f;
    rightWall.BOD->CreateFixture(&rightWall.SHAPE,1.0f);

	while(app.isOpen())
    {
        world.Step(timeStep,8,3);
        //mouseXs = app.GetInput().GetMouseX();
        //mouseYs = app.GetInput().GetMouseY();
		char buff[32];

        frameNumber++;
		if (fpsClock.getElapsedTime().asMilliseconds() > 1000) {
            char buf[64];
            
            lastFPSDisplay = string(buf);
            lastFPSFrame = frameNumber;
			fpsClock.restart();
            fflush(stdout);
        }

        sf::Event events;
        while (app.pollEvent(events)) {
			switch (events.type) {
				case sf::Event::Closed:
					app.close();
				break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						app.clear();
						app.display();
						good->setN(0);
						for(int i = 0; i < boxes; i++) {
							good[i].ResetPosition(world);
						}
					}/* draw other squares
					 else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::G)) {
						app.Clear();
						app.Display();
						good->setN(0);
						for(int i = 0; i < boxes; i++) {
							good[i] = CBox(world);
						}
					} */else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						app.close();
					else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
						for(int i = 0; i < boxes; i++) {
							good[i].jump(90);
						}
					}

				break;
			}
		}

        for(int i = 0; i < boxes; i++) {
            good[i].update();
        }

       ground.RECT.setPosition(ground.BOD->GetPosition().x*PPM,ground.BOD->GetPosition().y*PPM);
	   //offset by 25? why?
	   leftWall.RECT.setPosition(leftWall.BOD->GetPosition().x*PPM, leftWall.BOD->GetPosition().y*PPM);
	   rightWall.RECT.setPosition(rightWall.BOD->GetPosition().x*PPM, rightWall.BOD->GetPosition().y*PPM);
        //mouseXspeed = app.GetInput().GetMouseX() - mouseXs;
        //mouseYspeed = app.GetInput().GetMouseY() - mouseYs;

        app.clear();
        app.draw(ground.RECT);
		app.draw(leftWall.RECT);
		app.draw(rightWall.RECT);
        for(int i = 0; i < boxes; i++)
            app.draw(good[i].GetShape());
        

        /*glMatrixMode(GL_PROJECTION);
         glLoadIdentity();
         glOrtho(-50, 50, -50, 50, -1, 1);
         glMatrixMode(GL_MODELVIEW);
         glLoadIdentity();
         world.DrawDebugData();*/

        app.display();
    }

    return 0;
}

float framesPS(sf::Clock & clock)
{
    bool sec = false;
    int count = 0;
    count++;
	if(clock.getElapsedTime().asMilliseconds() >= 1000)
    {
        sec = true;
        clock.restart();
        count = 0;
    }
	float t = (float)clock.getElapsedTime().asMilliseconds();
    float ret = 0;
    if ( t ==  0 ) return 0;
	else {ret = count / (float)clock.getElapsedTime().asMilliseconds(); }
    if ( sec){
		char buf[64];
        fflush(stdout);}
    return ret;
}

