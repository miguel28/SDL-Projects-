/*
 *  PuyoPuyo
 *
 *
 *  Created by mike on 6/30/12.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */
#include "PuyoPuyo.h"

PuyoPuyo::PuyoPuyo()/*The contructor Load All Necessary Graphics to run the game, and setup the main game logic*/
{
    Text = new MK_Text();
    background = new MK_Background("Gfx/background.png", 480, 480);
    backTable = new MK_Background("Gfx/Table.png", 480, 480);
    title = new MK_Background("Gfx/TitleA.png", 480, 480);
    gameover = new MK_Background("Gfx/gameover.png", 480, 480);

    TilesGraphic = new MK_Sprite("Gfx/blocks.png");
    TilesGraphic->SetLayout(32,32,1,4);
    TempSpecterBlocks = new Uint8[TABLE_WIDTH * TABLE_HEIGHT];

    mEasy = new MK_Sprite("Gfx/tEasy.png");
    mEasy->x = 120; mEasy->y = 96;
    mEasy->SetLayout(200,64,1,2);
    mMedium = new MK_Sprite("Gfx/tMedium.png");
    mMedium->x = 120; mMedium->y = 160;
    mMedium->SetLayout(200,64,1,2);
    mHard = new MK_Sprite("Gfx/tHard.png");
    mHard->x = 120; mHard->y = 224;
    mHard->SetLayout(200,64,1,2);
    mExpert = new MK_Sprite("Gfx/tExpert.png");
    mExpert->x = 120; mExpert->y = 288;
    mExpert->SetLayout(200,64,1,2);

    int i,j;
    for(j=0; j<TABLE_HEIGHT; j++)
    {
        for(i=0; i<TABLE_WIDTH; i++)
        {
            Blocks[(j*6)+i] = new Block(TilesGraphic->Graphic);
            Blocks[(j*6)+i]->SetLayout(32,32,1,4);
            Blocks[(j*6)+i]->PosX=i;
            Blocks[(j*6)+i]->PosY=j;
        }
    }

    MovingBlocks[0] = new Block(TilesGraphic->Graphic);
    MovingBlocks[0]-> SetLayout(32,32,1,4);
    MovingBlocks[0]->PosX = 2;
    MovingBlocks[0]->PosY = 0;
    MovingBlocks[0]->Type = 1;

    MovingBlocks[1] = new Block(TilesGraphic->Graphic);
    MovingBlocks[1]-> SetLayout(32,32,1,4);
    MovingBlocks[1]->PosX = 3;
    MovingBlocks[1]->PosY = 0;
    MovingBlocks[1]->Type = 2;

    MovPosition = 0;
    dPosX = 2;
    dPosY = 0;

    srand (time(NULL));
    Score = 0;
    Level = 20;
    Scene = 0;
}

PuyoPuyo::~PuyoPuyo()/* Free Al memoey used by the Graphics and close the game with MK_Application destructor */
{
    delete Text;
    delete background;
    delete backTable;
    delete gameover;

    delete mEasy;
    delete mMedium;
    delete mHard;
    delete mExpert;

    delete TilesGraphic;
    delete Blocks;
    delete MovingBlocks;
    delete TempSpecterBlocks;
}

void PuyoPuyo::ResetGame() /*Reset the game parameters, for a new game*/
{
    GameOverCounter=0;
    MovPosition = 0;
    dPosX = 2;
    dPosY = 0;
    Score = 0;
    ClearTempBlocks();
    int i,j;
    for(j=0; j<TABLE_HEIGHT; j++)
        for(i=0; i<TABLE_WIDTH; i++)
            SetBlock(i,j,0);
}

