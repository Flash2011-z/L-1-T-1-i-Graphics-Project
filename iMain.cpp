#include<iostream>
using namespace std;
# include "iGraphics.h"
#include<windows.h>
#include<mmsystem.h>
#include<string.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"libwinmm.a ")



int bgspeed; //works on 10 12 15

// do not change this




#define screenwidth 1200-15
#define screenheight 661
int jumplimit=120;

int dino_x=180;
int dino_y=50;
int dino_index=0;
bool jump=false;
bool jumUp=false;
int dinojumpcordinate=0;


int gamestate=0;
bool musicOn=true;
bool musicOn2=false;

char*str2;
bool pause=false;

int i=0;


/*
	function iDraw() is called again and again by the system.

	*/
void collisioncheck();


char bgImage[10][100]=
{
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile000.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile001.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile002.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile003.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile004.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile005.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile006.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile007.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile008.bmp",
    "D:\\CSE L-1 T-1\\Project\\New bg\\120-661\\tile009.bmp"

};
char obstacle[8][100]=
{
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_00.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_01.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_02.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_03.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_04.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_05.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_06.bmp",
    "D:\\CSE L-1 T-1\\Project\\obstacle\\obstacle_07.bmp"

};


char dinoImage[3][100]=
{

    "D:\\CSE L-1 T-1\\Project\\Run\\Run_2.bmp",

    "D:\\CSE L-1 T-1\\Project\\Run\\Run_4.bmp",

    "D:\\CSE L-1 T-1\\Project\\Run\\Run_6.bmp"
};

char dinoJumpImage[1][100]= {"D:\\CSE L-1 T-1\\Project\\sprite\\jump.bmp"};

void HighScore();
void ReadScore();

struct bag
{
    int x;
    int y;
};
bag bg[10];

struct obs
{
    int obstacle_x;
    int obstacle_y;
    int obstacle_index;

};
char point[1000];
obs obstract[8];

int score=0;
void scoreupdate()
{
    if(gamestate==2) score++;

    ReadScore();
}

int len=0;
char str1[100];
bool newscore=true;

struct Hscore
{

    char name[100];
    int Scr=0;

} High_score[5];

void ReadScore()
{

    FILE *fp;
    fp=fopen("Score.txt","r");
    char showname[5][30],showscore[5][5];

    for(int i=0; i<5; i++)
    {
        fscanf(fp,"%s %d\n",High_score[i].name,&High_score[i].Scr);
    }

    for(int i=0; i<5; i++)
    {
        sprintf(showname[i],"%s",High_score[i].name);
        sprintf(showscore[i],"%d",High_score[i].Scr);
        iSetColor(255,219,187);
        iText(500,380-50*i,showname[i],GLUT_BITMAP_TIMES_ROMAN_24);
        iText(600,380-50*i,showscore[i],GLUT_BITMAP_TIMES_ROMAN_24);

    }
    fclose(fp);

}
void HighScore()
{
    FILE *fp;
    fp=fopen("Score.txt","r");
    for(int i=0; i<5; i++)
    {
        fscanf(fp,"%s %d\n",High_score[i].name,&High_score[i].Scr);
    }

    int t;
    //char n[50];

    if(newscore)
    {
        for(int i=0; i<5; i++)
        {
            if(High_score[i].Scr<score)
            {
                High_score[4].Scr=score;
                strcpy(High_score[4].name,str1);

                for(int j=0; j<5; j++)
                {
                    for(int k=4; k>j; k--)
                    {
                        if(High_score[k].Scr>High_score[k-1].Scr)
                        {
                            t=High_score[k-1].Scr;
                            High_score[k-1].Scr=High_score[k].Scr;
                            High_score[k].Scr=t;


                            char n[100];
                            strcpy(n,High_score[k-1].name);
                            strcpy(High_score[k-1].name,High_score[k].name);
                            strcpy(High_score[k].name,n);
                        }
                    }
                }

                FILE *fp;
                fp=fopen("Score.txt","w");
                for(int i=0; i<5; i++)
                {
                    fprintf(fp,"%s %d\n",High_score[i].name,High_score[i].Scr);
                }
                fclose(fp);


                score=0;
                break;

            }
        }
    }
}

