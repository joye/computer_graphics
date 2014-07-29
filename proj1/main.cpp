#include "core.h"
#include "matrix.h"

// Function Declarations
// Glut requires that we use global/static functions so we declare a few below
void myKeyboardFunc( unsigned char key, int x, int y );
void drawScene(void);
void resizeWindow(int w, int h);

// Rendering Functions
void initRendering();
void drawCube(const Matrix &mTransform);

// Global Variables, use as few as possible :)
float g_Rotation = 0;
float g_RotStep = 0.0001;
float g_Aspect = 1;

/////////////////////////////////////////////////////////////////////////////
// Name:           myKeyboardFunc
// Arguments:      the character pressed on the keyboard, and the (x,y)
//                 coordinates of the mouse location, 
// Returns:        none
// Notes:          glut calls this function each time a keystroke occurs              
/////////////////////////////////////////////////////////////////////////////
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key ) {

        // Increase the rotation step size
        case '+':        
            g_RotStep += 0.0001;
            if(g_RotStep > 0.001)
                g_RotStep = 0.001;
            break;
        // Decrease the rotation step size
        case '-':        
            g_RotStep -= 0.0001;
            if(g_RotStep < 0)
                g_RotStep = 0;
            break;   
        case 27:         // "27" is theEscape key
            exit(1);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Name:           drawScene
// Arguments:      none
// Returns:        none
// Notes:          drawScene is called by glut each time we draw a new frame
//                 Allocating memory (using 'new') in this function is generally 
//                 a bad idea, and it's slow. Remember, if you do allocate memory, 
//                 be sure to delete it before the function exits so you don't get
//                 memory leaks.
/////////////////////////////////////////////////////////////////////////////
void drawScene(void)
{
    
    // This command clears the screen to the 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup our projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//  glOrtho(-30,30,-30,30,0,80);
    gluPerspective(60,g_Aspect,.1,80);

    // Switch to ModelView
    glMatrixMode(GL_MODELVIEW);

//***************************************************************************
//**************** Do not alter anything above this line ********************
//************************* Begin Assignment ********************************


	Matrix rot1, trans1, CTM;
	CTM = Matrix::IDENTITY;
	Vector3 v = Vector3(-1,1,-1);
	v.Normalize();
	// Spinning Cube
	//rot1.MakeRotateY(g_Rotation);
	rot1.MakeRotateUnitAxis(v,g_Rotation);
	trans1.MakeTranslate(0,0,-40);
	CTM = CTM*trans1;
	drawCube(trans1*rot1);
	CTM = CTM*rot1;

	
	Matrix rot2,scale2,trans2;

	trans2.MakeTranslate(-10,0,0);
	rot2.MakeRotateY(g_Rotation);
	CTM = CTM*trans2;
	CTM = CTM*rot2;
	scale2.MakeScale(0.6f,0.6f,0.6f);
	//trans2.MakeTranslate(0,0,-4);
	CTM = CTM*scale2;
	drawCube(CTM);



	Matrix rot3, scale3,trans3;
	trans3.MakeTranslate(0,0,5);
	CTM = CTM*trans3;

	rot3.MakeRotateX(g_Rotation);
	CTM = CTM*rot3;

	scale3.MakeScale(0.5f,0.5f,0.5f);
	CTM = CTM*scale3;
	drawCube(CTM);
	

//************************** End Assignment *********************************
//**************** Do not alter anything past this line *********************
//***************************************************************************

    // Update rotation angle
    g_Rotation += g_RotStep;
    // Tell glut to redraw the scene for the next frame
    glutSwapBuffers();
    glutPostRedisplay();
}

/////////////////////////////////////////////////////////////////////////////
// Name:           initRendering
// Arguments:      none
// Returns:        none
// Notes:          Initialize the OpenGL features we'd like to use
/////////////////////////////////////////////////////////////////////////////
void initRendering()
{
    // Setup the background color
    glClearColor(0.5,0.7,0.9,1);
    // Enable depth testing
    glEnable ( GL_DEPTH_TEST );
    // Enable back face culling
    glEnable ( GL_CULL_FACE );
}

/////////////////////////////////////////////////////////////////////////////
// Name:           resizeWindow
// Arguments:      none
// Returns:        none
// Side Effects:   sets g_Aspect to the aspect ratio w/h
// Notes:          Called when the window is resized
//                 w, h - width and height of the window in pixels.
/////////////////////////////////////////////////////////////////////////////
void resizeWindow(int w, int h)
{
    // Define the portion of the window used for OpenGL rendering.
    glViewport( 0, 0, w, h );   // View port uses whole window
    g_Aspect = (float)w/h;
}
    
// Main routine
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    // Initialize glut
    glutInit(&argc,argv);

    // GLUT_DOUBLE: double buffering for smoother animations,
    // GLUT_RGB:    select the RGB color model (actually RGBA)
    // GLUT_DEPTH:  we want a window with a depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Window position (from top corner), and size (width and height)
    glutInitWindowPosition( 20, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow( "CSE167 Matrix Project" );

    // Setup the OpenGL features we'd like to use
    // NOTE: Always setup these features after creating the window, otherwise 
    // they may not work.
    initRendering();

    // Set up callback functions for key presses
    glutKeyboardFunc( myKeyboardFunc );         // Handles "normal" ascii symbols

    // Set up the callback function for resizing windows
    glutReshapeFunc( resizeWindow );

    // call this whenever window needs redrawing
    glutDisplayFunc( drawScene );

    printf("Press Escape to exit\n\
Use + and - to increase/decrease the rotation speed\n");
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop();

    return(0);  // This line is never reached.
}

/////////////////////////////////////////////////////////////////////////////
// Name:           drawCube
// Arguments:      A transformation to apply to the cube before drawing
// Returns:        none
// Side Effects:   draws a cube using OpenGL Quads
// Notes:          If passed the Identity matrix, this routine draws a cube
//                 with side length 2 centered at (0,0,0).
//                 Does not currently work with OpenGL lighting due to lack
//                 of surface normals
/////////////////////////////////////////////////////////////////////////////
void drawCube(const Matrix &mTransform) {

    Point3 p1 = mTransform * Point3( 1,-1, 1);
    Point3 p2 = mTransform * Point3( 1,-1,-1);
    Point3 p3 = mTransform * Point3( 1, 1,-1);
    Point3 p4 = mTransform * Point3( 1, 1, 1);
    Point3 p5 = mTransform * Point3(-1,-1, 1);
    Point3 p6 = mTransform * Point3(-1,-1,-1);
    Point3 p7 = mTransform * Point3(-1, 1,-1);
    Point3 p8 = mTransform * Point3(-1, 1, 1);
	/*mTransform.Print("mTransform");
	p1.Print("p1");
	p2.Print("p2");
	p3.Print("p3");
	p4.Print("p4");
	p5.Print("p5");
	p6.Print("p6");
	p7.Print("p7");
	p8.Print("p8");*/
    glBegin(GL_QUADS);

        glColor3f(0,1,0);
        glVertex3fv(p1);
        glVertex3fv(p2);
        glVertex3fv(p3);
        glVertex3fv(p4);

        glColor3f(0,1,0);
        glVertex3fv(p7);
        glVertex3fv(p6);
        glVertex3fv(p5);
        glVertex3fv(p8);

        glColor3f(1,1,1);
        glVertex3fv(p2);
        glVertex3fv(p1);
        glVertex3fv(p5);
        glVertex3fv(p6);

        glColor3f(0,0,1);
        glVertex3fv(p3);
        glVertex3fv(p2);
        glVertex3fv(p6);
        glVertex3fv(p7);

        glColor3f(1,1,1);
        glVertex3fv(p4);
        glVertex3fv(p3);
        glVertex3fv(p7);
        glVertex3fv(p8);

        glColor3f(0,0,1);
        glVertex3fv(p1);
        glVertex3fv(p4);
        glVertex3fv(p8);
        glVertex3fv(p5);

    glEnd();

}