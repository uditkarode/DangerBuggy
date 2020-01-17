// @Author Udit Karode <uditkarode.github.io>

#include <iostream.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <time.h>
#include <utils.h>
#include <factory.h>

void loadBorder();
void setupCoords();
void renderLanes();
void checkCollision();
int getUniqueRandom();
void renderGameComponents();
void loadObstacle(int);
void renderMenu(int);
void loadBuggy(int);

coords gBuggy, gObst;
const int LANES = 5;
char menuTitle[40] = "Danger Buggy";
char menuSubtitle[40] = "Press any key to continue";
int obstacleLane = -420;
int velocity;
int curLane = 1;
int laneSize = 0;
int score = 0;

enum {BUGGY, BORDER, OBSTACLE};

void main(){
    clrscr();
    initGraphics();
    renderMenu(false);
    renderGameComponents();
    loadBuggy(curLane);
    randomize();
    
    while(true){
        checkCollision();
        if(obstacleLane == -420) obstacleLane = getUniqueLane(LANES);
        loadObstacle(velocity);
        if(kbhit()){
            char press = getch();
            switch(press){
                case 'a':
                    if(curLane > 1){
                        loadBuggy(--curLane);
                    }
                    break;
                case 'd':
                    if(curLane < LANES){
                        loadBuggy(++curLane);
                    }
                    break;
                case 'q':
                    exit(0);
            }
        } score++;
    }
}

void renderMenu(boolean lost){
    int width = textwidth(menuTitle) ; int height = textheight(menuTitle);
    setbkcolor(RED);
    loadBorder();
    int mrg = 100; int left = mrg ; int top = mrg;
    int bottom = getmaxy() - mrg ; int right = getmaxx() - mrg;
    setfillstyle(SOLID_FILL, BLUE);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);
    setcolor(YELLOW);
    int menuXx = (right + left - width) / 2;
    int menuXy = (bottom + top - height) / 2;
    outtextxy(menuXx,menuXy,menuTitle);
    width = textwidth(menuSubtitle);
    menuXx = (right + left - width) / 2;
    menuXy += textheight(menuSubtitle) + 10;
    moveto(menuXx, menuXy);
    outtext(menuSubtitle);
    if(lost){
        while(true){
            if(getch() == 'p') exit(1);
        }
    } else {
        getch();
        setbkcolor(BLACK);
        cleardevice();
        cout << "Enter initial velocity: ";
        cin >> velocity;
        setbkcolor(BLUE);
    }
}

void renderGameComponents(){
    cleardevice();
    loadBorder();
    renderLanes();
    setupCoords();
}

void renderLanes(){
    laneSize = getmaxx()/LANES + 1;
    for (int i=1; i<=LANES+2; i++) {
        line(laneSize*i, 0, laneSize*i, getmaxy());
        outtextxy(laneSize*i-(laneSize)/2-23, getmaxy()-10, getLaneStr(i));
    }
    line(0, getmaxy()-15, getmaxx(), getmaxy()-15);
}

void loadBorder(){
    rectangle(0, 0, getmaxx(), getmaxy());
    coords borderCoords = {0, 0, getmaxx(), getmaxy()};
    Border *border = (Border*) RenderFactory(borderCoords).make(BORDER);
    border->render();
}

void loadBuggy(int lane){
    Buggy *buggy = (Buggy*) RenderFactory(gBuggy).make(BUGGY);
    gBuggy.x1-=10; gBuggy.x2+=10;
    buggy->erase(gBuggy);
    gBuggy.x1 = (laneSize*lane) - (laneSize/2+15);
    gBuggy.x2 = gBuggy.x1 + 30;
    setcolor(WHITE);
    buggy->render(gBuggy);
    setcolor(YELLOW);
}

void loadObstacle(int speed){
    if(laneChanged(obstacleLane)){
        gObst.x1 = laneSize * (obstacleLane-1) + 3;
        gObst.x2 = laneSize * obstacleLane - 3;
    }
    
    Obstacle *obstacle = (Obstacle*) RenderFactory(gObst).make(OBSTACLE);
    
    gObst.y1 -= speed;
    obstacle->erase(gObst);
    
    if(gObst.y2+speed >= getmaxy()-15){
        obstacleLane = -420;
        gObst.y1 = 10; gObst.y2 = 20;
    } else {
        gObst.y1+=2*speed; gObst.y2+=speed;
        obstacle->render(gObst);
    }
}

void setupCoords(){
    if(laneSize){
        gBuggy.x1 = laneSize - ((laneSize/2)+15);
        gBuggy.x2 = gBuggy.x1 + 30;
        gBuggy.y1 = getmaxy()-100;
        gBuggy.y2 = getmaxy()-50;
        
        gObst.y1 = 10; gObst.y2 = 20;
    }
}

void checkCollision(){
    if(gObst.y1 >= gBuggy.y1 && gObst.y1 <= getmaxy()-50 && obstacleLane == curLane){
        char tmp[50];
        cleardevice();
        strcpy(menuTitle, "Buggy had an accident! Score: ");
        strcat(menuTitle, itoa(score*velocity, tmp, 10));
        strcpy(menuSubtitle, "CS Project By: Udit Karode - Press P to exit");
        renderMenu(true);
    }
}
