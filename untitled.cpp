#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<array> 


class Button {
public:
	Button(){}
    Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color textColor,sf::Font &fonts,sf::Vector2f Coord) {
        button.setSize(buttonSize);
        button.setPosition(Coord);
        button.setOutlineThickness(3);
        button.setOutlineColor(sf::Color(0, 0, 0));

        // Get these for later use:
        btnWidth = buttonSize.x;
        btnHeight = buttonSize.y;

        text.setString(btnText);
        text.setCharacterSize(charSize);
        text.setFillColor(textColor);
        text.setFont(fonts);
        float div = 2.0 + btnHeight / btnWidth;
        float yPos = (Coord.y + btnHeight / 2) - (text.getLocalBounds().height / 2);
        float xPos = (Coord.x + btnWidth / 2) - (text.getLocalBounds().width / 2) - 2;
        text.setPosition(xPos, yPos);
    }
    void changeParameters(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color textColor,sf::Font &fonts,sf::Vector2f Coord) {
        button.setSize(buttonSize);
        button.setPosition(Coord);
        button.setOutlineThickness(3);
        button.setOutlineColor(sf::Color(0, 0, 0));

        // Get these for later use:
        btnWidth = buttonSize.x;
        btnHeight = buttonSize.y;

        text.setString(btnText);
        text.setCharacterSize(charSize);
        text.setFillColor(textColor);
        text.setFont(fonts);
        float div = 2.0 + btnHeight / btnWidth;
        float yPos = (Coord.y + btnHeight / 2) - (text.getLocalBounds().height / 2);
        float xPos = (Coord.x + btnWidth / 2) - (text.getLocalBounds().width / 2) - 2;
        text.setPosition(xPos, yPos);
    }
    void setBackColor(sf::Color color) {button.setFillColor(color);}
    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }
    bool isMouseOver(sf::RenderWindow &window) {
        sf::Vector2i mouseCoords( sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y );
        sf::Vector2f realCoords = window.mapPixelToCoords(mouseCoords);
        int btnPosX = button.getPosition().x;
        int btnPosY = button.getPosition().y;
        int btnxPosWidth = button.getPosition().x + button.getGlobalBounds().width;
        int btnyPosHeight = button.getPosition().y + button.getGlobalBounds().height;
        if (realCoords.x < btnxPosWidth && realCoords.x > btnPosX && realCoords.y < btnyPosHeight && realCoords.y > btnPosY) return true;
        return false;
}
    
private:
	sf::RectangleShape button;
	sf::Text text;

	float btnWidth;
	float btnHeight;
};

class Zone{
public:
	Zone(){}
    Zone(sf::Vector2f size, sf::Color insideColor, sf::Vector2f position, int thickness,sf::Color lineColor){
        zone.setSize(size);
        zone.setFillColor(insideColor);
        zone.setPosition(position);
        zone.setOutlineThickness(thickness);
        zone.setOutlineColor(lineColor);
    } 
	sf::RectangleShape zone;
};



class Musician {
public:
    Musician() {}
    
    virtual void setParameters(std::string wavPath[], std::string pngPath[]) = 0;
    virtual void modifVolume(int moinsOuPlus) = 0;
    virtual void modifPitch(int moinsOuPlus) = 0;
    virtual bool switchVal(bool changement, int &aChanger) = 0;


    virtual ~Musician() {} 
    protected:
        sf::SoundBuffer sndBuffer[4];
        sf::Texture textureStance;
        sf::Texture tabTexture[3];
        sf::Sprite tabSprite[3];
        sf::Sprite stance;
        sf::Sound Sound[4]; 
};


class Tambour: public Musician{
    public:
        Tambour(){}
        void setParameters(std::string wavPath[], std::string pngPath[]){
            int i;
            for (i = 0;i < 4;i++){
                sndBuffer[i].loadFromFile(wavPath[i]);
                drumSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[0],tabSprite[0],pngPath[0],110,210,0.17f);
            load_sprite(tabTexture[1],tabSprite[1],pngPath[1],125,174,0.17f);
            load_sprite(tabTexture[2],tabSprite[2],pngPath[2],124,193,0.17f);
            load_sprite(tabTexture[3],tabSprite[3],pngPath[3],124,204,0.17f);
            load_sprite(textureStance,stance,pngPath[4],123,176,0.17f);

            enableAffichageBoutons = 0;
            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) drumSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) drumSound[i].setVolume(soundVolume);
            }
        }
        void modifPitch(int moinsOuPlus){
            if (moinsOuPlus == 1 && soundPitch < 8){
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) drumSound[i].setPitch(soundPitch);
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) drumSound[i].setPitch(soundPitch);
            }
        }
        bool switchVal(bool changement,int &aChanger){
            if (changement){
                if (aChanger){
                    aChanger = 0;
                    return 1;
                }
                else{
                    aChanger = 1;
                    return 0;
                }
            }
            return 0;
        }
        sf::Sound drumSound[4];
        int enableAffichageBoutons;
        sf::Sprite stance;
        sf::Sprite tabSprite[4];
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) {
            texture.loadFromFile(pngPath);
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
        float soundVolume;
        float soundPitch;
        sf::SoundBuffer sndBuffer[4];
        sf::Texture textureStance;
        sf::Texture tabTexture[4];
        
        
        


};

