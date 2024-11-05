#ifndef TRAP_H
#define TRAP_H

#include <QPoint>
#include <QRect>
#include <QPixmap>

/**
* @brief The Trap class implements the game's Platforms entity
* and describes its behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class Trap
{
private:
    // position is the center point of the rectangle
    /** The coordinates of the Trap */
    QPoint itsPosition;
    /** The hitbox of the Trap */
    QRect itsRect;
    /** The height of the Trap */
    int itsHeight;
    /** The width of the Trap */
    int itsWidth;
    QPixmap itsSprite;

public:
    /**
    * @brief The constructor to create a Trap
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param initialPosition, type QPoint& : the Trap's position coordinates
    * @param initialHeight, type int : the Traps height value
    * @param initialWidth, type int : the Traps width value
    */
    Trap(const QPoint& initialPosition, int initialHeight, int initialWidth);
    /**
    * @brief The destructor to delete a trap
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Trap();
    /**
    * @brief This method update the Trap position in the game
    * relative to player movement
    * @author GIGNOUX Victor
    * @version 1
    * @date 3 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updateTrapRelativePosition(int x, bool isColliding);

    // Getters
    /**
    * @brief This method return the itsPosition value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsPosition, type QPoint : the coordinate of the Trap
    */
    QPoint getItsPosition() const;
    /**
    * @brief This method return the itsHeight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsHeight, type int : the height value of the Trap
    */
    int getItsHeight() const;
    /**
    * @brief This method return the itsWidth value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsWidth, type int : the width value of the Trap
    */
    int getItsWidth() const;
    /**
    * @brief This method return the itsRect value
    * (itsRect represent the hitbox of the Trap)
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type QRect : the hitbox of the Trap
    */
    QRect getItsRect() const;
    QPixmap getItsSprite() const;

    // Setters
    /**
    * @brief This method change the itsPosition value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newPosition, type QPoint& : The Trap's coordinates
    */
    void setItsPosition(const QPoint& newPosition);
    /**
    * @brief This method change the itsHeight value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newHeight, type int : the height value of the Trap
    */
    void setItsHeight(int newHeight);
    /**
    * @brief This method change the itsWidth value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newWidth, type int : the width value of the Trap
    */
    void setItsWidth(int newWidth);
    /**
    * @brief This method change the value of the hitbox of the Trap
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newRect, type QRect& : The hitbox value of the Trap
    */
    void setItsRect(const QRect& newRect);
};

#endif // TRAP_H
