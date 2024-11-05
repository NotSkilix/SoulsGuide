#ifndef PLAYER_H
#define PLAYER_H

#include <QRect>
#include <QVector>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QDebug>

#include "platform.h"
#include "enemy.h"
#include "typeDef.h"
#include "trap.h"
#include "powerup.h"

/**
* @brief The Player class implements the game's Player entity
* and describes its behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class Player
{
private:
    /** a hitbox which detects the bottom collision */
    QRect itsCollisionPointBottom;
    /** a hitbox which detects the right collision */
    QRect itsCollisionPointRight;
    /** a hitbox which detects the left collision */
    QRect itsCollisionPointLeft;
    /** a hitbox which detects the top collision */
    QRect itsCollisionPointTop;

    /** Indicates if there is a collision at the right */
    bool isCollidingRight = false;
    /** Indicates if there is a collision at the left */
    bool isCollidingLeft = false;
    /** Indicates if there is a collision at the top */
    bool isCollidingTop = false;
    /** Indicates if there is a collision at the bottom */
    bool isCollidingBottom = false;

    /** Indicates if there is a collision with an Enemy */
    bool isCollidingEnemy = false;
    /** Indicates if there is a collision with a Trap */
    bool isCollidingTrap = false;
    /** Indicates if there is a collision with the boss */
    bool isCollidingBoss = false;

    /** Indicates if the player is attacking on the left */
    bool isAttackingLeft = false;
    /** Indicates if the player is attacking on the right */
    bool isAttackingRight = false;

    /** flags and timers for power up */
    int SalmonSushiTimer;
    int SakeTimer;
    int WoodenSandalsTimer;

    /** The Player's position and size */
    QRect itsRect;

    /** List of platforms in the game */
    QVector<Platform> itsPlatforms;
    /** List of enemies in the game */
    QVector<Enemy*> itsEnemies;
    /** List of traps in the game */
    QVector<Trap> itsTraps;
    /** list of power ups pointers in the game */
    QVector<PowerUp> itsPowerUps;
    /** animations of the player */
    QVector<Animation*> itsAnimations;

    /** The attack hitbox on the right*/
    QRect itsAttackHitboxRight;
    /** The attack hitbox on the left*/
    QRect itsAttackHitboxLeft;

    /** Speed of the Player's movement */
    int itsSpeed;
    /** Vertical speed for jumping and gravity */
    float itsVerticalVelocity;
    /** If the player is pressing Q */
    bool isPressingQ = false;
    /** If the player is pressing D */
    bool isPressingD = false;
    /** Track if moving left */
    bool isMovingLeft = false;
    /** Track if moving right */
    bool isMovingRight = false;
    /** When the player is facing left */
    bool isFacingLeft = false;
    /** when the player is facing right */
    bool isFacingRight = true;
    /** when the player is attacking */
    bool isAttacking = false;
    /** when the player has jump key pressed */
    bool isJumping = false;
    /** when the player kill an enemy */
    bool isEnemyKill = false;
    /** number of equipped armors for the player*/
    int itsArmorCount = 0;
    /** duration of "iframes" the armor gives on contact*/
    int itsArmorDuration = 0;
    /** number of golden buffs the player has*/
    int itsGoldenBuffCount = 0;



    /** the current frame of the player */
    Frame * itsCurrentFrame;
    /** the current frame of the secondary animations, can be null */
    Frame * itsSecondaryFrame;
    /** the index of the current animation */
    int itsAnimationIndex = -1;
    /** the index of the secondary current animation */
    int itsSecondaryAnimationIndex = -1;

