#include "game.hpp"
#include "gui.hpp"
#include "gamemode.hpp"
#include "dodgeTheBalls.hpp"
#include "catchTheSquares.hpp"
#include "dodgeTheBallsMode.hpp"
#include "catchTheSquaresMode.hpp"
#include "constants.hpp"


#include <iostream>
#include <chrono> // for time control


Game::Game(const std::string& cascadePath, Playmode playmode, Player player) : m_playmode(playmode), m_dodgeTheBalls(m_frameWidth, m_frameHeight, playmode),m_catchTheSquares(m_frameWidth, m_frameHeight), m_gui(*this, cascadePath, playmode), m_player(player)

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
    cap.set(cv::CAP_PROP_FRAME_WIDTH,  Constants::FRAME_WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, Constants::FRAME_HEIGHT);

    m_frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    m_frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    // hier den neuen Mode vorbereiten
    switch(m_playmode)
    {
        case Playmode::DodgeTheBalls:
            m_gameMode = std::make_unique<DodgeTheBallsMode>();
            break;
        case Playmode::CatchTheSquares:
            m_gameMode = std::make_unique<CatchTheSquaresMode>();
            break;
    }
    m_gameMode->initialize(m_frameWidth, m_frameHeight);

    if (faceCascade.empty())
    {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }
    cv::namedWindow(Constants::WINDOW_NAME, cv::WINDOW_NORMAL);
    cv::setWindowProperty(Constants::WINDOW_NAME, cv::WND_PROP_FULLSCREEN, 0);
    cv::resizeWindow(Constants::WINDOW_NAME, Constants::FRAME_WIDTH, Constants::FRAME_HEIGHT);
    cv::moveWindow(Constants::WINDOW_NAME, 100, 100);
    return true;
}

void Game::run()
{
    if (!initialize()) {
        std::cerr << "Initialization failed." << std::endl;
        return;
    }
    cv::Mat frame;
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
        // *** Neuer Polymorpher Modus-Aufruf ***
        m_gameMode->spawnShape();                         // Ball spawnen
        m_gameMode->update();                      // Position updaten & Score
        m_gameMode->handleCollisions(faces, gameOver);
        m_gameMode->draw(frame);                          // Bälle zeichnen

        // Check if game is over
        if (m_gameMode->isGameOver()) 
        {
            gameOver = true;
        }
        m_gui.showScore(frame, m_gameMode->getScore());

        cv::imshow(Constants::WINDOW_NAME, frame);
        if (m_gui.getKeyboard() == 27) { // ESC
            break;
        }
    }
    //Leaderboard Eintrag hinzufügen
    std::string leaderboardFile;
    if (m_playmode == Playmode::DodgeTheBalls)
    {
        leaderboardFile = "../leaderboardDodgeTheBalls.txt";
    }
    else
    {
        leaderboardFile = "../leaderboardCatchTheSquares.txt";
    }

    Leaderboard lb(leaderboardFile);
    lb.load();
    lb.addScoreFromGameMode(*m_gameMode, m_player);

    // --- Game-Over-Bildschirm ---
    cv::Mat gameOverFrame(frame.size(), frame.type());
    while (true)
    {
        // Frame schwarz füllen und GameOver-UI rendern
        gameOverFrame.setTo(cv::Scalar::all(0));
        m_gui.showGameOver(gameOverFrame, m_gameMode->getScore(), m_player);

        // auf Bildschirm bringen
        cv::imshow(Constants::WINDOW_NAME, gameOverFrame);

        // Taste abfragen
        int key = m_gui.getKeyboard(); 
        if (key == 27)  // ESC
        {    
            break;
        }
        else if (key == 'l' || key == 'L')  // L für Leaderboard
        {
            // Leaderboard anzeigen
            cv::Mat lbFrame(frame.size(), frame.type());
            while (true)
            {
                lbFrame.setTo(cv::Scalar::all(0));
                m_gui.showLeaderboard(lbFrame);
                cv::imshow(Constants::WINDOW_NAME, lbFrame);
            
                int lbKey = m_gui.getKeyboard();
                if (lbKey == 27)  // ESC zurück zum GameOver
                {
                    break;
                }
            }
        }
    }
}



void Game::startGame()
{
    std::cout << "Press Enter to start the game..." << std::endl;
    std::cin.ignore(); // Überspringt das vorherige Eingabezeichen
    std::cin.get(); // Warten auf Enter-Taste
    std::cout << "\n";
}

