#include "Spotify.h"

void Spotify::openMainMenu()
{
	system("cls");
	std::cout << "Welcome to Spotify! What would you like to do?\n1 - Create a Playlist\n2 - Browse Playlists\n3 - Exit\nYour choice: ";
	float choice;
	std::cin >> choice;
	enum class MainMenuCommand { CreatePlaylist=1, BrowsePlayLists, Exit };
	while (!std::cin.good() || (choice != 1 && choice != 2 && choice !=3) || (choice - floor(choice) != 0.0f)) { //This checks if the choice is an integer 1, 2 or 3
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		system("cls");
		std::cout << "Welcome to Spotify! What would you like to do?\n1 - Create a Playlist\n2 - Browse Playlists\n3 - Exit\nYour choice: ";
		std::cin >> choice;
	}
	MainMenuCommand commandChoice = static_cast<MainMenuCommand>(choice);
	switch (commandChoice) {
	case MainMenuCommand::CreatePlaylist:
		m_activeCommand = MenuCommand::CreatePlaylist;
		break;
	case MainMenuCommand::BrowsePlayLists:
		m_activeCommand = MenuCommand::BrowsePlaylists;
		break;
	case MainMenuCommand::Exit:
		m_activeCommand = MenuCommand::Exit;
		break;
	}
}

void Spotify::openCreatePlaylistMenu()
{
	system("cls");
	std::cout << "Please enter a name for the playlist: ";
	std::string playlistName;
	std::cin >> playlistName;
	Playlist newPlaylist = Playlist(playlistName);
	m_playlists.addPlaylist(newPlaylist);
	while (true) {
		system("cls");
		std::cout << "Let's add a song to " << playlistName << "!\nPlease enter the song title: ";
		std::string songName;
		std::cin >> songName;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Please enter the artist name: ";
		std::string songArtist;
		std::cin >> songArtist;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Please enter the duration of the song: ";
		float songDuration;
		std::cin >> songDuration;
		while (!std::cin.good() || songDuration < 1 || (songDuration - floor(songDuration) != 0.0f)) { //This checks if the choice is an integer greater than 0
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a valid duration of the song: ";
			std::cin >> songDuration;
		}
		system("cls");
		std::cout << "Song added!" << std::endl;
		std::cout << "\n1 - Enter another song\n2 - Go back to main menu\nYour choice: ";
		float choice;
		std::cin >> choice;
		enum class EnterSongCommand { EnterAnotherSong = 1, MainMenu };
		while (!std::cin.good() || (choice != 1 && choice != 2) || (choice - floor(choice) != 0.0f)) { //This checks if the choice is an integer 1 or 2
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			std::cout << "Invalid choice" << std::endl;
			std::cout << "\n1 - Enter another song\n2 - Go back to main menu\nYour choice: ";
			std::cin >> choice;
		}
		EnterSongCommand commandChoice = static_cast<EnterSongCommand>(choice);
		switch (commandChoice) {
		case EnterSongCommand::EnterAnotherSong:
			break;
		case EnterSongCommand::MainMenu:
			openMainMenu();
			return;
		}
	}
}

Spotify::Spotify()
{
	m_activeCommand = MenuCommand::MainMenu;
}

void Spotify::runApp()
{
	while (true) {//m_activeCommand != MenuCommand::Exit
		switch (m_activeCommand) {
		case MenuCommand::MainMenu:
			openMainMenu();
			break;
		case MenuCommand::CreatePlaylist:
			openCreatePlaylistMenu();
			break;
		case MenuCommand::BrowsePlaylists:
			break;
		case MenuCommand::Exit:
			return;
		}

	}



}
