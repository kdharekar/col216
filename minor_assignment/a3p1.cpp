#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const std::string WHITESPACE = " \n\r\t\f\v";
int registers[32];

void decToHex(int d){

  char ar[8];
  for(int i=0;i <8;i++){
      ar[i]=48;
  }

  int i = 0;
  while(d != 0){

    int r = d%16;

    if(r < 10){
      int t = r + 48;
      ar[i] = t;
      i++;
    }else{
      ar[i] = r + 55;
      i++;
    }
    d = d/16;
  }

  if(i==0){cout << ar[i] ;}
  for(int j=i-1;j>=0;j--){
      cout << ar[j];
  }
}

struct instructions{
    string name;
    vector<string> vect ;
    instructions(string arr[]){
        name  = arr[0];
        stringstream check1(arr[1]);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
        vect.push_back(intermediate);
    }}
};
bool isnumber(string val){
      for(int i=0;i<val.length();i++){
          if(isdigit(val[i]) == false){
              return false;
          }
      }
      return true;
}
int main(int argc , char * argv[]){
    string f = argv[1];
    int rad = atoi(argv[2]);
    int cad = atoi(argv[3]);
    vector<struct instructions> instructions;
    int dram[(int)pow(2.0,10.0)][(int)pow(2.0,10.0)] = {0,0} ;  //dra;m memory matrix
    int buffer[(int)pow(2.0,10.0)] = {0};    //row buffer
    int row=-1;
    int up = 0;  //row buffer updates
    int cycle = 1;
    int k =0;   //storing row number where value will be stored or loaded
    int registers[32];
    ifstream file;
    int index  = 0;
    string val="";
    //cout << "hello";
    file.open(f);


    while(getline(file, val)) {
       //if(val == ""){continue;}
         int count = 0;
        string arr[2];
         arr[1]  = "";
        stringstream check1(val);
        string intermediate;
        while(check1>>intermediate){
            if(count==0){
                arr[0] = intermediate;
                count++;
            }
            else{
                arr[1]  = arr[1] + intermediate;
            }
        }
		instructions.push_back(arr);
       // cout << arr[0]<<"\n";
         //cout << arr[1]<<"\n";
	}

    unordered_map<string, int> registermap;
    registermap["$zero"] = 0;
    registermap["$at"] = 1; registermap["$ra"] = 31;
    registermap["$v0"] = 2; registermap["$fp"] = 30;
    registermap["$v1"] = 3; registermap["$sp"] = 29;
    registermap["$a0"] = 4; registermap["$gp"] = 28;
    registermap["$a1"] = 5; registermap["$k1"] = 27;
    registermap["$a2"] = 6; registermap["$k0"] = 26;
    registermap["$a3"] = 7; registermap["$t9"] = 25;
    registermap["$t0"] = 8; registermap["$t8"] = 24;
    registermap["$t1"] = 9; registermap["$s7"] = 23;
    registermap["$t2"] = 10;
    registermap["$t3"] = 11;
    registermap["$t4"] = 12;
    registermap["$t5"] = 13;
    registermap["$t6"] = 14;
    registermap["$t7"] = 15;
    registermap["$s0"] = 16;
    registermap["$s1"] = 17;
    registermap["$s2"] = 18;
    registermap["$s3"] = 19;
    registermap["$s4"] = 20;
    registermap["$s5"] = 21;
    registermap["$s6"] = 22;

    // we have loaded the instructions in vector instructions
    for(int i=0;i<32;i++){
        registers[i] = 0;
    }
    //registers[29] = 65535;
    int PC = 0;
    int filesize = instructions.size();


    int error = 0;
    while(PC<filesize){
        const char *c = instructions.at(PC).name.c_str();


/* add instruction starts */

        if(strcmp("add",c)==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(2)) !=1){
                error = 1;
                break;
            }

            registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] + registers[registermap[vect.at(2)]];

            cout << "\nCycle "<<cycle << ": " <<"add "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

            cycle++;
            PC++;
            cout << "Registers: ";
            for(int i=0;i<32;i++){
                //cout << "aa";
                int k = registers[i];
                decToHex(k) ;
                if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
            }
            cout << "\n";
        }
        else if(strcmp("",c)==0){
            PC++;
            continue;
        }


