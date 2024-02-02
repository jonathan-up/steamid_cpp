//
// Created by 22131 on 2024/2/2.
//

#include <iostream>
#include "SteamID.hpp"

void steam64() {
    std::cout << "------ STEAM64 ------" << "\n";
    auto s1 = new SteamID("76561198975579577");
    std::cout << "ACCOUNT_ID: " << s1->getAccountId() << "\n";
    std::cout << "STEAM2: " << s1->getIdSteam2Rendered(false) << "\n";
    std::cout << "STEAM3: " << s1->getIdSteam3Rendered() << "\n";
    std::cout << "STEAM64: " << s1->getIdSteam64() << "\n";
    std::cout << "IS_VALID" << s1->isValid() << "\n";
    std::cout << "IS_CLAN_CHAT: " << s1->isClanChat() << "\n";
    std::cout << "IS_LOBBY_CHAT: " << s1->isLobbyChat() << "\n";
    std::cout << "IS_MM_LOBBY_CHAT: " << s1->isMMSLobbyChat() << "\n";
}

void steam2() {
    std::cout << "------ STEAM2 RENDERED ------" << "\n";
    auto s1 = new SteamID("STEAM_0:1:507656924");
    std::cout << "ACCOUNT_ID: " << s1->getAccountId() << "\n";
    std::cout << "STEAM2: " << s1->getIdSteam2Rendered(false) << "\n";
    std::cout << "STEAM3: " << s1->getIdSteam3Rendered() << "\n";
    std::cout << "STEAM64: " << s1->getIdSteam64() << "\n";
    std::cout << "IS_VALID" << s1->isValid() << "\n";
    std::cout << "IS_CLAN_CHAT: " << s1->isClanChat() << "\n";
    std::cout << "IS_LOBBY_CHAT: " << s1->isLobbyChat() << "\n";
    std::cout << "IS_MM_LOBBY_CHAT: " << s1->isMMSLobbyChat() << "\n";
}

void steam3() {
    std::cout << "------ STEAM3 RENDERED ------" << "\n";
    auto s1 = new SteamID("[U:1:1015313849]");
    std::cout << "ACCOUNT_ID: " << s1->getAccountId() << "\n";
    std::cout << "STEAM2: " << s1->getIdSteam2Rendered(false) << "\n";
    std::cout << "STEAM3: " << s1->getIdSteam3Rendered() << "\n";
    std::cout << "STEAM64: " << s1->getIdSteam64() << "\n";
    std::cout << "IS_VALID" << s1->isValid() << "\n";
    std::cout << "IS_CLAN_CHAT: " << s1->isClanChat() << "\n";
    std::cout << "IS_LOBBY_CHAT: " << s1->isLobbyChat() << "\n";
    std::cout << "IS_MM_LOBBY_CHAT: " << s1->isMMSLobbyChat() << "\n";
}

int main() {
    steam64();
    steam2();
    steam3();
}
