#ifndef BOSS_H
#define BOSS_H

#include "typeDef.h"
#include "player.h"

/**
* @brief The Boss class implements the game's Boss entity
* and describes its behavior.
* @author BOURDY Axel
* @version 1
* @date 3 June 2024
*/
class Boss
{
private:
    /** Its health point (for the boss fight only) */
    int itsHealthPoint;
    /** Its move speed towards the player */
    int itsSpeed;
    /** the size of the boss and its position */
    QRect itsRect;
    /** iframe timer, how long till the boss can take damage after being hit*/
    int itsIframes = 0;
    // For the boss fight, default is false
    // bool isKillable; à réflechir
    /** The player of the game */
    Player * itsPlayer;
    /** the boss sprite */
    QPixmap itsSprite;
    /** the left boss sprite */
    QPixmap itsLeftSprite;
    /** the hibox of the boss */
    QRect itsHitbox;
public:
    /**
    * @brief The constructor to create a Boss
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    * @param aPlayer, type Player* : the Player in the game
    * @param spawnPoint, type QPoint : the point where the Boss appears
    * @param bossWidth, type int : the width of the boss (use typeDef.h to define)
    * @param bossHeight, type int : the height of the boss (use typeDef.h to define)
    * @param speed, type int: the boss speed
    */
    Boss(Player * aPlayer, QPoint spawnPoint, int bossWidth, int bossHeight, int speed);

    /**
    * @brief The destructor to delete a Boss
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Boss();

    // All the setters
    /**
    * @brief This method change the value of the speed of the Boss
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    * @param speed, type int : The speed value of the Boss
    */
    void setItsSpeed(int speed);

    /**
    * @brief This method takes the player's coordinates
    * and then moves in that direction
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    */
    void move();
    /**
    * @brief This method update the Boss position in the game
    * relative to player movement
    * @author GIGNOUX Victor
    * @version 1
    * @date 3 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updateBossRelativePosition(int x, bool isColliding);

    // All the getters
    /**
    * @brief This method return the itsPosition value
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    * @return itsPosition, type QPoint : the position of the Boss
    */
    QPoint getItsPosition() const;
    /**
    * @brief This method return the itsHealthPoint value
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    * @return itsHealthPoint, type int : the health point of the Boss
    */
    int getItsHealthPoint() const;
    /**
    * @brief This sets the itsHealthPoint value
    * @author PARDOEN James
    * @version 3
    * @date 12 June 2024
    * @param newHp, type int : the new health point of the Boss
    */
    void setItsHealthPoint(const int newHp);
    /**
    * @brief This method returns the itsIframes value
    * @author PARDOEN James
    * @version 3
    * @date 12 June 2024
    * @return itsIframes, type int : the iframe timer of the Boss
    */
    int getItsIframes() const;
    /**
    * @brief This sets the itsIframes value
    * @author PARDOEN James
    * @version 3
    * @date 12 June 2024
    * @param newVal, type int : the new iFrames value of the Boss
    */
    void setItsIframes(const int newVal);
    /**
    * @brief This method return the itsRect value
    * (itsRect represent the hitbox of the Boss)
    * @author BOURDY Axel
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type int : the hitbox of the Boss
    */
    QRect getItsRect() const;
    /**
    * @brief This method return the itsSprite value
    * @author GIGNOUX Victor
    * @version 2
    * @date 6 June 2024
    * @return itsSprite, type QPixmap : the sprite of the Boss
    */
    QPixmap getItsSprite() const;
    /**
    * @brief This method return the itsLeftSprite value
    * @author GIGNOUX Victor
    * @version 2
    * @date 12 June 2024
    * @return itsLeftSprite, type QPixmap : the left sprite of the Boss
    */
    QPixmap getItsLeftSprite() const;
    /**
    * @brief This method return the itsHitbox value
    * @author GIGNOUX Victor
    * @version 2
    * @date 12 June 2024
    * @return itsHitbox, type QRect : the hitbox of the Boss
    */
    QRect getItsHitbox() const;
    /**
     * @brief Setter of itsHitbox
     * @author GIGNOUX Victor
     * @version 3
     * @date 12 June 2024
     * @param newHitbox, type QRect : the new hitbox ofthe boss
     */
    void setItsHitbox(QRect newHitbox);
    /**
    * @brief Change the boss movements and delay the position of the player to
    *        allow a fair fight and increase his chances of survival on the boss fight
    *
    * @author BOURDY Axel
    * @version 3
    * @date 11 June 2024
    * @param aPosition, type QPoint : the delayed position of the player
    */
    void bossFightMove(QPoint aPosition);
};

#endif // BOSS_H
