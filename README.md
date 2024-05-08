# Ping Pong Game

## Introduction

This project is a simple implementation of the classic Ping Pong game using C++ and the Raylib library. It provides a fun and interactive gaming experience where players can compete against a CPU-controlled opponent.

## Features

- **Player vs. CPU Gameplay:** Enjoy challenging gameplay against an AI opponent.
- **Score Tracking:** Keep track of scores for both the player and CPU.
- **Collision Detection:** Simple collision detection ensures fair gameplay.
- **Basic AI:** The CPU-controlled opponent provides a reasonable challenge.
- **Adjustable Window Size:** Resize the game window to fit your preferences.

## Installation

To run this program, you'll need to have the Raylib library installed on your system. Follow these steps:

1. **Download and Install Raylib:** Download Raylib from [here](https://www.raylib.com/) and follow the installation instructions for your platform.
2. **Clone the Repository:** Clone this repository to your local machine using Git.
3. **Open in IDE:** Open the project in your preferred C++ Integrated Development Environment (IDE).
4. **Compile and Run:** Compile the source code and run the program.

## How to Play

1. **Launch the Game:** Start the game by executing the compiled executable.
2. **Control the Paddle:** Use the UP and DOWN arrow keys to control the player's paddle.
3. **Score Points:** Hit the ball past the opponent's paddle to score points.
4. **Winning:** The game continues until one player reaches a predefined score limit or until the player decides to quit.

## Controls

- **UP Arrow Key:** Move the player's paddle up.
- **DOWN Arrow Key:** Move the player's paddle down.

## Function Explanations

### Ball Class

- **getY():** Returns the current y-coordinate of the ball.
- **getX():** Returns the current x-coordinate of the ball.
- **getRad():** Returns the radius of the ball.
- **resetBall():** Resets the position of the ball and changes its direction.
- **Update():** Updates the position of the ball and handles collisions with walls and paddles.

### Paddle Class

- **drawPaddle():** Draws the paddle on the screen.
- **updatePlayer():** Updates the position of the player's paddle based on user input.

### CPUPaddle Class

- **drawCPU():** Draws the CPU-controlled paddle on the screen.
- **withinBounds():** Ensures that the CPU paddle stays within the screen boundaries.
- **updateCPU(float ballHeight, float ballX):** Updates the position of the CPU paddle based on the position of the ball.

## Contributing

Contributions to this project are welcome! If you find any bugs, have ideas for improvements, or want to add new features, feel free to submit a pull request or open an issue.

