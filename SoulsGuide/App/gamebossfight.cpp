#include "gamebossfight.h"

GameBossFight::GameBossFight(QObject *parent) {}

void GameBossFight::setGame()
{
    itsTimer = new QTimer(this);
    itsPlayer = new Player();
    itsPopUpError = new QMessageBox();
    itsCurrentLevel = 666; // To change
    isPlayerAlive = true;

    // Setup the game timer for updating game logic
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameLoopSlot()));
    itsTimer->start(16); // Approximates 60 FPS

    // reading level data
    try
    {
        readLevel(LEVEL4);
    }
    catch (std::runtime_error &e)
    {
        fileReaderError(e);
    }

    itsPlayer->updatePlatformData(itsPlatforms);
    itsPlayer->updateEnemyData(itsEnemies);

    // Spawn point example
    itsBossSpawnPoint.setX(1000);
    itsBossSpawnPoint.setY(150);

    itsBoss = new Boss(itsPlayer, itsBossSpawnPoint, BOSSFIGHT_BOSS_WIDTH, BOSSFIGHT_BOSS_HEIGHT, 1);
}

void GameBossFight::gameLoopSlot()
{
    gameLoop();
}

// TEMP
int itsPlayerPositionDelay = 0;
QPoint itsDelayedPlayerPosition;

void GameBossFight::gameLoop()
{
    itsPlayerPositionDelay++;
    // Player movement
    itsPlayer->update();
    itsPlayer->updatePlatformData(itsPlatforms);
    itsPlayer->updateEnemyData(itsEnemies);
    itsPlayer->updateTrapData(itsTraps);
    itsPlayer->updatePowerUpData(itsPowerUps);

    if(itsPlayer->getIsPressingQ() && !itsPlayer->getIsPressingD())
    {
        itsPlayer->setIsFacingLeft(true);
        itsPlayer->setIsFacingRight(false);
        itsPlayer->setIsMovingLeft(true);
    }
    else if(itsPlayer->getIsPressingD() && !itsPlayer->getIsPressingQ())
    {
        itsPlayer->setIsFacingRight(true);
        itsPlayer->setIsFacingLeft(false);
        itsPlayer->setIsMovingRight(true);
    }

    // Boss movement:
    if(itsPlayerPositionDelay==5)
    {
        itsDelayedPlayerPosition = itsPlayer->getItsRect().center();
        itsPlayerPositionDelay=0;
    }

    itsBoss->bossFightMove(itsDelayedPlayerPosition);
    itsBoss->setItsHitbox(QRect(itsBoss->getItsRect().x() + 20, itsBoss->getItsRect().y() + 20, itsBoss->getItsRect().width() - 40, itsBoss->getItsRect().height() - 40));

    //attack
    QRect attackHitboxRight = itsPlayer->getItsAttackHitboxRight();
    QRect attackHitboxLeft = itsPlayer->getItsAttackHitboxLeft();
    for (QVector<Enemy*>::Iterator it = itsEnemies.begin(); it != itsEnemies.end();)
    {
        if (itsPlayer->getSakeTimer() > 0)
        {
            itsPlayer->setItsRect(QRect(itsPlayer->getItsRect().x(), itsPlayer->getItsRect().y(), SAKE_PLAYER_WIDTH, SAKE_PLAYER_HEIGHT));
            attackHitboxRight = QRect(itsPlayer->getItsRect().x() + itsPlayer->getItsRect().width()-60, itsPlayer->getItsRect().y(), 80, 100);
            attackHitboxLeft = QRect(itsPlayer->getItsRect().x() - itsPlayer->getItsRect().width()+160, itsPlayer->getItsRect().y(), 80, 100);
        }
        else
        {
            // Reset player size
            itsPlayer->setItsRect(QRect(itsPlayer->getItsRect().x(), itsPlayer->getItsRect().y(), PLAYER_WIDTH, PLAYER_HEIGHT));
        }
        if ((attackHitboxLeft.intersects((*it)->getItsRect()) && itsPlayer->getIsAttackingLeft())
            || (attackHitboxRight.intersects((*it)->getItsRect()) && itsPlayer->getIsAttackingRight()))
        {
            it = itsEnemies.erase(it); // erase returns the next iterator
            itsPlayer->setIsEnemyKill(true); // the player has kill an enemy (useful for the jump reset)
            itsElapsedTime -= 1000; // 1sd
            itsPlayer->setItsGoldenBuffCount(itsPlayer->getItsGoldenBuffCount()+1);
        }

        if(it != itsEnemies.end())
            it++;
    }
    // attacking boss
    if ((attackHitboxLeft.intersects(itsBoss->getItsRect()) && itsPlayer->getIsAttackingLeft())
        || (attackHitboxRight.intersects(itsBoss->getItsRect()) && itsPlayer->getIsAttackingRight()))
    {
        if(itsPlayer->getItsGoldenBuffCount() > 0 && itsBoss->getItsIframes() <= 0){
            itsPlayer->setItsGoldenBuffCount(itsPlayer->getItsGoldenBuffCount()-1);
            itsBoss->setItsHealthPoint(itsBoss->getItsHealthPoint()-1);
            itsBoss->setItsIframes(64);
        }
    }
    if(itsBoss->getItsHealthPoint() <= 0){
        itsTimer->stop();
        isBossDefeated = true;
    }
    if(itsBoss->getItsIframes()>0)
        itsBoss->setItsIframes(itsBoss->getItsIframes()-1);

    // Player death
    Animation * animDeathRight = itsPlayer->getItsAnimations().at(8);
    Animation * animDeathLeft = itsPlayer->getItsAnimations().at(9);

    if(itsPlayer->getIsCollidingEnemy() || itsPlayer->getIsCollidingTrap() || itsPlayer->getIsCollidingBoss())
    {
        itsPlayer->setIsJumping(false);
        if(itsPlayer->getItsCurrentFrame()->next == animDeathRight->first || itsPlayer->getItsCurrentFrame()->next == animDeathLeft->first)
        {
            itsTimer->stop();
            itsDisplayMessage = "";
            isPlayerAlive = false;
        }
    }

    // for indication message
    if(itsPlayer->getIsEnemyKill())
    {
        setItsDisplayMessage("Saut Remboursé");
            setItsDisplayDuration(100);
    }

    //player movement left and right
    itsPlayer->bossFightMove(1 * itsPlayer->getIsMovingRight() - 1 * itsPlayer->getIsMovingLeft());
}
