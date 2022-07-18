#include "Spotify.h" 
#include <string>

//Exercise 4.2 - Create a Playlist Menu
//With the main menu done, it’s time to create the create - a - playlist menu.You should have the following private methods:
//void openCreatePlaylistMenu();
//
//The method should allow the user to enter a name to the playlistand add songs to it.
//
//
//Exercise 4.3 - Browser Playlists Menu
//Let’s create the final menu for our app, the one where you can browse playlists.Create the private method:
//void openBrowsePlaylistsMenu();
//
//The method should allow the user to browse the currently created playlistand choose one to be displayed.Choose how you want to make the user choose their next action.The example shows using enter as the key to go back


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
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
	std::cout << "Please enter a name for the playlist: ";
	std::string playlistName;
	std::getline(std::cin,playlistName);
	//std::cin >> playlistName;
	Playlist newPlaylist = Playlist(playlistName);
	while (true) {
		system("cls");
		std::cout << "Let's add a song to " << playlistName << "!\nPlease enter the song title: ";
		std::string songName;
		std::getline(std::cin, songName);
		std::cout << "Please enter the artist name: ";
		std::string songArtist;
		std::getline(std::cin, songArtist);
		std::cout << "Please enter the duration of the song: ";
		float songDuration;
		std::cin >> songDuration;
		while (!std::cin.good() || songDuration < 1 || (songDuration - floor(songDuration) != 0.0f)) { //This checks if the choice is an integer greater than 0
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please enter a valid duration of the song: ";
			std::cin >> songDuration;
		}
		Song newSong = Song(songName, songArtist, songDuration);
		newPlaylist.addSong(newSong);
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
			m_playlists.addPlaylist(newPlaylist);
			openMainMenu();
			return;
		}
	}
}

void Spotify::openBrowsePlaylists()
{
	while (m_playlists.getPlayListCount()>0) {
		system("cls");
		std::cout << "Here are your playlists!" << std::endl;
		for (int i = 1; i <= m_playlists.getPlayListCount(); i++) {
			std::cout << i << " - " << m_playlists.getPlaylist(i - 1).getPlaylistName() << std::endl;
		}
		std::cout << "\nWhich playlist do you want to see?: ";
		float playlistChoice;
		std::cin >> playlistChoice;
		while (!std::cin.good() || playlistChoice<1 || playlistChoice>m_playlists.getPlayListCount() || (playlistChoice - floor(playlistChoice) != 0.0f)) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Invalid choice" << std::endl;
			std::cout << "\nWhich playlist do you want to see?: ";
			std::cin >> playlistChoice;
		}
		system("cls");
		std::cout << "Here's " << m_playlists.getPlaylist(playlistChoice - 1).getPlaylistName() << "!\n" << std::endl;
		m_playlists.getPlaylist(playlistChoice - 1).displayPlaylist();
		std::cout << "\n1 - Pick another playlist\n2 - Go back to main menu\n\nWhat do you want to do?: ";
		float choice;
		std::cin >> choice;
		enum class BrowsePlaylistCommand { PickAnotherPlaylist = 1, MainMenu };
		while (!std::cin.good() || (choice != 1 && choice != 2) || (choice - floor(choice) != 0.0f)) { //This checks if the choice is an integer 1 or 2
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			system("cls");
			std::cout << "Invalid choice" << std::endl;
			std::cout << "\n1 - Pick another playlist\n2 - Go back to main menu\nYour choice: ";
			std::cin >> choice;
		}
		BrowsePlaylistCommand commandChoice = static_cast<BrowsePlaylistCommand>(choice);
		switch (commandChoice) {
		case BrowsePlaylistCommand::PickAnotherPlaylist:
			break;
		case BrowsePlaylistCommand::MainMenu:
			openMainMenu();
			return;
		}
	}
	system("cls");
	std::cout << "There are currently no playlists available, press anything and then enter to return to the main menu: ";
	std::string returnToMenu;
	std::cin >> returnToMenu;
	openMainMenu();
	return;
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
			openBrowsePlaylists();
			break;
		case MenuCommand::Exit:
			return;
		}

	}



}
