#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<array> 
#include <vector>
#include <list>

// La classe Button qui va permettre de créer des instances de boutons
class Button {
public:
    // Les constructeurs du bouton
	Button(){}
    Button(std::string btnText, sf::Vector2f buttonSize, int charSize, sf::Color textColor,sf::Font &fonts,sf::Vector2f Coord) {
        button.setSize(buttonSize);                         // Initialisation de la taille du bouton
        button.setPosition(Coord);                          // Initialisation de la position du bouton
        button.setOutlineThickness(3);                      // Initialisation de la largeur extérieur du bouton
        button.setOutlineColor(sf::Color(0, 0, 0));         // Initialisation de la couleur du bouton

        // Get these for later use:
        btnWidth = buttonSize.x;
        btnHeight = buttonSize.y;

        text.setString(btnText);                            // Initialisation du texte dans le bouton
        text.setCharacterSize(charSize);                    // Initialisation de la taille du texte
        text.setFillColor(textColor);                       // Initialisation de la couleur du texte
        text.setFont(fonts);                                // Initialisation de la police du texte
        
        float yPos = (Coord.y + btnHeight / 2) - (text.getLocalBounds().height / 2);
        float xPos = (Coord.x + btnWidth / 2) - (text.getLocalBounds().width / 2) - 2;
        text.setPosition(xPos, yPos);                       // Initialisation de la position du texte dans le bouton
    }

    // Méthode pour modifier tous les paramètres d'un bouton (ou lui en ajouter si on a utilisé le premier constructeur avec rien en argument)
    // donc identique au constructeur précédent
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
        float yPos = (Coord.y + btnHeight / 2) - (text.getLocalBounds().height / 2);
        float xPos = (Coord.x + btnWidth / 2) - (text.getLocalBounds().width / 2) - 2;
        text.setPosition(xPos, yPos);
    }

    // Méthode pour modifier la couleur du fond du bouton
    void setBackColor(sf::Color color) {button.setFillColor(color);}

    // Méthode pour afficher le bouton dans la fenêtre (window) (en affichant le button et le text)
    void drawTo(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(text);
    }

    // Méthode pour vérifier si lorsque sf::Event::MouseButtonPressed (si la souris est appuyé) la souris se situe au dessus du bouton ou non
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

    // Opérateur pour afficher les paramètres d'un bouton
    friend std::ostream& operator<<(std::ostream& os, const Button& btn) {
        os << "Button details: \n";
        os << "Width: " << btn.btnWidth;
        os << "| Height: " << btn.btnHeight << "\n";
        return os;
    }

    // Opérateur pour vérifier si deux boutons sont égaux selon leurs mesures
    bool operator==(const Button& other) const {
        return btnWidth == other.btnWidth && btnHeight == other.btnHeight;
    }
    
private:
	sf::RectangleShape button;
	sf::Text text;

	float btnWidth;
	float btnHeight;
};

// La classe Zone va permettre de créer plusieurs formes rectangulaires aisément
class Zone{
public:
    // Les constructeurs de zone
	Zone(){}
    Zone(sf::Vector2f size, sf::Color insideColor, sf::Vector2f position, int thickness,sf::Color lineColor){
        zone.setSize(size);                     // Initialisation de la taille
        zone.setFillColor(insideColor);         // Initialisation de la couleur intérieure
        zone.setPosition(position);             // Initialisation de la position
        zone.setOutlineThickness(thickness);    // Initialisation de la largeur extérieure
        zone.setOutlineColor(lineColor);        // Initialisation de la couleur de la largeur extérieure
    }

    // On garde zone en public pour pouvoir y accéder lorsque l'on dessine la zone dans la fenêtre (window.draw(nom_lambda.zone))
	sf::RectangleShape zone;
};


// La classe musicien est la classe mère de celles que l'on utilsera plus tard, elle contient donc les méthodes virtuelles et les attributs généraux
class Musician {
public:
    Musician() {}
    
