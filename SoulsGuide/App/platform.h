#ifndef PLATFORM_H
#define PLATFORM_H

#include <QRect>
#include <QPixmap>
#include <qdebug.h>

/**
* @brief The Platform class implements the game's Platforms entity
* and describes its behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class Platform
{
private:
    /** The hitbox of the Platform */
    QRect itsRect;         // Stores the position and size of the platform all in single rectangle
    /** If the platform is breakable or not */
    bool isBreakable;   // Flag to determine if the platform is breakable or not (not by default)
    /** the sprites of the platforms */
    QVector<QPixmap> itsSprites;

public:
    /**
    * @brief The constructor to create a Platform
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param x, type int : coordinate x of the platform
    * @param y, type int : coordinate y of the platform
    * @param width, type int : the width of the platform
    * @param height, type int : the height of the platform
    */
    Platform(int x, int y, int width, int height);
    /**
    * @brief The destructor to delete a platform
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Platform();
    /**
    * @brief This method update the Platform position in the game
    * relative to player movement
    * @author GIGNOUX Victor
    * @version 1
    * @date 3 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updatePlatformRelativePosition(int x, bool isColliding);
    /**
    * @brief This method loads the sprites of the platforms depending to the level
    * @author GIGNOUX Victor
    * @version 2
    * @date 9 June 2024
    * @param currentLevel, type int : the index of the current level
    */
    void loadSprites(int currentLevel);


    // getters
    /**
    * @brief This method return the hitbox of the Platform
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type QRect : the hitbox of the Platform
    */
    QRect getItsRect() const;
    /**
    * @brief This method return the isBreakable value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isBreakable, type bool : tell if the platform is breakable
    */
    bool getIsBreakable() const;
    /**
    * @brief This method return a sprite from the itsSprites vector
    * @author GIGNOUX Victor
    * @version 2
    * @date 6 June 2024
    * @param index, type int : the index of the sprite
    * @return itsSprites, type QPixmap : a sprite from the itsSprites vector
    */
    QPixmap getItsSprite(int index) const;

    // setters
    /**
    * @brief This method change the value of the hitbox of the Platform
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newItsRect, type QRect& : The hitbox value of the Flag
    */
    void setItsRect(const QRect &newItsRect);
    /**
    * @brief This method change the value of isBreakable
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newState, type bool : The state of the Platform (breakable or not)
    */
    void setIsBreakable(bool newState);
};

#endif // PLATFORM_H