public:
    /**
    * @brief The default constructor of the Player
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    Player();
    /**
    * @brief The constructor to create a Player with spawn coordinates
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param spawn, type QPoint : coordinates of the Player's spawn
    */
    Player(QPoint spawn);
    /**
    * @brief The destructor to delete a player
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Player();
    /**
    * @brief This method allow the player to jump if he is on the ground
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    void jump();

    /**
    * @brief This method update function for game loop integration.
    * It update the player's position based on gravity and current vertical velocity
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    void update();

    /**
    * @brief This method update player's vision of Traps
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param traps, type QVector<Trap> : The list of the Game's Traps
    */
    void updateTrapData(QVector<Trap> traps);

    /**
    * @brief This method update player's vision of Platforms
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param platforms, type QVector<Platform> : The list of the Game's Platforms
    */
    void updatePlatformData(QVector<Platform> platforms);

    /**
    * @brief This method update player's vision of Enemies
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param enemies, type QVector<Enemy> : The list of the Game's Enemies
    */
    void updateEnemyData(QVector<Enemy*> enemies);

    /**
    * @brief This method updates player's vision of power ups
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param enemies, type QVector<PowerUp> : The list of the Game's power ups
    */
    void updatePowerUpData(QVector<PowerUp> powerUps);

    /**
    * @brief This method switch the current frame to the next one
    * @author GIGNOUX Victor
    * @version 2
    * @date 7 June 2024
    */
    void playAnimation();

    /**
    * @brief This method change the current animation
    * @author GIGNOUX Victor
    * @version 2
    * @date 7 June 2024
    * @param index, type int : the index of the animation wanted
    */
    void setItsCurrentFrame(int index);

    /**
    * @brief This method change the secondary current animation
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    * @param index, type int : the index of the secondary animation wanted
    */
    void setItsSecondaryCurrentFrame(int index);

    /**
    * @brief This method load the images needed for the animations in a vector<Animation>
    * @author GIGNOUX Victor
    * @version 2
    * @date 7 June 2024
    * @param animationName, type QString : the name of the animation needed to find the images
    * @param frameNumber, type int : the number of frame this animation contains
    */
    void loadAnimation(QString animationName, int frameNumber);

    /**
    * @brief This method gives access to the current frame of the player
    * @author GIGNOUX Victor
    * @version 2
    * @date 7 June 2024
    * @return itsCurrentFrame, type QPixmap : the current frame of the player
    */
    Frame * getItsCurrentFrame() const;

    /**
    * @brief This method gives access to the secondary current frame of the player
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    * @return itsSecondaryFrame, type QPixmap : the secondary current frame of the player
    */
    Frame * getItsSecondaryFrame() const;

    /**
    * @brief This method return the itsCollisionPointBottom value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsCollisionPointBottom, type QRect : tell if the Player's hitbox detects the bottom collision
    */
    QRect getItsCollisionPointBottom() const;
    /**
    * @brief This method return the itsCollisionPointRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsCollisionPointRight, type QRect : tell if the Player's hitbox detects the right collision
    */
    QRect getItsCollisionPointRight() const;
    /**
    * @brief This method return the itsCollisionPointLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsCollisionPointLeft, type QRect : tell if the Player's hitbox detects the left collision
    */
    QRect getItsCollisionPointLeft() const;
    /**
    * @brief This method return the itsCollisionPointTop value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsCollisionPointTop, type QRect : tell if the Player's hitbox detects the top collision
    */
    QRect getItsCollisionPointTop() const;
    /**
    * @brief This method return the isCollidingRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingRight, type bool : tell if the Player's is colliding on the right
    */
    bool getIsCollidingRight() const;
    /**
    * @brief This method return the isCollidingLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingLeft, type bool : tell if the Player's is colliding on the left
    */
    bool getIsCollidingLeft() const;
    /**
    * @brief This method return the isCollidingTop value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingTop, type bool : tell if the Player's is colliding on the top
    */
    bool getIsCollidingTop() const;
    /**
    * @brief This method return the isCollidingBottom value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingBottom, type bool : tell if the Player's is colliding on the bottom
    */
    bool getIsCollidingBottom() const;
    /**
    * @brief This method return the isCollidingEnemy value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingEnemy, type bool : tell if the Player's is colliding on an Enemy
    */
    bool getIsCollidingEnemy() const;
    /**
    * @brief This method return the isCollidingTrap value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isCollidingTrap, type bool : tell if the Player's is colliding on a Trap
    */
    bool getIsCollidingTrap() const;
    /**
    * @brief This method return the isEnemyKill value
    * @author GOBBE Paul
    * @version 1
    * @date 10 June 2024
    * @return isEnemyKill, type bool : tell if the Player kill an enemy
    */
    bool getIsEnemyKill() const;
    /**
    * @brief This method return the itsRect value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type QRect : the Player's position and size
    */
    QRect getItsRect() const;
    /**
    * @brief This method return the itsPlatforms value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsPlatforms, type QVector<Platform> : the list of platforms in the game
    */
    QVector<Platform> getItsPlatforms() const;
    /**
    * @brief This method return the itsEnemies value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsEnemies, type QVector<Enemy> : the list of enemies in the game
    */
    QVector<Enemy*> getItsEnemies() const;
    /**
    * @brief This method return the itsTraps value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsTraps, type QVector<Trap> : the list of traps in the game
    */
    QVector<Trap> getItsTraps() const;
    /**
    * @brief This method return the itsPowerUps vector
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @return itsPowerUps, type QVector<PowerUp> : the list of power ups in the game
    */
    QVector<PowerUp> getItsPowerUps() const;
    /**
    * @brief This method return the itsSpeed value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsSpeed, type int : the Player's movement speed
    */
    int getItsSpeed() const;
    /**
    * @brief This method return the itsVerticalVelocity value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsVerticalVelocity, type float : the vertical speed for jumping and gravity
    */
    float getItsVerticalVelocity() const;
    /**
    * @brief This method return the isMovingLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isMovingLeft, type bool : indicates if the Player is moving left
    */
    bool getIsMovingLeft() const;
    /**
    * @brief This method return the isMovingRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isMovingRight, type bool : indicates if the Player is moving right
    */
    bool getIsMovingRight() const;

    /**
     * @brief Getter for SalmonSushiTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @return SalmonSushiTimer, type int : the current value of the Salmon Sushi Timer
     */
    int getSalmonSushiTimer() const;
    /**
     * @brief Setter for SalmonSushiTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @param timer, type int : the value to set the Salmon Sushi Timer to
     */
    void setSalmonSushiTimer(int timer);
    /**
     * @brief Getter for SakeTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @return SakeTimer, type int : the current value of the Sake Timer
     */
    int getSakeTimer() const;
    /**
    * @brief This method change the itsCollisionPointBottom value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsCollisionPointBottom, type QRect& : the new bottom hitbox
    */
    void setItsCollisionPointBottom(const QRect &newItsCollisionPointBottom);
    /**
    * @brief This method change the itsCollisionPointRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsCollisionPointRight, type QRect& : the new right hitbox
    */
    void setItsCollisionPointRight(const QRect &newItsCollisionPointRight);
    /**
    * @brief This method change the itsCollisionPointLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsCollisionPointLeft, type QRect& : the new left hitbox
    */
    void setItsCollisionPointLeft(const QRect &newItsCollisionPointLeft);
    /**
    * @brief This method change the itsCollisionPointTop value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsCollisionPointTop, type QRect& : the new top hitbox
    */
    void setItsCollisionPointTop(const QRect &newItsCollisionPointTop);
    /**
    * @brief This method change the isCollidingRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingRight, type bool : tell if the Player is colliding on the right
    */
    void setIsCollidingRight(bool newIsCollidingRight);
    /**
    * @brief This method change the isCollidingLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingLeft, type bool : tell if the Player is colliding on the left
    */
    void setIsCollidingLeft(bool newIsCollidingLeft);
    /**
    * @brief This method change the isCollidingTop value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingTop, type bool : tell if the Player is colliding on the top
    */
    void setIsCollidingTop(bool newIsCollidingTop);
    /**
    * @brief This method change the isCollidingBottom value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingBottom, type bool : tell if the Player is colliding on the bottom
    */
    void setIsCollidingBottom(bool newIsCollidingBottom);
    /**
    * @brief This method change the isCollidingEnemy value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingEnemy, type bool : tell if the Player is colliding with an Enemy
    */
    void setIsCollidingEnemy(bool newIsCollidingEnemy);
    /**
    * @brief This method change the isCollidingTrap value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsCollidingTrap, type bool : tell if the Player is colliding with a Trap
    */
    void setIsCollidingTrap(bool newIsCollidingTrap);
    /**
    * @brief This method change the isEnemyKill value
    * @author GOBBE Paul
    * @version 1
    * @date 10 June 2024
    * @param newIsEnemyKill, type bool : tell if the Player kill an enemy
    */
    void setIsEnemyKill(bool newIsEnemyKill);
    /**
    * @brief This method change the value of itsRect
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsRect, type QRect& : the new Player's position and size
    */
    void setItsRect(const QRect &newItsRect);
    /**
    * @brief This method change the itsPlatforms value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsPlatforms, type QVector<Platform>& : list of platforms in the game
    */
    void setItsPlatforms(const QVector<Platform> &newItsPlatforms);
    /**
    * @brief This method change the itsEnemies value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsEnemies, type QVector<Platform>& : list of enemies in the game
    */
    void setItsEnemies(const QVector<Enemy*> &newItsEnemies);
    /**
    * @brief This method change the itsTraps value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsTraps, type QVector<Platform>& : list of traps in the game
    */
    void setItsTraps(const QVector<Trap> &newItsTraps);
    /**
    * @brief This method change the itsPowerUps value
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param newItsPowerUps, type QVector<PowerUp>& : list of power ups in the game
    */
    void setItsPowerUps(const QVector<PowerUp> &newItsPowerUps);
    /**
    * @brief This method change the itsSpeed value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsSpeed, type int : Player's movement speed
    */
    void setItsSpeed(int newItsSpeed);
    /**
    * @brief This method change the ItsVerticalVelocity value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsVerticalVelocity, type int : the vertical speed for jumping and gravity
    */
    void setItsVerticalVelocity(float newItsVerticalVelocity);
    /**
    * @brief This method change the isMovingLeft value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsMovingLeft, type bool : indicates if the Player is moving left
    */
    void setIsMovingLeft(bool newIsMovingLeft);
    /**
    * @brief This method change the isMovingRight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newIsMovingRight, type bool : indicates if the Player is moving right
    */
    void setIsMovingRight(bool newIsMovingRight);
    /**
     * @brief Setter for SakeTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @param timer, type int : the value to set the Sake Timer to
     */
    void setSakeTimer(int timer);
    /**
     * @brief Getter for WoodenSandalsTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @return WoodenSandalsTimer, type int : the current value of the Wooden Sandals Timer
     */
    int getWoodenSandalsTimer() const;
    /**
     * @brief Setter for WoodenSandalsTimer
     * @author PARDOEN James
     * @version 2
     * @date 3 June 2024
     * @param timer, type int : the value to set the Wooden Sandals Timer to
     */
    void setWoodenSandalsTimer(int timer);
    /**
     * @brief Getter for isFacingLeft
     * @author PARDOEN James
     * @version 2
     * @date 7 June 2024
     * @return isFacingLeft, type bool : if the player is facing left
     */
    bool getIsFacingLeft() const;
    /**
     * @brief Getter for isFacingRight
     * @author PARDOEN James
     * @version 2
     * @date 7 June 2024
     * @return isFacingRight, type bool : if the player is facing right
     */
    bool getIsFacingRight() const;
    /**
     * @brief setter for isFacingRight
     * @author PARDOEN James
     * @version 2
     * @date 7 June 2024
     * @param newIsFacingRight, type bool : the new value of isFacingRight
     */
    void setIsFacingRight(bool newIsFacingRight);
    /**
     * @brief setter for isFacingLeft
     * @author PARDOEN James
     * @version 2
     * @date 7 June 2024
     * @param newIsFacingLeft, type bool : the new value of isFacingLeft
     */
    void setIsFacingLeft(bool newIsFacingLeft);
    /**
     * @brief Getter for isCollidingBoss
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @return isColliding, type bool : the current value of the collision with the boss
     */
    bool getIsCollidingBoss() const;
    /**
     * @brief Setter for isCollidingBoss
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @param newIsCollidingBoss, type bool : the value to set the isCollidingBoss value
     */
    void setIsCollidingBoss(bool newIsCollidingBoss);
    /**
     * @brief Getter for itsAnimations
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @return itsAnimations, type QVector<Animation> : the list of the animations
     */
    QVector<Animation *> getItsAnimations() const;
    /**
     * @brief Getter for itsAnimationIndex
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @return itsAnimationIndex, type int : the index of the current animation
     */
    int getItsAnimationIndex() const;
    /**
     * @brief Getter for itsSecondaryAnimationIndex
     * @author GIGNOUX Victor
     * @version 2
     * @date 8 June 2024
     * @return itsSecondaryAnimationIndex, type int : the index of the secondary current animation
     */
    int getItsSecondaryAnimationIndex() const;
    /**
     * @brief Setter for isAttacking
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @param isAttacking, type bool : the value to set the new isAttacking value
     */
    void setIsAttacking(bool newIsattacking);
    /**
     * @brief Getter for isAttacking
     * @author GIGNOUX Victor
     * @version 2
     * @date 7 June 2024
     * @return isAttacking, type bool : if the player is attacking
     */
    bool getIsAttacking() const;
    /**
     * @brief Setter for isJumping
     * @author GIGNOUX Victor
     * @version 2
     * @date 9 June 2024
     * @param newIsJumping, type bool : the value to set the new isJumping value
     */
    void setIsJumping(bool newIsJumping);
    /**
     * @brief getter for the armor count
     * @author PARDOEN James
     * @version 2
     * @date 11 June 2024
     * @return itsArmorCount, type int : the amount of armors equipped on the player
     */
    int getItsArmorCount() const;
    /**
     * @brief setter for the armor count
     * @author PARDOEN James
     * @version 2
     * @date 11 June 2024
     * @param newCount, type int : the new amount of armors to be set for the player
     */
    void setItsArmorCount(int newCount);
    /**
     * @brief getter for the armor duration
     * @auth or PARDOEN James
     * @version 2
     * @date 11 June 2024
     * @return itsArmorDuration, type int : the duration of the armor equipped on the player
     */
    int getItsArmorDuration() const;
    /**
     * @brief setter for the armor duration
     * @author PARDOEN James
     * @version 2
     * @date 11 June 2024
     * @param newDuration, type int : the new duration of the armor to be set for the player
     */
    void setItsArmorDuration(int newDuration);
    /**
     * @brief Getters for isAttackingLeft
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     */
    bool getIsAttackingLeft() const;
    /**
     * @brief Getters for isAttackingRight
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     */
    bool getIsAttackingRight() const;
    /**
     * @brief Getters for itsAttackHitboxRight
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     */
    QRect getItsAttackHitboxRight() const;
    /**
     * @brief Getters for itsAttackHitboxLeft
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     */
    QRect getItsAttackHitboxLeft() const;
    /**
     * @brief Setter for isAttackingLeft
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     * @param newIsAttackingLeft, type bool : the value to set the new isAttackingLeft value
     */
    void setIsAttackingLeft(bool newIsAttackingLeft);
    /**
     * @brief Setter for isAttackingLeft
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     * @param newIsAttackingRight, type bool : the value to set the new isAttackingRight value
     */
    void setIsAttackingRight(bool newIsAttackingRight);
    /**
     * @brief Setter for itsAttackingHitboxLeft
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     * @param newHitboxLeft, type QRect& : the value to set the new itsAttackingHitboxLeft value
     */
    void setItsAttackHitboxLeft(const QRect& newHitboxLeft);
    /**
     * @brief Setter for itsAttackingHitboxRight
     * @author PARDOEN James
     * @version 2
     * @date 9 June 2024
     * @param newHitboxRight, type QRect& : the value to set the new itsAttackingHitboxRight value
     */
    void setItsAttackHitboxRight(const QRect& newHitboxRight);
    /**
     * @brief Setter for itsGoldenBuffCount
     * @author PARDOEN James
     * @version 2
     * @date 12 June 2024
     * @param newCount, type int : set the value of itsGoldenBuffCount to newCount
     */
    void setItsGoldenBuffCount(const int newCount);
    /**
     * @brief Getter for itsGoldenBuffCount
     * @author PARDOEN James
     * @version 3
     * @date 12 June 2024
     * @return type int : the current amount of buffs
     */
    int getItsGoldenBuffCount() const;
    /**
     * @brief the movement of the player for the bossfight only
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @param direction, type int : set the direction of the player according to the parameter
     */
    void bossFightMove(int direction);
    /**
     * @brief Setter for isPressingD
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @param press, type bool : the value to set the new isPressingD value
     */
    void setIsPressingD(bool press);
    /**
     * @brief Setter for isPressingQ
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @param press, type bool : the value to set the new isPressingQ value
     */
    void setIsPressingQ(bool press);
    /**
     * @brief Getters for isPressingD
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @return isPressingD, type bool : if the user is pressing D key
     */
    bool getIsPressingD() const;
    /**
     * @brief Getters for isPressingQ
     * @author GIGNOUX Victor
     * @version 2
     * @date 12 June 2024
     * @return isPressingQ, type bool : if the user is pressing Q key
     */
    bool getIsPressingQ() const;
};

#endif // PLAYER_H
