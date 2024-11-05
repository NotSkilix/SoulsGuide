#include "player.h"

// Base Constructor
Player::Player()
    : itsRect(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-50, PLAYER_WIDTH, PLAYER_HEIGHT), // Set the player's main rectangle with its position
    itsSpeed(5),
    itsVerticalVelocity(0)
{
    // putting up collision points first time
    itsCollisionPointTop.setRect(itsRect.x() + itsRect.width() / 2 - 10, itsRect.y()+20, 20, 10);
    itsCollisionPointLeft.setRect(itsRect.x() + 55, itsRect.y() + 30, 10, 30);
    itsCollisionPointRight.setRect(itsRect.x() + itsRect.width()-65, itsRect.y()+30, 10, 30);
    itsCollisionPointBottom.setRect(this->itsRect.x()+this->itsRect.width()/2-10, this->itsRect.y()+this->itsRect.height()-10, 20, 10);

    // putting up attack hitboxes
    itsAttackHitboxRight.setRect(itsRect.x() + itsRect.width()-60, itsRect.y(), 60, 80);
    itsAttackHitboxLeft.setRect(itsRect.x(), itsRect.y(), 60, 80);

    // Initializing values of power up timers
    SalmonSushiTimer = 0;
    SakeTimer = 0;
    WoodenSandalsTimer = 0;

    //animations initialization
    loadAnimation("idleRight", 8);
    loadAnimation("idleLeft", 8);
    loadAnimation("runRight", 8);
    loadAnimation("runLeft", 8);
    loadAnimation("jumpRight", 2);
    loadAnimation("jumpLeft", 2);
    loadAnimation("fallRight", 2);
    loadAnimation("fallLeft", 2);
    loadAnimation("deathRight", 6);
    loadAnimation("deathLeft", 6);
    loadAnimation("attackRight", 6);
    loadAnimation("attackLeft", 6);
    loadAnimation("hitRight", 4);
    loadAnimation("hitLeft", 4);
    loadAnimation("getPowerup", 8);

    setItsCurrentFrame(0);
}

// Constructor With spawn points || should not be used right now, player kind of needs to be in center of screen until boss fight
Player::Player(QPoint spawn)
    : itsRect(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-50, PLAYER_WIDTH, PLAYER_HEIGHT), // Set the player's main rectangle
    itsSpeed(5),
    itsVerticalVelocity(0)
{
    // putting up collision points first time
    itsCollisionPointTop.setRect(itsRect.x() + itsRect.width() / 2 - 10, itsRect.y()+20, 20, 10);
    itsCollisionPointLeft.setRect(itsRect.x() + 55, itsRect.y() + 30, 10, 30);
    itsCollisionPointRight.setRect(itsRect.x() + itsRect.width()-65, itsRect.y()+30, 10, 30);
    itsCollisionPointBottom.setRect(this->itsRect.x()+this->itsRect.width()/2-10, this->itsRect.y()+this->itsRect.height()-10, 20, 10);

    // putting up attack hitboxes
    itsAttackHitboxRight.setRect(itsRect.x() + itsRect.width()-60, itsRect.y(), 60, 80);
    itsAttackHitboxLeft.setRect(itsRect.x(), itsRect.y(), 60, 80);

    // Initializing values of power up timers
    SalmonSushiTimer = 0;
    SakeTimer = 0;
    WoodenSandalsTimer = 0;

    //animations initialization
    loadAnimation("idleRight", 8); //0
    loadAnimation("idleLeft", 8);  //1
    loadAnimation("runRight", 8);  //2
    loadAnimation("runLeft", 8);   //3
    loadAnimation("jumpRight", 2); //4
    loadAnimation("jumpLeft", 2);  //5
    loadAnimation("fallRight", 2); //6
    loadAnimation("fallLeft", 2);  //7
    loadAnimation("deathRight", 6);//8
    loadAnimation("deathLeft", 6); //9
    loadAnimation("attackRight", 6);//10
    loadAnimation("attackLeft", 6); //11
    loadAnimation("hitRight", 4);//12
    loadAnimation("hitLeft", 4); //13
    loadAnimation("getPowerup", 8); //14

    setItsCurrentFrame(0);
}

