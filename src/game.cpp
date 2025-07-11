#include "game.hpp"
#include "gui.hpp"
#include "gamemode.hpp"
#include "dodgeTheBalls.hpp"
#include "catchTheSquares.hpp"

#include <iostream>
#include <chrono> // for time control


Game::Game(const std::string& cascadePath, Playmode playmode, Player player) : m_playmode(playmode), m_dodgeTheBalls(640, 480),m_catchTheSquares(640, 480), m_gui(*this, cascadePath, playmode), m_player(player)
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
    m_catchTheSquares = CatchTheSquares(frameWidth, frameHeight);

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
    if (!initialize()) {
        std::cerr << "Initialization failed." << std::endl;
        return;
    }
    cv::Mat frame;
    int dodgeSpawnCounter = 0;
    int catchSpawnCounter = 0;
    const int DODGE_SPAWN_INTERVAL = 30; // 1 ball every 30 frames
    const int CATCH_SPAWN_INTERVAL = 45;
    bool gameOver = false;

    while (!gameOver)
    {
        //0. Frame holen
        cap >> frame;
        if (frame.empty())
        {
            std::cerr << "Frame is empty! Camera not delivering images." << std::endl;
            break;
        }
        cv::flip(frame, frame, 1);



        // 1. Frame und Gesichter aktualisieren & anzeigen
        std::vector<cv::Rect> faces = m_gui.updateFrame(frame);

        // 2.1 DodgeTheBalls Logik
        if(m_playmode == Playmode::DodgeTheBalls)
        {
            if (dodgeSpawnCounter % DODGE_SPAWN_INTERVAL == 0)
            {
                m_dodgeTheBalls.spawnBall();
            }
            dodgeSpawnCounter++;
            m_dodgeTheBalls.updateBalls();
            m_dodgeTheBalls.calcScore(m_score);
            m_dodgeTheBalls.removeOffscreenBalls();

            // 3. Bälle zeichnen (auf das aktuelle Frame)
            m_dodgeTheBalls.drawBalls(frame);


            //5. Kollisionserkennung (optional: Gesichter aus updateFrame an Game übergeben)
            //Beispiel: Du müsstest die erkannten Gesichter aus updateFrame() an Game übergeben oder dort speichern.
            //Hier als Platzhalter:
            for (const auto& face : faces)
            {
                if (m_dodgeTheBalls.checkCollision(face))
                {
                    gameOver = true;
                    // Optional: Game-Over-Anzeige in der GUI
                }
            }

        }
        else if (m_playmode == Playmode::CatchTheSquares) 
        {
            int amountToWin = 0;
            std::cout << "How many squares do you want to catch, meanwhile you dodge the balls?" << std::endl;
            std::cout << "Enter your desired amount:" << std::endl;
            std::cin >> amountToWin >> std::endl;
            
            if (catchSpawnCounter % CATCH_SPAWN_INTERVAL == 0)
            {
                m_catchTheSquares.spawnSquares();
            }
            if (dodgeSpawnCounter % DODGE_SPAWN_INTERVAL == 0)
            {
                m_dodgeTheBalls.spawnBall();
            }
            catchSpawnCounter++;
            m_catchTheSquares.updateSquares();
            m_catchTheSquares.drawSquares(frame);

            dodgeSpawnCounter++;
            m_dodgeTheBalls.updateBalls();
            m_dodgeTheBalls.removeOffscreenBalls();
            m_dodgeTheBalls.drawBalls(frame);

            for (const auto& face : faces)
            {
                if (m_catchTheSquares.checkCollision(face))
                {
                    m_score++;
                    std::cout << "Score: " << m_score << std::endl;
                }
                else if (m_dodgeTheBalls.checkCollision(face))
                {
                    gameOver = true;
                    // Optional: Game-Over-Anzeige in der GUI
                }
                m_catchTheSquares.removeCollidedSquares(face);
            }
            
            m_catchTheSquares.removeOffscreenSquares();
        }
        m_gui.showScore(frame, m_score);

        cv::imshow(windowName, frame);
        
        if (m_gui.getKeyboard() == 27) { // ESC
            break;
        }
    }

    // --- Game-Over-Bildschirm ---
    // Hier erzeugen wir einen frischen Frame (schwarz), zeigen ihn an und
    // warten in einer Schleife auf ESC.
    cv::Mat gameOverFrame(frame.size(), frame.type());
    while (true)
    {
        // Frame schwarz füllen und GameOver-UI rendern
        gameOverFrame.setTo(cv::Scalar::all(0));
        m_gui.showGameOver(gameOverFrame, m_score, m_player);

        // auf Bildschirm bringen
        cv::imshow(windowName, gameOverFrame);

        // Taste abfragen
        int key = m_gui.getKeyboard(); 
        if (key == 27)  // ESC
            break;
    }
}



void Game::startGame()
{
    std::cout << "Press Enter to start the game..." << std::endl;
    std::cin.ignore(); // Überspringt das vorherige Eingabezeichen
    std::cin.get(); // Warten auf Enter-Taste
    std::cout << "\n";
}

