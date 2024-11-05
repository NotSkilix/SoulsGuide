
#ifndef ENEMY_H
#define ENEMY_H
#include <QRect>
#include <QPoint>
#include <QPixmap>
#include <QDebug>

#include "typeDef.h"

/**
* @brief The Enemy class implements the game's Enemies
* and describes their behavior.
* @author PARDOEN James
* @version 1
* @date 3 June 2024
*/
class Enemy {
private:
    /** Represents the enemy's position and size */
    QRect itsRect;
    /** the type of enemy */
    EnemyType itsType;
    /** First endpoint of patrol */
    QPoint itsFirstEndPoint;
    /** Second endpoint of patrol */
    QPoint itsSecondEndPoint;
    /** Current target endpoint */
    QPoint itsCurrentTarget;
    /** Speed of movement */
    int itsSpeed;
    /** Direction flag */
    bool isMovingToSecondPoint;
    /** animations of the enemy */
    QVector<Animation*> itsAnimations;
    /** the current frame of the player */
    Frame * itsCurrentFrame;
    /** the index of the current animation */
    int itsAnimationIndex = -1;

public:
    /**
    * @brief The constructor to create an Enemy
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param initialRect, type QRect& : the Enemy size and spawn coordinates
    * @param startingPoint, type QPoint& : the starting point of the Enemy's movement
    * @param endingPoint, type QPoint& : the ending point of the Enemy's movement
    * @param moveSpeed, type int : the movement's speed
    */
    Enemy(const QRect& initialRect, const QPoint& startingPoint, const QPoint& endingPoint, int moveSpeed, int type);

    /**
    * @brief The destructor to delete an Enemy
    * @author GIGNOUX Victor
    * @version 1
    * @date 6 June 2024
    */
    ~Enemy();

    /**
    * @brief This method update the position of Enemy
    * and check if he is on the starting/ending point
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    */
    void updatePosition();

    /**
    * @brief This method make the Enemy move to a target (point)
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param target, type QPoint& : the point where the Enemy is heading
    */
    void moveTowards(const QPoint& target);

    /**
    * @brief This method load the images needed for the animations in a vector<Animation>
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    * @param animationName, type QString : the name of the animation needed to find the images
    * @param frameNumber, type int : the number of frame this animation contains
    */
    void loadAnimation(QString animationName, int frameNumber);

    /**
    * @brief This method switch the current frame to the next one
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    */
    void playAnimation();

    // Getters
    /**
    * @brief This method gives access to the current frame of the enemy
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    * @return itsCurrentFrame, type QPixmap : the current frame of the enemy
    */
    Frame * getItsCurrentFrame() const;
    /**
    * @brief This method return the itsRect value
    * (itsRect represent the hitbox of the Enemy)
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsRect, type QRect : the hitbox of the Enemy
    */
    QRect getItsRect() const;
    /**
    * @brief This method return the itsFirstEndPoint coordinate
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsFirstEndPoint, type QPoint : the itsFirstEndPoint coordinate
    */
    QPoint getItsFirstEndPoint() const;
    /**
    * @brief This method return the itsSecondEndPoint coordinate
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsSecondEndPoint, type QPoint : the itsSecondEndPoint coordinate
    */
    QPoint getItsSecondEndPoint() const;
    /**
    * @brief This method return the itsCurrentTarget coordinate
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsCurrentTarget, type QPoint : the itsCurrentTarget coordinate
    */
    QPoint getItsCurrentTarget() const;
    /**
    * @brief This method return the itsSpeed value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return itsSpeed, type int : the itsSpeed value
    */
    int getItsSpeed() const;
    /**
    * @brief This method return the itsMovingToSecondPoint value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @return isMovingToSecondPoint, type bool : the isMovingToSecondPoint value
    */
    bool getIsMovingToSecondPoint() const;

    // Setters
    /**
    * @brief This method change the value of the hitbox of the Enemy
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newRect, type QRect& : The hitbox value of the Enemy
    */
    void setItsRect(const QRect& newRect);
    /**
    * @brief This method change the itsFirtsEndPoint value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param aFirtsEndPoint, type QPoint& : The itsFirstEndPoint coordinates
    */
    void setItsFirstEndPoint(const QPoint& aFirstEndPoint);
    /**
    * @brief This method change the value of the itsSecondEndPoint value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param aSecondEndPoint, type QPoint& : The itsSecondEndPoint coordinates
    */
    void setItsSecondEndPoint(const QPoint& aSecondEndPoint);
    /**
    * @brief This method change the itsCurrentTarget value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param aTarget, type QPoint& : The itsCurrentTarget coordinates
    */
    void setItsCurrentTarget(const QPoint& aTarget);
    /**
    * @brief This method change the itsSpeed value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newSpeed, type QPoint& : The itsSpeed value
    */
    void setItsSpeed(int newSpeed);
    /**
    * @brief This method change the itsMovingToSecondPoint value
    * @author PARDOEN James
    * @version 1
    * @date 3 June 2024
    * @param newMovingToPoint2, type bool : The itsMovingToSecondPoint value
    */
    void setIsMovingToSecondPoint(bool newMovingToPoint2);

    /**
    * @brief This method change the current animation
    * @author GIGNOUX Victor
    * @version 2
    * @date 8 June 2024
    * @param index, type int : the index of the animation wanted
    */
    void setItsCurrentFrame(int index);

    /**
    * @brief This method update the Enemy position in the game
    * relative to player movement
    * @author GIGNOUX Victor
    * @version 1
    * @date 3 June 2024
    * @param x, type int : The direction
    * @param isColliding, type bool : If the player collides with a platform
    */
    void updateEnemyRelativePosition(int x, bool isColliding);
};



#endif // ENEMY_H