Player::~Player() {}

// Allow the player to jump if he is on the ground
void Player::jump()
{
    if (isCollidingBottom || isEnemyKill)
    {
        itsVerticalVelocity = -15; // Adjust jump speed as needed
        if(SalmonSushiTimer > 0)
            itsVerticalVelocity = -20; // make the player jump higher with salmon sushi
        isCollidingBottom = false;// Player is no longer on the ground
        isEnemyKill = false; // Player use his double jump
    }
}

void Player::setItsCurrentFrame(int index)
{
    if(index != itsAnimationIndex)
    {
        Animation * anim = itsAnimations.at(index);
        itsCurrentFrame = anim->first;
        itsAnimationIndex = index;
    }
}

void Player::setItsSecondaryCurrentFrame(int index)
{
    if(index != itsSecondaryAnimationIndex)
    {
        Animation * anim = itsAnimations.at(index);
        itsSecondaryFrame = anim->first;
        itsSecondaryAnimationIndex = index;
    }
}

void Player::playAnimation()
{
    if(itsCurrentFrame->next != nullptr)
        itsCurrentFrame = itsCurrentFrame->next;
    else
        qDebug() << "no next frame";

    //checks if the attack animation is finished then player is no longer attacking
    Animation * animAttackRight = itsAnimations.at(10);
    Animation * animAttackLeft = itsAnimations.at(11);
    if((itsAnimationIndex == 10 && itsCurrentFrame->next == animAttackRight->first) ||
       (itsAnimationIndex == 11 && itsCurrentFrame->next == animAttackLeft->first) )
        isAttacking = false;

    //secondary animations
    if(itsSecondaryAnimationIndex != -1)
    {
        Animation * secondaryAnim = itsAnimations.at(itsSecondaryAnimationIndex);
        if(itsSecondaryFrame->next == secondaryAnim->first)
        {
            itsSecondaryFrame = nullptr;
            itsSecondaryAnimationIndex = -1;
        }
        else
            itsSecondaryFrame = itsSecondaryFrame->next;
    }
}

void Player::loadAnimation(QString animationName, int frameNumber)
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

