#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy() : player(nullptr) {}
PlayerStrategy::~PlayerStrategy() {}
void PlayerStrategy::setPlayer(Player* player) {
    this->player = player;
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

            //Cards
            bool flag = false;
            while (!flag) {
                cout << "\nChoose a card\n";
                showCards();
                int cardIndex;
                cin >> cardIndex;
                switch (handCard[cardIndex]->getType()) {
                case bomb: {
                    cout << "\nbomb";
                    cout << "\nSelect a target";
                    int tID;
                    cin >> tID;
                    Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
                    OrderList.push_back(*b);
                    flag = true;
                    break;
                }
                case reinforcement: {
                    cout << "\nreinforcement";
                    cout << "\nSelect a destination";
                    int tID;
                    cin >> tID;
                    Deploy* d = new Deploy(this, Map::worldMap.territories[tID - 1]->getTID(), 5);
                    OrderList.push_back(*d);
                    flag = true;
                    break;
                }
                case blockade: {
                    cout << "\nblockade";
                    cout << "\nSelect a target";
                    int tID;
                    cin >> tID;
                    Blockade* b = new Blockade(this, Map::worldMap.territories[tID - 1]->getTID());
                    OrderList.push_back(*b);
                    flag = true;
                    break;
                }
                case airlift: {
                    cout << "\nairlift";
                    cout << "\nSelect a destination";
                    int tID;
                    cin >> tID;
                    cout << "\nHow many troops are being moved?";
                    int num;
                    cin >> num;
                    cout << "\nWhere are they being taken from?";
                    int tID2;
                    cin >> tID2;
                    Airlift* a = new Airlift(this, Map::worldMap.territories[tID2 - 1]->getTID(),
                        Map::worldMap.territories[tID - 1]->getTID(), num);
                    OrderList.push_back(*a);
                    flag = true;
                    break;
                }
                case diplomacy: {
                    cout << "\ndiplomacy";
                    cout << "\nSelect a Player";
                    int pID2;
                    cin >> pID2;
                    Negotiate* n = new Negotiate(this, this->getPlayerByID(pID2));
                    OrderList.push_back(*n);
                    flag = true;
                    break;
                }
                default: {
                    cout << "invild input, try again!\n\n" << endl;

                }
                }
            }
        };
vector<Territory> HumanPlayerStrategy::toAttack(const string& s) {
         vector<int> attacks = parseStringToInt(s);
         for (auto i : attacks) {

             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();

             toAttacklist.push_back(i);
         }

         return toAttacklist;
     };
