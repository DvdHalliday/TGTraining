#include "Playlist.h"

Playlist::Playlist()
{
	setPlaylistTitle("THIS IS THE BEST PLAYLIST EVER");
	m_songCount = 0;
}

Playlist::Playlist(std::string playlistTitle)
{
	setPlaylistTitle(playlistTitle);
	m_songCount = 0;
}

void Playlist::setPlaylistTitle(std::string playlistTitle)
{
	m_playlistTitle = playlistTitle;
}

std::string Playlist::getPlaylistName() const
{
	return m_playlistTitle;
}

bool Playlist::addSong(Song song)
{
	if (m_songCount == m_MaxSongCount || !song.isValid()) return false;
	m_songs[m_songCount] = song;
	m_songCount++;
	return true;
}

Song Playlist::getSong(int songIndex) const
{
	return m_songs[songIndex];
}

void Playlist::displayPlaylist() const
{
	std::cout << "Song Title\t\tArtist Name\t\tDuration" << std::endl;
	std::cout << "-----------------------------------------------------------------------" << std::endl;
	for (int i = 0; i < m_songCount; i++) {
		std::cout << m_songs[i].getSongTitle() << "\t\t" << m_songs[i].getArtistName() << "\t\t" << m_songs[i].getFormattedDuration() << std::endl;
	}
}