    virtual void setParameters(std::list<std::string> wavPath, std::list<std::string> pngPath) = 0;
    virtual void modifVolume(int moinsOuPlus) = 0; //méthode virtuelle pour modifier le volume des sons propres à chacun des musiciens
    virtual void modifPitch(int moinsOuPlus) = 0; //méthode virtuelle pour modifier le pitch des sons propres à chacun des musiciens


    virtual ~Musician() {} 
protected: //attributs protégés pour que les classes filles puissent y accéder
    sf::SoundBuffer sndBuffer[4]; //tableau de buffer pour les sons
    sf::Texture textureStance;//texture pour l'image au repos 
    sf::Texture tabTexture[4];//tableau de texture pour les postures des musiciens
    sf::Sprite tabSprite[4]; //tableau de sprite pour les postures des musiciens
    sf::Sprite stance; //sprite pour l'image au repos
    sf::Sound Sound[4]; //tableau de son
    float soundVolume; //attribut pour le volume du son
    float soundPitch; //attribut pour le pitch du son
};

// Les classes Guitariste, Violon, Ocarina et Tambour héritent de la classe Musicien
class Tambour: public Musician{
    public:
        Tambour(){}
          
        void setParameters(std::list<std::string> wavPath, std::list<std::string> pngPath){ //méthode pour charger les images via une liste de string
            int i = 0;
            auto wavIter = wavPath.begin();
            auto pngIter = pngPath.begin();
            for (; wavIter != wavPath.end() && i < 4; ++wavIter, ++i){
                sndBuffer[i].loadFromFile(*wavIter);
                drumSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[0],tabSprite[0],*pngIter++,110,210,0.17f); //on charge les images via la méthode load_sprite et on les place
            load_sprite(tabTexture[1],tabSprite[1],*pngIter++,125,174,0.17f); 
            load_sprite(tabTexture[2],tabSprite[2],*pngIter++,124,193,0.17f);
            load_sprite(tabTexture[3],tabSprite[3],*pngIter++,124,204,0.17f);
            load_sprite(textureStance,stance,*pngIter,123,176,0.17f);
            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){ //méthode pour modifier le volume du son
            if (moinsOuPlus == 1) soundVolume = soundVolume + 10.0; 
            else soundVolume = soundVolume - 10.0;
            for (int i = 0;i < 4;i++) drumSound[i].setVolume(soundVolume); //on parcourt le tableau de son pour modifier le volume
        }
        void modifPitch(int moinsOuPlus){ //méthode pour modifier le pitch du son
            if (moinsOuPlus == 1 && soundPitch < 8) soundPitch = soundPitch + 1;
            else if (moinsOuPlus == -1 && soundPitch > 1) soundPitch = soundPitch - 1;
            for (int i = 0;i < 4;i++) drumSound[i].setPitch(soundPitch);
        }
        sf::Sound drumSound[4];
        sf::Sprite stance;
        sf::Sprite tabSprite[4];
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) { //méthode pour charger les images
            texture.loadFromFile(pngPath);
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
};

