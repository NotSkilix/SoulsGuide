#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <fstream>
#include <iostream>
#include <QMovie>
#include <QLayoutItem>

#include "game.h"
#include "typeDef.h"
#include "gamebossfight.h"

/**
* @brief The GameWindow class is the view and controller of the game.
* It display the level's elements and manages the control of the player
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    /**
    * @brief The constructor to initialize a Game window
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param parent, type QWidget* : the parent of the current widget
    */
    explicit GameWindow(QWidget *parent = nullptr);
    /**
    * @brief The destructor of the GameWindow class
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    ~GameWindow();
    /**
    * @brief Catches an exception sent as a parameter in a function
    *        that tries to run/read a background or music file
    * @param an exception sent from a try catch function
    * @author GOBBE Paul
    * @date 11/06/2024
    * @version Version 1
    */
    void backgroundAndMusicError(const exception &e);

protected:
    /**
    * @brief The event to manage when a key (Z, Q or D) is pressed
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param event, type QKeyEvent* : an event who contains information about the key press
    */
    void keyPressEvent(QKeyEvent *event) override;
    /**
    * @brief The event to manage when a key (Q or D) is released
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param event, type QKeyEvent* : an event who contains information about the key release
    */
    void keyReleaseEvent(QKeyEvent *event) override;
    /**
    * @brief The event to handle when the mouse is clicked
    * @author GOBBE Paul
    * @version 1
    * @date 10 June 2024
    * @param event, type QKeyEvent* : an event who contains information about the mouse click
    */
    void mousePressEvent(QMouseEvent *event) override;
    /**
    * @brief The event to manage when the mouse click is released
    * @author GOBBE Paul
    * @version 1
    * @date 10 June 2024
    * @param event, type QKeyEvent* : an event who contains information about the mouse click
    */
    void mouseReleaseEvent(QMouseEvent *event) override;
    /**
    * @brief The event to paint and display all the elements of the game (player, platforms, ...)
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param event, type QPaintEvent* : an event who can paint element such as rectangle for example
    */
    void paintEvent(QPaintEvent *event) override;
    /**
    * @brief The music reader for the GameWindow class, read a music depending
    *        on the level sent in the parameters.
    * @param the current level in the game.
    * @author BOURDY Axel
    * @version 2
    * @date 6 June 2024
    */
    void musicAndBackgroundLoader(const int currentLevel);
    /**
    * @brief Display the interface required to be displayed.
    * @param the required interface (enum)
    * @author BOURDY Axel
    * @version 2
    * @date 8 June 2024
    */
    void displayMenu(interface anInterface);
    /**
    * @brief Realize actions to the buttons depending on the menu.
    *        Specific menu: create the required button and push_back() to itsButtons vector
    *        new menu: delete the buttons stored in the vector to create new one for another menu
    * @param the required interface (enum)
    * @author BOURDY Axel
    * @version 2
    * @date 8 June 2024
    */
    void setupInterface(interface anInterface);

private slots:
    /**
    * @brief Update the timer display with the elapsed time in minutes and seconds
    * @author PARDOEN James
    * @date 06/06/2024
    * @version Version 2
    */
    void updateTimer();
    /**
    * @brief The event to change frames of the animations
    * @author GIGNOUX Victor
    * @version 2
    * @date 4 June 2024
    */
    void animationsManager();
    /**
    * @brief a slots that manage when the music status changed and by so
    *        create a loop of the music when its over.
    * @param The current media status of the mediaPlayer (itsMusicPlayer*)
    * @author BOURDY Axel
    * @version 2
    * @date 7 June 2024
    */
    void musicStatusChanged(QMediaPlayer::MediaStatus currentStatus);
    /**
    * @brief a slot that get when the level changes and update it.
    * @author BOURDY Axel
    * @version 2
    * @date 7 June 2024
    */
    void levelUpdate();
    /**
    * @brief a slot to start the game
    * @author BOURDY Axel
    * @version 2
    * @date 9 June 2024
    */
    void playGame();
    /**
    * @brief a slot to close the game
    * @author BOURDY Axel
    * @version 2
    * @date 9 June 2024
    */
    void closeGame();
    /**
    * @brief a slot to get to the main menu
    * @author BOURDY Axel
    * @version 2
    * @date 9 June 2024
    */
    void mainMenu();
    /**
    * @brief a slot to get to the leader board
    * @author GIGNOUX Victor
    * @version 2
    * @date 10 June 2024
    */
    void displayLeaderBoard();
    /**
    * @brief a slot to display the death screen once the player dies
    * @author BOURDY Axel
    * @version 2
    * @date 10 June 2024
    */
    void playerStatusUpdate();
    /**
    * @brief a slot to resume the game after it got paused
    * @author BOURDY Axel
    * @version 2
    * @date 10 June 2024
    */
    void resumeGame();
    /**
    * @brief a slot to play again after death
    * @author BOURDY Axel
    * @version 2
    * @date 10 June 2024
    */
    void playAgain();

private:
    /**
    * @brief Clear every display on the window
    * @author GIGNOUX Victor
    * @version 2
    * @date 10 June 2024
    */
    void clearScreen();

private:
    /** the Game who is display in the GameWindow. It contains all the element of the game */
    Game * itsGame;
    /** the Timer of the GameWindow */
    QTimer * itsTimer;                  // Timer for the game loop
    /** The timer used for the animations */
    QTimer * itsAnimationTimer;
    /** the Background of the Game */
    QPixmap itsBackground;             // QPixmap for the backgrounds of the levels
    /** The music player of the game that read the files loaded and manage it */
    QMediaPlayer * itsMusicPlayer;
    /** The audio and volume manager of the game */
    QAudioOutput * itsAudio;
    /** label responsible for the display of the timer */
    QLabel *itsTimerLabel;
    /** Int of the current music playing*/
    int itsMusicPlaying;
    /** The current interface displayed on the player's screen*/
    interface itsCurrentInterface;
    /** The first button of the game*/
    QPushButton * itsFirstButton;
    /** The second button of the game*/
    QPushButton * itsSecondButton;
    /** The third button of the game*/
    QPushButton * itsThirdButton;
    /** its grid layout*/
    QGridLayout * itsGrid;
    /** the text label*/
    QLabel * itsLabel;
    /** the line edit to enter the player's name */
    QLineEdit * itsLineEdit;
    /** The gif playing in the background of the main menu*/
    QMovie * itsBackgroundGif;
    /** The gif storage used to display on the screen */
    QLabel * itsMovieStorage;
    /** Indication label */
    QLabel * itsIndicationLabel;
    /** Label to display the amount of armor on player*/
    QLabel * itsArmorCount;
    /** Label to display the count of golden buffs on player*/
    QLabel * itsGoldenBuffCount;
};

#endif // GAMEWINDOW_H
