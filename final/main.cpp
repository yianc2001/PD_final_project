#include "graphics.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <windows.h>
using namespace std;

struct Box
{
    int left;
    int top;
    int right;
    int bottom;
    int id;
    int center_x;
    int center_y;
};

struct Mouse
{
    int x;
    int y;
};

int main()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
    //board design
    int screensize_x = 800;
    int screensize_y = 800;
    initwindow(screenWidth,screenHeight,"Spatial Span", -10, -10, false, true);
    
    setcolor(YELLOW);
    rectangle(0,0,screensize_x,screensize_y);
    
    rectangle(10,10,screensize_x-10,screensize_y-10);
    setfillstyle(SOLID_FILL,YELLOW);
    floodfill(5,5,YELLOW);
    
    int squareCnt = 6;
    int squareLength_x = 0;
    int squareLength_y = 0;
    squareLength_x = (screensize_x-20)/squareCnt;
    squareLength_y = (screensize_y-20)/squareCnt;
    
    for(int i = 10; i <= (790-squareLength_x); i+=squareLength_x)
    {
        for(int j = 10; j <= (790-squareLength_y); j+=squareLength_y)
        {
            setcolor(GREEN);
            rectangle(i,j,i+squareLength_x,j+squareLength_y);
        }
    }
    
    for(int i = 11; i <= (790-squareLength_x+1); i+=squareLength_x)
    {
        for(int j = 11; j <= (790-squareLength_y+1); j+=squareLength_y)
        {
            setfillstyle(SOLID_FILL,DARKGRAY);
            floodfill(i,j,GREEN);
        }
    }
    
    
    //Box
    Box createBox[squareCnt*squareCnt] = {0};
    int num = 0;
    for(int i = 10; i <= (790-squareLength_x); i+=squareLength_x)
    {
        for(int j = 10; j <= (790-squareLength_y); j+= squareLength_y)
        {
            createBox[num].id = num;
            createBox[num].left = i;
            createBox[num].right = (i + squareLength_x);
            createBox[num].top = j;
            createBox[num].bottom = (j+squareLength_y);
            createBox[num].center_x = (createBox[num].left + createBox[num].right)/2;
            createBox[num].center_y = (createBox[num].top + createBox[num].bottom)/2;
            num++;
        }
    }
    
    // set random
    int rn = 0;
    int testCnt = 6;
    srand(time(NULL));
    
    int* testSquare = new int[testCnt];
    for(int i = 0; i < testCnt; i++)
    {
        testSquare[i] = squareCnt*squareCnt;
    }
     
    bool different = false;
    for(int i = 0; i < testCnt; i++)
    {
        rn = rand()%(squareCnt*squareCnt);
        different = false;
        while(1)
        {
            different = false;
            for(int j = 0; j < (squareCnt*squareCnt); j++)
            {
                if(rn == testSquare[j])
                {
                    different = true;
                    break;
                }
            }
            
            if(different == true)
            {
                rn = rand()%(squareCnt*squareCnt);
            }
            else
            {
                testSquare[i] = rn;
                break;
            }
        }
    }
    for(int i = 0; i < testCnt; i++)
    {
        cout << testSquare[i] << endl;
    }
    
    //flash light
    delay(2000);
    int whichSquare = 0;
    for(int i = 0; i < testCnt; i++)
    {
        whichSquare = testSquare[i];
        setfillstyle(SOLID_FILL,CYAN);
        floodfill(createBox[whichSquare].center_x,createBox[whichSquare].center_y,GREEN);
        delay(2000);
        setfillstyle(SOLID_FILL,DARKGRAY);
        floodfill(createBox[whichSquare].center_x,createBox[whichSquare].center_y,GREEN);
    }
    
    //mouse click and button
    POINT mousePosition;
    Mouse* userClick = new Mouse[testCnt];
    
    for(int i = 0; i < testCnt; i++)
    {
        userClick[i].x = 0;
        userClick[i].y = 0;
    }
    int mX = 0;
    int mY = 0;
    int n = 0;
    int t = 0;
    
    while(1)
    {
        if(t == 0)
        {
            GetAsyncKeyState(VK_SHIFT);
            t++;
        }
        while(1)
        {
            if(GetAsyncKeyState(VK_LBUTTON))
            {
                if(n == 0)
                {
                    n++;
                }
                else
                {
                    GetCursorPos(&mousePosition);
                    mX = mousePosition.x;
                    mY = mousePosition.y;
                 
                    if((mX <= (screensize_x-10)) && (mY <= (screensize_y-10)))
                    {
                        setfillstyle(SOLID_FILL,WHITE);
                        floodfill(mX,mY,GREEN);
                        delay(500);
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        floodfill(mX,mY,GREEN);
                        userClick[n-1].x = mX;
                        userClick[n-1].y = mY;
                        cout << mX << " " << mY << " " << endl;
                        n++;
                    }
                }
            }
            if(n == (testCnt+1))
            {
                break;
            }
        }
        if(n == (testCnt+1))
        {
            break;
        }
        delay(50);
    }
    
    //test result input
    int* userChoice = new int[testCnt];
    for(int i = 0; i < testCnt; i++)
    {
        userChoice[i] = 0;
    }
    
    for(int i = 0; i < testCnt; i++)
    {
        userChoice[i] = ((userClick[i].x - 10)/130)*6 + ((userClick[i].y - 10)/130);
    }
    
    for(int i = 0; i < testCnt; i++)
    {
        cout << userChoice[i] << endl;
    }
    
    //show test result
    int score = 0;
    for(int i = 0; i < testCnt; i++)
    {
        if(userChoice[i] == testSquare[i])
        {
            score += 10;
        }
        
    }
    cout << score;
    char sent[50] = {0};
    sprintf(sent,"Your Score is %d", score);
    setcolor(YELLOW);
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    outtextxy(1000,500,sent);
    delay(10000);
        
    getch();
    delete userChoice;
    delete testSquare;
    delete userClick;
    closegraph();
    
}