class Guitariste : public Musician{    
    public:
        Guitariste(){}
        void setParameters(std::list<std::string> wavPath, std::list<std::string> pngPath){ //méthode pour charger les images via une liste de string
            int i = 1;
            auto wavIter = wavPath.begin(); //itérateur pour parcourir la liste  de fichier wav
            auto pngIter = pngPath.begin(); //itérateur pour parcourir la liste  de fichier png
            for (; wavIter != wavPath.end() && i < 4; ++wavIter, ++i){ //on parcourt la liste de fichier wav
                sndBuffer[i].loadFromFile(*wavIter);
                guitarSound[i].setBuffer(sndBuffer[i]); //on charge les sons via la méthode loadFromFile
            }


            load_sprite(tabTexture[0],tabSprite[0],*pngIter++,385,111,0.30f); //on charge les images via la méthode load_sprite et on les place
            load_sprite(tabTexture[1],tabSprite[1],*pngIter++,385,121,0.30f);
            load_sprite(tabTexture[2],tabSprite[2],*pngIter++,385,110,0.30f);
            load_sprite(textureStance,stance,*pngIter,385,67,0.25f);

            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){ //méthode pour modifier le volume du son
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) guitarSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) guitarSound[i].setVolume(soundVolume);
            }
        }
        void modifPitch(int moinsOuPlus){ //méthode pour modifier le pitch du son
            if (moinsOuPlus == 1 && soundPitch < 8){
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) guitarSound[i].setPitch(soundPitch);
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){ //on parcourt le tableau de son pour modifier le pitch
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) guitarSound[i].setPitch(soundPitch);
            }
        }

        
        sf::Sprite stance; //sprite pour l'image en position de base du guitariste
        sf::Sprite tabSprite[3]; //tableau de sprites pour les animation du guitariste

        sf::Sound guitarSound[4]; //tableau de sons du guitariste
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) { 
            texture.loadFromFile(pngPath); //méthode pour charger les images depuis un fichier
            sprite.setTexture( texture ); //on affecte la texture au sprite
            sprite.setPosition(sf::Vector2f(PosX,PosY)); //on place le sprite à la position (PosX,PosY)
            sprite.setScale(Scale,Scale); //on met à l'echelle le sprite
        }
};



class Violon: public Musician{
    public:
        Violon(){}
        void setParameters(std::list<std::string> wavPath, std::list<std::string> pngPath){
            int i = 0;
            auto wavIter = wavPath.begin(); //itérateur pour parcourir la liste  de fichier wav
            auto pngIter = pngPath.begin(); //itérateur pour parcourir la liste  de fichier png
            for (; wavIter != wavPath.end() && i < 4; ++wavIter, ++i){ //on parcourt la liste de fichier wav
                sndBuffer[i].loadFromFile(*wavIter);
                VioSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[1],tabSprite[1],*pngIter++,75,270,1);
            load_sprite(tabTexture[2],tabSprite[2],*pngIter++,75,270,1);
            load_sprite(tabTexture[0],tabSprite[0],*pngIter++,75,270,1); //on charge les images via la méthode load_sprite et on les place
            load_sprite(textureStance,stance,*pngIter,75,270,1);

            soundVolume = 100.0; //on initialise le volume à 100
            soundPitch = 1; //on initialise le pitch à 1
        }
        void modifVolume(int moinsOuPlus){
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) VioSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) VioSound[i].setVolume(soundVolume);//on parcourt le tableau de son pour modifier le volume
            }
        }
        void modifPitch(int moinsOuPlus){
            if (moinsOuPlus == 1 && soundPitch < 8){
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) VioSound[i].setPitch(soundPitch);
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) VioSound[i].setPitch(soundPitch);//on parcourt le tableau de son pour modifier le pitch
            }
        }
        sf::Sound VioSound[4] ;
        sf::Sprite stance;
        sf::Sprite tabSprite[4];
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) { //méthode pour charger les images
            texture.loadFromFile(pngPath); //on charge les images via la méthode loadfromfile
            sprite.setTexture( texture ); //affectation de la texture au sprite
            sprite.setPosition(sf::Vector2f(PosX,PosY));//placement du sprite à la position (PosX,PosY)
            sprite.setScale(Scale,Scale); //mise à l'echelle du sprite
        }

};

