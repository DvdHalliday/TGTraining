#pragma once
#include <iostream>

//Exercise 1 - Songs
//Create a Song class in your project.Make sure to declare it in a.h and define it in a.cpp.
//
//Your Song class should have the following private members :
//	std::string songTitle;
//std::string artistName;
//int duration;
//
//It should have a default constructor, a constructor with parameters to initialize the private members, getters, and setters.
//
//Additionally, implement the following methods :
//std::string getFormatedDuration(); // Should return duration in the
//						// mm:ss format
//bool isValid(); // You decide how a song is considered valid or not


class Song {
private:
	std::string m_songTitle;
	std::string m_artistName;
	int m_duration;
public:
	Song();
	Song(std::string songTitle, std::string artistName, int duration);
	std::string getSongTitle() const;
	std::string getArtistName() const;
	int getDuration() const;
	void setSongTitle(std::string songTitle);
	void setArtistName(std::string artistName) ;
	void setDuration(int duration) ;
	std::string getFormattedDuration() const;
	bool isValid() const;
};