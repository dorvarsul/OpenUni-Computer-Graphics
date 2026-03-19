#include <GL/glut.h>
#include <cmath>
#include <random>

// Draws a sun near the top-left using a triangle fan (center + circular rim points).
void drawSun() {

    float centerX = -0.7;
    float centerY = 0.7;
    float RADIUS = 0.1;

    // The center vertex gets a brighter color; the rim gets a warmer orange,
    // creating a simple radial gradient.
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(centerX, centerY);

        glColor3f(1.0, 0.6, 0.0);
        // Sample points around a full circle to form the fan boundary.
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * M_PI * (float)i / 100.0;
            float x = RADIUS * cosf(angle);
            float y = RADIUS * sinf(angle);
            glVertex2f(centerX + x, centerY + y);
        }
    glEnd();
}

// Draws the background (sky + grass) and the perspective road in the center.
void drawRoad() {
    // One quad stream is used for several connected rectangular/trapezoid regions.
    glBegin(GL_QUADS);
        // Drawing sky 
        glColor3f(0.7, 0.85, 1.0); // Lighter blue at the center
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);

        glColor3f(0.1, 0.4, 0.8); // Darker blue at the top
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);

        // Drawing grass
        glColor3f(0.1, 0.2, 0.0); // Darker green at the bottom
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
    
        glColor3f(0.4, 0.8, 0.1); // Lighter green at the center
        glVertex2f(1.0, 0.0);
        glVertex2f(-1.0, 0.0);

        // Drawing road center
        glColor3f(0.1, 0.1, 0.1); // Dark gray for road base
        glVertex2f(-0.4, -1.0);
        glVertex2f(0.4, -1.0);

        glColor3f(0.2, 0.2, 0.2); // Lighter gray for road top
        glVertex2f(0.1, 0.0);
        glVertex2f(-0.1, 0.0);

        // Drawing road outlines
        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(-0.39, -1.0);
        glVertex2f(-0.41, -1.0);

        glColor3f(1.0,1.0,1.0);
        glVertex2f(-0.11, 0.0);
        glVertex2f(-0.09, 0.0);

        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(0.39, -1.0);
        glVertex2f(0.41, -1.0);

        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(0.11, 0.0);
        glVertex2f(0.09, 0.0);
    glEnd();

    // Draw short center lane segments (dashed line) as vertical line pieces.
    glLineWidth(5.0);
    glBegin(GL_LINES);
        // Drawing road markings
        for (int i = 0; i <= 4; i++) {
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f(0.0, -1.0 + i * 0.2);
            glVertex2f(0.0, -1.0 + i * 0.2 + 0.1);
        }
    glEnd();

}

// Draws a simple rectangular building with repeating window rectangles.
void drawBuilding(float x, float y, float width, float height, float colorVariation) {
    glBegin(GL_QUADS);
        // Building body color is varied slightly per building for visual diversity.
        glColor3f(0.5 + colorVariation, 0.5 + colorVariation, 0.5 + colorVariation);
        glVertex2f(x, y);
        glVertex2f(x+width, y);
        glVertex2f(x+width, y+height);
        glVertex2f(x, y+height);

        // Windows
        // Iterate upward and place one horizontal window strip per level.
        for (float windowBase = y + height / 5; windowBase < y + height - 0.1; windowBase += height / 5 + 0.1) {
            glColor3f(0.8, 0.8, 0.8);
            glVertex2f(x + width/4, windowBase);
            glVertex2f(x + 3 * (width/4), windowBase);
            glVertex2f(x + 3 * (width/4), windowBase + height / 5);
            glVertex2f(x + width/4, windowBase + height / 5);
        }
    glEnd();
}

// Composes a skyline by drawing multiple buildings at fixed positions/sizes.
void drawCity() {
    drawBuilding(-0.5, 0.0, 0.18, 0.25, 0.1);
    drawBuilding(-0.3, 0.0, 0.1, 0.4, -0.01);
    drawBuilding(-0.15, 0.0, 0.13, 0.58, 0.05);
    drawBuilding(0.05, 0.0, 0.1, 0.62, -0.02);
    drawBuilding(0.25, 0.0, 0.15, 0.7, 0.03);
    drawBuilding(0.4, 0.0, 0.1, 0.3, -0.04);
}

// GLUT display callback: clears the frame and draws the full scene.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render order: background/road first, then foreground scene objects.
    drawRoad();
    drawSun();
    drawCity();

    // Force immediate execution/flush for single-buffered rendering.
    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT and parse command-line arguments.
    glutInit(&argc, argv);

    // Window creation
    glutInitWindowSize(1024, 768);
    glutCreateWindow("MMN11");

    // Define the drawing region in pixels.
    glViewport(0, 0, 1920, 1080);

    // Register the render callback and enter the event loop.
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;    
}



