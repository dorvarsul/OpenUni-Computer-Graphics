#include <GL/glut.h>
#include <cmath>
#include <random>

void drawSun() {

    float centerX = -0.7;
    float centerY = 0.7;
    float RADIUS = 0.1;
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(centerX, centerY);

        glColor3f(1.0, 0.6, 0.0);
        for (int i = 0; i <= 100; i++) {
            float angle = 2.0f * M_PI * (float)i / 100.0;
            float x = RADIUS * cosf(angle);
            float y = RADIUS * sinf(angle);
            glVertex2f(centerX + x, centerY + y);
        }
    glEnd();
}

void drawRoad() {
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

void drawBuilding(float x, float y, float width, float height, float colorVariation) {
    glBegin(GL_QUADS);
        glColor3f(0.5 + colorVariation, 0.5 + colorVariation, 0.5 + colorVariation);
        glVertex2f(x, y);
        glVertex2f(x+width, y);
        glVertex2f(x+width, y+height);
        glVertex2f(x, y+height);

        // Windows
        for (float windowBase = y + height / 5; windowBase < y + height - 0.1; windowBase += height / 5 + 0.1) {
            glColor3f(0.8, 0.8, 0.8);
            glVertex2f(x + width/4, windowBase);
            glVertex2f(x + 3 * (width/4), windowBase);
            glVertex2f(x + 3 * (width/4), windowBase + height / 5);
            glVertex2f(x + width/4, windowBase + height / 5);
        }
    glEnd();
}

void drawCity() {
    drawBuilding(-0.5, 0.0, 0.18, 0.25, 0.1);
    drawBuilding(-0.3, 0.0, 0.1, 0.4, -0.01);
    drawBuilding(-0.15, 0.0, 0.13, 0.58, 0.05);
    drawBuilding(0.05, 0.0, 0.1, 0.62, -0.02);
    drawBuilding(0.25, 0.0, 0.15, 0.7, 0.03);
    drawBuilding(0.4, 0.0, 0.1, 0.3, -0.04);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawRoad();
    drawSun();
    drawCity();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);

    // Window creation
    glutInitWindowSize(1024, 768);
    glutCreateWindow("MMN11");
    glViewport(0, 0, 1920, 1080);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;    
}



