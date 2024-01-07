#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


class Button {
public:
	Button(){}

    Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color bgColor, sf::Color textColor) {
        button.setSize(buttonSize);
        button.setFillColor(bgColor);

        // Get these for later use:
        btnWidth = buttonSize.x;
        btnHeight = buttonSize.y;

        text.setString(btnText);
        text.setCharacterSize(charSize);
        text.setColor(textColor);
    }
	void setText(std::string t) {text.setString(t);}

	void setSize(sf::Vector2f s) {button.setSize(s);}

    void setCharSize(int c) {text.setCharacterSize(c);}

    void setFont(sf::Font &fonts) {text.setFont(fonts);}

    void setBackColor(sf::Color color) {button.setFillColor(color);}

    void setTextColor(sf::Color color) {text.setColor(color);}

	void setPosition(sf::Vector2f point) {
        button.setPosition(point);

        // Center text on button:
        float div = 2.0 + btnHeight / btnWidth;

        float xPos = (point.x + btnWidth / div) - (text.getLocalBounds().width / 2);
        float yPos = (point.y + btnHeight / div) - (text.getLocalBounds().height / 2);
        text.setPosition(xPos, yPos);
    }

	
    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        sf::Vector2i mouseCoords( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y );

        sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);

        float mouseX = realCoords.x;
        float mouseY = realCoords.y;

        int btnPosX = button.getPosition().x;
        int btnPosY = button.getPosition().y;

        int btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
        int btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;

        if (mouseX < btnxPosWidth + 20 && mouseX > btnPosX - 20 && mouseY < btnyPosHeight + 20 && mouseY > btnPosY - 20) {
            return true;
        }
        return false;
    
}
private:
	sf::RectangleShape button;
	sf::Text text;

	float btnWidth;
	float btnHeight;
};




int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 800), "C'est long comme chaine de caracteres"); // (Longueur,Hauteur)
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    
    sf::Texture backgroundTexture1;
    if (!backgroundTexture1.loadFromFile("podium.png")) {
        std::cerr << "Erreur lors du chargement de l'image de fond 1" << std::endl;
        return 1;
    }

    sf::Sprite backgroundSprite1(backgroundTexture1);

    sf::Texture t1;
    t1.loadFromFile("S1.png");
    sf::Sprite S1;
    S1.setTexture(t1);
    S1.setPosition(sf::Vector2f(10, 10));
    S1.setScale(0.5f,0.5f);

    sf::Texture t2;
    t2.loadFromFile("S2.png");
    sf::Sprite S2;
    S2.setTexture(t2);
    S2.setPosition(sf::Vector2f(10, 10));
    S2.setScale(0.5f,0.5f);

    // Pour gérer la taille de l'image affichée si elle est trop grande
    //backgroundSprite1.setScale(0.6f,0.6f);

    // Pour gérer la position de l'image affichée
    //backgroundSprite1.setPosition(220,40);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("Bass.wav")) return -1;
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::Font arial;
    arial.loadFromFile("Pixel_font.ttf");

    Button btn1("Play Game", sf::Vector2f(150,75), 17, sf::Color::Green, sf::Color::Black);
    btn1.setFont(arial);
	btn1.setPosition(sf::Vector2f(625, 700));
    btn1.setText("< GROS BOUTON >");

    int j = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed){
                if (btn1.isMouseOver(window)){
                    j = 1;
                    sound.play();
                }
            }
        }
        if (btn1.isMouseOver(window)) {
			// Highlight buttons when mouse is over them:
			btn1.setBackColor(sf::Color(255, 0, 0));
			}
		else {
			btn1.setBackColor(sf::Color(0, 0, 255));
		}

        window.clear();

        window.draw(backgroundSprite1);
        btn1.drawTo(window);

        if (j == 0 || j == 500){
            window.draw(S1);
            j = 0;
        }
        
        if (j > 0 && j < 500){
            window.draw(S2);
            j++;
            std::cout << j << std::endl;
        }
        
        
        
        window.display();
    }

    return 0;
}