from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
phyWidth,phyHeight=700,700
logWidth,logHeight=100,100

buttonWid,buttonHeg=10,10



def Button(x1,y1,x2,y2,x3,y3,x4,y4,AlphaX,AlphaY):
    glBegin(GL_QUADS)
    glVertex2f(10, 10)
    glVertex2f(20, 10)
    glVertex2f(20, 20)
    glVertex2f(10, 20)
    glEnd()
def Polygon(x1,y1,x2,y2,x3,y3,x4,y4,AlphaX,AlphaY):
    glBegin(GL_POLYGON)
    glVertex2f(10, 10)
    glVertex2f(20, 10)
    glVertex2f(20, 20)
    glVertex2f(10, 20)
    glEnd()

def iterate():
    glViewport(0, 0, phyWidth, phyHeight)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, logWidth, 0.0, logHeight, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def mainMenu():
    glColor3f(0,0,0)
    #Background
    Button()
    #Buttons
    Button()
    Button()


def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    mainMenu()
    glutSwapBuffers()

glutInit()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(phyWidth, phyHeight)
glutInitWindowPosition(0, 0)
wind = glutCreateWindow("OpenGL Coding Practice")
glutDisplayFunc(showScreen)
glutIdleFunc(showScreen)
glutMainLoop()











""" openCV code
    image=np.zeros((phyWidth,phyHeight),np.uint8)
    cv.rectangle(image,(0,0),(100,100),(226,158,255),-1)
    image = cv.cvtColor(image, cv.COLOR_BGR2RGB)
    cv.imshow(mainMenuText,image)
    cv.waitKey(0)
    cv.destroyAllWindows()
    
"""

# phyWidth,phyHeight=700,700
# logWidth,logHeight=100,100