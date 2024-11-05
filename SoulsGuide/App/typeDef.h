#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QPixmap>
#include <iostream>
using namespace std;

// Global:
/** The window height dimension (value in pixel) */
const int WINDOW_HEIGHT = 740;
/** The window width dimension (value in pixel) */
const int WINDOW_WIDTH = 1260;
/** The gravity in the game.
 *  This impacts the physics of the game, for example the player jumping */
const float GRAVITY = 0.7;
const int POWERUP_TIME = 6; // in seconds
const int FPS = 60;

// Boss:
/** The Boss height value */
const int BOSS_HEIGHT = 300;
/** The Boss width value */
const int BOSS_WIDTH = 250;
/** The Boss height value */
const int BOSSFIGHT_BOSS_HEIGHT = 200;
/** The Boss width value */
const int BOSSFIGHT_BOSS_WIDTH = 150;

// Player:
/** The Player height value */
const int PLAYER_HEIGHT = 80;
/** The Player width value */
const int PLAYER_WIDTH = 170;
/** The Player height value by taking sake power-up */
const int SAKE_PLAYER_HEIGHT = 100;
/** The Player width value by taking sake power-up */
const int SAKE_PLAYER_WIDTH = 190;

// Power Up
enum PowerUpType
{
    SalmonSushi,
    WoodenSandals,
    Sake
};
/** defines how long the iframes of the armor lasts in 16th of a second*/
const int ARMOR_DURATION = 36;

//Enemy
enum EnemyType{
    Skully,
    Phantom,
    Eye,
    Gold
};

// Level
/** The name of level 1 CSV file and his location */
const string LEVEL1 = "../App/level_1.csv";
/** The name of level 2 CSV file and his location */
const string LEVEL2 = "../App/level_2.csv";
/** The name of level 3 CSV file and his location */
const string LEVEL3 = "../App/level_3.csv";
/** The name of level 3 CSV file and his location */
const string LEVEL4 = "../App/level_4.csv";

// Backgrounds
const string BACKGROUND_MAINMENU = "../game_ressources/background_mainMenu.png";
const string BACKGROUND_DEATHSCREEN = "../game_ressources/background_deathscreen.png";
const string BACKGROUND_LEVEL1 = "../game_ressources/background_level1.png";
const string BACKGROUND_LEVEL2 = "../game_ressources/background_level2.png";
const string BACKGROUND_LEVEL3 = "../game_ressources/background_level3.png";
const string BACKGROUND_LEVEL4 = "../game_ressources/background_level4.png";
const string BACKGROUND_DEFAULT = BACKGROUND_LEVEL1;


// Musics
const string MUSIC_MAINMENU = "../game_ressources/music_mainMenu.wav";
const string MUSIC_LEVEL1 = "../game_ressources/music_level1.mp3";
const string MUSIC_LEVEL2 = "../game_ressources/music_level2.wav"; // MUSIC SET TO MAINMENU UNTIL WE HAVE THE RIGHT ONE
const string MUSIC_LEVEL3 = "../game_ressources/music_level3.mp3";
const string MUSIC_BOSSFIGHT = "../game_ressources/music_level666.wav"; // MUSIC SET TO MAINMENU UNTIL WE HAVE THE RIGHT ONE
const string MUSIC_DEFAULT = MUSIC_MAINMENU;

//Game Logo
//string GAMELOGO = "../game_ressources/gameLogo.png";

/** @brief The Frame contains an image of the animation and the next one */
struct Frame{
    QPixmap image;
    Frame * next;
};

/** @brief The Animation is a linked list that contains Frame */
struct Animation{
    Frame * first;
};

/** The interface enumeration */
enum interface
{
    NONE, // Used to delete the interface
    GAME,
    MAINMENU,
    DEATHSCREEN,
    LEADERBOARD,
    PAUSED
};

#endif // TYPEDEF_H
