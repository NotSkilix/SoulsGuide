#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent),
    itsGame(new Game(this)),
    itsTimer(new QTimer(this)),
    itsAnimationTimer(new QTimer(this)),
    itsMusicPlayer(new QMediaPlayer()),
    itsAudio(new QAudioOutput()),
    itsTimerLabel(new QLabel(this)),
    itsGrid(new QGridLayout(this)),
    itsLabel(new QLabel(this)),
    itsBackgroundGif (new QMovie(this)),
    itsMovieStorage(new QLabel(this)),
    itsIndicationLabel(new QLabel(this)),
    itsArmorCount(new QLabel(this)),
    itsGoldenBuffCount(new QLabel(this))
{
    try
    {
        displayMenu(MAINMENU);
        // Connect the music player to get when the music is over and replay it depending on its level
        connect(itsMusicPlayer, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(musicStatusChanged(QMediaPlayer::MediaStatus)));
    }
    catch(exception &e)
    {
        qDebug() << e.what();
    }

    this->setWindowTitle("Soul's Guide");
    this->setFixedSize(1260,740);

    QIcon gameIcon;
    gameIcon.addFile("../game_ressources/Logo_SoulsGuide.png");
    this->setWindowIcon(gameIcon);

}

GameWindow::~GameWindow() {}

void GameWindow::animationsManager()
{
    itsGame->getItsPlayer()->playAnimation();
    for (Enemy * enemy : itsGame->getItsEnemies())
    {
        enemy->playAnimation();
    }
}

