#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "board.h"
#include "gym.h"
#include "academic.h"
#include "residences.h"

using namespace std;


Board::Board(bool load, bool test, string filename) {
    test = test;
    turn = doubleCount = rollCount = 0;
    
    // useful variables
    int input;
    int cost;
    int position;
    int improveCost;
    int tuition[6];
    int indicator;
    int improveCount;
    string name;
    string block;
    string owner;
    string skip;
    char piece;
    bool playerInit = false;
    const int defaultImprove = 0;
    string defaultOwner = "BANK";
    ifstream file("properties.txt");
    
    
    if (load) {
        ifstream in(filename);
        
        
        // initialize player
        in >> numPlayer;
        for (int i = 0; i < numPlayer; ++i) {
            in >> name >> piece >> input;
            players.emplace_back(Player(name,piece));
            players.at(i).setTims(input);
            in >> input;
            players.at(i).setMoney(input);
            in >> input;
            players.at(i).setPosition(input);
        }
        
        // initialize buildings
        for (int i = 0; i < 30; ++i) {
            file >> indicator;
            if (indicator == 0)  {
                file >> name >> cost >> position >> improveCost >> block;
                in >> skip >> owner >> improveCount;
                for (int k = 0; k < 6; ++k) {
                    file >> tuition[k];
                }
                buildings.insert(pair<int, Building*>(position, new Academic(name, cost, position, improveCost, block, tuition, improveCount, owner)));
            } else if (indicator == 1) {
                file >> name >> cost >> position;
                buildings.insert(pair<int, Building*>(position, new Gym(name, cost, position, defaultOwner)));
            } else if (indicator == 2) {
                file >> name >> input >> cost >> position;
                buildings.insert(pair<int, Building*>(position, new Residence(name, input, cost, position, defaultOwner)));
            }
        }
        
    } else {
        
        // initialize player
        
        cout << "How many players are there?" << endl;
        cin >> numPlayer;
        for (int i = 0; i < numPlayer; ++i) {
            cout << "Player name?" << endl;
            string name;
            cin >> name;
            cout << "Player character?" << endl;
            char piece;
            cin >> piece;
            players.emplace_back(Player(name, piece));
        }
        
        // initialize buildings
        for (int i = 0; i < 30; ++i) {
            file >> indicator;
            if (indicator == 0)  {
                file >> name >> cost >> position >> improveCost >> block;
                for (int k = 0; k < 6; ++k) {
                    file >> tuition[k];
                }
                buildings.insert(pair<int, Building*>(position, new Academic(name, cost, position, improveCost, block, tuition, defaultImprove, defaultOwner)));
            } else if (indicator == 1) {
                file >> name >> cost >> position;
                buildings.insert(pair<int, Building*>(position, new Gym(name, cost, position, defaultOwner)));
            } else if (indicator == 2) {
                file >> name >> input >> cost >> position;
                buildings.insert(pair<int, Building*>(position, new Residence(name, input, cost, position, defaultOwner)));
            }
        }
    }
    
}


void Board::move(int dice1, int dice2) {
    int newPos = players.at(turn).getPosition() + dice1 + dice2;
    // moves player
    if(newPos >= 40){
        players.at(turn).setMoney(players.at(turn).getMoney() + 200);
        newPos-=40;
    }
    
    players.at(turn).setPosition(newPos);
    
    // hardcode private function bool isBuilding()
    // if property
    if (isBuilding(newPos)) {
        if (buildings.find(newPos)->second->getOwner() == "BANK") {
            std::cout << "Would you like to buy " << buildings.find(newPos)->second->getName() << "?" << std::endl;
            this->buy(newPos);
        } else {
            this->payRent(newPos);
        }
    } else {
        this->runNonProp(newPos); // needs to be coded
    }
}

void Board::roll(int dice1, int dice2) {
    
    // checks testing mode
    if (!test) {
        std::cout << "Error: the game is not in testing mode." << std::endl;
        return;
    }
    if (rollCount == 1 || doubleCount == 3) return;
    
    srand(time(NULL));
    
    if (dice1 == dice2) {
        ++doubleCount;
        rollCount = 0;
    }
    
    move(dice1, dice2);
}

