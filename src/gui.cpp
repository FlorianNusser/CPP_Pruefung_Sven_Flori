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
    faceCascade.detectMultiScale(frame, faces, GuiConstants::FACE_DETECT_SCALE, GuiConstants::FACE_DETECT_NEIGHBORS, GuiConstants::FACE_DETECT_FLAGS, cv::Size(60, 60));
    //Falls kein neues Gesicht erkannt wird, wird das letzte erkannte Gesicht verwendet
    if (faces.empty()) {
        faces = m_lastFaces;
    }
    else {
        m_lastFaces = faces;    // Sonst letztes Ergebnis updaten
    }

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
            cv::Point(GuiConstants::SCORE_X_COORDINATE, GuiConstants::SCORE_Y_COORDINATE),
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            getScalarFromColor(Color::WHITE),
            2);
}


void Gui::showGameOver(cv::Mat &frame, int score, Player player)
{
    // 1. Hintergrund schwarz füllen
    frame.setTo(getScalarFromColor(Color::BLACK));

    // 2. Schriftparameter
    int fontFace       = GuiConstants::FONT_FACE;
    double titleScale  = GuiConstants::GO_TITLE_SCALE;
    double textScale   = GuiConstants::GO_TEXT_SCALE;
    int   thickness    = GuiConstants::GO_THICKNESS;
    int   baseline     = GuiConstants::GO_BASELINE;
    cv::Scalar red     = getScalarFromColor(Color::RED);
    int   paddingTop   = GuiConstants::GO_PADDING_TOP;
    int   lineSpacing  = GuiConstants::GO_LINE_SPACING;

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

    // 1) Escape-Button unten rechts
    drawButton(frame, GuiConstants::BTN_ESC_TEXT, Anchor::BottomRight);

    // 2) Leaderboard-Button unten links
    drawButton(frame, GuiConstants::BTN_LB_TEXT, Anchor::BottomLeft);
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
        ? "../leaderboardCatchTheSquares.txt"
        : "../leaderboardDodgeTheBalls.txt";

    // 2) Einträge einlesen
    auto entries = parseLeaderboardFile(filename, m_playmode);

    // 3) Optional: Sortieren nach Score (Token[2]) absteigend
    std::sort(entries.begin(), entries.end(),
        [](auto& a, auto& b) {
            return std::stoi(a[2]) > std::stoi(b[2]);
        });

    // 4) Grafik: Überschrift
    const int fontFace    = GuiConstants::FONT_FACE;
    const double scale    = GuiConstants::LB_TITLE_SCALE;
    const int thickness   = GuiConstants::GO_THICKNESS;
    const cv::Scalar color = getScalarFromColor(Color::WHITE);

    std::string title = "Leaderboard";
    cv::Size  sz    = cv::getTextSize(title, fontFace, scale, thickness, nullptr);
    cv::Point org  = { (frame.cols - sz.width) / 2, GuiConstants::LB_TITLE_Y };
    cv::putText(frame, title, org, fontFace, scale, color, thickness);

    // 5) Tabellen-Kopf
    int startY      = org.y + 40;
    int lineHeight  = GuiConstants::LB_LINE_HEIGHT;
    int colIdX      = GuiConstants::LB_COL_ID_X;
    int colNameX    = GuiConstants::LB_COL_NAME_X;
    int colScoreX   = GuiConstants::LB_COL_SCORE_X;
    int colExtraX   = GuiConstants::LB_COL_EXTRA_X; // für gefallene Objekte

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

void Gui::drawButton(cv::Mat& frame, const std::string& text, Anchor anchor)
{
    int baseline = 0;

    // Text-Größe ermitteln
    cv::Size sz = cv::getTextSize(
        text,
        GuiConstants::FONT_FACE,
        GuiConstants::BTN_FONT_SCALE,
        GuiConstants::BTN_THICKNESS,
        &baseline
    );

    // Text-Position abhängig vom Anchor
    int x = (anchor == Anchor::BottomLeft)
            ? GuiConstants::BTN_MARGIN
            : frame.cols - sz.width - GuiConstants::BTN_MARGIN;
    int y = frame.rows - GuiConstants::BTN_MARGIN;
    cv::Point txtOrg(x, y);

    // Eckpunkte des Button-Rechtecks
    cv::Point rectTL(x - GuiConstants::BTN_PAD_X, y - sz.height - GuiConstants::BTN_PAD_Y);
    cv::Point rectBR(x + sz.width + GuiConstants::BTN_PAD_X, y + GuiConstants::BTN_PAD_Y);

    // Hintergrund
    cv::rectangle(frame, rectTL, rectBR, GuiConstants::BTN_BG_COLOR, cv::FILLED);

    // Text
    cv::putText(
        frame,
        text,
        txtOrg,
        GuiConstants::FONT_FACE,
        GuiConstants::BTN_FONT_SCALE,
        GuiConstants::BTN_TEXT_COLOR,
        GuiConstants::BTN_THICKNESS
    );
}