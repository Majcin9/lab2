#include <iostream>
#include <string>
#define MAX_PLAYERS 10
#define MAX_BOARD_SIZE 100

using namespace std;

typedef struct Player {
 int position;
 int cash;
 int in_jail;
 int moved;
 string name;
 int tried_to_end;
 int in_workhouse;
} Pl;

typedef struct Field {
 string owner;
 int cost;
 string name;
 string type;
 string deedOwner;
}Fi;

int main() {
  int prebuy_phase = 0;
 int nPlayers = 2;
 int actualPlayer = 0;
 int BOARD_SIZE = 11;
 Pl players[MAX_PLAYERS];
 Fi fields[MAX_BOARD_SIZE];
 string name_template = "P0";
 for (int i =0;i<nPlayers;i++) {
  const char player_number = (char)i + '0';
  name_template[1] = player_number;
  players[i].position = 0;
  players[i].cash = 200;
  players[i].moved = 0;
  players[i].name = name_template;
  players[i].tried_to_end = 0;
  players[i].in_workhouse = 0;
 }

 for (int i=0;i<BOARD_SIZE;i++) {
  fields[i].owner = "NONE";
  fields[i].cost =0;
  fields[i].deedOwner = "NONE";
 }
 fields[0].type = "START";
 fields[1].type = "PROPERTY";
 fields[2].type = "PROPERTY";
 fields[3].type = "PROPERTY";
 fields[4].type = "WORKSHOP";
 fields[5].type = "UTILITY";
 fields[6].type = "TRAIN";
 fields[7].type = "JAIL";
 fields[8].type = "SHELTER";
 fields[9].type = "CHANCE";
 fields[10].type = "TAXES";

 fields[0].name = "START";
 fields[1].cost = 50, fields[1].name = "A1";
 fields[2].cost = 80, fields[2].name = "A2";
 fields[3].cost = 100, fields[3].name = "A3";
 fields[4].name = "WORKHOUSE";
 fields[5].cost = 50, fields[5].name = "UTILITY 1";
 fields[6].cost = 50, fields[6].name = "TRAIN 1";
 fields[7].name = "JAIL";
 fields[8].name = "SHELTER";
 fields[9].name = "CHANCE";
 fields[10].name = "TAXES";

 string s;
 while(cin >> s)
 {
  if(s == "MOVE") {
    int argument =0;
    cin >> argument;
   if (players[actualPlayer].moved == 1) {
    cout <<players[actualPlayer].name << " MOVED ALREADY\n";
   }
   else if(prebuy_phase){
    cout << "NOT POSSIBLE - ONLY BUYING OF PROPERTIES WITH DEEDS POSSIBLE\n";
   }
   else {
    int argument2 = 0;
    int shelter_pos = 8;
    for (int i =0;i<BOARD_SIZE;i++)
      if (fields[i].type == "SHELTER")
        shelter_pos = i;
    if (cin.peek() == ' ' && players[actualPlayer].in_jail == 1) {
     cin >> argument2;
    }
    if (argument > 6 || argument < 1) {
     cout << players[actualPlayer].name << " ERROR: IMPOSSIBLE DICE SIZE\n";
    }
    else{
      if (players[actualPlayer].in_workhouse){
        players[actualPlayer].cash+=argument;
        if (players[actualPlayer].cash>0){
          cout << players[actualPlayer].name << " YOUR DEBTS ARE PAID, YOU ARE MOVED TO NEAREST SHELTER\n";
          players[actualPlayer].in_workhouse = 0;
          players[actualPlayer].position = shelter_pos;
        }
        else {
          cout << players[actualPlayer].name << " STILL IN WORKHOUSE \n";
        }
      }
      else if (fields[(players[actualPlayer].position+argument)].type == "JAIL") {
        cout << players[actualPlayer].name << " WELCOME TO JAIL \n";
        players[actualPlayer].in_jail = 1;
       int jail_pos = 0;
        for (int i = 0;i<BOARD_SIZE;i++)
         if (fields[i].type == "JAIL")
          jail_pos = i;
        players[actualPlayer].position = jail_pos;

      }

      else if (players[actualPlayer].in_jail != 1) {
       if (players[actualPlayer].position+argument >= BOARD_SIZE)
        players[actualPlayer].cash += 100;
       players[actualPlayer].position = (players[actualPlayer].position + argument) % BOARD_SIZE;
      }
      else {
       if (argument == argument2) {
        players[actualPlayer].position = shelter_pos;
        cout  << players[actualPlayer].name << " SEE YOU NEXT TIME \n";
       }
       else
        cout << players[actualPlayer].name << " STILL IN GAOL \n";
     }

     if (fields[players[actualPlayer].position].name == "JAIL") {
      players[actualPlayer].in_jail = 1;

     }
     else {
       int owner_index = -1;
       for (int i = 0;i<nPlayers;i++){
         if (fields[players[actualPlayer].position].owner == players[i].name)
           owner_index = i;
       }
      if ((owner_index != actualPlayer) && fields[players[actualPlayer].position].owner != "NONE") {
       if (players[actualPlayer].cash >= (fields[players[actualPlayer].position].cost/2)) {
        players[actualPlayer].cash -= (fields[players[actualPlayer].position].cost/2);
        players[owner_index].cash+=fields[players[actualPlayer].position].cost/2; //lol
       }
       else {
        players[owner_index].cash+=fields[players[actualPlayer].position].cost/2;
        players[actualPlayer].cash -=fields[players[actualPlayer].position].cost/2;
        if (players[actualPlayer].cash<0)
          cout << players[actualPlayer].name << " YOU HAVE DEBT. SELL SOMETHING OR YOU GO INTO WORKHOUSE.\n";
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
    for (int i = 0;i<nPlayers;i++) {
     cout << players[i].name << ": "<<players[i].position<<" , "<< players[i].cash << "$ | ";
    }
    cout << "\n";
   }
   else  if(argument == 1)
   {
      cout << "Tile no., Tile Name, Owner Name, Base Price, Land Rent, Players Standing \n";
      for (int i = 0;i<BOARD_SIZE;i++){

        int howmany = 0;

        for (int j = 0;j<nPlayers;j++)
          if (players[j].position == i)
            howmany +=j+1;
        if (fields[i].deedOwner != "NONE"){

        }
        cout << i << " " << fields[i].name << " ";
        if ((fields[i].owner == "NONE") && ((fields[i].deedOwner == "NONE") || (!prebuy_phase)))
          cout << "- ";
        else if (fields[i].owner != "NONE"){ 
          cout << fields[i].owner << " ";
        }
        else{
          cout << "(" << fields[i].deedOwner << ") ";
        }
        if (fields[i].cost > 0)
          cout << fields[i].cost << " " << fields[i].cost/2 << " ";
        else 
          cout << "- - ";

        cout << howmany << "\n";
      }
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
  else if (s == "ENABLE_PREBUYING"){
    prebuy_phase = 1;
  }
   else if( s == "BUY")
   {
    int price = fields[players[actualPlayer].position].cost;
    if (prebuy_phase){
      int pole;
      cin >> pole;
      if ((fields[pole-1].deedOwner == players[actualPlayer].name) && (players[actualPlayer].cash>=fields[pole-1].cost)){
        fields[pole-1].owner = players[actualPlayer].name;
        players[actualPlayer].cash-=fields[pole-1].cost;
      }
      else if (players[actualPlayer].cash<fields[pole-1].cost){
        cout << players[actualPlayer].name << " NOT ENOUGH MONEY\n";
      }
      else{
        cout << players[actualPlayer].name << " NO DEED\n";
      }
    }
    else{
    int property = players[actualPlayer].position;
    int winner = actualPlayer;
    if (price>0 && fields[property].owner == "NONE") {
     while(true) {
      string command;
      cin >> command;
      if(command == "END"){
       players[winner].cash-=price;
       fields[property].owner = players[winner].name;
       cout << players[winner].name << " WON THE AUCTION\n";
       if (players[winner].cash <0)
        cout << players[winner].name << " YOU HAVE DEBT. SELL SOMETHING OR YOU GO INTO WORKHOUSE\n";
       break;
      }
      if(command == "BID"){
       int player;
       int bidValue;
       cin >> player;
       cin >> bidValue;
       if (bidValue < fields[players[actualPlayer].position].cost){
        cout << players[player].name << " CANNOT BID FOR LESS THAN INITIAL PRICE\n";
       }
       else if (price == fields[players[actualPlayer].position].cost) {
        if (bidValue>=price) {
         price = bidValue;
         winner = player;
        }
       }
       else if (bidValue <= price) {
        cout << players[player].name << " CANNOT BID FOR LESS OR EQUAL\n";
       }
       else {
        if (bidValue>price) {
         price = bidValue;
         winner = player;
        }
       }
      }
     }
    }
    }
   }
  else if (s =="ADD_TILE") {
   string t,n;
   cin >> t >> n;
   BOARD_SIZE++;
   fields[BOARD_SIZE-1].type = t;
   fields[BOARD_SIZE-1].name= n;
   if ((fields[BOARD_SIZE-1].type == "PROPERTY") || (fields[BOARD_SIZE-1].type == "UTILITY") || (fields[BOARD_SIZE-1].type == "TRAIN")) {
    int price;
    string deed,owner;
    cin >> price >> deed >> owner;
    fields[BOARD_SIZE-1].cost = price;
    fields[BOARD_SIZE-1].deedOwner = deed;
    fields[BOARD_SIZE-1].owner = owner;
   }
  }
  else if (s == "NULL_BOARD_AND_PLAYERS") {
   for (int i =0;i<nPlayers;i++) {
    players[i].cash =0;
    players[i].name="";
    players[i].in_jail=0;
    players[i].position =0;
    players[i].moved=0;
   }
   for (int i =0;i<BOARD_SIZE;i++) {
    fields[i].owner ="NONE";
    fields[i].name="";
    fields[i].cost=0;
    fields[i].deedOwner = "NONE";
   }
   nPlayers = 0;
   BOARD_SIZE = 0;
  }
  else if (s == "ADD_PLAYER") {
   int i, x;
   string n;
   cin >> i >> x >> n;
   nPlayers+=1;
   players[nPlayers-1].position = i;
   players[nPlayers-1].cash = x;
   if (n.length()<=10)
    players[nPlayers-1].name = n;
  }
  else if( s == "#") {
   string a;
   getline(cin, a);
   }
  else if( s == "SELL"){
   int property_num;
   cin >> property_num;
   if (fields[property_num].owner != players[actualPlayer].name) {
    cout << players[actualPlayer].name << " SELLING UNOWNED PROPERTY\n";
   }
   else{
      fields[property_num].owner = "NONE";
      players[actualPlayer].cash += (fields[property_num].cost/2);
     }

   }
  else if( s== "END_TURN"){
    if (players[actualPlayer].cash<0){
      if (players[actualPlayer].tried_to_end == 1){
        int work_pos = 0;
        for (int i = 0;i<BOARD_SIZE;i++)
          if (fields[i].type == "WORKSHOP")
            work_pos = i;
        if (players[actualPlayer].in_workhouse != 1)
         cout << players[actualPlayer].name << " DUE TO YOUR DEBTS YOU ARE FORCED INTO CLOSEST WORKHOUSE.\n";
        players[actualPlayer].position = work_pos;
        players[actualPlayer].in_workhouse = 1;
        players[actualPlayer].moved =0;
        actualPlayer = (++actualPlayer) % nPlayers;
        
      }
      else {
      players[actualPlayer].tried_to_end+=1;
      cout << players[actualPlayer].name << " YOU HAVE DEBTS. YOU CANNOT END TURN. YOU HAVE TO SELL SOMETHING.\n";
      }
    }
    else { 
      if ((actualPlayer == nPlayers-1) && (prebuy_phase))
        prebuy_phase = 0;
      players[actualPlayer].moved =0;
      actualPlayer = (++actualPlayer) % nPlayers;
    }
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
