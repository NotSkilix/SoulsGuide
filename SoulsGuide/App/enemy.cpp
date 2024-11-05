#include "enemy.h"

Enemy::Enemy(const QRect& initialRect, const QPoint& startingPoint, const QPoint& endingPoint, int moveSpeed, int type) : itsRect(initialRect), itsFirstEndPoint(startingPoint), itsSecondEndPoint(endingPoint), itsSpeed(moveSpeed), isMovingToSecondPoint(true)
{
    itsCurrentTarget = endingPoint;  // Start by moving towards the first target point

    if(type == 0)
    {
        itsType = EnemyType::Skully;
        loadAnimation("skullyRight", 9);
        loadAnimation("skullyLeft", 9);
    }
    else if(type == 1)
    {
        itsType = EnemyType::Phantom;
        loadAnimation("phantomRight", 4);
        loadAnimation("phantomLeft", 4);
    }
    else if(type == 2)
    {
        itsType = EnemyType::Eye;
        loadAnimation("eyeRight", 4);
        loadAnimation("eyeLeft", 4);
    }
    else if(type == 3)
    {
        itsType = EnemyType::Gold;
        loadAnimation("goldenEyeRight", 4);
        loadAnimation("goldenEyeLeft", 4);
    }
    setItsCurrentFrame(0);
}

Enemy::~Enemy() {}

void Enemy::updatePosition() {
    QPoint currentPos = itsRect.center();
    if (currentPos == itsCurrentTarget)
    {
        // Switch target when current one is reached
        itsCurrentTarget = (itsCurrentTarget == itsFirstEndPoint) ? itsSecondEndPoint : itsFirstEndPoint;
        isMovingToSecondPoint = !isMovingToSecondPoint; // Toggle movement direction
        setItsCurrentFrame(!isMovingToSecondPoint);
    }
    moveTowards(itsCurrentTarget);
}

void Enemy::moveTowards(const QPoint& target) {
    QPoint currentPos = itsRect.center();
    int dx = target.x() - currentPos.x();
    int dy = target.y() - currentPos.y();
    int absDx = std::abs(dx);
    int absDy = std::abs(dy);

    int moveX = (absDx > 0) ? (dx / absDx) * itsSpeed : 0;  // Normalize direction and multiply by speed
    int moveY = (absDy > 0) ? (dy / absDy) * itsSpeed : 0;

    // Ensure that the enemy does not overshoot the target
    if (absDx < itsSpeed) moveX = dx;
    if (absDy < itsSpeed) moveY = dy;

    itsRect.translate(moveX, moveY);
}

void Enemy::updateEnemyRelativePosition(int x, bool isColliding)
{
    if(!isColliding)
    {
        itsRect.translate(x, 0);
        itsFirstEndPoint.setX(itsFirstEndPoint.x() + x);
        itsSecondEndPoint.setX(itsSecondEndPoint.x() + x);
        itsCurrentTarget.setX(itsCurrentTarget.x() + x);
    }
}

void Enemy::playAnimation()
{
    if(itsCurrentFrame->next != nullptr)
        itsCurrentFrame = itsCurrentFrame->next;
    else
        qDebug() << "no next frame";
}

void Enemy::loadAnimation(QString animationName, int frameNumber)
{
    Animation * newAnimation = new Animation;
    for(int i = 0; i < frameNumber; i++)
    {
        QString filename = "../game_ressources/" + animationName + "/" + animationName + QString::number(i) + ".png";
        Frame * newFrame = new Frame;
        if(newFrame->image.load(filename))
        {
            if(i == 0)
            {
                newAnimation->first = newFrame;
                itsCurrentFrame = newAnimation->first;
            }
            else
            {
                itsCurrentFrame->next = newFrame;
                itsCurrentFrame = itsCurrentFrame->next;
            }

            if(i == frameNumber-1)
                itsCurrentFrame->next = newAnimation->first;
        }
        else
            qDebug() << "missing frame " << filename;
    }
    itsAnimations.append(newAnimation);
}


// Getters
Frame * Enemy::getItsCurrentFrame() const
{
    return itsCurrentFrame;
}

QRect Enemy::getItsRect() const {
    return itsRect;
}

QPoint Enemy::getItsFirstEndPoint() const {
    return itsFirstEndPoint;
}

QPoint Enemy::getItsSecondEndPoint() const {
    return itsSecondEndPoint;
}

QPoint Enemy::getItsCurrentTarget() const {
    return itsCurrentTarget;
}

int Enemy::getItsSpeed() const {
    return itsSpeed;
}

bool Enemy::getIsMovingToSecondPoint() const {
    return isMovingToSecondPoint;
}

// Setters
void Enemy::setItsRect(const QRect& newRect) {
    itsRect = newRect;
}

void Enemy::setItsFirstEndPoint(const QPoint& newEndPoint1) {
    itsFirstEndPoint = newEndPoint1;
}

void Enemy::setItsSecondEndPoint(const QPoint& newEndPoint2) {
    itsSecondEndPoint = newEndPoint2;
}

void Enemy::setItsCurrentTarget(const QPoint& newCurrentTarget) {
    itsCurrentTarget = newCurrentTarget;
}

void Enemy::setItsSpeed(int newSpeed) {
    itsSpeed = newSpeed;
}

void Enemy::setIsMovingToSecondPoint(bool newMovingToPoint2) {
    isMovingToSecondPoint = newMovingToPoint2;
}

void Enemy::setItsCurrentFrame(int index)
{
    if(index != itsAnimationIndex)
    {
        Animation * anim = itsAnimations.at(index);
        itsCurrentFrame = anim->first;
        itsAnimationIndex = index;
    }
}
