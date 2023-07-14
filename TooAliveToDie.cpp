#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include <ctime>
#include <stack>
#include <chrono>

#pragma comment(lib,"winmm.lib")

using namespace std;

const int maxWeapons = 12;
string collectedWeapons [maxWeapons];
int numcollectedWeapons = 0;

const int maxConsumables = 3;


struct Consumable {
    string name;
    int quantity;
};

string choice_confirm;
string choice_again;
string dialogue_choice;

string track;

int HPbar_width;
int turns;

int Abundance;
int Perceiver;
int Gunslinger;

int give_times;
int handgun_ammo;
int AR15_ammo;
int MP5_ammo;
int shotgun_ammo;
int red9_ammo;
int sniper_ammo;
int grenadeLauncher_ammo;

int flag_confirm_name;
int flag_choice;
int Santiago_flag;
int Rena1_flag;
int Rena2_flag;
int JACK1_flag;
int JACK2_flag;
int Piper_flag;
int death_flag;
int flag_friends;
int handgun_upgrade;

int Gamma_flag;
int Mastermind_flag;

struct Dialogue_Node{
    string choice;
    Dialogue_Node* previous;
    Dialogue_Node* next;
};

class Dialogue_List{
    private:
        Dialogue_Node* head;
        Dialogue_Node* tail;
    public:
        Dialogue_List(){
            head = NULL;
            tail = NULL;
        }

    void addDialogueChoice (const string& choice){
        Dialogue_Node* newNode = new Dialogue_Node;
        newNode->choice = choice;
        newNode->previous = NULL;
        newNode->next = NULL;

        if (head == NULL){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
    }
    
    void Display_Choices() {
        Dialogue_Node* current =head;
        cout << "\n\nChoices made throughout:\n\n";
        while(current != NULL){
            cout << current->choice << endl;
            current = current->next;
        }
    }
};



void battle_start_animation(){
    system("CLS");

    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Battle - Transition.wav"), NULL, SND_FILENAME | SND_ASYNC);    
    }                                                                                                                
    cout << "    //   ) )     // | |  /__  ___/  /__  ___/     / /        //   / /" << endl;
    Sleep(50);
    cout << "   //___/ /     //__| |    / /        / /        / /        //____" << endl; 
    Sleep(50);
    cout << "  / __  (      / ___  |   / /        / /        / /        / ____" << endl;    
    Sleep(50); 
    cout << " //    ) )    //    | |  / /        / /        / /        //" << endl; 
    Sleep(50);         
    cout << "//____/ /    //     | | / /        / /        / /____/ / //____/ /" << endl;    
    Sleep(900);
    system("CLS");

}

void color(const string& text, int color){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    cout << text << endl;
    SetConsoleTextAttribute(hConsole, 7);
}

void intro()
{
    system("CLS");
    PlaySound(TEXT("Sound Effects/Intro.wav"), NULL, SND_FILENAME | SND_ASYNC);
    color("\t#### ##   ## ##    ## ##              ##     ####       ####   ### ###  ### ###           #### ##   ## ##            ### ##     ####   ### ###  ", 10);
    Sleep(50);
    color("\t# ## ##  ##   ##  ##   ##              ##     ##         ##     ##  ##   ##  ##           # ## ##  ##   ##            ##  ##     ##     ##  ##  ", 10);
    Sleep(50);
    color("\t  ##     ##   ##  ##   ##            ## ##    ##         ##     ##  ##   ##                 ##     ##   ##            ##  ##     ##     ##      ", 10);
    Sleep(50);
    color("\t  ##     ##   ##  ##   ##            ##  ##   ##         ##     ##  ##   ## ##              ##     ##   ##            ##  ##     ##     ## ##   ", 10);
    Sleep(50);
    color("\t  ##     ##   ##  ##   ##            ## ###   ##         ##     ### ##   ##                 ##     ##   ##            ##  ##     ##     ##      ", 10);
    Sleep(50);
    color("\t  ##     ##   ##  ##   ##            ##  ##   ##  ##     ##      ###     ##  ##             ##     ##   ##            ##  ##     ##     ##  ##  ", 10);
    Sleep(50);
    color("\t ####     ## ##    ## ##            ###  ##  ### ###    ####      ##    ### ###            ####     ## ##            ### ##     ####   ### ###  ", 10);
    Sleep(4500);
}


