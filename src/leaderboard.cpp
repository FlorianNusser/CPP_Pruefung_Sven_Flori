#include "leaderboard.hpp"
#include "leaderboard.hpp"
#include "gameModeInterface.hpp"
#include "player.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>

Leaderboard::Leaderboard(const std::string& filename) : m_filename(filename) 
{
}

void Leaderboard::load() 
{
    m_entries.clear();
    std::ifstream file(m_filename);
    std::string line;
    while (std::getline(file, line)) 
    {
        std::istringstream iss(line);
        LeaderboardEntry entry;
        std::string token;
        std::getline(iss, token, ';'); entry.playerId = std::stoi(token);
        std::getline(iss, entry.playerName, ';');
        std::getline(iss, token, ';'); entry.score = std::stoi(token);
        if (std::getline(iss, token, ';')) entry.userLimit = std::stoi(token);
        else entry.userLimit = 0;
        m_entries.push_back(entry);
    }
}

void Leaderboard::save() 
{
    std::ofstream file(m_filename, std::ios::trunc);
    if (!file) 
    {
        std::cerr << "Konnte Leaderboard-Datei nicht öffnen: " << m_filename << std::endl;
        return;
    }
    for (const auto& entry : m_entries) 
    {
        file << entry.playerId << ";" << entry.playerName << ";" << entry.score;
        if (entry.userLimit > 0)
            file << ";" << entry.userLimit;
        file << "\n";
    }
}

void Leaderboard::addEntry(const LeaderboardEntry& entry) 
{
    m_entries.push_back(entry);
    // sort after score or ratio
    if (entry.userLimit > 0) 
    {
        std::sort(m_entries.begin(), m_entries.end(),
            [](const LeaderboardEntry& a, const LeaderboardEntry& b) 
            {
                double ratioA = a.userLimit > 0 ? (double)a.score / a.userLimit : 0.0;
                double ratioB = b.userLimit > 0 ? (double)b.score / b.userLimit : 0.0;
                return ratioA > ratioB;
            });
    } else 
    {
        std::sort(m_entries.begin(), m_entries.end(),
            [](const LeaderboardEntry& a, const LeaderboardEntry& b) 
            {
                return a.score > b.score;
            });
    }
    save();
}

std::vector<LeaderboardEntry> Leaderboard::getSortedEntriesDodgeTheBalls() const 
{
    std::vector<LeaderboardEntry> result;
    for (const auto& entry : m_entries)
        if (entry.userLimit == 0) result.push_back(entry);
    std::sort(result.begin(), result.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) 
        {
            return a.score > b.score;
        });
    return result;
}

std::vector<LeaderboardEntry> Leaderboard::getSortedEntriesCatchTheSquares() const 
{
    std::vector<LeaderboardEntry> result;
    for (const auto& entry : m_entries)
        if (entry.userLimit > 0) result.push_back(entry);
    std::sort(result.begin(), result.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) 
        {
            double ratioA = (double)a.score / a.userLimit;
            double ratioB = (double)b.score / b.userLimit;
            return ratioA > ratioB;
        });
    return result;
}

void Leaderboard::addScoreFromGameMode(const GameModeInterface& mode, Player& player) 
{
    LeaderboardEntry entry = mode.getLeaderboardEntry(player, mode.getScore());
    addEntry(entry);
}