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



class Enemy {
private:
    string name;
    int currentHP;
    int maxHP;
    int damage;

public:
    Enemy(const string& enemyName, int currentHP, int maxtHP, int enemyDamage)
        : name(enemyName), currentHP(currentHP), maxHP(maxHP), damage(enemyDamage) {}

    string getName() const {
        return name;
    }

    int getCurrentHP() const {
        return currentHP;
    }

    int getMaxHP() const {
        return maxHP;
    }

    int getDamage() const {
        return damage;
    }

    void takeDamage(int amount) {
        currentHP -= amount;
    }
};




class Player {
    private:
        string name;
        int currentHP;
        int maxHP;
        int currentULT;
        int maxULT;
        int damage;
    
    public:
        Player(const string& playerName, int maxHealth, int maxUltimate)
            : name(playerName), currentHP(maxHealth), maxHP(maxHealth),
            currentULT(0), maxULT(maxUltimate), damage(0) {}

        string getName() const {
            return name;
        }

        int getCurrentHP() const {
            return currentHP;
        }

        int getMaxHP() const {
            return maxHP;
        }

        int getCurrentULT() const {
            return currentULT;
        }

        int getMaxULT() const {
            return maxULT;
        }

        int getDamage() const {
            return damage;
        }

        void setName(const string& playerName) {
            name = playerName;
        }

        void setMaxHP(int newMaxHP) { 
            maxHP = newMaxHP; 
        }

        void setDamage(int newDamage) {
            damage = newDamage;
        }

