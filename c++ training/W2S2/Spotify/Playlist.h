#pragma once
#include <iostream>
#include "Song.h"

//Create a new class called Playlist.Playlists should be containers for songs, so it should let the user add songs to the playlist.
//
//It should have the following private members.
//const static int MaxSongCount;
//std::string playlistTitle;
//Song songs[MaxSongCount];
//int songCount;
//
//The class should have a default constructor, a constructor that initializes the playlist title, and a getterand setter for the playlist name.
//
//Additionally, implement the following methods :
//bool addSong(Song song);
//Song getSong(int songIndex);
//void displayPlaylist();


class Playlist {
private:
	const static int m_MaxSongCount = 25;
	std::string m_playlistTitle;
	Song m_songs[m_MaxSongCount];
	int m_songCount;
public:
	Playlist();
	Playlist(const std::string playlistTitle);
	void setPlaylistTitle(const std::string playlistTitle);
	std::string getPlaylistName() const;
	bool addSong(const Song song);
	Song getSong(const int songIndex) const;
	void displayPlaylist() const;
};