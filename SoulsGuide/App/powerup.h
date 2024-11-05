#ifndef POWERUP_H
#define POWERUP_H
#include <typeDef.h>
#include <QRect>
#include <QPoint>
#include <QPixmap>

/**
* @brief The PowerUp class implements the game's powerups entity
* and describes their behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class PowerUp {
private:
    /** the 3 different sprites of the power ups */
    QVector<QPixmap> itsSprites;

protected:
    QRect itsRect;
    PowerUpType itsType;

public:
    /**
    * @brief The constructor to create a Power Up with spawn coordinates and type
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param coordinate, type QPoint& : coordinates of the Power Up's spawn
    * @param type, type PowerUpType : the type of the Power Up
    */
    PowerUp(const QPoint& coordinate, int width, int height, PowerUpType type);

    /**
    * @brief The constructor to create a Power Up with spawn coordinates and type
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param coordinate, type QPoint& : coordinates of the Power Up's spawn
    * @param typeStr, type string& : the type of the Power Up with a string
    */
    PowerUp(const QPoint& coordinate, int width, int height, const std::string& typeStr);
    /**
    * @brief The destructor to delete a power up
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    */
    ~PowerUp();

    /**
    * @brief This method update the Power Up position in the game
    * relative to player movement
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updatePowerUpRelativePosition(int x, bool isColliding);

    /**
    * @brief This method return the itsRect attribute
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @return itsRect, type QRect : the position and size of the power up
    */
    QRect getItsRect() const;

    /**
    * @brief This method return the itsPowerUpType attribute
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @return itsPowerUpType, type PowerUpType : the type of the power up
    */
    PowerUpType getItsPowerUpType() const;

    /**
    * @brief This method return a sprite from the itsSprites vector
    * @author GIGNOUX Victor
    * @version 2
    * @date 6 June 2024
    * @param index, type int : the index of the sprite
    * @return itsSprites, type QPixmap : a sprite from the itsSprites vector
    */
    QPixmap getItsSprite(int index) const;

    /**
    * @brief This method changes the itsRect attribute
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param newRect, type QRect : the new position and sier of the power up
    */
    void setItsRect(const QRect& newRect);

    /**
    * @brief This method change the itsPowerUpType attribute
    * @author PARDOEN James
    * @version 2
    * @date 6 June 2024
    * @param itsPowerUpType, type PowerUpType : the new type of the power up
    */
    void setItsPowerUpType(PowerUpType newType);
};


#endif // POWERUP_H
