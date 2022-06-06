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
int centerX = logWidth/2, centerY =-3;
int sqWidth=12;
int sqHeight=8;
int squareX=centerX,squareY=centerY;
int mouseX,mouseY;
bool negFlag=false;
int keyCounter=0;       //to make sure the user can only input a negative sign in the first of his answer
int score=0;
stringstream input;     // Input and answer from the user
int userAnswer;     // to store the user answer and check if it was valid
int disCount=0;       // to know which problems are shown

class square{
public:
    int centerX=(logWidth/2);
    int centerY=-3;
    int width=10,height=6;
    float red,green,blue;
    int alphaX,alphaY;
    char equation[10];
    int answer;
    bool isAnswered=false;
    bool isDisplayed=false;
    square(char * eq,int w,int h,float r,float g,float b,int cx,int cy){
        width=w;
        height=h;
        strcpy(equation,eq);
        red=r;
        blue=b;
        green=g;
        centerX=cx;
        centerY=cy;
    }
    square(){};
    bool checkRange(int x, int y){// check if point given is within the square
        return x >= centerX-width/2 && x <= centerX+width/2 && y >= centerY-height/2 && y <= centerY+height/2;
    }
};

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
    for (int i=0;i<3;i++){
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
            printf("if invoked\n");
            t2+=15;
            break;
        }
        printf("%d\t%d",t1,t2);
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
        //printf("%s\n",eq);
        string myEq = eq;
        square problem=square();
        //problem.equation=eq       //apparently this is wrong cause you can't assign to arrays -- they're not modifiable       oh god don't I love c
        strcpy(problem.equation, myEq.c_str());
        problem.answer=answerArr[i];
        //printf("%s\n",problem.equation);
        printf("%d\n",problem.answer);
        problems.push_back(problem);
    }
    list <square>::iterator it = problems.begin();
    advance(it,disCount);
    printf("yooooooooooooooooo %s\n",it->equation);
}

void drawVerticalLine(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(logWidth/2,0);
    glVertex2i(logWidth/2,logHeight);
    glEnd();
}

void printSome(char *str,int x,int y) {
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
    glFlush();
}
void drawBoxes(){
    list <square>::iterator it = problems.begin();
    advance(it,disCount);
    glColor3f(1.0, 1.0, 1.0);
    //printf("%d\t%d\n",it->centerX,it->centerY);
    glBegin(GL_QUADS);
    glVertex2i(centerX-sqWidth,centerY+sqHeight+it->alphaY);
    glVertex2i(centerX+sqWidth,centerY+sqHeight+it->alphaY);
    glVertex2i(centerX+sqWidth,centerY-sqHeight+it->alphaY);
    glVertex2i(centerX-sqWidth,centerY-sqHeight+it->alphaY);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    printSome(it->equation,centerX-sqWidth+2,centerY+it->alphaY);

}

void highScores(){
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


void keyboard(unsigned char key,int x,int y){
    if((key>='0'&& key<='9') || key=='-'){
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
        //string s=input.str();
        // input.clear();
        input.str("");//clear buffer
        negFlag=false;
        keyCounter=0;
        //cout<<s<<endl;
        printf("%d\n",userAnswer);
        checkAnswer();
        //userAnswer=0;
    }
}

void mouseClick(int btn, int state, int x, int y){
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        mouseX = x;
        mouseX=0.5+1.0*mouseX*logWidth/PhyWidth;
        mouseY = PhyHeight - y;
        mouseY=0.5+1.0*mouseY*logHeight/PhyHeight;
        squareX=mouseX;
        squareY=mouseY;
    }
    glutPostRedisplay();
}

void passiveMouse(int x,int y){
}

void checkAnswerTimer( int value ){
    glutTimerFunc(3000, checkAnswerTimer, value);
    glutPostRedisplay();
    disCount++;
    printf("%d lmao \n",disCount);
}

void displayTimer(int value){
    glutTimerFunc(120, displayTimer, value);
    glutPostRedisplay();
    list <square>::iterator it = problems.begin();
    advance(it,disCount);
    it->alphaY+=(logHeight/25);
    glutPostRedisplay();
    

    
}

void init(float Red,float Blue,float Green,float Alpha){
    glClearColor( Red,Green,Blue,Alpha );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}

void Display(){
    glClear( GL_COLOR_BUFFER_BIT );
    drawVerticalLine();
    drawBoxes();
    glFlush();
    glutSwapBuffers();
}

int main( int argc, char ** argv){
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition( 150, 150);
    glutInitWindowSize(PhyWidth, PhyHeight);
    glutCreateWindow("Math Hero");
    init(0, 0, 0,1);
    glutDisplayFunc(Display);
    glutMouseFunc(mouseClick);
    glutPassiveMotionFunc(passiveMouse);
    glutKeyboardFunc(keyboard);
    //highScores();
    //equationGen();
    checkAnswerTimer(0);
    displayTimer(0);
    birdsGen();
    glutMainLoop();
}

