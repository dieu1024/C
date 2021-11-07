//
//  main.cpp
//
//  Created by 김지우
//

#include <bangtal>
using namespace bangtal;
#include <ctime>
#include <cstdlib>

auto main_scene = Scene::create("", "background.png");
auto easy = Scene::create("","background.png");
auto hard = Scene::create("","background.png");

auto easybutton = Object::create("easy.png", main_scene,405,255);
auto hardbutton = Object::create("hard.png", main_scene,655,255);


void easy_init (){
    easy->enter();
    
    ObjectPtr ecards[12];
    
    for (int ind = 0; ind < 12; ++ind){
        ecards[ind]=Object::create("card.png", easy, 205 + (ind % 4) * (200 + 20), 35 + (ind / 4) * (200 + 20));
        ecards[ind]->setScale(2.f);
    }
    
//    char path[20];
//    for (int i = 0; i < 12; i++){
//            sprintf(path,"fruit%d.png", (i%6)+1);
//    }
//
//    ecards[ind]->setOnMouseCallback([&](auto, int x, int y, auto)->bool{
//
//        ecards[ind]->setImage(path);
//
//        return true;
//    });

}

void hard_init (){
    hard->enter();
    
    ObjectPtr ecards[48];
    
    for (int ind = 0; ind < 48; ++ind){
        ecards[ind]=Object::create("card.png", hard, 205 + (ind % 8) * (100 + 10), 35 + (ind / 8) * (100 + 10));
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    
    easybutton->setOnMouseCallback([&](auto, auto, auto, auto)->bool{
        easy_init();
        easybutton->hide();
        hardbutton->hide();

        return true;
    });
    
    hardbutton->setOnMouseCallback([&](auto, auto, auto, auto)->bool{
        hard_init();
        easybutton->hide();
        hardbutton->hide();

        return true;
    });

    startGame(main_scene);

}
