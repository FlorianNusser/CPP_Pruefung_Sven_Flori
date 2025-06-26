#include "gui.hpp"

Gui::Gui(Color textcolor, const std::string& playername, Playmode playmode)
    :m_textcolor(textcolor), m_playername(playername), m_playmode(playmode), m_score(0) 
{
    // Initialize GUI components if needed
}

Gui::~Gui(){}