void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // paint the background
    if(itsCurrentInterface == MAINMENU)
    {
        QPoint whereToAppear = {0,0};
        painter.drawPixmap(whereToAppear,itsBackground);

        //350 240;
        QPixmap gameLogo;
        QString gamePath;

        whereToAppear = {WINDOW_WIDTH/2-(350/2),WINDOW_HEIGHT/10};

        gamePath.append("../game_ressources/gameLogo.png");

        gameLogo.load(gamePath);

        painter.drawPixmap(whereToAppear,gameLogo);

    }

    // paint the background
    else if(itsCurrentInterface == DEATHSCREEN)
    {
        QPoint whereToAppear = {0,0};
        painter.drawPixmap(whereToAppear,itsBackground);

        //350 240;
        QPixmap gameLogo;
        QString gamePath;

        whereToAppear = {WINDOW_WIDTH/2-(350/2),WINDOW_HEIGHT/10};

        gamePath.append("../game_ressources/deathScreen.png");

        gameLogo.load(gamePath);

        painter.drawPixmap(whereToAppear,gameLogo);
    }

    else if(itsCurrentInterface == LEADERBOARD)
    {
        QPoint whereToAppear = {0,0};
        painter.drawPixmap(whereToAppear,itsBackground);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(255,230,210));
        int size = 450;
        QRect leaderBoardRect = QRect(WINDOW_WIDTH/2 - size/2,WINDOW_HEIGHT/2 - size/2,size,size);
        painter.drawRect(leaderBoardRect);

        painter.setPen(QPen(Qt::black, 5));
        painter.drawLine(WINDOW_WIDTH/2 - size/2 + 60,
                         WINDOW_HEIGHT/2 - size/2 + 10,
                         WINDOW_WIDTH/2 - size/2 + 60,
                         WINDOW_HEIGHT/2 - size/2 + size - 10);
        for(int i = 1; i < 10;i++)
        {
            painter.drawLine(WINDOW_WIDTH/2 - size/2 + 10,
                            WINDOW_HEIGHT/2 - size/2 + i*(size/10),
                            WINDOW_WIDTH/2 - size/2 + size - 10,
                            WINDOW_HEIGHT/2 - size/2 + i*(size/10));
        }

        //lecture du fichier de leader board
        ifstream iFile("../App/leaderBoard.txt");
        string playerName, score;
        int counter = 0;
        if (!iFile.is_open())
        {
            throw std::runtime_error("The level file is damaged or missing.");
        }
        else
        {
            QFont font = QFont();
            font.setPointSize(20);
            painter.setFont(font);
            while(!iFile.eof())
            {
                if(iFile >> playerName >> score)
                {
                    painter.drawText(QPointF(WINDOW_WIDTH/2 - size/2 + 30, WINDOW_HEIGHT/2 - size/2 + 35 + (size/10) * counter), QString::number(counter+1));//number
                    painter.drawText(QPointF(WINDOW_WIDTH/2 - size/2 + 80, WINDOW_HEIGHT/2 - size/2 + 35 + (size/10) * counter), QString::fromStdString(playerName));//player
                    painter.drawText(QPointF(WINDOW_WIDTH/2 - size/2 + 320, WINDOW_HEIGHT/2 - size/2 + 35 + (size/10) * counter), QString::fromStdString(score));//score
                    counter++;
                }
            }
        }
        iFile.close();
    }

    // paint the pause background (game)
    else if(itsCurrentInterface == PAUSED)
    {
        itsCurrentInterface=GAME;
    }
    // Paint the game

    else if(itsCurrentInterface == GAME)
    {
        // Paint the background
        QPoint whereToAppear = {0,0};
        painter.drawPixmap(whereToAppear,itsBackground);


//        if(itsGame->getItsCurrentLevel() > 3)
//        {
//            displayLeaderBoard();
//            itsGame->setItsCurrentLevel(1);
//        }

        /*
        // Paint the background
        QPoint whereToAppear = {0,0};
        painter.drawPixmap(whereToAppear,itsBackground);
        */
        /*
        // Collision paint
        painter.setBrush(Qt::magenta);
        if (itsGame->getItsPlayer()->getIsCollidingBottom()) {
            painter.setBrush(Qt::black);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointBottom());
        } else {
            painter.setBrush(Qt::magenta);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointBottom());
        }

        if (itsGame->getItsPlayer()->getIsCollidingRight()) {
            painter.setBrush(Qt::black);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointRight());
        } else {
            painter.setBrush(Qt::magenta);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointRight());
        }

        if (itsGame->getItsPlayer()->getIsCollidingTop()) {
            painter.setBrush(Qt::black);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointTop());
        } else {
            painter.setBrush(Qt::magenta);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointTop());
        }

        if (itsGame->getItsPlayer()->getIsCollidingLeft()) {
            painter.setBrush(Qt::black);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointLeft());
        } else {
            painter.setBrush(Qt::magenta);
            painter.drawRect(itsGame->getItsPlayer()->getItsCollisionPointLeft());
        }
    */

        // paint traps
        painter.setBrush(QColor(0, 0, 139)); // Dark blue color
        for(const Trap &trap : itsGame->getItsTraps())
        {
            int xIndex = trap.getItsRect().width()/40; //number of traps sprite this trap can contain horizontally
            for(int i = 0; i < xIndex; i++)
            {
                QRect trapRect = QRect(trap.getItsRect().x() + i * 40, trap.getItsRect().y(), 40 ,100);
                painter.drawPixmap(trapRect, trap.getItsSprite());
            }
        }

        // Paint platforms
        for (const Platform &platform : itsGame->getItsPlayer()->getItsPlatforms())
        {
            int xIndex = platform.getItsRect().width()/40; //number of platform sprite this platform can contain horizontally
            int yIndex = platform.getItsRect().height()/40; //number of platform sprite this platform can contain vertically
            for(int i = 0; i < xIndex; i++)
            {
                for(int j = 0; j < yIndex; j++)
                {
                    QRect platformRect = QRect(platform.getItsRect().x() + i * 40, platform.getItsRect().y() + j * 40, 40 ,40);
                    painter.drawPixmap(platformRect, platform.getItsSprite(j == 0));
                }
            }
        }

        // Power ups
        painter.setBrush(QColor(0, 139, 0));
        for(const PowerUp &powerUp : itsGame->getItsPowerUps()){
            switch (powerUp.getItsPowerUpType()) {
            case PowerUpType(SalmonSushi):
                painter.drawPixmap(powerUp.getItsRect(), powerUp.getItsSprite(1));
                break;
            case PowerUpType(Sake):
                painter.drawPixmap(powerUp.getItsRect(), powerUp.getItsSprite(0));
                break;
            case PowerUpType(WoodenSandals):
                painter.drawPixmap(powerUp.getItsRect(), powerUp.getItsSprite(2));
                break;
            default:
                break;
            }
        }

        // paint flag
        if(itsGame->getItsCurrentLevel() == 1)
            painter.drawPixmap(itsGame->getItsFirstFlag().getItsRect(), itsGame->getItsFirstFlag().getItsSprite(0));
        else
            painter.drawPixmap(itsGame->getItsFirstFlag().getItsRect(), itsGame->getItsFirstFlag().getItsSprite(1));

        // Paint enemies
        for (Enemy * enemy : itsGame->getItsPlayer()->getItsEnemies())
        {
            painter.drawPixmap(enemy->getItsRect(), enemy->getItsCurrentFrame()->image);
        }

        // Paint boss
        if(itsGame->getItsCurrentLevel() == 666 && itsGame->getItsBoss()->getItsRect().center().x() > itsGame->getItsPlayer()->getItsRect().x())
            painter.drawPixmap(itsGame->getItsBoss()->getItsRect(), itsGame->getItsBoss()->getItsLeftSprite());
        else
            painter.drawPixmap(itsGame->getItsBoss()->getItsRect(), itsGame->getItsBoss()->getItsSprite());

        // Paint Power Up Timer Bar
        if (itsGame->getItsPlayer()->getItsGoldenBuffCount() > 0) {
            painter.setPen(QColor(255, 215, 0)); // Gold outline
            painter.setBrush(QColor(255, 215, 0));  // Gold fill
            painter.drawRect(10, 10, 450, 30);
            if(itsGame->getItsPlayer()->getItsGoldenBuffCount() > 1){
                itsGoldenBuffCount->setText("x"+QString::number(itsGame->getItsPlayer()->getItsGoldenBuffCount()));
                itsGoldenBuffCount->setFont(QFont("", 20, QFont::Bold)); // Set font size to 20
                itsGoldenBuffCount->setStyleSheet("QLabel { color : white; }");
                itsGoldenBuffCount->adjustSize();
                itsGoldenBuffCount->move(465, 10);
            }
            else
                itsGoldenBuffCount->setText("");
        }
        else
            itsGoldenBuffCount->setText("");

        if (itsGame->getItsPlayer()->getSalmonSushiTimer() > 0) {
            painter.setPen(QColor(255, 182, 193));  // Sakura pink
            painter.setBrush(Qt::NoBrush);  // empty rectangle
            painter.drawRect(10, 10, 450, 30);
            painter.setBrush(QColor(255, 182, 193));  // Sakura pink fill
            painter.drawRect(10, 10, itsGame->getItsPlayer()->getSalmonSushiTimer() * 1.25, 30);
        } else if (itsGame->getItsPlayer()->getSakeTimer() > 0) {
            painter.setPen(QColor(255, 255, 255));  // White
            painter.setBrush(Qt::NoBrush);  // empty rectangle
            painter.drawRect(10, 10, 450, 30);
            painter.setBrush(QColor(255, 255, 255));  // White fill
            painter.drawRect(10, 10, itsGame->getItsPlayer()->getSakeTimer() * 1.25, 30);
        } else if (itsGame->getItsPlayer()->getWoodenSandalsTimer() > 0) {
            painter.setPen(QColor(210, 180, 140));  // Light brown
            painter.setBrush(Qt::NoBrush);  // empty rectangle
            painter.drawRect(10, 10, 450, 30);
            painter.setBrush(QColor(210, 180, 140));  // Light brown fill
            painter.drawRect(10, 10, itsGame->getItsPlayer()->getWoodenSandalsTimer() * 1.25, 30);
        }

        // paint armor iframe bar
        if (itsGame->getItsPlayer()->getItsArmorDuration() > 0) {
            painter.setPen(QColor(255, 255, 255));  // White
            painter.setBrush(Qt::NoBrush);
            int barWidthFull = 45;
            int barHeight = 3;
            int posX = itsGame->getItsPlayer()->getItsRect().x() + 65;
            int posY = itsGame->getItsPlayer()->getItsRect().y() - 10;
            painter.drawRect(posX, posY, barWidthFull, barHeight);
            double armorRatio = static_cast<double>(itsGame->getItsPlayer()->getItsArmorDuration()) / ARMOR_DURATION;
            int barWidth = static_cast<int>(armorRatio * barWidthFull);
            painter.setBrush(QColor(255, 255, 255));  // White fill
            painter.drawRect(posX, posY, barWidth, barHeight);
        }

        if (itsGame->getItsPlayer()->getItsArmorCount() > 0) {
            painter.drawPixmap(1025, 15, 50, 50, itsGame->getItsFirstFlag().getItsSprite(1));
            itsArmorCount->setText(QString::number(itsGame->getItsPlayer()->getItsArmorCount()) + "x");
            QFont font = itsArmorCount->font();
            font.setPointSize(30); // Large font size
            font.setBold(true);    // Bold text
            itsArmorCount->setFont(font);
            itsArmorCount->setStyleSheet("QLabel { color : white; }");  // Set text color to white
            itsArmorCount->adjustSize();  // Adjust the size of the label to fit the text
            itsArmorCount->move(1000 - itsArmorCount->width()+10, -15 + (110 - itsArmorCount->height()) / 2);
            itsArmorCount->show();
        }
        else{
            itsArmorCount->setText(QString::fromStdString(""));
        }

        // Display boss HP
        if (itsGame->getItsBoss()->getItsHealthPoint() > 0 && itsGame->getItsCurrentLevel() == 666) {
            painter.setPen(QColor(255, 255, 255));  // White outline
            painter.setBrush(Qt::NoBrush);
            int barWidthFull = 45*3;
            int barHeight = 3*3;

            // Get the boss's rectangle
            QRect bossRect = itsGame->getItsBoss()->getItsRect();
            int posX = bossRect.x() + (bossRect.width() - barWidthFull) / 2 + 5;  // Center the bar horizontally on the boss
            int posY = bossRect.y() - 10;  // Position the bar above the boss

            painter.drawRect(posX, posY, barWidthFull, barHeight);

            // Calculate the health ratio
            double healthRatio = static_cast<double>(itsGame->getItsBoss()->getItsHealthPoint()) / 3;
            int barWidth = static_cast<int>(healthRatio * barWidthFull);

            painter.setBrush(QColor(255, 0, 0));  // Red fill
            painter.drawRect(posX, posY, barWidth, barHeight);
        }

        // Get Player position
        Player * p = itsGame->getItsPlayer();
        //player is facing right
        if(p->getIsFacingRight() && !p->getIsAttacking())
        {
            //death
            if((p->getIsCollidingEnemy() || p->getIsCollidingTrap() || p->getIsCollidingBoss()) && p->getIsCollidingBottom()){
                p->setItsCurrentFrame(8);
            }
            //falling
            else if(p->getItsVerticalVelocity() > 0)
                p->setItsCurrentFrame(6);
            //jumping
            else if (p->getItsVerticalVelocity() < 0)
                p->setItsCurrentFrame(4);
            else
            {
                //moving
                if(p->getIsMovingRight() && !p->getIsCollidingRight())
                    p->setItsCurrentFrame(2);
                //idle
                else
                    p->setItsCurrentFrame(0);
            }
        }
        //player is facing left
        if(p->getIsFacingLeft() && !p->getIsAttacking())
        {
            //death
            if((p->getIsCollidingEnemy() || p->getIsCollidingTrap() || p->getIsCollidingBoss()) && p->getIsCollidingBottom())
                p->setItsCurrentFrame(9);
            //falling
            else if(p->getItsVerticalVelocity() > 0)
                p->setItsCurrentFrame(7);
            //jumping
            else if (p->getItsVerticalVelocity() < 0)
                p->setItsCurrentFrame(5);
            else
            {
                //moving
                if(p->getIsMovingLeft() && !p->getIsCollidingLeft())
                    p->setItsCurrentFrame(3);
                //idle
                else
                    p->setItsCurrentFrame(1);
            }
        }

        painter.drawPixmap(p->getItsRect(), p->getItsCurrentFrame()->image);
        if(p->getItsSecondaryAnimationIndex() != -1)
            painter.drawPixmap(p->getItsRect(), p->getItsSecondaryFrame()->image);

        // Display indication label message
        itsIndicationLabel->move(itsGame->getItsPlayer()->getItsRect().x() + 15, itsGame->getItsPlayer()->getItsRect().y() - 15);

        if (itsGame->getItsDisplayDuration() > 0) {
            itsIndicationLabel->setText(QString::fromStdString(itsGame->getItsDisplayMessage()));
            itsIndicationLabel->setStyleSheet("QLabel { color : white; font-weight: bold; font-size: 14px; }");
        }
        else if(itsCurrentInterface != GAME){
            itsIndicationLabel->setText("");
        }
        else{
            itsIndicationLabel->setText("");
        }

        // paint Player
        painter.drawPixmap(p->getItsRect(), p->getItsCurrentFrame()->image);
        if(p->getItsSecondaryAnimationIndex() != -1)
            painter.drawPixmap(p->getItsRect(), p->getItsSecondaryFrame()->image);
    }
    if(itsCurrentInterface != GAME)
        itsGoldenBuffCount->setText("");
}

