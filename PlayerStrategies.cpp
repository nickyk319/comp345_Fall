#include "PlayerStrategies.h"
#include <cstdlib>

PlayerStrategy::PlayerStrategy() : player(nullptr) {}
PlayerStrategy::~PlayerStrategy() {}
PlayerStrategy::PlayerStrategy(const PlayerStrategy& copy) {
    this->player = copy.player;
}
PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& op) {
    player = op.player;
    return *this;
}
std::ostream& operator<<(std::ostream& out, const PlayerStrategy& output) {
    out << "This is player strategy";
    return out;
}

void PlayerStrategy::setPlayer(Player* player) {
    this->player = player;
}

static int getRandom(int a, int b) {
    return (rand() % (b - a + 1)) + a;
}

HumanPlayerStrategy::HumanPlayerStrategy() : PlayerStrategy() {}

HumanPlayerStrategy::~HumanPlayerStrategy() {}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& copy): PlayerStrategy(copy) {}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& op) {
    player = op.player;
    return *this;
}

std::ostream& operator<<(std::ostream& out,
                         const HumanPlayerStrategy& output) {
    out << "This is human player strategy";
    return out;
}

// the human player give command to do action - g
void  HumanPlayerStrategy::issueOrder() {
            cout << "\nISSUE ORDER: \n" << endl;
            cout << "Enter Order of Territories to Attack\n";

            printAdjacentTerritories();
            cout << "\n";
            string attackInput;
            cin >> attackInput;
            toAttack(attackInput);
            cout << "\nYou selected: " << attackInput;

            cout << "\n\nEnter Order of Territories to Defend\n";
            printTerritories();
            cout << "\n";
            string defendInput;
            cin >> defendInput;
            todefend(defendInput);
            cout << "\nYou selected: " << defendInput;

            //Deploy
            cout << "\nDEPLOY ORDER: \n" << endl;
            while (reinforcements > 0) {
                cout << "Reinforcements: " << reinforcements;
                cout << "\nSelect a Territory to Deploy to\n";
                printTerritories();
                int tID;
                cin >> tID;

                cout << "\nHow many reinformcements would you like to deploy?";
                cout << "\n" << *(Map::worldMap.territories[tID - 1]);
                int numDeploy;
                cin >> numDeploy;

                reinforcements -= numDeploy;
                Deploy* d = new Deploy(this, tID, numDeploy);
                cout << "\nAdded " << numDeploy << " Reinforcements!";
                cout << "\n" << Map::worldMap.territories[tID - 1]->getTName();
                OrderList.push_back(*d);
            }

            //Advance
            cout << "ADVANCE ORDER: \n" << endl;
            for (auto i : todefendlist) {
                cout << "Defending " << Map::worldMap.territories[i - 1]->getTName();
                cout << "\nWhich Territory are you advancing to?\n";
                Map::worldMap.territories[i - 1]->displayBorders();
                int tID;
                int num;
                cin >> tID;
                for (auto j : territories) {
                    if (j->tID == tID) {
                        cout << "\nHow many troops are being moved?\n";
                        cin >> num;
                        Advance* a = new Advance(this, Map::worldMap.territories[i - 1]->getTID(),
                            Map::worldMap.territories[tID - 1]->getTID(), num);
                        OrderList.push_back(*a);
                        cout << "Success!";
                        break;
                    }
                    cout << "\nTerritory does not belong to you...\n";
                }
            }
            for (auto i : toAttacklist) {
                cout << "Attacking with " << Map::worldMap.territories[i - 1]->getTName();
                cout << "\nWhich Territory are you attacking?\n";
                Map::worldMap.territories[i - 1]->displayBorders();
                int tID;
                cin >> tID;
                for (auto j : territories) {
                    if (j->tID == tID) {
                        cout << "\nTerritory belongs to you...\n";
                        break;
                    }
                    Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
                    OrderList.push_back(*b);
                    cout << "\nSuccess!\n";
                }
            }
        };
vector<Territory> HumanPlayerStrategy::toAttack(const string& s) {
         vector<int> toAttacklist = parseStringToInt(s);
         for (auto i : toAttacklist) {

             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();

             toAttacklist.push_back(i);
         }

         return toAttacklist;
     };
vector<Territory> HumanPlayerStrategy::todenfend(const string& s {
         vector<int> todefendlist = parseStringToInt(s);
         for (auto i : todefendlist) {
             todefendlist.push_back(i);
             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
         }
         return todefendlist;
     };

AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategy() {}

AggressivePlayerStrategy::~AggressivePlayerStrategy() {}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& copy)
        : PlayerStrategy(copy) {}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& op) {
    player = op.player;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& output) {
    out << "This is aggressive player strategy";
    return out;
}