class Guitariste : public Musician{    
    public:
        Guitariste(){}
        void setParameters(std::string wavPath[4],std::string pngPath[4]){
            int i;
            for (i = 0;i < 4;i++){
                sndBuffer[i].loadFromFile(wavPath[i]);
                guitarSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[0],tabSprite[0],pngPath[0],385,111,0.30f);
            load_sprite(tabTexture[1],tabSprite[1],pngPath[1],385,121,0.30f);
            load_sprite(tabTexture[2],tabSprite[2],pngPath[2],385,110,0.30f);
            load_sprite(textureStance,stance,pngPath[3],385,67,0.25f);

            enableAffichageBoutons = 0;
            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) guitarSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) guitarSound[i].setVolume(soundVolume);
            }
        }
        void modifPitch(int moinsOuPlus){
            if (moinsOuPlus == 1 && soundPitch < 8){
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) guitarSound[i].setPitch(soundPitch);
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) guitarSound[i].setPitch(soundPitch);
            }
        }
        bool switchVal(bool changement,int &aChanger){
            if (changement){
                if (aChanger){
                    aChanger = 0;
                    return 1;
                }
                else{
                    aChanger = 1;
                    return 0;
                }
            }
            return 0;
        }

        int enableAffichageBoutons;
        
        sf::Sprite stance;
        sf::Sprite tabSprite[3];

        sf::Sound guitarSound[4];
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) {
            texture.loadFromFile(pngPath);
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
        float soundVolume;
        float soundPitch;
        sf::SoundBuffer sndBuffer[4];
        sf::Texture textureStance;
        sf::Texture tabTexture[3];
};

class Ocarina: public Musician{
    public:
        Ocarina(){}
        void setParameters(std::string wavPath[], std::string pngPath[]){
            int i;
            for (i = 0;i < 4;i++){
                sndBuffer[i].loadFromFile(wavPath[i]);
                OcaSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[0],tabSprite[0],pngPath[0],500,150,0.30f);
            load_sprite(tabTexture[1],tabSprite[1],pngPath[1],500,150,0.30f);
            load_sprite(tabTexture[2],tabSprite[2],pngPath[2],500,150,0.30f);
            load_sprite(textureStance,stance,pngPath[3],500,70,5.0);

            enableAffichageBoutons = 0;
            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) OcaSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) OcaSound[i].setVolume(soundVolume);
            }
        }
        void modifPitch(int moinsOuPlus){
            if (moinsOuPlus == 1 && soundPitch < 8){
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) OcaSound[i].setPitch(soundPitch);
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) OcaSound[i].setPitch(soundPitch);
            }
        }
        bool switchVal(bool changement,int &aChanger){
            if (changement){
                if (aChanger){
                    aChanger = 0;
                    return 1;
                }
                else{
                    aChanger = 1;
                    return 0;
                }
            }
            return 0;
        }
        sf::Sound OcaSound[4] ;
        int enableAffichageBoutons;
        sf::Sprite stance;
        sf::Sprite tabSprite[4];
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) {
            texture.loadFromFile(pngPath);
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
        float soundVolume;
        float soundPitch;
        sf::SoundBuffer sndBuffer[4];
        sf::Texture textureStance;
        sf::Texture tabTexture[4];
}; 


void changeColor(sf::RenderWindow &W,Button &btn){
    if (btn.isMouseOver(W))btn.setBackColor(sf::Color(128, 128, 128));
	else btn.setBackColor(sf::Color(150, 150, 150));
}

void defilementSprite(sf::RenderWindow &W,sf::Sprite tabSprite[],int Taille){
    static int index = 0;
    static int i = 0;
    W.draw(tabSprite[index]);
    i++;
    if (i == 300){
        i = 0;
        index++;
    }
    if (index == Taille) index = 0;
}

bool switchVal(bool changement,int &aChanger){
            if (changement){
                if (aChanger){
                    aChanger = 0;
                    return 1;
                }
                else{
                    aChanger = 1;
                    return 0;
                }
            }
            return 0;
        }