// Update the player's position based on gravity and current vertical velocity
void Player::update()
{
    // Apply gravity to vertical velocity
    itsVerticalVelocity += GRAVITY; // Gravity pull, adjust as necessary for game physics

    // Update the player's vertical position
    itsRect.translate(0, itsVerticalVelocity);

    if(isJumping)
        jump();

    isCollidingBottom = false;
    isCollidingTop = false;
    isCollidingLeft = false;
    isCollidingRight = false;

    // apply faster speed if on Salmon sushi
    if(SalmonSushiTimer > 0)
        itsSpeed = 7;
    else
        itsSpeed = 5;

    // Check for collision with each platform
    Platform bottomCollidedPlatform = Platform(0,0,0,0);
    Platform sideCollidedPlatform = Platform(0,0,0,0);
    for (const Platform& platform : itsPlatforms) {
        // Check each collision rectangle and set corresponding flags
        if (itsCollisionPointTop.intersects(platform.getItsRect())) {
            isCollidingTop = true;
            itsVerticalVelocity = abs(itsVerticalVelocity)/1.5;
        }
        if (itsCollisionPointBottom.intersects(platform.getItsRect()) && itsVerticalVelocity > 0)
        {
            bottomCollidedPlatform = platform;
            itsVerticalVelocity = 0;  // Stop vertical movement
            isCollidingBottom = true;  // Player is on the ground
        }
        if (itsCollisionPointLeft.intersects(platform.getItsRect()))
        {
            sideCollidedPlatform = platform;
            isCollidingLeft = true;
        }
        if (itsCollisionPointRight.intersects(platform.getItsRect()))
        {
            sideCollidedPlatform = platform;
            isCollidingRight = true;
        }
    }

    if(!isCollidingTop && isCollidingBottom)
        itsRect.moveBottom(bottomCollidedPlatform.getItsRect().top());  // Place the player on top of the platform
    if(isCollidingRight && isCollidingBottom && isCollidingTop)
        itsRect.moveRight(itsRect.right() - (itsCollisionPointRight.right() - sideCollidedPlatform.getItsRect().left()));
    if(isCollidingLeft && isCollidingBottom && isCollidingTop)
        itsRect.moveRight(itsRect.right() + (sideCollidedPlatform.getItsRect().right() - itsCollisionPointLeft.left()));

    // Check for enemy and flag collision
    for(Enemy * enemy : itsEnemies){
        if(itsCollisionPointBottom.intersects(enemy->getItsRect()) || itsCollisionPointTop.intersects(enemy->getItsRect()) ||
            itsCollisionPointLeft.intersects(enemy->getItsRect()) || itsCollisionPointRight.intersects(enemy->getItsRect())){
            if(itsArmorCount > 0 && itsArmorDuration == 0){
                itsArmorCount--;
                itsArmorDuration = ARMOR_DURATION;
            }
            else if(itsArmorCount <= 0 && itsArmorDuration == 0)
                isCollidingEnemy = true;
        }
    }
    for(const Trap& trap : itsTraps){
        if((itsCollisionPointBottom.intersects(trap.getItsRect()) || itsCollisionPointTop.intersects(trap.getItsRect()) ||
            itsCollisionPointLeft.intersects(trap.getItsRect()) || itsCollisionPointRight.intersects(trap.getItsRect()))
            && WoodenSandalsTimer <= 0){
            if(itsArmorCount > 0 && itsArmorDuration == 0){
                itsArmorCount--;
                itsArmorDuration = ARMOR_DURATION;
            }
            else if(itsArmorCount <= 0 && itsArmorDuration == 0)
                isCollidingTrap = true;
        }
    }
    // handle armor timer
    if(itsArmorDuration > 0){
        itsArmorDuration--;
    }

    for (QVector<PowerUp>::iterator it = itsPowerUps.begin(); it != itsPowerUps.end();) {
        if(itsCollisionPointBottom.intersects(it->getItsRect()) || itsCollisionPointTop.intersects(it->getItsRect()) ||
            itsCollisionPointLeft.intersects(it->getItsRect()) || itsCollisionPointRight.intersects(it->getItsRect()))
        {
            switch (it->getItsPowerUpType()) {
            case SalmonSushi:
                SalmonSushiTimer = POWERUP_TIME*FPS;
                setItsSecondaryCurrentFrame(14);
                break;
            case Sake:
                SakeTimer = POWERUP_TIME*FPS;
                setItsSecondaryCurrentFrame(14);
                break;
            case WoodenSandals:
                WoodenSandalsTimer = POWERUP_TIME*FPS;
                setItsSecondaryCurrentFrame(14);
                break;
            default:
                break;
            }
            break; // Erase and get the next iterator
        } else {
            ++it;
        }
    }
    // Handle Power Ups
    if(SalmonSushiTimer > 0)
        SalmonSushiTimer--;
    if(SakeTimer > 0)
        SakeTimer--;
    if(WoodenSandalsTimer > 0)
        WoodenSandalsTimer--;

    // Update the hitbox of the attacks
    itsAttackHitboxRight.setRect(itsRect.x() + itsRect.width()-60, itsRect.y(), 60, 80);
    itsAttackHitboxLeft.setRect(itsRect.x(), itsRect.y(), 60, 80);

    // adjust position of collision points and hitboxes
    itsCollisionPointTop.setRect(itsRect.x() + itsRect.width() / 2 - 10, itsRect.y() + 20, 20, 10);
    itsCollisionPointLeft.setRect(itsRect.x() + 70, itsRect.y() + 30, 15, 40);
    itsCollisionPointRight.setRect(itsRect.x() + itsRect.width() - 85, itsRect.y() + 30, 15, 40);
    itsCollisionPointBottom.setRect(this->itsRect.x() + this->itsRect.width() / 2 - 10, this->itsRect.y() + this->itsRect.height() - 10, 20, 10);
}

void Player::updatePlatformData(QVector<Platform> platforms) {
    this->itsPlatforms = platforms;
}

void Player::updateEnemyData(QVector<Enemy*> enemies) {
    this->itsEnemies = enemies;
}

void Player::updateTrapData(QVector<Trap> traps){
    this->itsTraps = traps;
}