        void Ultimate(Enemy &enemy){
            int ultimateDamage = 50;
            cout << "\n\n" << getName() << " uses their ultimate!";
            PlaySound(TEXT("Ult_Handgun.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            Sleep(9100);
            cout << "\n\n" << getName() << " deals " << ultimateDamage << " of damage to " << enemy.getName() << "!";
            PlaySound(TEXT("Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            Sleep(2000);
        }

        void takeDamage(int amount) {
            currentHP -= amount;
        }
};


string choice_story;
string choice_story_2;
string choice_name_confirm;
string choice_battle;
string choice_again;
string dialogue_choice;



int HPbar_width;

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


void battle_start(Player& player, Enemy& enemy) {
    int battle_On = 1;

    PlaySound(TEXT("Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    do {
        do {
            string playerHPBar = Generate_Player_HP_bar(player.getCurrentHP(), player.getMaxHP(), HPbar_width);
            string playerULTBar = Generate_Player_ULT_bar(player.getCurrentULT(), player.getMaxULT(), HPbar_width);
            cout << "\n" << player.getName() << " readies their weapon!";
            cout << "\n" << player.getName() << " HP: " << playerHPBar << " " << player.getCurrentHP() << "/" << player.getMaxHP();
            cout << "\n" << player.getName() << " ULT Bar: " << playerULTBar << " " << player.getCurrentULT() << "/" << player.getMaxULT();

            string enemyHPBar = Generate_Enemy_HP_bar(enemy.getCurrentHP(), enemy.getMaxHP(), HPbar_width);
            cout << "\n\n" << enemy.getName() << " is preparing to attack!";
            cout << "\n" << enemy.getName() << " HP: " << enemyHPBar << " " << enemy.getCurrentHP() << "/" << enemy.getMaxHP();

            flag_choice = 0;
            cout << "\n\nWhat do you want to do?";
            cout << "\n1. Attack\n2. Use an item\n3. Use Ultimate" << endl;
            cin >> choice_battle;

            if (choice_battle == "1" && handgun_flag == 1) {
                if (handgun_ammo > 0) {
                    cout << "\n" << player.getName() << " shoots the gun, and deals " << Player_damage << " damage to " << enemy.getName() << "!";
                    player.setDamage(player.getDamage());
                    player.Ultimate(enemy);
                    handgun_ammo--;
                    flag_choice = 1;
                } 
                
                else {
                    cout << "\n\nYou have no handgun ammo left!";
                }

            } 
            
            else if (choice_battle == "1" && bat_flag == 1) {

                cout << "\n" << player.getName() << " swings the bat, and deals " << Player_damage << " damage to " << enemy.getName() << "!";
                flag_choice = 1;
            } 

            else if (choice_battle == "2") {
                // Implement item usage logic
            } 

            else if (choice_battle == "3" && player.getCurrentULT() == player.getMaxULT()) {
                player.Ultimate(enemy);
                flag_choice = 1;
            } 

            else if (choice_battle == "3" && player.getCurrentULT() != player.getMaxULT()) {
                cout << player.getName() << " tries to use their Ultimate, but failed! The Ultimate Bar has to be full!";
            } 

            else if (choice_battle == "9") {
                player.Ultimate(enemy);
                flag_choice = 1;
            } 
            
            else {
                cout << "\nInvalid choice. You take damage.";
                flag_choice = 1;
            }

        } while (flag_choice == 0);

        enemy.takeDamage(Player_damage);

        if (enemy.getCurrentHP() > 0) {
            cout << "\n\n" << enemy.getName() << " attacks! You take " << enemy.getDamage() << " damage!";
            player.takeDamage(enemy.getDamage());
        }

        if (enemy.getCurrentHP() <= 0) {
           battle_On = 0;
            PlaySound(TEXT("You Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou killed " << enemy.getName() << "!";
            player.setMaxHP(player.getMaxHP() + 10);
            cout << "\n\nYour Max HP is increased by 10!";
            Sleep(5000);
        }

        if (player.getCurrentHP() <= 0) {
            battle_On = 0;
            PlaySound(TEXT("You Died.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\n" << player.getName() << " died!";
            cout << "\nWould you like to try again? [Y/n]: ";
            do {
                cin >> choice_again;
                if (choice_again == "Y" || choice_again == "y") {
                    flag_choice = 1;
                    break;
                } 
                
                else if (choice_again == "N" || choice_again == "n") {
                    cout << "Thank you for playing Too Alive to Die!";
                    return;
                } 
                
                else {
                    cout << "Invalid input. Try again.";
                    flag_choice = 0;
                }

            } while (flag_choice == 0);
        }

    } while (battle_On == 1);
}

void scenarioA2(Player &player){

    cout << "\n\n\"Great. Come with me.\"";
    cout << "\n\nThe man leads you to the direction he came from. Now that you take a good look at him, he doesn't seem to be a patient. He is wearing casual civilian clothes; a vest and pants. What is he planning to do here?";
    cout <<  "He leads you through many halls, many of which are clear of the things you saw. He's walking really fast. He goes down a set of stairs, leading you along.";
    cout << "\n\n\"Got any questions? That look on your face says a lot. You trusted me, so I'll answer your questions.\"";
    do {
    cout << "You say:\n1. What are we doing, exactly?\n2. Why are you helping me?\n3. --> What's the rush?";
    cin >> dialogue_choice;
    flag_choice = 0;

        if (dialogue_choice == "1"){
            cout << "\n\n\"We're getting the virus. The only sample of the virus left.\"";
            cout  << "\n\n\"And yes. The things you saw, the things that are roaming this place, they're infected. They're not who they were anymore.\"";
        }

        else if (dialogue_choice == "2"){
            cout << "\n\n\"Let's just say it's to feel good about myself. Let's leave it at that.\"";
        }

        else if (dialogue_choice == "3"){
            cout << "\n\n\"We need to get to the lab as soon as possible.\" Santiago keeps striding.";
            cout << "\n\n\"This place is going to blow up.\"";
            flag_choice = 1;
        }

        else {
            cout << "Try again.";
            flag_choice = 0;
        }

    }while (flag_choice == 0);

    cout << "\n\nThe facility is going to blow up? What does he mean by that?";
    cout << "\n\n\"Someone rigged this place to blow. We have 30 minutes. We better hustle, or we go poof.\"";
    cout << "\n\nHe stops, and looks at you.\"Name's Santiago. What's your name, muchacho?\"";
    cout << "\n\nYou tell him your name. The stairs go way down, only separated by levels. Throughout the trip, you see levels E1 to F5. It seems like a long way down.";
    cout << "\n\n\"\"" << player.getName() << ", huh? I'll remember that.\" He nodded to himself, and continues walking.";
    cout << "\n\nAs you're both going down the stairs for what seemed an eternity, Santiago stops you.";
    cout << "\n\n\"Shh. Two of them. You see them?\"";
    cout  << "\n\nSantiago was right. Two of the infected are blocking the way down. They seem... more deformed, their muscles and tendons showing rather than skin.";
    cout << "\n\n\"Hunters. They react to sound.\"";
    cout << "\n\nSantiago throws a rock through the open door in level F6. As expected, the Hunters quickly pursued the rock into the door.";
    cout << "\n\nSantiago then ushers you to follow him, going down the stairs once more. You follow suit";
    cout << "\n\nThen, you accidentally step on a  piece of meat.";
    cout << "\n\nThe Hunters hear it, and immediately shriek.";
    cout << "\n\n\"Damn it! Hearing's sharper than  my ex's tongue! Let's give 'em hell!\"";

    Enemy enemy ("Hunter", 200, 200, 40);
    battle_start_animation();
    battle_start(player, enemy);

    cout << "\n\n\"We managed to live through that. You alright?\"";
    do {
        cout << "\n\nYou say:\n1. I'm alright. Barely a scratch.\n2. I almost died.";
        cin >> dialogue_choice;

        if (dialogue_choice == "1"){
            cout << "\n\n\"Good. If you can talk like that, then you're fine.\" He continues going down the stairs. \"We're not much far now. The labs are close. Need to take any bathroom breaks?\"";
        }

        else if (dialogue_choice == "2"){
            cout << "\n\n\"Good.\" He continues going down the stairs. \"We're not much far now. The labs are close. Need to take any bathroom breaks?\"";
        }

        else {
            cout << "\n\nTry again.";
        }

    } while (flag_choice == 0);

    cout << "\n\nJust as he says that, the stairs stop at level F10. This time, the door is closed. It has a scanner for keycards.";
    cout << "\n\nSantiago punches the card to the scanner, and the door automatically opens, revealing yet another long hallway inside.";
    cout << "\n\nYou both head inside. It's dimly lit, with green lightsticks and broken fluorescent light tubes littered around the place.";
    cout << "\n\nThe place was thrashed around.";
    cout << "\n\nYou both go through a series of doors, keeping quiet to not attract infected.";
    cout << "\n\nAs you're following Santiago, you see an open room. You look closely, and see a chainsaw inside!";
       //add scene
    cout << "\n\n\"This is it.\" Santiago says, stopping at an entrance of a door. \" Plenty of infected through this door. There's no turning back. You still in?\"";
    
    do {
        cout << "\n\nYou say/do:\n1. --> You think? I'm ready for this.\n2. --> *Kick the door open.*";
        flag_choice = 0;
        cin >> dialogue_choice;
        if (dialogue_choice == "1"){
            cout << "\n\n\"Then let's do this.\" Santiago nods, before opening the door slowly. Unfortunately, the door bumped into an infected, making it shriek, and alerting all six in the room.";
            cout << "\n\n\"The hell!?\"";
            //add enemy
            battle_start_animation();
            battle_start(player, enemy);
        }

        else if (dialogue_choice == "2"){
            cout << "\n\n\"What the hell are you doing!?\" Santiago exclaims, the door flinging an infected blocking it as its head gets cut off.";
            cout << "\n\nThe sound alerts the five infected in the room. \"So much for being quiet!\"";
            //add enemy
            battle_start_animation();
            battle_start(player, enemy);
        }

        else{
            cout << "Try again.";
        }
    } while (flag_choice == 0);
}


void scenarioA1(Player &player){
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
    
    Enemy enemy ("Dead(?) Body - Weak", 35, 100, 20);

    cin >> dialogue_choice;
    if (dialogue_choice == "1"){
        cout << "\n\nYou decide to fight the weak one first!";
        PlaySound(TEXT("Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);
        battle_start_animation();
        battle_start(player, enemy);

    }

}


void scenarioA(Player& player){
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

    Enemy enemy ("Dead(?) Body", 50, 50, 20);

    PlaySound(TEXT("Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(1200);
    intro();
    battle_start_animation();
    battle_start(player, enemy);

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
        scenarioA1(player);
    }
    else if (dialogue_choice == "2"){
        Sleep(2000);
        cout << "\n\n\"That's the spirit.\" The man says, before walking to the direction you found him in.";

    }

    
}

void scenarioB(Player& player){
    Sleep(3000);
    cout << "\n\nSuddenly, you hear banging on the window deeper into the corridor. You rush to the window, trying to see what it is that's causing it."; 
    Sleep(2000);
    cout << "\n\nBefore you could even arrive, the glass breaks, letting a shadow inside. It seemed slow, yet it looks like a humanoid figure. You couldn't make out what it is due to how dark it is.";
    Sleep(3000);
    cout << "\n\nAnd then... it makes a churning sound.";
    Sleep(2000);
    PlaySound(TEXT("zombie_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(2000);

    Enemy enemy ("Dark Humanoid Shadow", 30, 30, 10);

    cout << "\n\nThere's no way out from where you came from! You have to fight whatever that is!" << endl;
    Sleep(1500);
    intro();
    battle_start_animation();
    battle_start(player, enemy);
    PlaySound(TEXT("Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);

    }




int main(){
    
    do{

    system("CLS");

    string playerName;
    HPbar_width = 20;
    handgun_flag = 0;
    bat_flag = 0;


    PlaySound(TEXT("Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Player player("Unnamed Patient", 100, 0);

    cout << "You wake up in a small room surrounded by white walls, a bright lightbulb hanging from above.";
    Sleep(2000);
    cout << "\n\nYou assess yourself, and find yourself wearing a hospital gown. You sit up straight from the bed, and look around you.";
    
    do {

    cout << "\n\nYou then remember your name: ";
    cin >> playerName;
    player.setName(playerName);
    cout << "\nIs " << player.getName() << " your name? [Y/n]: ";
    cin >> choice_name_confirm;

    if (choice_name_confirm == "y" || choice_name_confirm == "Y"){
        cout << "\nYou remember your name. It's " << player.getName() << ".";
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
        scenarioA(player);
    }

    else if (choice_story_2 == "2"){
        cout << "\nWhatever's in that room, it's too big of a risk to get. It's like you felt that something was going to happen the moment you set foot in that room.";
        Sleep(2000);
        cout << "\n\nYou continue deeper into the corridor. You find a bat, lying on the ground. You decide to take it. Feels sturdy enough.";
        bat_flag = 1;
        flag_choice = 1;
        scenarioB(player);
    }

    else {
        cout << "\nTry again.\n";
    }
    }while (flag_choice == 0);



    }while (choice_again == "Y" || choice_again == "y");

    

return 0;

}