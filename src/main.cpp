#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

#define width  800
#define height 600

struct Point {int x, y;} a[4], b[4]; // Tetrominos axis

const int fW = 10;
const int fH = 20;

int field[fW][fH] = {0};

int coords[7][4] = {
    1, 3, 5, 7,
    2, 4, 5, 7,
    3, 5, 4, 6,
    3, 5, 4, 7,
    2, 3, 5, 7,
    3, 5, 7, 6,
    2, 3, 4, 5
};

bool check()
{
    for(int i = 0; i < 4; i++)
    {
        if (a[i].x < 0 || a[i].x >= fW || a[i].y >= fH) {return false;}
        else if(field[a[i].y][a[i].x]) {return false;}
    }

    return true;
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(width, height), "Cetris");
    window.setFramerateLimit(30);

    sf::Texture tTexture;
    tTexture.loadFromFile("images/tetrominos.png");
    sf::Texture bgTexture;
    bgTexture.loadFromFile("images/bg.jpg");

    sf::Sprite tetrominos;
    tetrominos.setTexture(tTexture);
    sf::Sprite bg;
    bg.setTexture(bgTexture);

    int xPos = 0, p = 1;
    
    float timer = 0, delay = 0.8;

    bool rotate = false;

    sf::Clock clock;

    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        sf::Event event;

        while(window.pollEvent(event))
        {   
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    rotate = true;
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    xPos = -1;
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    xPos = 1;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                delay = 0.2;
            }
        }

        for(int i = 0; i < 4; i++)
        {
            b[i] = a[i];
            a[i].x += xPos;
        }

        if(!check())
        {
            for(int i = 0; i < 4; i++)
            {
                a[i] = b[i];
            }
        }

        if(rotate)
        {
            Point point = a[1];

            for(int i = 0; i < 4; i++)
            {
                int x = a[i].y - point.y;
                int y = a[i].x - point.x;

                a[i].x = point.x - x;
                a[i].y = point.y + y;
            }

            if(!check())
            {
                for(int i = 0; i < 4; i++)
                {
                    a[i] = b[i];
                }
            }
        }

        if(timer > delay)
        {
            for(int i = 0; i < 4; i++)
            {
                b[i] = a[i];
                a[i].y += 1;
            }

            if(!check())
            {
                for(int i = 0; i < 4; i++)
                {
                    field[b[i].y][b[i].x] = p;
                }

                p = 1 + rand()%7;
                int n = rand()%7;

                for(int i = 0; i < 4; i++)
                {
                    a[i].x = coords[n][i] % 2;
                    a[i].y = coords[n][i] / 2;
                }
            }

            timer = 0;
        }

        int k = fH - 1;

        for (int i = fH - 1; i > 0; i--)
        {
            int count = 0;
            for (int j = 0; j < fW; j++)
            {
                if (field[i][j])
                {
                    count++;
                }
                field[k][j] = field[i][j];
            }

            if (count < fW)
            {
                k--;
            }
        }

        xPos = 0;
        rotate = false;
        delay = 0.8;

        window.clear(sf::Color::Black);
        window.draw(bg);

        for(int i = 0; i < fH; i++)
        {
            for(int j = 0; j < fW; j++)
            {
                if(field[i][j] == 0) {continue;}
                tetrominos.setTextureRect(sf::IntRect(field[i][j] * 16, 0, 16, 16));
                tetrominos.setPosition(j * 18, i * 18);
                window.draw(tetrominos);
            }
        }

        for(int i = 0; i < 4; i++)
        {
            tetrominos.setTextureRect(sf::IntRect(p * 16, 0, 16, 16));
            tetrominos.setPosition(a[i].x * 18, a[i].y * 18);
            window.draw(tetrominos);
        }

        window.display();
    }

    return 0;
}