#include "game.hpp"
#include <iostream>

Game::Game(const std::string& cascadePath) : m_dodgeTheBalls(640, 480) { // Initialisiere DodgeTheBalls mit Standardgröße
    faceCascade.load(cascadePath);
}

Game::~Game() {
    if (cap.isOpened()) {
        cap.release();
    }
    cv::destroyAllWindows();
}

bool Game::initialize() {
    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera." << std::endl;
        return false;
    }
    frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    if (frameWidth == 0 || frameHeight == 0) {
        frameWidth = 640;
        frameHeight = 480;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, frameWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, frameHeight);
    }
    if (faceCascade.empty()) {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

void Game::run() {
    if (!initialize()) return;
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::flip(frame, frame, 1);
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }
        cv::imshow(windowName, frame);
        int key = cv::waitKey(10);
        if (key == 27) break; // ESC to exit

        //Dodge the Balls Game Logic
        m_dodgeTheBalls.spawnBall();
        m_dodgeTheBalls.updateBalls();
        m_dodgeTheBalls.drawBalls(frame);
        m_dodgeTheBalls.removeOffscreenBalls();

        // Check for collisions with player rectangle (example, you need to define playerRect)
        /*if (m_dodgeTheBalls.checkCollision(cv::Rect(100, 100, 50, 50))) {
            std::cout << "Collision detected!" << std::endl;
            // Handle collision (e.g., game over or score deduction)
        }*/
    }
}