void Board::roll() {
    // assuming player vector is called players
    // assuming player index says information about turns
    
    
    // if already rolled
    if (rollCount == 1 || doubleCount == 3) return;
    
    // if not done in main
    srand (time(NULL));
    
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;
    
    if (dice1 == dice2) {
        ++doubleCount;
        rollCount = 0;
    }
    
    // move
    move(dice1, dice2);
    
}

void Board::next() {
    
    // check if player paid rent
    if (rollCount != 1 && doubleCount != 3) {
        std::cout << "You can still roll" << std::endl;
        return;
    }
    std::cout << players.at(turn).getName() << "'s turn ended." << std::endl;
    if (turn >= numPlayer) {
        turn -= numPlayer;
    }
    ++turn;
    doubleCount = 0;
    rollCount = 0;
    std::cout << "It is now " << players.at(turn).getName() << "'s turn. " << std::endl;
}

int Board::getBuildingPos(std::string name) {
    for (auto it: buildings) {
        if (it.second->getName() == name)
            return it.second->getPosition();
    }
    return -1;
}

bool Board::isBuilding(int pos) {
    return buildings.count(pos);
}

// requires fix
void Board::buy(int pos) {
    // try...catch
    std::string ans;
    while (true) {
        std::cin >> ans;
        if (ans == "Yes" && canBuy(players.at(turn), buildings.find(pos)->second->getPrice())) {
            buildings.find(pos)->second->setOwner(players.at(turn).getName());
            players.at(turn).setMoney(players.at(turn).getMoney() -
                                      buildings.find(pos)->second->getPrice());
            break;
        } else if (ans == "Yes") {
            cout << "You don't have enough money to buy this property.\n";
            break;
        } else if (ans == "No") {
            this->auction(pos);
            break;
        } else if (ans == "Mortgage") {
            string building;
            // this->mortage(building);
        } else {
            std::cout << "Please enter Yes or No or Mortgage\n";
        }
    }
}


void Board::auction(int pos) {
    std::cout << "Auction has started! First player gets to bet first.\n";
    std::vector<int> inAuction;
    int currentBid = 0;
    int tempTurn = 0;
    int tempBid = 0;
    std::string withDraw; // keeps track of who withdrew
    std::istringstream convert;
    
    // initialize inAuction, vector of players still in the aution
    int size = players.size();
    for (int i = 0; i < size; ++i) {
        inAuction.emplace_back(i);
    }
    
    std::cout << "Auction for " << buildings.find(pos)->second->getName() << " has begun.\n";
    // run the auction
    while (inAuction.size() != 1) {
        std::cout << "Player: " << players.at(inAuction.at(tempTurn)).getName() << std::endl;
        std::cout << "Please enter a bid or withdraw\n";
        std::cin >> withDraw;
        
        // if input is string
        if (withDraw == "wd") {
            //remove player from inAuction
            inAuction.erase(inAuction.begin() + tempTurn);
            if (tempTurn >= inAuction.size()) tempTurn = 0;
            continue;
        } else if (withDraw[0] < 48 || withDraw[0] > 57) {
            std::cout << "Please enter a valid bid or command.\n";
            continue;
        }
        
        // if input is integer
        convert.clear();
        convert.str(withDraw);
        convert >> tempBid;
        if (tempBid > currentBid) {
            std::cout << "A new bid has been set to " << tempBid << std::endl;
            currentBid = tempBid;
            ++tempTurn;
            if (tempTurn >= inAuction.size()) tempTurn = 0;
        } else {
            std::cout << "Please enter a bid that is higher than current bid.\n";
        }
    }
    
    // take out money, give building to player
    int playerInd = inAuction.at(0);
    std::cout << "Player: " << players.at(playerInd).getName() << " wins this auction.\n";
    players.at(inAuction.at(0)).setMoney(players.at(playerInd).getMoney() - currentBid);
    buildings.find(pos)->second->setOwner(players.at(playerInd).getName());
}


