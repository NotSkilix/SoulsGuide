#include "game.h"

Game::Game(QObject *parent) : QObject(parent) {}

Game::~Game()
{}

void Game::setGame()
{
    itsTimer = new QTimer(this);
    itsPlayer = new Player();
    itsPopUpError = new QMessageBox();
    itsCurrentLevel = 1;
    itsElapsedTime = 0;
    isPlayerAlive = true;

    // Setup the game timer for updating game logic
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameLoopSlot()));
    itsTimer->start(16); // Approximates 60 FPS

    // reading level data
    try
    {
        readLevel(LEVEL1);
    }
    catch (std::runtime_error &e)
    {
        fileReaderError(e);
    }


    itsPlayer->updatePlatformData(itsPlatforms);
    itsPlayer->updateEnemyData(itsEnemies);

    // Spawn point example
    itsBossSpawnPoint.setX(0);
    itsBossSpawnPoint.setY(150);

    itsBoss = new Boss(itsPlayer, itsBossSpawnPoint, BOSS_WIDTH, BOSS_HEIGHT, 3);
}

void Game::gameLoopSlot()
{
    gameLoop();
}

void Game::gameLoop()
{
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
    
    // Player Attack
    for (QVector<Enemy*>::Iterator it = itsEnemies.begin(); it != itsEnemies.end();)
    {
        QRect attackHitboxRight = itsPlayer->getItsAttackHitboxRight();
        QRect attackHitboxLeft = itsPlayer->getItsAttackHitboxLeft();
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
        }

        if(it != itsEnemies.end())
            it++;
    }
    if(itsPlayer->getIsEnemyKill()){ // for indication message
        setItsDisplayMessage("Saut Remboursé");
        setItsDisplayDuration(100);
    }
    // Player touch power up
    for (auto it = itsPowerUps.begin(); it != itsPowerUps.end();) {
        if (itsPlayer->getItsCollisionPointBottom().intersects(it->getItsRect()) || itsPlayer->getItsCollisionPointTop().intersects(it->getItsRect()) ||
            itsPlayer->getItsCollisionPointLeft().intersects(it->getItsRect()) || itsPlayer->getItsCollisionPointRight().intersects(it->getItsRect())) {
            switch(it->getItsPowerUpType()){
            case SalmonSushi:
                setItsDisplayMessage("+ Vitesse \n + Saut");
                break;
            case WoodenSandals:
                setItsDisplayMessage("Immmunisé \n au pièges");
                break;
            case Sake:
                setItsDisplayMessage("+ Taille");
                break;
            default:
                setItsDisplayMessage("Power Up \n Inconnu");
                break;
            }
            setItsDisplayDuration(400);
            it = itsPowerUps.erase(it);
        } else {
            ++it;
        }
    }

    // Update player state and position
    itsPlayer->update();
    if(!itsPlayer->getIsCollidingEnemy() && !itsPlayer->getIsCollidingTrap() && !itsPlayer->getIsCollidingBoss())
    {
        for(QVector<Enemy*>::iterator it = itsEnemies.begin(); it != itsEnemies.end();it++ ) {
            (*it)->updatePosition();
            (*it)->updateEnemyRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
            (*it)->updateEnemyRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());
        }
        //updates platforms positions depending to the player's position
        for(QVector<Platform>::iterator it = itsPlatforms.begin(); it != itsPlatforms.end(); it++)
        {
            it->updatePlatformRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
            it->updatePlatformRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());
        }
        for(QVector<Trap>::iterator it = itsTraps.begin(); it != itsTraps.end(); it++)
        {
            it->updateTrapRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
            it->updateTrapRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());
        }
        for (QVector<PowerUp>::iterator it = itsPowerUps.begin(); it != itsPowerUps.end(); ++it)
        {
            it->updatePowerUpRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
            it->updatePowerUpRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());
        }

        itsFirstFlag.updateFlagRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
        itsFirstFlag.updateFlagRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());

        itsBoss->move();
        itsBoss->updateBossRelativePosition(itsPlayer->getIsMovingRight() * -itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingRight());
        itsBoss->updateBossRelativePosition(itsPlayer->getIsMovingLeft() * itsPlayer->getItsSpeed(), itsPlayer->getIsCollidingLeft());
        itsBoss->setItsHitbox(QRect(itsBoss->getItsRect().x() + 20, itsBoss->getItsRect().y() + 20, itsBoss->getItsRect().width() - 40, itsBoss->getItsRect().height() - 40));
    }

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

    // Player touch flag
    if (itsPlayer->getItsCollisionPointBottom().intersects(itsFirstFlag.getItsRect()) || itsPlayer->getItsCollisionPointTop().intersects(itsFirstFlag.getItsRect()) ||
        itsPlayer->getItsCollisionPointLeft().intersects(itsFirstFlag.getItsRect()) || itsPlayer->getItsCollisionPointRight().intersects(itsFirstFlag.getItsRect())) {
        // give armors
        if(itsCurrentLevel == 2 || itsCurrentLevel == 3)
            itsPlayer->setItsArmorCount(itsPlayer->getItsArmorCount()+1);
        itsCurrentLevel++;
        if(itsCurrentLevel < 4) goToLevel(itsCurrentLevel);
    }
}

