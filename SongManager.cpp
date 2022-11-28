

#include "SongManager.h"

using namespace std;

SongManager* SongManager::s_instance{ nullptr };

SongManager& SongManager::Instance()
{
    if (s_instance == nullptr)
    {
        s_instance = new SongManager();
    }

    return *s_instance;
}

SongManager::SongManager()
{};

SongManager::~SongManager()
{
    for (auto songName : _songNames)
    {
        system(("rm " + SONG_DIRECTORY + songName).c_str());
    }

    cout << "Songs Deleted.\n";
}

int SongManager::AddSong(string songName)
{
    _songNames.push_back(songName);

    return 1;
}