void Board::payRent(int position) {
    
    // checks if player can rent
    bool noMoney = true;
    while (noMoney) {
        bool mortgage = false;
        if (players.at(turn).getMoney() < buildings.find(position)->second->getRent()) {
            cout << "You don't have enough money. Would you like to mortgage or trade?\n";
            mortgage = true;
        } else {
            noMoney = false;
        }
        
        while (mortgage) {
            string ans;
            string ans2;
            string ans3;
            cin >> ans;
            if (ans == "mortgage") {
                cin >> ans;
                int pos = getBuildingPos(ans);
                if (pos == -1) {
                    cout << "That is not a building\n";
                } else if (players.at(turn).getName() != buildings.find(pos)->second->getOwner()) {
                    cout << "That is not your building.\n";
                } else {
                    mortgage(buildings.find(pos)->second->getName());
                }
            } else if (ans = "trade") {
                cin >> ans;
                cin >> ans2;
                cin >> ans3;
                //trade(ans, ans2, ans3);
            } else if (ans == "none") {
                return;
            } else {
                cout << "Please enter either: mortgage <building>, trade <player> <give> <receive>, none\n";
            }
        }
    }
    
    // paying process
    players.at(turn).setMoney(players.at(turn).getMoney() - buildings.find(position)->second->getRent());
    int playerIndex = this->findPlayer(buildings.find(position)->second->getOwner());
    players.at(playerIndex).setMoney(players.at(playerIndex).getMoney() + buildings.find(position)->second->getRent());
    // switch pay rent to true for player
}


int Board::findPlayer(std::string name) {
    int len = players.size();
    for (int i = 0; i < len; ++i) {
        if (players.at(i).getName() == name) return i;
    }
    return -1;
}

void Board::improve(string building,string action){
    int pos = getBuildingPos(building);
    if(pos == -1) {
        cout << "There is no such building. Please try again\n";
        return;
    }
    if (buildings.find(pos)->second->getType() != "ACADEMIC") {
        cout << "You cannot add improvements to this building\n";
        return;
    }
    while (true) {
        if(action=="buy") {
            if (!static_cast<Academic*>(buildings.find(pos)->second)->addImprovement()) {
                cout << "You already have maximum number of improvements\n";
            } else {
                players.at(turn).setMoney(players.at(turn).getMoney()
                                          - static_cast<Academic*>(buildings.find(pos)->second)->getImproveCost());
            }
            break;
        } // needs fix
        else if(action=="sell") {
            if (!static_cast<Academic*>(buildings.find(pos)->second)->removeImprovement()) {
                cout << "You have no improvements.\n";
            } else {
                players.at(turn).setMoney(players.at(turn).getMoney()
                                          + static_cast<Academic*>(buildings.find(pos)->second)->getImproveCost());
            }
            break;
        } // needs fix
        else {
            cout << "Please enter either 'buy' or 'sell'\n";
        }
    }
    
}


//prints all the assets of the given player
void Board::assets(Player &p){
    vector<int> assets = p.getAssets();
    cout << p.getName() << " has $" << p.getMoney() << " and owns the buildings:" << endl;
    for(int a:assets){
        cout << a << endl;
    }
    cout << "and " << p.getResNum() << " residences." << endl;
}


// saves the data to given filename as described in watopoly.pdf
// fix data according to datat type
void Board::save(const string filename){
    ofstream out;
    out.open(filename);
    out << players.size() << endl;
    for(auto p:players){
        cout << p.getName() << " " << p.getPiece() << " " << p.getTims() << " " << p.getMoney()
        << " " << p.getPosition();
    }
    for(auto b:buildings){
        if (b.second->getType() == "ACADEMIC") {
            cout << b.second->getName() << " " << b.second->getOwner() << " " << static_cast<Academic*>(b.second)->getImproveCount() << endl;
        } else {
            cout << b.second->getName() << " " << b.second->getOwner() << endl;
        }
    }
}


//goes through the players vector to print their assets.
void Board::all(){
    for(Player p:players){
        assets(p);
    }
}

void Board::runNonProp(int position) {
    switch(position) {
        case 2: case 17: case 33:
            slc(players.at(turn));
            break;
        case 4:
            tuition(players.at(turn));
            break;
        case 7: case 22:
            needlesHall(players.at(turn));
            break;
        case 20:
            gooseNesting(players.at(turn));
            break;
        case 30:
            goToTims(players.at(turn));
        default: break;
    }
}

bool Board::canBuy(Player &p, int cost) {
    return p.getMoney() >= cost;
}
