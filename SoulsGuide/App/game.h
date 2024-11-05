#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QPainter>
#include <QVector>
#include <QMessageBox>
#include <QApplication>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>

#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "trap.h"
#include "flag.h"
#include "boss.h"
#include "powerup.h"

/**
* @brief The Game class is the model of the game.
* It creates and manages the levels and their functioning.
* @author GIGNOUX Victor
* @version 1
* @date 5 June 2024
*/
class Game : public QObject
{
    Q_OBJECT

public:
    /**
    * @brief The destructor of the Game class
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    */
    explicit Game(QObject *parent = nullptr);
    /**
    * @brief The destructor to delete a Game
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Game();
    /**
    * @brief Setup a new Game with his Timer, his Player and his Gameloop
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    */
    virtual void setGame();
    /**
    * @brief Delete the elements of the levels and setup a new game
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    */
    void deleteLevel();
    /**
    * @brief Delete the elements of the previous level and go to the one given as parametre
    * @param level, type : int, level that the function will load
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    */
    void goToLevel(int level);
    /**
    * @brief Load a background sent as a parameter in a QString, keep in mind that all the maps
    *        are defined in a const string in the typeDef.h
    * @param a background file in a string (find in typeDef.h)
    * @return a QPixmap of the background image
    * @author BOURDY Axel
    * @date 06/06/2024
    * @version Version 1
    */
    QString loadBackground(string background);
    /**
    * @brief Catches an exception sent as a parameter in a function
    *        that tries to run/read a file
    * @param an exception sent from a try catch function
    * @author BOURDY Axel
    * @date 06/06/2024
    * @version Version 1
    */
    void fileReaderError(exception &e);
    /**
    * @brief This method return the itsPlayer value
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsPlayer, type Player* : the Player of the game
    */
    Player *getItsPlayer() const;
    /**
    * @brief This method return the itsTimer value
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsTimer, type QTimer* : the Timer of the game
    */
    QTimer *getItsTimer() const;
    /**
    * @brief This method return the itsPopupError value
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsPopupError, type QMessageBox* : the popup error of the game
    */
    QMessageBox *getItsPopupError() const;
    /**
    * @brief This method return the itsBoss value
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsBoss, type Boss* : the Boss of the game
    */
    Boss *getItsBoss() const;
    /**
    * @brief This method return the itsPlatforms vector
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsPlatforms, type QVector<Platform> : the Platforms of the game
    */
    QVector<Platform> getItsPlatforms() const;
    /**
    * @brief This method return the itsEnemies vector
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsEnemies, type QVector<Enemy> : the Enemies of the game
    */
    QVector<Enemy*> getItsEnemies() const;
    /**
    * @brief This method return the itsTraps vector
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsTraps, type QVector<Trap> : the Traps of the game
    */
    QVector<Trap> getItsTraps() const;
    /**
    * @brief This method return the itsPowerUps vector
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @return itsPowerUps, type QVector<PowerUp> : the Power Ups of the game
    */
    QVector<PowerUp> getItsPowerUps() const;
    /**
    * @brief This method return the itsFirstFlag value
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @return itsFirstFlag, type Flag : the Flag of the game
    */
    Flag getItsFirstFlag() const;
    /**
     * @brief Get the elapsed time in the game in seconds
     * @author PARDOEN James
     * @version 2
     * @date 6 June 2024
     * @return The elapsed time in seconds
     */
    int getItsElapsedTime() const;
    /**
     * @brief Set the elapsed time in the game in seconds
     * @author PARDOEN James
     * @version 2
     * @date 6 June 2024
     * @param time The elapsed time in seconds
     */
    void setItsElapsedTime(int time);
    /**
     * @brief get the current level the player is at.
     * @author BOURDY Axel
     * @version 2
     * @date 7 June 2024
     */
    int getItsCurrentLevel() const;
    /**
     * @brief set the current level the player is at.
     * @author BOURDY Axel
     * @version 2
     * @date 7 June 2024
     */
    void setItsCurrentLevel(const int currentLevel);
    /**
     * @brief get whether or not the player is still alive
     * @author BOURDY Axel
     * @version 2
     * @date 10 June 2024
     */
    bool getIsPlayerAlive() const;
    /**
     * @brief set whether or not the player is still alive
     * @author BOURDY Axel
     * @param a boolean of the player's status.
     *        False = dead
     *        True = Alive
     * @version 2
     * @date 10 June 2024
     */
    void setIsPlayerAlive(const bool playerStatus);
    /**
     * @brief set message display duration
     * @author PARDOEN James
     * @param an int for duration in millisecond
     * @version 2
     * @date 10 June 2024
     */
    void setItsDisplayDuration(const int duration);
    /**
     * @brief get message display duration
     * @author PARDOEN James
     * @param an int for duration in millisecond
     * @version 2
     * @date 10 June 2024
     */
    int getItsDisplayDuration();
    /**
     * @brief set label message
     * @author PARDOEN James
     * @param a string of the message
     * @version 2
     * @date 10 June 2024
     */
    void setItsDisplayMessage(const std::string message);
    /**
     * @brief get label message
     * @author PARDOEN James
     * @version 2
     * @date 10 June 2024
     */
    std::string getItsDisplayMessage();
    /**
     * @brief pause the game or not (depends on the bool in the parameter)
     * @param the new game status:
     *        true = pause
     *        false = continue
     * @author BOURDY Axel
     * @version 2
     * @date 11 June 2024
     */
    void pauseGame(const bool newGameStatus);
    /**
    * @brief This method read a level from a CSV file
    * and add the data into variables
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    * @param aLevel, type string : the level CSV file
    */
    void readLevel(string aLevel);