void Player::updatePowerUpData(QVector<PowerUp> powerUps){
    itsPowerUps = powerUps;
}

void Player::bossFightMove(int direction)
{
    itsRect.translate(direction * itsSpeed, 0);
}

//getters and setters
QRect Player::getItsCollisionPointBottom() const
{
    return itsCollisionPointBottom;
}

void Player::setItsCollisionPointBottom(const QRect &newItsCollisionPointBottom)
{
    itsCollisionPointBottom = newItsCollisionPointBottom;
}

QRect Player::getItsCollisionPointRight() const
{
    return itsCollisionPointRight;
}

void Player::setItsCollisionPointRight(const QRect &newItsCollisionPointRight)
{
    itsCollisionPointRight = newItsCollisionPointRight;
}

QRect Player::getItsCollisionPointLeft() const
{
    return itsCollisionPointLeft;
}

void Player::setItsCollisionPointLeft(const QRect &newItsCollisionPointLeft)
{
    itsCollisionPointLeft = newItsCollisionPointLeft;
}

QRect Player::getItsCollisionPointTop() const
{
    return itsCollisionPointTop;
}

void Player::setItsCollisionPointTop(const QRect &newItsCollisionPointTop)
{
    itsCollisionPointTop = newItsCollisionPointTop;
}

bool Player::getIsCollidingRight() const
{
    return isCollidingRight;
}

void Player::setIsCollidingRight(bool newIsCollidingRight)
{
    isCollidingRight = newIsCollidingRight;
}

bool Player::getIsCollidingLeft() const
{
    return isCollidingLeft;
}

void Player::setIsCollidingLeft(bool newIsCollidingLeft)
{
    isCollidingLeft = newIsCollidingLeft;
}

bool Player::getIsCollidingTop() const
{
    return isCollidingTop;
}

void Player::setIsCollidingTop(bool newIsCollidingTop)
{
    isCollidingTop = newIsCollidingTop;
}

bool Player::getIsCollidingBottom() const
{
    return isCollidingBottom;
}

bool Player::getIsAttackingLeft() const
{
    return isAttackingLeft;
}

bool Player::getIsAttackingRight() const
{
    return isAttackingRight;
}

QRect Player::getItsAttackHitboxRight() const
{
    return itsAttackHitboxRight;
}

QRect Player::getItsAttackHitboxLeft() const
{
    return itsAttackHitboxLeft;
}


void Player::setIsCollidingBottom(bool newIsCollidingBottom)
{
    isCollidingBottom = newIsCollidingBottom;
}

bool Player::getIsCollidingEnemy() const
{
    return isCollidingEnemy;
}

void Player::setIsCollidingEnemy(bool newIsCollidingEnemy)
{
    isCollidingEnemy = newIsCollidingEnemy;
}

bool Player::getIsCollidingTrap() const
{
    return isCollidingTrap;
}

void Player::setIsCollidingTrap(bool newIsCollidingTrap)
{
    isCollidingTrap = newIsCollidingTrap;
}

QRect Player::getItsRect() const
{
    return itsRect;
}

void Player::setItsRect(const QRect &newItsRect)
{
    itsRect = newItsRect;
}

QVector<Platform> Player::getItsPlatforms() const
{
    return itsPlatforms;
}

void Player::setItsPlatforms(const QVector<Platform> &newItsPlatforms)
{
    itsPlatforms = newItsPlatforms;
}

QVector<Enemy*> Player::getItsEnemies() const
{
    return itsEnemies;
}

void Player::setItsEnemies(const QVector<Enemy*> &newItsEnemies)
{
    itsEnemies = newItsEnemies;
}

void Player::setIsAttackingLeft(bool newIsAttackingLeft) {
    isAttackingLeft = newIsAttackingLeft;
}

void Player::setIsAttackingRight(bool newIsAttackingRight) {
    isAttackingRight = newIsAttackingRight;
}

void Player::setItsAttackHitboxRight(const QRect& newHitboxRight)
{
    itsAttackHitboxRight = newHitboxRight;
}

void Player::setItsAttackHitboxLeft(const QRect& newHitboxLeft)
{
    itsAttackHitboxLeft = newHitboxLeft;
}

bool Player::getIsEnemyKill() const
{
    return isEnemyKill;
}

