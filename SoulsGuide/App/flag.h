#ifndef FLAG_H
#define FLAG_H

#include <QPoint>
#include <QRect>
#include <QPixmap>

/**
* @brief The Flag class implements the game's Flag entity
* and describes its behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class Flag
{
public:
    /**
    * @brief The default constructor of the Flag
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    Flag();
    /**
    * @brief The destructor to delete a Flag
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Flag();
    /**
    * @brief The constructor to create a Flag
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param initialPosition, type QPoint& : the Flag's position coordinates
    * @param initialSize, type int : the size of the Flag (the Flag is a square)
    */
    Flag(const QPoint& initialPosition, int initialSize);

    // Getters
    /**
    * @brief This method return the itsPosition value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsPosition, type QPoint : the coordinate of the Flag
    */
    QPoint getItsPosition() const;
    /**
    * @brief This method return the itsSize value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsSize, type int : the size of the Flag
    */
    int getItsSize() const;
    /**
    * @brief This method return the itsRect value
    * (itsRect represent the hitbox of the Flag)
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type QRect : the hitbox of the Flag
    */
    QRect getItsRect() const;
    /**
    * @brief This method return a sprite from the itsSprites vector
    * @author GIGNOUX Victor
    * @version 2
    * @date 6 June 2024
    * @param index, type int : the index of the sprite
    * @return itsSprites, type QPixmap : a sprite from the itsSprites vector
    */
    QPixmap getItsSprite(int index) const;

    // Setters
    /**
    * @brief This method change the itsPosition value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newPosition, type QPoint& : The Flag's coordinates
    */
    void setItsPosition(const QPoint& newPosition);
    /**
    * @brief This method change the itsSize value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newSize, type int : The Flag's size
    */
    void setItsSize(int newSize);
    /**
    * @brief This method change the value of the hitbox of the Flag
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newRect, type QRect& : The hitbox value of the Flag
    */
    void setItsRect(const QRect& newRect);

    //change the position of the traps when the player is theoritically moving
    /**
    * @brief This method update the Flag position in the game
    * relative to player movement
    * @author GIGNOUX Victor
    * @version 1
    * @date 3 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updateFlagRelativePosition(int x, bool isColliding);

private:
    // Flag is a square, the QPoint called position serves as the center of the square
    /** The coordinates of the Flag's position */
    QPoint itsPosition;
    /** The hitbox of the Flag */
    QRect itsRect;
    /** The size of the Flag */
    int itsSize;
    /** the 3 different sprites of the objects */
    QVector<QPixmap> itsSprites;
};

#endif // FLAG_H