void win(){
    PlaySound(TEXT("Music/Drive - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    system("CLS");
    color ("\t\t\t##  ##    ## ##   ##  ###            ## ##   ##  ###  ### ##   ### ###  ### ##            #### ##  ###  ##  ### ###  ", 9);
    Sleep(50);
    color ("\t\t\t##  ##   ##   ##  ##   ##           ##   ##  ##   ##   ##  ##   ##  ##   ##  ##           # ## ##   ##  ##   ##  ##  ", 9);
    Sleep(50);
    color ("\t\t\t##  ##   ##   ##  ##   ##           ##       ##   ##   ##  ##   ##       ##  ##             ##      ##  ##   ##      ", 9);
    Sleep(50);
    color ("\t\t\t ## ##   ##   ##  ##   ##           ##       ##   ##   ## ##    ## ##    ##  ##             ##      ## ###   ## ##   ", 9);
    Sleep(50);
    color ("\t\t\t  ##     ##   ##  ##   ##           ##       ##   ##   ## ##    ##       ##  ##             ##      ##  ##   ##      ", 9);
    Sleep(50);
    color ("\t\t\t  ##     ##   ##  ##   ##           ##   ##  ##   ##   ##  ##   ##  ##   ##  ##             ##      ##  ##   ##  ##  ", 9);
    Sleep(50);
    color ("\t\t\t  ##      ## ##    ## ##             ## ##    ## ##   #### ##  ### ###  ### ##             ####    ###  ##  ### ###  ", 9);
    Sleep(50);
    cout << endl;
    Sleep(50);
    color ("\t### ##    ## ##   ##   ##  ### ##     ####   ### ###             ####   ###  ##  ### ###  ### ###   ## ##   #### ##    ####    ## ##   ###  ##  ", 9);
    Sleep(50);
    color ("\t##  ##   ##   ##   ## ##    ##  ##     ##     ##  ##              ##      ## ##   ##  ##   ##  ##  ##   ##  # ## ##     ##    ##   ##    ## ##  ", 9);
    Sleep(50);
    color ("\t   ##    ##   ##  # ### #   ##  ##     ##     ##                  ##     # ## #   ##       ##      ##         ##        ##    ##   ##   # ## #  ", 9);
    Sleep(50);
    color ("\t  ##     ##   ##  ## # ##   ## ##      ##     ## ##               ##     ## ##    ## ##    ## ##   ##         ##        ##    ##   ##   ## ##   ", 9);
    Sleep(50);
    color ("\t ##      ##   ##  ##   ##   ##  ##     ##     ##                  ##     ##  ##   ##       ##      ##         ##        ##    ##   ##   ##  ##  ", 9);
    Sleep(50);
    color ("\t##  ##   ##   ##  ##   ##   ##  ##     ##     ##  ##              ##     ##  ##   ##       ##  ##  ##   ##    ##        ##    ##   ##   ##  ##  ", 9);
    Sleep(50);
    color ("\t# ####    ## ##   ##   ##  ### ##     ####   ### ###             ####   ###  ##  ####     ### ###   ## ##    ####      ####    ## ##   ###  ##  ", 9);
    Sleep(6000);
}


void lose(){
    system("CLS");
    PlaySound(TEXT("Music/You Died.wav"), NULL, SND_FILENAME | SND_ASYNC);

    color ("                    .........                                                             ", 12);
    Sleep(50);
    color ("                    ======+++.                       .-==++++++++=-:                      ", 12);
    Sleep(50);
    color ("                    ---===+++.                    :=++==+++++++++++++=:                   ", 12);
    Sleep(50);
    color ("                    ---===+++.                  :================+++++++-.                ", 12);
    Sleep(50);
    color ("                    ----==+++.                .===================++++++++-               ", 12);
    Sleep(50);
    color ("                    ----==+++.               :-----------==========++++++++=              ", 12);
    Sleep(50);
    color ("          :-------------===++==========     .:.--------------======+==++++++-              ", 12);
    Sleep(50);
    color ("          :-------------=======+++++++=     - :-----------------==+====++++++.              ", 12);
    Sleep(50);
    color ("          :--------------========+++++=    :. -----===-----===---+++====+++++-               ", 12);
    Sleep(50);
    color ("          :------------==-=+=====+++++=    : .-----##=%#---=@+---#@+%%==+++++=              ", 12);
    Sleep(50);
    color ("          :-------------=-=====+++++++=    : :-----##-%#---=@+---#@=#@==+++++=             ", 12);
    Sleep(50);
    color ("          :-------------====++======+==    : ------%#+%+---=@+---#@**===+++++=            ", 12);
    Sleep(50);
    color ("                    ----==+++.             :.------%#-%#---=@+---#@=====+++++=            ##    ##  #######  ##     ##    ########  #### ######## ######## ", 12);
    Sleep(50);
    color ("                    -----==++.             :.------#*-*#-*=+#+=#-*#+=+#++++++=             ##  ##  ##     ## ##     ##    ##     ##  ##  ##       ##     ## ", 12);
    Sleep(50);
    color ("                    -----=+++.             ::---------------=----======++++++=              ####   ##     ## ##     ##    ##     ##  ##  ##       ##     ## ", 12);
    Sleep(50);
    color ("                    -----=+++.             ::--------------=----======+++++++=               ##    ##     ## ##     ##    ##     ##  ##  ######   ##     ##  ", 12);
    Sleep(50);
    color ("                    -----=+++.             :-----------=--==---======++++++++=               ##    ##     ## ##     ##    ##     ##  ##  ##       ##     ## ", 12);
    Sleep(50);
    color ("                    -----=+++.             :--------=-=---=---======+++++++++=               ##    ##     ## ##     ##    ##     ##  ##  ##       ##     ## ", 12);
    Sleep(50);
    color ("                    ----==+++.             :-------=----=--=======+++++++++++=               ##     #######   #######     ########  #### ######## ######## ", 12);
    Sleep(50);
    color ("                    ----==+++.           . :-=-----=----=-======+++++++++++++=            ", 12);
    Sleep(50);
    color ("               .=-  =-===++++.::          =+--+-+-==--=+==++==+++++++++++++++=.--         ", 12);
    Sleep(50);
    color ("                 ++:+=++++++++=           .++=+++=+++++++++++++++++++++++++++++:          ", 12);
    Sleep(50);
    color ("              ...-+++++++++++===:      :-=-+-===+==+=-==++++++=======+---====+===-.       ", 12);
    Sleep(50);
    color ("             .::-=--==+==+==+=+-:.        --=++======--=++==+:---=-=====-=-=-==+=         ", 12);
    Sleep(50);
    color ("                :--=++====+--==+:         .---=+-===----=++-=--==+=====++--==:-:.         ", 12);
    Sleep(50);
    color ("                 :--==--=--===-:           .:-=-:-=::--=--=+=--==+===--===..              ", 12);
    Sleep(50);
    color ("                    . .::....                            ..    ..    ....                 ", 12);
    Sleep(4500);

}

void Butcher(){
    cout << "                               .=+:               " << endl;
    Sleep(100);
    cout << "                             -*@@@%               " << endl;
    Sleep(100);
    cout << "                          :*@@@@%*.               " << endl;
    Sleep(100);
    cout << "                       .+@@@@%*:                  " << endl;
    Sleep(100);
    cout << "                   ..=%@@@%*-                     " << endl;
    Sleep(100);
    cout << "                .=%#*%@@%-                        " << endl;
    Sleep(100);
    cout << "              -#@##@#**.    :+**=.                " << endl;
    Sleep(100);
    cout << "           :-=@@@@%%@#+    *@#+++*+               " << endl;
    Sleep(100);
    cout << "           ###@@@@#==+=:. .%@#*+==#.              " << endl;
    Sleep(100);
    cout << "            +@@@*   =*#+- =@%##===:               " << endl;
    Sleep(100);
    cout << "            .@@=.     .%+=.#@#+==-                " << endl;
    Sleep(100);
    cout << "            :@#        :#*++###+=-.               " << endl;
    Sleep(100);
    cout << "            *@#:::.::--+@@%*+==*+---:             " << endl;
    Sleep(100);
    cout << "            *%##%*#%@@@%@%%@#+--%:---.            " << endl;
    Sleep(100);
    cout << "            .**#%%%@@@@@##@@@@#%%+++-             " << endl;
    Sleep(100);
    cout << "                ::. .%@@@@@@@@@%#+--:             " << endl;
    Sleep(100);
    cout << "                    :@@@@@@@#*+==++*:             " << endl;
    Sleep(100);
    cout << "                    *@@@@@%%*--=-=+=              " << endl;
    Sleep(100);
    cout << "                   *@@@@@%%#%=--:--.              " << endl;
    Sleep(100);
    cout << "                  -@@@@@%####*----=               " << endl;
    Sleep(100);
    cout << "                 .@@@@@@%###***+*+:               " << endl;
    Sleep(100);
    cout << "                :@@@@@@@@%##*+*++                 " << endl;
    Sleep(100);
    cout << "               -@@@@@@@@@%%##**##.                " << endl;
    Sleep(100);
    cout << "              =@@@@@@@@@%%%##****-                " << endl;
    Sleep(100);
    cout << "             =@@@@@@@@@@%%%####**+                " << endl;
    Sleep(100);
    cout << "            -@@@@@@@@@@@%%###%%***                " << endl;
    Sleep(100);
    cout << "            %@@@@@@@@@@%%####@@#**                " << endl;
    Sleep(100);
    cout << "            .+@@@@@@@@%%####%@@%*#.               " << endl;
    Sleep(100);
    cout << "              .#@@@@@%%####-:@@@%#+               " << endl;
    Sleep(100);
    cout << "               #@@@@@%###*=  +@@@%#=              " << endl;
    Sleep(100);
    cout << "               *@@@@+ .:-=   :@@@@%#              " << endl;
    Sleep(100);
    cout << "              .%@@@@=         =@@@%%.             " << endl;
    Sleep(100);
    cout << "              .%@@@+           #@@@%=             " << endl;
    Sleep(100);
    cout << "            .+@@@@*            -@@@%#             " << endl;
    Sleep(100);
    cout << "          :#@@@%==             .%@@@#             " << endl;
    Sleep(100);
    cout << "           ::..                 .@@%*             " << endl;
    Sleep(100);
    cout << "                                .@@%#             " << endl;
    Sleep(100);
    cout << "                                *@@@%             " << endl;
    Sleep(100);
}


void Titan(){
    cout << "\t\t\t\t               :=.     .:-==-.::                       " << endl;
    Sleep(100);
    cout << "\t\t\t\t           .=-=++****--==***#%%:                       " << endl;
    Sleep(100);;
    cout << "\t\t\t\t           *@*#++++++******##%#*=-.                    " << endl;
    Sleep(100);
    cout << "\t\t\t\t          :###%****####*=*-=+*#*%*+*=-=-:              " << endl;
    Sleep(100);
    cout << "\t\t\t\t          +#*%#%%%%%+*%**#=:##*****##*==+=.            " << endl;
    Sleep(100);
    cout << "\t\t\t\t         .=##%##%%%%##%#+=*####+=-=+##+=---:           " << endl;
    Sleep(100);
    cout << "\t\t\t\t       :=*%*#%##%#%#%%%*#*#**###+=+=##*=--=*           " << endl;
    Sleep(100);
    cout << "\t\t\t\t    .+**+#@*##%%#%%#%@%**+**+**+=++++##-==**:          " << endl;
    Sleep(100);
    cout << "\t\t\t\t   :##**%%%@@%#@%%%#%#*+++****#+==+##%*=-=#--          " << endl;
    Sleep(100);
    cout << "\t\t\t\t  +####%%%%%%%**%%#%#*****###**####%+##**++*+:.        " << endl;
    Sleep(100);
    cout << "\t\t\t\t *%%%#*###%#-.  -#%%##%%%%%%#####%*.  *#**=#%**=.      " << endl;
    Sleep(100);
    cout << "\t\t\t\t=%@%##%#+#*      -%@@%%######%%#:      *%%%#*++*+:     " << endl;
    Sleep(100);
    cout << "\t\t\t\t+@%*%#%%*:-    : *%%@@%%%%%%****       .##*+=+#+++     " << endl;
    Sleep(100);
    cout << "\t\t\t\t-%- :.--=    .+#*#%%%%%%%@%%*=+=:       :**++#*+=      " << endl;
    Sleep(100);
    cout << "\t\t\t\t =.         -**##*##%##*#%%%#++===.     -##*****+.     " << endl;
    Sleep(100);
    cout << "\t\t\t\t           =##*****+#%%#%%%%####**+     +%%###*##=     " << endl;
    Sleep(100);
    cout << "\t\t\t\t          :#%##*###***+-:+%%%%##*=+=.   .#%%%#*%#-     " << endl;
    Sleep(100);
    cout << "\t\t\t\t        :+#%%%**####=     *%%%#*+=+#**:  =%%%@%*=      " << endl;
    Sleep(100);
    cout << "\t\t\t\t       *%%%%@%####*.       -#%%#*+#*=+%*: :...-+.      " << endl;
    Sleep(100);
    cout << "\t\t\t\t       +%##%#%%%##-         .#%%%%*+--*#+              " << endl;
    Sleep(100);
    cout << "\t\t\t\t       -%%%@%%%%%#*          -%%##**+++++:             " << endl;
    Sleep(100);
    cout << "\t\t\t\t       :%%%%##%%%#=          :%%%%##*++++=             " << endl;
    Sleep(100);
    cout << "\t\t\t\t       +%%%##%%%%#.           =%%%#**+==++-            " << endl;
    Sleep(100);
    cout << "\t\t\t\t      -%%%%%%%%%%#             -#%%#***+*++-           " << endl;
    Sleep(100);
    cout << "\t\t\t\t    .=**%%%#%%%%%-              -%##*+*++*++=          " << endl;
    Sleep(100);
    cout << "\t\t\t\t   .*####**#%#***.              :#%%%###*#***.         " << endl;
    Sleep(100);
    cout << "\t\t\t\t    :--+=:---:..                 *%#*%#++++=+:         " << endl;
    Sleep(100);
    cout << "\t\t\t\t                                 =*#+##+#+#+*+         " << endl;
    Sleep(100);
}

void Gamma(){
    Sleep(100);
    cout << "                                  .:::.                               " << endl;
    Sleep(100);
    cout << "                              .+*+*#%%*.                              " << endl;
    Sleep(100);
    cout << "                              +%%@%@@%%+                              " << endl;
    Sleep(100);
    cout << "                              #%%%%%%%%#-..                           " << endl;
    Sleep(100);
    cout << "                            :=%%%%#####*+=.                           " << endl;
    Sleep(100);
    cout << "                            :-+#######%#*+                            " << endl;
    Sleep(100);
    cout << "                              -####*###*+*                            " << endl;
    Sleep(100);
    cout << "                             .####***##**%*=.                         " << endl;
    Sleep(100);
    cout << "                            :*#%*******#%%#**.                        " << endl;
    Sleep(100);
    cout << "                     ::..:-+#*#%%##*##%%@@#++++:=+++-:                " << endl;
    Sleep(100);
    cout << "                 :=++*++++***#%@@@@@@@@@%*+++**+++++**+-.             " << endl;
    Sleep(100);
    cout << "               :*%%%#**++++**###%%%%#*+++++++++*+*%#####*=.           " << endl;
    Sleep(100);;
    cout << "              -#%#%%##*+##*#*#********+*+++***##%%%###%%%%%=          " << endl;
    Sleep(100);
    cout << "             :%%#%%%*####**#*###****+***#######%%%####%%%%%#+         " << endl;
     Sleep(100);
    cout << "            .#%##%%*###*#*##**#######%***#*###%#**##**%@@%%*#+.       " << endl;
    Sleep(100);
    cout << "            *%%#%%##*###**###%######****#####*****#**#@%###*##+       " << endl;
    Sleep(100);
    cout << "           :#%%%%%%%%%%%####%##**###**##%%%%%%%@@%%%%%%%#%###%#-      " << endl;
     Sleep(100);
    cout << "           :#%%%%%%%%%%%%%#%##########%%%%%%%@@@@@@@@@@%%%%%%%+       " << endl;
     Sleep(100);
    cout << "           -%@@@@@#%%%%%%%%%#######@%%%%%@@%@@@@%@@@@@@@%%%%%%#       " << endl;
     Sleep(100);
    cout << "           =%@@@@@%%@@@%%%%##%####%%%%%%%%%@@@@%%@@@%%@%%%%%%%%.      " << endl;
     Sleep(100);
    cout << "          .#%@@@@@@%%%%%%%%%%%%%%%%%%%@%@@@@@@%%@%@@=:%@%@%%%%%-      " << endl;
    Sleep(100);
    cout << "         -##%@@@@@@%%%%%%%%%%%%%%%%%%%%%%%@@@%@@@@@#   *@%##***#:     " << endl;
    Sleep(100);
    cout << "        .#%##%@@@@@*%%%%%%%%%%%%%%@%%%%%%%@%@@@@@@#.    +%%#**#%*     " << endl;
    Sleep(100);
    cout << "       -#%##%%%%@@+.%%%%%%@@%%%@%%@@%@%%%%%@@@@@%#       +%%##%%%-    " << endl;
    Sleep(100);
    cout << "      .#%%%%%%@%@*  #%%%%@%@@%@@%%@%@%%%@@%%@@@@#        *%%####%#    " << endl;
     Sleep(100);
    cout << "     .*%###%%@@@%.  +%@%%%%%%%%@%@@@%#%@@@@%@@@@:        -%%%*##%@:   " << endl;
     Sleep(100);
    cout << "     -%%%%%@@@%+:   -%@%@@%%%######%%%@%@@@@@@@#          *%%##%@%:   " << endl;
     Sleep(100);
    cout << "     ####%%%@%-     =%@@@%%%%%%%%##**%%%%@@@@@@#:         #%%##%#%-   " << endl;
     Sleep(100);
    cout << "    .####%@@#       +%%%%%%%%%####%%#%%%%%@@%%#*.         *%#*###%%*  " << endl;
     Sleep(100);
    cout << "    +%##%%%*:       #%%%%%%%%%%###%%#%@%%#%%%%%#.         :%#*#%%%:.. " << endl;
     Sleep(100);
    cout << "    #%##%%#        -#%#%#%%%%%%###%%%####%%%%%%#-         +%##%%%%:   " << endl;
     Sleep(100);
    cout << "    #%#%%+.        *%%#%@%%%%%%##%%%%%%%%%%%%%%%*         -###%%@+.   " << endl;
     Sleep(100);
    cout << "   .%%###*        .%%%%%@%%%%%%%#%%%%%%%##%%%%%%%-        +####%%:    " << endl;
     Sleep(100);
    cout << "   +%##%@@=       -%%%%@@%%%%%%%%%%%%%%####%%%%%%#       =%%%*#@%=    " << endl;
     Sleep(100);
    cout << "   -**%%*=        +%%%%@@%%%%%%%%%%%%%%%%#%%%%%%%%-      =@==#%@@+    " << endl;
    Sleep(100);
    cout << "                 .#%%%%@@%%%%%%%%%%%%%%%%%%%@@%%%%#       -*:%%%*     " << endl;
    Sleep(100);
    cout << "                 +%%%%%@@%%%%%%%%%%%%%%%%%%@%@@@%#%.        -@@#      " << endl;
    Sleep(100);
    cout << "                .%%%%%%@@%%%%%%%%%%%%%%%%%@@@@@@@#%=        .:-       " << endl;
    Sleep(100);
    cout << "                -%%%%%@@%%%%%%%%%%%%%%%%%%%@@@@@@%%#                  " << endl;
    Sleep(100);
    cout << "                *%@%%%@@%%%%%%%%%%%%%%%%@%%@@@@@@%#%.                 " << endl;
    Sleep(100);
    cout << "                #@%%%@@%%%%%%%%%%%%%%%%%@%%@@%%@@%#%-                 " << endl;
     Sleep(100);
    cout << "                %@%%%@@%%@%%%%%%%%%%%%%%%%%@@%%%%%#%*                 " << endl;
     Sleep(100);
    cout << "               .%@%%%@%%@@%%%%%%@@%%%%%@@@@@%%%%%%##%:                " << endl;
    Sleep(100);
    cout << "               :%%%%%%%@@@%%%%%%%@%%%%@@@@@@@%%%%%%#%#                " << endl;
     Sleep(100);
    cout << "               =%%%%%%@@@@%%%%%%%@%%%%@@@@@@@@@%%@@%#%+               " << endl;
     Sleep(100);
    cout << "               +%#%%@%@@@@%%%%%%%@@%%%@@@@@@@@@@%@@@%#%.              " << endl;
    Sleep(100);
    cout << "               ##%%%@%@@@@%@@%%%%@@%%%%@@@%@@@@%@@@@@%%=              " << endl;
    Sleep(100);
    cout << "              :#%%%%@%@@@@%@%%%%%@@%%%%@@@%%@@@@@@@@@@%#              " << endl;
     Sleep(100);
    cout << "              +%%%%@@%@@@@%@@@@%%%@%%%@@@@%%@@@@@@@@@@@%+             " << endl;
    Sleep(100);
    cout << "             .##%@%@@%@@@@@%@@@%%%@@%%@@@%%@%@%%%@@@@@@@%:            " << endl;
    Sleep(100);
    cout << "             =#%%@%%@%@@@@@%@%@%%%@@@@@@%@@@@%%%%@@@%@@@@+            " << endl;
    Sleep(100);
    cout << "             ##%%%%%%%@@@@@%%%%%%%%@@@@@%%%%%%%%%%%%%%@@@%.           " << endl;
    Sleep(100);
    cout << "            :###%%%%%@@@@@@%%%%%%%@@@@@%%%%%%%%%%%@@@@@@@@*           " << endl;
     Sleep(100);
    cout << "            -###%%%%@@@@@@@%%%%%%%%@@%%%%%%%%%%%%@@@@@%@%@%:          " << endl;
    Sleep(100);
    cout << "            =##%%%%%%@@@@@%%######%%%%%%%%%%%%%%@@@@@@%%%#*:          " << endl;
    Sleep(100);
    cout << "              :%@@@@@@@@@@+++++++++=========++*@@@@@@@@@@-            " << endl;
     Sleep(100);
    cout << "              -%@@@@@@@@@*                     =@@@@@@@@@*:           " << endl;
     Sleep(100);
    cout << "              #@%%@@@@@@@:                      *@@@@@@@@%#           " << endl;
    Sleep(100);
    cout << "              +@@@@@@@@@*                       =@@@@@@@@%=           " << endl;
    Sleep(100);
    cout << "             :%%%%@@@@@%                         +@@@@@@%%+:          " << endl;
     Sleep(100);
    cout << "             =@%%%@@@@@#                         +%@%%%@@@%*          " << endl;
     Sleep(100);
    cout << "              #@%%%@@@@-                         .+@@@@@@@@:          " << endl;
     Sleep(100);
    cout << "             -%%%%%@@%*                            =%%%%%%%*          " << endl;
     Sleep(100);
    cout << "             +##*%@@@%:                             #%###%%+          " << endl;
     Sleep(100);
    cout << "           .+#**#%@@@@:                             *###***.          " << endl;
     Sleep(100);
    cout << "         .*####%%@%@@%:                             ##*++++=          " << endl;
    Sleep(100);
    cout << "         +%%%%@@@%***+.                            :%%#%%%%#:         " << endl;
     Sleep(100);
    cout << "          ......                                   .=======-.         " << endl;
    Sleep(3000);

}

void Gamma2(){
    cout << "                                     -***+-                           " << endl;
    Sleep(100);
    cout << "                                    -%%#**##                          " << endl;
    Sleep(100);
    cout << "                                   .+%%*##%%:                         " << endl;
    Sleep(100);
    cout << "                                   .%@%*%#%@*                         " << endl;
    Sleep(100);
    cout << "                                   =%@@@@@@%:                         " << endl;
    Sleep(100);
    cout << "                               .:-=#@@@@@@@@+--:                      " << endl;
    Sleep(100);
    cout << "                          .****##%%%%%%%@%%%##***+-.                  " << endl;
    Sleep(100);
    cout << "                       :=*%@@%%%%%%%%%%%%%%%%%#***##**+-.             " << endl;
    Sleep(100);
    cout << "                      +#%##%#####%%%@%%@%%%%%%##***+++**#=            " << endl;
    Sleep(100);
    cout << "                    .##@@%#%%%%%+#*++*#%%###%#*******+*+*#*           " << endl;
    Sleep(100);
    cout << "                  .=%@%%%@%@@@@#+##*+#%@%#%#*#***#***##***%-          " << endl;
    Sleep(100);
    cout << "                 +%%%%%@@@@%%#%###=*+%@%%%%#*+***#%%%#*###%#:         " << endl;
    Sleep(100);
    cout << "                .*@%%@%%%%%#%***##**#%#%####*##%@@@%+****###*         " << endl;
    Sleep(100);
    cout << "                  *@%%%%%%@%%####%%%###*+**#####%@@%=+*++*#%%         " << endl;
    Sleep(100);
    cout << "                 =%@@@@@@@%@%**###%%##*****###%%@@@%+=+****%@*        " << endl;
    Sleep(100);
    cout << "               .*%%@@%@@@@@%@*%%*%%%%####*##%##%%@@%*.+*#%@@@%.       " << endl;
    Sleep(100);
    cout << "             .+%%%%@%@%@@@@%**%%###%%#*#####%#*%%@@-   +@@%%@@.       " << endl;
    Sleep(100);
    cout << "          :+#%%@%%%%@@%@@%= :%%##%%%%#***####*###%=   +%%#%@@@:       " << endl;
    Sleep(100);
    cout << "         -*@#%@%%@@%@@@@*   +#%%#%%%%%%****#*=+*#%*= .##%#*%@@.       " << endl;
    Sleep(100);
    cout << "          =%@@%%%@@@@@@%   -%@@@@%@%%%%##***++#%@@@%  =#%###@=        " << endl;
    Sleep(100);
    cout << "           =%%%%@@@@@@@-  .#@@@@@@@@%@@@@@@%%%%@@@@@- .%@@@@+         " << endl;
    Sleep(100);
    cout << "          :#%%@%%%@%+%:   *%@%@@%@@%@@%%@@%%@@@@@@@@: :@@@@@*         " << endl;
    Sleep(100);
    cout << "        :*%%@@%@%%@@+     *%%@%%%**#@@%%%%@@%@@@@@@@*-@@@@@+          " << endl;
    Sleep(100);
    cout << "       =%%@@%%@%@%@=     :%@@@@@%*##@@%###@@@@@@@@@@##@@@@@#          " << endl;
    Sleep(100);
    cout << "     .#@@%@@@@@@%@@:     *%%%@@@@@@@@@@%##%@@@@@@@@@@-+*%%#=          " << endl;
    Sleep(100);
    cout << "    .%@%@@@@@@@@@#-      =#%@@@@@@@@@@%@@%%###*@@@@@@-                " << endl;
    Sleep(100);
    cout << "    :%%+%@@@@@@@+        -%@@@@@@@@@@@%%@@%%##%@@@@@%.                " << endl;
    Sleep(100);
    cout << "    :%%#@@@@@@%%%.       =%%@@@@@@@@@@@%%@@@@@%@@@@@@*                " << endl;
    Sleep(100);
    cout << "    .%@%%@@@@@@@@*       +#%%%@@@@@@@@@%%%@@@@@@@@@@@%*               " << endl;
    Sleep(100);
    cout << "    :%@%%@@@@@@@@-       +%%@@@@@@@@@@@%%%%@@@@@@@@@@*#=              " << endl;
    Sleep(100);
    cout << "    =@@@%@%@@@@@@.       :%%@@@@@@@@@@%%%@#%@@@@@@@@@*#*              " << endl;
    Sleep(100);
    cout << "    *#%@@@@%@@@@:        .%#%@@@@@@@@#%%#@@#%@@@@@@@@%%+              " << endl;
    Sleep(100);
    cout << "    +*#+.=%%@@@@.         # *%@@@@@@%###%@@@%@@@@@@@@@#               " << endl;
    Sleep(100);
    cout << "   .+##  .*+*%%-            -#@@@@@@@%#**#%@@%@@@@@@@%.               " << endl;
    Sleep(100);
    cout << "    =+*  :=+%**=            :#@@@@@@@%@@@@#%@%@@@@@@@#                " << endl;
    Sleep(100);
    cout << "    .-=+ :-+#--*            +@@@@@@@@#@%%%#%@@%@@@@@@*                " << endl;
    Sleep(100);
    cout << "      .-=:-=#.:*-           *@@@@@@@@=-#@%#@@@@@@@@@@%                " << endl;
    Sleep(100);
    cout << "         ::-#  +:           *@@@@@@@@-  .=#@@@@@@@@@@@:               " << endl;
    Sleep(100);
    cout << "          .-+:              +@@@@@@@+     :%@@%@@@@@@@*               " << endl;
    Sleep(100);
    cout << "           .:=              +@@@@@@%.      #@@@@@%@@@@*               " << endl;
    Sleep(100);
    cout << "             ..             *@%@@@@+       :%@@@@%#*#*.               " << endl;
    Sleep(100);
    cout << "                            #@@@@@@-       :%@@@@*@-                  " << endl;
    Sleep(100);
    cout << "                           +%@@@@@@:        +@@@@%+                   " << endl;
    Sleep(100);
    cout << "                        .=%@@@@@@@@.        +@@@@%*                   " << endl;
    Sleep(100);
    cout << "                     .*%@@@@@@@@@@@.        =@@@@@%.                  " << endl;
    Sleep(100);
    cout << "                     *@%@@@@@@**#*+         =%@@@@@-                  " << endl;
    Sleep(100);
    cout << "                     .==++==:               +%%%%@@#                  " << endl;
    Sleep(100);
    cout << "                                            -####*+:                  " << endl;
    Sleep(3000);
}

void Mastermind(){
    cout << "                                   .-+***++-:.                                               " << endl;
    Sleep(100);
    cout << "                                 :--+***#*%%%%=                                            " << endl;
    Sleep(100);
    cout << "                                -==+*#%%%%%%%%#+                                           " << endl;
    Sleep(100);
    cout << "                               .-+#%%%@@@@@@@@%*.                                          " << endl;
    Sleep(100);
    cout << "                               .-+#==+*%%%@@@%%*.                                          " << endl;
    Sleep(100);
    cout << "                               .-*#=+++**#%%%#%+                                           " << endl;
    Sleep(100);
    cout << "                               :=*+=++**##%%%*#=                                           " << endl;
    Sleep(100);
    cout << "                               .+==#%@@%%%@%***:                                           " << endl;
    Sleep(100);
    cout << "                                :*:+##***%%%#*-                          :=+*+=:           " << endl;
    Sleep(100);
    cout << "                            .:+%@#-*****##%###%*=.                 :: .=#@%==+##*-         " << endl;
    Sleep(100);
    cout << "                            .*#%@%#+*#*#%%##%@@@@%*=:            :##-+@@@%#=-##+%+.        " << endl;
    Sleep(100);
    cout << "                          .:+###%@@%##*%%%%%@@@@%@%@%#+.        :%#=#%%%@@%%%@+            " << endl;
    Sleep(100);
    cout << "                       .-*#%%%%@%%@@@%%%%%@@@@@@@%%@%+.        :%%@@%@%*#@#%%-             " << endl;
    Sleep(100);
    cout << "                  .:=+#%%%@@@@%@@#%@@@@@%%@@@@@@@@%%+-.       .@@*@@@%%#-*%*-              " << endl;
    Sleep(100);
    cout << "                .=###**##%%%@@@@%*#%@@@@@%@@@@@@%%@#*++=:     +@@@@@@@@@@%*.               " << endl;
    Sleep(100);
    cout << "               -=#%##%%*+*##%@@@@*#%%%%%@@%%@@@@@@@@@%*=+*-.  -@@@@@@=%@=.                 " << endl;
    Sleep(100);
    cout << "              :-=#%%%%%@%**#%%@@@@##%##%#%%##%%@@@@@@%*#%#**= -@@@@@@@@@##*%%%*+-          " << endl;
    Sleep(100);
    cout << "             .-+#%%%%%@@@@###%%%@@@#%%####%##**#@@@@@%*#%%%@#=.#@@@@@@@@%%@%@@#@%#-        " << endl;
    Sleep(100);
    cout << "             -+##%%%%%@@@@%####%%@@@#%%**##%##**%@@@@%###%%@%*- .*@@#%@%#%%@%@%@@@%        " << endl;
    Sleep(100);
    cout << "           .-+##%%%%%@@@@@@%%%%%#%@@%#%%###%####%@@@@%#%%@%%%%*   *%@@@%#%@@%%#%@@@#:      " << endl;
    Sleep(100);
    cout << "           =#+*%@%%%@@@@@@@@@%###%%%@#%%%%%%%#%%%@@@@@%@%%%%%#*-    :: %%%@@@#*@@@@%#.     " << endl;
    Sleep(100);
    cout << "          :=*+#@%@%@@@@@@@@@%%##%%%%@@#%@@@@@%@@@@@@@@%@@%@@%%#:      :%@%@@@%=*@%%%#:     " << endl;
    Sleep(100);
    cout << "        - ==+*@@%@@@@@@@@@@@@%%#%@%%@@%%@@@@@@@@@@@@@%%%%%#%%%#+.    .%@@@@@%*@@@@@%=      " << endl;
    Sleep(100);
    cout << "        %*=*#*%@@@@@@@@@@@@@@@%%@@%%@@@#@@@@@%@@@@@@@%%%%%#%@%%#-    +@@@@@@%#@@@%=:       " << endl;
    Sleep(100);
    cout << "       .%=+###%@@@@@@@@@@@@@@@@@@@#%%@@%@@@%%%%%%%@@@@#%*%%%@%#*+..-*@@@@@@@@#+@@@#@-      " << endl;
    Sleep(100);
    cout << "       .-=##%%%@%@@@@@@@@@@@@@@@@@%%%%@@%%%@%%%%%%@@@@#@####@%%####%@@@@@@@@#=*@%*=.       " << endl;
    Sleep(100);
    cout << "       +=+#%%%@@@@@%%*%@@@@@@@@@@@@@%%%@%@@@@@%@@%@@@@#%@%%%%%@%%%%%@@@@@@%@@@%+.          " << endl;
    Sleep(100);
    cout << "      +%+##%@@@%@@@%: +%@@@@@@@@@@@@%%%@%@@@@@%@@@@@@@%%@@@@@@%@%@@@@@@@@@@@@*.            " << endl;
    Sleep(100);
    cout << "      #*#%%@@@@@%%%#  -#%@@@@@@@@@@@@%%@%@@@@@%@@@@@@@%%@@@@@%#@@@@@@@@%%@@@#.             " << endl;
    Sleep(100);
    cout << "     =%*#%%@@@@%%%#*: .*#%%%%@@@@@@@@%%@@%@@@@@@@@@@@@%%@@%@@%#@@@@@@@@@@@@@%*             " << endl;
    Sleep(100);
    cout << "    -%%*#%%@@@@@@@%#%*=*%%%%@@@@@@@@%%%%@%@@@@@@@@@@@@%%@@%@@%@@@@@@@@@@@@%%#=             " << endl;
    Sleep(100);
    cout << "    .:=*%%%%@@@@@%%%%%%=#%%%@@@@@@@@%%%%@%@@@@@@@@@@@@@%@@%%@@@@@@@%@@%**+:.               " << endl;
    Sleep(100);
    cout << "        -#%@%@@@@@%%@@*=#@%%@@@@@@@@%%%@@%@@@@@@@@@@@@@%@@%%#@@@@@@@#-                     " << endl;
    Sleep(100);
    cout << "          -*@@@@@@@@@@==#%%@@@@@@@@%%%%@@%@@@@@@@@@@@@@%@@%%- =*+=:                        " << endl;
    Sleep(100);
    cout << "            .=#@@@@@@#++#%%@@@@@@@@%%%%%@%@@@@@@@@@@@@@%@@#%+                              " << endl;
    Sleep(100);
    cout << "               :*%@@@+**%%@@%%@@@@@%%%@@@%@@@@@@@@@@@@@%@@#%#                              " << endl;
    Sleep(100);
    cout << "                 :=*#++#%%@@%@@@@@@%%%@@@%@@@@%%%%@@@@@%@@%#%.                             " << endl;
    Sleep(100);
    cout << "                    =+*#%@@%%@@@@@@@%%@@@%@@@@@@@@@@@@@@%@%#%:                             " << endl;
    Sleep(100);
    cout << "                   :+*#%%@@%%@@@@@@@%@@%@%@@@@@@@@@@@@@@%@%#@=                             " << endl;
    Sleep(100);
    cout << "                   =*##%@@%%%@@@@@@@@@@@%%@@@@@@@@@@@@@@%@@%@*                             " << endl;
    Sleep(100);
    cout << "                  .+*#%@@@%%@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@%@#                             " << endl;
    Sleep(100);
    cout << "                  =*##@@@%%%@@@@@@@@%@@@%@@@@@@@@@@@@@@@@%@%@%:                            " << endl;
    Sleep(100);
    cout << "                 .+*#%@@@%%%@@@@@@@@%@@@%@@@%@@%%%@@@@@@@@@%@@+                            " << endl;
    Sleep(100);
    cout << "                 -*#@%@@%%%%@@@@@@@%%@@@%@@@@@@%@@@@@@@@@@@%@@#                            " << endl;
    Sleep(100);
    cout << "                 +*%@@@@%%%%@@@@@@@%@@@@%@@@@@@@@@@@@@@@@@@%@@%-                           " << endl;
    Sleep(100);
    cout << "                :*#@%@@%%%%@@@@@@@@%@@@@@@@@@@@@@%%@@@@@@@@@@@@*                           " << endl;
    Sleep(100);
    cout << "                =*%@@@%%%%@@@@@@@@@%@@@@@@@@@@@@@@@@@@@@@@@@@@@#.                          " << endl;
    Sleep(100);
    cout << "               .*#%%@%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%-                          " << endl;
    Sleep(100);
    cout << "               +#%@@%%%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@%+                          " << endl;
    Sleep(100);
    cout << "              -#%%@@%%%%%%@@@@@@@@@@@@@%@@@@@@@@@@@@@@@@@@%@%@@%#                          " << endl;
    Sleep(100);
    cout << "              #%%%@@@%%%%%@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@@%%%@@@#.                         " << endl;
    Sleep(100);
    cout << "             +%%%@@%@%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@%-                         " << endl;
    Sleep(100);
    cout << "             #%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%@@@@%+                         " << endl;
    Sleep(100);
    cout << "            =%%%@@%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%%@@%#                         " << endl;
    Sleep(100);
    cout << "            #%%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%%@@@@%                         " << endl;
    Sleep(100);
    cout << "           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@-                        " << endl;
    Sleep(3000);
}


class Enemy {
private:
    string name;
    int currentHP;
    int maxHP;
    int damage;

public:
    Enemy(const string& enemyName, int currentHP, int maxHP, int enemyDamage)
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
        string Class;
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
        
        string getClass() const {
            return Class;
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

        void setClass(const string &ClassName){
            Class = ClassName;
        }

        void heal(int amount){
            currentHP += amount;
            if (currentHP > maxHP){
                currentHP = maxHP;
            }
        }

        void setcritwithDamage(int newDamage, int critChance) {
            damage = newDamage;
            int randomValue = rand() % 100 + 1;

            if (getClass() == "Perceiver" && randomValue <= critChance){
                damage *= 3;
                cout << "\nCritical Hit! Damage is tripled!";
            }

            else if (randomValue <= critChance){
                damage *= 2;
                cout << "\nCritical Hit! Damage is doubled!";
            }
        }

        void setDamage(int newDamage){
            damage = newDamage;
            if (getClass() == "Gunslinger" && getDamage() > 0){
                damage += 15;
            }

        }

        void Ultimate(Enemy &enemy){
            cout << "\n\n" << getName() << " uses their Ultimate!";
            if (getClass() == "Gunslinger"){
                setDamage(100);
                PlaySound(TEXT("Sound Effects/Ultimate_Gunslinger.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cout << "\n\n" <<  getName() << " materializes an M4A1 from their body, and unleashes its power for a short while!";
                Sleep(9100);
                cout << "\n\n" << getName() << " deals " << getDamage() << " of damage to " << enemy.getName() << "!";
                cout << "\n\n" <<  getName() << " gets 10 of every ammo!";
                handgun_ammo += 10;
                AR15_ammo += 10;
                MP5_ammo += 10;
                shotgun_ammo += 10;
                red9_ammo += 10;
                sniper_ammo += 10;
                
            }

            else if  (getClass() == "Perceiver"){
                setDamage(200);
                PlaySound(TEXT("Sound Effects/Ultimate_Perceiver.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cout << "\n\n" <<  getName() << "'s hand burns in flames, and in one punch, it releases all the energy inside!";
                Sleep(12100);
                cout << "\n\n" << getName() << " deals " << getDamage() << " of damage to " << enemy.getName() << "!";
            }

            else {
                PlaySound(TEXT("Sound Effects/Ultimate_Abundance.wav"), NULL, SND_FILENAME | SND_ASYNC);
                cout << "\n\n" <<  getName() << " releases all the energy inide them, and fils their HP to max!";
                Sleep(8100);
                cout << "\n\nFull HP healed!";
                currentHP = maxHP;
            }

            currentULT = 0;
            if (track == "DreadFearful"){
                PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else if (track == "ShootingRange"){
                PlaySound(TEXT("Music/Battle - Shooting Range.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
            else if (track == "Fearful"){
                PlaySound(TEXT("Music/Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else{
                PlaySound(TEXT("Music/Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            Sleep(2000);
        }

        void takeDamage(int amount) {
            currentHP -= amount;
        }

        void chargeULT(int amount){
            currentULT += amount;
            if (currentULT > 100){
                currentULT = 100;
            }
        }
};

void addWeapon(string collectedWeapons[], string weapon){
    collectedWeapons[numcollectedWeapons] = weapon;
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\n" << weapon << " is added to your inventory!";
    Sleep(3000);
    numcollectedWeapons++;
}

void checkAmmo(){
    cout << "\n\nHandgun Ammo: " << handgun_ammo;
    cout << "\nAR15 Ammo: " << AR15_ammo;
    cout << "\nMP5 Ammo: " << MP5_ammo;
    cout << "\nShotgun Ammo: " << shotgun_ammo; 
    cout << "\nRed9 Ammo: " << red9_ammo;
    cout << "\nSniper Ammo: " << sniper_ammo;
    cout << "\nGrenade Launcher Ammo: " << grenadeLauncher_ammo;

}

void weaponInventory(){
    cout << "Select the weapon to use: " << endl;
    for (int i = 0; i < numcollectedWeapons; i++) {
        cout << "[" << (i + 1) << "]" << ": " << collectedWeapons[i] << endl;
    }
}


string Generate_Player_HP_bar(const Player& player, int HPbar_width) {
    float BarRatio = static_cast<float>(player.getCurrentHP()) / player.getMaxHP();
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string playerHPBar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            playerHPBar += "=";
        } else {
            playerHPBar += " ";
        }
    }
    playerHPBar += "]";

    return playerHPBar;
}

string Generate_Player_ULT_bar(const Player& player, int HPbar_width) {
    float BarRatio = static_cast<float>(player.getCurrentULT()) / player.getMaxULT();
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string playerULTBar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            playerULTBar += "=";
        } else {
            playerULTBar += " ";
        }
    }
    playerULTBar += "]";

    return playerULTBar;
}

string Generate_Enemy_HP_bar(const Enemy& enemy, int HPbar_width) {
    float BarRatio = static_cast<float>(enemy.getCurrentHP()) / enemy.getMaxHP();
    int FillBar = static_cast<int>(BarRatio * HPbar_width);

    string enemyHPBar = "[";
    for (int i = 0; i < HPbar_width; i++) {
        if (i < FillBar) {
            enemyHPBar += "=";
        } else {
            enemyHPBar += " ";
        }
    }
    enemyHPBar += "]";

    return enemyHPBar;
}

void displayConsumables(const Consumable consumables[]){
    for (int i = 0; i < maxConsumables; i++) {
        cout << consumables[i].name << ", Quantity: " << consumables[i].quantity << endl;
    }
}

void battle_start(Player& player, Enemy& enemy, Consumable consumables[], Dialogue_List &choices) {
    int battle_On = 1;
    string choice_battle;

    if(track == "Fearful"){
       PlaySound(TEXT("Music/Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }

    else if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Battle - Shooting Range.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }

    else if (track == "DreadFearful"){
        PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }

    else{
        PlaySound(TEXT("Music/Dread - Battle.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }

    do {
        do {
            system("CLS");
            string playerHPBar = Generate_Player_HP_bar(player, HPbar_width);
            string playerULTBar = Generate_Player_ULT_bar(player, HPbar_width);
            cout << "\n" << player.getName() << " readies their weapon!";
            cout << "\n" << player.getName() << " HP: " << playerHPBar << " " << player.getCurrentHP() << "/" << player.getMaxHP();
            cout << "\n" << player.getName() << " ULT Bar: " << playerULTBar << " " << player.getCurrentULT() << "/" << player.getMaxULT();

            string enemyHPBar = Generate_Enemy_HP_bar(enemy, HPbar_width);
            cout << "\n\n" << enemy.getName() << " is preparing to attack!";
            cout << "\n" << enemy.getName() << " HP: " << enemyHPBar << " " << enemy.getCurrentHP() << "/" << enemy.getMaxHP();

            flag_choice = 0;
            player.setDamage(0);

            cout << "\n\nWhat do you want to do?";
            cout << "\n1. Attack\n2. Use an item\n3. Use Ultimate\n4. Check Ammo" << endl;
            cin >> choice_battle;

            if (choice_battle == "1"){
                int choice_weaponNumber;
                weaponInventory();
                while(!(cin >> choice_weaponNumber)){
                    cin.clear();
                    cout << "\nInvalid input. Try again.\n";
                    while (cin.get() !='\n');
                }
                if (choice_weaponNumber >= 1){
                    int weapon_index = choice_weaponNumber - 1;
                    string choice_weapon = collectedWeapons[weapon_index];

                    if (choice_weapon == "Bat"){
                        player.setcritwithDamage(15, 60);;
                        cout << "\n" << player.getName() << " swings the Bat, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(20);
                        flag_choice = 1;
                    }  
                    else if (choice_weapon == "Knife"){
                        player.setcritwithDamage(30, 40);
                        cout << "\n" << player.getName() << " slices using the Knife, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(30);
                        flag_choice = 1;
                    }
                    else if (choice_weapon == "Metal Pipe"){
                        player.setcritwithDamage(18, 30);
                        cout << "\n" << player.getName() << " bashes using the Metal Pipe, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(22);
                        flag_choice = 1;
                    }
                    else if (choice_weapon == "Katana"){
                        player.setcritwithDamage(33, 40);
                        cout << "\n" << player.getName() << " slices and dices using the Katana, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(33);
                        flag_choice = 1;
                    }
                    else if (choice_weapon == "Crowbar"){
                        player.setcritwithDamage(22, 25);
                        cout << "\n" << player.getName() << " claws through using the Crowbar, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(20);
                        flag_choice = 1;
                    }
                    else if (choice_weapon == "Chainsaw"){
                        player.setcritwithDamage(33, 30);
                        cout << "\n" << player.getName() << " saws through using the Chainsaw, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                        Sleep(3000);
                        player.chargeULT(40);
                        flag_choice = 1;
                    }
                    else if (choice_weapon == "Handgun"){
                        if (handgun_ammo > 0){
                            player.setDamage(25);
                            if (handgun_upgrade == 1){
                                player.setDamage(45);
                            }
                            cout << "\n" << player.getName() << " shoots the Handgun, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(25);
                            handgun_ammo--;
                            flag_choice = 1;
                        }
                        else {
                            cout << "\nYou don't have any Handgun Ammo left!";
                            Sleep(3000);
                        }

                    }
                    else if (choice_weapon == "AR15"){
                        if (AR15_ammo > 0){
                            player.setDamage(40);
                            cout << "\n" << player.getName() << " shoots the AR15, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(40);
                            AR15_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any AR15 Ammo left!";
                            Sleep(3000);
                        }
                    }
                    else if (choice_weapon == "Sniper"){
                        if (sniper_ammo > 0){
                            player.setDamage(70);
                            cout << "\n" << player.getName() << " shoots the Sniper, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(55);
                            sniper_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any Sniper Ammo left!";
                            Sleep(3000);
                        }
                    }
                    else if (choice_weapon == "Shotgun"){
                        if (shotgun_ammo > 0){
                            player.setDamage(50);
                            cout << "\n" << player.getName() << " shoots the Shotgun, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(60);
                            shotgun_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any Shotgun ammo left!";
                            Sleep(3000);
                        }
                    }
                    else if (choice_weapon == "MP5"){
                        if (MP5_ammo > 0){
                            player.setDamage(35);
                            cout << "\n" << player.getName() << " shoots the MP5, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(44);
                            MP5_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any MP5 Ammo left!";
                            Sleep(3000);
                        }
                    }
                    else if (choice_weapon == "Red9"){
                        if (red9_ammo > 0){
                            player.setDamage(46);
                            cout << "\n" << player.getName() << " shoots the Red9, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(34);
                            red9_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any Red9 Ammo left!";
                            Sleep(3000);
                        }
                    }
                    else if (choice_weapon == "Grenade Launcher"){
                        if (grenadeLauncher_ammo > 0){
                            player.setDamage(4250);
                            cout << "\n" << player.getName() << " shoots the Grenade Launcher, and deals " << player.getDamage() << " damage to " << enemy.getName() << "!";
                            Sleep(3000);
                            player.chargeULT(50);
                            grenadeLauncher_ammo--;
                            flag_choice = 1; 
                        }  
                        else {
                            cout << "\nYou don't have any Grenade Launcer Ammo left!";
                            Sleep(3000);
                        }
                    }

                }
                else {
                    cout << "\n\nInvalid choice. Try again.";
                    Sleep(3000);
                }
                
                
            } 

            else if (choice_battle == "2") {
                string choice_consumable;
                cout << "\nChoose from one of the items below: " << endl;
                displayConsumables(consumables);
                cin >> choice_consumable;
            
                if (choice_consumable == "1" && consumables[0].quantity > 0){
                    consumables[0].quantity -= 1;
                    player.heal(10000);
                    cout << "\n" << player.getName() << " used First Aid Kit! They gain full HP! They now have " << player.getCurrentHP() << " HP!"; 
                    Sleep(3000);
                    flag_choice = 1;
                }
                else if (choice_consumable == "2" && consumables[1].quantity > 0){
                    consumables[1].quantity -= 1;
                    player.heal(100);
                    cout << "\n" << player.getName() << " used Bandages! They gain 100 HP! They now have " << player.getCurrentHP() << " HP!"; 
                    Sleep(3000);
                    flag_choice = 1;                
                }  
                else if (choice_consumable == "3" && consumables[2].quantity > 0){
                    consumables[2].quantity -= 1;
                    player.heal(80);
                    cout << "\n" << player.getName() << " used Alcohol! They gain 80 HP! They now have " << player.getCurrentHP() << " HP!";
                    Sleep(3000);
                    flag_choice = 1; 
                } 
                else{
                    cout << "\nYou don't have enough of that item!";
                    Sleep(3000);
                } 

            }


            else if (choice_battle == "3" && player.getCurrentULT() == player.getMaxULT()) {
                player.Ultimate(enemy);
                flag_choice = 1;
            } 

            else if (choice_battle == "3" && player.getCurrentULT() != player.getMaxULT()) {
                cout << player.getName() << " tries to use their Ultimate, but failed! The Ultimate Bar has to be full!";
                Sleep(3000);
            } 

            else if (choice_battle == "4"){
                checkAmmo();
                Sleep(3000);
            }

            else if (choice_battle == "OVER9000") {
                player.Ultimate(enemy);
                flag_choice = 1;
            } 

            
            else if (choice_battle == "KILLYOURSELF") {
                player.takeDamage(player.getMaxHP());
                flag_choice = 1;
            } 

            else if(choice_battle == "HESOYAM"){
                cout << "\n\nYou heal yourself!";
                Sleep(3000);
                player.heal(player.getMaxHP());
                flag_choice = 1;
            }

            else if (choice_battle == "BAGUVIX"){
                cout << "\n\nYou have infinite health!";
                Sleep(3000);
                HPbar_width = 40;
                player.setMaxHP(10000000000);
                player.heal(player.getMaxHP());
                flag_choice = 1;
            }

            else if (choice_battle == "FULLCLIP"){
                cout << "\n\nYou get unlimited ammo!";
                Sleep(3000);
                handgun_ammo += 100000;
                AR15_ammo += 100000;
                MP5_ammo += 100000;
                shotgun_ammo += 100000;
                red9_ammo += 100000;
                sniper_ammo += 100000;
                grenadeLauncher_ammo += 100000;
                flag_choice = 1;    
            }   

            else if (choice_battle == "DROPKICK"){
                player.setcritwithDamage(1000,50);
                cout << "\n\n" << player.getName() << " dropkicks " << enemy.getName() << "! It deals " << player.getDamage() << " damage!";
                Sleep(3000);
                player.chargeULT(40);
                flag_choice = 1;
            }

            else if (choice_battle == "MAG"){
                player.setcritwithDamage(50,50);
                cout << "\n\n" << player.getName() << " shoots the Magnum! It deals " << player.getDamage() << " damage!";
                Sleep(3000);
                player.chargeULT(100);
                flag_choice = 1;
            }
            
            else {
                cout << "\nInvalid choice.";
                Sleep(3000);
            }

        } while (flag_choice == 0);

        enemy.takeDamage(player.getDamage());

        if (Gamma_flag == 1){
            cout << "\n\nWe don't have enough firepower!";
            Sleep(3000);
            turns++; 
            if (turns == 12){
                break;
            }
        }
        if (Mastermind_flag == 1){
            cout << "\n\n\"Puny inferior imbeciles.\"";
            Sleep(3000);
            turns++; 
            if (turns == 8){
                break;
            }
        }

        if (Santiago_flag == 1){
            cout << "\n\nSantiago shoots with his Red9! He deals 35 damage!"; 
            Sleep(3000);
            enemy.takeDamage(35);
            if (handgun_ammo <= 0 && give_times < 3){
                cout << "\n\n\"Out of ammo, huh? Catch!\"";
                Sleep(3000);
                cout << "\n\nSantiago gives you 5 Handgun Ammo!";
                Sleep(3000);
                handgun_ammo = 5;
            }
        }

        if (Rena1_flag == 1){
            cout << "\n\n??? slices with her Knife! She deals 20 damage!";
            Sleep(3000);
            enemy.takeDamage(20);
            if (handgun_ammo <=0 && give_times < 3){
                cout << "\n\n??? gives you 5 Handgun Ammo!";
                Sleep(3000);
                handgun_ammo = 5;
            }
        }

        if (Rena2_flag == 1){
            cout << "\n\nRena slices with her Knife! She deals 20 damage!";
            Sleep(3000);
            enemy.takeDamage(20);
            if (handgun_ammo <= 0 && give_times < 3){
                cout << "\n\nRena gives you 5 Handgun Ammo!";
                Sleep(3000);
                handgun_ammo = 5;
            }
        }

        if (Piper_flag == 1){
            if (turns == 3){
                cout << "\n\nPiper shoots with her Rocket Launcher! She deals 200 damage!";
                Sleep(3000);
                enemy.takeDamage(200);
                turns = 0;
                }
            else {
                cout << "\n\n\"Damn thing is charging! Hold on!\"";
                Sleep(3000);
                turns++;
            }
        }

        if (JACK1_flag == 1){
            cout << "\n\n??? shoots with his Handgun! He deals 25 damage!";
            Sleep(3000);
            enemy.takeDamage(25);
        }

        if (JACK2_flag == 1){
            cout << "\n\nJACK shoots with his Magnum! He deals 50 damage!";
            Sleep(3000);
            enemy.takeDamage(50);
        }

        if (enemy.getCurrentHP() > 0) {
            cout << "\n\n" << enemy.getName() << " attacks! You take " << enemy.getDamage() << " damage!";
            Sleep(3000);
            player.takeDamage(enemy.getDamage());
        }

        if (enemy.getCurrentHP() <= 0) {
            battle_On = 0;
            PlaySound(TEXT("Music/You Win.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou defeated " << enemy.getName() << "!";
            player.setMaxHP(player.getMaxHP() + 20);
            cout << "\n\nYour Max HP is increased by 20!";
            Sleep(3000);
            int randomIndex = std::rand() % maxConsumables;
            consumables[randomIndex].quantity += 2;
            PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou obtained " << "2 " << consumables[randomIndex].name << " after the battle!" << endl;
            Sleep(3000);

        }

        if (player.getCurrentHP() <= 0) {
            battle_On = 0;
            cout << "\n\n" << player.getName() << " died!";
            Sleep(3000);
            lose();
            choices.Display_Choices();
            
            do {
                cout << "\nWould you like to try again? [Y/n]: ";
                cin >> choice_again;
                Sleep(3000);
                if (choice_again == "Y" || choice_again == "y") {
                    flag_choice = 1;
                    death_flag = 1;
                } 
                
                else if (choice_again == "N" || choice_again == "n") {
                    cout << "Thank you for playing Too Alive to Die!";
                    Sleep(4000);
                    death_flag = 1;
                } 
                
                else {
                    cout << "Invalid input. Try again.";
                    flag_choice = 0;
                }

            } while (flag_choice == 0);
        }

    } while (battle_On == 1);
    system("CLS");
}



void scenarioA2(Player &player, Enemy &enemy, Consumable consumables[], Dialogue_List &choices){

    stack <Enemy> A2enemy;
    A2enemy.push(Enemy("The Mastermind", 10000, 10000, 40));
    A2enemy.push(Enemy("The Mastermind", 10000, 10000, 40));
    A2enemy.push(Enemy("Hunter", 300, 300, 30));
    A2enemy.push(Enemy("Hunter", 300, 300, 30));
    A2enemy.push(Enemy("Hunter", 300, 300, 30));
    A2enemy.push(Enemy("Superior Hunter", 500, 500, 40));
    A2enemy.push(Enemy("Screecher", 150, 150, 20));  
    A2enemy.push(Enemy("Hunter", 200, 200, 30)); 
    A2enemy.push(Enemy("Screecher", 150, 150, 20));   
    A2enemy.push(Enemy("Hunters", 400, 400, 15));   
   
    Sleep(2000);
    cout << "\n\n??? now fights by your side!";
    Santiago_flag = 1;
    Sleep(2000);
    cout << "\n\nThe man leads you to the direction he came from. Now that you take a good look at him, he doesn't seem to be a patient. He is wearing casual civilian clothes; a vest and pants. What is he planning to do here?";
    Sleep(2000);
    cout <<  "\n\nHe leads you through many halls, many of which are clear of the things you saw. He's walking really fast. He goes down a set of stairs, leading you along.";
    Sleep(2000);
    cout << "\n\n\"Got any questions? That look on your face says a lot. You trusted me, so I'll answer your questions.\"";
    do {
        Sleep(2000);
        cout << "\n\nYou say:\n1. What are we doing, exactly?\n2. Why are you helping me?\n3. --> What's the rush?\n";
        cin >> dialogue_choice;
        system("CLS");
        flag_choice = 0;

            if (dialogue_choice == "1"){
                Sleep(2000);
                cout << "\n\n\"We're getting the virus. The only sample of the virus left.\"";
                Sleep(2000);
                cout  << "\n\n\"And yes. The things you saw, the things that are roaming this place, they're Infected. They're not who they were anymore.\"";
            }

            else if (dialogue_choice == "2"){
                Sleep(2000);
                cout << "\n\n\"Let's just say it's to feel good about myself. Let's leave it at that.\"";
            }

            else if (dialogue_choice == "3"){
                Sleep(2000);
                cout << "\n\n\"We need to get to the lab as soon as possible.\" The man keeps striding.";
                Sleep(2000);
                cout << "\n\n\"This place is going to blow up.\"";
                flag_choice = 1;
            }

            else {
                cout << "Try again.";
                flag_choice = 0;
            }

    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\nThe facility is going to blow up? What does he mean by that?";
    Sleep(2000);
    cout << "\n\n\"Someone rigged this place to blow. We have 30 minutes. We better hustle, or we go poof.\"";
    Sleep(2000);
    cout << "\n\nHe stops, and looks at you. \"Name's Santiago. What's your name, muchacho?\"";
    Sleep(2000);
    cout << "\n\nYou tell him your name. The stairs go way down, only separated by levels. Throughout the trip, you see levels E1 to F5. It seems like a long way down.";
    Sleep(4000);
    cout << "\n\n\"" << player.getName() << ", huh? I'll remember that.\" He nodded to himself, before walking.";
    Sleep(2000);
    cout << "\n\nAs you're both going down the stairs for what seemed an eternity, Santiago stops you.";
    Sleep(2000);
    cout << "\n\n\"Shh. Two of them. You see them?\"";
    Sleep(2000);
    cout  << "\n\nSantiago was right. Two of the Infected are blocking the way down. They seem... more deformed, their muscles and tendons showing rather than skin.";
    Sleep(4000);
    cout << "\n\n\"Hunters. They react to sound.\"";
    Sleep(2000);
    cout << "\n\nSantiago throws a rock through the open door in level F6. As expected, the Hunters quickly pursued the rock into the door.";
    Sleep(4000);
    cout << "\n\nSantiago then ushers you to follow him, going down the stairs once more. You follow suit.";
    Sleep(2000);
    cout << "\n\nThen, you accidentally step on a piece of meat.";
    Sleep(2000);
    cout << "\n\nThe Hunters hear it, and immediately let out a screech.";
    PlaySound(TEXT("Sound Effects/Hunter_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(4000);
    cout << "\n\n\"Damn it! Their hearing's sharper than my ex's tongue! Let's give 'em hell!\"";
    Sleep(2000);

    Enemy &A2enemy1 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy1, consumables, choices);
    if (death_flag == 1){
        return;
    }
    A2enemy.pop();

    cout << "\n\nAs the Hunters die, they melt, dropping a Crowbar!";
    Sleep(3000);
    addWeapon(collectedWeapons,"Crowbar");

    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 8 Handgun Ammo!";
    handgun_ammo += 8;
    Sleep(3000);

    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\n\"We managed to live through that. You alright?\"";
    do {
        Sleep(2000);
        cout << "\n\nYou say:\n1. I'm alright. Barely a scratch.\n2. I almost died.\n";
        cin >> dialogue_choice;
        system("CLS");

        if (dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\n\"Good. If you can talk like that, then you're fine.\" He continues going down the stairs. \"We're not much far now. The labs are close. Need to take any bathroom breaks?\"";
            Sleep(3000);
        }

        else if (dialogue_choice == "1"){
            Sleep(2000);
            cout << "\n\n\"Good.\" He continues going down the stairs. \"We're not much far now. The labs are close. Need to take any bathroom breaks?\"";
            Sleep(3000);
        }

        else {
            cout << "\n\nTry again.";
        }

    } while (flag_choice == 0);

    cout << "\n\nJust as he says that, the stairs stop at level F10. This time, the door is closed. It has a scanner for keycards.";
    Sleep(4000);
    cout << "\n\nSantiago punches the card to the scanner, and the door automatically opens, revealing yet another long hallway inside.";
    Sleep(4000);
    cout << "\n\nYou both head inside. It's dimly lit, with green lightsticks and broken fluorescent light tubes littered around the place.";
    Sleep(5000);
    cout << "\n\nThe place was thrashed around. It even has a hole on the ceiling. It seems fresh.";
    Sleep(2000);
    cout << "\n\nYou both go through a series of doors, keeping quiet to not attract Infected.";
    Sleep(3000);
    cout << "\n\n\"This is it.\" Santiago says, stopping at an entrance of a door. \" Plenty of Infected through this door. There's no turning back. You still in?\"";
    Sleep(4000);

    do {
        Sleep(2000);
        cout << "\n\nYou say/do:\n1. --> You think? I'm ready for this.\n2. --> *Kick the door open.*\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Waited for Santiago to open the door.");
            Sleep(2000);
            cout << "\n\n\"Then let's do this.\" Santiago nods, before opening the door slowly. Unfortunately, the door bumped into an Infected, making it shriek, and alerting all three in the room.";
            Sleep(5000);
            cout << "\n\n\"The hell!?\"";
            Sleep(2000);
            Enemy &A2enemy2 = A2enemy.top();
            battle_start_animation();
            battle_start(player, A2enemy2, consumables, choices);
                if (death_flag == 1){
                    return;
                }  

            PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou picked up 6 Handgun Ammo!";
            handgun_ammo += 6;
            Sleep(3000);

            PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            cout << "\n\nThat one's a Hunter!";
            Sleep(2000);
            cout << "\n\nGot any ammo left?";
            Sleep(2000);

            A2enemy.pop();
            Enemy &A2enemy3 = A2enemy.top();
            battle_start_animation();
            battle_start(player, A2enemy3, consumables, choices);
                if (death_flag == 1){
                    return;
                }  
            PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou picked up 9 Handgun Ammo!";
            handgun_ammo += 9;
            Sleep(3000);

        }

        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Kicked the door open.");
            Sleep(2000);
            cout << "\n\n\"What the hell are you doing!?\" Santiago exclaims, the door flinging an Infected blocking it as its head gets cut off.";
            Sleep(4500);
            cout << "\n\nThe sound alerts the two other Infected in the room. \"So much for being quiet! Wait! One's a Hunter!\"";
            Sleep(5000);
            PlaySound(TEXT("Hunter_sound.wav"), NULL, SND_FILENAME | SND_ASYNC); 
            A2enemy.pop();
            Enemy &A2enemy3 = A2enemy.top();
            battle_start_animation();
            battle_start(player, A2enemy3, consumables, choices);
            if (death_flag == 1){
                return;
            } 
            PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout << "\n\nYou picked up 8 Handgun Ammo!";
            handgun_ammo += 8;
            Sleep(3000);

        }

        else{
            cout << "Try again.";
        }
    } while (flag_choice == 0);

    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nWe got a Screecher! Shut it up!";
    Sleep(2000);
    cout << "\n\nAs the Screecher was about to screech, Santiago distracts it by shooting it in the face.";
    Sleep(4000);
    cout << "\n\nShut up, pendejo!";
    Sleep(2000);
    cout << "\n\nThe system announces, \"System Meltdown will begin in 15 minutes. Please evacuate.\"";
    Sleep(4000);
    cout << "\n\n\"Let's hustle, muchacho!\"";
    Sleep(2000);
    A2enemy.pop();
    Enemy &A2enemy4 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy4, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 7 Handgun Ammo!";
    handgun_ammo += 7;
    Sleep(3000);

    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"Coast is clear. Sheesh.\"";
    Sleep(2000);
    cout << "\n\nSantiago shakes his head, then searches the lab for something.";
    Sleep(2000);
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. Is this lab where the virus was made?\n2. --> So the sample... It's here?\n";
        cin >> dialogue_choice;
        system("CLS");

        if (dialogue_choice == "1"){
            Sleep(1000);
            cout << "\n\n\"Yup. This is where it all started. Quadrangle developed their virus here.\"";
            Sleep(3000);
            cout << "\n\nHe shakes his head and scoffs, as he keeps searching for something on a desk.";
        }
        else if(dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\n\"It's here, alright.\"";
            Sleep(2000);
            cout << "\n\nHe gets a slip of paper from the desk, and reads it.";
            Sleep(2000);
            cout << "\n\nHe ushers you to follow.";
            flag_choice = 1;
        }
    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\nHe leads you to a safe hidden behind a painting, and inputs numbers from the slip of paper.";
    Sleep(4000);
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. What do you plan on doing with the sample?\n2. How'd you even know about all of this stuff?\n3. --> Wait for him to open the safe.\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(2000);
            cout << "\n\n\"This sample will help us find a cure. There is an Anti-Quadrangle party that I know that has the resources to make a cure.\"";
            Sleep(5000);
            cout << "\n\n\"They just need a sample. Even just a small one.\"";
        }
        else if (dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\nHe sighs.";
            Sleep(3000);
            cout << "\n\n\"Alright. I'll tell you the truth.\"";
            Sleep(3000);
            cout << "\n\n\"I'm a scientist. I used to work for Quadrangle.\"";
            Sleep(3000);
            cout << "\n\nSo that's why he said that it's to make himself feel better.";
            flag_friends = 1;
        }

        else if  (dialogue_choice == "3"){
            Sleep(2000);
            cout << "\n\nHe opens the safe, and as expected, the sample is there, in a test tube.";
            flag_choice = 1;
        }

        else {
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    if (flag_friends == 1){
        Sleep(3000);
        cout << "\n\n\"I'm glad you're still with me, " << player.getName() << ", even after what I said.\"";
        Sleep(3000);
        cout << "\n\n\"Let's get through this together.\"";
        Sleep(3000);
        cout << "\n\nHe fist bumps you.";
        choices.addDialogueChoice("Asked about who Santiago really is.");
    }
    else {
        choices.addDialogueChoice("Did not ask Santiago about his intentions.");
    }

    Sleep(3000);
    cout << "\n\nSantiago grabs the sample, and puts it inside a container. It's a metal case.";
    Sleep(3000);
    cout << "\n\nThe system warns once more, \"System Meltdown will begin in 10 minutes. Please evacuate. Please evacuate.\"";
    Sleep(3000);
    cout << "\n\n\"Let's get the hell out of here.\"";
    Sleep(3000);
    cout << "\n\nSantiago nods at you, and both of you race to the top of the stairs.";
    Sleep(3000);
    cout << "\n\nYou go back through all the routes you took, and arrive at the center of it all.";
    Sleep(3000);
    cout << "\n\nThere are four bridges connecting to the center. You are on one bridge. At the center of it all lies an elevator.";
    Sleep(3500);
    cout << "\n\nThat's our ticket out. I have a keycard. Let's go.";
    Sleep(3000);
    cout << "\n\nBut before you can run any further, a Hunter blocks your path. It growls, seemingly very wary. It looks very different. It has scales instead of muscles and tendons.";
    PlaySound(TEXT("Sound Effects/growl.wav"), NULL, SND_FILENAME | SND_ASYNC); 
    Sleep(3000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    Sleep(3000);
    cout << "\n\n\"We got no time for you, pendejo!\"";
    Sleep(3000);
    cout << "\n\nYou both engage the Hunter!";
    Sleep(3000);

    A2enemy.pop();
    Enemy &A2enemy5 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy5, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nThe Superior Hunter dropped a... It's an upgrade!?";
    Sleep(3000);
    cout << "\n\nHandgun damage is increased by 20!";
    handgun_upgrade = 1;
    Sleep(3000);

    PlaySound(TEXT("Music/Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    track = "Fearful";
    cout << "\n\n\"That Hunter was different! What the hell!?\"";
    Sleep(3000);
    cout << "\n\nHe breathes out.";
    Sleep(3000);
    cout << "\n\n\"It almost infected me!\""; 
    Sleep(3000);
    cout << "\n\nBefore you could move, three more Hunters surround you.";
    Sleep(3000);
    cout << "\n\n\"Don't worry, muchacho, they're the normal kind.\"";
    Sleep(3000);
    cout << "\n\nHe flashes you a smile.";
    Sleep(3000);
    cout << "\n\n\"Let's do this!\"";
    Sleep(3000);

    A2enemy.pop();
    Enemy &A2enemy6 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy6, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 4 Handgun Ammo!";
    handgun_ammo += 4;
    Sleep(3000);

    PlaySound(TEXT("Music/Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"Got one!\"";
    Sleep(3000);
    cout << "\n\nYou fight the next one!";
    Sleep(3000);

    A2enemy.pop();
    Enemy &A2enemy7 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy7, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 3 Handgun Ammo!";
    handgun_ammo += 3;
    Sleep(3000);
        
    PlaySound(TEXT("Music/Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"We got two!\"";
    Sleep(3000);
    cout << "\n\nYou fight the next one!";
    Sleep(3000);


    A2enemy.pop();
    Enemy &A2enemy8 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy8, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 6 Handgun Ammo!";
    handgun_ammo += 6;
    Sleep(3000);
        
    PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"We got three!\"";
    Sleep(3000);
    cout << "\n\n\"System Meltdown in 5 minutes. Please evacuate. Please evacuate.\"";
    Sleep(3000);
    cout << "\n\n\"Just in time, yeah, muchacho?\"";
    Sleep(3000);
    cout << "\n\nYou both were about to reach the elevator door, until...";
    Sleep(3000);
    cout << "\n\nYou both were flung by an unknown force back to the middle of the bridge.";
    Sleep(3000);
    cout << "\n\nYou feel a surge of pain.";
    Sleep(3000);
    cout << "\n\nYou take 30 damage.";
    Sleep(3000);
    player.takeDamage(30);
    cout << "\n\nYou and Santiago struggle to get back up.";
    Sleep(3000);
    cout << "\n\nYou see a figure. A man. He doesn't look like he's Infected.";
    Sleep(3000);
    cout << "\n\n\"Inferior creatures.\" The man says, a black mold sprouting out of his arm.";
    Sleep(3500);
    cout << "\n\n\"You shall be dealt with.\"";
    Sleep(3000);
    cout << "\n\n\"I cannot allow you to cure the Infection.\" The man says, \"Do you not see the power it holds?";
    Sleep(4000);
    cout << "\n\n\"It is the pinnacle of human evolution!\" The man shouts, \"I hired you, Dr. Santiago, to achieve this dream!\"";
    Sleep(4000);
    cout << "\n\n\"And you, patient!\" The man exclaims, \"Weren't you a product of the experiments!? Your new power, is there!\"";
    Sleep(5000);
    cout << "\n\n\"You, " << player.getName() << ", are Patient One! The only successful host after Patient Zero!\""; 
    Sleep(4000);
    cout << "\n\nWhat is he saying? You were the successful patient all this time...? But what about the amnesia?";
    Sleep(4000);
    cout << "\n\n\"You, Patient One!\" The man says, \"You were the key! I was able to achieve power! Until you were set back!\"";
    Sleep(4000);
    cout << "\n\n\"You had all the knowledge, but you lost your control!\"";
    Sleep(3000);
    cout << "\n\n\"You! You started this outbreak!\"";
    Sleep(3000);
    cout << "\n\n\"Wesker's wrong, muchacho. He's pinning the blame on you.\" Santiago said, \"He was the one that lost control of the entire lab. He was reckless.\"";
    Sleep(5000);
    cout << "\n\n\"Enough!\" The man, Wesker, interrupted. \"I will kill you!\"";
    Sleep(3000);
    cout << "\n\nYou look at Santiago, and he nods at you.";
    Sleep(3000);
    cout << "\n\nIt's time for the final boss.\n";
    Sleep(3000);

    Mastermind();
    track = "DreadFearful";
    Mastermind_flag = 1;
    A2enemy.pop();
    Enemy &A2enemy9 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy9, consumables, choices);
    if (death_flag == 1){
        return;
    } 

    Sleep(3000);
    cout << "\n\n\"He's too strong!\" Santiago exclaims, \"How the hell do we kill him!?\"";
    Sleep(3000);
    cout << "\n\n\"Here's the answer.\" The man said, \"You don't.\"";
    Sleep(3000);
    cout << "\n\nThe man flings you with the mold on his arm.";
    Sleep(3000);
    PlaySound(TEXT("Sound Effects/thud.wav"), NULL, SND_FILENAME | SND_ASYNC);
    if (flag_friends = 1){
        cout << "\n\n\"Muchacho! I ain't leaving you here!\"";
        Sleep(3000);
        cout << "\n\nSantiago moves to beside you, shooting a lot of bullets into the man.";\
        Sleep(3000);
        cout << "\n\nThe man doesn't flinch.";
        Sleep(3000);
        cout << "\n\n\"Damn it!\"";

    }
    else if (flag_friends = 0){
        cout << "\n\n\"Muchacho, run! I can handle this!\"";
        Sleep(3000);
        cout << "\n\nThe man chokes Santiago with the mold on the man's arm.";
        Sleep(3000);
        cout << "\n\n\"I can easily crush you.\"";
        Sleep(3000);
        cout << "\n\n\"I'd... like... to... see you... try...\" Santiago says, before pulling a fast one and shooting him in the face.";
        Sleep(5000);
        PlaySound(TEXT("Sound Effects/red9.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(3000);
        cout << "\n\nThe man doesn't flinch. He crushes Santiago's neck.";
        Sleep(3000);
        cout << "\n\nThe man flings his body to your feet.";
        Sleep(3000);
        cout << "\n\n\"Take this... my Red9. It's yours...\"";
        Sleep(3000);
        addWeapon(collectedWeapons, "Red9");
        PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout << "\n\nReceived... 50 Red9 Ammo.";
        red9_ammo += 50;
        Sleep(3000);
        cout << "\n\n\"Hey... muchacho....\" Santiago's voice cracked. \"People can change... right?\"";
        Sleep(3000);
        cout << "\n\nHe says, before he loses his strength.";
        Sleep(3000);
        cout << "\n\n\"It's time to deal with you next.\" The man says, approaching slowly.";
        Santiago_flag = 0;
    }

    Sleep(3000);
    cout << "\n\n\"Hey!\" A woman's voice was heard from the right bridge.";
    Sleep(3000);
    cout << "\n\nWesker looked irritated, but still sets his eyes on you.";
    Sleep(3000);
    cout << "\n\n\"Take this!\" The voice said, a grenade launcher falling beside you.";
    Sleep(3000);
    addWeapon(collectedWeapons, "Grenade Launcher");
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nReceived 2 Grenade Launcher Ammo!";
    grenadeLauncher_ammo = 2;
    Sleep(3000);
    cout << "\n\nYou pick it up, and threaten the man. He scowls at you.";
    Sleep(3000);
    cout << "\n\nYou hear steps of running away from the scene.";
    Sleep(3000);
    if (flag_friends == 1){
        cout << "\n\nA Grenade Launcher!? Hahahaha! Let's do this, " << player.getName() << "!";
        Sleep(3000);
    }
    cout << "\n\nYou stare at the man. It's time for the final battle!\n";
    Sleep(3000);

    Mastermind();
    Mastermind_flag = 0;
    A2enemy.pop();
    Enemy &A2enemy10 = A2enemy.top();
    battle_start_animation();
    battle_start(player, A2enemy10, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    
    cout << "\n\n\"System Meltdown will begin in 10...";

    if (flag_friends == 0){
        PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
        cout << "\n\nYou run for the elevator.";
        Sleep(2000);
        cout << "\n\n9...";
        Sleep(2000);
        cout << "\n\nYou press the button to go up.";
        Sleep(2000);
        cout << "\n\n\"7...\"";
        Sleep(3000);
        cout << "\n\nThe elevator responds, going up.";
        Sleep(2000);
        cout << "\n\n\"6...\"";
        Sleep(2000);
        cout << "\n\nThe elevator goes up at a fast rate. You can't even make out what's outside with all the blur from the speed.";
        Sleep(5000);
        cout << "\n\n\"1...\"";
        Sleep(2000);
        cout << "\n\nThe elevator arrives into the outside world. You can hear a bit of the explosion from below.";
        PlaySound(TEXT("Sound Effects/distant explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(3000);
        PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
        cout << "\n\nThe elevator opens, and it reveals a lush green forest. It's as if the outside world wasn't affected from the outbreak below.";
        Sleep(5000);
        cout << "\n\nYou step outside, and see nothing much else. Maybe it seemed that only the scientists had access to the outside world... and most of them died.";
        Sleep(5000);
        cout << "\n\nYou sit down on the ground, contemplating what to do.";
        Sleep(5000);
        cout << "\n\nThere is no way to get the cure now, but there is peace. Maybe you'll try to survive for as long as you can.";
        Sleep(5000);
        cout << "\n\nYou see a deer from a distance, eating some of the vegetation peacefully.";
        Sleep(5000);
        cout << "\n\nYou smile bitterly, and draw your Red9.";
        Sleep(5000);
        PlaySound(TEXT("Sound Effects/red9.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(3000);
        cout << "\n\nYou win! You escaped the zombies!";
        Sleep(3000);
    }

    else{
        PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
        cout << "\n\nYou and Santiago run for the elevator. \"Let's go, muchacho!\"";
        Sleep(2000);
        cout << "\n\n9...";
        Sleep(2000);
        cout << "\n\nYou press the button to go up. \"We can reach it! The elevator is fast!\"";
        Sleep(2000);
        cout << "\n\n\"7...\"";
        Sleep(3000);
        cout << "\n\nThe elevator responds, going up.";
        Sleep(2000);
        cout << "\n\n\"6...\"";
        Sleep(2000);
        cout << "\n\nThe elevator goes up at a fast rate. You can't even make out what's outside with all the blur from the speed.";
        Sleep(5000);
        cout << "\n\n\"1...\"";
        Sleep(2000);
        cout << "\n\nThe elevator arrives into the outside world. You can hear a bit of the explosion from below.";
        PlaySound(TEXT("Sound Effects/distant explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
        Sleep(3000);
        PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
        cout << "\n\nThe elevator opens, and it reveals a lush green forest. It's as if the outside world wasn't affected from the outbreak below.";
        Sleep(5000);
        cout << "\n\nYou step outside, and see nothing much else. Maybe it seemed that only the scientists had access to the outside world... and most of them died.";
        Sleep(5000);
        cout << "\n\nYou sit down on the ground, contemplating what to do.";
        Sleep(5000);
        cout << "\n\n\"Finally out, huh? I was stuck in that hellhole for years.\"";
        Sleep(5000);
        cout << "\n\nSantiago sits down beside you, and lights a cigarette.";
        Sleep(5000);
        cout << "\n\nHe offers you a stick.";
        Sleep(5000);
        do{
            cout << "\n\nYou do:\n1. --> Accept.\n2. --> Decline.\n";
            cin >> dialogue_choice;
            system("CLS");
            if (dialogue_choice == "1"){
                cout << "\n\nYou take the stick, and Santiago lights it for you.";
                Sleep(5000);
                cout << "\n\n\"Beats killing zombies, am I right?\"";
                Sleep(5000);
                cout << "\n\nYou stare at him.";
                Sleep(5000);
                cout << "\n\n\"What? Well, I never said we wouldn't find more zombies when we're delivering the sample, right?\"";
                Sleep(5000);
                cout << "\n\n\"They're far, but they're here.\"";
                Sleep(5000);
                cout << "\n\n\"Well, we can take our time.\" He says, smoking.";
                Sleep(5000);
                cout << "\n\n\"How about we...\" He says, pointing at a deer \"Kill some time?\"";
                Sleep(5000);
                win();
                flag_choice = 1;
            }
            else if (dialogue_choice == "2"){
                cout << "\n\n\"Whatever.\" He shrugs.";
                Sleep(5000);
                cout << "\n\n\"We still got work to do.\"";
                Sleep(5000);
                cout << "\n\nYou forgot. You were still supposed to deliver the sample.";
                Sleep(5000);
                cout << "\n\n\"Well, we can take our time.\" He says, smoking.";
                Sleep(5000);
                cout << "\n\n\"How about we...\" He says, pointing at a deer \"Kill some time?\"";
                win();
                flag_choice = 1;
            }
            else{
                cout << "\n\nTry again.";
            }

        }while(flag_choice == 0);
    }

   choices.Display_Choices();

    do {
        flag_choice = 0;
        cout << "\nWould you like to try again? [Y/n]: ";
        cin >> choice_again;
        if (choice_again == "Y" || choice_again == "y") {
            flag_choice = 1;
            return;
        } 
                
        else if (choice_again == "N" || choice_again == "n") {
            cout << "Thank you for playing Too Alive to Die!";
            Sleep(4000);
        } 
                
        else {
            cout << "Invalid input. Try again.";
        }

    } while (flag_choice == 0);


}


void scenarioA1(Player &player, Enemy &enemy, Consumable consumables[], Dialogue_List &choices){

    stack <Enemy> A1enemy;
    A1enemy.push(Enemy("The Butcher", 1000, 1000, 40));
    A1enemy.push(Enemy("Nine-Limbs", 200, 200, 20));
    A1enemy.push(Enemy("Nine-Limbs", 200, 200, 20));
    A1enemy.push(Enemy("Nine-Limbs", 200, 200, 20));
    A1enemy.push(Enemy("Dead Body(?)", 150, 150, 20));   
    A1enemy.push(Enemy("Dead Body(?)", 150, 150, 20));   
    A1enemy.push(Enemy("???", 100, 100, 15));
    A1enemy.push(Enemy("???", 50, 50, 5));
    A1enemy.push(Enemy("Dead Body(?) - Weak", 25, 50, 20));    
    

    Sleep(2000);
    cout << "\n\nYou continue down the corridor, and go up the stairs.";
    Sleep(2000);
    cout << "\n\nYou find yourself in a big area, four bridges intersecting into the center. At the center lies... the elevator!";
    Sleep(3000);
    cout << "\n\nThat must be the way out!";
    Sleep(2000);
    cout << "\n\nBut then, three of those things are blocking the way!";
    Sleep(2000);
    cout<< "\n\nOne of them seems weak, and is holding a metal pipe. You only have one ammo left."; 
    Sleep(2000);
    cout << "\n\nWhat will you do?\n1. Risk it and fight the things.\n2. Run back to where you found the man.\n";
    
    do{
        cin >> dialogue_choice;
        flag_choice = 0;
        if (dialogue_choice == "1"){
            Enemy &A1enemy1 = A1enemy.top();
            Sleep(2000);
            cout << "\n\nYou decide to fight the weak one first!";
            Sleep(2000);
            battle_start_animation();
            battle_start(player, A1enemy1, consumables, choices);
            if (death_flag == 1){
                return;
            }  
            PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            cout << "\n\nThe weak thing dies, and drops the metal pipe!";
            Sleep(2000);
            addWeapon(collectedWeapons, "Metal Pipe");
            PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            cout << "\n\nThat wasn't that much of a problem. Those two of his friends are the only thing to worry about now.";
            Sleep(2000);
            cout << "\n\nSuddenly, something attacks you from behind! You manage to dodge it, but that was close.";
            Sleep(2000);
            cout << "\n\nYou turn to face it, and it was a little girl in a cloak! She's holding a knife! It seems that she is intent on killing you! But why?";
            Sleep(2000);
            cout << "\n\nThere's no choice! You have to defend yourself!";
            Sleep(3000);
            A1enemy.pop();
            Enemy &A1enemy2 = A1enemy.top();
            battle_start_animation();
            battle_start(player, A1enemy2, consumables, choices);
            if (death_flag == 1){
                return;
            }          
            A1enemy.pop();
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            Enemy &A1enemy1 = A1enemy.top();
            A1enemy.pop();
            Sleep(2000);
            cout << "\n\nYou try to go back, but you bump into someone. You were certain it was a person.";
            Sleep(2000);
            cout << "\n\nWhen you gather your bearings, you see a little girl in a cloak holding a knife. She's shaking as she tries to stand her guard.";
            Sleep(2000);
            
     
        do{
            cout << "\n\nYou say:\n1. It's alright. I won't hurt you.\n2. What's a kid doing around here?\n";
            flag_choice = 0;
            cin >> dialogue_choice;
            system("CLS");
            if (dialogue_choice == "1"){
                choices.addDialogueChoice("It's alright. I won't hurt you.");
                Sleep(2000);
                cout << "\n\nThe little girl calms down, but her eyes show that she's wary of you. She raises her knife to strike.";
                Sleep(5000);
                Enemy &A1enemy2 = A1enemy.top();
                battle_start_animation();
                battle_start(player, A1enemy2, consumables, choices);
                if (death_flag == 1){
                    return;
                }  
                A1enemy.pop();
                flag_choice = 1;
            }
            else if (dialogue_choice == "2"){
                choices.addDialogueChoice("What's a kid doing around here?");
                Sleep(2000);
                cout << "\n\nThe little girl just tightens her grip on the knife in response, strengthening her resolve. It's like she's ready to attack.";
                Sleep(2000);
                A1enemy.pop();
                Enemy &A1enemy3 = A1enemy.top();
                battle_start_animation();
                battle_start(player, A1enemy3, consumables, choices);
                if (death_flag == 1){
                    return;
                }             
                flag_choice = 1;
            }
            else{
                cout << "\n\nTry again.";
            }
            }while (flag_choice == 0);
    }
    else{
        cout << "\n\nInvalid choice. Try again.";
    }
    }while (flag_choice == 0);
    
    Sleep(2000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\nThe little girl gets knocked to the ground, unable to fight further.";
    Sleep(2000);
    cout << "\n\nThroughout the fight, it seemed that she was holding back. She lies there, on the ground, looking at you with fear.";
    Sleep(2000);
    
    do{ 
        cout << "\n\nYou do:\n1. You ignore her, and fight the rest of the enemies.\n2. You help her stand up.\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("You ignore Rena, and fight the rest of the enemies.");
            Sleep(2000);
            cout << "\n\nYou turn back to the Infected, and attack the first one.";
            Sleep(2000);
            cout << "\n\nBefore you could raise your weapon, the little girl goes to your side!";
            Sleep(2000);
            cout << "\n\n??? now fights by your side!";
            Rena1_flag = 1;
            Sleep(2000);
            A1enemy.pop();
            Enemy &A1enemy4 = A1enemy.top();
            battle_start_animation();
            battle_start(player, A1enemy4, consumables, choices);
            if (death_flag == 1){
                return;
            }             
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            Sleep(2000);
            choices.addDialogueChoice("You help her stand up.");
            flag_friends = 1;
            cout << "\n\nYou help her up. She looks at the Infected behind you, then nods her head. It seems she knows what you want to do.";
            Sleep(4000);
            cout << "\n\n??? now fights by your side!";
            Rena1_flag = 1;
            Sleep(2000);
            A1enemy.pop();
            Enemy &A1enemy4 = A1enemy.top();
            battle_start_animation();
            battle_start(player, A1enemy4, consumables, choices);
            if (death_flag == 1){
                return;
            }  
            flag_choice = 1;
        }
        else {
            cout << "\n\nTry again.";
            
        }

    }while (flag_choice == 0);


    cout << "\n\n??? gives you 5 Handgun Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    handgun_ammo += 5;
    Sleep(3000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nYou then attack the last Infected!";
    Sleep(3000);

    A1enemy.pop();
    Enemy &A1enemy5 = A1enemy.top();
    battle_start_animation();
    battle_start(player, A1enemy5, consumables, choices);
    if (death_flag == 1){
        return;
    }         
    
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nYou breathe in and out fast. That was exhausting,";
    Sleep(3000);
    cout << "\n\nIt seems that the little girl is doing the same. Though her voice sounds more strained.";
    Sleep(3000);
    cout << "\n\n\"Rena.\" She says.";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou do\n1. --> What?\n2. --> " << player.getName() << "." << endl;
        cin >> dialogue_choice;
        if (dialogue_choice == "1"){
            Sleep(3000);
            cout << "\n\n\"My name is Rena...\" The little girl says.";
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            Sleep(3000);
            cout << "\"" << player.getName() << "...\""; 
            flag_choice  = 1;
        }
        else{
            cout << "\n\nTry again.";
        }
    }while (flag_choice = 0);

    cout << "\n\nYou then head over to the elevator in the center of the area. You press a button, but it instead displays an X mark on the screen.";
    Sleep(4000);
    cout << "\n\n\"Needs a keycard...\" Rena says.";
    Sleep(3000);
    do{
        flag_choice = 0;
        Sleep(3000);
        cout << "\n\nYou say:\n1. Where's the closest keycard?\n2. Why are you wearing a cloak? You hiding something there?\n3. --> Let's go.\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            cout << "\n\n\"West Wing...\" Rena says. You turn to your left, and see a bridge extending to a narrow passage, the same as the opening where you found the elevator.";
            Sleep(5000);
        }
        else if (dialogue_choice == "2"){   
            if (flag_friends == 1){
                Sleep(3000);
                cout << "\n\nShe shows you a bite mark on her left arm.";
                Sleep(3000);
                cout << "\n\nIf it doesn't get treated immediately, she'll turn into one of those things.";
                Sleep(3000);
                cout << "\n\nYou breathe in, and try to reassure her.";
                Sleep(3000);
            }
            else{
                Sleep(3000);
                cout << "\n\nShe doesn't answer.";
            }
        }
        else if (dialogue_choice == "3"){
            flag_choice = 1;
        }
        else {
            cout << "\n\nTry again.";
        }
    
    }while (flag_choice == 0);

    Sleep(3000);
    cout << "\n\nShe leads you to the West Wing.";
    Sleep(3000);
    cout << "\n\n\"System Meltdown will begin in 20 minutes. Please evacuate.\" The system warns.";
    Sleep(4000);
    cout << "\n\nYou pick up the pace. Rena does so as well.";
    Sleep(3000);
    cout << "\n\n\"So where is the keycard?\" You ask.";
    Sleep(3000);
    cout << "\n\n\"Biology Lab...\" Rena says meekly.";
    Sleep(3000);
    cout << "\n\nYou nod, and look at the signs. The Biology Lab is just ahead.";
    Sleep(3000);
    cout << "\n\nBefore you could go any further, an Infected with nine limbs attached to its body bursts out of a closed door!";
    Sleep(4000);
    cout << "\n\nIt's a horrifying creature of abomination. Multiple different parts of different colors are attached by staples and stitches.";
    Sleep(5000);
    cout << "\n\nIt moves as if it was a ball, using its arms and legs to roll. The sounds of its limbs moving are like those of a cockroach.";
    PlaySound(TEXT("Sound Effects/nine-limbs.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(5000);
    cout << "\n\nYou prepare yourself.";
    Sleep(3000);

    A1enemy.pop();
    Enemy &A1enemy6 = A1enemy.top();
    battle_start_animation();
    battle_start(player, A1enemy6, consumables, choices);
    if (death_flag == 1){
        return;
    }         

    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nThe noises seem to attract more of those things, and they attack!";
    Sleep(3000);
    cout << "\n\nYou prepare yourselves!";
    Sleep(3000);
    
    A1enemy.pop();
    Enemy &A1enemy7 = A1enemy.top();
    battle_start_animation();
    battle_start(player, A1enemy7, consumables, choices);
    if (death_flag == 1){
        return;
    }   

    cout << "\n\nThe Nine-Limbs drop an AR15 with 10 AR15 ammo!";
    addWeapon(collectedWeapons, "AR15");
    AR15_ammo = 10;
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nOne more appears!";
    Sleep(3000);
    cout << "\n\nYou prepare yourselves!";
    Sleep(3000);

    A1enemy.pop();
    Enemy &A1enemy9 = A1enemy.top();
    battle_start_animation();
    battle_start(player, A1enemy9, consumables, choices);
    if (death_flag == 1){
        return;
    }   
    cout << "\n\nRena gives you one of her Knives!";
    addWeapon (collectedWeapons, "Knife");
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nYou both quickly head inside the Biology Lab with Rena.";
    Sleep(3000);
    cout << "\n\nInside, it's not what you expected.";
    Sleep(3000);
    cout << "\n\nThe room was filled with flesh. It makes you almost puke.";
    Sleep(3000);
    cout << "\n\nThere were a lot of bear traps hanging on the wall. This used to be an ordinary lab, but it was disturbed.";
    Sleep(4000);
    cout << "\n\nIt's as if someone else owned the place now.";
    Sleep(3000);
    cout << "\n\nRealizing this, you quickly search for the keycard, opening every drawer and cabinet.";
    Sleep(4000);
    cout << "\n\nWhile searching, you found a... tube of an unkown liquid?";
    Sleep(3000);
    cout << "\n\nIt's bluish in color. What is it for?";
    Sleep(3000);
    cout << "\n\nThere's also a note from where you found the liquid.";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou do:\n1. --> Read the note.\n2. --> Keep searching for the keycard.\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(4000);
            choices.addDialogueChoice("Read the note.");
            cout << "\n\nThere's a lot of words on the note. They seem to be describing a certain chemical.";
            Sleep(4000);
            cout << "\n\nYou don't know what the first part means due to the medical jargo. It takes a while to understand.";
            Sleep(4000);
            cout << "\n\nThe last part, you can read. It says that the tube contains the suppressant for the virus.";
            Sleep(4000);
            cout << "\n\nWhich means that it can cure someone of their early stage Infection.";
            Sleep(3000);
            if (flag_friends == 1){
                cout << "\n\nYou look at Rena. You give her a nod.";
                Sleep(3000);
                cout << "\n\nYou inject her with the suppressant. It should stop the Infection.";
                Sleep(4000);
                cout << "\n\nYou then find the keycard and head to the elevator with Rena.";
                Sleep(3000);
                flag_friends++;
            }
            else{
                cout << "\n\nYou don't seem to have a need for it. Might as well keep it just in case.";
                Sleep(3000);
                cout << "\n\nYou then find the keycard and head to the elevator with Rena.";
                Sleep(4000);
            }
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Kept searching for the keycard.");
            cout << "\n\nYou keep searching for the keycard, and you eventually found it. It took a bit of searching, but you can finally get out of here.";
            Sleep(4000);
            cout << "\n\nYou go with Rena to the elevator.";
            Sleep(3000);
            flag_choice = 2;
        }
        else{
            cout << "\n\nTry again.";
        }
    }while (flag_choice == 0);

    if (flag_choice  == 1){
        track = "DreadFearful";
        cout << "\n\nYou open the elevator, but then you face a tall Infected.";
        Sleep(3000);
        cout << "\n\nIt has a Chainsaw.";
        Sleep(3000);
        cout << "\n\nIt must be the one that stays in the Biology Lab. It even is holding one of its bear traps on hand.";
        Sleep(4000);
        cout << "\n\nYou fight the Butcher! Final boss!";
        Sleep(3000);
        A1enemy.pop();
        Enemy &A1enemy8 = A1enemy.top();
        battle_start_animation();
        battle_start(player, A1enemy8, consumables, choices);
        if (death_flag == 1){
            return;
        }   
    }

    if (flag_choice == 2 && flag_friends <= 1) {
        cout << "\n\nYou open the elevator, and head inside.";
        Sleep(3000);
        cout << "\n\nThen you notice Rena coughing.";
        Sleep(3000);
        cout << "\n\nShe shows you a bite mark on her arm.";
        Sleep(3000);
        cout << "\n\nShe hesitantly gives you her hidden gun. She is telling you to kill her.";
        Sleep(4000);
        do{
            flag_choice = 0;
            cout << "\n\nYou do:\n1. You kill her. \n2. You leave her.\n3. You take her with you.\n";
            if (flag_friends == 1){
                cout << "4. Inject her with the suppressant.";
            }
            cin >> dialogue_choice;
            system("CLS");
            if (dialogue_choice == "1"){
                choices.addDialogueChoice("Killed Rena.");
                Sleep(3000);
                cout << "\n\nYou shoot her.";
                PlaySound(TEXT("Sound Effects/red9.wav"), NULL, SND_FILENAME | SND_ASYNC);
                Sleep(4000);
                cout << "\n\nShe smiles and puts your hand to her face.";
                Sleep(3000);
                cout << "\n\n\"Thank you...\" She says in her final words.";
                Sleep(3000);
                PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                cout << "\n\nYou slowly, dejectedly press the button on the elevator to go up.";
                Sleep(5000);
                cout << "\n\nYou wait, and once you arrive, you step outside.";
                Sleep(5000);
                cout << "\n\nYou grip the gun tightly.";
                Sleep(5000);
                cout << "\n\nWhy does it have to end this way?";
                Sleep(5000);
                cout << "\n\nYou win! You escaped the zombies!";
                Sleep(5000);
            }
            else if (dialogue_choice == "2"){
                choices.addDialogueChoice("Left Rena.");
                cout << "\n\nSeeing your hesitance, she steps out of the elevator.";
                Sleep(3000);
                PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                cout << "\n\nYou slowly, dejectedly press the button on the elevator to go up.";
                Sleep(5000);
                cout << "\n\nYou wait, and once you arrive, you step outside.";
                Sleep(5000);
                cout << "\n\nYou grip the gun tightly.";
                Sleep(5000);
                cout << "\n\nWhy does it have to end this way?";
                Sleep(5000);
                cout << "\n\nYou win! You escaped the zombies!";
                Sleep(5000);
            }

            else if (dialogue_choice == "3"){
                choices.addDialogueChoice("Forced Rena to come.");
                cout << "\n\nYou take her in. She refuses, but you force her.";
                Sleep(3000);
                cout << "\n\nThere must be a way. There has to be.";
                Sleep(3000);
                PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                cout << "\n\nYou quickly press the button on the elevator.";
                Sleep(5000);
                cout << "\n\nYou arrive to the surface, and start walking with her.";
                Sleep(5000);
                cout << "\n\nThere should be a way.";
                Sleep(5000);
                cout << "\n\nYou win! You escaped the zombies!";
                Sleep(5000);
            }

            else if (dialogue_choice == "4" && flag_friends == 1){
                choices.addDialogueChoice("Saved Rena.");
                cout << "\n\nYou inject her with the suppresant.";
                Sleep(3000);
                cout << "\n\nShe stares at you in shock. Her coughing seems to have stopped.";
                Sleep(3000);
                cout << "\n\nShe smiles, and says...";
                Sleep(3000);
                cout << "\n\n\"Thank you.\"";
                Sleep(3000);
                PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                cout << "\n\nYou smile, and press the button on the elevator.";
                Sleep(5000);
                cout << "\n\nYou arrive to the surface, and start walking with her.";
                Sleep(5000);
                cout << "\n\nWhat would happen next, you wonder?";
                Sleep(5000);
                cout << "\n\nMaybe you'll just try to survive.";
                Sleep(5000);
                cout << "\n\nYou win! You escaped the zombies!";
                Sleep(5000);
            }
            else {
                cout << "\n\nTry again.";
            }
        }while (flag_choice == 0);
    }
    else if (flag_friends == 2){
                choices.addDialogueChoice("Saved Rena.");
                PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                cout << "\n\nYou run to the elevator with her, and press the button.";
                Sleep(5000);
                cout << "\n\nYou arrive to the surface, and start walking with her.";
                Sleep(5000);
                cout << "\n\nWhat would happen next, you wonder?";
                Sleep(5000);
                cout << "\n\nMaybe you'll just try to survive.";
                Sleep(5000);
                cout << "\n\nYou win! You escaped the zombies!";
                Sleep(5000);
    }

    choices.Display_Choices();

    do {
        flag_choice = 0;
        cout << "\nWould you like to try again? [Y/n]: ";
        cin >> choice_again;
        if (choice_again == "Y" || choice_again == "y") {
            flag_choice = 1;
            return;
        } 
                
        else if (choice_again == "N" || choice_again == "n") {
            cout << "Thank you for playing Too Alive to Die!";
            Sleep(4000);
        } 
                
        else {
            cout << "Invalid input. Try again.";
        }

    } while (flag_choice == 0);


}

void scenarioA(Player& player, Consumable consumables[], Dialogue_List choices){

    Sleep(3000);
    cout << "\n\nYou were ready, with the pistol in hand. Fortunately for you, you had training for these types of weapons. You don't know how or why, but muscle memory just works.";
    Sleep(5000);
    cout << "\n\nYou decide to check the magazine, and repulse upon peering at it. You have four bullets. What's that gonna do in this situation!?";
    Sleep(5000);
    cout << "\n\nYou sigh, and load the magazine back into the gun. Whatever's out there, it's better that you're ready for it.";
    Sleep(5000);
    cout << "\n\nSuddenly, the body starts moving. It seems to be... alive? But it's dead! There's no way!";
    Sleep(3000);
    cout << "\n\nYou try to call out to the body, but it doesn't answer. All that escapes from its mouth is...";
    Sleep(2000);
    PlaySound(TEXT("Sound Effects/zombie_groan_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);

    Enemy enemy ("Dead(?) Body", 50, 50, 20);

    intro();
    battle_start_animation();
    battle_start(player, enemy, consumables, choices);
        if (death_flag == 1){
        return;
    }

    cout << "\n\nThe shooting seems to have attracted a lot of whatever that body was. You don't have much ammo left.";
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(3000);
    cout << "\n\nYou decide to book it and run deeper into the corridors.";
    Sleep(3000);
    cout << "\n\nYou run down the corridor, and you see more lights the deeper you go. It seems like you're going somewhere safer. You slow down.";
    Sleep(3000);
    cout << "\n\nA voice calls out to you. You turn to the left to look, and you see a person.";
    Sleep(2000);
    cout << "\n\n\"Hey. You a patient?\" the man asks.";
    Sleep(2000);
    do{
    flag_choice = 0;
    cout << "\n\nYou say:";
    Sleep(500);
    cout << "\n1. A patient? What do you mean?\n2. What is this place?\n3. What are you here for?\n4. --> What are you planning to do?" << endl;
    cin >> dialogue_choice;
    system("CLS");
    
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
        cout << "\n\n\"Tell you what. You help me do some things, and I'll help you too.\" He says, his eyes calm and composed.";
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
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. --> I don't know who you are. No deal.\n2. --> Let's go." << endl;
        cin >> dialogue_choice;
        system("CLS");
        
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Did not go with Santiago.");
            Sleep(2000);
            cout << "\n\n\"Your loss.\" The man says, before moving out of sight. Seems he has his own business to take care of.";
            flag_choice = 1;
            scenarioA1(player, enemy, consumables, choices);
        }
        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Went with Santiago.");
            Sleep(2000);
            cout << "\n\"Great. Come with me.\"";
            flag_choice = 1;
            scenarioA2(player, enemy, consumables, choices);

        }
        else{
            cout << "\n\nInvalid choice. Try again.";
        }
    }  while (flag_choice == 0);



}

void scenarioB1(Player &player, Consumable consumables[], Dialogue_List &choices){


    stack <Enemy> B1enemy;
    B1enemy.push(Enemy("Mr. Gamma", 1500, 5000, 50));
    B1enemy.push(Enemy("Mr. Gamma", 5000, 5000, 30));
    B1enemy.push(Enemy("Wretch Blob", 300, 300, 30));
    B1enemy.push(Enemy("Big Blob", 500, 500, 30));
    B1enemy.push(Enemy("Wretch", 300, 300, 10));
    B1enemy.push(Enemy("Wretch", 300, 300, 10));
    B1enemy.push(Enemy("Wretch", 300, 300, 10));
    B1enemy.push(Enemy("Wretch", 300, 300, 10));
    B1enemy.push(Enemy("Wretch", 300, 300, 10));
    B1enemy.push(Enemy("Screecher", 200, 200, 25));
    B1enemy.push(Enemy("Infected", 140, 140, 20));


    Sleep(2000);
    cout << "You immediately go through it, close the door, and lock it.";
    Sleep(2000);
    cout << "\n\nYou peek through the small hole on the door created by a bullet, and see many of the humanoid shadows banging on the door.";
    Sleep(2000);
    cout << "\n\nYou sigh, hanging your head back--";
    Sleep(500);
    cout << "\n\nYou feel something metallic press against the back of your head.";
    Sleep(2000);
    cout << "\n\n\"Going somewhere?\" A man's voice is heard from behind you, as he presses the metallic barrel against the back of your head."; 
    Sleep(2000);
    cout << "\n\nThis is dangerous. It's over if he pulls the trigger.";
    Sleep(2000);
    
    do{
        cout << "\n\nYou say/do:\n1. What do you want?\n2. Try to disarm him.\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Asked JACK what he wants");
            Sleep(2000);
            cout << "\n\n\"I just want something simple. You give me some ammo and help me, and I'll spare you.\"";
            flag_choice = 1;
        }
        else if (dialogue_choice == "2") {
            choices.addDialogueChoice("Tried to disarm JACK.");
            Sleep(2000);
            cout << "\n\nYou quickly twist your body, and then push his arm away from you. The gun clicks in response.";
            Sleep(2000);
            cout << "\n\nYou realize... the gun is empty.";
            Sleep(2000);
            cout << "\n\n\"Caught my bluff, huh?\"";
            Sleep(2000);
            cout << "\n\nHe quickly twists your arms and pins you to the door, your back facing him.";
            Sleep(2000);
            cout << "\n\n\"I can still feed you to those things.\""; 
            flag_choice = 1;
        }
        else{
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\n\"I've activated a system meltdown. In 30 minutes, the facility will blow up sky high.\"";
    Sleep(2000);
    cout << "\n\n\"Just give me some ammo and help me, and we'll get out of here alive.\"";
    Sleep(2000);
    cout << "\n\nYou have no choice. You give him all the ammo you have.";
    Sleep(2000);
    cout << "\n\nGave 5 Handgun Ammo to the man.";
    PlaySound(TEXT("Sound Effects/Give.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    handgun_ammo -= 5;
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\n\"Good.\" He lets you go. \"We on the same page?\"";
    Sleep(2000);
    cout << "\n\n\"The system meltdown isn't enough. I was setting charges all throughout the underground, but I ran out of ammo to those things.\"";
    Sleep(2000);
    cout << "\n\nHe gestures his head to the door.";
    Sleep(2000);
    cout << "\n\n\"Too many.\" He says this calmly and sternly, as if the things out there didn't matter to him.";
    Sleep(2000);
    cout << "\n\nYou look at him and all his gear. He seems to be a soldier for a private military company, wearing an all black uniform, a helmet, and a gas mask with red eye filters. He has ammo pouches and grenade pouches all over his body.";
    Sleep(2000);
    cout << "\n\nHe even has a lot of weapons. A submachine gun, a magnum, a handgun, and a shotgun, all slinging on his body. He looks like he means business.";
    Sleep(2000);
    cout << "\n\n\"This facility is the sole reason everything turned out like this. We have to blow it up.\"";
    Sleep(2000);
    cout << "\n\n\"Let's move.\" The man says, loading the ammo you gave him into the handgun that he has.";
    Sleep(2000);
 
    do{
        cout << "\n\nYou say:\n1. What is this facility for?\n2. What's your name?\n3. --> Let's go.\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(2000);
            cout << "\n\n\"The start of the outbreak.\"";
        }
        else if (dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\n\"Not important.\" He cracks his neck while he says this...";
            flag_friends = 1;
            flag_choice = 1;
        }
        else if (dialogue_choice == "3"){
            Sleep(2000);
            cout << "\n\n\"Then let's go.\"";
            flag_choice = 1;
        }
        else{
            cout << "\n\nTry again.";
        }
    }while (flag_choice == 0);

    if (flag_friends == 0){
        choices.addDialogueChoice("Did not ask about JACK's name.");
    }
    else{
        choices.addDialogueChoice("Asked JACK his name.");
    }

    Sleep(2000);
    cout << "\n\nHe seems to be not interested in talking. He leads you to a small passageway, then to a ladder that goes down.";
    Sleep(2000);
    cout << "\n\nYou both find a map in the room below, and read it.";
    Sleep(2000);
    cout << "\n\nYou are five floors away from the exit, judging by the contents of the map.";
    Sleep(2000);
    cout << "\n\nThe man immediately moves, now knowing where to go to next. You follow him.";
    Sleep(2000);
    cout << "\n\nYou end up in a large room, having many offices lodged inside this one room. One nameplate reads \"Marvin, G.\"";
    Sleep(2000);
    cout << "\n\n\"Security Room. Careful.\" The man identifies the room.";
    Sleep(2000);
    cout << "\n\nThe man wastes no time, and immediately goes toward the other door on the far side of the room. You see a note on the Marvin, G. table.";
    Sleep(2000);

    do{
        cout << "\n\nYou do:\n1. --> Follow him\n2. Read the note.\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\nThe note reads, \"Rookie. If you see this note, get out of here. If you see one of those things and have no ammo, DROPKICK them for me.\"";
            Sleep(2000);
            cout << "\n\nThe dropkick word seems to have been written weirdly, in all capital letters. Maybe it means something?";
        }
        else{
            cout << "\n\nTry again.";
        }
    }while(flag_choice == 0);

    Sleep(2000);
    cout << "\n\nYou follow him, and face one of those things.";
    Sleep(2000);
    cout << "\n\n\"Infected.\" He raises his weapon.";
    Sleep(2000);
    cout << "\n\n??? now fights by your side!";
    JACK1_flag = 1;
    Sleep(2000);
    Enemy &B1enemy1 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy1, consumables, choices);
    if (death_flag == 1){
        return;
    }  
    B1enemy.pop();
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(2000);
    cout << "\n\nThe man picks up some ammunition around the offices, before planting a bomb on the floor.";
    Sleep(2000);
    cout << "\n\nHe goes through the door that was blocked by the Infected, and checks his corners, before letting you through.";
    Sleep(2000);
    cout << "\n\n\"Keep moving.\"";
    Sleep(2000);
    cout << "\n\nYou look at the right, and find a dead end. Seems the left is the only way to go.";
    Sleep(2000);
    cout << "\n\n\"Nightwing. I'm at Point K12. Planted 4 out of 6 bombs. Need info on my extraction.\" The man radios using the radio on his left shoulder.";
    Sleep(2000);
    cout << "\n\n\"Got it. Moving.\"";
    Sleep(2000);
    cout << "\n\nThe system facility echoes its warning, \"System Meltdown will begin in 20 minutes. Please evacuate. System Meltdown will begin in 20 minutes. Please evacuate.\"";
    Sleep(2000);
    cout << "\n\nThe man picks up the pace, and goes down the stairs once he turns the corner with you.";
    Sleep(2000);
    cout << "\n\n\"Hurry up. We don't have much time.\"";
    Sleep(2000);
    cout << "\n\nThe man keeps moving, skipping all the rooms and going to the nearest route on the map.";
    Sleep(2000);
    cout << "\n\n\"Stop.\"";
    Sleep(2000);
    cout << "\n\nThe man stops, gesturing his finger towards one of the Infected. It looks like the same type that screeched before.";
    Sleep(2000);
    cout << "\n\n\"Screechers. They screech when they're about to die.\"";
    Sleep(2000);
    cout << "\n\nThe man then gestures you to fight it with him.";
    Sleep(3500);
    Enemy &B1enemy2 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy2, consumables, choices);
    if (death_flag == 1){
        return;
    }  
    B1enemy.pop();
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(2000);
    cout << "\n\nThe Screecher drops 10 Shotgun Ammo and 8 MP5 Ammo! ??? picks them up.";
    Sleep(2000);
    cout << "\n\nThe Screecher tries to screech, but the man immediately stomps on its face, rendering it unable to do it.";
    Sleep(2000);
    cout << "\n\nThe man handles the navigation, going through the fastest possible route.";
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. What company do you work for?\n2. Were you ordered to plant the bombs?\n3. --> What's the next place?\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(2000);
            cout << "\n\n\"Quadrangle.\"";
        }
        else if (dialogue_choice == "2"){
            Sleep(2000);
            cout << "\n\n\"Yes.\"";
        }
        else if (dialogue_choice == "3"){
            Sleep(2000);
            cout << "\n\n\"The labs.\"";
            flag_choice = 1;
        }
        else{
            cout << "\n\nTry again.";
        }
    
    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\nAs always, the man only says things that are necessary. He doesn't care for idle talk.";
    Sleep(2000);
    cout << "\n\nYou both enter the labs, and see a lot of big test tubes. Inside them were the Infected, but different.";
    Sleep(2000);
    cout << "\n\nThey had smaller bodies, and they look less like humans, and more like monkeys, their back hunched over while their arms reaching their feet.";
    Sleep(2000);
    cout << "\n\nThey look really creepy.";
    Sleep(2000);
    cout << "\n\n\"Wretches. Durable and weak, but strong in numbers. Be careful.\"";
    Sleep(2000);
    cout << "\n\nHe slings over his MP5 and gives it to you. He also gives you its ammo.";
    Sleep(2000);
    cout << "\n\nRecieved MP5!";
    addWeapon(collectedWeapons, "MP5");
    cout << "\n\nReceived 8 MP5 Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    MP5_ammo = 8;
    Sleep(3000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    if (flag_friends == 1){
        Sleep(2000);
        cout << "\n\nThe man places a bomb on the center of the room. He looks at you and says,";
        Sleep(2000);
        cout << "\n\n\"JACK. They call me JACK.\"";
    }
    else{
        Sleep(200);
        cout << "\n\nThe man places a bomb on the center of the room. You take further inspection on his uniform, and see...";
        Sleep(2000);
        cout << "\n\nThe name, \"JACK\", embedded on the left shoulder of his uniform.";
    }

    JACK1_flag = 0;
    JACK2_flag = 1;
     
    Sleep(3000);
    cout << "\n\nJACK searches the lab for something. It seeemed that he's searching really thoroughly.";
    Sleep(3000);
    cout << "\n\nBefore you could ask...";
    Sleep(2000);
    cout << "\n\nThe System echoes throughout the laboratory once again, \"System Meltdown in 15 minutes. Releasing all test subjects.\"";
    Sleep(2000);
    cout << "\n\nYou grimace. Does that mean...";
    Sleep(2000);
    cout << "\n\nThe Wretches inside the test tubes burst out, screeching chaotically.";
    PlaySound(TEXT("Sound Effects/Wretches.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(4000);
    cout << "\n\nJACK raises his weapon.";
    Enemy &B1enemy3 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy3, consumables, choices);
    if (death_flag == 1){
        return;
    }  
    cout << "\n\nYou picked up 10 MP5 Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    MP5_ammo += 10;
    B1enemy.pop();
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(2000);
    cout << "\n\nMore Wretches burst out of the test tubes! Get ready to fight all of them!";
    Sleep(2000);

    Enemy &B1enemy4 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy4, consumables, choices);
    if (death_flag == 1){
        return;
    }  
    cout << "\n\nYou picked up 8 MP5 Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    MP5_ammo += 8;
    B1enemy.pop();
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\nAnother one!";
    Sleep(2000);

    Enemy &B1enemy5 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy5, consumables, choices);
    if (death_flag == 1){
        return;
    }  
    cout << "\n\nYou picked up 8 MP5 Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    MP5_ammo += 8;
    B1enemy.pop();
    track = "Fearful";
    PlaySound(TEXT("Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\n\"System Meltdown beginning in 10 minutes. Please evacuate.\" The system warns once more, irritating you.";
    Sleep(3500);
    cout << "\n\n\"Keep moving!\" JACK says, pushing through every enemy as he kills each one with you.";
    Sleep(3000);
    cout << "\n\nAnother enemy!";
    Sleep(2000);

    Enemy &B1enemy6 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy6, consumables, choices);
    if (death_flag == 1){
        return;
    }

    cout << "\n\nYou picked up 7 MP5 Ammo!";
    MP5_ammo += 7;
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);

    PlaySound(TEXT("Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    B1enemy.pop();  

    cout << "\n\nLast one!";
    Sleep(3000);

    Enemy &B1enemy7 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy7, consumables, choices);
    if (death_flag == 1){
        return;
    }

    cout << "\n\nYou picked up 6 MP5 Ammo!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    MP5_ammo += 6;
    Sleep(3000);
    PlaySound(TEXT("Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    B1enemy.pop();  

    cout << "\n\nThere's not much time. You have to book it.";
    Sleep(2000);
    cout << "\n\n\"Move!\" JACK says, pushing past every obstacle and sprinting through every room with you.";
    Sleep(3000);
    cout << "\n\n\"The way out is close! That's the last bomb we have to plant!\"";
    Sleep(3500);
    cout << "\n\nYou sprint faster and faster, your breathing getting heavier and faster.";
    Sleep(3000);
    cout << "\n\nThat is... until a big blob of goo blocks your way.";
    Sleep(3000);
    cout << "\n\n\"What the hell is that!?\"";
    Sleep(2000);
    cout << "\n\nIt's big, and tall. it fills the whole room with its own goo. But it doesn't seem to be able to move from its spot.";
    Sleep(4500);
    cout << "\n\n\"Let's take it down!";
    Sleep(2000);

    Enemy &B1enemy8 = B1enemy.top();
    battle_start_animation();
    battle_start(player, B1enemy8, consumables, choices);
    if (death_flag == 1){
        return;
    }


    cout << "\n\nYou picked up 50 MP5 Ammo! That's a lot!";
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    MP5_ammo += 50;
    PlaySound(TEXT("Fearful is No Word for It.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\nYou're running out of time. It seems that the Big Blob has dissolved, but it dropped something!";
    Sleep(3000);
    cout << "\n\nYou have a bad feeling something would happen if you took it.";
    Sleep(3000);
    B1enemy.pop();
    do{
        flag_choice = 0;
        cout << "\n\nYou do:\n1. Pick up the item.\n2. Keep running.\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(3000);
            cout << "\n\nYou pick up the item. It seems to be... a Chainsaw!";
            Sleep(3000);
            addWeapon(collectedWeapons, "Chainsaw");
            cout << "\n\nBut then... the blob returns in a form of a Wretch!";
            Sleep(3000);
            cout << "\n\nNo turning back!";
            Sleep(3000);
            Enemy &B1enemy9 = B1enemy.top();
            battle_start_animation();
            battle_start(player, B1enemy9, consumables, choices);
                if (death_flag == 1){
                    return;
                }
        }

        else if (dialogue_choice == "2"){
            Sleep(3000);
            cout << "\n\nEvery reward has its risks.";
            B1enemy.pop(); 
            flag_choice = 1;
        }

        else{
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    B1enemy.pop();  
    cout << "\n\n\"System Meltdown will begin in 5 minutes. Please evacuate. System Meltdown will begin in 5 minutes. Please evacuate.\" The system warns one more time."; 
    Sleep(3000);
    cout << "\n\n\"There's not much time left! Move it!\"";
    Sleep(2000);
    cout << "\n\nYou go down a set of stairs with him, and at the end, you see a Submarine.";
    Sleep(2000);
    cout << "\n\nHe plants the bombs on each side of the stairs you came from, and you watch him."; 
    Sleep(2000);
    cout << "\n\nYou widen your eyes, when a big loud thud is heard from behind you.";
    PlaySound(TEXT("Sound Effects/thud.wav"), NULL, SND_FILENAME | SND_ASYNC); 
    Sleep(3200);
    cout << "\n\nJACK immediately reacts and turns his head.";
    Sleep(2000);
    cout << "\n\nYou also turn around, and see a giant... person? It doesn't look like the Infected.";
    Sleep(2000);
    cout << "\n\n\"A Tyrant...\" JACK muses, before raising his weapon.";
    Sleep(2000);
    cout<< "\n\nA man wearing civilian clothes lay beside the Tyrant. It seems to have been dragged all the way here.";
    Sleep(2000);
    cout << "\n\nIt's time... for the final boss!\n";

    Enemy &B1enemy10 = B1enemy.top();
    Gamma();
    Gamma_flag = 1;
    track = "DreadFearful";
    battle_start_animation();
    battle_start(player, B1enemy10, consumables, choices);
    if (death_flag == 1){
        return;
    }
    B1enemy.pop();

    cout << "\n\nIt's not enough! There's nothing we can do!";
    Sleep(2000);
    cout << "\n\n\"Nightwing! Get out! Now!\" JACK talks through his comms.";
    Sleep(2000);
    cout << "\n\n\"I can't leave you! I'm waiting!\"";
    Sleep(2000);
    cout << "\n\n\"That's an order!\" JACK shouts.";
    Sleep(2000);
    cout << "\n\nThe system echoes again. Debris is collapsing all around you as tremors start to shake the grouund.";
    Sleep(3000);
    cout << "\n\n\"System Meltdown will begin in 3 minutes. Please evacuate. Please evacuate.\"";
    Sleep(3000);
    cout << "\n\nThe Tyrant before you doesn't stand still, and tries to land a hit on one of you, as you both dodge it barely.";
    Sleep(3000);
    cout << "\n\nMore debris falls, and out of peculiarity, something falls too!";
    Sleep(2000);
    cout << "\n\nYou run to it... and see a Rocket Launcher!";
    Sleep(2000);
    cout << "\n\nYou picked up the Rocket Launcher!";
    Sleep(2000);
    cout << "\n\nYou hoist it on your shoulder, and charge it up.";
    Sleep(2000);
    cout << "\n\nYou shoot it at the Tyrant!";
    PlaySound(TEXT("Sound Effects/rocket.wav"), NULL, SND_FILENAME | SND_ASYNC); 
    cout << "\n\nThe rocket explodes upon impact, and once the smoke clears...";
    Sleep(4200);
    cout << "\n\nThe Tyrant is stil standing! But it has taken significant damage!";
    Sleep(2000);
    cout << "\n\n\"Engage!\" JACK says, shooting.";
    Sleep(2000);
    cout << "\n\nIt's the final battle! Get ready!\n";
    Sleep(3000);

    Enemy &B1enemy11 = B1enemy.top();
    Gamma2();
    Gamma_flag = 0;
    battle_start_animation();
    battle_start(player, B1enemy11, consumables, choices);
    if (death_flag == 1){
        return;
    }

    PlaySound(TEXT("Music/Dread is Fearful.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"System Meltdown will begin in 10...\"";
    Sleep(2000);
    cout << "\n\nWith the Tyrant defeated, you both rush over to the waiting Submarine.";
    Sleep(2000);
    cout << "\n\n\"8...\"";
    Sleep(2000);
    cout << "\n\n\"Punch it!\" JACK says as he gets inside the Submarine with you. The submariner nods, and closes the door remotely.";
    Sleep(3000);
    cout << "\n\n\"5...\"";
    Sleep(2000);
    cout << "\n\nThe Submarine roars into life as it pushes through the water and sinks deeper into the ocean.";
    Sleep(2000);
    cout << "\n\n\"3...\"";
    Sleep(2000);
    cout << "\n\n\"Floor it!\" JACK says, as the Submarine hits many debris falling from the top of the cave.";
    Sleep(2000);
    cout << "\n\n\"1...\"";
    Sleep(3000);
    cout << "\n\n\"I'm trying!\" The Submarine tries its best to move forward, avoiding every obstacle as they try to find the exit.";
    Sleep(2000);
    cout << "\n\n\"0...\"";
    Sleep(2000);
    PlaySound(TEXT("Sound Effects/distant explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nJust as the cave's surging waters roar and the caves collapse, the submarine reaches an opening out to the sea.";
    Sleep(2000);
    cout << "\n\nYou sigh in relief as you reach calm waters. The explosion has died down from below.";
    if (flag_friends == 1){
        Sleep(4000);
        cout << "\n\nJACK offers you a hand.";
        PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
        Sleep(3000);
        cout << "\n\n\"Shake it.\"";
        Sleep(3000);

        do{
            cout << "\n\nYou do:\n1. --> Accept.\n2. --> Decline.\n";
            cin >> dialogue_choice;
            system("CLS");
            if (dialogue_choice == "1"){
                cout << "\n\nYou shake his hand.";
                flag_choice = 1;
            }
            else if (dialogue_choice == "2"){
                cout << "\n\n\"Hm. Not the physical type.\" He says, before giving you his Magnum.";
                cout << "\n\n\"How about something sentimental? No?\" He asks again. You seem to shake your head instinctively.";
                cout << "\n\n\"It's mine?. Huh. You're right about that.";
                cout << "\n\n\"If you do need it, just call it. MAG.\"";
                flag_choice = 1;
            }
            else{
                cout << "\n\nTry again.";
            }

        }while(flag_choice == 0);

        Sleep(5000);
        cout << "\n\n\"What's your plan after this, patient?\" JACK asks.";
        Sleep(5000);
        cout << "\n\n\"Ah, not patient.\" He pauses, before inhaling, throwing a tube of a liquid to the ground.";
        Sleep(5000);
        cout << "\n\nHe crushes it with his boots.";
        Sleep(5000);
        cout << "\n\n\"Extraction successful. Couldn't find the sample. It was probably taken by Dr. Santiago.\" He reports to his radio, before turning to look at you again.";
        Sleep(5000);
        cout << "\n\n\"What's your name?\"";
        Sleep(5000);
        cout << "\n\nYou smile.";
        Sleep(5000);
        cout << "\n\nYou win! You have escaped the zombies!";
        Sleep(5000);
        
    }
    
    else {
        cout << "\n\nYou have escaped the zombies!";
        Sleep(3000);
        cout << "\n\nOr so you thought...";
        Sleep(3000);
        cout << "\n\nJACK and the submariner point their guns at you.";
        Sleep(3000);
        cout << "\n\n\"Sample is secure. Tying up loose ends.\" JACK says on his radio, before shooting you in the head.";
        PlaySound(TEXT("Sound Effects/shotgun.wav"), NULL, SND_FILENAME | SND_ASYNC); 
        Sleep(3000);
        lose(); 
        Sleep(3000);
        cout << "\n\nYou die.";
        Sleep(2000);
        cout << "\n\nIt seemed that JACK didn't trust you. Maybe something needed to be done along the way?";
        Sleep(3000);
    }

    choices.Display_Choices();

    do {
        flag_choice = 0;
        cout << "\nWould you like to try again? [Y/n]: ";
        cin >> choice_again;
        if (choice_again == "Y" || choice_again == "y") {
            flag_choice = 1;
            return;
        } 
                
        else if (choice_again == "N" || choice_again == "n") {
            cout << "Thank you for playing Too Alive to Die!";
            Sleep(4000);
        } 
                
        else {
            cout << "Invalid input. Try again.";
        }

    } while (flag_choice == 0);



}

void scenarioB2 (Player &player, Consumable consumables[], Dialogue_List &choices){

    stack <Enemy> B2enemy;
    B2enemy.push(Enemy("The Titan", 2500, 2500, 40));
    B2enemy.push(Enemy("The Titan", 3000, 3000, 40));
    B2enemy.push(Enemy("Hunter Blob", 600, 600, 30));
    B2enemy.push(Enemy("Hunter Blob", 600, 600, 30));
    B2enemy.push(Enemy("Wretch Blob", 400, 400, 10));
    B2enemy.push(Enemy("Wretch Blob", 400, 400, 10));
    B2enemy.push(Enemy("Wretch Blob", 400, 400, 10));
    B2enemy.push(Enemy("Hunter Blob", 600, 600, 30));
    B2enemy.push(Enemy("Screecher Blob", 400, 400, 25));
    B2enemy.push(Enemy("Infected Blob", 400, 400, 10));
    B2enemy.push(Enemy("Infected Blob", 400, 400, 10));
    B2enemy.push(Enemy("Infected Blob", 400, 400, 10));
    B2enemy.push(Enemy("Screecher", 200, 200, 25));

    Sleep(2000);
    cout << "\n\nYou go around the corner, and run as fast as you can.";
    Sleep(3000);
    cout << "\n\nThe things chase after you, and they are really fast.";
    Sleep(3000);
    cout << "\n\n\"You! Duck!\" You hear a woman's voice in front of you. It's hard to see.";
    Sleep(3000);
    cout << "\n\nYou do as the voice says, and duck.";
    Sleep(3000);
    PlaySound(TEXT("Sound Effects/rocket.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(4000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nYou look behind you as you duck, and you see the things explode.";
    Sleep(3000);
    cout << "\n\n\"Agh. That's a wasted charge. I didn't get to kill the other one.\"";
    Sleep(3000);
    cout << "\n\nShe was right. There was another that was left.";
    Sleep(3000);
    cout << "\n\nYou turn to look at where the voice was coming from. You see a woman in her 20s, wearing a cap, a pair of black shades, and a black tactical uniform.";
    Sleep(5000);
    cout << "\n\nShe takes off her shades. \"You alright? My name is Piper.\"";
    Sleep(3000);
    cout << "\n\nShe rubs the back of her head sheepishly, and asks, \"Uh, could you stall that Screecher for me?\" She asks.";
    Sleep(3000);
    cout << "\n\nWhat?";
    Sleep(3000);
    cout << "\n\n\"This bad boy needs to charge before I can shoot it, so...\"";
    Sleep(3000);
    cout << "\n\nWhat?";
    Sleep(3000);
    cout << "\n\nPiper will now fight beside you!";
    Piper_flag = 1;
    Sleep(3000);

    Enemy &B2enemy1 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy1, consumables, choices);
    if (death_flag == 1){
        return;
    } 
    Sleep(1000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"Wooh! Good job there!\" Piper said, \"I would've ran if you weren't here!\"";
    Sleep(3000);
    cout << "\n\nThis woman seems to be a nutcrack.";
    Sleep(3000);
    cout << "\n\n\"Why are you looking at me like that? You're looking at me as if I'm stupid.\"";
    Sleep(3000);
    cout << "\n\n\"Well, whatever. Looking for a quick way to get out of here?\"";
    Sleep(3000);
    cout << "\n\nYou nod your head.";
    Sleep(3000);
    cout << "\n\n\"Great! I got just the thing!\" She pats the Rocket Launcher on her shoulder.";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. Where are we going?\n2. --> Where are you using that?\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(3000);
            cout << "\n\nA little friend told me that we can just migrate to the moon.";
            Sleep(3000);
            cout << "\n\n\"They already established an outpost there. The problem is nobody has reached out to them.\"";
            Sleep(3500);
            cout << "\n\n\"You know, Infected, and all.\"";
            Sleep(3000);
            cout << "\n\n\"I did get news that they already made farms and stuff over there. They even terraformed the place.\"";
            Sleep(3000);
            cout << "\n\n\"We're all making a move now, now that someone activated the System Meltdown.\" She rolls her eyes.";
            Sleep(4000);
            cout << "\n\n\"Whoever that was, they'll have to find a way out of this place. Even if they get out, the outside world still has Infected.\"";
            Sleep(5000);
            cout << "\n\nShe talks... a lot.";
            Sleep(3000);
        }
        else if (dialogue_choice == "2"){
            flag_choice = 1;
        }
        else{
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\n\"Here.\"";
    Sleep(1000);
    cout << "\n\nShe shoots the Rocket Launcher onto the ground where the Screecher died. It explodes on impact.";
    PlaySound(TEXT("Sound Effects/rocket.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(4000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. --> What the hell did you just do!?\n2. --> That's just reckless!\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Asked what she did.");
            Sleep(2000);
            cout << "\n\n\"I just made a way out! Come on!\"";
            flag_choice = 1;
        }

        else if(dialogue_choice == "2"){   
            choices.addDialogueChoice("Told her she was reckless.");
            Sleep(2000); 
            cout << "\n\n\"Reckless!? More like efficient!\" She sings the efficient part.";
            flag_choice = 1;
        }

        else {
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    Sleep(3000);
    cout << "\n\nShe drags you and jumps down the hole with you. You grimace.";
    Sleep(3000);
    cout << "\n\nYou fall down on your feet with her. The room is really dark. It looks like... a locker room?";
    Sleep(4000);
    cout << "\n\n\"Keep up! Enemies ahead!\"";
    Sleep(3000);
    cout << "\n\nThere are lots of little blobs around the room. They seem to form into different forms of Infected.";
    Sleep(4000);
    cout << "\n\n\"I'm fired up! Let's do this!\"";
    Sleep(3000);
    cout << "\n\nThis woman is really unbearable...";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy2 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy2, consumables, choices);
    if (death_flag == 1){
        return;	
        } 

    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\nOnce the dust settles, you notice that you fell again into the middle of a shooting range room.";
    Sleep(3000);
    cout << "\n\nYou see that most of the target practice are destroyed, and there are lots of blobs in the room, taking different shapes of enemies.";
    Sleep(4000);
    cout << "\n\nYou pick up a Shotgun on one of the shooting desks.";
    Sleep(3000);
    addWeapon(collectedWeapons, "Shotgun");
    shotgun_ammo = 50;
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    cout << "\n\n\"Wanna have some fun? Think of those enemies as shooting targets!\"";
    Sleep(3000);
    cout << "\n\nYou have a bad feeling about her suggestion.";
    Sleep(3000);
    cout << "\n\n\"Come on, do it! Or are you chicken?\"";
    Sleep(3000);
    cout << "\n\nShe then makes chicken noises.";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou do:\n1. --> You think of the Infected as target practice.\n2. --> You just think of them as real Infected.\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Thought of the enemies as target practice.");
            Sleep(3000);
            track = "ShootingRange";
            PlaySound(TEXT("Music/Shooting Range.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            cout << "\n\n\"Hoo baby! I'm feeling the flow! Dance with me!\"";
            Sleep(3000);
            cout << "\n\nShe hits the Cha-cha.";
            Sleep(5000);
            cout << "\n\nIt seems she's having fun.";
            Sleep(3000);
            flag_choice = 1;

        }
        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Thought of the enemies as normal.");
            cout << "\n\n\"Oh, boo hoo. Whatever. Let's just take them out!\"";
            Sleep(3000);
            flag_choice = 1;
        }
        else {
            cout << "\n\nTry again.";
        }
    }while (flag_choice == 0);

    B2enemy.pop();
    Enemy &B2enemy3 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy3, consumables, choices);
    if (death_flag == 1){
        return;	
        } 

    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }                   

    cout << "\n\n\"Let's keep going!\"";
    Sleep(3000);
    cout << "\n\n\"We got this!\"";


    B2enemy.pop();
    Enemy &B2enemy4 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy4, consumables, choices);
    if (death_flag == 1){
        return;	
        } 

    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }                    

    cout << "\n\n\"Ahahaha!\" Piper laughs, \"That was fun!\"";
    Sleep(3000);
    if (track == "ShootingRange"){
        cout << "\n\n\"I told you it would be fun!\"";
        Sleep(3000);
    }
    cout << "\n\nShe suddenly gets serious. \"There may be some supplies here.\"";
    Sleep(3000);
    cout << "\n\n\"Do you need them?\"";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou do:\n1. --> Search around for supplies.\n2. --> Head to the exit as fast as possible.\n";
        cin >> dialogue_choice; 
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Searched for supplies.");
            Sleep(3000);
            cout << "\n\nYou look around for supplies. You find...";
            Sleep(3000);
            cout << "\n\nA Katana!";
            Sleep(3000);
            addWeapon(collectedWeapons, "Katana");
                if (track == "ShootingRange"){
                    PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
                }
                else{
                    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
                }     
            flag_choice = 1;
        }
        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Didn't search for supplies.");
            flag_choice = 1;
        }
        else {
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    Sleep(3000);
    cout << "\n\n\"Alright then! Adios, floor!\"";\
    Sleep(3000);
    cout << "\n\nShe charges up the Rocket Launcher again, and fires it on the floor, making the both of you fall under.";
    Sleep(3500);
    PlaySound(TEXT("Sound Effects/rocket.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(3000);
    cout << "\n\n\"Hey, hey! Screecher Blob! But, huh, weird!\"";
    Sleep(3000);
    cout << "\n\n\"Why are there so many blobs? Did they reproduce too much?\"";
    Sleep(3000);
    cout << "\n\nYou facepalm at how laidback this woman is.";
    Sleep(3000);
    cout << "\n\nYou fight the Screecher Blob!";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy5 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy5, consumables, choices);
    if (death_flag == 1){
        return;	
        } 
    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }                    

    cout << "\n\nYou now find yourselves in the labs. Hanging broken fluorescent lights surround in your wake, and a hole can be seen on the ceiling.";
    Sleep(5000);
    cout << "\n\nThis Piper woman is really crazy.";
    Sleep(3000);
    cout << "\n\n\"System Meltdown in 10 minutes. Please evacuate.\" The system warns.";
    Sleep(3000);
    cout << "\n\n\"Whatcha waiting for!? More Infected Blobs! Careful! One's a Hunter!";
    Sleep(3000);
    cout << "\n\nShe hoists the Rocket Launcher once more, and...";
    Sleep(3000);
    cout << "\n\nYou prepare for a battle of 4!";
    Sleep(3000);
    cout << "\n\nBattle 1 out of 4!";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy6 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy6, consumables, choices);
    if (death_flag == 1){
        return;	
        } 
    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }      

    cout << "\n\n\"Oh, boy! We're forming a party here!\"";
    Sleep(3000);
    cout << "\n\nBattle 2 out of 4!";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy7 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy7, consumables, choices);
    if (death_flag == 1){
        return;	
        } 
    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }     

    cout << "\n\n\"You alright?\" Piper's tone changes. \"Let me patch you up.\"";

    if (player.getCurrentHP() < 100){
        Sleep(3000);
        cout << "\n\nPiper heals " << player.getName() << "! They get healed to full HP!";
        player.heal(player.getMaxHP());
    }
    else {
        Sleep(3000);
        cout << "\n\n\"Ah. You're alright. Let me just give you a First Aid Kit then.\"";
        Sleep(3000);
        cout << "\n\nYou receive a First Aid Kit!";
        PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
        consumables[0].quantity += 1;
        Sleep(3000);
        if (track == "ShootingRange"){
            PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
        }
        else{
            PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
        }     

    }
    Sleep(3000);
    cout << "\n\n\"We'll get through this, alright?\" She assures you, and faces the next Infected with you.";
    Sleep(3000);
    cout << "\n\n\"Bring it on, Suckos!\"";
    Sleep(3000);
    cout << "\n\nBattle 3 out of 4!";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy8 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy8, consumables, choices);
    if (death_flag == 1){
        return;	
        } 
    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }     

    cout << "\n\nYou go down through multiple floors with each Rocket fired. It seems that the facility runs deeper than expected.";
    Sleep(3000);
    cout << "\n\n\"I'm not done having my fun yet!\" Piper exclaims, patting her Rocket Launcher.";
    Sleep(3000);
    cout << "\n\nBattle 4 out of 4!";
    Sleep(3000);

    B2enemy.pop();
    Enemy &B2enemy9 = B2enemy.top();
    battle_start_animation();
    battle_start(player, B2enemy9, consumables, choices);
    if (death_flag == 1){
        return;	
        } 
    if (track == "ShootingRange"){
        PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
    }
    else{
        PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
    }     

    cout << "\n\n\"That's it!\" Piper exclaims as the dust settles.";
    Sleep(3000);
    cout << "\n\nYou see where she's pointing at. It's a giant rocket.";
    Sleep(3000);
    cout << "\n\n\"Beautiful, right!? I made it myself!\"";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou say:\n1. You made it yourself?\n2. What is a rocket doing here anyway?\n3. --> We'll ride that to the moon?\n";
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            Sleep(3000);
            cout << "\n\n\"Yup! This bad boy has enough power to get to the moon in 3 hours!\"";
            Sleep(3000);
            cout << "\n\n\"You know what they say. Early bird gets the worm!\"";
            Sleep(3000);
            cout << "\n\nThat doesn't apply here...";
            Sleep(3000);
        }
        else if (dialogue_choice == "2"){
            Sleep(3000);
            cout << "\n\n\"I was tasked with building it. I'm actually the Tech Lead in this entire facility. Count yourself lucky!\"";
            Sleep(4000);
            cout << "\n\nThat's a bit hard to believe. Then again... She has that Rocket Launcher on her shoulder. Maybe she invented it too.";
            Sleep(4500);
        }
        else if (dialogue_choice == "3"){
            Sleep(3000);
            cout << "\n\n\"Exactly. Now, come with me!\"";
            Sleep(3000);
            flag_choice = 1;

        }
        else {
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);

    cout << "\n\nShe drags your arm and heads nearer to the rocket.";
    Sleep(3000);
    cout << "\n\n\"Everything's prepped and ready! All we need is passengers!\"";
    Sleep(3000);
    cout << "\n\nBefore you could enter the rocket, two Hunter Blobs block your way.";
    Sleep(3000);
    cout << "\n\nThey don't seem to attack.";
    Sleep(3000);
    cout << "\n\nThey gesture their head, asking you to follow them.";
    Sleep(3000);
    cout << "\n\n\"What? You think after killing like, a lot of them, they're just gonna ask us to come with them? I say no to that!\"";
    Sleep(4500);
    cout << "\n\nBut then again... it's weird. They're not hostile. Do you follow them?";
    Sleep(3000);
    do{
        flag_choice = 0;
        cout << "\n\nYou do:\n1. --> Follow the Hunter Blobs.\n2. --> Don't.\n";
        cin >> dialogue_choice;
        system("CLS");

        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Dueled the Cyberdemon.");
            Sleep(3000);
            cout << "\n\n\"Really!? You're comning with them!? Hold on!\"";
            Sleep(3000);
            cout << "\n\nPiper catches up with you as you follow the Hunters.";
            Sleep(3000);
            cout << "\n\nYou have a bad feeling about this.";
            Sleep(3000);
            cout << "\n\nTurns out it wasn't that far. It was just a few meters away from the rocket.";
            Sleep(3000);    
            cout << "\n\nThe Hunter Blobs lead you to a giant devil-like Infected. It looks really calm.";
            Sleep(4000);
            cout << "\n\nIt has a claw as its weapon on its left arm, and an... energy cannon as its right arm!?";
            Sleep(3500);
            cout << "\n\n\"Oh hey! It's a Cyberdemon!\" Piper casually addresses it. \"This guy's name is Titan!\"";
            Sleep(3000);
            cout << "\n\nThe Cyberdemon pats its weapons. It seems to want a duel.";
            Sleep(3000);
            cout << "\n\n\"A battle to the death, huh!? I'll take this dance!\"";
            Sleep(3000);
            cout << "\n\nShe bows at the Cyberdemon, before hoisting the Rocket Launcher onto her shoulder.";
            Sleep(3500);
            cout << "\n\n\"Let's do it!\"";
            Sleep(3000);
            cout << "\n\nIt's the final boss! Get ready!";
            Sleep(3000);

             if (track == "ShootingRange"){
                cout << "\n\n\"Let's party!\n\"" << endl;
                Sleep(3000);
            }
            else{
                track = "DreadFearful";
            }

            Titan();
            B2enemy.pop();
            B2enemy.pop();
            B2enemy.pop();
            B2enemy.pop();
            Enemy &B2enemy13 = B2enemy.top();
            battle_start_animation();
            battle_start(player, B2enemy13, consumables, choices);
            if (death_flag == 1){
                return;	
                } 
            if (track == "ShootingRange"){
                 PlaySound(TEXT("Music/Shooting Range.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else{
                 PlaySound(TEXT("Dread is Fearful.wav"), NULL, SND_FILENAME | SND_ASYNC);    
            } 
        }

        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Didn't duel the Cyberdemon.");
            cout << "\n\n\"That's right, slime faces!";
            Sleep(3000);
            cout << "\n\nThe Hunter Blobs get angry upon hearing this insult. They attack.";
            Sleep(3000);
            cout << "\n\n\"I told you they can't be trusted!\"";
            Sleep(3000);
            B2enemy.pop();
            Enemy &B2enemy10 = B2enemy.top();
            battle_start_animation();
            battle_start(player, B2enemy10, consumables, choices);
            if (death_flag == 1){
                return;	
                } 
            if (track == "ShootingRange"){
                 PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else{
                 PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
            }   

            cout << "\n\nThe other Hunter Blob attacks!";
            Sleep(3000);
            
            B2enemy.pop();
            Enemy &B2enemy11 = B2enemy.top();
            battle_start_animation();
            battle_start(player, B2enemy11, consumables, choices);
            if (death_flag == 1){
                return;	
                } 
            if (track == "ShootingRange"){
                 PlaySound(TEXT("Music/Shooting Range2.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else{
                 PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);   
            } 

            cout << "\n\n\"Gotta hand it to them, they suck!\"";
            Sleep(3000);
            cout << "\n\nBefore you could move another inch, a giant devil-like Infected blocks your way. It looks really angry.";
            Sleep(4000);
            cout << "\n\nIt has a claw as its weapon on its left arm, and an... energy cannon as its right arm!?";
            Sleep(3500);
            cout << "\n\n\"Oh hey! It's a Cyberdemon!\" Piper casually addresses it.";
            Sleep(3000);
            cout << "\n\n\"Let's end this with a BANG, shall we!?\" Piper says, hoisting the Rocket Launcher on her shoulder again.";
            Sleep(4000);
            cout << "\n\nIt's time for the final boss!";
            Sleep(3000);

            if (track == "ShootingRange"){
                cout << "\n\n\"Let's party!\"";
                Sleep(3000);
            }
            else{
                track = "DreadFearful";
            }

            Titan();
            B2enemy.pop();
            Enemy &B2enemy12 = B2enemy.top();
            battle_start_animation();
            battle_start(player, B2enemy12, consumables, choices);
            if (death_flag == 1){
                return;	
                } 
            if (track == "ShootingRange"){
                 PlaySound(TEXT("Music/Shooting Range.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); 
            }
            else{
                 PlaySound(TEXT("Dread is Fearful.wav"), NULL, SND_FILENAME | SND_ASYNC);    
            } 

        }

        else{
            cout << "\n\nTry again.";
        }

    }while (flag_choice == 0);
    
    cout << "\n\n\"System Meltdown will begin in 5 minutes. Please evacuate. Please evacuate.";
    Sleep(3000);
    cout << "\n\nHaving killed the Cyberdemon, you both head into the rocket.";
    Sleep(3000);
    cout << "\n\n\"We have a lot of time to kill, " << player.getName() << ".\"";
    Sleep(3000);
    cout << "\n\nShe pats your back as she turns on the controls.";
    Sleep(3000);
    cout << "\n\n\"It's time for liftoff!\"";
    Sleep(3000);
    cout << "\n\nThe rocket's engines roar, as it immediately takes off. It definitely beats any other rocket that exists today.";
    PlaySound(TEXT("Sound Effects/rocketLaunch.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(4500);
    PlaySound(TEXT("Music/Drive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    cout << "\n\nPiper sighs, and sits down on the pilot seat.";\
    Sleep(5000);
    cout << "\n\nYou sit down on the co-pilot seat.";
    Sleep(5000);
    cout << "\n\n\"Told you we'd be fast.\"";
    Sleep(5000);
    cout << "\n\nShe puts down the Rocket Launcher on the floor.";
    Sleep(5000);
    cout << "\n\n\"Hey... " << player.getName() << "...\"";
    Sleep(5000);
    cout << "\n\n\"This might be the wrong time to ask...";
    Sleep(5000);
    cout << "\n\n\"But...\"";
    Sleep(5000);
    cout << "\n\n\"Are you single?\"";
    Sleep(5000);
    cout << "\n\n\"What? What do you mean how do I know your name? You just ruined the mood!\"";
    Sleep(5000);
    cout << "\n\nYou win! You have escaped the zombies!";
    
   choices.Display_Choices();

    do {
        flag_choice = 0;
        cout << "\nWould you like to try again? [Y/n]: ";
        cin >> choice_again;
        if (choice_again == "Y" || choice_again == "y") {
            flag_choice = 1;
            return;
        } 
                
        else if (choice_again == "N" || choice_again == "n") {
            cout << "Thank you for playing Too Alive to Die!";
            Sleep(4000);
        } 
                
        else {
            cout << "Invalid input. Try again.";
        }

    } while (flag_choice == 0);

}

void scenarioB(Player& player, Consumable consumables[], Dialogue_List &choices){
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(3000);
    cout << "\n\nSuddenly, you hear banging on the window deeper into the corridor. You rush to the window, trying to see what it is that's causing it."; 
    Sleep(2000);
    cout << "\n\nBefore you could even arrive, the glass breaks, letting a shadow inside. It seemed slow, yet it looks like a humanoid figure. You couldn't make out what it is due to how dark it is.";
    Sleep(3000);
    cout << "\n\nAnd then... it makes a churning sound.";
    Sleep(2000);
    PlaySound(TEXT("Sound Effects/zombie_1.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Sleep(2000);

    Enemy enemy ("Dark Humanoid Shadow", 30, 30, 10);

    cout << "\n\nThere's no way out from where you came from! You have to fight whatever that is!" << endl;
    Sleep(1500);
    intro();
    battle_start_animation();
    battle_start(player, enemy, consumables, choices);
        if (death_flag == 1){
        return;
    }
    Sleep(2000);
    PlaySound(TEXT("Sound Effects/Pick Up.wav"), NULL, SND_FILENAME | SND_ASYNC);
    cout << "\n\nYou picked up 5 Handgun Ammo!";
    handgun_ammo = 5;
    Sleep(3000);
    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Sleep(2000);
    cout << "\n\nThe shadow falls to the ground. It twitches, before it screeches really loud.";
    Sleep(2000);
    cout << "\n\nNext thing you know, more of the shadows go towards your position.";
    Sleep(2000);
    cout << "\n\nYou run, going straight. You face three directions, the left, the right, and the front.";
    Sleep(2000);
    cout << "\n\nBut then, many of the shadows are blocking the front and the left!";
    Sleep(2000);
    cout << "\n\nYou decide to run to the right!";
    Sleep(2000);
    cout << "\n\nYou run straight, not turning back, and reach a corner. There is a door in front of you. It probably leads to a room. There's another way to the right.";
    Sleep(2000);
    
    do{
        cout << "\n\nYou do:\n1. Go through the door.\n2. Go right.\n";
        flag_choice = 0;
        cin >> dialogue_choice;
        system("CLS");
        if (dialogue_choice == "1"){
            choices.addDialogueChoice("Went through the door.");
            scenarioB1(player, consumables, choices);
        }
        else if (dialogue_choice == "2"){
            choices.addDialogueChoice("Went right.");
            scenarioB2(player, consumables, choices);
        }
        else {
            cout << "\n\nTry again.";
        }
    }while (flag_choice == 0);
    

    }




int main(){
    
    auto startTime = chrono::steady_clock::now();

    do{
    
    system("CLS");
    srand(time(NULL));

    string playerName;
    HPbar_width = 20;
    give_times = 0;
    handgun_ammo = 0;
    AR15_ammo = 0;
    MP5_ammo = 0;
    shotgun_ammo = 0;
    red9_ammo = 0;
    sniper_ammo = 0;
    grenadeLauncher_ammo = 0;

    turns = 0;
    handgun_upgrade = 0;
    flag_friends = 0;
    Santiago_flag = 0;
    Rena1_flag = 0;
    Rena2_flag = 0;
    JACK1_flag = 0;
    JACK2_flag = 0;
    Piper_flag = 0;
    death_flag = 0;


    Gamma_flag = 0;
    Mastermind_flag = 0;
    

    Consumable consumables[maxConsumables];
    Dialogue_List choices;

    consumables[0] = {"First Aid Kit", 0};
    consumables[1] = {"Bandages", 0};
    consumables[2] = {"Alcohol", 0};


    PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    Player player("Unnamed Patient", 100, 100);

    cout << "You wake up in a small room surrounded by white walls, a bright lightbulb hanging from above.";
    Sleep(2000);
    cout << "\n\nYou hear an echo of a voice, \"System Meltdown has begun. Please evacuate. System Meltdown has begun. Please evacuate.\"";
    Sleep(2000);
    cout << "\n\nYou assess yourself, and find yourself wearing a hospital gown. You sit up straight from the bed, and look around you.";
    
    do {

    cout << "\n\nYou then remember your name: ";
    cin >> playerName;
    player.setName(playerName);
    cout << "\nIs " << player.getName() << " your name? [Y/n]: ";
    cin >> choice_confirm;
    system("CLS");

    if (choice_confirm == "y" || choice_confirm == "Y"){
        cout << "\nYou remember your name. It's " << player.getName() << ".";
        flag_confirm_name = 1;

    }

    else if (choice_confirm == "n" || choice_confirm == "N"){
        cout << "\nWhat is your name?";
    }

    else {
        cout << "Wrong input. Try again.";
        flag_confirm_name = 0;
    }

    }while (choice_confirm == "n"  || choice_confirm == "N" || flag_confirm_name == 0);



    do {
        string ClassName;
        flag_choice = 0;
        Sleep(2000);
        cout << "\n\nYou feel something shine inside you, a power. A choice. A path. You are chosen to choose:\n";
        Sleep(4000);
        cout << "\n1. Abundance - You start with +50% more Max HP.";
        cout << "\n2. Gunslinger - Your Ranged Weapons will deal 15 more damage.";
        cout << "\n3. Perceiver - Your Melee Weapons will deal 3 times more damage on Crit.";
        Sleep(2000);
        cout << "\n\nWhat will you choose?\n";
        cin >> ClassName;
        system("CLS");

        if (ClassName == "1" || ClassName == "Abundance" || ClassName == "abundance"){
            cout << "\n\nAbundance is the start of life, before it extinguishes. It prospers and lives, until it withers and dies.";
            player.setClass("Abundance");
            choices.addDialogueChoice("Abundance Class");
            player.setMaxHP(150);
            player.heal(150);
            flag_choice = 1;            
        }

        else if(ClassName == "2" || ClassName == "Gunslinger" || ClassName == "gunslinger"){
            cout << "\n\nGunslingers have a way of life. Shoot it, and it dies. Simple as that.";
            player.setClass ("Gunslinger");
            choices.addDialogueChoice("Gunslinger Class");
            flag_choice = 1;            
        }

        else if (ClassName == "3" || ClassName == "Perceiver" || ClassName == "perceiver"){
            cout << "\n\nPerceivers are natural-born weakness finders. They know where to hit where it hurts.";
            player.setClass ("Perceiver");
            choices.addDialogueChoice("Perceiver Class");
            flag_choice = 1;
        }

        else{
            cout << "\n\nTry again.";
            flag_choice = 0;
        }




    }while (flag_choice == 0);

    Sleep(2000);
    cout << "\n\nThe door leading out of the room seems to be open. A piece of paper is on the dresser next to your bed. What could be out there, and why are you here?";
    Sleep(4000);
    cout << "\n\n(*A story choice with a preceding \"-->\" will advance the story.)";
    cout << "\n\nYou decide to:";
    Sleep(1000);

    do{
    cout << "\n1. Read the piece of paper.\n2. --> Get out of the room.\n3. Peek out." << endl;
    cin >> dialogue_choice;
    system("CLS");
    Sleep(1500);

    if (dialogue_choice == "1"){
        cout << "\nYou pick up the piece of paper and read it. It's just scribbles. You flip it the other way, and now it reads, in full big letters, \"RUN FOR YOUR LIFE\"" << endl;        
        }

    else if (dialogue_choice == "2"){
        cout << "\nYou leave the room. There was nothing else to do anyway. Outside, it is really dark. You see a long corridor full of many rooms like yours. There's blood spilled everywhere, and the smell is horrendous. The blood seems dry, like it has been there for a while. Something tells you that something is wrong with this place." << endl;
        flag_choice = 1;
    }
    else if (dialogue_choice == "3"){
        cout << "\nYou peek out. It is really dark. You see a corridor full of many rooms like yours. Not to mention, the smell is rancid. Something tells you that something is wrong with this place." << endl;
    }

    else {
        flag_choice = 0;
        cout << "\nTry again.\n";
    }

    }while (dialogue_choice == "1" || dialogue_choice == "3" || flag_choice == 0);

    Sleep(4000);
    cout << "\nYou look around the corridors once more. It's really quiet. In one room, you see a body, lying on its belly, limp on the floor. A pool of dry blood seems to have oozed from the body.";
    Sleep(5000);
    cout << "\n\nYou decide to:";
    Sleep(1000);


    
    do{
        cout << "\n1. --> Investigate the body.\n2. --> Continue walking through the corridor.\n";
        cin >> dialogue_choice;
        system("CLS");
        Sleep(2000);
        flag_choice = 0;
            if (dialogue_choice  == "1"){
                choices.addDialogueChoice("Investigated the body.");
                cout << "\nThe body seems... dead. It was obvious, with the way it's lying down on its belly. Its gender is almost impossible to speculate, as its hair is long, but its body build, masculine.";
                Sleep(5000);
                cout << "\n\nYour eyes catch a glimpse of the body's hand. It's a handgun. You grab it immediately, and instinctively back away. Whatever caused all of this must be dangerous.";
                addWeapon (collectedWeapons, "Handgun");
                PlaySound(TEXT("Music/Looming Dread.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
                handgun_ammo = 4;
                flag_choice = 1;
                scenarioA(player, consumables, choices);
            }

            else if (dialogue_choice == "2"){
                choices.addDialogueChoice("Continued walking through the corridor.");
                cout << "\nWhatever's in that room, it's too big of a risk to get. It's like you felt that something was going to happen the moment you set foot in that room.";
                Sleep(2000);
                cout << "\n\nYou continue deeper into the corridor. You find a bat, lying on the ground. You decide to take it. Feels sturdy enough.";
                addWeapon (collectedWeapons, "Bat");
                flag_choice = 1;
                scenarioB(player, consumables, choices);
            }

            else {
                cout << "\nTry again.\n";
            }
    }while (flag_choice == 0);

}while (choice_again == "Y" || choice_again == "y");

auto endTime = chrono::steady_clock::now();
auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
cout << "\n\nExecution Time: " << duration.count() << " s" << endl;


return 0;

}