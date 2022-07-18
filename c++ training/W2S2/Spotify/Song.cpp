#include "Song.h"
#include <string>

Song::Song()
{
	m_songTitle = "";
	m_artistName = "";
	m_duration = 0;
}

Song::Song(const std::string songTitle, const std::string artistName, const int duration)
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

void Song::setSongTitle(const std::string songTitle)
{
	m_songTitle = songTitle;
}

void Song::setArtistName(const std::string artistName)
{
	m_artistName = artistName;
}

void Song::setDuration(const int duration)
{
	m_duration = duration;
}

std::string Song::getFormattedDuration() const
{
	std::string formattedString = "";
	const int seconds = m_duration % 60;
	const int minutes = (m_duration - seconds) / 60;
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



