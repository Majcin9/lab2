#include <iostream>
#include <string>
#define MAX_PLAYERS 10
#define BOARD_SIZE 11

using namespace std;

typedef struct Player {
 int position;
 int cash;
 int in_jail;
 int moved;
} Pl;

typedef struct Field {
 int owner;
 int cost;
 string name;
}Fi;

int main() {
 int nPlayers = 2;
 int actualPlayer = 0;

 Pl players[MAX_PLAYERS];
 Fi fields[BOARD_SIZE];



 for (int i =0;i<nPlayers;i++) {
  players[i].position = 0;
  players[i].cash = 200;
  players[i].moved = 0;
 }

 for (int i=0;i<BOARD_SIZE;i++) {
  fields[i].owner = -1;
  fields[i].cost =0;
 }
 fields[7].name = "JAIL";
 fields[8].name = "SHELTER";

 fields[1].cost = 50, fields[1].name = "A1";
 fields[2].cost = 80, fields[2].name = "A2";
 fields[3].cost = 100, fields[3].name = "A3";
 fields[5].cost = 50, fields[5].name = "U1";
 fields[6].cost = 50, fields[6].name = "T1";

 string s;
 while(cin >> s)
 {
  if(s == "MOVE") {
    int argument, argument2 =0;
    cin >> argument;
   if (players[actualPlayer].moved == 1) {
    cout << "ERROR: PLAYER P" << actualPlayer << " MOVED ALREADY\n";
   }
   else {
    if (cin.peek() == ' ' && players[actualPlayer].in_jail == 1) {
     cin >> argument2;
    }
    if (argument > 6 || argument < 1) {
     cout << "ERROR: IMPOSSIBLE DICE SIZE\n";
    }
    else{

     if (fields[(players[actualPlayer].position+argument)].name == "JAIL") {
      cout << "WELCOME TO JAIL P" << actualPlayer << "\n";
     }

     if (players[actualPlayer].in_jail != 1) {
      if (players[actualPlayer].position+argument >= BOARD_SIZE)
       players[actualPlayer].cash += 100;
      players[actualPlayer].position = (players[actualPlayer].position + argument) % BOARD_SIZE;
     }
     else {
      if (argument == argument2) {
       players[actualPlayer].position +=1;
       cout << "SEE YOU NEXT TIME P" << actualPlayer << "\n";
      }
      else
       cout << "STILL IN GAOL P" << actualPlayer << "\n";
     }

     if (fields[players[actualPlayer].position].name == "JAIL") {
      players[actualPlayer].in_jail = 1;

     }
     else {
      if ((fields[players[actualPlayer].position].owner != actualPlayer) && fields[players[actualPlayer].position].owner != -1) {
       if (players[actualPlayer].cash >= (fields[players[actualPlayer].position].cost/2)) {
        players[actualPlayer].cash -= (fields[players[actualPlayer].position].cost/2);
        players[fields[players[actualPlayer].position].owner].cash+=fields[players[actualPlayer].position].cost/2; //lol
       }
       else {
        players[fields[players[actualPlayer].position].owner].cash+=players[actualPlayer].cash;
        players[actualPlayer].cash = 0;
       }
      }
     }
     players[actualPlayer].moved =1;
    }
   }
  }
  else if( s == "PRINT")
  {
   int argument;
   cin >> argument;
   if(argument == 0)
   {
    cout << "PLAYER_ACTING: "<< actualPlayer << " ||| ";
    string whichp = "P0: ";
    for (int i = 0;i<nPlayers;i++) {
     const char c = i + '0';
     whichp[1] = c;
     cout << whichp <<players[i].position<<" , "<< players[i].cash << "$ | ";
    }
    cout << "\n";
   }
   else  if(argument == 1)
   {

   }
  }
  else if(s == "SET_N_PLAYERS") {
   cin >> nPlayers;
  }
  else if(s == "SET_PLAYER_POS") {
   int who,where;
   cin >> who >> where;
   if ((who >=0 && who <=nPlayers) && (where >=0 && where <= BOARD_SIZE)) {
    players[who].position = where;
   }
  }
  else if (s == "SET_PLAYER_TURN") {
   int who;
   cin >> who;
   if (who >=0 && who <=nPlayers) {
    actualPlayer = who;
   }
  }
  else if (s == "SET_PLAYER_ACCOUNT") {
   int who,how_much;
   cin >> who >> how_much;
   if (who >=0 && who <=nPlayers) {
    players[who].cash=how_much;
   }
  }

   else if( s == "BUY")
   {
    // Check whose turn it is, check if the property is not occupied and sellable
    // The rules of selling are as follows:
    // There is an auction, the bids are specified in the form Px y, which means that the player x offers y for the property.
    // The initial price is the worth of the property.

    int price = fields[players[actualPlayer].position].cost;
    int property = players[actualPlayer].position;
    int winner = actualPlayer;
    if (price>0 && fields[property].owner == -1) {
     while(true)
     {
      string command;
      cin >> command;
      if(command == "END"){
       players[winner].cash-=price;
       fields[property].owner = winner;
       cout << "P" << winner << " WON THE AUCTION\n";
       break;
      }
      if(command == "BID"){
       int player;
       int bidValue;
       cin >> player;
       cin >> bidValue;
       if (players[player].cash>=bidValue && ((bidValue>price) || (bidValue>=fields[players[actualPlayer].position].cost))) {
        price = bidValue;
        winner = player;
       }
       else {
        cout << "CANNOT BID FOR LESS\n";
       }
      }
     }
    }
   }
  else if( s == "#") {
   string a,b,c;
   cin >> a >> b >> c;
   }
  else if( s == "SELL"){
   int property_num;
   cin >> property_num;
   if (fields[property_num].owner != actualPlayer) {
    cout << "ERROR: P" << actualPlayer << " SELLING UNOWNED PROPERTY\n";
   }
   else{
      fields[property_num].owner = -1;
      players[actualPlayer].cash += (fields[property_num].cost/2);
     }

   }
  else if( s== "END_TURN"){
    players[actualPlayer].moved =0;
    actualPlayer = (++actualPlayer) % nPlayers;
   }
  else if (s=="END_GAME") {
   return -1;
  }
  else
   {
    cout << "UNKNOWN COMMAND: "<<s;
    cout.flush();
    return -1;
   }
  }
 return 0;
 }
