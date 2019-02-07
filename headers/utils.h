typedef int boolean;
#define true 1
#define false 0

int tmp_changed=0;
int tmp_lanes[2], i=0;

void initGraphics(){
    int gd = DETECT, gm; initgraph(&gd, &gm, "");
    int err = graphresult();
    if(err != grOk){
        cout << "BGI Error: " << err; getch(); exit(1);
    } setcolor(YELLOW);
}

char* getLaneStr(int lane){
    char tmp[50], tmp2[50] = "Lane ";
    return strcat(tmp2, itoa(lane, tmp, 10));
}

int tmpGetter(int &k){
    if(++k>1){
        k=0;
    } return k;
}

int getUniqueLane(const int lanes){
    while(1){
        int newRand = random(lanes) + 1;
        if(newRand != tmp_lanes[tmpGetter(i)] && newRand != tmp_lanes[tmpGetter(i)]){
            tmp_lanes[tmpGetter(i)] = newRand;
            return newRand;
        }
    }
}

boolean laneChanged(int lane){
    if(tmp_changed != lane){
        tmp_changed = lane;
        return true;
    } else return false;
}

struct coords {
    int x1, x2; int y1, y2;
};
