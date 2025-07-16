#ifndef LEADERBOARD_HPP
#define LEADERBOARD_HPP

class GameModeInterface;
class Player;


#include <string>
#include <vector>

struct LeaderboardEntry {
    int playerId;
    std::string playerName;
    int score;
    int userLimit; // 0 für DodgeTheBalls, >0 für CatchTheSquares
};

class Leaderboard {
public:
    Leaderboard(const std::string& filename);

    void load();
    void save();
    void addEntry(const LeaderboardEntry& entry);
    void addScoreFromGameMode(const GameModeInterface& mode, Player& player);

    std::vector<LeaderboardEntry> getSortedEntriesDodgeTheBalls() const;
    std::vector<LeaderboardEntry> getSortedEntriesCatchTheSquares() const;

private:
    std::string m_filename;
    std::vector<LeaderboardEntry> m_entries;
};

#endif // LEADERBOARD_HPP