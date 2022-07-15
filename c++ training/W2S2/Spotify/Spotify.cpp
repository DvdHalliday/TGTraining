#include "Spotify.h"

Spotify::Spotify()
{
	m_activeCommand = MenuCommand::MainMenu;
}

void Spotify::runApp()
{
	while (true) {//m_activeCommand != MenuCommand::Exit
		switch (m_activeCommand) {
		case MenuCommand::MainMenu:
			continue;
		case MenuCommand::CreatePlaylist:
			continue;
		case MenuCommand::BrowsePlaylists:
			continue;
		case MenuCommand::Exit:
			break;
		}
	}

}