void Game::readLevel(string aLevel)
{
    ifstream file(aLevel);

    if (!file.is_open())
    {
        throw std::runtime_error("The level file is damaged or missing.");
    }

    int enemyCount = 0;
    int platformCount = 0;
    int trapCount = 0;
    int flagCount = 0;
    int powerUpCount = 0;
    bool spawnExist = false;

    std::string line;
    std::string currentSection;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        if (line == "platform" || line == "trap" || line == "enemy" || line == "flag" || line == "spawn" || line == "SalmonSushi" || line == "Sake" || line == "WoodenSandals")
        {
            currentSection = line;
            continue;
        }

        std::istringstream stream(line);
        std::string token;
        std::vector<int> values;

        while (std::getline(stream, token, ';')) {
            values.push_back(std::stoi(token));
        }

        if (currentSection == "platform")
        {
            if (values.size() == 4) {
                Platform platform = Platform(values[0], values[1], values[2], values[3]);
                platform.loadSprites(itsCurrentLevel);
                itsPlatforms.append(platform);
                platformCount++;
            }
        } else if (currentSection == "trap") {
            if (values.size() == 4) {
                itsTraps.append(Trap(QPoint(values[0], values[1]), values[2], values[3]));
                trapCount++;
            }
        } else if (currentSection == "enemy") {
            if (values.size() == 10) {
                itsEnemies.append(new Enemy(QRect(values[0], values[1], values[2], values[3]),
                                        QPoint(values[4], values[5]),
                                        QPoint(values[6], values[7]),
                                        values[8], values[9]));
                enemyCount++;
            }
        } else if (currentSection == "flag") {
            if (values.size() == 3) {
                itsFirstFlag = Flag(QPoint(values[0], values[1]), values[2]);
                flagCount++;
            }
        } else if (currentSection == "spawn") {
            if(values.size() == 2){
                delete itsPlayer;
                itsPlayer=nullptr;
                itsPlayer = new Player(QPoint(values[0], values[1]));
                spawnExist = true;
            }
        } else if (currentSection == "Sake" || currentSection == "WoodenSandals" || currentSection == "SalmonSushi"){
            powerUpCount++;
            if(values.size() == 4){
                itsPowerUps.append(PowerUp(QPoint(values[0], values[1]), values[2], values[3], currentSection));
            }
        }
    }

    qDebug()<<" Enemy Count : "<<enemyCount<<"\n"<<"Platform Count : "<<platformCount<<"\n"
             <<"Trap count :"<<trapCount<<"\n"<<"Flag Count :"<<flagCount<<"\n"<<"Is there spawn ? : "<<spawnExist<<"\n"
             <<"Power Up Count :"<<powerUpCount<<"\n";

    file.close();
}

void Game::deleteLevel()
{
    itsPlatforms.clear();
    itsTraps.clear();
    itsEnemies.clear();
    itsPowerUps.clear();
}