// computer player which focus on attack
void AggressivePlayerStrategy::issueOrder() {
    cout << "\nISSUE ORDER: \n" << endl;
    cout << "Enter Order of Territories to Attack\n";

    printAdjacentTerritories();
    cout << "\n";
    string attackInput;
    cin >> attackInput;
    toAttack(attackInput);
    cout << "\nYou selected: " << attackInput;

    cout << "\n\nEnter Order of Territories to Defend\n";
    printTerritories();
    cout << "\n";
    string defendInput;
    cin >> defendInput;
    todefend(defendInput);
    cout << "\nYou selected: " << defendInput;

    //Deploy
    cout << "\nDEPLOY ORDER: \n" << endl;
    while (reinforcements > 0) {
        cout << "Reinforcements: " << reinforcements;
        cout << "\nSelect a Territory to Deploy to\n";
        printTerritories();
        int tID;
        cin >> tID;

        cout << "\nHow many reinformcements would you like to deploy?";
        cout << "\n" << *(Map::worldMap.territories[tID - 1]);
        int numDeploy;
        cin >> numDeploy;

        reinforcements -= numDeploy;
        Deploy* d = new Deploy(this, tID, numDeploy);
        cout << "\nAdded " << numDeploy << " Reinforcements!";
        cout << "\n" << Map::worldMap.territories[tID - 1]->getTName();
        OrderList.push_back(*d);
    }

    //Advance
    cout << "ADVANCE ORDER: \n" << endl;
    for (auto i : todefendlist) {
        cout << "Defending " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you advancing to?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        int num;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nHow many troops are being moved?\n";
                cin >> num;
                Advance* a = new Advance(this, Map::worldMap.territories[i - 1]->getTID(),
                    Map::worldMap.territories[tID - 1]->getTID(), num);
                OrderList.push_back(*a);
                cout << "Success!";
                break;
            }
            cout << "\nTerritory does not belong to you...\n";
        }
    }
    for (auto i : toAttacklist) {
        cout << "Attacking with " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you attacking?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nTerritory belongs to you...\n";
                break;
            }
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            cout << "\nSuccess!\n";
        }
    }

};
vector<Territory> AggressivePlayerStrategy::toAttack() {
    vector <Territory> agrList;
    vector<int> attacks = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {
        
        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }

    int n = agrList.size;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j >= i; j--)
        {
            if (agrList[j - 1].getNumArmy > agrList[j].getNumArmy)
                Territory temp = agrList[i];
                 agrList[i] = agrList[j];
                 agrList[j] = temp;
        }
    }

    return agrList;
};
vector<Territory> AggressivePlayerStrategy::todenfend(const string& s{
         vector <Territory> dfdList;
    vector<int> defends = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }
         return dfdList;
         
    };

BenevolentPlayerStrategy::BenevolentPlayerStrategy() : PlayerStrategy() {}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& copy): PlayerStrategy(toCopy) {}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(
        const BenevolentPlayerStrategy& op) {
    player = op.player;
    return *this;
}

std::ostream& operator<<(std::ostream& out,
                         const BenevolentPlayerStrategy& output) {
    out << "This is benevolent player strategy";
    return out;
}

// computer player which focus on defend
void BenevolentPlayerStrategy::issueOrder() {
    cout << "\nISSUE ORDER: \n" << endl;
    cout << "Enter Order of Territories to Attack\n";

    printAdjacentTerritories();
    cout << "\n";
    string attackInput;
    cin >> attackInput;
    toAttack(attackInput);
    cout << "\nYou selected: " << attackInput;

    cout << "\n\nEnter Order of Territories to Defend\n";
    printTerritories();
    cout << "\n";
    string defendInput;
    cin >> defendInput;
    todefend(defendInput);
    cout << "\nYou selected: " << defendInput;

    //Deploy
    cout << "\nDEPLOY ORDER: \n" << endl;
    while (reinforcements > 0) {
        cout << "Reinforcements: " << reinforcements;
        cout << "\nSelect a Territory to Deploy to\n";
        printTerritories();
        int tID;
        cin >> tID;

        cout << "\nHow many reinformcements would you like to deploy?";
        cout << "\n" << *(Map::worldMap.territories[tID - 1]);
        int numDeploy;
        cin >> numDeploy;

        reinforcements -= numDeploy;
        Deploy* d = new Deploy(this, tID, numDeploy);
        cout << "\nAdded " << numDeploy << " Reinforcements!";
        cout << "\n" << Map::worldMap.territories[tID - 1]->getTName();
        OrderList.push_back(*d);
    }

    //Advance
    cout << "ADVANCE ORDER: \n" << endl;
    for (auto i : todefendlist) {
        cout << "Defending " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you advancing to?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        int num;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nHow many troops are being moved?\n";
                cin >> num;
                Advance* a = new Advance(this, Map::worldMap.territories[i - 1]->getTID(),
                    Map::worldMap.territories[tID - 1]->getTID(), num);
                OrderList.push_back(*a);
                cout << "Success!";
                break;
            }
            cout << "\nTerritory does not belong to you...\n";
        }
    }
    for (auto i : toAttacklist) {
        cout << "Attacking with " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you attacking?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nTerritory belongs to you...\n";
                break;
            }
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            cout << "\nSuccess!\n";
        }
    }


};
vector<Territory> BenevolentPlayerStrategy::toAttack(const string& s) {
    vector <Territory> agrList;
    vector<int> attacks = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }

    return agrList;
};
vector<Territory> BenevolentPlayerStrategy::todenfend(const string& s{
        vector <Territory> dfdList;
    vector<int> defends = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }

    int n = dfdList.size;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j >= i; j--)
        {
            if (dfdList[j - 1].getNumArmy > dfdList[j].getNumArmy)
                swap(array, j, j - 1);

            Territory temp = dfdList[i];
            dfdList[i] = dfdList[j];
            dfdList[j] = temp;

        }
    }


    return dfdList;
    };

