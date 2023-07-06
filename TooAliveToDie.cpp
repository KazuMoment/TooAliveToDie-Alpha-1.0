#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

//class Node{
    //Node* next;
    //string choice_story;
//}


string choice_story;
string choice_story_2;
string choice_name_confirm;
string choice_battle;
string choice_again;
string dialogue_choice;

string player_name;
string enemy_name;

int Player_currentHP;
int Player_maxHP;
int Player_currentULT;
int Player_maxULT;
int HPbar_width;
int Player_damage;

int Enemy_currentHP;
int Enemy_maxHP;
int Enemy_damage;

int handgun_ammo;

int handgun_flag;
int bat_flag;
int flag_confirm_name = 0;
int flag_choice = 0;

void battle_start_animation(){
    system("CLS");
    PlaySound(TEXT("Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);                                                                                                                        
    cout << "    //   ) )     // | |  /__  ___/  /__  ___/     / /        //   / /" << endl;
    Sleep(50);
    cout << "   //___/ /     //__| |    / /        / /        / /        //____" << endl; 
    Sleep(50);
    cout << "  / __  (      / ___  |   / /        / /        / /        / ____" << endl;    
    Sleep(50); 
    cout << " //    ) )    //    | |  / /        / /        / /        //" << endl; 
    Sleep(50);         
    cout << "//____/ /    //     | | / /        / /        / /____/ / //____/ /" << endl;    
    Sleep(1000);
    system("CLS");

}

void intro(){
    system("CLS");
    PlaySound(TEXT("Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "#### ##   ## ##    ## ##              ##     ####       ####   ### ###  ### ###           #### ##   ## ##            ### ##     ####   ### ###  " << endl;
    Sleep(50);
    cout << "# ## ##  ##   ##  ##   ##              ##     ##         ##     ##  ##   ##  ##           # ## ##  ##   ##            ##  ##     ##     ##  ##  " << endl;
    Sleep(50);
    cout << "  ##     ##   ##  ##   ##            ## ##    ##         ##     ##  ##   ##                 ##     ##   ##            ##  ##     ##     ##      " << endl;
    Sleep(50);
    cout << "  ##     ##   ##  ##   ##            ##  ##   ##         ##     ##  ##   ## ##              ##     ##   ##            ##  ##     ##     ## ##   " << endl;
    Sleep(50);
    cout << "  ##     ##   ##  ##   ##            ## ###   ##         ##     ### ##   ##                 ##     ##   ##            ##  ##     ##     ##      " << endl;
    Sleep(50);
    cout << "  ##     ##   ##  ##   ##            ##  ##   ##  ##     ##      ###     ##  ##             ##     ##   ##            ##  ##     ##     ##  ##  " << endl;
    Sleep(50);
    cout << " ####     ## ##    ## ##            ###  ##  ### ###    ####      ##    ### ###            ####     ## ##            ### ##     ####   ### ###  " << endl;
    Sleep(4500);
}

string Generate_Player_HP_bar(int Player_currentHP, int Player_maxHP, int HPbar_width) {
    float BarRatio = static_cast<float>(Player_currentHP) / Player_maxHP;
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string Player_HP_bar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            Player_HP_bar += "=";
        } else {
            Player_HP_bar += " ";
        }
    }
    Player_HP_bar += "]";

    return Player_HP_bar;
}

string Generate_Player_ULT_bar(int Player_currentULT, int Player_maxULT, int HPbar_width) {
    float BarRatio = static_cast<float>(Player_currentULT) / Player_maxULT;
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string Player_ULT_bar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            Player_ULT_bar += "=";
        } else {
            Player_ULT_bar += " ";
        }
    }
    Player_ULT_bar += "]";

    return Player_ULT_bar;
}

string Generate_Enemy_HP_bar(int Enemy_currentHP, int Enemy_maxHP, int HPbar_width) {
    float BarRatio = static_cast<float>(Enemy_currentHP) / Enemy_maxHP;
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string Enemy_HP_bar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            Enemy_HP_bar += "=";
        } else {
            Enemy_HP_bar += " ";
        }
    }
    Enemy_HP_bar += "]";

    return Enemy_HP_bar;
}

