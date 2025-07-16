#include "gui.hpp"
#include "constants.hpp"
#include <vector>

Gui::Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode)
    :m_game(game), m_textcolor(Color::WHITE), m_frameWidth(0), m_frameHeight(0)
{
    // Lädt "facaCascade" und überprüft, ob es erfolgreich war
    if (!faceCascade.load(cascadeFilePath))
    {
        std::cerr << "Error loading cascade file!" << std::endl;
    }
    //std::cout << "Gui Constructor called." << std::endl;
}

Gui::~Gui()
{

}



// Aktualisiert das aktuelle Kamerabild und erkennt Gesichter
std::vector<cv::Rect> Gui::updateFrame(cv::Mat& frame) {
    if (frame.empty()) return {};


    // Gesichtserkennung (kann für Spielerrechteck genutzt werden)
    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(frame, faces, 1.1, 3, 0, cv::Size(60, 60));

    // Zeichne erkannte Gesichter
    for (const auto& face : faces) {
        cv::rectangle(frame, face, getScalarFromColor(Color::GREEN), 2);
    }

    return faces;
}



// Liest eine Taste von der Tastatur aus (z.B. für Steuerung oder Beenden)
int Gui::getKeyboard() {
    // Gibt den ASCII-Code der gedrückten Taste zurück, -1 falls keine Taste gedrückt
    int key = cv::waitKey(10);
    return key;
}

void Gui::showScore(cv::Mat &frame, int score)
{
    std::string scoreText = "Score: " + std::to_string(score);
    cv::putText(frame,
            scoreText,
            cv::Point(Constants::SCORE_X_COORDINATE, Constants::SCORE_Y_COORDINATE),
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            getScalarFromColor(Color::WHITE),
            2);
}


void Gui::showGameOver(cv::Mat &frame, int score, Player player)
{
    // 1. Hintergrund schwarz füllen
    frame.setTo(cv::Scalar(0, 0, 0));

    // 2. Schriftparameter
    int fontFace       = cv::FONT_HERSHEY_DUPLEX;
    double titleScale  = 2.0;
    double textScale   = 1.0;
    int   thickness    = 2;
    int   baseline     = 0;
    cv::Scalar red     = cv::Scalar(0, 0, 255);
    int   paddingTop   = 50;
    int   lineSpacing  = 20;

    // 3. „Game Over“ ganz oben zentriert
    std::string title = "Game Over";
    cv::Size   sz    = cv::getTextSize(title, fontFace, titleScale, thickness, &baseline);
    cv::Point  org   = cv::Point((frame.cols - sz.width) / 2,
                                  paddingTop + sz.height);
    cv::putText(frame, title, org, fontFace, titleScale, red, thickness);

    // 4. Score darunter
    std::string scoreText = "Score: " + std::to_string(score);
    sz  = cv::getTextSize(scoreText, fontFace, textScale, thickness, &baseline);
    org = cv::Point((frame.cols - sz.width) / 2,
                    org.y + lineSpacing + sz.height);
    cv::putText(frame, scoreText, org, fontFace, textScale, red, thickness);

    // 5. Spielernamen darunter
    std::string nameText = player.getPlayername();
    sz  = cv::getTextSize(nameText, fontFace, textScale, thickness, &baseline);
    org = cv::Point((frame.cols - sz.width) / 2,
                    org.y + lineSpacing + sz.height);
    cv::putText(frame, nameText, org, fontFace, textScale, red, thickness);

    // 6. Escape-Button unten rechts
    std::string escText    = "Esc: Beenden";
    int         btnFace    = cv::FONT_HERSHEY_SIMPLEX;
    double      btnScale   = 0.8;
    int         btnThick   = 2;
    int         margin     = 20;

    sz  = cv::getTextSize(escText, btnFace, btnScale, btnThick, &baseline);
    cv::Point txtOrg(frame.cols - sz.width - margin,
                     frame.rows - margin);
    cv::Point rectTL(txtOrg.x - 10,         txtOrg.y - sz.height - 5);
    cv::Point rectBR(txtOrg.x + sz.width + 10, txtOrg.y + 5);

    // weiße Button-Hintergrundfläche
    cv::rectangle(frame, rectTL, rectBR, cv::Scalar(255,255,255), cv::FILLED);

    // schwarzer Button-Text
    cv::putText(frame, escText, txtOrg, btnFace, btnScale, cv::Scalar(0,0,0), btnThick);
}