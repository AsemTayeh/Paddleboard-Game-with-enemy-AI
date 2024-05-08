#include <iostream>
#include <string>
#include <raylib.h>

using namespace std;

const int screenWidth = 1920;
const int screenHeight = 1080;
int CPUScoreInt = 0;
int playerScoreInt = 0;

class Ball {

private:

    float xPos, yPos;
    float radius;

public:

    int speedX, speedY;

    Ball() {

        DrawCircle(screenWidth / 2, screenHeight / 2, 20.0, WHITE); // First 2 parameters are the circle's starting position. (x and y respectively)
        xPos = screenWidth / 2 + 1;
        yPos = screenHeight / 2;
        radius = 20.0;
        speedX = 7.5; // setting ball speed to 7.5 fixes colission issue
        speedY = 7.5;
    }

    float getY() {

        return yPos;
    }

    float getX() {

        return xPos;
    }

    float getRad() {

        return radius;
    }

    void resetBall() {

        yPos = screenHeight / 2;
        xPos = screenWidth / 2;
        int randomSpeed[2] = { -1,1 };

        speedX *= randomSpeed[GetRandomValue(0, 1)];
        speedY *= randomSpeed[GetRandomValue(0, 1)];
    }

    void Update() {

        yPos += speedY;
        xPos += speedX;

        if (yPos + radius >= GetScreenHeight() || yPos - radius <= 0) {

            speedY *= -1;
        }

        if (xPos + radius >= GetScreenWidth()) {

            speedX *= -1;
            CPUScoreInt++;
            resetBall();
        }

        if (xPos - radius <= 0) {

            playerScoreInt++;
            resetBall();
        }

        DrawCircle(xPos, yPos, radius, WHITE);
    }
};

class Paddle {

public:

    float xPos, yPos;
    float width, height;
    int score;
    double ySpeed;

    Paddle() {

        xPos = screenWidth - 45;
        yPos = screenHeight / 2 - 90;
        width = 35;
        height = 180;
        score = 0;
        ySpeed = 7;
    }

    void drawPaddle() {

        DrawRectangle(xPos, yPos, width, height, WHITE);
    }

    void updatePlayer() {

        if (yPos + height >= screenHeight) {

            if (IsKeyDown(KEY_DOWN) == true) {

                yPos = screenHeight - height; // so it can stand up straight
                // alternatively yPos -= ySpeed; but this leads to choppiness on angles
                return;
            }
        }

        if (yPos <= 0) {

            if (IsKeyDown(KEY_UP) == true) {

                yPos = 0;
                // alternatively yPos += ySpeed;
                return;
            }
        }

        if (IsKeyDown(KEY_UP) == true) { // iskeydown means is the UP KEY being pressed down

            yPos -= ySpeed;
        }

        if (IsKeyDown(KEY_DOWN) == true) { // iskeydown means is the DOWN KEY being pressed down

            yPos += ySpeed;
        }
    }

};

class CPUPaddle : public Paddle {

public:

    CPUPaddle() {

        xPos = 10;
        yPos = screenHeight / 2 - 90;
        height = 180;
        width = 35;
        ySpeed = 6.1;
    }

    void drawCPU() {

        DrawRectangle(xPos, yPos, width, height, WHITE);
    }

    void withinBounds() {

        if (yPos <= 0)
            yPos = 0;

        if (yPos + height >= screenHeight)
            yPos = screenHeight - height;
    }

    void updateCPU(float ballHeight, float ballX) {

        // because y is at the center of the paddle
        if (yPos + height / 2 > ballHeight and ballX <= screenWidth / 2) {

            yPos -= ySpeed; // if CPU paddle is under the ball, go up
        }

        if (yPos + height / 2 < ballHeight and ballX <= screenWidth / 2) {

            yPos += ySpeed;
        }

        withinBounds();
    }
};


int main() {


    InitWindow(screenWidth, screenHeight, "Datastructures-1 Lab Ping Pong Project");
    SetTargetFPS(60);
    Ball ball;
    Paddle player;
    CPUPaddle CPU;

    while (WindowShouldClose() == false) {

        BeginDrawing();


        ClearBackground(DARKBLUE); // to prevent tracing of each draw we do

        string playerScore = to_string(playerScoreInt);
        string CPUScore = to_string(CPUScoreInt);


        DrawCircle(screenWidth / 2, screenHeight / 2, 125, LIGHTGRAY);
        DrawText("Score", screenWidth / 2 + 40, 25, 50, WHITE);
        DrawText(playerScore.c_str(), screenWidth / 2 + 100, 100, 50, WHITE);
        DrawText("Score", screenWidth / 2 - 200, 25, 50, RED);
        DrawText(CPUScore.c_str(), screenWidth / 2 - 125, 100, 50, RED);

        if (CheckCollisionCircleRec(Vector2{ ball.getX(), ball.getY() }, ball.getRad(), Rectangle{ player.xPos, player.yPos, player.width, player.height })) {

            ball.speedX *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ ball.getX(), ball.getY() }, ball.getRad(), Rectangle{ CPU.xPos, CPU.yPos, CPU.width, CPU.height })) {

            ball.speedX *= -1;
        }

        player.drawPaddle();
        CPU.drawCPU();
        player.updatePlayer();
        CPU.updateCPU(ball.getY(), ball.getX());
        ball.Update();
        DrawLine(screenWidth / 2, screenHeight, screenWidth / 2, 0, WHITE);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// WindowShouldClose, checks if the x icon is pressed or esc, signaling the end of the game.
// BeginDrawing begins the drawing process
// in draw rectangle, when centering it centers from the top left, corner of the rectangle, so to counter that, we subtract half of its height to center from the middle
// regarding the x and y axis, we want the paddle to be 10 pts away from the left or right of the window edge, that's why the first statement has 10, as the x axis, as in
// 10 away from the left corner, and has screenHeight / 2 as a y position, as in half of the resolution down - half of its height so it can be centered for the mid point of the rectangle
// in the second drawRectangle function, its x position is set to width - 45, why? so it can be in the right most corner, minus half of its width to account for edges, and - 10 pts to be aligned
// with the other rectangle, and the screenHeight/2 - half of height is for the same reason as the first one
// when it comes to draw line, we start its x position at half of the width, and its y position at the very top of screen, aka screenHeight, we end its x position at the same position it started,
// but we end its y position at 0, so it draws the line from top to bottom,
// line should be drawn before any other object.
// 0 is top of screen