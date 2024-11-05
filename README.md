# How to Play the Game (user guide)

## Controls
- **Z** - Jump
- **Q** - Move left
- **D** - Move right
- **Left mouse click** - Attack (unlocked at level 2)

## Overview

In *Soul's Guide*, you play as Toyo, an experienced samurai. The objective of the game is to reach the end of all three levels consecutively without getting killed by the boss, enemies, or traps scattered throughout each level. The end of each level is marked by a key item.

After completing the levels, you will face the boss in the final arena. Here, you must dodge the enemies' incessant charges while collecting power-ups in the form of golden enemies scattered throughout the arena. Gathering all three and then attacking the boss three times will grant you victory.

## Gameplay Details
### Game walkthrough
When you open the game you will have access to the main menu and will see three buttons:
   - Jouer: play
You can now play the game and *try* to reach its end, however if you die your screen will change and a new death screen will appear, you can now choose to test your skill and play again, or go to the main menu and see what the other buttons does:
   - Leaderboard : leaderBoard
On this screen with the same style as the main menu, you can see the leaderboard and who's the best player that ever played on your game! It has values has default but they are high in time, you can for sure beat the developpers's time.
   - Quitter : exit
Exit the game and closes it. 

### Level Progression
- **Level 1**: At the end of this level, you will gain your trusty weapon, the Katana. It allows you to attack and kill enemies with the Left Mouse Click. Killing an enemy mid-air refunds your jump, effectively allowing you to double jump. This mechanic is essential for levels 2 and 3, and your ability to pull it off consistently is key to winning the game.
  
- **Level 2 & 3**: At the end of these levels, you will receive an armor point. This armor point allows you to survive hits from otherwise fatal obstacles, whether it's from the boss, traps, or enemies. You can have multiple armor points at a time.

### Final Arena
In the final arena, you must:
1. Dodge the boss' incessant charge (It will follow you no matter where you hide)
2. Collect power-ups in the form of golden enemies.
3. Gather all three power-ups.
4. Attack the boss three times to achieve victory.

Good luck, Samurai!

# How to Install

## Using Source Code and Qt Creator

1. Clone the project in a directory of your choosing.
2. Open Qt Creator.
3. Click on "Open Project".
4. Select `retrog24_c2_soulsguide/SoulsGuide/App/App.pro`.
5. Swap the Compilation type to "Release" on the bottom left context menu marked with a monitor icon.
6. Compile the project by clicking on the hammer icon at the bottom right.
7. Click the green play button at the bottom right.
8. You can now close the game then follow this step by step on how to use windeployqt :

1. Move (if wanted to) the release folder located in your game's build to the deskstop (exemple of the build folder's name: `build-App-Desktop_Qt_6_7_1_MinGW_64_bit-Release`)
2. Search in your operating system browser the QT Cmd of your Qt's version by searching `Qt 6.7.1` (where 6.7.1 is an example version, choose the one you possess and usually run with)
3. Copy the path to the release folder and paste it into the Qt CMD: `cd "C:\Users\User\Deskstop\SoulsGuide\release"` (Usually will look like that if moved to the deskstop but can vary)
4. Use this command: `windeployqt.exe App.exe`
5. **Game ressources**
   Then in that same directory create "App" and "game_ressources" folders.
   Copy the contents of the git's main branch SoulsGuide/game_ressources into the game_ressources file you previously created.
   Copy the following files from SoulsGuide/App into the App folder you previously created :
      level_1.csv
      level_2.csv
      level_3.csv
      level_4.csv
      leaderBoard.txt
The game is now ready to launch, just go into the release folder and execute the App.exe file.

## Dowload from Google Drive (windows)
Alternatively, you can download a fully functional release of the game from this google drive link :
https://drive.google.com/file/d/1OKe6zPM6LwoTxVQdKxxnqQ70w7u31nC6/view?usp=sharing

After downloading, extract the file contents and open the release folder, there will be located the game : App.exe