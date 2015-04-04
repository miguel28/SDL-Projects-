/*
 *  PuyoPuyo
 *
 *
 *  Created by mike on 6/30/12.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifndef PUYOPUYO_H
#define PUYOPUYO_H
#include <MK_Application.h>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <iomanip>

#include "Block.h"
#define TABLE_WIDTH 6
#define TABLE_HEIGHT 12

/*
    The game uses a sprites grid logic
    the default board game size is 6x12 defined #define TABLE_WIDTH 6, #define TABLE_HEIGHT 12

    In the contructor create an unidimentional array of blocks (72 in total).

    Each block has an integer identifier from 0 to 4
    0 = Empty Block
    1-4 = four diferen type of blocks.

    With this logic I can process the state of all block and check connections
    of the same type of block in all game board.
*/

class PuyoPuyo : public MK_Application /* PuyoPuyo App inherits the MK_Application class */
{
    public:
        MK_Text* Text;
        PuyoPuyo();
        bool GameLogic();
        void ResetGame();
        void Menu();
        void Playing();
        void Controls();
        void DrawScore();
        bool Collition(Sint8 x, Sint8 y);
        void SetBlock(Uint8 x, Uint8 y, Uint8 t);
        Uint8 GetBlock(Uint8 x, Uint8 y);
        void Gravity();
        void CheckBlockConnections();
        void CheckBlockBounds(Sint8 x, Sint8 y);
        void SetTempBlock(Uint8 x, Uint8 y);
        Uint8 GetTempBlock(Uint8 x, Uint8 y);
        void ClearTempBlocks();
        void DestroyBlockConnections();
        void DestroyingBlocks();
        Uint8 GetRandom();
        void GameOver();
        virtual ~PuyoPuyo();
    protected:
    private:
        MK_Background* background;
        MK_Background* backTable;
        MK_Background* title;
        MK_Background* gameover;
        MK_Sprite* TilesGraphic;
        MK_Sprite *mEasy,*mMedium,*mHard,*mExpert;
        Block* Blocks[(TABLE_WIDTH*TABLE_HEIGHT)];
        Block* MovingBlocks[2];
        Uint8 MovPosition;
        Uint8 dPosX,dPosY;
        Uint8 DownCounter;

        Uint8 CounterBlocks;
        Uint8 TempTypeBlock;
        Uint8 *TempSpecterBlocks;

        bool Destroying;
        Uint16 AnimCounter;
        Uint32 Score;
        Uint8 Level;
        Uint8 Scene;
        Uint16 GameOverCounter;
};

#endif // PUYOPUYO_H
