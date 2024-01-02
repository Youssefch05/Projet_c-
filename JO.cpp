
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "JO.hpp"
#include <iostream>
#include <math.h>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ceremonie des JO!");

    sf::Texture backgroundtexture;
    sf::SoundBuffer buffersaxo;
    buffersaxo.loadFromFile("saxo.wav");

    sf::SoundBuffer bufferviolon;
    bufferviolon.loadFromFile("violon.wav");

    backgroundtexture.loadFromFile("background.jpeg") ;
    sf::Sprite background(backgroundtexture);
    background.setScale(3,3);
    sf::Texture musicientexture;
    musicientexture.loadFromFile("saxo.png");
    sf::Sprite saxo(musicientexture);
    saxo.setScale(0.5,0.5);
    saxo.setPosition(100,100);
    sf::Texture violontexture;
    violontexture.loadFromFile("violon.jpeg");
    sf::Sprite violon(violontexture);
    violon.setScale(0.5,0.5);
    violon.setPosition(200,100);
    

    sf::Sound saxophone;
    saxophone.setBuffer(buffersaxo);


    sf::Sound violoncelle;
    violoncelle.setBuffer(bufferviolon);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i position = sf::Mouse::getPosition(window);
                //std::cout << "X: " << position.x << " Y: " << position.y << std::endl;
                if (position.x > 100 && position.x < 200 && position.y > 100 && position.y < 200){
                    
                    saxophone.play();
                    std::cout << "X: " << position.x << " Y: " << position.y << std::endl;
                }
                if (position.x > 200 && position.x < 300 && position.y > 100 && position.y < 200){
                    
                    violoncelle.play();
                    std::cout << "X: " << position.x << " Y: " << position.y << std::endl;
                }
                
                
            }
        }
        

        window.clear();
        window.draw(background);
        window.draw(saxo);
        window.draw(violon);
        window.display();
    }

    return 0;

}