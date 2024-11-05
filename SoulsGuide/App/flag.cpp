#include "flag.h"

// Default Constructor
Flag::Flag() : itsPosition(0, 0), itsSize(0) {
    itsRect = QRect(itsPosition.x() - itsSize / 2, itsPosition.y() - itsSize / 2, itsSize, itsSize);
    QPixmap katanaSprite, armorSprite;
    katanaSprite.load("../game_ressources/katana.png");
    armorSprite.load("../game_ressources/armor.png");
    itsSprites.append(katanaSprite);
    itsSprites.append(armorSprite);
}

// Constructor with parameters
Flag::Flag(const QPoint& initialPosition, int initialSize)
    : itsPosition(initialPosition), itsSize(initialSize) {
    itsRect = QRect(itsPosition.x() - itsSize / 2, itsPosition.y() - itsSize / 2, itsSize, itsSize);
    QPixmap katanaSprite, armorSprite;
    katanaSprite.load("../game_ressources/katana.png");
    armorSprite.load("../game_ressources/armor.png");
    itsSprites.append(katanaSprite);
    itsSprites.append(armorSprite);
}

Flag::~Flag() {}

// Getters
QPoint Flag::getItsPosition() const {
    return itsPosition;
}

int Flag::getItsSize() const {
    return itsSize;
}

QRect Flag::getItsRect() const {
    return itsRect;
}

QPixmap Flag::getItsSprite(int index) const
{
    return itsSprites.at(index);
}

// Setters
void Flag::setItsPosition(const QPoint& newPosition) {
    itsPosition = newPosition;
}

void Flag::setItsSize(int newSize) {
    itsSize = newSize;
}

void Flag::setItsRect(const QRect& newRect) {
    itsRect = newRect;
    itsPosition = itsRect.center();
    itsSize = itsRect.width(); // Assuming width equals height for a square
}

void Flag::updateFlagRelativePosition(int x, bool isColliding)
{
    if(!isColliding)
        itsRect.translate(x, 0);
}
