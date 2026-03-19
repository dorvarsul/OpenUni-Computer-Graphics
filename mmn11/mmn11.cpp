#include <GL/glut.h>
#include <cmath>
#include <random>

bool isNight = false;

// Forward declarations
void drawCloud(float centerX, float centerY, float radius);

// Draws a sun near the top-left using a triangle fan (center + circular rim points).
void drawSky() {

    glBegin(GL_QUADS);
        // Drawing sky
        if (isNight) {
            glColor3f(0.1, 0.1, 0.2); // Darker blue at the bottom
        } else {
            glColor3f(0.5, 0.7, 1.0); // Lighter blue at the bottom
        }
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);

        if (isNight) {
            glColor3f(0.05, 0.05, 0.1); // Even darker blue at the top
        } else {
            glColor3f(0.2, 0.4, 0.8); // Even lighter blue at the top
        }
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
    glEnd();

    if (!isNight) {
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
    } else {
        // Draw a simple moon as a white circle for night mode.
        float centerX = -0.7;
        float centerY = 0.7;
        float RADIUS = 0.1;

        glBegin(GL_TRIANGLE_FAN);
            glColor3f(0.9, 0.9, 0.9);
            glVertex2f(centerX, centerY);

            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * M_PI * (float)i / 100.0;
                float x = RADIUS * cosf(angle);
                float y = RADIUS * sinf(angle);
               glVertex2f(centerX + x, centerY + y);
            }
    }
    glEnd();
}

// Draws small white dots to represent stars in the night sky.
void drawStars() {
    if (!isNight) return;
    
    glColor3f(1.0, 1.0, 1.0); // White stars
    glPointSize(2.0);
    glBegin(GL_POINTS);
    
    // Use a seeded random generator for consistent star placement
    std::mt19937 gen(42); // Fixed seed for consistent stars
    std::uniform_real_distribution<> disX(-1.0, 1.0);
    std::uniform_real_distribution<> disY(0.0, 1.0); // Stars only in upper half
    
    // Generate 60 stars
    for (int i = 0; i < 60; i++) {
        float x = disX(gen);
        float y = disY(gen);
        glVertex2f(x, y);
    }
    
    glEnd();
    glPointSize(1.0); // Reset point size
}

// Draws simple white clouds in the daytime sky.
void drawClouds() {
    if (isNight) return; // Clouds only during daytime
    
    glColor3f(1.0, 1.0, 1.0); // White clouds
    
    // Cloud 1: top-right area
    drawCloud(0.6, 0.7, 0.08);
    
    // Cloud 2: top-left area
    drawCloud(-0.5, 0.75, 0.1);
    
    // Cloud 3: middle-right area
    drawCloud(0.3, 0.5, 0.07);
    
    // Cloud 4: middle area
    drawCloud(-0.2, 0.55, 0.09);
}

// Helper function to draw a single cloud as overlapping circles.
void drawCloud(float centerX, float centerY, float radius) {
    glColor3f(1.0, 1.0, 1.0); // White
    
    // Draw cloud as 3 overlapping circles
    for (int circle = 0; circle < 3; circle++) {
        float offsetX = (circle - 1) * radius * 0.6;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(centerX + offsetX, centerY);
            for (int i = 0; i <= 100; i++) {
                float angle = 2.0f * M_PI * (float)i / 100.0;
                float x = radius * cosf(angle);
                float y = radius * sinf(angle);
                glVertex2f(centerX + offsetX + x, centerY + y);
            }
        glEnd();
    }
}

// Draws the background (sky + grass) and the perspective road in the center.
void drawRoad() {
    // One quad stream is used for several connected rectangular/trapezoid regions.
    glBegin(GL_QUADS);


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
            if (!isNight) {
                glColor3f(0.85, 0.85, 0.85); // Light gray for daytime windows
            } else {
                glColor3f(1.0, 1.0, 0.0); // Yellowish white for lit windows at night
            }
            
            glVertex2f(x + width/4, windowBase);
            glVertex2f(x + 3 * (width/4), windowBase);
            glVertex2f(x + 3 * (width/4), windowBase + height / 5);
            glVertex2f(x + width/4, windowBase + height / 5);
        }
    glEnd();
}

// Composes a skyline by drawing multiple buildings at fixed positions/sizes.
void drawCity() {
    drawBuilding(-0.4, 0.0, 0.15, 0.25, -0.03);
    drawBuilding(-0.22, 0.0, 0.1, 0.4, -0.05);
    drawBuilding(-0.1, 0.0, 0.2, 0.75, -0.02);
    drawBuilding(0.12, 0.0, 0.15, 0.5, -0.06);
    drawBuilding(0.3, 0.0, 0.1, 0.7, -0.1);
    drawBuilding(0.4, 0.0, 0.09, 0.4, -0.01);
    drawBuilding(0.5, 0.0, 0.12, 0.2, 0.0);
}

void renderText(float x, float y, const char* text, int type) {
    if (type == 0) {
        glColor3f(0.0, 0.0, 0.0); // Black for title
    } else if (type == 1) {
        glColor3f(1.0, 1.0, 1.0); // White for name of student
    } else {
        glColor3f(0.8, 0.9, 0.9); // Default to light cyan for other text
    }

    // Set the position where the text should start
    glRasterPos2f(x, y);

    // Loop through each character in the string
    for (const char* c = text; *c != '\0'; c++) {
        if (type == 0) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        } else if (type == 1) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
        } else {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
        }
    }
}

void drawExitButton() {
    glBegin(GL_QUADS);
        glColor3f(0.8, 0.1, 0.1); // Red color for the button
        float x1 = 0.7, y1 = -0.9, width = 0.2, height = 0.1;
        glVertex2f(x1, y1);
        glVertex2f(x1 + width, y1);
        glVertex2f(x1 + width, y1 + height);
        glVertex2f(x1, y1 + height);
    glEnd();

    // 2. Draw the Text
    renderText(x1 + width / 4, y1 + height / 2, "Exit", 2);
}

void mouse(int button, int state, int x, int y) {
    // 1. Check for Right Click press
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        
        // Get current window dimensions
        float w = glutGet(GLUT_WINDOW_WIDTH);
        float h = glutGet(GLUT_WINDOW_HEIGHT);

        // 2. Convert Mouse Pixels to NDC (-1.0 to 1.0)
        // Formula: (pixel / total_size) * 2 - 1
        float mouseX = (x / w) * 2.0f - 1.0f;
        float mouseY = ((h - y) / h) * 2.0f - 1.0f; // Note the (h-y) to flip the axis

        // 3. Define your button boundaries (from your image)
        float x1 = 0.7f;
        float width = 0.2f;
        float y1 = -0.9f;
        float height = 0.1f;

        float x2 = x1 + width;  // 0.9
        float y2 = y1 + height; // -0.8

        // 4. Hit Detection
        if (mouseX >= x1 && mouseX <= x2 && mouseY >= y1 && mouseY <= y2) {
            printf("Closing program.\n");
            exit(0); 
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        isNight = !isNight;
        glutPostRedisplay();
    }
}

// GLUT display callback: clears the frame and draws the full scene.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Render order: background/road first, then foreground scene objects.
    drawRoad();
    drawSky();
    drawStars();
    drawClouds();
    drawCity();

    // Render Text in the top-left corner
    renderText(-0.95, 0.9, "Scene - Road to the City", 1);
    renderText(0.5, 0.9, "By Dor Varsulker", 0);

    drawExitButton();

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
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;    
}