/* lw instruction starts*/


  else if(strcmp(c,"lw")==0){

            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=2){
                error = 1;
                cout << "hell";
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                cout << "he";
                break;
            }
            //processmap[vect[0]] = 1

            string s =  vect.at(1).c_str();
            string t = "";
            string r = "";
            int i=0;
            while(true){
              if(isdigit(s[i])){
                t = t+s[i]; i++;
              }else {break;}

            }
            int q = stoi(s);

            if(i==s.length()){
               k = q/((int)pow(2.0,10.0));


              if((q)%4!=0){
                cout<<"Error: address value not a factor of 4  at line"<<PC<<endl;
                error=2;
                  break;
              }

              if(row==-1){
                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cycle++;
                cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  int j = dram[k][l];
                  buffer[l] = j;
                }
                cycle += 10;
                up++;
                cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< q%((int)pow(2.0,10.0)) <<" row "<<k <<endl;
                row = k;
              registers[registermap[vect.at(0)]] =  buffer[q%((int)pow(2.0,10.0))]  ;
                cycle += 2;

              }else if(row == k){

                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cycle++;
                cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< q%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
                row = k;
              registers[registermap[vect.at(0)]] =  buffer[q%((int)pow(2.0,10.0))]  ;
                cycle += 2;

              }else{

                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cycle++;
                cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: write back row "<< row <<endl;
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  dram[row][l] = buffer[l];
                }
                cycle += 10;

                cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  buffer[l] = dram[k][l];
                }
                cycle += 10;
                up++;
                cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< q%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
                row = k;
              registers[registermap[vect.at(0)]] =  buffer[q%((int)pow(2.0,10.0))]  ;
                cycle += 2;

              }
            row = k;

            PC++;
            cout << "Registers: ";
            for(int i=0;i<32;i++){
                //cout << "aa";
                int k = registers[i];
                decToHex(k) ;
                if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
            }
            cout << "\n";


          }else{
            r += s.substr(i+1, s.length()-i-2 );
            if(registermap.count(r) !=1){
                error = 1;
                cout<<"hell2";
                break;
            }
            if((q)%4!=0){
              cout<<"Error: offset value not a factor of 4  at line"<<PC<<endl;
              error=2;
                break;
            }

            int  d = q + registers[registermap[r]];

            k = d/((int)pow(2.0,10.0));

            if((d)%4!=0){
              cout<<"Error: address value not a factor of 4 at line"<<PC<<endl;
              error=1;
                break;
            }

            if(row==-1){
              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                int j = dram[k][l];
                buffer[l] = j;
              }
              cycle += 10;
              up++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< d%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
              row = k;
            registers[registermap[vect.at(0)]] =  buffer[d%((int)pow(2.0,10.0))]  ;
              cycle += 2;

            }else if(row == k){

              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< d%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
              row = k;
            registers[registermap[vect.at(0)]] =  buffer[d%((int)pow(2.0,10.0))]  ;
              cycle += 2;

            }else{

              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: write back row "<< row <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                dram[row][l] = buffer[l];
              }
              cycle += 10;

              cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                buffer[l] = dram[k][l];
              }
              cycle += 10;
              up++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: read column "<< d%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
              row = k;
            registers[registermap[vect.at(0)]] =  buffer[d%((int)pow(2.0,10.0))]  ;
              cycle += 2;

            }
          row = k;

          PC++;
          cout << "Registers: ";
          for(int i=0;i<32;i++){
              //cout << "aa";
              int k = registers[i];
              decToHex(k) ;
              if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
          }
          cout << "\n";

          }

        }