void Player::setIsEnemyKill(bool newIsEnemyKill)
{
    isEnemyKill = newIsEnemyKill;
}

QVector<Trap> Player::getItsTraps() const
{
    return itsTraps;
}

QVector<PowerUp> Player::getItsPowerUps() const
{
    return itsPowerUps;
}

void Player::setItsTraps(const QVector<Trap> &newItsTraps)
{
    itsTraps = newItsTraps;
}

int Player::getItsSpeed() const
{
    return itsSpeed;
}

void Player::setItsSpeed(int newItsSpeed)
{
    itsSpeed = newItsSpeed;
}

float Player::getItsVerticalVelocity() const
{
    return itsVerticalVelocity;
}

void Player::setItsVerticalVelocity(float newItsVerticalVelocity)
{
    itsVerticalVelocity = newItsVerticalVelocity;
}

bool Player::getIsMovingLeft() const
{
    return isMovingLeft;
}

void Player::setIsMovingLeft(bool newIsMovingLeft)
{
    isMovingLeft = newIsMovingLeft;
}

bool Player::getIsMovingRight() const
{
    return isMovingRight;
}

void Player::setIsMovingRight(bool newIsMovingRight)
{
    isMovingRight = newIsMovingRight;
}

void Player::setItsPowerUps(const QVector<PowerUp> &newItsPowerUps)
{
    itsPowerUps = newItsPowerUps;
}

int Player::getSalmonSushiTimer() const {
    return SalmonSushiTimer;
}

void Player::setSalmonSushiTimer(int timer) {
    SalmonSushiTimer = timer;
}

int Player::getSakeTimer() const {
    return SakeTimer;
}

void Player::setSakeTimer(int timer) {
    SakeTimer = timer;
}

int Player::getWoodenSandalsTimer() const {
    return WoodenSandalsTimer;
}

void Player::setWoodenSandalsTimer(int timer) {
    WoodenSandalsTimer = timer;
}

Frame * Player::getItsCurrentFrame() const
{
    return itsCurrentFrame;
}

Frame * Player::getItsSecondaryFrame() const
{
    return itsSecondaryFrame;
}

bool Player::getIsFacingLeft() const {
    return isFacingLeft;
}

bool Player::getIsFacingRight() const {
    return isFacingRight;
}

void Player::setIsFacingLeft(bool newIsFacingLeft) {
    isFacingLeft = newIsFacingLeft;
}

void Player::setIsFacingRight(bool newIsFacingRight) {
    isFacingRight = newIsFacingRight;
}

bool Player::getIsCollidingBoss() const{
    return isCollidingBoss;
}

void Player::setIsCollidingBoss(bool newIsCollidingBoss)
{
    isCollidingBoss = newIsCollidingBoss;
}

QVector<Animation *> Player::getItsAnimations() const
{
    return itsAnimations;
}

int Player::getItsAnimationIndex() const
{
    return itsAnimationIndex;
}

int Player::getItsSecondaryAnimationIndex() const
{
    return itsSecondaryAnimationIndex;
}

void Player::setIsAttacking(bool newIsattacking)
{
    isAttacking = newIsattacking;
}

bool Player::getIsAttacking() const
{
    return isAttacking;
}

void Player::setIsJumping(bool newIsJumping)
{
    isJumping = newIsJumping;
}

int Player::getItsArmorCount() const
{
    return itsArmorCount;
}

void Player::setItsArmorCount(int newCount)
{
    itsArmorCount = newCount;
}

int Player::getItsArmorDuration() const {
    return itsArmorDuration;
}

void Player::setItsArmorDuration(int newDuration) {
    itsArmorDuration = newDuration;
}

int Player::getItsGoldenBuffCount() const{
    return itsGoldenBuffCount;
}

void Player::setItsGoldenBuffCount(const int newCount)
{
    itsGoldenBuffCount=newCount;
}

bool Player::getIsPressingD() const
{
    return isPressingD;
}

bool Player::getIsPressingQ() const
{
    return isPressingQ;
}

void Player::setIsPressingD(bool press)
{
    isPressingD = press;
}

void Player::setIsPressingQ(bool press)
{
    isPressingQ = press;
}
