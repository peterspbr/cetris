#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Integers
const int windowWidth = 800, windowHeight = 600;
int theShape, theShapeSize;
int shapeLocation[] = {0, 64, 160, 256, 352, 480, 576};
int shapeSize[] = {64, 96};

// Double precision
float positionX, positionY, velocity;

// Bool
bool falling, drawShape;

int main()
{
    // Variables initialisation
    theShape = 1;
    positionX = windowWidth / 2;
    velocity = 0.1f;
    drawShape = true;

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
        if(!shape.loadFromFile("assets/textures/shapes.png", IntRect(shapeLocation[theShape], 0, shapeSize[theShapeSize], 64)))
        {
            cout << "Error: Cannot open texture" << endl;
            window.close();
            return 1;  
        }

        // Adjust the size of the shape to fit the quare one.
        if(theShape == 0)
        {
            theShapeSize = 0; // If the shape is the quare one, then adjust to 64x64.
        } else {
            theShapeSize = 1; // Else adjust to 96x64.
        }

        // Create sprite
        Sprite shapeSprite;
        shapeSprite.setTexture(shape);

        float lastPosition; // Store the last position of the last drawn shape to calculate the last shape collision point.

        shapeSprite.setOrigin(Vector2f(0.0f, 0.0f)); // Set the origin of the sprite to the center of the texture.

        // Makes the sprite fall until it touches the end of the screen
        if(positionY <= (windowHeight - lastPosition) - 64)
        {
            positionY += velocity;
            falling = true;
        }
        else if(positionY >= (windowHeight - lastPosition) - 64)
        {
            positionY = 0.0f;
            srand(time(NULL));
            theShape = rand() % 7;
            lastPosition += 64; // All the shapes is 64px tall, so the value is static.
            falling = false;
            drawShape = true;
            printf("Last position of shape: %f\n", lastPosition); // For debug purposes.
        }

        // Exit the game if the shepes reach the top of the window, just like in Tetris.
        if(lastPosition > windowHeight)
        {
            printf("Game over\n");
            exit(0);
        }

        // Sprite transformations
        shapeSprite.setPosition(Vector2f(positionX, positionY));

        // Clear, draw then display
        window.clear(Color::Black);
        if(drawShape)
        {
            window.draw(shapeSprite);
        }
        window.display();
    }

    return 0;
}