int main(){
    // Déclaration des variables générales
    int i;
    int j = 0;
    int guit = 0;
    int oldEnableInst[5] = {0,0,0,0};
    int enableInst[5] = {0,0,0,0};
    int guitaristeAppuye = 0;
    int debutSprite = 0;
    sf::Sound currentSound[4];
    int currentNote[4] = {0,0,0,0};
    int currentP = 0;
    int onLoop = 0;

    int guitarOnLoop = 0;
    int enableGuitarChords[4] = {0,0,0,0};
    int verifGuitare = 0;
    int lowEnable = 0;
    int alternant = 0;

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1115, 800), "C'est long comme chaine de caracteres"); // (Longueur,Hauteur)
    
    // Zones des boutons
    Zone rectBoutInst(sf::Vector2f(222, 800),sf::Color(190,190,190),sf::Vector2f(893, 0),-7,sf::Color(130, 130, 130));
    Zone rectContNoir1(sf::Vector2f(222, 800),sf::Color::Transparent,sf::Vector2f(893, 0),-2,sf::Color(0, 0, 0));
    Zone rectBoutAct(sf::Vector2f(893, 228),sf::Color(190,190,190),sf::Vector2f(0, 572),-7,sf::Color(130, 130, 130));
    Zone rectContNoir2(sf::Vector2f(893, 228),sf::Color::Transparent,sf::Vector2f(0, 572),-2,sf::Color(0, 0, 0));

    // Chargement de la police
    sf::Font Pix;
    Pix.loadFromFile("Pixel_font.ttf");

    // Chargement de l'image de fond
    sf::Texture backgroundTexture1;
    backgroundTexture1.loadFromFile("podium.png");
    sf::Sprite backgroundSprite1(backgroundTexture1);
    backgroundSprite1.setScale(0.95f,0.95f);    

    // Boutons des musiciens
    int boutonsAppuyes[5] = {0,0,0,0,0};
    Button tabBoutonInstruments[5];
    char Instruments[5][20] = {"GUITARE","BATTERIE","OCARINA","TROMBONE","CHANT"};
    for (i = 0;i < 5;i++) tabBoutonInstruments[i].changeParameters(Instruments[i],sf::Vector2f(170,50), 14, sf::Color::Black,Pix,sf::Vector2f(919, 15+100*i));

    // Bouton pour fermer la fenêtre
    Button fermeture("X", sf::Vector2f(35,35), 14, sf::Color::Black,Pix,sf::Vector2f(990, 730));

    // Déclaration du guitariste
    Guitariste guitarist;
    std::string wav[4] = {"guitare//guit1.wav","guitare//guit2.wav","guitare//guit3.wav","guitare//guit4.wav"};
    std::string png[4] = {"guitare//R1.png","guitare//R2.png","guitare//R3.png","guitare//Stance.png"};
    guitarist.setParameters(wav,png);


    // Déclaration du batteur
    Tambour drummer;
    std::string wav2[4] = {"batterie//batt1.wav","batterie//batt2.wav","batterie//batt3.wav","batterie//batt4.wav"};
    std::string png2[5] = {"batterie//BL1.png","batterie//BL2.png","batterie//BR1.png","batterie//BR2.png","batterie//Stance.png"};
    drummer.setParameters(wav2,png2);
    
    //Déclaration de l'ocarina
    Ocarina ocarina;
    std::string wav3[4] = {"ocarina//oca1.wav","ocarina//oca2.wav","ocarina//oca3.wav","ocarina//oca4.wav"};
    std::string png3[4] = {"ocarina//oca1.png","ocarina//oca2.png","ocarina//oca3.png","ocarina//Stance.png"};
    ocarina.setParameters(wav3,png3);
    // Paramétrage des boutons du guitariste
    Button N1("NOTE 1",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(30,620));
    Button N2("NOTE 2",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(200,620));
    Button N3("NOTE 3",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(370,620));
    Button N4("NOTE 4",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(540,620));
    Button NOTES[4] = {N1,N2,N3,N4};
    Button LOOP("ON LOOP",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(710,620));
    Button VP("VOL +",sf::Vector2f(100,40),14,sf::Color::Black,Pix,sf::Vector2f(150,700));
    Button VM("VOL -",sf::Vector2f(100,40),14,sf::Color::Black,Pix,sf::Vector2f(30,700));
    Button PM("LOW PITCH",sf::Vector2f(180,40),14,sf::Color::Black,Pix,sf::Vector2f(300,700));
    Button PP("HIGH PITCH",sf::Vector2f(180,40),14,sf::Color::Black,Pix,sf::Vector2f(500,700));


    while (window.isOpen()){
        sf::Event event;

        for (i = 0;i < 5;i++){
            if (oldEnableInst[i] == 0 && enableInst[i] ==1){
                for (j = 0;j < 5;j++){
                    if (j != i){
                        if (enableInst[j] == 1) enableInst[j] = 0;
                    }
                }
            }
        }
        for (i = 0;i < 5;i++) oldEnableInst[i] = enableInst[i];
        
        
        while (window.pollEvent(event)){
            if (event.type == sf::Event::MouseButtonPressed){

                // Appui du bouton de fermeture de la fenêtre
                if (fermeture.isMouseOver(window)) window.close();

                // Appui des boutons relatifs au choix d'instrument
                for (i = 0;i < 5;i++){
                    switchVal(tabBoutonInstruments[i].isMouseOver(window),enableInst[i]);
                    if (enableInst[i] && i == 0){
                        for (j = 0;j < 4;j++) currentSound[j] = guitarist.guitarSound[j];
                        currentP = 1;
                    }
                    else if (enableInst[i] && i == 1){
                        for (j = 0;j < 4;j++) currentSound[j] = drummer.drumSound[j];
                        currentP = 2;
                    }
                    else if (enableInst[i] && i == 2){
                        for (j = 0;j < 4;j++) currentSound[j] = ocarina.OcaSound[j];
                        currentP = 3;
                    }
                }
                
                // Boutons des notes
                for (i = 0;i < 4;i++) switchVal(NOTES[i].isMouseOver(window),currentNote[i]);

                if (VM.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifVolume(-1);
                    else if (enableInst[1]) drummer.modifVolume(-1);
                    else if (enableInst[2]) ocarina.modifVolume(-1);
                }
                if (VP.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifVolume(1);
                        else if (enableInst[1]) drummer.modifVolume(1);
                        else if (enableInst[2]) ocarina.modifVolume(1);    
                }
                if (PM.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifPitch(-1);
                    else if (enableInst[1]) drummer.modifPitch(-1);
                    else if (enableInst[2]) ocarina.modifPitch(-1);

                }
                if (PP.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifPitch(1);
                    else if (enableInst[1]) drummer.modifPitch(1);
                    else if (enableInst[2]) ocarina.modifPitch(1);
                }

                lowEnable = switchVal(LOOP.isMouseOver(window),onLoop);
                if (lowEnable) for (i = 0;i < 4;i++) currentNote[i] = 0;

                if (onLoop) for (i = 0;i < 4;i++) currentSound[i].setLoop(1);

            }
        }
        window.clear();

        // Affichage de l'image de fond
        window.draw(backgroundSprite1);

        // Affichage des zones des boutons
        window.draw(rectBoutInst.zone);
        window.draw(rectBoutAct.zone);
        window.draw(rectContNoir1.zone);
        window.draw(rectContNoir2.zone);

        // Affichage et changement de couleur des boutons (si la souris passe dessus)
        for (i = 0;i < 5;i++) changeColor(window,tabBoutonInstruments[i]);
        for (i = 0;i < 5;i++) tabBoutonInstruments[i].drawTo(window);
        changeColor(window,fermeture);
        fermeture.drawTo(window);

        if (currentP){
           for (i = 0;i < 4;i++) NOTES[i].drawTo(window);
            for (i = 0;i < 4;i++) changeColor(window,NOTES[i]);

            LOOP.drawTo(window);
            changeColor(window,LOOP);
            VP.drawTo(window);
            changeColor(window,VP);
            VM.drawTo(window);
            changeColor(window,VM);
            PM.drawTo(window);
            changeColor(window,PM);
            PP.drawTo(window);
            changeColor(window,PP); 
            
        }
        



//*************$$$$************************************************************


        for (i = 0;i < 4;i++){
            if (currentNote[i]){
                if (currentP == 1) defilementSprite(window,guitarist.tabSprite,3);
                if (currentP == 2) defilementSprite(window,drummer.tabSprite,4);
                if (currentP == 3) defilementSprite(window,ocarina.tabSprite,3);
                if (onLoop){
                    if (currentSound[i].getStatus() == 0) currentSound[i].play();
                    continue;
                }
                if (currentNote[i] == 1) currentSound[i].play();
                currentNote[i] = 2;
                if (currentSound[i].getStatus() == 0) currentNote[i] = 0;
            }
        }
        if (currentP == 0 || currentP == 1) window.draw(drummer.stance);
        if (currentP == 0 || currentP == 2) window.draw(guitarist.stance);
        if (currentP == 0 || currentP == 3) window.draw(ocarina.stance);



        for (i = 0;i < 4;i++) if (currentNote[i]) break;
        if (i == 4){
            window.draw(guitarist.stance);
            window.draw(drummer.stance);
            window.draw(ocarina.stance);
            
        }

        window.display();
    }
    return 0;
}