
#include "MainMenu.hpp"

MainMenu::MainMenu(float width, float height){
    
    if(!font.loadFromFile("Font/sansation.ttf")){
        cout << "No font is here";
    }
    
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(sf::Color::White);
    mainMenu[0].setString("MANDELBROT");
    mainMenu[0].setCharacterSize(40);
    mainMenu[0].setPosition(450,60);
    
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(sf::Color::White);
    mainMenu[1].setString("JULIA 1");
    mainMenu[1].setCharacterSize(40);
    mainMenu[1].setPosition(450,130);
    
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(sf::Color::White);
    mainMenu[2].setString("JULIA 2");
    mainMenu[2].setCharacterSize(40);
    mainMenu[2].setPosition(450,210);
    
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(sf::Color::White);
    mainMenu[3].setString("BURNING SHIP");
    mainMenu[3].setCharacterSize(40);
    mainMenu[3].setPosition(450,290);
    
    
    
    mainMenuSelected = -1;
}

MainMenu::~MainMenu(){
    
}

//Draw MainMenu
void MainMenu::draw(RenderWindow& window){
    for(int i=0; i<Max_main_menu; i++){
        window.draw(mainMenu[i]);
    }
}

//MoveUp
void MainMenu::MoveUp(){
    if(mainMenuSelected >= 0){
        mainMenu[mainMenuSelected].setFillColor(Color::White);
        
        mainMenuSelected--;
        if(mainMenuSelected == -1){
            mainMenuSelected = 3;
        }
        mainMenu[mainMenuSelected].setFillColor(Color::Black);
    }
}

//MoveDown
void MainMenu::MoveDown(){
    if(mainMenuSelected+1 <= Max_main_menu) {
        mainMenu[mainMenuSelected].setFillColor(Color::White);
        
        mainMenuSelected++;
        if(mainMenuSelected == 4){
            mainMenuSelected = 0;
        }
        mainMenu[mainMenuSelected].setFillColor(Color::Black);
    }
}
