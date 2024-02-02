# steamid_cpp
SteamID class for C++.

C++ port of [php-steamid](https://github.com/DoctorMcKay/php-steamid)

# example
```c++
#include <iostream>
#include "SteamID.hpp"

int main() {
    auto s1 = new SteamID("76561198975579577");
    std::cout << "ACCOUNT_ID: " << s1->getAccountId() << "\n";
    std::cout << "STEAM2: " << s1->getIdSteam2Rendered(false) << "\n";
    std::cout << "STEAM3: " << s1->getIdSteam3Rendered() << "\n";
}
```