bool PuyoPuyo::GameLogic() /* When the app run, can be only 3 scene. 1.-Main Menu, 2.-Playing the game, 3.-Gameover  */
{
    if(Scene == 0)Menu();
    if(Scene == 1)Playing();
    if(Scene == 2)GameOver();
    Update(); //Update Inputs and Screen
    return true;
}
void PuyoPuyo::Menu()/*The menu Show the Game Title, controls and dificulty selector*/
{
    background->DrawBackground(Screen);  //Draw The Background
    if(Mouse.x>120 && Mouse.x<320 && Mouse.y>96 && Mouse.y<160) //Check if the mouse are in the sprite to highlight it.
    {
        mEasy->DrawSprite(Screen,1);
        if(Mouse.Newpress.LClick)   // If the user press Left Click Starts the game
        {
            Level = 40;
            Scene = 2;
            ResetGame();
        }
    }
    else mEasy->DrawSprite(Screen,0);

    //For all cases of difficulty
    if(Mouse.x>120 && Mouse.x<320 && Mouse.y>160 && Mouse.y<224)
    {
        mMedium->DrawSprite(Screen,1);
        if(Mouse.Newpress.LClick)
        {
            Level = 30;
            Scene = 1;
            ResetGame();
        }
    }
    else mMedium->DrawSprite(Screen,0);

    if(Mouse.x>120 && Mouse.x<320 && Mouse.y>224 && Mouse.y<288)
    {
        mHard->DrawSprite(Screen,1);
        if(Mouse.Newpress.LClick)
        {
            Level = 20;
            Scene = 1;
            ResetGame();
        }
    }
    else mHard->DrawSprite(Screen,0);

    if(Mouse.x>120 && Mouse.x<320 && Mouse.y>288 && Mouse.y<352)
    {
        mExpert->DrawSprite(Screen,1);
        if(Mouse.Newpress.LClick)
        {
            Level = 10;
            Scene = 1;
            ResetGame();
        }
    }
    else mExpert->DrawSprite(Screen,0);
    title->DrawBackground(Screen); // Draw the Title and controls
}
void PuyoPuyo::Playing()// The main game method
{
    /* Logic Processing*/
    if(Pad.Newpress.Q)Scene=0;
    if(!Destroying)
    {
        Controls();
        Gravity();
        CheckBlockConnections();
    }
    else DestroyingBlocks();

    /* Draw all graphics on the screen */
    background->DrawBackground(Screen);
    backTable->DrawBackground(Screen);
    int i;
    for(i=0; i<(TABLE_WIDTH*TABLE_HEIGHT); i++)
    {
        Blocks[i]->Render(Screen);
    }

    if(!Destroying)
    {
        MovingBlocks[0]->Render(Screen);
        MovingBlocks[1]->Render(Screen);
    }
    DrawScore();
}
void PuyoPuyo::DrawScore() /* Draw the current Score */
{
    Text->SetText("Score :");
    Text->x =300;
    Text->y =70;
    Text->DrawText(Screen);

    ostringstream stream;
    stream << setfill('0') << setw(10) << Score;
    Text->SetText(stream.str());
    Text->x =300;
    Text->y =100;
    Text->DrawText(Screen);
}
void PuyoPuyo::Controls()/* This method is responsible for controlling the blocks position*/
{
    /*
        For the block move I used dPosX and dPosY coordinates variables to positioning the falling blocks
    */

    if(Pad.Newpress.Left) // Keyboard Newpress Left Key Check
    {
        if(MovPosition == 0 || MovPosition == 2)//If Horizontal position then check the corresponding collisions to move arround
            if(!Collition(dPosX-1, dPosY))
                dPosX--;
        if(MovPosition == 1 || MovPosition == 3)//If Vertical position then check the corresponding collisions to move arround
            if(!Collition(dPosX-1, dPosY) && !Collition(dPosX-1, dPosY+1))
                dPosX--;
    }
    if(Pad.Newpress.Right) // Keyboard Newpress Right Key Check
    {
        if(MovPosition == 0 || MovPosition == 2)// The same in another case
            if(!Collition(dPosX+2, dPosY))
                dPosX++;
        if(MovPosition == 1 || MovPosition == 3)
            if(!Collition(dPosX+1, dPosY) && !Collition(dPosX+1, dPosY+1))
                dPosX++;
    }
    if(Pad.Newpress.Space) // Check keyboard newpress Space key
    {
        /*
            The blocks (two) that falling down can be rotated
            Every newpress of the key Space the block rotates 90º(both)
            and to identify this I used the MovPosition Counter
            Thats why I have 4 Diferent Position

            0 = Horizontal 0º
            1 = Vertical 90º
            2 = Horizontal 180º
            3 = Vertical 270º

            and the the MovPosition counter reach 4 I reset it to 0

        */
        if(MovPosition == 0 || MovPosition == 2)//If Horizontal position then check the corresponding collisions to rotate
        {
            if(!Collition(dPosX,dPosY+2))
            MovPosition++;
        }
        else if(MovPosition == 1 || MovPosition == 3)//If vertical position then check the corresponding collisions to rotate
        {
            if(!Collition(dPosX+1,dPosY) && !Collition(dPosX+1,dPosY+1))
            MovPosition++;
        }

        if(MovPosition == 4)MovPosition = 0;
        if(MovPosition == 0 || MovPosition == 2)
           if(Collition(dPosX+2,dPosY))
            dPosX--;
    }

    switch(MovPosition) // for all 4 case I position the blocks acording the dPosX, dPosY...
    {
    case 0:
        MovingBlocks[0]->PosX = dPosX;
        MovingBlocks[0]->PosY = dPosY;
        MovingBlocks[1]->PosX = dPosX+1;
        MovingBlocks[1]->PosY = dPosY;
        break;
    case 1:
        MovingBlocks[0]->PosX = dPosX;
        MovingBlocks[0]->PosY = dPosY;
        MovingBlocks[1]->PosX = dPosX;
        MovingBlocks[1]->PosY = dPosY+1;
        break;
    case 2:
        MovingBlocks[1]->PosX = dPosX;
        MovingBlocks[1]->PosY = dPosY;
        MovingBlocks[0]->PosX = dPosX+1;
        MovingBlocks[0]->PosY = dPosY;
        break;
    case 3:
        MovingBlocks[1]->PosX = dPosX;
        MovingBlocks[1]->PosY = dPosY;
        MovingBlocks[0]->PosX = dPosX;
        MovingBlocks[0]->PosY = dPosY+1;
        break;
    }
    /*
        I used a DownCounter variable to control the falling velocity
        that it depends of the diffitulty that the user therefore selected(Level Variable)
    */

    DownCounter++;
    if(Pad.Held.Down)DownCounter+=10; // If the use held down the Down Key the block falls faster

    /*
        When the counter reaches the max counter(depend Level variable)
        the blocks fall 1 position (dPos++) and check if below them are more blocks
        cording with the position that the blocks are falled.
        After finding a block below the user loses control of those blocks and start dropping a new pair
        With random seletion
    */
    if(DownCounter>=Level)
    {
        DownCounter=0;
        if(MovPosition == 0 || MovPosition == 2)
        {
            if(!Collition(dPosX,dPosY+1) && !Collition(dPosX+1,dPosY+1))dPosY++;
            else
            {
                SetBlock(MovingBlocks[0]->PosX,MovingBlocks[0]->PosY,MovingBlocks[0]->Type);
                SetBlock(MovingBlocks[1]->PosX,MovingBlocks[1]->PosY,MovingBlocks[1]->Type);
                dPosX = 2;
                dPosY = 0;
                MovingBlocks[0]->Type=GetRandom();
                MovingBlocks[1]->Type=GetRandom();
                if(Collition(2,0)||Collition(3,0))
                    Scene = 2;
            }
        }
        if(MovPosition == 1 || MovPosition == 3)
        {
            if(!Collition(dPosX,dPosY+2))dPosY++;
            else
            {
                SetBlock(MovingBlocks[0]->PosX,MovingBlocks[0]->PosY,MovingBlocks[0]->Type);
                SetBlock(MovingBlocks[1]->PosX,MovingBlocks[1]->PosY,MovingBlocks[1]->Type);
                dPosX = 2;
                dPosY = 0;
                MovingBlocks[0]->Type=GetRandom();
                MovingBlocks[1]->Type=GetRandom();
                if(Collition(2,0)||Collition(2,1))
                    Scene = 2;
            }
        }
    }
}