vector<Territory> HumanPlayerStrategy::todenfend(const string& s {
         vector<int> defends = parseStringToInt(s);
         for (auto i : defends) {
             todefendlist.push_back(i);
             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
         }
         return todefendlist;
     };



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

    //Cards
    bool flag = false;
    while (!flag) {
        cout << "\nChoose a card\n";
        showCards();
        int cardIndex;
        cin >> cardIndex;
        switch (handCard[cardIndex]->getType()) {
        case bomb: {
            cout << "\nbomb";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case reinforcement: {
            cout << "\nreinforcement";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            Deploy* d = new Deploy(this, Map::worldMap.territories[tID - 1]->getTID(), 5);
            OrderList.push_back(*d);
            flag = true;
            break;
        }
        case blockade: {
            cout << "\nblockade";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Blockade* b = new Blockade(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case airlift: {
            cout << "\nairlift";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            cout << "\nHow many troops are being moved?";
            int num;
            cin >> num;
            cout << "\nWhere are they being taken from?";
            int tID2;
            cin >> tID2;
            Airlift* a = new Airlift(this, Map::worldMap.territories[tID2 - 1]->getTID(),
                Map::worldMap.territories[tID - 1]->getTID(), num);
            OrderList.push_back(*a);
            flag = true;
            break;
        }
        case diplomacy: {
            cout << "\ndiplomacy";
            cout << "\nSelect a Player";
            int pID2;
            cin >> pID2;
            Negotiate* n = new Negotiate(this, this->getPlayerByID(pID2));
            OrderList.push_back(*n);
            flag = true;
            break;
        }
        default: {
            cout << "invild input, try again!\n\n" << endl;

        }
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
         vector<int> defends = parseStringToInt(s);
         for (auto i : defends) {
             todefendlist.push_back(i);
             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
         }
         return todefendlist;
    };


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

    //Cards
    bool flag = false;
    while (!flag) {
        cout << "\nChoose a card\n";
        showCards();
        int cardIndex;
        cin >> cardIndex;
        switch (handCard[cardIndex]->getType()) {
        case bomb: {
            cout << "\nbomb";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case reinforcement: {
            cout << "\nreinforcement";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            Deploy* d = new Deploy(this, Map::worldMap.territories[tID - 1]->getTID(), 5);
            OrderList.push_back(*d);
            flag = true;
            break;
        }
        case blockade: {
            cout << "\nblockade";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Blockade* b = new Blockade(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case airlift: {
            cout << "\nairlift";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            cout << "\nHow many troops are being moved?";
            int num;
            cin >> num;
            cout << "\nWhere are they being taken from?";
            int tID2;
            cin >> tID2;
            Airlift* a = new Airlift(this, Map::worldMap.territories[tID2 - 1]->getTID(),
                Map::worldMap.territories[tID - 1]->getTID(), num);
            OrderList.push_back(*a);
            flag = true;
            break;
        }
        case diplomacy: {
            cout << "\ndiplomacy";
            cout << "\nSelect a Player";
            int pID2;
            cin >> pID2;
            Negotiate* n = new Negotiate(this, this->getPlayerByID(pID2));
            OrderList.push_back(*n);
            flag = true;
            break;
        }
        default: {
            cout << "invild input, try again!\n\n" << endl;

        }
        }
    }
};
vector<Territory> BenevolentPlayerStrategy::toAttack(const string& s) {
    vector<int> attacks = parseStringToInt(s);
    for (auto i : attacks) {

        cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();

        toAttacklist.push_back(i);
    }

    return toAttacklist;
};
vector<Territory> BenevolentPlayerStrategy::todenfend(const string& s{
        vector <Territory> dfdList;
    vector<int> attacks = parseStringToInt(s);
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
vector<Territory> NeutralPlayerStrategy::toAttack(const string& s) {
    vector<int> attacks = parseStringToInt(s);
    for (auto i : attacks) {

        cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();

        toAttacklist.push_back(i);
    }

    return toAttacklist;
};
vector<Territory> NeutralPlayerStrategy::todenfend(const string& s{
         vector<int> defends = parseStringToInt(s);
         for (auto i : defends) {
             todefendlist.push_back(i);
             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
         }
         return todefendlist;
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

    //Cards
    bool flag = false;
    while (!flag) {
        cout << "\nChoose a card\n";
        showCards();
        int cardIndex;
        cin >> cardIndex;
        switch (handCard[cardIndex]->getType()) {
        case bomb: {
            cout << "\nbomb";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Bomb* b = new Bomb(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case reinforcement: {
            cout << "\nreinforcement";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            Deploy* d = new Deploy(this, Map::worldMap.territories[tID - 1]->getTID(), 5);
            OrderList.push_back(*d);
            flag = true;
            break;
        }
        case blockade: {
            cout << "\nblockade";
            cout << "\nSelect a target";
            int tID;
            cin >> tID;
            Blockade* b = new Blockade(this, Map::worldMap.territories[tID - 1]->getTID());
            OrderList.push_back(*b);
            flag = true;
            break;
        }
        case airlift: {
            cout << "\nairlift";
            cout << "\nSelect a destination";
            int tID;
            cin >> tID;
            cout << "\nHow many troops are being moved?";
            int num;
            cin >> num;
            cout << "\nWhere are they being taken from?";
            int tID2;
            cin >> tID2;
            Airlift* a = new Airlift(this, Map::worldMap.territories[tID2 - 1]->getTID(),
                Map::worldMap.territories[tID - 1]->getTID(), num);
            OrderList.push_back(*a);
            flag = true;
            break;
        }
        case diplomacy: {
            cout << "\ndiplomacy";
            cout << "\nSelect a Player";
            int pID2;
            cin >> pID2;
            Negotiate* n = new Negotiate(this, this->getPlayerByID(pID2));
            OrderList.push_back(*n);
            flag = true;
            break;
        }
        default: {
            cout << "invild input, try again!\n\n" << endl;

        }
        }
    }
};
vector<Territory> CheaterPlayerStrategy::toAttack(const string& s) {
    vector<int> attacks = parseStringToInt(s);
   

        for (int i = 0; i < Map::worldMap.territories.size(); i++) {
            string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
            string territoryName = Map::worldMap.territories[i]->getTName();
            int id = Map::worldMap.territories[i]->tID;
            if (territoryPlayer != (playerName)) {
                cout << "Territory: " << territoryName << ", owned by " << territoryPlayer << " id: " << id << endl;
            }

            toAttacklist.push_back(id);
        }

        
    

    return toAttacklist;
};
vector<Territory> CheaterPlayerStrategy::todenfend(const string& s{
         vector<int> defends = parseStringToInt(s);
         for (auto i : defends) {
             todefendlist.push_back(i);
             cout << "\nYou selected: " << Map::worldMap.territories[i - 1]->getTName();
         }
         return todefendlist;
    };
