#include "powerup.h"

// Constructs a PowerUp with a coordinate and type
PowerUp::PowerUp(const QPoint& coordinate, int width, int height, PowerUpType type)
    : itsRect(coordinate.x() - width / 2, coordinate.y() - height / 2, width, height), itsType(type)
{
    QPixmap sakeSprite, sushiSprite, sandalsSprite;
    sakeSprite.load("../game_ressources/powerup_sake.png");
    sushiSprite.load("../game_ressources/powerup_sushi.png");
    sandalsSprite.load("../game_ressources/powerup_sandals.png");
    itsSprites.append(sakeSprite);
    itsSprites.append(sushiSprite);
    itsSprites.append(sandalsSprite);
}

// Constructs a PowerUp with a coordinate and type specified as a string
PowerUp::PowerUp(const QPoint& coordinate, int width , int height, const std::string& typeStr)
    : itsRect(coordinate.x() - width / 2, coordinate.y() - height / 2, width, height)
{
    if (typeStr == "SalmonSushi")
    {
        itsType = SalmonSushi;
    }
    else if (typeStr == "WoodenSandals")
    {
        itsType = WoodenSandals;
    }
    else if (typeStr == "Sake")
    {
        itsType = Sake;
    }
    else
    {
        itsType = SalmonSushi; // Example default
    }

    QPixmap sakeSprite, sushiSprite, sandalsSprite;
    sakeSprite.load("../game_ressources/powerup_sake.png");
    sushiSprite.load("../game_ressources/powerup_sushi.png");
    sandalsSprite.load("../game_ressources/powerup_sandals.png");
    itsSprites.append(sakeSprite);
    itsSprites.append(sushiSprite);
    itsSprites.append(sandalsSprite);
}

PowerUp::~PowerUp() {}

void PowerUp::updatePowerUpRelativePosition(int x, bool isColliding) {
    if (!isColliding) {
        itsRect.translate(x, 0);
    }
}

QRect PowerUp::getItsRect() const {
    return itsRect;
}

PowerUpType PowerUp::getItsPowerUpType() const {
    return itsType;
}

QPixmap PowerUp::getItsSprite(int index) const
{
    return itsSprites.at(index);
}

void PowerUp::setItsRect(const QRect& newRect)
{
    itsRect = newRect;
}

void PowerUp::setItsPowerUpType(PowerUpType newType)
{
    itsType = newType;
}