// computer player which don't issue order - g
void NeutralPlayerStrategy::issueOrder() {
    cout << "\nNO ISSUE ORDER: \n" << endl;
};
vector<Territory> BenevolentPlayerStrategy::toAttack(const string & s) {
        vector <Territory> agrList;
        vector<int> attacks = parseStringToInt(s);
        for (int i = 0; i < Map::worldMap.territories.size(); i++) {

            string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
            if (territoryPlayer == this->player) {
                agrList.push_back(worldMap.territories[i])
            }

        }

        return agrList;
};
vector<Territory> NeutralPlayerStrategy::todenfend(const string& s{
    vector <Territory> dfdList;
    vector<int> defends = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }
         return dfdList;
    };

// computer player which always try to attack nearby territories -g
void CheaterPlayerStrategy::issueOrder() {
    cout << "\nISSUE ORDER: \n" << endl;
    cout << "Enter Order of Territories to Attack\n";

    printAdjacentTerritories();
    cout << "\n";
    string attackInput;
    cin >> attackInput;
    toAttack(attackInput);
    cout << "\nYou selected: " << attackInput;

    cout << "\n\nEnter Order of Territories to Defend\n";
    printTerritories();
    cout << "\n";
    string defendInput;
    cin >> defendInput;
    todefend(defendInput);
    cout << "\nYou selected: " << defendInput;

    //Deploy
    cout << "\nDEPLOY ORDER: \n" << endl;
    while (reinforcements > 0) {
        cout << "Reinforcements: " << reinforcements;
        cout << "\nSelect a Territory to Deploy to\n";
        printTerritories();
        int tID;
        cin >> tID;

        cout << "\nHow many reinformcements would you like to deploy?";
        cout << "\n" << *(Map::worldMap.territories[tID - 1]);
        int numDeploy;
        cin >> numDeploy;

        reinforcements -= numDeploy;
        Deploy* d = new Deploy(this, tID, numDeploy);
        cout << "\nAdded " << numDeploy << " Reinforcements!";
        cout << "\n" << Map::worldMap.territories[tID - 1]->getTName();
        OrderList.push_back(*d);
    }

    //Advance
    cout << "ADVANCE ORDER: \n" << endl;
    for (auto i : todefendlist) {
        cout << "Defending " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you advancing to?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        int num;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nHow many troops are being moved?\n";
                cin >> num;
                Advance* a = new Advance(this, Map::worldMap.territories[i - 1]->getTID(),
                    Map::worldMap.territories[tID - 1]->getTID(), num);
                OrderList.push_back(*a);
                cout << "Success!";
                break;
            }
            cout << "\nTerritory does not belong to you...\n";
        }
    }
    for (auto i : toAttacklist) {
        cout << "Attacking with " << Map::worldMap.territories[i - 1]->getTName();
        cout << "\nWhich Territory are you attacking?\n";
        Map::worldMap.territories[i - 1]->displayBorders();
        int tID;
        cin >> tID;
        for (auto j : territories) {
            if (j->tID == tID) {
                cout << "\nTerritory belongs to you...\n";
                break;
            }
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            cout << "\nSuccess!\n";
        }
    }

    
};
vector<Territory> CheaterPlayerStrategy::toAttack(const string& s) {
    vector <Territory> agrList;
    vector<int> attacks = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }

    return agrList;
};
vector<Territory> CheaterPlayerStrategy::todenfend(const string& s{
    vector <Territory> dfdList;
    vector<int> defends = parseStringToInt(s);
    for (int i = 0; i < Map::worldMap.territories.size(); i++) {

        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        if (territoryPlayer == this->player) {
            agrList.push_back(worldMap.territories[i])
        }

    }
         return dfdList;
    };
