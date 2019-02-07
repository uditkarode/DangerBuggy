class RenderObject {
    protected:
    coords target;
    
    void rndr(){
        rectangle(target.x1, target.y1, target.x2, target.y2);
    }
    
    void fill(int fillColor, int borderColor=YELLOW){
        setfillstyle(SOLID_FILL, fillColor);
        floodfill(target.x1+10, target.y1+5, borderColor);
    }
    
    coords getCoords(){
        return this->target;
    }
    
    public:
    void erase(coords eraser, int bgColor=BLUE){
        int orig = getcolor(); setcolor(GREEN);
        rectangle(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
        setfillstyle(SOLID_FILL, bgColor);
        floodfill(eraser.x1+5, eraser.y1+5, GREEN);
        setcolor(BLUE);
        rectangle(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
        setcolor(orig);
    }
    
    void borderErase(coords eraser){
        int orig = getcolor();
        setcolor(BLUE);
        rectangle(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
        setcolor(orig);
    }
};

class Buggy : public RenderObject {
    void renderWheels(){
        circle(target.x1-5, target.y1+10, 5);
        circle(target.x1+35, target.y1+10, 5);
        circle(target.x1-5, target.y2-10, 5);
        circle(target.x1+35, target.y2-10, 5);
    }
    
    public:
    Buggy(coords arg){
        this->target = arg;
    }
    
    void render(coords newc){
        this->target = newc;
        rndr();
        fill(RED, WHITE);
        renderWheels();
    }
};

class Obstacle : public RenderObject {
    void renderText(){
        int oldColor = getcolor();
        setcolor(RED);
        outtextxy(this->target.x1 + 30, this->target.y1 + 2, "! TREE !");
        moveto(0,0);
        setcolor(oldColor);
    }
    
    public:
    Obstacle(coords arg){
        this->target = arg;
    }
    
    void render(coords newc){
        this->target = newc;
        rndr();
        fill(YELLOW);
        renderText();
    }
};

class Border : public RenderObject {
    public:
    Border(coords arg){
        this->target = arg;
    }
    
    void render(){
        rndr();
    }
};

static class RenderFactory {
    static coords target;
    
    public:
    RenderFactory(coords target){
        this -> target = target;
    }
    
    static RenderObject *make(int type){
            if(type==0)
                return new Buggy(target);
            else if(type==1)
                return new Border(target);
            else if(type==2)
                return new Obstacle(target);
            else return NULL;
    }
};
