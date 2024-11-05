#include "boss.h"

Boss::Boss(Player * aPlayer, QPoint spawnPoint, int bossWidth, int bossHeight, int speed)
{
    itsPlayer = aPlayer;
    itsHealthPoint = 3;
    itsSpeed= speed;
    itsRect = {spawnPoint.x(),spawnPoint.y(),bossWidth,bossHeight};
    itsSprite.load("../game_ressources/boss.png");
    itsLeftSprite.load("../game_ressources/bossLeft.png");
}

Boss::~Boss() {}

void Boss::setItsSpeed(int speed)
{
    itsSpeed = speed;
}

void Boss::move()
{
    QPoint playerPosition, bossPosition;

    playerPosition = itsPlayer->getItsRect().center();
    bossPosition = itsRect.center();

    int xDirection = playerPosition.x() - bossPosition.x(); // Boss direction (y) related to the player
    int yDirection = playerPosition.y() - bossPosition.y(); // Boss direction (x) related to the player

    // Boss moves vertically if he is not aligned to the boss

    if(yDirection > -2 && yDirection < 2)
        itsRect.translate((xDirection/abs(xDirection))*itsSpeed, 0);
    else
        itsRect.translate((xDirection/abs(xDirection))*itsSpeed, (yDirection/abs(yDirection))*itsSpeed);

    if(itsPlayer->getItsCollisionPointBottom().intersects(itsHitbox) || itsPlayer->getItsCollisionPointTop().intersects(itsHitbox)
        || itsPlayer->getItsCollisionPointLeft().intersects(itsHitbox) || itsPlayer->getItsCollisionPointRight().intersects(itsHitbox))
    {
        if(itsPlayer->getItsArmorCount() > 0 && itsPlayer->getItsArmorDuration() == 0){
            itsPlayer->setItsArmorCount(itsPlayer->getItsArmorCount()-1);
            itsPlayer->setItsArmorDuration(ARMOR_DURATION);
        }
        else if(itsPlayer->getItsArmorCount() <= 0 && itsPlayer->getItsArmorDuration() == 0)
            itsPlayer->setIsCollidingBoss(true);
    }
}

void Boss::updateBossRelativePosition(int x, bool isColliding)
{
    if(!isColliding)
    {
        if(getItsRect().x() > -150)
            itsRect.translate(x, 0);
        else
            itsRect.moveTo(-150, getItsRect().y());
    }
}

QPoint Boss::getItsPosition() const
{
    return {itsRect.x(), itsRect.y()};
}

int Boss::getItsHealthPoint() const
{
    return itsHealthPoint;
}

QRect Boss::getItsRect() const
{
    return itsRect;
}

QPixmap Boss::getItsSprite() const
{
    return itsSprite;
}

QPixmap Boss::getItsLeftSprite() const
{
    return itsLeftSprite;
}

QRect Boss::getItsHitbox()const
{
    return itsHitbox;
}

void Boss::setItsHitbox(QRect newHitbox)
{
    itsHitbox = newHitbox;
}

void Boss::bossFightMove(QPoint aPosition)
{

    QPoint playerPosition, bossPosition;

    bossPosition = itsRect.center();

    int xDirection = aPosition.x() - bossPosition.x(); // Boss direction (y) related to the delayed player
    int yDirection = aPosition.y() - bossPosition.y(); // Boss direction (x) related to the delayed player

    // Move the boss toward the player
    if(yDirection > -2 && yDirection < 2)
        itsRect.translate((xDirection/abs(xDirection))*itsSpeed, 0);
    else
        itsRect.translate((xDirection/abs(xDirection))*itsSpeed, (yDirection/abs(yDirection))*itsSpeed);

    // Detect collision with the player
    if(itsPlayer->getItsCollisionPointBottom().intersects(itsHitbox) || itsPlayer->getItsCollisionPointTop().intersects(itsHitbox)
        || itsPlayer->getItsCollisionPointLeft().intersects(itsHitbox) || itsPlayer->getItsCollisionPointRight().intersects(itsHitbox))
    {
        if(itsPlayer->getItsArmorCount() > 0 && itsPlayer->getItsArmorDuration() == 0){
            itsPlayer->setItsArmorCount(itsPlayer->getItsArmorCount()-1);
            itsPlayer->setItsArmorDuration(ARMOR_DURATION);
        }
        else if(itsPlayer->getItsArmorCount() <= 0 && itsPlayer->getItsArmorDuration() == 0)
            itsPlayer->setIsCollidingBoss(true);
    }
}

void Boss::setItsHealthPoint(const int newHp){
    itsHealthPoint = newHp;
}

int Boss::getItsIframes() const{
    return itsIframes;
}

void Boss::setItsIframes(const int newVal){
    itsIframes = newVal;
}