void GameWindow::backgroundAndMusicError(const exception &e)
{
    itsGame->getItsTimer()->stop();
    QString messageError = e.what();
    messageError.push_back("\nPlease check the background or the music file of one of the levels. \nFix the missing file and run the game again");
    itsGame->getItsPopupError()->setText(messageError);
    itsGame->getItsPopupError()->show();

    connect(itsGame->getItsPopupError(), SIGNAL(accepted()), this, SLOT(closeGame())); //If the button "ok" is pressed
    connect(itsGame->getItsPopupError(), SIGNAL(rejected()), this, SLOT(closeGame())); // If the window's cross is pressed
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if(itsCurrentInterface == GAME && !itsGame->getItsPlayer()->getIsCollidingBoss()
        && !itsGame->getItsPlayer()->getIsCollidingEnemy() && !itsGame->getItsPlayer()->getIsCollidingTrap())
    {
        if (!event->isAutoRepeat()) // Ignore auto-repeat events to avoid handling the same press multiple times
        {
            Player * p = itsGame->getItsPlayer();
            switch (event->key())
            {
            case Qt::Key_Q:
                p->setIsPressingQ(true);
                if(!p->getIsPressingD())
                {
                    p->setIsFacingLeft(true);
                    p->setIsFacingRight(false);
                    p->setIsMovingLeft(true);
                }
                break;
            case Qt::Key_D:
                p->setIsPressingD(true);
                if(!p->getIsPressingQ())
                {
                    p->setIsFacingRight(true);
                    p->setIsFacingLeft(false);
                    p->setIsMovingRight(true);
                }
                break;
            case Qt::Key_Z:
                if(!p->getIsCollidingEnemy() && !p->getIsCollidingTrap() && !p->getIsCollidingBoss())
                    p->setIsJumping(true);
                break;
            case Qt::Key_Escape:
                displayMenu(PAUSED);
                break;
            case Qt::Key_U:
                itsGame->getItsBoss()->setItsHealthPoint(0);
            }
        }
    }
}

void GameWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(itsCurrentInterface == GAME)
    {
        if (!event->isAutoRepeat())
        {
            Player * p = itsGame->getItsPlayer();
            switch (event->key())
            {
            case Qt::Key_Q:
                p->setIsPressingQ(false);
                p->setIsMovingLeft(false);
                break;
            case Qt::Key_D:
                p->setIsPressingD(false);
                p->setIsMovingRight(false);
                break;
            case Qt::Key_Z:
                p->setIsJumping(false);
                break;
            }
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if(itsCurrentInterface == GAME)
    {
        Player * p = itsGame->getItsPlayer();
        if(!p->getIsCollidingEnemy() && !p->getIsCollidingTrap() && !p->getIsCollidingBoss() && itsGame->getItsCurrentLevel()!=1)
        {
            p->setIsAttacking(true);
            if(p->getIsFacingRight())
            {
                p->setItsCurrentFrame(10);
                p->setIsAttackingRight(true);
            }
            else
            {
                p->setIsAttackingLeft(true);
                p->setItsCurrentFrame(11);
            }
        }
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(itsCurrentInterface == GAME)
    {
        itsGame->getItsPlayer()->setIsAttackingLeft(false);
        itsGame->getItsPlayer()->setIsAttackingRight(false);
    }
}

void GameWindow::musicAndBackgroundLoader(const int currentLevel)
{
    bool isMusicPlayingSame = itsMusicPlaying==currentLevel; // Boolean to get if the music currently playing will be the same as the next one

    string aMusicPath, aBackgroundPath;

    // Change the music depending on the level
    switch(currentLevel)
    {
    case -1:
        aMusicPath=MUSIC_MAINMENU;
        aBackgroundPath=BACKGROUND_DEATHSCREEN;
        itsMusicPlaying = 0;
        break;
    case 0:
        aMusicPath=MUSIC_MAINMENU;
        aBackgroundPath=BACKGROUND_MAINMENU;
        itsMusicPlaying = 0;
        break;
    case 1:
        aMusicPath=MUSIC_LEVEL1;
        aBackgroundPath=BACKGROUND_LEVEL1;
        itsMusicPlaying = 1;
        break;
    case 2:
        aMusicPath=MUSIC_LEVEL2;
        aBackgroundPath=BACKGROUND_LEVEL2;
        itsMusicPlaying = 2;
        break;
    case 3:
        aMusicPath=MUSIC_LEVEL3;
        aBackgroundPath=BACKGROUND_LEVEL3;
        itsMusicPlaying = 3;
        break;
    case 666:
        aMusicPath=MUSIC_BOSSFIGHT;
        aBackgroundPath=BACKGROUND_LEVEL4;
        itsMusicPlaying = 666; // CHANGED RECENTLY, DELETE COMMENT IF WORKING
        break;
    }

    if(!isMusicPlayingSame)
    {
        ifstream musicFile, imageFile;

        try
        {
            // Try to open the files
            musicFile.open(aMusicPath);
            imageFile.open(aBackgroundPath);

            if (!musicFile.is_open() || !imageFile.is_open()) // Check if the files exist and are readable
            {
                throw std::runtime_error("A game resource is missing or damaged...");
            }

            musicFile.close();
            imageFile.close();

            QString theMusic, theBackground;

            // Background image
            theBackground.append(aBackgroundPath);
            if (!itsBackground.load(theBackground)) {
                throw std::runtime_error("Failed to load background image");
            }

            theMusic.append(aMusicPath); // Convert "aMusicPath", a string, to a QString

            itsMusicPlayer->setSource(QUrl::fromLocalFile(theMusic)); // Load the music
            itsMusicPlayer->setAudioOutput(itsAudio); // Connect the audio to the music player

            itsAudio->setVolume(0.5); // From 0 (minimum) to 1 (maximum)

            itsMusicPlayer->play();
        }
        catch (const std::exception &e)
        {
            qDebug() << "Run into an issue in musicAndBackgroundLoader: " << e.what();
            backgroundAndMusicError(e);
        }
    }
    else
    {
        ifstream imageFile;

        try
        {
            QString theBackground;

            // Background image
            theBackground.append(aBackgroundPath);
            if (!itsBackground.load(theBackground))
            {
                throw std::runtime_error("Failed to load background image");
            }
        }
        catch (const std::exception &e)
        {
            qDebug() << "Run into an issue in musicAndBackgroundLoader: " << e.what();
            backgroundAndMusicError(e);
        }
    }
}

void GameWindow::updateTimer()
{
    if (itsCurrentInterface == GAME)
    {
        itsGame->setItsElapsedTime(itsGame->getItsElapsedTime()+16); // Increment elapsed time by 16 milliseconds

        int totalSeconds = itsGame->getItsElapsedTime() / 1000;
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;

        // Format the time as MM:SS
        QString timeText = QString::asprintf("%02d:%02d", minutes, seconds);

        // Update the QLabel with the formatted time
        itsTimerLabel->setText(timeText);

        // indication label decrement
        if(itsGame->getItsDisplayDuration() > 0)
            itsGame->setItsDisplayDuration(itsGame->getItsDisplayDuration()-1);
    }
    else
    {
        itsTimerLabel->setText("");
    }
}

void GameWindow::musicStatusChanged(QMediaPlayer::MediaStatus currentStatus)
{
    if(currentStatus==QMediaPlayer::EndOfMedia) // First time the media end will always be QMediaPlayer::EndOfMedia but not if we switch music.
    {
        musicAndBackgroundLoader(itsGame->getItsCurrentLevel());
    }
}

void GameWindow::levelUpdate()
{
    //when is boss fight || changer la condition pour qu'elle ne s'appelle qu'une fois
    if(itsGame->getItsCurrentLevel() == 4)
    {
        itsGame->setItsCurrentLevel(666);
        //keep informations about timer and armors
        int time = itsGame->getItsElapsedTime();
        int armorCount = itsGame->getItsPlayer()->getItsArmorCount();

        //new game
        itsGame = new GameBossFight(this);

        //init game
        itsGame->setGame();

        //set infos about timer and armors
        itsGame->setItsElapsedTime(time);
        itsGame->getItsPlayer()->setItsArmorCount(armorCount);

        if(itsMusicPlaying!=4)
            musicAndBackgroundLoader(666);
    }

    // update the music on new level
    if(itsGame->getItsCurrentLevel()!=666 && itsGame->getItsCurrentLevel()!=-1 && itsGame->getItsCurrentLevel()!=itsMusicPlaying)
        musicAndBackgroundLoader(itsGame->getItsCurrentLevel());
    else if(itsGame->getItsCurrentLevel()==-1 && itsMusicPlaying!=0)
        musicAndBackgroundLoader(-1);


    if(itsGame->getIsBossDefeated())
    {
        displayLeaderBoard();
        itsGame->setIsBossDefeated(false);
        itsGame->getItsBoss()->setItsHealthPoint(1);
    }
}


void GameWindow::displayMenu(interface anInterface)
{
    if(anInterface==MAINMENU)
    {
        itsCurrentInterface = MAINMENU;
        itsGame->setItsCurrentLevel(0);

        musicAndBackgroundLoader(itsGame->getItsCurrentLevel());
        itsBackgroundGif->setFileName("../game_ressources/mainMenuGif.gif");

        setupInterface(itsCurrentInterface);

        connect(itsFirstButton, SIGNAL(pressed()), this, SLOT(playGame()));
        connect(itsSecondButton, SIGNAL(pressed()), this, SLOT(displayLeaderBoard()));
        connect(itsThirdButton, SIGNAL(pressed()), this, SLOT(closeGame()));
    }

    else if(anInterface==DEATHSCREEN)
    {
        itsCurrentInterface = DEATHSCREEN;

        if(itsGame->getItsCurrentLevel() == 666)
        {
            itsGame = new Game(this);
        }

        itsGame->setItsCurrentLevel(-1);

        setupInterface(itsCurrentInterface);

        musicAndBackgroundLoader(-1);

        connect(itsFirstButton, SIGNAL(pressed()), this, SLOT(playAgain()));
        connect(itsSecondButton, SIGNAL(pressed()), this, SLOT(mainMenu()));
    }

    else if(anInterface==GAME)
    {
        itsCurrentInterface=GAME;

        itsMovieStorage->clear();
        itsGame = new Game(this);
        itsGame->setGame();

        // Read the background image and music
        musicAndBackgroundLoader(itsGame->getItsCurrentLevel());

        itsTimer->disconnect();
        // Setup the game timer for updating game logic and game timer
        connect(itsTimer, SIGNAL(timeout()), this, SLOT(update()));
        connect(itsTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));

        // Setup the game timer to update the music if needed
        connect(itsTimer, SIGNAL(timeout()), this, SLOT(levelUpdate()));

        // Setup the game timer to display the death screen when the player dies
        connect(itsTimer, SIGNAL(timeout()), this, SLOT(playerStatusUpdate()));

        itsTimer->start(16); // Approximates 60 FPS

        // Setup the game timer for updating frames animations
        connect(itsAnimationTimer, SIGNAL(timeout()), this, SLOT(animationsManager()));
        itsAnimationTimer->start(50); // Approximates 60 FPS

        itsTimerLabel->setGeometry(QRect(1150, 10, 200, 50)); // Adjust position and size as needed
        QFont font = itsTimerLabel->font();
        font.setPointSize(24);  // Set font size
        font.setBold(true);     // Set font weight to bold
        itsTimerLabel->setFont(font);
        itsTimerLabel->setStyleSheet("QLabel { color : white; }");
    }

    else if(anInterface == LEADERBOARD)
    {
        itsCurrentInterface = LEADERBOARD;
        itsGame->setItsCurrentLevel(-1);

        setupInterface(itsCurrentInterface);

        musicAndBackgroundLoader(0);

        connect(itsFirstButton, SIGNAL(pressed()), this, SLOT(playAgain()));
        connect(itsSecondButton, SIGNAL(pressed()), this, SLOT(mainMenu()));
    }
    else if (anInterface == PAUSED)
    {
        itsCurrentInterface = PAUSED;
        setupInterface(itsCurrentInterface);

        // Stop the timers.
        itsTimer->stop();
        itsGame->pauseGame(true);
        itsAnimationTimer->stop();

        paintEvent(NULL); // Trigger the paintEvent one last time because it cannot be triggered due to itsTimer being stopped

        connect(itsFirstButton, SIGNAL(pressed()), this, SLOT(resumeGame()));
        connect(itsSecondButton, SIGNAL(pressed()), this, SLOT(mainMenu()));
    }
}

void GameWindow::playGame()
{
    itsBackgroundGif->stop();

    setupInterface(NONE);
    displayMenu(GAME);
}

void GameWindow::closeGame()
{
    exit(0);
}

void GameWindow::mainMenu()
{
    itsBackgroundGif->stop();
    itsAnimationTimer->disconnect();

    itsGame->deleteLevel();

    setupInterface(NONE);
    displayMenu(MAINMENU);
}

void GameWindow::displayLeaderBoard()
{
    itsBackgroundGif->start();
    setupInterface(NONE);
    displayMenu(LEADERBOARD);
}

void GameWindow::resumeGame()
{
    itsAnimationTimer->start(); //start back the timer at its original speed
    itsTimer->start();

    setupInterface(NONE);
    itsCurrentInterface=GAME;
    itsGame->pauseGame(false);
}

void GameWindow::playAgain()
{
    itsAnimationTimer->disconnect();

    itsGame->deleteLevel();

    setupInterface(NONE);
    displayMenu(GAME);
}

void GameWindow::playerStatusUpdate()
{
    if(itsGame->getIsPlayerAlive()==false)
    {
        itsGame->setIsPlayerAlive(true);
        itsAnimationTimer->stop();

        QTimer::singleShot(500,this, [this]()
        {
            setupInterface(NONE);
            displayMenu(DEATHSCREEN);
        });
    }
}

void GameWindow::setupInterface(interface anInterface)
{
    QString styleSheetGreyButton = (
        "QPushButton {"
        "    background-color: #2B2B2B; /* Gray background */"
        "    color: white;               /* White text */"
        "    border: 2px solid #F6DAD3;  /* Pink border */"
        "    padding: 15px 30px;         /* Adjust padding for size */"
        "    border-radius: 25px;        /* Rounded corners */"
        "    font-size: 18px;            /* Adjust font size */"
        "    font-weight: bold;          /* Bold text */"
        "    margin: 10px;               /* Margin for spacing */"
        "}"
        "QPushButton:hover {             /* Hover effect */"
        "    background-color: #3E3E3E;  /* Slightly lighter gray on hover */"
        "}"
        "QPushButton:pressed {           /* Pressed effect */"
        "    background-color: #1E1E1E;  /* Darker background when pressed */"
        "}"
        );

    QString styleSheetWhiteButton = (
        "QPushButton {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                      stop: 0 #f8f8f8, stop: 1 #e0e0e0); /* Subtle gradient */"
        "    color: black;"
        "    border: 2px solid #acacac; /* Gray border */"
        "    padding: 15px 30px; /* Adjust padding for size */"
        "    border-radius: 25px; /* Rounded corners */"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    margin: 10px; /* Margin for spacing */"
        "}"

        "QPushButton:hover {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                      stop: 0 #333, stop: 1 #333); /* Lighter on hover */"
        "}"

        "QPushButton:pressed {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                                      stop: 0 #c0c0c0, stop: 1 #a0a0a0); /* Darker when pressed */"
        "    padding-top: 17px; /* Push down on press */"
        "    padding-left: 32px;"
        "}"
        );
    QString deathTextStyle = (
        "QLabel {"
        "    color: white;"                       // White text
        "    font-size: 48px;"                    // Font size
        "    font-weight: bold;"                  // Bold text
        "    text-align: center;"                 // Center text
        "    margin: 20px;"                       // Margin for spacing
        "}"
    );

    QString leaderBoardTextStyle = (
        "QLabel {"
        "    color: white;"                       // Black text
        "    font-size: 50px;"                    // Font size
        "    font-weight: bold;"                  // Bold text
        "    margin: 0px;"                       // Margin for spacing
        "    margin: 20px;"
        "}"
    );

    clearScreen();

    if(anInterface==MAINMENU)
    {
        QSpacerItem * sideSpacer = new QSpacerItem(500,0);
        QSpacerItem * topSpacer = new QSpacerItem(0,240);

        itsFirstButton = new QPushButton("Jouer", this);
        itsSecondButton = new QPushButton("Leaderboard", this);
        itsThirdButton = new QPushButton("Quitter", this);

        itsBackgroundGif->setSpeed(95); // % of the gif speed
        itsBackgroundGif->setScaledSize({WINDOW_WIDTH,WINDOW_HEIGHT});

        itsMovieStorage->setMovie(itsBackgroundGif);
        itsMovieStorage->setGeometry(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

        itsBackgroundGif->start();

        itsFirstButton->setStyleSheet(styleSheetGreyButton);
        itsSecondButton->setStyleSheet(styleSheetGreyButton);
        itsThirdButton->setStyleSheet(styleSheetGreyButton);

        itsGrid->addItem(topSpacer,0,0); // Separate the game logo from the buttons
        itsGrid->addItem(sideSpacer,0,0); // left spacer
        itsGrid->addItem(sideSpacer,0,2); // right spacer

        itsGrid->addWidget(itsFirstButton,1,1);
        itsGrid->addWidget(itsSecondButton,2,1);
        itsGrid->addWidget(itsThirdButton,3,1);
    }
    else if (anInterface==DEATHSCREEN)
    {
        QSpacerItem * sideSpacer = new QSpacerItem(500,0);
        QSpacerItem * topSpacer = new QSpacerItem(0,240);

        itsLabel->setText("Vous êtes morts...");
        itsLabel->setStyleSheet(deathTextStyle);

        itsFirstButton = new QPushButton("Re-jouer", this);
        itsSecondButton = new QPushButton("Menu Principal", this);

        itsFirstButton->setStyleSheet(styleSheetWhiteButton);
        itsSecondButton->setStyleSheet(styleSheetWhiteButton);

        itsGrid->addItem(sideSpacer,0,0);
        itsGrid->addItem(sideSpacer,0,2);
        itsGrid->addItem(topSpacer,0,0); // Separate the death logo from the buttons

        itsGrid->addWidget(itsLabel,1,1);
        itsGrid->addWidget(itsFirstButton,2,1);
        itsGrid->addWidget(itsSecondButton,3,1);

    }
    else if(anInterface == LEADERBOARD)
    {
        QSpacerItem * sideSpacer = new QSpacerItem(500,0);
        QSpacerItem * topSpacer = new QSpacerItem(0,500);

        itsFirstButton = new QPushButton("Menu Principal", this);

        itsLabel->setText("LEADERBOARD");
        itsLabel->setStyleSheet(leaderBoardTextStyle);

        itsGrid->addWidget(itsFirstButton, 2, 1);
        itsGrid->addWidget(itsLabel, 0, 1);

        itsGrid->addItem(topSpacer,1,3);
        itsGrid->addItem(sideSpacer,1,0);
        itsGrid->addItem(sideSpacer,1,2);

        itsFirstButton->setStyleSheet(styleSheetWhiteButton);

        connect(itsFirstButton, SIGNAL(pressed()), this, SLOT(mainMenu()));


        if(itsTimerLabel->text() != "")
        {
            string playerName, score, actualScore = itsTimerLabel->text().toStdString();
            string previousText = "", nextText = "";
            bool scoreRegistered = false;
            int counter = 0;

            ifstream iFile("../App/leaderBoard.txt");
            if (!iFile.is_open())
            {
                throw std::runtime_error("The level file is damaged or missing.");
            }
            else
            {
                while(!iFile.eof() && counter < 10)
                {
                    if(iFile >> playerName >> score) // read the ligne
                    {
                        if(actualScore < score && !scoreRegistered) // if the score is better and un-registered
                        {
                            if(counter < 9)
                                nextText += playerName + " " + score + "\n";
                            scoreRegistered = true; // Score saved
                        }
                        else
                        {
                            if(counter < 9)
                            {
                                if(scoreRegistered) // if saved, text come after
                                    nextText += playerName + " " + score + "\n";
                                else    // if not, comes after
                                    previousText += playerName + " " + score + "\n";
                            }
                        }
                        counter ++;
                    }
                }

            }
            iFile.close();

            if(scoreRegistered || counter < 9)
            {
                //display of the button and lineEdit
                itsLineEdit = new QLineEdit(this);
                itsLineEdit->setFixedWidth(250);
                itsLineEdit->setFixedHeight(50);
                QFont font = QFont();
                font.setPointSize(20);
                itsLineEdit->setFont(font);
                itsLineEdit->setPlaceholderText("Entrer Pseudo");

                QPushButton * button = new QPushButton("Enregistrer score",this);
                button->setStyleSheet(styleSheetWhiteButton);
                button->setFixedWidth(250);

                itsGrid->addWidget(itsLineEdit, 1, 0);
                itsGrid->addWidget(button, 2, 0);

                //register the score of the player with the name in the lineEdit

                connect(button, &QPushButton::clicked, this, [this, previousText, nextText, actualScore]()
                {
                    if(itsLineEdit->text() != "")
                    {
                        string myScore = itsLineEdit->text().toStdString() + " " + actualScore + "\n";
                        ofstream oFile("../App/leaderBoard.txt");
                        if (!oFile.is_open())
                        {
                            throw std::runtime_error("The level file is damaged or missing.");
                        }
                        else
                        {
                            oFile.seekp(0);
                            oFile << previousText << myScore << nextText;
                        }
                        oFile.close();
                    }
                });

            }
        }
    }

    else if(itsCurrentInterface==PAUSED)
    {
        QSpacerItem * sideSpacer = new QSpacerItem(500,0);
        QSpacerItem * topSpacer = new QSpacerItem(0,240);

        itsLabel->setText("Jeu en pause");
        itsLabel->setStyleSheet(deathTextStyle);

        itsFirstButton = new QPushButton("Continue", this);
        itsSecondButton = new QPushButton("Menu Principal", this);

        itsFirstButton->setStyleSheet(styleSheetWhiteButton);
        itsSecondButton->setStyleSheet(styleSheetWhiteButton);

        itsGrid->addItem(sideSpacer,1,0);
        itsGrid->addItem(sideSpacer,2,2);
        itsGrid->addItem(topSpacer,0,0); // Separate the death logo from the buttons

        itsGrid->addWidget(itsFirstButton,1,1);
        itsGrid->addWidget(itsSecondButton,2,1);
        itsGrid->addWidget(itsLabel, 0,1); // Top of the screen, middle.
    }

    else
    {
        try
        {
            while (!itsGrid->isEmpty())
            {
                int rowCount = itsGrid->rowCount();
                int columnCount = itsGrid->columnCount();
                itsFirstButton->disconnect();
                itsSecondButton->disconnect();
                itsThirdButton->disconnect();

                for (int row = rowCount - 1; row >= 0; --row)
                {
                    for (int col = columnCount - 1; col >= 0; --col)
                    {
                        // Find the item
                        QLayoutItem *item = itsGrid->itemAtPosition(row, col);
                        if (item)
                        {
                            itsGrid->removeItem(item);

                            QWidget *widget = item->widget();
                            if (widget)
                            {
                                widget->setParent(nullptr); // DETACH FROM PARENT
                            }
                        }
                        itsGrid->update();
                    }
                }
            }
        }
        catch(exception &e)
        {
            qDebug() << "Error while trying to delete menus: " << e.what();
        }
    }
}

void GameWindow::clearScreen()
{
    update(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
#include "moc_gamewindow.cpp"
