#include "trap.h"

// Constructor
Trap::Trap(const QPoint& initialPosition, int initialHeight, int initialWidth)
    : itsPosition(initialPosition), itsHeight(initialHeight), itsWidth(initialWidth) {
    itsRect = QRect(itsPosition.x() - itsWidth / 2, itsPosition.y() - itsHeight / 2, itsWidth, itsHeight);
    itsSprite.load("../game_ressources/trap.png");
}

Trap::~Trap() {}

void Trap::updateTrapRelativePosition(int x, bool isColliding)
{
    if(!isColliding)
        itsRect.translate(x, 0);
}

// Getters
QPoint Trap::getItsPosition() const {
    return itsPosition;
}

int Trap::getItsHeight() const {
    return itsHeight;
}

int Trap::getItsWidth() const {
    return itsWidth;
}

QRect Trap::getItsRect() const {
    return itsRect;
}

QPixmap Trap::getItsSprite() const
{
    return itsSprite;
}

// Setters
void Trap::setItsPosition(const QPoint& newPosition) {
    itsPosition = newPosition;
}

void Trap::setItsHeight(int newHeight) {
    itsHeight = newHeight;
}

void Trap::setItsWidth(int newWidth) {
    itsWidth = newWidth;
}

void Trap::setItsRect(const QRect& newRect) {
    itsRect = newRect;
    itsPosition = itsRect.center();
    itsHeight = itsRect.height();
    itsWidth = itsRect.width();
}

