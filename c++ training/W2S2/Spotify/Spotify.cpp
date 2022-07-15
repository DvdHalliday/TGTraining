#include "Spotify.h"

void Spotify::openMainMenu()
{
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
			break;
		case MenuCommand::BrowsePlaylists:
			break;
		case MenuCommand::Exit:
			return;
		}

	}

}