void iDraw()
{
    //place your drawing codes here
    iClear();

    if(gamestate==0)
    {
        iClear();
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\bg1.bmp");

    }

    else if(gamestate==1)

    {
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\dificulty.bmp");
    }


    else if(gamestate==2)
    {
        iClear();
        iSetColor(255,255,255);
        iFilledRectangle(0,0,screenwidth,screenheight);
        for(int i=0; i<10; i++)
        {


            iShowBMP(bg[i].x,bg[i].y,bgImage[i]);

        }

        for(int i=0; i<8; i++)
        {
            iShowBMP2(obstract[i].obstacle_x,obstract[i].obstacle_y,obstacle[obstract[i].obstacle_index],0);
        }



        if(jump)
        {
            if(jumUp)iShowBMP2(dino_x,dino_y+dinojumpcordinate,dinoJumpImage[0],0);
            else iShowBMP2(dino_x,dino_y+dinojumpcordinate,dinoJumpImage[0],0);
        }
        else iShowBMP2(dino_x,dino_y,dinoImage[dino_index],0);

        collisioncheck();



        iSetColor(0,0,0);
        iFilledRectangle(0,0,120,screenheight);
        iSetColor(245, 219, 193);
        iText(15,530,"Score:",GLUT_BITMAP_TIMES_ROMAN_24);
        sprintf(point,"%d",score);
        iText(80,530,point,GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(245, 219, 193);
        iText(5,450,"DIFFICULTY",GLUT_BITMAP_HELVETICA_18);

        iText(25,420,str2,GLUT_BITMAP_HELVETICA_18);
        iShowBMP(0,100,"D:\\CSE L-1 T-1\\Project\\pause.bmp");



    }
    else if(gamestate==3)
    {
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\crying dino.bmp");

    }


    else if(gamestate==4)
    {
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\game over5.bmp");
        iSetColor(255, 77, 255);
        iText(786,350,point,GLUT_BITMAP_TIMES_ROMAN_24);
         iText(790,275,str1,GLUT_BITMAP_TIMES_ROMAN_24);
         iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);


          //musicOn=true;
           // PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\bg music.wav",NULL,SND_LOOP|SND_ASYNC);



    }

    else if(gamestate==5)
    {
        iClear();
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\settings.bmp");
    }

    else if(gamestate==6)
    {
        iClear();
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\leaderboard.bmp");
        ReadScore();
    }

    else if(gamestate==7)
    {
        iClear();
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\about us.bmp");

    }
    else if(gamestate==8)
    {
        iClear();
        iShowBMP(0,0,"D:\\CSE L-1 T-1\\Project\\instructions.bmp");

    }


}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{


    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
    /*if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    	//place your codes here
    	//	printf("x = %d, y= %d\n",mx,my);
    	x += 10;
    	y += 10;
    }*/

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

    {
        if((gamestate==0 && mx>=491 && mx<=751) && (my>=368 && my<=477))
        {
            gamestate=1;

        }

        else if((gamestate==1 && mx>=444 && mx<=755) && (my>=478 && my<=623))
        {
            gamestate=2;
            bgspeed=10;
            jumplimit=140;
            musicOn=false;
            PlaySoundW(0,0,0);
             str2="EASY";
             score=0;

             iResumeTimer(0);
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);



        }
        else if((gamestate==1 && mx>=374 && mx<=818) && (my>=303 && my<=428))
        {
            gamestate=2;
            bgspeed=12;
            jumplimit=130;
            musicOn=false;
            PlaySoundW(0,0,0);
             str2="MEDIUM";
             score=0;

             iResumeTimer(0);
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);



        }
        else if((gamestate==1 && mx>=450 && mx<=750) && (my>=95 && my<=222))
        {
            gamestate=2;
            bgspeed=15;
            jumplimit=120;
            musicOn=false;
            PlaySoundW(0,0,0);
              str2="HARD";
              score=0;


            iResumeTimer(0);
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);

        }

        else if((gamestate==0 && mx>=41 && mx<=324) && (my>=248 && my<=352))
            gamestate=5;

        else if((gamestate==0 && mx>=786 && mx<=1173) && (my>=135 && my<=208))
            gamestate=6;
        else if((gamestate==0 && mx>=852 && mx<=1140) && (my>=268 && my<=342))
            gamestate=7;

        else if((gamestate==0 && mx>=11 && mx<=399) && (my>=137 && my<=205))
            gamestate=8;

       else if(gamestate==5)
       {
           if((mx>=535 && mx<=653) && (my>=375 && my<=457))
           {
            if(!musicOn){
            musicOn=true;
            PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\bg music.wav",NULL,SND_LOOP|SND_ASYNC);
            }}
            else if((mx>=678 && mx<=833) && (my>=375 && my<=462))
            {
                if(musicOn)
                {
                    musicOn=false;
                    PlaySoundW(0,0,0);
                }
            }
       }
        printf("x = %d, y= %d\n",mx,my);
    }
}

