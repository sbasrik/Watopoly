#include "nonProperty.h"
#include <iostream>
#include <map>
using namespace std;

void NonProperty::changeNumOfCups(int amount){
    numOfCups+=amount;
}

int NonProperty::getNumOfCups(){
    return numOfCups;
}

void NonProperty::collectOsap(Player &p){
    p.setMoney(p.getMoney() + OSAP_MONEY);
}

/*static void NonProperty::DCTimsLine(Player &p){
 }*/

void NonProperty::goToTims(Player &p){
    p.setPosition(DC_TIMS_LINE_POSITION);
}

/*static void NonProperty::gooseNesting(Player &p){
 }*/

void NonProperty::tuition(Player &p){
    int num=0;
    
    cout<<"You are on Tuition square. You have 2 options. Enter the corresponding number to choose:"<<endl;
    cout<<"1: Pay $300 tuition."<<endl;
    cout<<"2: Pay %10 of your total worth"<<endl;
    
    cin>>num;
    
    if(num==1)
        p.setMoney(p.getMoney()-TUITION);
    else
        if(num==2)
            p.setMoney(p.getMoney()-(p.totalWorth()/10));
        else{
            cout<<"You entered a wrong character!"<<endl<<endl;
            NonProperty::tuition(p);
        }
}

void NonProperty::coopFee(Player &p){
    p.setMoney(p.getMoney()-COOP_FEE);
}

void NonProperty::slc(Player &p){
    
    if(NonProperty::getNumOfCups()<4 && rand()%100==0){
        p.changeCups(1);
        NonProperty::changeNumOfCups(1);
        return;
    }
    
    int r = rand()%24;
    int newPos = -1;
    
    if(r>=0 && r<=2){
        newPos = (p.getPosition()-3)%NUM_OF_SQUARES;
        cout<<"You have moved 3 squares back and landed on ";
    }
    
    if(r>=3 && r<=6){
        newPos = ( (p.getPosition()-2)%NUM_OF_SQUARES );
        cout<<"You have moved 2 squares back and landed on ";
    }
    
    if(r>=7 && r<=10){
        newPos = ( (p.getPosition()-1)%NUM_OF_SQUARES );
        cout<<"You have moved 1 square back and landed on ";
    }
    
    if(r>=11 && r<=13){
        newPos = ( (p.getPosition()+1)%NUM_OF_SQUARES );
        cout<<"You have moved 1 square forward and landed on ";
    }
    
    if(r>=14 && r<=17){
        newPos = ( (p.getPosition()+2)%NUM_OF_SQUARES );
        cout<<"You have moved 2 squares forward and landed on ";
    }
    
    if(r>=18 && r<=21){
        newPos = ( (p.getPosition()+3)%NUM_OF_SQUARES );
        cout<<"You have moved 3 squares forward and landed on ";
    }
    
    if(r==22){
        newPos = 10;
        cout<<"You have been moved to ";
    }
    
    if(r==23){
        newPos = 0;
        cout<<"You have been moved to ";
    }
    
    p.setPosition(newPos);
    cout<<"Position "<<newPos<<endl;

    cout<<"There is a bug honey!"<<endl;
    
    return;
}


void NonProperty::needlesHall(Player &p){
    
    if(numOfCups<4 && rand()%100==0){
        p.changeCups(1);
        NonProperty::changeNumOfCups(1);
        return;
    }
    
    int r = rand()%18;
    int change = 0;
    
    if( r>=0 && r<=0  )      change = -200;
    if( r>=1 && r<=2  )      change = -100;
    if( r>=3 && r<=5  )      change = -50;
    if( r>=6 && r<=11 )      change = 25;
    if( r>=12 && r<=14 )     change = 50;
    if( r>=15 && r<=16 )     change = 100;
    if( r>=17 && r<=17 )     change = 200;
    
    p.setMoney(p.getMoney()+change);
    
    if(change>0)
        cout<<"Congratulations! You have gained $"<<change<<" in Needles Hall because you held the door for others."<<endl;
    else
        cout<<"Bad news... You have lost $"<<change<<" in Needles Hall because you did not say 'thank you' to the person holding the door for you"<<endl;
    
    return;
}
