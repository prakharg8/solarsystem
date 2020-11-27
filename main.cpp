#include "Entity.h"

const int width = 1700, height = 1000;

//helper functions for vectors
float getMagnitude(Vector2f& v) {
    return pow(pow(v.x, 2) + pow(v.y, 2), 0.5);
}
void makeUnitVector(Vector2f& v) {
    float mag = getMagnitude(v);
    v.x /= mag;
    v.y /= mag;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "toy solar system");
    vector<Entity> solsystem;
    Entity sun(25, 333000, Vector2f(width / 2, height / 2), { 0,0 });
    sun.entity.setFillColor(Color(255, 255, 0));
    Vector2f vel = { 0,0 }, pos = { 0,0 };
    float scale = 0.001, G = .001;
    Clock loop, speed;
    Time timeInterval = milliseconds(50), increment = microseconds(4000);

    while (window.isOpen())
    {
        bool showOrbit = true;
        loop.restart();
        vel = { 0,0 };
        //events
        sf::Event event;
        while (window.pollEvent(event))
        {
            int index;
            switch (event.type) {
            case Event::Closed:
                window.close();
                break;
            case Event::MouseButtonPressed:
                pos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                solsystem.push_back(Entity(5, 1, pos, vel));
                cout << "entity added" << endl;
                break;
            case Event::MouseButtonReleased:
                vel = (operator*(scale, pos) - operator*(scale, Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y)));
                index = (int)solsystem.size() - 1;
                solsystem[index].setVel(vel);
                solsystem[index].setForces(true);
                break;
            case Event::MouseWheelMoved:
                if (event.mouseWheel.delta > 0 && timeInterval.asMilliseconds() <= 100) timeInterval = timeInterval + increment;
                else if (event.mouseWheel.delta < 0 && timeInterval.asMilliseconds() >= 1) timeInterval = timeInterval - increment;
                if (timeInterval.asMilliseconds() < 1) timeInterval = milliseconds(1);
                else if (timeInterval.asMilliseconds() > 100) timeInterval = milliseconds(100);
                break;
            }
        }

        if (speed.getElapsedTime() >= timeInterval) {
            //physics implementation
			for (int i = 0, size = (int)solsystem.size(); i < size; i++) {
				if (solsystem[i].getForces()) {
					Vector2f gravity = { 0,0 }, gdir = sun.entity.getPosition() - solsystem[i].entity.getPosition();
					if (getMagnitude(gdir) <= sun.getRadius()) {
						solsystem.erase(solsystem.begin() + i);
						i--;
						size--;
						continue;
					}
					float gmag = G * (sun.getMass() / (pow(getMagnitude(gdir), 2)));
					makeUnitVector(gdir);
					gravity = operator*(gmag, gdir);
					solsystem[i].setVel(solsystem[i].getVel() + gravity);
				}
				solsystem[i].entity.move(solsystem[i].getVel());
			}
            speed.restart();
        }

        //drawing
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            showOrbit = false;
        }
        if (showOrbit)window.clear(Color(0, 0, 0));
        for (int i = 0, size = (int)solsystem.size(); i < size; i++) {
            solsystem[i].draw(window);
        }
        sun.draw(window);
        window.display();
    }
    return 0;
}
