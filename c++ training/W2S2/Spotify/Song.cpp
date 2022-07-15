#include "Song.h"
#include <string>

Song::Song()
{
	m_songTitle = "Jingle Bells";
	m_artistName = "Frank Sinatra";
	m_duration = 125;
}

Song::Song(std::string songTitle, std::string artistName, int duration)
{
	setSongTitle(songTitle);
	setArtistName(artistName);
	setDuration(duration);
}

std::string Song::getSongTitle() const
{
	return m_songTitle;
}

std::string Song::getArtistName() const
{
	return m_artistName;
}

int Song::getDuration() const
{
	return m_duration;
}

void Song::setSongTitle(std::string songTitle)
{
	m_songTitle = songTitle;
}

void Song::setArtistName(std::string artistName)
{
	m_artistName = artistName;
}

void Song::setDuration(int duration)
{
	m_duration = duration;
}

std::string Song::getFormattedDuration() const
{
	std::string formattedString = "";
	int seconds = m_duration % 60;
	int minutes = (m_duration - seconds) / 60;
	if (minutes < 10) formattedString += '0';
	formattedString += std::to_string(minutes) + ":";
	if (seconds < 10) formattedString += '0';
	formattedString += std::to_string(seconds);
	return formattedString;
}

bool Song::isValid() const
{
	return (m_duration>0 && !empty(m_artistName) && !empty(m_songTitle));
}



