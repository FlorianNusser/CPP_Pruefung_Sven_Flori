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

TEST(RandomGeneratorTest, GeneratorInstance)
{
    std::mt19937& gen1 = RandomGenerator::getGenerator();
    std::mt19937& gen2 = RandomGenerator::getGenerator();
    
    EXPECT_EQ(&gen1, &gen2); // Should return the same instance
}

TEST(RandomGeneratorTest, Distribution)
{
    std::uniform_int_distribution<int> dist(1, 10);
    int value = dist(RandomGenerator::getGenerator());
    
    EXPECT_GE(value, 1);
    EXPECT_LE(value, 10);
}

TEST(ColorTest, ColorToScalar)
{
    EXPECT_EQ(getScalarFromColor(Color::RED), cv::Scalar(0, 0, 255));
    EXPECT_EQ(getScalarFromColor(Color::GREEN), cv::Scalar(0, 255, 0));
    EXPECT_EQ(getScalarFromColor(Color::BLUE), cv::Scalar(255, 0, 0));
    EXPECT_EQ(getScalarFromColor(Color::YELLOW), cv::Scalar(0, 255, 255));
    
    // Test for unknown color
    EXPECT_THROW(getScalarFromColor(static_cast<Color>(99)), std::invalid_argument);
}

TEST(DodgeTheBallsTest, CollisionDetection)
{
    DodgeTheBalls logic(640, 480, Playmode::DodgeTheBalls);
    
    // Test-Ball mit bekannter Position hinzufügen
    auto ball = std::make_shared<Ball>(cv::Point2f(100, 100), Color::RED, 0, 15);
    const_cast<std::vector<std::shared_ptr<Ball>>&>(logic.getBalls()).push_back(ball);

    // Rechteck das kollidieren sollte (überlappt mit Ball bei 100,100 mit Radius 15)
    cv::Rect collidingRect(95, 95, 30, 30);
    EXPECT_TRUE(logic.checkCollision(collidingRect));

    // Rechteck das nicht kollidieren sollte
    cv::Rect safeRect(200, 200, 30, 30);
    EXPECT_FALSE(logic.checkCollision(safeRect));
}


TEST(CatchTheSquaresTest, CollisionDetection)
{
    CatchTheSquares logic(640, 480);
    
    // Temporarily remove const (only for tests)
    const_cast<std::vector<std::shared_ptr<Square>>&>(logic.getSquares()).push_back(
        std::make_shared<Square>(cv::Point2f(100, 100), Color::GREEN, 0, 20)
    );

    cv::Rect collidingRect(90, 90, 30, 30);
    EXPECT_TRUE(logic.checkCollision(collidingRect));

    cv::Rect safeRect(200, 200, 30, 30);
    EXPECT_FALSE(logic.checkCollision(safeRect));
}

TEST(BallTest, ConstructorAndGetters)
{
    Ball ball(cv::Point2f(100, 150), Color::BLUE, 5, 15);
    EXPECT_EQ(ball.getPosition(), cv::Point2f(100, 150));
    EXPECT_EQ(ball.getColor(), Color::BLUE);
    EXPECT_EQ(ball.getVelocityY(), 5);
    EXPECT_EQ(ball.getRadius(), 15);
}

TEST(SquareTest, ConstructorAndGetters)
{
    Square square(cv::Point2f(200, 250), Color::GREEN, 3, 25);
    EXPECT_EQ(square.getPosition(), cv::Point2f(200, 250));
    EXPECT_EQ(square.getColor(), Color::GREEN);
    EXPECT_EQ(square.getVelocityY(), 3);
    EXPECT_EQ(square.getSidelength(), 25);
    
    cv::Rect expectedRect(200, 250, 25, 25);
    EXPECT_EQ(square.getRect(), expectedRect);
}

TEST(DodgeTheBallsModeTest, Initialization)
{
    DodgeTheBallsMode mode;
    mode.initialize(800, 600);
    EXPECT_EQ(mode.getSpawnedShapes(), 0);
    EXPECT_EQ(mode.getActiveShapes(), 0);
    EXPECT_EQ(mode.getScore(), 0);
    EXPECT_FALSE(mode.isGameOver());
}

TEST(CatchTheSquaresModeTest, Initialization)
{
    CatchTheSquaresMode mode;
    mode.initialize(800, 600);
    EXPECT_EQ(mode.getSpawnedShapes(), 0);
    EXPECT_EQ(mode.getActiveShapes(), 0);
    EXPECT_EQ(mode.getScore(), 0);
    EXPECT_FALSE(mode.isGameOver());
}

TEST(MenuTest, PlayerNameInput)
{
    Menu menu;
    
    // Simulate input
    std::istringstream input("John\n");
    std::streambuf* origCin = std::cin.rdbuf(input.rdbuf());
    
    Player p = menu.namePlayer();
    std::cin.rdbuf(origCin); // Reset
    
    EXPECT_EQ(p.getPlayername(), "John");
}

TEST(MenuTest, GameModeSelection)
{
    Menu menu;
    
    // Simulate input for DodgeTheBalls
    std::istringstream input1("1\n");
    std::streambuf* origCin = std::cin.rdbuf(input1.rdbuf());
    
    Playmode mode1 = menu.selectGamemode();
    std::cin.rdbuf(origCin);
    EXPECT_EQ(mode1, Playmode::DodgeTheBalls);
    
    // Simulate input for CatchTheSquares
    std::istringstream input2("2\n");
    origCin = std::cin.rdbuf(input2.rdbuf());
    
    Playmode mode2 = menu.selectGamemode();
    std::cin.rdbuf(origCin);
    EXPECT_EQ(mode2, Playmode::CatchTheSquares);
}

TEST(ShapeTest, BaseFunctionality)
{
    // Concrete class for testing
    class TestShape : public Shape
    {
    public:
        TestShape() : Shape(cv::Point2f(50, 60), Color::RED, 5) {}
    };
    
    TestShape shape;
    EXPECT_EQ(shape.getPosition(), cv::Point2f(50, 60));
    EXPECT_EQ(shape.getColor(), Color::RED);
    EXPECT_EQ(shape.getVelocityY(), 5);
    
    shape.setPosition(cv::Point2f(70, 80));
    EXPECT_EQ(shape.getPosition(), cv::Point2f(70, 80));
}