#include "SteamID.hpp"

SteamID::SteamID(const std::string &id) {
    if (id.empty()) {
        this->universe = UNIVERSE_INVALID;
        this->type = TYPE_INVALID;
        this->instance = INSTANCE_ALL;
        this->accountId = 0;
        return;
    }

    // check if steam2 rendered
    std::regex patternSteam2("^STEAM_([0-5]):([0-1]):([0-9]+)$");
    std::smatch matches;
    if (std::regex_search(id, matches, patternSteam2)) {
        if (matches.size() < 4) {
            return;
        }
        // matches[0]: full steam id
        // matches[1]: universe type
        // matches[2]: instance type
        // matches[3]: account id
        try {
            int _universe = std::stoi(matches[1].str());
            int _instance = std::stoi(matches[2].str());
            int _account = std::stoi(matches[3].str());

            this->universe = _universe;
            if (_universe <= UNIVERSE_PUBLIC) {
                this->universe = UNIVERSE_PUBLIC;
            }

            this->type = TYPE_INDIVIDUAL;
            this->instance = INSTANCE_DESKTOP;
            this->accountId = _account * 2 + _instance;
        } catch (const std::exception &e) {
            // throw a custom exception?
            throw std::invalid_argument("invalid steam id");
        }

        return;
    }

    // check if steam3 rendered
    std::regex patternSteam3("^\\[([a-zA-Z]):([0-5]):([0-9]+)(:[0-9]+)?\\]$");
    if (std::regex_search(id, matches, patternSteam3)) {
        if (matches.size() < 5) {
            return;
        }
        // matches[0]: full steam id
        // matches[1]: type char
        // matches[2]: universe type
        // matches[3]: account id
        // matches[4]: instance type
        try {
            int _universe = std::stoi(matches[2].str());
            std::string _typeChar = matches[1].str();
            int _account = std::stoi(matches[3].str());
            std::string _instance = matches[4].str();

            this->universe = _universe;
            this->accountId = _account;
            if (!_instance.empty()) {
                std::string instanceStr = _instance.substr(1);
                this->instance = std::stoi(instanceStr);
            } else {
                this->instance = INSTANCE_DESKTOP;
                if (_typeChar == "g" || _typeChar == "T" || _typeChar == "c" || _typeChar == "L") {
                    this->instance = INSTANCE_ALL;
                }
            }

            if (_typeChar == "c") {
                this->instance |= CHAT_INSTANCE_FLAG_CLAN;
                this->type = TYPE_CHAT;
            } else if (_typeChar == "L") {
                this->instance |= CHAT_INSTANCE_FLAG_LOBBY;
                this->type = TYPE_CHAT;
            } else {
                this->type = getTypeFromChar(_typeChar[0]);
            }

        } catch (const std::exception &e) {
            // throw a custom exception?
            throw std::invalid_argument("invalid steam id");
        }

        return;
    }

    //check if steam 64
    try {
        long long _id = std::stoll(id);
        this->universe = static_cast<int>(_id >> 56);
        this->type = static_cast<int>((_id >> 52) & 0xF);
        this->instance = static_cast<int>((_id >> 32) & 0xFFFFF);
        this->accountId = _id & 0xFFFFFFFF;
    } catch (const std::exception &e) {
        throw std::invalid_argument("invalid steam id");
    }
}

std::string SteamID::getIdSteam2Rendered(bool newerFormat = false) const {
    if (this->type != TYPE_INDIVIDUAL) {
        throw std::runtime_error("Can't get Steam2 rendered ID for non-individual ID");
    }

    long long _universe = this->universe;
    if (_universe == 1 && !newerFormat) {
        _universe = 0;
    }

    std::string steam2;
    steam2.append("STEAM_")
            .append(std::to_string(_universe))
            .append(":")
            .append(std::to_string((this->accountId & 1)))
            .append(":")
            .append(std::to_string((int) (this->accountId / 2)));

    return steam2;
}

std::string SteamID::getIdSteam3Rendered() const {
    char typeChar = getCharFromType(this->type) != '\0' ? getCharFromType(this->type) : 'i';
    if (this->instance & CHAT_INSTANCE_FLAG_LOBBY) {
        typeChar = 'c';
    } else if (this->instance & CHAT_INSTANCE_FLAG_LOBBY) {
        typeChar = 'L';
    }

    bool renderInstance = (this->type == TYPE_ANON_GAMESERVER || this->type == TYPE_MULTISEAT ||
                           (this->type == TYPE_INDIVIDUAL && this->instance != INSTANCE_DESKTOP));
    std::string steam3;
    steam3.append("[")
            .append(std::string(1, typeChar))
            .append(":")
            .append(std::to_string(this->universe))
            .append(":")
            .append(std::to_string(this->accountId));

    if (renderInstance) {
        steam3.append(":");
        steam3.append(std::to_string(this->instance));
    }
    steam3.append("]");

    return steam3;
}

long long SteamID::getIdSteam64() const {
    return ((this->universe << 56) | (this->type << 52) | (this->instance << 32) | (this->accountId));
}

int SteamID::getTypeFromChar(char c) {
    const char typeChars[] = {'I', 'U', 'M', 'G', 'A', 'P', 'C', 'g', 'T', 'a'};
    for (int i = 0; i < sizeof typeChars; i++) {
        if (c == typeChars[i]) {
            return i;
        }
    }
    return TYPE_INVALID;
}

char SteamID::getCharFromType(long long t) {
    const char typeChars[] = {'I', 'U', 'M', 'G', 'A', 'P', 'C', 'g', 'T', 'a'};
    if (t < 0 || t > sizeof typeChars) {
        return '\0';
    }
    return typeChars[t];
}

bool SteamID::isValid() const {
    if (this->type <= TYPE_INVALID || this->type > TYPE_ANON_USER) {
        return false;
    }
    if (this->universe <= UNIVERSE_INVALID || this->universe > UNIVERSE_DEV) {
        return false;
    }
    if (this->type == TYPE_INDIVIDUAL && (this->accountId == 0 || this->instance > INSTANCE_WEB)) {
        return false;
    }
    if (this->type == TYPE_CLAN && (this->accountId == 0 || this->instance != INSTANCE_ALL)) {
        return false;
    }
    if (this->type == TYPE_GAMESERVER && this->accountId == 0) {
        return false;
    }

    return true;
}

bool SteamID::isClanChat() const {
    return this->type == TYPE_CHAT && (this->instance & CHAT_INSTANCE_FLAG_CLAN);
}

bool SteamID::isLobbyChat() const {
    return this->type == TYPE_CHAT && (this->instance & CHAT_INSTANCE_FLAG_LOBBY);
}

bool SteamID::isMMSLobbyChat() const {
    return this->type == TYPE_CHAT && (this->instance & CHAT_INSTANCE_FLAG_MMSLOBBY);
}

long long SteamID::getAccountId() const {
    return this->accountId;
}
