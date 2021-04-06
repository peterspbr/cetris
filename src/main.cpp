#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Integers
const int windowWidth = 800, windowHeight = 600;
int shapeLocation[] = {0, 64, 160, 256, 352, 448, 544};
int shapeSize[] = {64, 96};

// Double precision
float positionX, positionY, velocity;

// Bool
bool falling = true;

int main()
{
    // Variables initialisation
    positionX = windowWidth / 2;
    velocity = 0.1f;

    // Create SFML window
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Cetris");

    // Game loop
    while(window.isOpen())
    {
        // Poll events
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }

            if(Keyboard::isKeyPressed(Keyboard::Left) && positionX > 180 &&  falling){positionX -= 32.0f;}
            if(Keyboard::isKeyPressed(Keyboard::Right) && positionX < 450 && falling){positionX += 32.0f;}
            if(Keyboard::isKeyPressed(Keyboard::Down)){velocity = 0.3f;} else {velocity = 0.1f;}
        }
        
        // Get texture from file
        Texture shape;
        if(!shape.loadFromFile("assets/textures/shapes.png", IntRect(shapeLocation[1], 0, shapeSize[1], 64)))
        {
            cout << "Error: Cannot open texture" << endl;
            window.close();
            return 1;  
        }

        shape.setSmooth(true); // Set antialiasing

        // Create sprite
        Sprite shapeSprite;
        shapeSprite.setTexture(shape);

        shapeSprite.setOrigin(Vector2f(0.0f, 0.0f));

        // Makes the sprite fall until it touches the end of the screen
        if(positionY <= windowHeight - 64)
        {
            positionY += velocity;
            falling = true;
        } else if(positionY >= windowHeight - 64)
        {
            falling = false;
            //positionY = 0;
        }

        // Sprite transformations
        shapeSprite.setPosition(Vector2f(positionX, positionY));

        // Clear, draw then display
        window.clear(Color::Black);
        window.draw(shapeSprite);
        window.display();
    }

    return 0;
}