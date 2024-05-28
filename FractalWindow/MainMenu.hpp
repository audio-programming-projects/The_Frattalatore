#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_main_menu 5

class MainMenu
{
    
public:
    MainMenu(float width, float height);
    ~MainMenu();

    virtual void draw(RenderWindow& window);
    virtual void MoveUp();
    virtual void MoveDown();
    
    int getMainMenuPressed() {
        return mainMenuSelected;
    }
    
    
private:
    int mainMenuSelected;
    sf::Font font;
    sf::Text mainMenu[Max_main_menu];
    
};