void Game::goToLevel(int level){
    // Delete level elements
    itsPlatforms.clear();
    itsTraps.clear();
    itsEnemies.clear();
    itsPowerUps.clear();

    delete itsBoss;
    itsBoss=nullptr;

    int armorCount = itsPlayer->getItsArmorCount();

    delete itsPlayer;
    itsPlayer=nullptr;

    deleteLevel();

    // initialize new level
    string strLevel;
    itsPlayer = new Player();
    itsPlayer->setItsArmorCount(armorCount);
    itsPopUpError = new QMessageBox();

    switch(level)
    {
        case 1: strLevel = LEVEL1; break;
        case 2: strLevel = LEVEL2; break;
        case 3: strLevel = LEVEL3; break;
        case 666: strLevel = LEVEL4; break;
    }

    // reading level data
    try
    {
        readLevel(strLevel);
    }
    catch (std::runtime_error &e)
    {
        fileReaderError(e);
    }


    itsPlayer->updatePlatformData(itsPlatforms);
    itsPlayer->updateEnemyData(itsEnemies);

    // Spawn point example
    itsBossSpawnPoint.setX(0);
    itsBossSpawnPoint.setY(150);

    itsBoss = new Boss(itsPlayer, itsBossSpawnPoint, BOSS_WIDTH, BOSS_HEIGHT, 3);
}

QTimer *Game::getItsTimer() const
{
    return itsTimer;
}

QMessageBox *Game::getItsPopupError() const
{
    return itsPopUpError;
}

Player *Game::getItsPlayer() const
{
    return itsPlayer;
}

Boss *Game::getItsBoss() const
{
    return itsBoss;
}

QVector<Platform> Game::getItsPlatforms() const
{
    return itsPlatforms;
}

QVector<Enemy*> Game::getItsEnemies() const
{
    return itsEnemies;
}

QVector<Trap> Game::getItsTraps() const
{
    return itsTraps;
}

QVector<PowerUp> Game::getItsPowerUps() const
{
    return itsPowerUps;
}

Flag Game::getItsFirstFlag() const
{
    return itsFirstFlag;
}

int Game::getItsElapsedTime() const
{
    return itsElapsedTime;
}

void Game::setItsElapsedTime(int time)
{
    itsElapsedTime = time;
}

QString Game::loadBackground(string background)
{
    ifstream file;
        file.open(background);
    if(file.is_open())
    {
        file.close();

        return QString::fromStdString(background);
    }
    {
        throw std::runtime_error("The background file is damaged or missing.");
    }
}

void Game::killApp()
{
    exit(0);
}

void Game::fileReaderError(exception &e)
{
    itsTimer->stop();
    QString messageError = e.what();
    messageError.push_back("\nThe file might be missing or is damaged. \nFix the missing file and run the game again");
    itsPopUpError->setText(messageError);
    itsPopUpError->setStandardButtons(QMessageBox::Ok);
    itsPopUpError->show();

    connect(itsPopUpError, SIGNAL(accepted()), this, SLOT(killApp())); //If the button "ok" is pressed
    connect(itsPopUpError, SIGNAL(rejected()), this, SLOT(killApp())); // If the window's cross is pressed
}

int Game::getItsCurrentLevel() const
{
    return itsCurrentLevel;
}

void Game::setItsCurrentLevel(const int currentLevel)
{
    itsCurrentLevel = currentLevel;
}

bool Game::getIsPlayerAlive() const
{
    return isPlayerAlive;
}

void Game::setIsPlayerAlive(const bool playerStatus)
{
    isPlayerAlive = playerStatus;
}

void Game::setItsDisplayDuration(const int duration){
    itsDisplayDuration = duration;
}

int Game::getItsDisplayDuration(){
    return itsDisplayDuration;
}

void Game::setItsDisplayMessage(const std::string message){
    itsDisplayMessage = message;
}

std::string Game::getItsDisplayMessage(){
    return itsDisplayMessage;
}
bool Game::getIsBossDefeated() const
{
    return isBossDefeated;
}

void Game::setIsBossDefeated(bool newIsBossDefeated)
{
    isBossDefeated = newIsBossDefeated;
}

void Game::pauseGame(const bool newGameStatus)
{
    if(newGameStatus == true)
    {
        itsTimer->stop();
    }
    else
    {
        itsTimer->start(16); // restart timer at 60fps
    }
}