class Ocarina: public Musician{
    public:
        Ocarina(){} //constructeur
        void setParameters(std::list<std::string> wavPath, std::list<std::string> pngPath){ //méthode pour charger les images via une liste de string
            int i = 0;
            auto wavIter = wavPath.begin(); //itérateur pour parcourir la liste  de fichier wav
            auto pngIter = pngPath.begin(); //itérateur pour parcourir la liste  de fichier png
            for (; wavIter != wavPath.end() && i < 4; ++wavIter, ++i){
                sndBuffer[i].loadFromFile(*wavIter);
                OcaSound[i].setBuffer(sndBuffer[i]);
            }

            load_sprite(tabTexture[0],tabSprite[0],*pngIter++,537,152,0.16f); //on charge les images via la méthode load_sprite et on les place
            load_sprite(tabTexture[1],tabSprite[1],*pngIter++,537,152,0.16f); 
            load_sprite(tabTexture[2],tabSprite[2],*pngIter++,537,152,0.16f);
            load_sprite(textureStance,stance,*pngIter,535,168,0.16f);

            soundVolume = 100.0;
            soundPitch = 1;
        }
        void modifVolume(int moinsOuPlus){ //méthode pour modifier le volume du son
            if (moinsOuPlus == 1){
                soundVolume = soundVolume + 10.0;
                for (int i = 0;i < 4;i++) OcaSound[i].setVolume(soundVolume);
            }
            else{
                soundVolume = soundVolume - 10.0;
                for (int i = 0;i < 4;i++) OcaSound[i].setVolume(soundVolume);
            }
        }
        void modifPitch(int moinsOuPlus){ //méthode pour modifier le pitch du son
            if (moinsOuPlus == 1 && soundPitch < 8){ 
                soundPitch = soundPitch + 1;
                for (int i = 0;i < 4;i++) OcaSound[i].setPitch(soundPitch); //on parcourt le tableau de son pour modifier le pitch
            }
            else if (moinsOuPlus == -1 && soundPitch > 1){
                soundPitch = soundPitch - 1;
                for (int i = 0;i < 4;i++) OcaSound[i].setPitch(soundPitch); //on parcourt le tableau de son pour modifier le pitch
            }
        }
        sf::Sound OcaSound[4] ; //tableau de son
        sf::Sprite stance; //sprite pour l'image de chef d'orchestre
        sf::Sprite tabSprite[4]; //tableau de sprite pour les images de chef d'orchestre
    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) { //méthode pour charger les images
            texture.loadFromFile(pngPath); 
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
}; 


// cette classe diffère des autres car elle ne contient pas de son mais uniquement des images c'est pourquoi elle n'hérite pas de la classe Musicien
class Chef_Orchecstre{
    public:
        Chef_Orchecstre(){} //constructeur
        void setParameters(std::vector<std::string> pngPath){ //méthode pour charger les images

            load_sprite(tabTexture[0],tabSprite[0],pngPath[0],720,359,0.135f); //on charge les images via la méthode load_sprite et on les place
            load_sprite(tabTexture[1],tabSprite[1],pngPath[1],650,360,0.14f);
            load_sprite(tabTexture[2],tabSprite[2],pngPath[2],680,367,0.155f);
            load_sprite(tabTexture[3],tabSprite[3],pngPath[3],650,374,0.15f);
            load_sprite(textureStance,stance,pngPath[4],734,370,0.14f);
        }
        sf::Sprite stance; //sprite pour l'image de chef d'orchestre
        sf::Sprite tabSprite[4]; //tableau de sprite pour les images de chef d'orchestre

    private:
        void load_sprite(sf::Texture &texture,sf::Sprite &sprite,std::string pngPath,int PosX,int PosY,float Scale) { //méthode pour charger les images
            texture.loadFromFile(pngPath);
            sprite.setTexture( texture );
            sprite.setPosition(sf::Vector2f(PosX,PosY));
            sprite.setScale(Scale,Scale);
        }
        sf::Texture textureStance; //texture pour l'image de chef d'orchestre
        sf::Texture tabTexture[4]; //tableau de texture pour les images de chef d'orchestre
};

        

// Fonction de changement de couleur du bouton, à utiliser lorsque la souris passe sur un bouton
void changeColor(sf::RenderWindow &W,Button &btn){
    if (btn.isMouseOver(W))btn.setBackColor(sf::Color(128, 128, 128));
	else btn.setBackColor(sf::Color(150, 150, 150));
}

