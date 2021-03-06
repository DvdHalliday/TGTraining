#include "PlaylistContainer.h"

PlaylistContainer::PlaylistContainer()
{
	m_playlistCount = 0;
}

void PlaylistContainer::addPlaylist(const Playlist playlist)
{
	m_playlists[m_playlistCount] = playlist;
	m_playlistCount++;
}

Playlist PlaylistContainer::getPlaylist(const int playlistIndex) const
{
	return m_playlists[playlistIndex];
}

int PlaylistContainer::getPlayListCount() const
{
	return m_playlistCount;
}