/* sw instruction starts */


        else if(strcmp(c,"sw")==0){
            vector<string> vect  = instructions[PC].vect;

                if(vect.size()!=2){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }


            string s =  vect.at(1).c_str();
            string t = "";
            string r = "";
            int i=0;
            while(true){
              if(isdigit(s[i])){
                t = t+s[i]; i++;
              }else {break;}

            }
            int q = stoi(s);

            if(i==s.length()){
              k = q/((int)pow(2.0,10.0));


             if((q)%4!=0){
               cout<<"Error: address value not a factor of 4 at line"<<PC<<endl;
               error=2;
                 break;
             }

             if(row==-1){
               cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
               cout << "DRAM: request issued \n";
               cycle++;
               cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
               for(int l=0; l <(int)pow(2.0,10.0); l++){
                 int j = dram[k][l];
                 buffer[l] = j;
               }
               cycle += 10;
               up++;
               cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< q%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
               row = k;
            buffer[q%((int)pow(2.0,10.0))] = registers[registermap[vect.at(0)]]  ;
               cycle += 2;
               up++;
               cout<< "Memory: Address " << q <<" = ";
               decToHex(registers[registermap[vect.at(0)]]);
               cout<<endl;

             }else if(row == k){

               cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
               cout << "DRAM: request issued \n";
               cycle++;
               cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< q%((int)pow(2.0,10.0))<<" row "<<k <<endl;
               row = k;
             buffer[q%((int)pow(2.0,10.0))] = registers[registermap[vect.at(0)]]   ;
               cycle += 2;
               up++;
               cout<< "Memory: Address " << q <<" = ";
               decToHex(registers[registermap[vect.at(0)]]);
               cout<<endl;

             }else{

               cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
               cout << "DRAM: request issued \n";
               cycle++;
               cout<<"Cycle " << cycle << "-" << cycle+9<<": DRAM: write back row "<< row <<endl;
               for(int l=0; l <(int)pow(2.0,10.0); l++){
                 dram[row][l] = buffer[l];
               }
               cycle += 10;

               cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
               for(int l=0; l <(int)pow(2.0,10.0); l++){
                 buffer[l] = dram[k][l];
               }
               cycle += 10;
               up++;
               cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< q%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
               row = k;
              buffer[q%((int)pow(2.0,10.0))] = registers[registermap[vect.at(0)]]  ;
               cycle += 2;
               up++;
               cout<< "Memory: Address " << q <<" = ";
               decToHex(registers[registermap[vect.at(0)]]);
               cout<<endl;

             }
           row = k;

           PC++;


          }else{

            r += s.substr(i+1, s.length()-i-2 );
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
              if((q)%4!=0){
                cout<<"Error: offset value not a factor of 4 at line "<<PC<<endl;
                  error =2;
                  break;
              }

            int  d = q + registers[registermap[r]];

            k = d/((int)pow(2.0,10.0));

            if((d)%4!=0){
              cout<<"Error: address value not a factor of 4 at line "<<PC<<endl;
              error=2;
                break;
            }

            if(row==-1){
              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                int j = dram[k][l];
                buffer[l] = j;
              }
              cycle += 10;
              up++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< d%((int)pow(2.0,10.0))<<" row "<<k <<endl;
              row = k;
            buffer[d%((int)pow(2.0,10.0))] = registers[registermap[vect.at(0)]]   ;
              cycle += 2;
              up++;
              cout<< "Memory: Address " << d <<" = ";
              decToHex(registers[registermap[vect.at(0)]]);
              cout<<endl;

            }else if(row == k){

              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< d%((int)pow(2.0,10.0)) <<" row "<<k<<endl;
              row = k;
          buffer[d%((int)pow(2.0,10.0))] =  registers[registermap[vect.at(0)]]  ;
              cycle += 2;
              up++;
              cout<< "Memory: Address " << d <<" = ";
              decToHex(registers[registermap[vect.at(0)]]);
              cout<<endl;

            }else{

              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              cout<<"Cycle " << cycle << "-" << cycle+9<<": DRAM: write back row "<< row <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                dram[row][l] = buffer[l];
              }
              cycle += 10;

              cout<<"Cycle " << cycle << "-" << cycle+9<<": \nDRAM: activate row "<< k  <<endl;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                buffer[l] = dram[k][l];
              }
              cycle += 10;
              up++;
              cout<<"Cycle " << cycle << "-" << cycle+1<<": \nDRAM: write to column "<< d%((int)pow(2.0,10.0))<<" row "<<k <<endl;
              row = k;
          buffer[d%((int)pow(2.0,10.0))] =  registers[registermap[vect.at(0)]]  ;
              cycle += 2;
              up++;
              cout<< "Memory: Address " << d <<" = ";
              decToHex(registers[registermap[vect.at(0)]]);
              cout<<endl;

            }
          row = k;

          PC++;


          }

        }


/* addi instruction starts */

        else if(strcmp(c,"addi")==0){


            vector<string> vect  = instructions[PC].vect;

             if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }


                //const char *d = vect.at(2).c_str();

                cout << "\nCycle "<<cycle << ": " <<"addi "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

                cycle++;

                string d = vect.at(2);
                if(d[0] == 36){
                  if(d == "$zero"){
                  registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] + registers[registermap[vect.at(2)]];
                }else{error =1; break;}
                }else{
                  registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] + stoi(d);
                }



            PC++;
            cout << "Registers: ";
            for(int i=0;i<32;i++){
                //cout << "aa";
                int k = registers[i];
                decToHex(k) ;
                if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
            }
            cout << "\n";
        }
        else{
            error =1;
            //cout<<"hwhwwh";
            break;
        }

    }


    if(error == 0){
      cout<< "\nTotal execution time in clock cycles is: " << cycle-1<<endl;
      cout<<"\nNumber of row buffer updates: "<< up <<endl;

    }
    else if(error == 1){
        cout << "syntax error at line: " << PC <<endl;
    }
    else if(error =2 ){
      cout <<endl;
    }
    else{
        cout << "jump not valid at line" << PC <<endl;
    }

}