//Fonction pour parcourir le tableau de nos sprites pour donner un effet d'animation
void defilementSprite(sf::RenderWindow &W,sf::Sprite tabSprite[],int Taille){ 
    static int index = 0; // index de parcours du tableau de sprite
    static int i = 0; // compteur pour le défilement
    W.draw(tabSprite[index]); // on dessine le sprite à l'index courant
    i++;
    if (i == 400){ //400 est une sorte de compteur pour avoir un défilement régulier
        i = 0;
        index++; // on passe à l'index suivant
    }
    if (index == Taille) index = 0; // si on arrive à la fin du tableau on revient au début
}

// Fonction pour changer la valeur d'une variable selon un événement
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

// Définition du main
int main(){
    // Déclaration des variables générales
    int i;                              // Compteur pour les for
    int j = 0;                          // Compteur pour les for secondaires
   
    int oldEnableInst[4] = {0,0,0,0};   // Tableau de valeurs pour les activations précédentes des musiciens
    int enableInst[4] = {0,0,0,0};      // Tableau de valeurs pour les activations actuelles des musiciens
    
    int currentNote[4] = {0,0,0,0};     // Tableau de valeurs pour les activations des notes
    int currentP = 0;                   // Indice du musicien actuel
    int onLoop = 0;                     // Indicateur de la répétition ou non de la musique
    int lowEnable = 0;                  // Indicateur inverse

    // Création de la fenêtre
    sf::RenderWindow window(sf::VideoMode(1115, 800), "Concert aux Jeux Olympiques"); // (Longueur,Hauteur)
    
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

    // Création et Placement des boutons des musiciens
    Button tabBoutonInstruments[4];
    char Instruments[4][20] = {"GUITARE","BATTERIE","OCARINA","VIOLON"};
    for (i = 0;i < 4;i++) tabBoutonInstruments[i].changeParameters(Instruments[i],sf::Vector2f(170,50), 14, sf::Color::Black,Pix,sf::Vector2f(919, 15+100*i));

    // Bouton pour fermer la fenêtre
    Button fermeture("X", sf::Vector2f(35,35), 14, sf::Color::Black,Pix,sf::Vector2f(990, 730));

    // Déclaration du guitariste et chargement des sons et png
    Guitariste guitarist;
    std::list<std::string> wav = {"guitare//guit1.wav","guitare//guit2.wav","guitare//guit3.wav","guitare//guit4.wav"};
    std::list<std::string> png = {"guitare//R1.png","guitare//R2.png","guitare//R3.png","guitare//Stance.png"};
    guitarist.setParameters(wav,png);

    // Déclaration du violoniste et chargement des sons et png
    Violon violonist;
    std::list<std::string> wav1 = {"violon//violon1.wav","violon//violon2.wav","violon//violon3.wav","violon//violon4.wav"};
    std::list<std::string> png1 = {"violon//violon1.png","violon//violon2.png","violon//violon3.png","violon//Stance.png"};
    violonist.setParameters(wav1,png1);

    // Déclaration du batteur et chargement des sons et png
    Tambour drummer;
    std::list<std::string> wav2 = {"batterie//batt1.wav","batterie//batt2.wav","batterie//batt3.wav","batterie//batt4.wav"};
    std::list<std::string> png2 = {"batterie//BL1.png","batterie//BL2.png","batterie//BR1.png","batterie//BR2.png","batterie//Stance.png"};
    drummer.setParameters(wav2,png2);
    
    //Déclaration de l'ocarina et chargement des sons et png
    Ocarina ocarina;
    std::list<std::string> wav3 = {"ocarina//oca1.wav","ocarina//oca2.wav","ocarina//oca3.wav","ocarina//oca4.wav"};
    std::list<std::string> png3 = {"ocarina//oca1.png","ocarina//oca2.png","ocarina//oca3.png","ocarina//Stance.png"};
    ocarina.setParameters(wav3,png3);

    // Déclaration du chef d'orchestre et chargement des sons et png
    Chef_Orchecstre chef;
    std::vector<std::string> png4 = {"chef//chef1.png","chef//chef2.png","chef//chef3.png","chef//chef4.png","chef//Stance.png"};
    chef.setParameters(png4);

    // Paramétrage des boutons
    Button N1("NOTE 1",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(30,620));          // Bouton pour la note 1
    Button N2("NOTE 2",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(200,620));         // Bouton pour la note 2
    Button N3("NOTE 3",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(370,620));         // Bouton pour la note 3
    Button N4("NOTE 4",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(540,620));         // Bouton pour la note 4
    Button NOTES[4] = {N1,N2,N3,N4};                                                                // Tableau des notes
    Button LOOP("ON LOOP",sf::Vector2f(150,40),14,sf::Color::Black,Pix,sf::Vector2f(710,620));      // Bouton pour mettre la musique en répétition
    Button VP("VOL +",sf::Vector2f(100,40),14,sf::Color::Black,Pix,sf::Vector2f(150,700));          // Bouton pour augmenter le volume du son
    Button VM("VOL -",sf::Vector2f(100,40),14,sf::Color::Black,Pix,sf::Vector2f(30,700));           // Bouton pour baisser le volume du son
    Button PM("LOW PITCH",sf::Vector2f(180,40),14,sf::Color::Black,Pix,sf::Vector2f(300,700));      // Bouton pour baisser le pitch du son
    Button PP("HIGH PITCH",sf::Vector2f(180,40),14,sf::Color::Black,Pix,sf::Vector2f(500,700));     // Bouton pour augmenter le pitch du son
    
    //test surcharge opérateur <<
    std::cout << fermeture << std::endl;
    
    //test surcharge opérateur ==
    if (tabBoutonInstruments[0] == tabBoutonInstruments[1]) std::cout << "Les boutons sont de mêmes dimensions" << std::endl;
    else std::cout << "Les boutons sont de différentes dimensions" << std::endl;

    // Boucle de la simulation, on n'en sortira qu'une fois la fenêtre fermée
    while (window.isOpen()){
        sf::Event event;                // Variable de l'événement

        // Vérification de si il y a un changement de musicien et désactivation du musicien précédemment sélectionné
        for (i = 0;i < 4;i++){
            if (oldEnableInst[i] == 0 && enableInst[i] ==1){        // Si un nouveau musicien a été sélectionné
                for (j = 0;j < 4;j++){
                    if (j != i){                                    // On vérifie parmi les autres si il y'en a d'activé
                        if (enableInst[j] == 1) enableInst[j] = 0;  // On les désactive si c'est le cas
                    }
                }
                currentP = i + 1;                                   // On modifie l'indice du musicien actuel en conséquence
            }
        }
        for (i = 0;i < 4;i++) oldEnableInst[i] = enableInst[i];     // On passe les nouvelles aux anciennes
        
        // Boucle de si il y a un événement
        while (window.pollEvent(event)){
            // Si la souris a été cliqué on va vérifier au dessus de quels boutons 
            if (event.type == sf::Event::MouseButtonPressed){

                // Appui du bouton de fermeture de la fenêtre
                if (fermeture.isMouseOver(window)) window.close();

                // Appui des boutons relatifs au choix d'instrument
                for (i = 0;i < 5;i++) switchVal(tabBoutonInstruments[i].isMouseOver(window),enableInst[i]);
                
                // Boutons des notes
                for (i = 0;i < 4;i++){
                    if (NOTES[i].isMouseOver(window)){
                        // Si on est en mode loop, on active la note qui a été appuyée selon le musicien actuel puis on saute le reste juste après
                        if (onLoop){
                            if (currentP == 1 && guitarist.guitarSound[i].getStatus() != 2) guitarist.guitarSound[i].play();
                            if (currentP == 2 && drummer.drumSound[i].getStatus() != 2) drummer.drumSound[i].play();
                            if (currentP == 3 && ocarina.OcaSound[i].getStatus() != 2) ocarina.OcaSound[i].play();
                            if (currentP == 4 && violonist.VioSound[i].getStatus() != 2) violonist.VioSound[i].play();
                            continue;
                        }

                        // Si on est pas en mode loop mais que la note actuelle a déjà été appuyée, on arrête le son
                        if (currentNote[i]){
                            currentNote[i] = 0;
                            guitarist.guitarSound[i].stop();
                            drummer.drumSound[i].stop();
                            ocarina.OcaSound[i].stop();
                            violonist.VioSound[i].stop();
                        }
                        // À l'inverse, si elle n'a pas été appuyée encore, on active la note
                        else{
                            currentNote[i] = 1;
                        }
                    }
                }

                // Appui du bouton de baisse du volume et selon le musicien actuel on modifie son volume respectif
                if (VM.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifVolume(-1);
                    else if (enableInst[1]) drummer.modifVolume(-1);
                    else if (enableInst[2]) ocarina.modifVolume(-1);
                    else if (enableInst[3]) violonist.modifVolume(-1);
                }
                // Appui du bouton d'augmentation du volume et selon le musicien actuel on modifie son volume respectif
                if (VP.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifVolume(1);
                        else if (enableInst[1]) drummer.modifVolume(1);
                        else if (enableInst[2]) ocarina.modifVolume(1);
                        else if (enableInst[3]) violonist.modifVolume(1);    
                }
                // Appui du bouton de baisse du pitch et selon le musicien actuel on modifie son pitch respectif
                if (PM.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifPitch(-1);
                    else if (enableInst[1]) drummer.modifPitch(-1);
                    else if (enableInst[2]) ocarina.modifPitch(-1);
                    else if (enableInst[3]) violonist.modifPitch(-1);

                }
                // Appui du bouton d'augmentation du pitch et selon le musicien actuel on modifie son pitch respectif
                if (PP.isMouseOver(window)){
                    if (enableInst[0]) guitarist.modifPitch(1);
                    else if (enableInst[1]) drummer.modifPitch(1);
                    else if (enableInst[2]) ocarina.modifPitch(1);
                    else if (enableInst[3]) violonist.modifPitch(1);
                }

                // Vérification d'appui du bouton loop, si on réappuie dessus, on stop tout et on enlève le mode loop pour chaque musicien
                lowEnable = switchVal(LOOP.isMouseOver(window),onLoop);
                if (lowEnable){
                    for (i = 0;i < 4;i++){
                        currentNote[i] = 0;
                        guitarist.guitarSound[i].stop();
                        guitarist.guitarSound[i].setLoop(0);
                        drummer.drumSound[i].stop();
                        drummer.drumSound[i].setLoop(0);
                        ocarina.OcaSound[i].stop();
                        ocarina.OcaSound[i].setLoop(0);
                        violonist.VioSound[i].stop();
                        violonist.VioSound[i].setLoop(0);
                    }
                }
                // Sinon on active le mode loop pour chaque musicien
                if (onLoop){
                    for (i = 0;i < 4;i++){
                        if (currentP == 1) guitarist.guitarSound[i].setLoop(1);
                        if (currentP == 2) drummer.drumSound[i].setLoop(1);
                        if (currentP == 3) ocarina.OcaSound[i].setLoop(1);
                        if (currentP == 4) violonist.VioSound[i].setLoop(1);
                    }
                }
            }
        }
        
        
        // Nettoyage de la fenêtre
        window.clear();

        // Affichage de l'image de fond
        window.draw(backgroundSprite1);

        // Affichage des zones des boutons
        window.draw(rectBoutInst.zone);
        window.draw(rectBoutAct.zone);
        window.draw(rectContNoir1.zone);
        window.draw(rectContNoir2.zone);

        // Affichage et changement de couleur des boutons (si la souris passe dessus)
        for (i = 0;i < 4;i++) changeColor(window,tabBoutonInstruments[i]);
        for (i = 0;i < 4;i++) tabBoutonInstruments[i].drawTo(window);
        changeColor(window,fermeture);
        fermeture.drawTo(window);

        // Affichage des boutons propres aux musiciens
        if (currentP){
            for (i = 1;i < 4;i++) NOTES[i].drawTo(window);
            for (i = 1;i < 4;i++) changeColor(window,NOTES[i]);

            if (currentP != 1){                 // Dû à un bug au niveau de la note 1 du guitariste, on saute son bouton note 1
                NOTES[0].drawTo(window);
                changeColor(window,NOTES[0]);
            }

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
        
        // Affichage des différents sprites ou de la stance d'un musicien selon si une musique propre à lui est en train d'être joué
        for (i = 0;i < 4;i++){
            if (guitarist.guitarSound[i].getStatus() != 0){             // Si un son est joué (status != 0) on défile le sprite et on empêche 
                defilementSprite(window,guitarist.tabSprite,3);         // le compteur i d'atteindre la valeur 4
                break;
            }
        }
        if (i == 4) window.draw(guitarist.stance);                      // Si i a atteint 4, ça veut dire qu'aucun son n'est joué donc stance de base

        // Même chose
        for (i = 0;i < 4;i++){
            if (violonist.VioSound[i].getStatus() != 0){
                defilementSprite(window,violonist.tabSprite,3);
                break;
            }
        }
        if (i == 4) window.draw(violonist.stance);

        for (i = 0;i < 4;i++){
            if (drummer.drumSound[i].getStatus() != 0){
                defilementSprite(window,drummer.tabSprite,4);
                break;
            }
        }
        if (i == 4) window.draw(drummer.stance);

        for (i = 0;i < 4;i++){
            if (ocarina.OcaSound[i].getStatus() != 0){
                defilementSprite(window,ocarina.tabSprite,3);
                break;
            }
        }
        if (i == 4) window.draw(ocarina.stance);
        
        // Affichage des différents sprites ou de la stance du chef d'orchestre selon si un son est en train d'être joué ou non
        for (i = 0;i < 4;i++){
            if (ocarina.OcaSound[i].getStatus() != 0 || drummer.drumSound[i].getStatus() != 0 || guitarist.guitarSound[i].getStatus() != 0 || violonist.VioSound[i].getStatus() != 0){
                defilementSprite(window,chef.tabSprite,4);
                break;
            }
        }
        if (i == 4) window.draw(chef.stance);

        // For des sons
        for (i = 0;i < 4;i++){
            if (currentNote[i] == 1){           // Si une note a été activé
                if (onLoop){                    // Si on est en mode loop, on skip car on s'en occupe déjà plus haut
                    continue;
                }

                // Selon le joueur actuel, on joue la note respective
                if (currentP == 1) guitarist.guitarSound[i].play();
                if (currentP == 2) drummer.drumSound[i].play();
                if (currentP == 3) ocarina.OcaSound[i].play();
                if (currentP == 4) violonist.VioSound[i].play();
                currentNote[i] = 2;                 // Puis on passe à deux pour signifier que le son a été activé
            }
            else if (currentNote[i] == 2){          // Si le son a déjà été activé
                if (currentP == 1 && guitarist.guitarSound[i].getStatus() == 0) currentNote[i] = 0;     // Si on atteint la fin du son, currentNote
                if (currentP == 2 && drummer.drumSound[i].getStatus() == 0) currentNote[i] = 0;         // repasse à 0
                if (currentP == 3 && ocarina.OcaSound[i].getStatus() == 0) currentNote[i] = 0;
                if (currentP == 4 && violonist.VioSound[i].getStatus() == 0) currentNote[i] = 0;
            }
        }

        // Affichage de la fenêtre
        window.display();
    }

    // Fin du main
    return 0;
}