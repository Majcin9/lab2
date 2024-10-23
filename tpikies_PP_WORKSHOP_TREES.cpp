#include <iostream>
#include <string>
#include <math.h>

using namespace std;

int main(){
 float t1y, t1x,t1r,t1h;
 bool t1active = false;

 float t2y,t2x,t2r,t2h;
 bool t2active = false;

 float r_incr,h_incr;

 while(true)
 {
  string command;
  cin >> command;
  cout << command;
  if(command == "ADD"){
   int id;
   cin >> id;
   if(id == 1){
    if(t1active){
     cout << "Tree already active"<<endl;
     continue;
    }
    cin >> t1y >> t1x >> t1r >> t1h;
    t1active = true;
   }
   if(id == 2){
    if(t2active){
     cout << "Tree already active"<<endl;
     continue;
    }
    cin >> t2y;
    cin >> t2x;
    cin >> t2r;
    cin >> t2h;
    t2active = true;
   }
  }
  else if(command == "MDL"){
   int mode;
   cin >> mode;
   if(mode == 0){
    cin >> r_incr >> h_incr;
   }
  }
  else if (command == "REM") {
   int id;
   cin >> id;
   if (id == 1) {
    t1active = false;
   } else if (id == 2) {
    t2active = false;
   }
  } else if (command == "PRT") {
   int mode;
   cin >> mode;
   if (mode == 3) {
   } else {
    cout << "Trees:" << endl;
    cout << "1 at " << t1y << ", " << t1x << " r=" << t1r << " h=" << t1h << endl;
    if (mode == 2) {
     cout << " Interfering with: ";
     if (abs(t1y - t2y) * abs(t1y - t2y) + abs(t1x - t2x) * abs(t1x - t2x) <= (t1r + t2r) * (t1r + t2r)) {
      cout << "2" << endl;;
      float shiftx = t2x - t1x;
      float shifty = t2y - t1y;
      float r = sqrt(shiftx * shiftx + shifty * shifty);
      float shiftx2 = shiftx / r;
      float shifty2 = shifty / r;

      float arccos = acos(shifty2);

      float prevangle = -22.5 / 180.0 * 3.1415;

      int sector = -1;
      for (int i = 0; i < 8; i++) {
       float angle = prevangle + 45.0 / 180.0 * 3.1415;
       if (arccos >= prevangle && arccos <= angle) {
        sector = i;
       }
       prevangle = angle;
      }
      if (sector == -1) {
       cout << "???";
       return -1;
      }

      if (sector == -1) {
       cout << "ERROR" << endl;
       return -1;
      }
     }
     cout << endl;
    }
    cout << "2 at " << t2y << ", " << t2x << " r=" << t2r << " h=" << t2h << endl;
    if (mode == 2) {
     cout << " Interfering with: ";
     if (abs(t1y - t2y) * abs(t1y - t2y) + abs(t1x - t2x) * abs(t1x - t2x) <= (t1r + t2r) * (t1r + t2r)) {
      cout << "1";
     }
     cout << endl;
    }
   }
  } else if (command == "ADV") {
   int nepochs;
   cin >> nepochs;
   t1r += nepochs * r_incr;
   t2r += nepochs * r_incr;

   t1h += nepochs * h_incr;
   t2h += nepochs * h_incr;
  } else if (command == "END") {
   break;
  } else {
   cout << "Unknown command" << endl;
  }
 }
}