#include "gui.hpp"
#include <vector>

Gui::Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode)
    :m_game(game), m_textcolor(Color::WHITE), m_score(0), m_frameWidth(0), m_frameHeight(0)
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
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }

    // Hier könntest du weitere Spiellogik aufrufen, z.B. game.update(faces);


    return faces;
}


// Zeichnet alle Bälle auf das übergebene Frame
void Gui::drawBalls(cv::Mat& frame, std::vector<Ball> balls) {
    if (frame.empty()) return;

    for (const auto& ball : balls) {
        cv::circle(frame, ball.position, static_cast<int>(ball.radius), ball.color, -1);
    }

    // Optional: weitere Spielfiguren, Score, etc. zeichnen
}

// Liest eine Taste von der Tastatur aus (z.B. für Steuerung oder Beenden)
int Gui::getKeybord() {
    // Gibt den ASCII-Code der gedrückten Taste zurück, -1 falls keine Taste gedrückt
    int key = cv::waitKey(10);
    return key;
}