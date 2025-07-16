#include <gtest/gtest.h>
#include "player.hpp"
#include "shape.hpp"
#include "ball.hpp"
#include "square.hpp"
#include "catchTheSquares.hpp"
#include "dodgeTheBalls.hpp"
#include "game.hpp"
#include "menu.hpp"
#include "gamemode.hpp"
#include "dodgeTheBallsMode.hpp"
#include "catchTheSquaresMode.hpp"
#include "gui.hpp"
#include "randomGenerator.hpp"

TEST(RandomGeneratorTest, GeneratorInstance) {
    std::mt19937& gen1 = RandomGenerator::getGenerator();
    std::mt19937& gen2 = RandomGenerator::getGenerator();
    
    EXPECT_EQ(&gen1, &gen2); // Sollte dieselbe Instanz zurückgeben
}

TEST(RandomGeneratorTest, Distribution) {
    std::uniform_int_distribution<int> dist(1, 10);
    int value = dist(RandomGenerator::getGenerator());
    
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 10);
}

TEST(ColorTest, ColorToScalar) {
    EXPECT_EQ(getScalarFromColor(Color::RED), cv::Scalar(0, 0, 255));
    EXPECT_EQ(getScalarFromColor(Color::GREEN), cv::Scalar(0, 255, 0));
    EXPECT_EQ(getScalarFromColor(Color::BLUE), cv::Scalar(255, 0, 0));
    EXPECT_EQ(getScalarFromColor(Color::YELLOW), cv::Scalar(0, 255, 255));
    
    // Test für unbekannte Farbe
    EXPECT_THROW(getScalarFromColor(static_cast<Color>(99)), std::invalid_argument);
}

TEST(DodgeTheBallsTest, CollisionDetection) {
    DodgeTheBalls logic(640, 480);

    // Ball erstellen und hinzufügen
    logic.spawnBall();

    // Spieler-Rect das kollidiert
    cv::Rect playerRect(90, 90, 30, 30);
    EXPECT_TRUE(logic.checkCollision(playerRect));

    // Spieler-Rect ohne Kollision
    cv::Rect safeRect(200, 200, 30, 30);
    EXPECT_FALSE(logic.checkCollision(safeRect));
}

TEST(CatchTheSquaresTest, CollisionDetection) {
    CatchTheSquares logic(640, 480);

    // Quadrat erstellen und hinzufügen
    logic.spawnSquares(); // Verwende die vorhandene Methode

    // Spieler-Rect das kollidiert
    cv::Rect playerRect(110, 110, 20, 20);
    EXPECT_TRUE(logic.checkCollision(playerRect));

    // Spieler-Rect ohne Kollision
    cv::Rect safeRect(200, 200, 20, 20);
    EXPECT_FALSE(logic.checkCollision(safeRect));
}