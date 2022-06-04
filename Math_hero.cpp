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
using namespace std;
int PhyWidth = 700, PhyHeight = 700;
int logWidth = 100, logHeight = 100;
int centerX = logWidth/2, centerY = logHeight/2;
int sqWidth=10;
int squareX=centerX,squareY=centerY;
int mouseX,mouseY;
bool negFlag=false;
int keyCounter=0;



// Input and answer from the user
stringstream input;
int userAnswer;

class square{
public:
    int centerX,centerY;
    int width,height;
    float red,green,blue;
    int alphaX,alphaY;
    char equation[10];
    int answer;
    bool isAnswered=false;
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

list <square> problems;
void printSome(char *str,int x,int y) {
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
    glFlush();
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
        printf("%s\n",eq);
        string myEq = eq;
        square problem=square();
        //problem.equation=eq       //apparently this is wrong cause you can't assign to arrays -- they're not modifiable       oh god don't I love c
        strcpy(problem.equation, myEq.c_str());
        problem.answer=answerArr[i];
        printf("%s\n",problem.equation);
        printf("%d\n",problem.answer);
        problems.push_back(problem);
    }
    printf("%d\n",problems.size());
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


void timer1( int value ){
    glutTimerFunc(100, timer1, value);
    glutPostRedisplay();
}

void init(float Red,float Blue,float Green,float Alpha){
    glClearColor( Red,Green,Blue,Alpha );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, logWidth, 0.0, logHeight);
}

void Display(){
    glClear( GL_COLOR_BUFFER_BIT );
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
    equationGen();
    // timer1(0);
    glutMainLoop();
}

// list <square>::iterator it = problems.begin();
// advance(it,49);
