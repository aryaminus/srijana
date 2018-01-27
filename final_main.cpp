/*
 * final_main.cpp: OpenGL/GLUT C/C++ Setup graphics project
 * To compile with -lfreeglut -lglu32 -lopengl32
 */

//#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */

int refreshMills = 30;

/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
}

/* Callback handler for window re-paint event */
void display() {
   glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)

   glFlush();  // Render now
}

/* Call back when the windows is re-sized */
void myReshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping area to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();
   if (width >= height) {
     // aspect >= 1, set the height from -1 to 1, with larger width
      gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
   } else {
      // aspect < 1, set the width to -1 to 1, with larger height
     gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
   }
}

/* Called back when the timer expired */
void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
}

/* Callback handler for normal-key event */
void keyboard(unsigned char key, int x, int y) {
   switch (key) {
      case 27:     // ESC key
         exit(0);
         break;
   }
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
   glutInit(&argc, argv);                 // Initialize GLUT
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Use RGBA color, enable double buffering and enable depth buffer
   glutCreateWindow("Srijana: User and Neural Network game"); // Create a window with the given title
   glutInitWindowSize(800, 600);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutDisplayFunc(display); // Register display callback handler for window re-paint
   glutReshapeFunc(myReshape);       // Register callback handler for window re-size event
   glutTimerFunc(0, Timer, 0);     // First timer call immediately
   glutKeyboardFunc(keyboard);   // Register callback handler for special-key event
   initGL();
   glutMainLoop();           // Enter the event-processing loop
   return 0;
}