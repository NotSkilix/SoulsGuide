#ifndef GAMEBOSSFIGHT_H
#define GAMEBOSSFIGHT_H

#include "game.h"

/**
* @brief The GameBossFight class is the model of the boss fight final level.
* It creates and manages this level and his functioning.
* @author GIGNOUX Victor
* @version 1
* @date 5 June 2024
*/
class GameBossFight : public Game
{
public:
    GameBossFight(QObject * parent = nullptr);
    void setGame() override;
    void gameLoop() override;

private slots:
    void gameLoopSlot();
};

#endif // GAMEBOSSFIGHT_H