bool PuyoPuyo::Collition(Sint8 x, Sint8 y)/* Check if exits a block in detemined position*/
{
    if(x<0 || x>5 || y<0 || y>11)return true;
    else if(Blocks[(y*6)+x]->Type>0)return true;
    else return false;
}

void PuyoPuyo::SetBlock(Uint8 x, Uint8 y, Uint8 t)/* Set block in determined position*/
{
    if(x<0 || x>5 || y<0 || y>11)
        return;
    Blocks[(y*6)+x]->Type=t;
}

Uint8 PuyoPuyo::GetBlock(Uint8 x, Uint8 y)/* Get the type block in determined position*/
{
    if(x<0 || x>5 || y<0 || y>11)
        return 8;
    return Blocks[(y*6)+x]->Type;
}

/*
    It is a gravity funtion, if any block does not have any lock below them, it can be fall 1 position

    This method is called every frame
*/

void PuyoPuyo::Gravity()
{
    Sint8 i,j;
    for(j=TABLE_HEIGHT-2; j>=0; j--)
    {
        for(i=0; i<TABLE_WIDTH; i++)
        {
            if(GetBlock(i, j)>0)
            {
                if(GetBlock(i, j+1)==0)
                {
                    SetBlock(i, j+1, GetBlock(i, j));
                    SetBlock(i, j, 0);
                }
            }
        }
    }
}

