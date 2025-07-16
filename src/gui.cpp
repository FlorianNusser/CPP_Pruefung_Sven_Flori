#include "gui.hpp"
#include "constants.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

Gui::Gui(Game& game, const std::string& cascadeFilePath, Playmode playmode)
    :m_game(game), m_textcolor(Color::WHITE), m_frameWidth(0), m_frameHeight(0), m_playmode(playmode)
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

std::vector<std::vector<std::string>> Gui::parseLeaderboardFile(const std::string& filename, Playmode mode)
{
    std::vector<std::vector<std::string>> entries;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open leaderboard file: " << filename << "\n";
        return entries;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string tok;
        // Spalte nach ';'
        while (std::getline(ss, tok, ';')) {
            tokens.push_back(tok);
        }
        // CatchTheSquares hat 4 Tokens, DodgeTheBalls 3
        if ((mode == Playmode::CatchTheSquares && tokens.size() == 4) ||
            (mode == Playmode::DodgeTheBalls    && tokens.size() == 3))
        {
            entries.push_back(tokens);
        }
    }
    return entries;
}

void Gui::showLeaderboard(cv::Mat& frame)
{
    // 1) Datei auswählen
    const std::string filename = (m_playmode == Playmode::CatchTheSquares)
        ? "../leaderBoardCatchTheSquares.txt"
        : "../leaderBoardDodgeTheBalls.txt";

    // 2) Einträge einlesen
    auto entries = parseLeaderboardFile(filename, m_playmode);

    // 3) Optional: Sortieren nach Score (Token[2]) absteigend
    std::sort(entries.begin(), entries.end(),
        [](auto& a, auto& b) {
            return std::stoi(a[2]) > std::stoi(b[2]);
        });

    // 4) Grafik: Überschrift
    const int fontFace    = cv::FONT_HERSHEY_DUPLEX;
    const double scale    = 1.2;
    const int thickness   = 2;
    const cv::Scalar color = getScalarFromColor(Color::WHITE);

    std::string title = "Leaderboard";
    cv::Size  sz    = cv::getTextSize(title, fontFace, scale, thickness, nullptr);
    cv::Point org  = { (frame.cols - sz.width) / 2, 50 };
    cv::putText(frame, title, org, fontFace, scale, color, thickness);

    // 5) Tabellen-Kopf
    int startY      = org.y + 40;
    int lineHeight  = 30;
    int colIdX      = 50;
    int colNameX    = 120;
    int colScoreX   = 350;
    int colExtraX   = 480; // für gefallene Objekte

    cv::putText(frame, "ID",    {colIdX,   startY},    fontFace, 1.0, color, 2);
    cv::putText(frame, "Name",  {colNameX, startY},    fontFace, 1.0, color, 2);
    cv::putText(frame, "Score", {colScoreX,startY},    fontFace, 1.0, color, 2);
    if (m_playmode == Playmode::CatchTheSquares) {
        cv::putText(frame, "Fallen", {colExtraX, startY}, fontFace, 1.0, color, 2);
    }

    // 6) Top 10 Zeilen
    for (size_t i = 0; i < entries.size() && i < 10; ++i) {
        int y = startY + lineHeight * (int(i) + 1);
        auto& row = entries[i];

        // row[0] = ID, row[1] = Name, row[2] = Score, row[3] optional Objects
        cv::putText(frame, row[0], {colIdX,   y}, fontFace, 0.8, color, 2);
        cv::putText(frame, row[1], {colNameX, y}, fontFace, 0.8, color, 2);
        cv::putText(frame, row[2], {colScoreX,y}, fontFace, 0.8, color, 2);
        if (m_playmode == Playmode::CatchTheSquares) {
            cv::putText(frame, row[3], {colExtraX, y}, fontFace, 0.8, color, 2);
        }
    }
}

