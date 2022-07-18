#pragma once
#include "Playlist.h"


//Exercise 3 - PlaylistContainer
//Create a new class called PlaylistContainer.PlaylistContainer should be a collection of playlists, so it should look very similar to the Playlist class.
//It should have the following private members :
//	const static int MaxPlaylistCount;
//Playlist playlists[MaxPlaylistCount];
//int playlistCount;
//
//The class should have a default constructor, a method to add a playlist, a method to get a playlist with an index, and a method to know the current playlist count.
//
//Test your program up until here.Create a main.cpp fileand implement the main method.In here, create a couple playlists with a couple songsand add them to a PlaylistContainer instance.Then, get those same playlists using the getter from the instanceand display the playlists in the console.
//
//What happens when you try to get a playlist with an out of bounds index ? How would you handle it ?
//
//When you make sure everything is working, you can continue to the next exercise.

class PlaylistContainer {
private:
	const static int m_MaxPlaylistCount = 10;
	Playlist m_playlists[m_MaxPlaylistCount];
	int m_playlistCount;
public:
	PlaylistContainer();
	void addPlaylist(const Playlist playlist);
	Playlist getPlaylist(const int playlistIndex) const;
	int getPlayListCount() const;
};