/*
    Here the difficult of all game programming.
    Basically I check every frame, every block connections,
    where I used the Methods Overload logic (CheckBlockBounds(Sint8 x, Sint8 y))
    to check if exits a 4 or more block connections of the same type.
    This method is called self until it end if is no longer blocks of the same
    type. Then this method stores the position of the blocks that it will be
    delete of the gameboard in (SetTempBlock(x,y))

*/

void PuyoPuyo::CheckBlockConnections()
{
    Sint8 i,j;
    bool Exit = false;
    for(j=TABLE_HEIGHT-1; j>=0; j--)
    {
        for(i=0; i<TABLE_WIDTH; i++)
        {
            ClearTempBlocks();
            if(GetBlock(i, j)>0)
            {
                TempTypeBlock=GetBlock(i, j);
                CounterBlocks=0;
                CheckBlockBounds(i,j);
                if(CounterBlocks>=4)
                {
                    Destroying = true;
                    AnimCounter=0;
                    Exit=true;
                }
            }
            if(Exit)break;
        }
        if(Exit)break;
    }
}
void PuyoPuyo::CheckBlockBounds(Sint8 x, Sint8 y)
{
    if(x<0 || x>5 || y<0 || y>11)
        return;
    if(GetTempBlock(x,y)==1)
        return;

    if(GetBlock(x, y)==TempTypeBlock)
    {
        CounterBlocks++;
        SetTempBlock(x,y);
        CheckBlockBounds(x-1,y);
        CheckBlockBounds(x+1,y);
        CheckBlockBounds(x,y-1);
        CheckBlockBounds(x,y+1);
        return;
    }
    else return;
}

void PuyoPuyo::SetTempBlock(Uint8 x, Uint8 y)
{
    TempSpecterBlocks[(y*6)+x]=1;
}

Uint8 PuyoPuyo::GetTempBlock(Uint8 x, Uint8 y)
{
    return TempSpecterBlocks[(y*6)+x];
}

void PuyoPuyo::ClearTempBlocks()
{
    int i;
    for(i=0; i<(TABLE_WIDTH * TABLE_HEIGHT); i++)
        TempSpecterBlocks[i]=0;
}

void PuyoPuyo::DestroyBlockConnections()
{
    Sint8 i,j;

    for(j=TABLE_HEIGHT-1; j>=0; j--)
    {
        for(i=0; i<TABLE_WIDTH; i++)
        {
            if(GetTempBlock(i, j)==1)
            {
                SetBlock(i, j, 0);
                Blocks[(j*6)+i]->StopAnimation();
                Score+=100;
            }
        }
    }
}

void PuyoPuyo::DestroyingBlocks()
{
    AnimCounter++;
    if(AnimCounter>=60)
    {
        Destroying = false;
        DestroyBlockConnections();
    }
    else
    {
        int i,j;
        for(j=TABLE_HEIGHT-1; j>=0; j--)
        {
            for(i=0; i<TABLE_WIDTH; i++)
            {
                if(GetTempBlock(i, j)==1)
                {
                    Blocks[(j*6)+i]->SetAnimation(AnimCounter*10, (float)1/(float)((AnimCounter/30)+1));
                }
            }
        }
    }
}

Uint8 PuyoPuyo::GetRandom()
{
    Uint8 a=(Uint8)(rand() % 15);
    Uint8 b = (a/4)+1;
    return b;
}

void PuyoPuyo::GameOver()
{
    GameOverCounter++;
    background->DrawBackground(Screen);
    gameover->DrawBackground(Screen);
    if(GameOverCounter==250)Scene=0;
}
