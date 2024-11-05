#include "platform.h"

Platform::Platform(int x, int y, int width, int height) : itsRect(x, y, width, height), isBreakable(false) {} // Initialize isBreakable to false

Platform::~Platform() {}

void Platform::loadSprites(int currentLevel)
{
    QPixmap  sprite, topSprite;

    if(sprite.load("../game_ressources/platform" + QString::number(currentLevel) + ".png"))
        itsSprites.append(sprite);
    else
    {
        qDebug() << "missing frame platform " + QString::number(currentLevel) << " added level 1 sprites by default";
    }


    if(topSprite.load("../game_ressources/topPlatform" + QString::number(currentLevel) + ".png"))
        itsSprites.append(topSprite);

    else
    {
        qDebug() << "missing frame top platform " + QString::number(currentLevel) << " added level 1 sprites by default";
    }
}

// getter
QRect Platform::getItsRect() const
{
    return itsRect;
}

bool Platform::getIsBreakable() const {
    return isBreakable;
}

QPixmap Platform::getItsSprite(int index) const
{
    return itsSprites.at(index);
}

// setter
void Platform::setItsRect(const QRect &newItsRect)
{
    itsRect = newItsRect;
}

void Platform::updatePlatformRelativePosition(int x, bool isColliding)
{
    if(!isColliding)
        itsRect.translate(x, 0);
}

void Platform::setIsBreakable(bool newState)
{
    isBreakable = newState;
}
