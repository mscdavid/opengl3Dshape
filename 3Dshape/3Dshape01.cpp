#include <GL/freeglut.h>

float rtri = 0.0f;  // Rotation angle for the triangle
float rquad = 0.0f; // Rotation angle for the cube

float posX = 0.0f, posY = 0.0f, posZ = -6.0f; // Position variables
float scale = 1.0f;                           // Scale variable
float rotX = 0.0f, rotY = 0.0f;               // Rotation variables

float moveSpeed = 0.05f;  // Movement speed
float rotSpeed = 2.0f;    // Rotation speed
float scaleSpeed = 0.05f; // Scaling speed

// To store the movement direction
float moveX = 0.0f, moveY = 0.0f, moveZ = 0.0f;

void handleKeyPress(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': rotY -= rotSpeed; break;          // Rotate left
    case 'd': rotY += rotSpeed; break;          // Rotate right
    case 'w': rotX -= rotSpeed; break;          // Rotate up
    case 's': rotX += rotSpeed; break;          // Rotate down
    case '+': scale += scaleSpeed; break;       // Increase scale
    case '-': if (scale > 0.1f) scale -= scaleSpeed; break; // Decrease scale
    }
}

void handleSpecialKeyPress(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT: moveX = -moveSpeed; break;  // Move left
    case GLUT_KEY_RIGHT: moveX = moveSpeed; break; // Move right
    case GLUT_KEY_UP: moveY = moveSpeed; break;    // Move up
    case GLUT_KEY_DOWN: moveY = -moveSpeed; break;  // Move down
    }
}

void handleSpecialKeyRelease(int key, int x, int y) {
    // Reset the movement direction when keys are released
    if (key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT) moveX = 0.0f;
    if (key == GLUT_KEY_UP || key == GLUT_KEY_DOWN) moveY = 0.0f;
}

void DrawGLScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The View

    posX += moveX;
    posY += moveY;
    posZ += moveZ;

    glTranslatef(posX, posY, posZ);     // Move based on position variables
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);  // Rotate based on X axis
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);  // Rotate based on Y axis
    glScalef(scale, scale, scale);       // Apply scaling to the cube

    


    glBegin(GL_TRIANGLES);                  // Start Drawing The Pyramid



    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Front)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);          // Left Of Triangle (Front)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);          // Right Of Triangle (Front)



    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Right)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(1.0f, -1.0f, 1.0f);          // Left Of Triangle (Right)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(1.0f, -1.0f, -1.0f);         // Right Of Triangle (Right)



    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Back)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(1.0f, -1.0f, -1.0f);         // Left Of Triangle (Back)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);         // Right Of Triangle (Back)


    glColor3f(1.0f, 0.0f, 0.0f);          // Red
    glVertex3f(0.0f, 1.0f, 0.0f);          // Top Of Triangle (Left)
    glColor3f(0.0f, 0.0f, 1.0f);          // Blue
    glVertex3f(-1.0f, -1.0f, -1.0f);          // Left Of Triangle (Left)
    glColor3f(0.0f, 1.0f, 0.0f);          // Green
    glVertex3f(-1.0f, -1.0f, 1.0f);          // Right Of Triangle (Left)
    glEnd();                        // Done Drawing The Pyramid

    


    glLoadIdentity();
    glTranslatef(1.5f, 0.0f, -7.0f);              // Move Right And Into The Screen

    glRotatef(rquad, 1.0f, 1.0f, 1.0f);            // Rotate The Cube On X, Y & Z

 

    rtri += 0.2f;                     // Increase The Rotation Variable For The Triangle
    rquad -= 0.15f;                       // Decrease The Rotation Variable For The Quad
                       // Keep Goi
    glutSwapBuffers();  // Swap buffers for double buffering
}

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set the background color to black
    glEnable(GL_DEPTH_TEST);                // Enable depth testing for 3D rendering
    glMatrixMode(GL_PROJECTION);            // Set the projection matrix mode
    glLoadIdentity();                       // Reset the projection matrix
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); // Set the perspective view
    glMatrixMode(GL_MODELVIEW);             // Set the modelview matrix mode
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);                  // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Set the display mode
    glutInitWindowSize(800, 600);           // Set the window size
    glutCreateWindow("3D Model Viewer");    // Create the window

    initGL();                               // Initialize OpenGL settings

    glutDisplayFunc(DrawGLScene);           // Set the display function
    glutIdleFunc(DrawGLScene);              // Set the idle function to keep rendering
    glutKeyboardFunc(handleKeyPress);       // Set the keyboard press handler
    glutSpecialFunc(handleSpecialKeyPress); // Set the special key press handler
    glutSpecialUpFunc(handleSpecialKeyRelease); // Handle key release for smooth stop

    glutMainLoop();                         // Start the GLUT main loop
    return 0;
}