void Ultimate(){
    Player_damage = 50;
    cout << "\n\n" << player_name << " uses their ultimate!";
    PlaySound(TEXT("Ult_Handgun.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(9100);
    cout  << "\n\n" << player_name << " deals " << Player_damage << " of damage to " << enemy_name << "!";
    PlaySound(TEXT("Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(2000);
}

void battle_start() {
    int battle_On = 1;

    PlaySound(TEXT("Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    do {

        do{
        string Player_HP_bar = Generate_Player_HP_bar(Player_currentHP, Player_maxHP, HPbar_width);
        string Player_ULT_bar = Generate_Player_ULT_bar(Player_currentULT, Player_maxULT, HPbar_width);
        cout << "\n" << player_name << " readies their weapon!";
        cout << "\n" << player_name << " HP: " << Player_HP_bar << " " << Player_currentHP << "/" << Player_maxHP;
        cout << "\n" << player_name << " ULT Bar: " << Player_ULT_bar << " " << Player_currentULT << "/" << Player_maxULT;

        string Enemy_HP_bar = Generate_Enemy_HP_bar(Enemy_currentHP, Enemy_maxHP, HPbar_width);
        cout << "\n\n" << enemy_name << " is preparing to attack!";
        cout << "\n" << enemy_name << " HP: " << Enemy_HP_bar << " " << Enemy_currentHP << "/" << Enemy_maxHP;

        Player_damage = 0;
        flag_choice = 0;
        cout << "\n\nWhat do you want to do?";
        cout << "\n1. Attack\n2. Use an item\n3. Use Ultimate" << endl;
        cin >> choice_battle;


      
        if (choice_battle == "1" && handgun_flag == 1) {
            if (handgun_ammo > 0){
                Player_damage = 25;
                cout << "\n" << player_name << " shoots the gun, and deals " << Player_damage << " damage to " << enemy_name << "!";
                Player_currentULT += 10;
                handgun_ammo--; 
                flag_choice = 1;
            }
            else {
                cout << "\n\nYou have no handgun ammo left!";
            }

        } 
        else if (choice_battle == "1" && bat_flag == 1){
            Player_damage = 15;
            cout << "\n" << player_name << " swings the bat, and deals " << Player_damage << " damage to " << enemy_name << "!";
            Player_currentULT += 10;
            flag_choice = 1;
        }

        else if (choice_battle == "2") {


        } 
        
        else if (choice_battle == "3" && Player_currentULT == Player_maxULT) {
            Ultimate();
            flag_choice = 1;
        } 

        else if (choice_battle == "3" && Player_currentULT != Player_maxULT){
            cout << player_name << " tries to use their Ultimate, but failed! The Ultimate Bar has to be full!";

        }

        else if (choice_battle == "9"){
            Ultimate();
            flag_choice = 1;
        }
        
        else {
            cout << "\nInvalid choice. You take damage.";
            flag_choice = 1;

        }
        }while (flag_choice == 0);


        Enemy_currentHP -= Player_damage;

        if (Enemy_currentHP > 0){
        cout << "\n\n" << enemy_name << " attacks! You take " << Enemy_damage << " damage!";
        Player_currentHP -= Enemy_damage;
        }

        if (Enemy_currentHP <= 0){
            battle_On = 0;
            PlaySound(TEXT("You Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou killed " << enemy_name << "!";
            Player_maxHP += 10; 
            cout << "\n\nYour Max HP is increased by 10!";
            Sleep(5000);
        }

        if (Player_currentHP <=0){
            battle_On = 0;
            PlaySound(TEXT("You Died.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\n" << player_name << " died!";
            cout << "\nWould you like to try again? [Y/n]: ";
            do {
            cin >> choice_again;
            if (choice_again == "Y" || choice_again == "y"){
                flag_choice = 1;
                break;
                

            }
            else if (choice_again == "N" || choice_again == "n"){
                cout << "Thank you for playing Too Alive to Die!";
                return;

            }
            else {
                cout << "Invalid input. Try again.";
                flag_choice = 0;
                
            }
            }while (flag_choice == 0);
        }





    } while (battle_On == 1);
}

void scenarioA1(){
    Sleep(2000);
    cout << "\n\nYou continue down the corridor, and go up the stairs.";
    Sleep(2000);
    cout << "\n\nYou find yourself in a big area, four bridges intersecting into the center. At the center lies... the elevator!";
    Sleep(3000);
    cout << "\n\nThat must be the way out!";
    Sleep(2000);
    cout << "\n\nBut then, three of those things are blocking the way!";
    Sleep(2000);
    cout<< "\n\nOne of them seems weak, and is holding a metal pipe. You only have one ammo left. What will you do?\n1. Risk it and fight the things.\n2. Run back to where you found the man.";
    enemy_name = "Dead(?) Body - Weak";
    Enemy_currentHP = 25;
    Enemy_maxHP = 100;
    cin >> dialogue_choice;
    if (dialogue_choice == "1"){
        cout << "\n\nYou decide to fight the weak one first!";
        PlaySound(TEXT("Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);
        battle_start_animation();
        battle_start();

    }

}


void scenarioA(){
    Sleep(3000);
    cout << "\n\nYou were ready, with the pistol in hand. Fortunately for you, you had training for these types of weapons. You don't know how or why, but muscle memory just works.";
    Sleep(5000);
    cout << "\n\nYou decide to check the magazine, and repulse upon peering at it. You have three bullets. What's that gonna do in this situation!?";
    Sleep(5000);
    cout << "\n\nYou sigh, and load the magazine back into the gun. Whatever's out there, it's better that you're ready for it.";
    Sleep(5000);
    cout << "\n\nSuddenly, the body starts moving. It seems to be... alive? But it's dead! There's no way!";
    Sleep(3000);
    cout << "\n\nYou try to call out to the body, but it doesn't answer. All that escapes from its mouth is...";
    Sleep(2000);
    PlaySound(TEXT("zombie_groan_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    enemy_name = "Dead(?) Body";
    Enemy_currentHP = 50;
    Enemy_maxHP = 50;
    Enemy_damage = 20;
    PlaySound(TEXT("Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1200);
    intro();
    battle_start_animation();
    battle_start();

    Sleep(3000);
    cout << "\n\nThe shooting seems to have attracted a lot of whatever that body was. You don't have much ammo left.";
    //zombies sound
    PlaySound(TEXT("Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\nYou decide to book it and run deeper into the corridors.";
    Sleep(3000);
    cout << "\n\nYou run down the corridor, and you see more lights the deeper you go. It seems like you're going somewhere safer. You slow down.";
    Sleep(3000);
    cout << "\n\nA voice calls out to you. You turn to the left to look, and you see a person.";
    Sleep(2000);
    cout << "\n\n\"Hey. You a patient too?\" the man asks.";
    Sleep(2000);
    do{
    flag_choice = 0;
    cout << "\n\nYou say:";
    Sleep(500);
    cout << "\n1. A patient? What do you mean?\n2. What is this place?\n3. What are you doing here?\n4. --> What are we gonna do?" << endl;
    cin >> dialogue_choice;
    
    if (dialogue_choice  == "1"){
        Sleep(2000);
        cout << "\n\nThe man widens his eyes, and answers, \"Lost your memories, huh?\"";
        Sleep(2000);
        cout << "\n\n\"That's alright. That means you forgot everything that happened here.\"";
    }
    else if (dialogue_choice == "2"){
        Sleep(2000);
        cout << "\n\n\"To put it simply, it's an underground facility.\" The man answers.";
        Sleep(2000);
        cout << "\n\n\"Tell you what. You help me get out of this place, and I'll help you too.\" He says, his eyes calm and composed.";
    }
    else if (dialogue_choice == "3"){
        Sleep(2000);
        cout << "\n\n\"Like I said, I'm stuck here, same as you.\" He says, shrugging.";
        Sleep(2000);
        cout << "\n\n\"Help me, and I help you.\"";
    }
    else if (dialogue_choice == "4"){
        Sleep(2000);
        cout << "\n\n\"We're going to escape, that's what. You gonna help me or not?\"";
        flag_choice = 1;
    }
    else{
        cout << "\n\nTry again.";
        flag_choice = 0;

    }
    }while(dialogue_choice == "1" || dialogue_choice == "2" || dialogue_choice == "3" || flag_choice == 0);
    
    Sleep(2000);
    cout << "\n\nYou say:\n1. --> I don't know who you are. No deal.\n2. --> Let's go." << endl;
    cin >> dialogue_choice;
    
    if (dialogue_choice == "1"){
        Sleep(2000);
        cout << "\n\n\"Your loss.\" The man says, before moving out of sight. Seems he has his own business to take care of.";
        scenarioA1();
    }
    else if (dialogue_choice == "2"){
        Sleep(2000);
        cout << "\n\n\"That's the spirit.\" The man says, before walking to the direction you found him in.";

    }

    
}

void scenarioB(){
    Sleep(3000);
    cout << "\n\nSuddenly, you hear banging on the window deeper into the corridor. You rush to the window, trying to see what it is that's causing it."; 
    Sleep(2000);
    cout << "\n\nBefore you could even arrive, the glass breaks, letting a shadow inside. It seemed slow, yet it looks like a humanoid figure. You couldn't make out what it is due to how dark it is.";
    Sleep(3000);
    cout << "\n\nAnd then... it makes a churning sound.";
    Sleep(2000);
    PlaySound(TEXT("zombie_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(2000);
    enemy_name = "Dark Humanoid Shadow";
    Enemy_currentHP = 30;
    Enemy_maxHP = 30;
    Enemy_damage = 10;
    cout << "\n\nThere's no way out from where you came from! You have to fight whatever that is!" << endl;
    Sleep(1500);
    intro();
    battle_start_animation();
    battle_start();
    PlaySound(TEXT("Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    }




int main(){
    
    do{

    system("CLS");

    Player_currentHP = 100;
    Player_maxHP = 100;
    Player_currentULT = 0;
    Player_maxULT = 100;
    HPbar_width = 20;
    handgun_flag = 0;
    bat_flag = 0;


    PlaySound(TEXT("Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    cout << "You wake up in a small room surrounded by white walls, a bright lightbulb hanging from above.";
    Sleep(2000);
    cout << "\n\nYou assess yourself, and find yourself wearing a hospital gown. You sit up straight from the bed, and look around you.";
    
    do {

    cout << "\n\nYou then remember your name: ";
    cin >> player_name;
    cout << "\nIs " << player_name << " your name? [Y/n]: ";
    cin >> choice_name_confirm;

    if (choice_name_confirm == "y" || choice_name_confirm == "Y"){
        cout << "\nYou remember your name. It's " << player_name << ".";
        flag_confirm_name = 1;
    }

    else if (choice_name_confirm == "n" || choice_name_confirm == "N"){
        cout << "\nWhat is your name?";
    }

    else {
        cout << "Wrong input. Try again.";
        flag_confirm_name = 0;
    }

    }while (choice_name_confirm == "n"  || choice_name_confirm == "N" || flag_confirm_name == 0);

    Sleep(2000);
    cout << "\n\nThe door leading out of the room seems to be open. A piece of paper is on the dresser next to your bed. What could be out there, and why are you here?";
    Sleep(4000);
    cout << "\n\n(*A story choice with a preceding \"-->\" will advance the story.)";
    cout << "\n\nYou decide to:";
    Sleep(1000);

    do{
    cout << "\n1. Read the piece of paper.\n2. --> Get out of the room.\n3. Peek out." << endl;
    cin >> choice_story;
    Sleep(1500);

    if (choice_story == "1"){
        cout << "\nYou pick up the piece of paper and read it. It's just scribbles. You flip it the other way, and now it reads, in full big letters, \"RUN FOR YOUR LIFE\"" << endl;        
        }

    else if (choice_story == "2"){
        cout << "\nYou leave the room. There was nothing else to do anyway. Outside, it is really dark. You see a long corridor full of many rooms like yours. There's blood spilled everywhere, and the smell is horrendous. The blood seems dry, like it has been there for a while. Something tells you that something is wrong with this place." << endl;
        flag_choice = 1;
    }
    else if (choice_story == "3"){
        cout << "\nYou peek out. It is really dark. You see a corridor full of many rooms like yours. Not to mention, the smell is rancid. Something tells you that something is wrong with this place." << endl;
    }

    else {
        flag_choice = 0;
        cout << "\nTry again.\n";
    }

    }while (choice_story == "1" || choice_story == "3" || flag_choice == 0);

    Sleep(4000);
    cout << "\nYou look around the corridors once more. It's really quiet. In one room, you see a body, lying on its belly, limp on the floor. A pool of dry blood seems to have oozed from the body.";
    Sleep(5000);
    cout << "\n\nYou decide to:";
    Sleep(1000);


    
    do{
    cout << "\n1. --> Investigate the body.\n2. --> Continue walking through the corridor.\n";
    cin >> choice_story_2;
    Sleep(2000);
    flag_choice = 0;
    if (choice_story_2  == "1"){
        cout << "\nThe body seems... dead. It was obvious, with the way it's lying down on its belly. Its gender is almost impossible to speculate, as its hair is long, but its body build, masculine.";
        Sleep(5000);
        cout << "\n\nYour eyes catch a glimpse of the body's hand. It's a handgun. You grab it immediately, and instinctively back away. Whatever caused all of this must be dangerous.";
        handgun_flag = 1;
        handgun_ammo = 3;
        flag_choice = 1;
        scenarioA();
    }

    else if (choice_story_2 == "2"){
        cout << "\nWhatever's in that room, it's too big of a risk to get. It's like you felt that something was going to happen the moment you set foot in that room.";
        Sleep(2000);
        cout << "\n\nYou continue deeper into the corridor. You find a bat, lying on the ground. You decide to take it. Feels sturdy enough.";
        bat_flag = 1;
        flag_choice = 1;
        scenarioB();
    }

    else {
        cout << "\nTry again.\n";
    }
    }while (flag_choice == 0);



    }while (choice_again == "Y" || choice_again == "y");

    

return 0;

}