    /**
     * @brief Get the isBossDefeated attribute
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @return isBossDefeated, type bool : if the boss is defeated
     */
    bool getIsBossDefeated() const;
    /**
     * @brief Set the isBossDefeated attribute
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @param the new value of the isBossDefeated
     */
    void setIsBossDefeated(bool newIsBossDefeated);

    virtual void gameLoop();

private slots:
    /**
    * @brief This method initialize the game loop.
    * It constantly updates the data of the different elements of the game.
    * It also check for event such as death of the player or end of the level
    * @author GIGNOUX Victor
    * @version 1
    * @date 5 June 2024
    */
    void gameLoopSlot();  // Slot to update the game state
    /**
    * @brief Kill the app once it is triggered
    * Used whenever the sprites cannot be fine
    * @author BOURDY Axel
    * @date 06/06/2024
    * @version Version 1
    */
    void killApp();

protected:
    /** The Timer of the game */
    QTimer * itsTimer;
    /** The Player of the game */
    Player * itsPlayer;
    /** The Boss of the game */
    Boss * itsBoss;
    /** The vector of all the PLatforms of the game */
    QVector<Platform> itsPlatforms;
    /** The vector of all the Enemies of the game */
    QVector<Enemy*> itsEnemies;
    /** The vector of all the Traps of the game */
    QVector<Trap> itsTraps;
    /** The vector of the power ups of the game */
    QVector<PowerUp> itsPowerUps;
    /** The Flag of the game */
    Flag    itsFirstFlag;
    /** A message box when any error is catch*/
    QMessageBox * itsPopUpError;
    /** The position where the boss spawns */
    QPoint itsBossSpawnPoint;
    /** current level the player is on */
    int itsCurrentLevel = 1;
    /** elapsed time in game in milliseconds*/
    int itsElapsedTime;
    /** the current status of the play*/
    bool isPlayerAlive;
    /** amount of time the message will be displayed in the indication label**/
    int itsDisplayDuration;
    /** content of the indication label */
    string itsDisplayMessage;
    /** when the boss is defeated */
    bool isBossDefeated = false;
};

#endif // GAME_H
