#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<GL/glut.h>
#include <stdio.h>
#include<string>
#include <iostream>
#include <sstream>
#include <fstream>
#include<list>
#include <iterator>
#include<time.h>
using namespace std;
int PhyWidth = 700, PhyHeight = 700;
int logWidth = 100, logHeight = 100;
int centerX = logWidth/2, centerY =logHeight/2;//-sqHiehgt/2
int squareX=centerX,squareY=centerY;
int mouseX=centerX,mouseY=centerY;
bool negFlag=false;
int keyCounter=0;       //to make sure the user can only input a negative sign in the first of his answer
int score=0;
stringstream input;     // Input and answer from the user
int userAnswer;     // to store the user answer and check if it was valid
int disCount=-4;       // to know which problems are shown
int flag=0;         //menu 0 , play 1
void printSome(const char *str,int x,int y) {
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    glFlush();
}

class square{
public:
    // int cX=(logWidth/2);
    // int cY=-(height/2);
    // int width=10,height=6;
    int cX,cY,width,height;
    float red,green,blue;
    int alphaX=0,alphaY=0;
    char equation[10];
    int answer;
    bool isAnswered=false;
    square(const char * eq,int w,int h,int cx,int cy){
        width=w;
        height=h;
        strcpy(equation,eq);
        cX=cx;
        cY=cy;
    }
    square(int w,int h,int cx,int cy){
        width=w;
        height=h;
        cX=cx;
        cY=cy;
    }
    square (){}
    int returnWid()
    {
        return width;
    }
    void drawSquare(int offset)
    {
        glBegin(GL_QUADS);
        glVertex2d(cX-(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY+(height/2));
        glVertex2d(cX-(width/2),cY+(height/2));
        glEnd();
        glColor3f(0,0,0);
        printSome(equation,cX-offset,cY);
    }
    void drawSquare()
    {
        glBegin(GL_QUADS);
        glVertex2d(cX-(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY+(height/2));
        glVertex2d(cX-(width/2),cY+(height/2));
        glEnd();
        glColor3f(0,0,0);
    }
    void drawSquare(int passiveX,int passiveY) // for the passive mouse looking asthetic
    {
        glColor3f(1,1,1);//white background
        glBegin(GL_QUADS);
        glVertex2d(cX-(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY-(height/2));
        glVertex2d(cX+(width/2),cY+(height/2));
        glVertex2d(cX-(width/2),cY+(height/2));
        glEnd();
        glBegin(GL_QUADS);//a bit darker
        glVertex2d(cX-(width/2),cY-(height/2)+passiveY);
        glVertex2d(cX+(width/2),cY-(height/2)+passiveY);
        glVertex2d(cX+(width/2),cY+(height/2)+passiveY);
        glVertex2d(cX-(width/2),cY+(height/2)+passiveY);
        glEnd();
        glColor3f(0,0,0);
        printSome(equation,cX,cY);
    }
    bool checkRange(int x, int y){// check if point given is within the square
        return x >= cX-width/2 && x <= cX+width/2 && y >= cY-height/2 && y <= cY+height/2;
    }
};
square play=square("Play",20,15,centerX,centerY+25);
square hs=square("High Scores",20,15,centerX,centerY);
square ex=square("Exit",20,15,centerX,centerY-25);
square background=square(logWidth,logHeight,centerX,centerY);
class powerUpBird{
    public:
        int time;       //the time the power up bird should appear
        int cx;        // the location of the bird on the screen
        bool isShown = false; // check if the bird is on the screen at the current time
        powerUpBird(int t){
            time=t;
        }
};

list <powerUpBird> birds;

list <square> problems;
void checkAnswer(){
    for (int i=0;i<4;i++){
        list <square>::iterator it = problems.begin();
        advance(it,i+disCount);
        if(userAnswer==it->answer&&!it->isAnswered){ 
            score++;
            it->isAnswered=true;
            printf("Answer %d is correct for problem no. %d your score is %d\n",userAnswer,i+disCount+1,score);
        }
    }
}

void birdsGen(){ // needs further modefying to inssure that t2 is bigger than t1 at leaset by 15 seconds
                 // and both of them are in the 60 seonds time period
                 // so for the time being let us just work with 1 bird instead of two by only using the first
                 // powerUpBird object in the birds list
    srand(time(0));
    int t1,t2;   
    t1=rand()%40;

    while(true){
        t2=rand()%40;
        if(t2<(t1+15));
            t2+=15;
            break;
        }
        //printf("%d\t%d",t1,t2);
        powerUpBird bird1 = powerUpBird(t1);
        powerUpBird bird2 = powerUpBird(t2);
        birds.push_back(t1);
        birds.push_back(t2);   
}
void equationGen()
{
    //Need to add the generated equation to the squares
    int answerArr[50];
    int num1,num2;
    char operator_;
    char op[3]={'-','+','x'};//lets keep the / for now
    char eq[10];
    for (int i=0;i<50;i++){
        operator_=op[rand()%3];
        num1=rand()%50;
        num2=rand()%50;
        if(operator_=='x')
        {
            num1=rand()%20;
            num2=rand()%20;

        }
        switch(operator_)
        {
            case '-':answerArr[i]=num1-num2;break;
            case '+':answerArr[i]=num1+num2;break;
            case 'x':answerArr[i]=num1*num2;break;
        }
        sprintf(eq,"%d %c %d",num1,operator_,num2);
        string myEq = eq;
        square problem=square(10,6,50,-3);
        //problem.equation=eq       //apparently this is wrong cause you can't assign to arrays -- they're not modifiable       oh god don't I love c
        strcpy(problem.equation, myEq.c_str());
        problem.answer=answerArr[i];
        problem.alphaY=-(logHeight/4)*i;
        problems.push_back(problem);
    }
}

void drawVerticalLine(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(logWidth/2,0);
    glVertex2i(logWidth/2,logHeight);
    glEnd();
}

void drawBoxes(){
    for(int i=0;i<50;i++){
        list <square>::iterator it = problems.begin();
        advance(it,i);
        if(!it->isAnswered) glColor3f(1.0, 1.0, 1.0);
        else glColor3f(0.0,1.0,0.0);
        glBegin(GL_QUADS);
        glVertex2i(it->cX-it->width,it->cY+it->height+it->alphaY);
        glVertex2i(it->cX+it->width,it->cY+it->height+it->alphaY);
        glVertex2i(it->cX+it->width,it->cY-it->height+it->alphaY);
        glVertex2i(it->cX-it->width,it->cY-it->height+it->alphaY);
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        printSome(it->equation,it->cX-it->width+5,it->cY+it->alphaY);
    }
}


void highScores(){//gets triggered after 60 seconds
    int s[10];
    string line;
    int i=0;
    ifstream scores("scores.txt");
    if(scores.is_open()){
        while (getline(scores,line)){
        }
        scores.close();
    }
    else
        cout<<"error to open";
    //write to scores files after sorting the arary
    scores.close();
}
char ans[10];
void keyboard(unsigned char key,int x,int y){
    if(!(key ==(char) 127 || key ==(char) 13 || (key >='0' && key<='9') || key=='-') || (key ==(char) 13 && input.rdbuf()->in_avail() == 0) )//not valid input
    {
        printf("Not valid input");
        input.str(std::string());//clear
    }
    else{
        if(key == (char) 127)//Delete Key, gotta figure out how to delete the key from the input itself , since Sstream is just gonna destory itself, or make it delete the whole thing
        {
            memset(ans,0,255);
            keyCounter=0;
            input.str(std::string());//clear
        }
        ans[keyCounter]=key;
        if(((key>='0'&& key<='9') || key=='-')){
            if(key=='-'&&!negFlag&&keyCounter==0){ 
                input<<key;
                negFlag=true;
                keyCounter++;
            }
            else if (key>='0'&& key<='9'){
                input<<key;
                keyCounter++;
            }
        }
        if(key == (char) 13)
        {
            userAnswer=stoi(input.str());
            input.str("");//clear buffer
            negFlag=false;
            keyCounter=0;
            memset(ans,0,255);
            printf("%d\n",userAnswer);
            checkAnswer();
        }
    }
}
void incr (){
    for (int i=0;i<50;i++){
        list <square>::iterator it = problems.begin();
        advance(it,i);
        it->alphaY+=(logHeight/50);

    }
}
void checkAnswerTimer( int value ){
    if(value)
    {
        glutTimerFunc(2500, checkAnswerTimer, value);
        disCount++;
    }
    else
    {
        return ;
    }
}

void displayTimer(int value){
    if(value)
    {
        glutTimerFunc(200, displayTimer, value);
        incr();
        glutPostRedisplay();
    }
    else
    {
        return ;//do nothing
    }
}
void mouseClick(int btn, int state, int x, int y){
    if((btn==GLUT_LEFT_BUTTON && state==GLUT_UP) && flag == 0)
    {
        mouseX = x;
        mouseX=0.5+1.0*mouseX*logWidth/PhyWidth;
        mouseY = PhyHeight - y;
        mouseY=0.5+1.0*mouseY*logHeight/PhyHeight;
        if(play.checkRange(mouseX,mouseY))
        {
            flag=1;
            checkAnswerTimer(1);
            displayTimer(1);
        }
        if (hs.checkRange(mouseX,mouseY)) printf("HIGHSCORE");
        if (ex.checkRange(mouseX,mouseY)) exit(0);
    }
    glutPostRedisplay();
}

void passiveMouse(int x,int y){
    mouseX = x;
    mouseX=0.5+1.0*mouseX*logWidth/PhyWidth;
    mouseY = PhyHeight - y;
    mouseY=0.5+1.0*mouseY*logHeight/PhyHeight;
    if(play.checkRange(mouseX,mouseY) && flag==0)// dead for now
    {
        //glColor3f(1,1,1);
    }
}



void init(float Red,float Blue,float Green,float Alpha){
    glClearColor( Red,Green,Blue,Alpha );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}

char sc[10];

// square play=square("Play",20,15,centerX,centerY+25); 
void playGame()
{
    drawVerticalLine();// in play function
    drawBoxes();
    glColor3f(1,1,1);
    sprintf(sc,"%s %d","Score: ",score);// PUT IN PLAY FUNC
    printSome(sc,logWidth/10,logHeight/10);
    printSome("Answer: ",logWidth-0.9*logWidth,logHeight-10);
    printSome(ans,logWidth-0.9*logWidth + 10,logHeight-10);
}

void menu()//gets triggered with setup in the background
{
    glColor3f(1,1,1);
    play.drawSquare(3);
    glColor3f(1,1,1);
    hs.drawSquare(7);
    glColor3f(1,1,1);
    ex.drawSquare(5);
}

void Display(){
    glClear( GL_COLOR_BUFFER_BIT );
    switch (flag)
    {
        case 0:menu();break;
        case 1:playGame();break;
    }
    // drawVerticalLine();// in play function
    // drawBoxes();
    glColor3f(1,1,1);
    // menu();
    // printf("%d\n",play.cX);
    // hs.drawSquare();
    // ex.drawSquare();

    glFlush();
    glutSwapBuffers();
}
int main( int argc, char ** argv){
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition( 500, 0);
    glutInitWindowSize(PhyWidth, PhyHeight);
    glutCreateWindow("Math Hero");
    init(0, 0, 0,1);
    glutDisplayFunc(Display);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(keyboard);
    //highScores();
    memset(ans,0,255);
    // checkAnswerTimer(0);
    // displayTimer(0);
    birdsGen();
    equationGen();
    glutMainLoop();
}