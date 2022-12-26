//ASCII码值'@'(64)代表一个元素
#include<stdio.h>
#include<windows.h>
#include<conio.h>

const int FRAME_WIDE = 15;
const int FRAME_HEIGH = 20;

int gameMark = 0;
int centerLocation = 0;
bool movingSquares = false;//表示有没有正在移动的结构体
int squaresType = 0;
bool gameFlag = 1;
int sleeptime = 300;

struct gamePanelElem
{
    char data;
    bool moveFlag;
};

void gotoxy(int x, int y);
void printFrame(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creakSquares(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void moveEleme(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void initGamePanel(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void checkErasableLayer(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType0(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType1(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType2(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType3(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType4(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void creatType5(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE]);
void moveElemeToLeft(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate);
void moveDown(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate);
void moveElemeToRight(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate);
void rotate(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate);
void checkIsFailed(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],bool* gameFlag);
void eraseRow(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int i);
bool canRoate(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate);



int main()
{
    gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE];
    initGamePanel(gamePanel);
    while(gameFlag)
    {
        if(!movingSquares)
        {
            creakSquares(gamePanel);
        }
        printFrame(gamePanel);
        moveEleme(gamePanel);
        Sleep(sleeptime);
    }
    printf("游戏已结束.\n");
    system("pause");
    return 0;
}



void initGamePanel(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])
{
    for(int i = 0;i < FRAME_HEIGH;i++)  //防止空值错误
    {
        for(int j = 0;j < FRAME_WIDE;j++)
        {
            gamePanel[i][j].data = ' ';
            gamePanel[i][j].moveFlag = false;
        }
    }

    for(int i = 1;i < FRAME_WIDE-1;i++)
    {
        gamePanel[0][i].data = '-';
        gamePanel[FRAME_HEIGH-1][i].data = '-';
    }
    for(int i = 1;i < FRAME_HEIGH-1;i++)
    {
        gamePanel[i][0].data = '|';
        gamePanel[i][FRAME_WIDE-1].data = '|';
    }
    gamePanel[0][0].data = '*';
    gamePanel[0][FRAME_WIDE-1].data = '*';
    gamePanel[FRAME_HEIGH-1][0].data = '*';
    gamePanel[FRAME_HEIGH-1][FRAME_WIDE-1].data = '*';
}

//控制台控制光标坐标
void gotoxy(int x, int y)
{
    COORD coord = {(short)x, (short)y};   
    /*COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。其定义为：

    typedef struct _COORD {

    SHORT X; // horizontal coordinate

    SHORT Y; // vertical coordinate
    } COORD;*/

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void printFrame(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])
{
    gotoxy(0,0);
    printf("******************************************\n");
    printf("*s键加快方块移动速度，a键方块左移        *\n");
    printf("*d键方块右移，w键顺时针旋转,p键暂停游戏  *\n");
    printf("******************************************\n");
    printf("*请先将键盘调成小写模式，否则可能会无法响*\n");
    printf("*应相关按键(同时也不要按太快，毕竟只是俄 *\n");
    printf("*罗斯方块.......)                        *\n");
    printf("******************************************\n");
    printf("当前分数：%d\n",gameMark);
    for(int i = 0;i < FRAME_HEIGH;i++)
    {
        for(int j = 0;j < FRAME_WIDE;j++)
        {
            printf("%c",gamePanel[i][j].data);
        }
        printf("\n");
    }
}

void creakSquares(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //在gamePanel上创建新的方块
{
    int type = rand()%6;
    switch (type)
    {
        case 0:creatType0(gamePanel);break;
        case 1:creatType1(gamePanel);break;
        case 2:creatType2(gamePanel);break;
        case 3:creatType3(gamePanel);break;
        case 4:creatType4(gamePanel);break;
        case 5:creatType5(gamePanel);break;
    }
}

void creatType0(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个横条（345），接下来的不方便展示，用九宫格来代替，左上角元素为第0个
{
    int Loc = rand()%(FRAME_WIDE-4)+2;
    gamePanel[1][Loc].data = '@';
    gamePanel[1][Loc-1].data = '@';
    gamePanel[1][Loc+1].data = '@';
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[1][Loc-1].moveFlag = true;
    gamePanel[1][Loc+1].moveFlag = true;
    centerLocation = Loc;
    movingSquares = true;
    squaresType = 0;
}
void creatType1(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个0145
{
    int Loc = rand()%(FRAME_WIDE-4)+2;
    gamePanel[1][Loc-1].data = '@';
    gamePanel[1][Loc].data = '@';
    gamePanel[2][Loc].data = '@';
    gamePanel[2][Loc+1].data = '@';
    gamePanel[1][Loc-1].moveFlag = true;
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[2][Loc].moveFlag = true;
    gamePanel[2][Loc+1].moveFlag = true;
    centerLocation = Loc+FRAME_WIDE;
    movingSquares = true;
    squaresType = 1;
}
void creatType2(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个1478
{
    int Loc = rand()%(FRAME_WIDE-2)+1;
    gamePanel[1][Loc].data = '@';
    gamePanel[2][Loc].data = '@';
    gamePanel[3][Loc].data = '@';
    gamePanel[3][Loc+1].data = '@';
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[2][Loc].moveFlag = true;
    gamePanel[3][Loc].moveFlag = true;
    gamePanel[3][Loc+1].moveFlag = true;
    centerLocation = Loc+FRAME_WIDE;
    movingSquares = true;
    squaresType = 2;
}
void creatType3(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个4678
{
    int Loc = rand()%(FRAME_WIDE-4)+2;
    gamePanel[1][Loc].data = '@';
    gamePanel[2][Loc].data = '@';
    gamePanel[2][Loc-1].data = '@';
    gamePanel[2][Loc+1].data = '@';
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[2][Loc].moveFlag = true;
    gamePanel[2][Loc-1].moveFlag = true;
    gamePanel[2][Loc+1].moveFlag = true;
    centerLocation = Loc+FRAME_WIDE;
    movingSquares = true;
    squaresType = 3;
}
void creatType4(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个4578
{
    int Loc = rand()%(FRAME_WIDE-3)+1;
    gamePanel[1][Loc].data = '@';
    gamePanel[1][Loc+1].data = '@';
    gamePanel[2][Loc].data = '@';
    gamePanel[2][Loc+1].data = '@';
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[1][Loc+1].moveFlag = true;
    gamePanel[2][Loc].moveFlag = true;
    gamePanel[2][Loc+1].moveFlag = true;
    centerLocation = Loc;
    movingSquares = true;
    squaresType = 4;
}
void creatType5(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])  //创建一个01478
{
    int Loc = rand()%(FRAME_WIDE-4)+2;
    gamePanel[1][Loc-1].data = '@';
    gamePanel[1][Loc].data = '@';
    gamePanel[2][Loc].data = '@';
    gamePanel[3][Loc].data = '@';
    gamePanel[3][Loc+1].data = '@';
    gamePanel[1][Loc-1].moveFlag = true;
    gamePanel[1][Loc].moveFlag = true;
    gamePanel[2][Loc].moveFlag = true;
    gamePanel[3][Loc].moveFlag = true;
    gamePanel[3][Loc+1].moveFlag = true;
    centerLocation = Loc+FRAME_WIDE;
    movingSquares = true;
    squaresType = 5;
}

void moveEleme(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])
{
    for(int i = 0;i < 10;i++)
    {
        if(kbhit())
        {
            int key = getch();
            switch (key)
            {
                case 65:
                case 97:moveElemeToLeft(gamePanel,centerLocation);
                        break;
                case 83:
                case 115:moveDown(gamePanel,centerLocation);
                         break;
                case 68:
                case 100:moveElemeToRight(gamePanel,centerLocation);
                         break;
                case 87:
                case 119:rotate(gamePanel,centerLocation);
                         break;
                case 112:system("pause");system("cls");
            }
        }
    }
    moveDown(gamePanel,centerLocation);
}

void moveElemeToLeft(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate)
{
    int n = centerLocate/FRAME_WIDE+1,m = centerLocate%FRAME_WIDE,maxLeft=-1;
    bool canMoveToLeft = true;
    for(int j = m-1;j <= m+1;j++)
    {
        for(int i = n-1;i <= n+1;i++)
        {
            if(gamePanel[i][j].moveFlag)
            {
                maxLeft = j;
                break;
            }
        }
        if(maxLeft != -1)break;
    }
    if(maxLeft-1 <= 0)canMoveToLeft = false;
    for(int i = n-1;i <= n+1;i++)
    {
        if(!canMoveToLeft)break;
        if(gamePanel[i][m-1].data == '@' && gamePanel[i][m-2].data == '@')canMoveToLeft = false;
    }
    if(canMoveToLeft)
    {
        for(int i = n-1;i <= n+1;i++)
        {
            for (int j = m-1; j <= m+1; j++)
            {
                if(gamePanel[i][j].moveFlag)
                {
                    gamePanel[i][j-1].data = '@';
                    gamePanel[i][j-1].moveFlag = true;
                    gamePanel[i][j].data = ' ';
                    gamePanel[i][j].moveFlag = false;
                }
            }
        }
        for(int i = n-1;i <= n+1;i++)
        {
            if((i == 0) || (i == FRAME_WIDE-1) || (n-1 == 0))continue;
            if(gamePanel[n-1][i].data == '@' && gamePanel[n-1][i].moveFlag == false)continue;
            gamePanel[i][m+1].data = ' ';
            gamePanel[i][m+1].moveFlag = false;
        }
        centerLocation-=1;
    }
}

void moveDown(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate)
{
    int n = centerLocate/FRAME_WIDE+1,m = centerLocate%FRAME_WIDE,maxDown = -1;
    bool canMoveDown = true;
    for(int i = n+1;i >= n-1;i--)
    {
        for(int j = m+1;j >= m-1;j--)
        {
            if(gamePanel[i][j].moveFlag)
            {
                maxDown = i;
                break;
            }
        }
        if(maxDown != -1)break;
    }
    if(maxDown+1 >= FRAME_HEIGH-1)canMoveDown = false;
    for(int i = n+1;i >= n-1;i--)
    {
        for(int j = m-1;j <= m+1;j++)
        {
            if(!canMoveDown)break;
            if(gamePanel[i][j].data == '@' && (gamePanel[i][j].moveFlag == true) && (gamePanel[i+1][j].data == '@') && gamePanel[i+1][j].moveFlag == false)canMoveDown = false;
        }
    }
    if(canMoveDown)
    {
        for(int i = n+1;i >= n-1;i--)
        {
            for (int j = m+1; j >= m-1; j--)
            {
                if(gamePanel[i][j].moveFlag && (gamePanel[i][j].data == '@'))
                {
                    gamePanel[i+1][j].data = '@';
                    gamePanel[i+1][j].moveFlag = true;
                    gamePanel[i][j].data = ' ';
                    gamePanel[i][j].moveFlag = false;
                }
            }
        }
        for(int j = m-1;j <= m+1;j++)
        {
            if((j == 0) || (j == FRAME_WIDE-1) || (n-1 == 0))continue;
            if(gamePanel[n-1][j].data == '@' && gamePanel[n-1][j].moveFlag == false)continue;
            gamePanel[n-1][j].data = ' ';
            gamePanel[n-1][j].moveFlag = false;
        }
        centerLocation+=FRAME_WIDE;
    }
    else
    {
        for(int i = n-1;i <= n+1;i++)
        {
            for(int j = m-1;j <= m+1;j++)
            {
                if(gamePanel[i][j].moveFlag)
                {
                    gamePanel[i][j].moveFlag = false;
                }
            }
        }
        movingSquares = false;
        centerLocation = 0;

        checkErasableLayer(gamePanel);
        checkIsFailed(gamePanel,&gameFlag);
    }
}
void moveElemeToRight(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate)
{
    int n = centerLocate/FRAME_WIDE+1,m = centerLocate%FRAME_WIDE,maxRight = -1;
    bool canMoveToRight = true;
    for(int j = m+1;j >= m-1;j--)
    {
        for(int i = n-1;i <= n+1;i++)
        {
            if(gamePanel[i][j].moveFlag)
            {
                maxRight = j;
                break;
            }
        }
        if(maxRight != -1)break;
    }
    if(maxRight+1 >= FRAME_WIDE-1)canMoveToRight = false;
    for(int i = n-1;i <= n+1;i++)
    {
        if(!canMoveToRight)break;
        if(gamePanel[i][m+1].data == '@' && gamePanel[i][m+2].data == '@')canMoveToRight = false;
    }
    if(canMoveToRight)
    {
        for(int i = n-1;i <= n+1;i++)
        {
            for (int j = m+1; j >= m-1; j--)
            {
                if(gamePanel[i][j].moveFlag)
                {
                    gamePanel[i][j+1].data = '@';
                    gamePanel[i][j+1].moveFlag = true;
                    gamePanel[i][j].data = ' ';
                    gamePanel[i][j].moveFlag = false;
                }
            }
        }
        for(int i = n-1;i <= n+1;i++)
        {
            if((i == 0) || (i == FRAME_WIDE-1) || (n-1 == 0))continue;
            if(gamePanel[n-1][i].data == '@' && gamePanel[n-1][i].moveFlag == false)continue;
            gamePanel[i][m-1].data = ' ';
            gamePanel[i][m-1].moveFlag = false;
        }
        centerLocation+=1;
    }
}

void rotate(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate)
{
    if(canRoate(gamePanel,centerLocate))
    {
        int n = centerLocate/FRAME_WIDE+1,m = centerLocate%FRAME_WIDE;
        char temp;
        bool tempFlag;
        temp = gamePanel[n-1][m].data;
        gamePanel[n-1][m].data = gamePanel[n][m-1].data;
        gamePanel[n][m-1].data = gamePanel[n+1][m].data;
        gamePanel[n+1][m].data = gamePanel[n][m+1].data;
        gamePanel[n][m+1].data = temp;
        temp = gamePanel[n-1][m-1].data;
        gamePanel[n-1][m-1].data = gamePanel[n+1][m-1].data;
        gamePanel[n+1][m-1].data = gamePanel[n+1][m+1].data;
        gamePanel[n+1][m+1].data = gamePanel[n-1][m+1].data;
        gamePanel[n-1][m+1].data = temp;

        tempFlag = gamePanel[n-1][m].moveFlag;
        gamePanel[n-1][m].moveFlag = gamePanel[n][m-1].moveFlag;
        gamePanel[n][m-1].moveFlag = gamePanel[n+1][m].moveFlag;
        gamePanel[n+1][m].moveFlag = gamePanel[n][m+1].moveFlag;
        gamePanel[n][m+1].moveFlag = tempFlag;
        tempFlag = gamePanel[n-1][m-1].moveFlag;
        gamePanel[n-1][m-1].moveFlag = gamePanel[n+1][m-1].moveFlag;
        gamePanel[n+1][m-1].moveFlag = gamePanel[n+1][m+1].moveFlag;
        gamePanel[n+1][m+1].moveFlag = gamePanel[n-1][m+1].moveFlag;
        gamePanel[n-1][m+1].moveFlag = tempFlag;
    }
}

bool canRoate(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int centerLocate)
{
    bool flag = true;
    for(int i = centerLocate/FRAME_WIDE+1;i >= centerLocate/FRAME_HEIGH-1;i--)
    {
        for(int j = centerLocate%FRAME_WIDE-1;j <= centerLocate%FRAME_WIDE+1;j++)
        {
            if(gamePanel[i][j].data == '@' && gamePanel[i][j].moveFlag == false)
            {
                flag = false;
                break;
            }
        }
        if(!flag)break;
    }
    return flag;
}

void checkErasableLayer(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE])
{
    int i,j;
    for(i = FRAME_HEIGH-2;i >= 2;i--)
    {
        for(j = 1;j < FRAME_WIDE-1;j++)
        {
            if(gamePanel[i][j].data != '@')break;
        }
        if(j == FRAME_WIDE-1)
        {
            eraseRow(gamePanel,i);
            gameMark++;
        }
    }
}

void eraseRow(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],int row)
{
    for(int i = row-1;i >= 1;i--)
    {
        for(int j = 1;j < FRAME_WIDE-1;j++)
        {
            gamePanel[i+1][j].data = gamePanel[i][j].data;
            gamePanel[i+1][j].moveFlag = gamePanel[i][j].moveFlag;
        }
    }
    for(int j = 1;j < FRAME_WIDE-1;j++)
        {
            gamePanel[1][j].data = ' ';
            gamePanel[1][j].moveFlag = false;
        }
}

void checkIsFailed(gamePanelElem gamePanel[FRAME_HEIGH][FRAME_WIDE],bool* gameFlag)
{
    for(int i = 1;i < FRAME_WIDE-1;i++)
    {
        if(gamePanel[1][i].data == '@' && gamePanel[1][i].moveFlag == false)*gameFlag = false;
    }
}