#include "gui.hpp"

Gui::Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode)
    :m_textcolor(Color::White), m_score(0), m_frameWidth(0), m_frameHeight(0)
{
    // Lädt "facaCascade" und überprüft, ob es erfolgreich war
    if (!faceCascade.load(m_cascadeFilePath))
    {
        std::cerr << "Error loading cascade file!" << std::endl;
    }
    //std::cout << "Gui Constructor called." << std::endl;
}

Gui::~Gui(){
    if (cap.isOpened())
    {
        cap.release();
    }
    cv::destroyAllWindows();
}

bool Gui::initialize() {
    cap.open(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open camera." << std::endl;
        return false;
    }

    m_frameWidth = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    m_frameHeight = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    if (m_frameWidth == 0 || m_frameHeight == 0) {
        m_frameWidth = 640;
        m_frameHeight = 480;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, m_frameWidth);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, m_frameHeight);
    }

    if (faceCascade.empty())
    {
        std::cerr << "Error: Could not load Haar cascade file." << std::endl;
        return false;
    }

    cv::namedWindow(m_windowName, cv::WINDOW_AUTOSIZE);
    return true;
}

std::string Gui::getCascadeFilePath() const
{
    return m_cascadeFilePath;
}