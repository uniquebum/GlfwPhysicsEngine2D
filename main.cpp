#include "./headers/GlfwHeaders.h"
#include <iostream>

int main(void)
{
    GLFWwindow *window;
    GlfwGameControl gameControl;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /* Define view size as W_WIDTH and W_HEIGHT instead of -1 to 1 (also scaling and rotation) */
    glViewport(0.0f, 0.0f, W_WIDTH, W_HEIGHT);
    glLoadIdentity();
    glOrtho(0, W_WIDTH, 0, W_HEIGHT, 0, 1); //Screen size, rotation and scaling

    /* Define keycallbacks */
    glfwSetWindowUserPointer(window, (void *)&gameControl);
    glfwSetKeyCallback(window, GlfwGameControl::keyCallback);

    // TODO: Abstractify shape definition
    // Define shapes
    GlfwSquare *sq = gameControl.createObject(GlfwSquare(470, 440, 200, 60, 0, false, 20));
    sq->setVelocity(3, 0);
    gameControl.createObject(GlfwSquare(1, 1, W_WIDTH - 1, 80));
    gameControl.createObject(GlfwSquare(760, 350, 280, 60, M_PI / 2, false, 120));
    //gameControl.createObject(GlfwSquare(60, 650, 100, 30, 0, false, 120));

    // Reset performance calc
    gameControl.resetPerformance();
    double msPerFrame;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Calculate performance
        msPerFrame = gameControl.getPerformance();
        std::cout << msPerFrame << "\n";

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Update objects */
        gameControl.updateAll(msPerFrame);

        /* Draw objects */
        gameControl.drawAll();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
FPS LIMITER

double lasttime = glfwGetTime();
while (!glfwWindowShouldClose(window)) {
    myGameUpdate();
    while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {
        // TODO: Put the thread to sleep, yield, or simply do nothing
    }
    lasttime += 1.0/TARGET_FPS;
}
*/
