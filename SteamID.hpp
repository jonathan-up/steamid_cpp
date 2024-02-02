#pragma once

#include <regex>

class SteamID {
public:
    // SteamID universes
    static const int UNIVERSE_INVALID = 0;
    static const int UNIVERSE_PUBLIC = 1;
    static const int UNIVERSE_BETA = 2;
    static const int UNIVERSE_INTERNAL = 3;
    static const int UNIVERSE_DEV = 4;

    // SteamID account types
    static const int TYPE_INVALID = 0;
    static const int TYPE_INDIVIDUAL = 1;
    static const int TYPE_MULTISEAT = 2;
    static const int TYPE_GAMESERVER = 3;
    static const int TYPE_ANON_GAMESERVER = 4;
    static const int TYPE_PENDING = 5;
    static const int TYPE_CONTENT_SERVER = 6;
    static const int TYPE_CLAN = 7;
    static const int TYPE_CHAT = 8;
    static const int TYPE_P2P_SUPER_SEEDER = 9;
    static const int TYPE_ANON_USER = 10;

    static const int INSTANCE_ALL = 0;
    static const int INSTANCE_DESKTOP = 1;
    static const int INSTANCE_CONSOLE = 2;
    static const int INSTANCE_WEB = 4;

    static const int CHAT_INSTANCE_FLAG_CLAN = 0x80000;
    static const int CHAT_INSTANCE_FLAG_LOBBY = 0x40000;
    static const int CHAT_INSTANCE_FLAG_MMSLOBBY = 0x20000;

    explicit SteamID(const std::string &id);

    std::string getIdSteam2Rendered(bool newerFormat) const;

    std::string getIdSteam3Rendered() const;

    long long getIdSteam64() const;

    bool isValid() const;

    bool isClanChat() const;

    bool isLobbyChat() const;

    bool isMMSLobbyChat() const;

    long long getAccountId() const;

private:
    long long universe;
    long long type;
    long long instance;
    long long accountId;

    static int getTypeFromChar(char type);

    static char getCharFromType(long long t);
};
