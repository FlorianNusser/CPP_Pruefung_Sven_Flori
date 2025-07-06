#include "game.hpp"
#include "gui.hpp"
#include "dodgeTheBalls.hpp"

#include <iostream>
#include <chrono> // for time control


Game::Game(const std::string& cascadePath) : m_dodgeTheBalls(640, 480) 
{
    if (!faceCascade.load(cascadePath))
    {
        std::cerr << "Error loading cascade file!" << std::endl;
    }
}

Game::~Game()
{
    if (cap.isOpened())
    {
        cap.release();
    }
    cv::destroyAllWindows();
}

bool Game::initialize() {
    cap.open(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open camera." << std::endl;
        return false;
    }

    frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    
    // make sure, that DodgeTheBalls has the right size
    m_dodgeTheBalls = DodgeTheBalls(frameWidth, frameHeight);

    if (faceCascade.empty()) 
    {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

void Game::run()
{

    if (!initialize())
    {
        std::cerr << "Initialization failed." << std::endl;
        return;
    }

    cv::Mat frame;
    int spawnCounter = 0;
    const int SPAWN_INTERVAL = 30; // 1 ball all 30 frames
    bool gameOver = false;

    while (!gameOver)
    {
        cap >> frame;
        if (frame.empty()) break;

        cv::flip(frame, frame, 1);

        // face detection
        std::vector<cv::Rect> faces;
        faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

        // ball-logic
        if (spawnCounter % SPAWN_INTERVAL == 0) 
        {
            m_dodgeTheBalls.spawnBall();
        }
        spawnCounter++;

        m_dodgeTheBalls.updateBalls();
        m_dodgeTheBalls.drawBalls(frame);
        m_dodgeTheBalls.removeOffscreenBalls();

        // Collision check for all faces
        for (const auto& face : faces) 
        {
            if (m_dodgeTheBalls.checkCollision(face)) 
            {
                gameOver = true;
                cv::putText(frame, "GAME OVER!", cv::Point(100, 200),
                          cv::FONT_HERSHEY_SIMPLEX, 2, cv::Scalar(0, 0, 255), 3);
                cv::imshow(windowName, frame);
                cv::waitKey(2000);
                break;
            }
        }

        for (const auto& face : faces) 
        {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow(windowName, frame);
        int key = cv::waitKey(10);
        if (key == 27) break; // ESC to exit
    }
}