/*if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
	//place your codes here
	x -= 10;
	y -= 10;
}*/


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{



    if(key=='n')
    {

    }



    else if(gamestate==4)
    {
        if(key=='\r')
        {
            gamestate=0;
            HighScore();
            musicOn=true;
            PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\bg music.wav",NULL,SND_LOOP|SND_ASYNC);
        }
        else if(key=='\b')
        {
            if(len<=0)len=0;
            else len--;

            str1[len]='\0';
        }
        else
        {
            str1[len]=key;
            len++;

            if(len>15)len=15;

            str1[len]='\0';
        }

    }
    else if(key=='m')
    {
        if(musicOn)
        {
            musicOn=false;
            PlaySoundW(0,0,0);
        }
        else
        {
            musicOn=true;
            PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\bg music.wav",NULL,SND_LOOP|SND_ASYNC);

        }
    }
    else if(key==' ')
    {
       PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\jump.wav",NULL,SND_ASYNC);
        if(!jump)
        {
            jump=true;
            jumUp=true;
        }

    }
    else if(gamestate==3)
    {
        if(key=='f')
            gamestate=4;
    }

    else if(key=='h')
    {
        gamestate=0;
    }
    else if(gamestate==2 && key=='p')
    {
        if(!pause)
        {
            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);
            pause=true;
        }
        else if(pause)
        {
            iResumeTimer(0);
            iResumeTimer(1);
            iResumeTimer(2);
            iResumeTimer(3);
            pause=false;
        }
    }

}
//place your codes for other keys here


/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_UP)
    {

    }
    else if (key == GLUT_KEY_DOWN)
    {

    }
    else if (key == GLUT_KEY_RIGHT)
    {

    }
    else if (key == GLUT_KEY_LEFT)
    {

    }

    //place your codes for other keys here
}

void setAll()
{
    int sum=0;
    for(int i=0; i<10; i++)
    {
        bg[i].y=0;
        bg[i].x=sum;
        sum+=120;
    }

}

void changebg()
{
    for(int i=0; i<10; i++)
    {
        bg[i].x-=bgspeed;
        if(bg[i].x<0)
            bg[i].x=screenwidth;
    }


    for(int i=0; i<8; i++)
    {
        obstract[i].obstacle_x-=bgspeed;
        if(obstract[i].obstacle_x<0)
        {
            obstract[i].obstacle_x=screenwidth;
            obstract[i].obstacle_index++;
        }
        if(obstract[i].obstacle_index>7)obstract[i].obstacle_index=0;
    }
}

void changedino()
{
    dino_index++;
    if(dino_index>2)dino_index=0;


}

void changeJump()
{
    if(jump)
    {
        if(jumUp)
        {
            dinojumpcordinate+=10;
            if(dinojumpcordinate>jumplimit)
                jumUp=false;
        }

        else
        {
            dinojumpcordinate-=10;
            if(dinojumpcordinate<0)
            {
                jump=false;

                dinojumpcordinate=0;

            }

        }

    }
}

void changeObstacle()
{

}

void setObstacle()
{
    for(int i=0; i<8; i++)
    {
         obstract[i].obstacle_x=screenwidth;
        obstract[i].obstacle_y=50;
        //obstract[i].obstacle_index=rand()%4;
    }
}

void collisioncheck()
{
    for(int i=0; i<8; i++)
        if((dino_x+64>obstract[i].obstacle_x && dino_x<obstract[i].obstacle_x+42) && (dino_y+dinojumpcordinate+70>obstract[i].obstacle_y && dino_y+dinojumpcordinate<obstract[i].obstacle_y+70))
        {

            gamestate=3;
            PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\game over music.wav",NULL,SND_ASYNC);
            iPauseTimer(3);//pause score

        }

}

int main()
{
    //place your own initialization codes here.
    setObstacle();
    setAll();
    iSetTimer(20,changebg);
    iSetTimer(120,changedino);
    iSetTimer(20,changeJump);
    iSetTimer(100,scoreupdate);
    PlaySoundW(L"D:\\CSE L-1 T-1\\Project\\bg music.wav",NULL,SND_LOOP|SND_ASYNC);

    iInitialize(screenwidth,screenheight, "Chrome Dino");

    return 0;

}
