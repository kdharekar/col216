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
    int buffer[(int)pow(2.0,10.0)];    //row buffer
    int row=-1;
    int up = 0;  //row buffer updates
    int cycle = 1;
    int cyc = 0;
    string reg = "";
    int address  = 0;
    int check =0;
    int sl = 0;
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
    unordered_map<string, int> processmap;
    processmap["$zero"] = 0;
    processmap["$at"] = 0; processmap["$ra"] = 0;
    processmap["$v0"] = 0; processmap["$fp"] = 0;
    processmap["$v1"] = 0; processmap["$sp"] = 0;
    processmap["$a0"] = 0; processmap["$gp"] = 0;
    processmap["$a1"] = 0; processmap["$k1"] = 0;
    processmap["$a2"] = 0; processmap["$k0"] = 0;
    processmap["$a3"] = 0; processmap["$t9"] = 0;
    processmap["$t0"] = 0; processmap["$t8"] = 0;
    processmap["$t1"] = 0; processmap["$s7"] = 0;
    processmap["$t2"] = 0;
    processmap["$t3"] = 0;
    processmap["$t4"] = 0;
    processmap["$t5"] = 0;
    processmap["$t6"] = 0;
    processmap["$t7"] = 0;
    processmap["$s0"] = 0;
    processmap["$s1"] = 0;
    processmap["$s2"] = 0;
    processmap["$s3"] = 0;
    processmap["$s4"] = 0;
    processmap["$s5"] = 0;
    processmap["$s6"] = 0;
    // we have loaded the instructions in vector instructions
    for(int i=0;i<32;i++){
        registers[i] = 0;
    }
    //registers[29] = 65535;
    int PC = 0;
    int filesize = instructions.size();
    int count_instruction[10];
    for(int i=0;i<10;i++){
        count_instruction[i] = 0;
    }

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

            if(processmap[vect[0]]==1 || processmap[vect[1]]==1 || processmap[vect[2]]==1 ){
            if(sl == 1){
              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              up++;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc +1 ;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              up++;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc +1;
            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }

        else{

              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;

              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc +1;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc+1 ;
            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }
        }


    if(cycle ==cyc){
        if(sl == 1){
          if(cycle < cyc){
          cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
          buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
          up++;
          cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

          check = 0;
          cycle = cyc  ;
        }else if(cycle == cyc){
          cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
          buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
          up++;
          cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

          check = 0;
          cycle = cyc ;
        }else{
          check =0;
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
        }
      }

    else{

          if(cycle < cyc){
          cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
          registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;

          cout << "Registers: ";
          for(int i=0;i<32;i++){
              //cout << "aa";
              int k = registers[i];
              decToHex(k) ;
              if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
          }
          cout << "\n";
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

          check = 0;
          cycle = cyc ;
        }else if(cycle == cyc){
          cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
          registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
          cout << "Registers: ";
          for(int i=0;i<32;i++){
              //cout << "aa";
              int k = registers[i];
              decToHex(k) ;
              if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
          }
          cout << "\n";
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

          check = 0;
          cycle = cyc;
        }else{
          check =0;
          processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
        }
      }
    }

            registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] + registers[registermap[vect.at(2)]];
            count_instruction[0]++;
            cout << "\nCycle "<<cycle << ": " <<"add "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;
            if(check ==1){
              if(sl==1){
              cout << "DRAM: storing value from "<< reg<<" to address "<< address<<" .....in progress"<<endl;}
              else{
                cout << "DRAM: loading value to "<< reg<<" from address "<< address<<" .....in progress"<<endl;}


            }
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
            count_instruction[7]++;
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=2){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            //processmap[vect[0]] = 1;

            if(processmap[vect[0]]==1 || check ==1 ){
            if(sl == 1){
              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              up++;
              processmap[vect[0]] = 0;
              check = 0;
              cycle = cyc +1;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              up++;
              processmap[vect[0]] = 0;
              check = 0;
              cycle = cyc +1;
            }else{
              check =0;
              processmap[vect[0]] = 0;
            }
          }

        else{

              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;
              check = 0;
              cycle = cyc +1;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;
              check = 0;
              cycle = cyc +1;
            }else{
              check =0;
              processmap[vect[0]] = 0;
            }
          }
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
                 cout<<"Error: address value not a factor of 4  at line"<<PC<<endl;
                 error=2;
                   break;
               }
              check =1;
              sl = 0;
              if(row==-1){
                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  int j = dram[k][l];
                  buffer[l] = j;
                }
                up++;
                cyc = cycle + rad + cad;
                cycle++;
                processmap[vect[0]]=1;
                address = q;
                reg = vect[0];

              }else if(row == k){

                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cyc = cycle + cad;
                cycle++;
                processmap[vect[0]]=1;
                address = q;
                reg = vect[0];

              }else{

                cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  dram[row][l] = buffer[l];
                }
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  buffer[l] = dram[k][l];
                }
                up++;
                cyc = cycle + 2*rad + cad;
                processmap[vect[0]]=1;
                address = q;
                reg = vect[0];
                cycle++;

              }
            row = k;

            PC++;


          }else{
            r += s.substr(i+1, s.length()-i-2 );
            if((q)%4!=0){
              cout<<"Error: offset value not a factor of 4  at line"<<PC<<endl;
              error=2;
                break;
            }
              check=1;
              sl=0;
            int  d = q + registers[registermap[r]];

            k = d/((int)pow(2.0,10.0));

            if((d)%4!=0){
              cout<<"Error: address value not a factor of 4  at line"<<PC<<endl;
              error=2;
                break;
            }
            if(row==-1){
              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                int j = dram[k][l];
                buffer[l] = j;
              }
              up++;
              cyc = cycle + rad + cad;
              cycle++;
              processmap[vect[0]]=1;
              address = d;
              reg = vect[0];

            }else if(row == k){

              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cyc = cycle + cad;
              processmap[vect[0]]=1;
              cycle++;
              reg = vect[0];
              address = d;

          }else{

            cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
            cout << "DRAM: request issued \n";
            for(int l=0; l <(int)pow(2.0,10.0); l++){
              dram[row][l] = buffer[l];
            }
            for(int l=0; l <(int)pow(2.0,10.0); l++){
              buffer[l] = dram[k][l];
            }
            up++;
            cyc = cycle + 2*rad + cad;
            processmap[vect[0]]=1;
            address = d;
            reg = vect[0];
            cycle++;

            }
          row = k;

          PC++;

          }

        }


/* sw instruction starts */


        else if(strcmp(c,"sw")==0){
            vector<string> vect  = instructions[PC].vect;
            count_instruction[8]++;
                if(vect.size()!=2){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }


      if(processmap[vect[0]]==1 || check ==1){
              if(sl == 1){
                if(cycle < cyc){
                cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
                buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
                cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
                up++;
                processmap[vect[0]] = 0;
                check = 0;
                cycle = cyc +1;
              }else if(cycle == cyc){
                cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
                buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
                cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
                up++;
                processmap[vect[0]] = 0;
                check = 0;
                cycle = cyc +1;
              }else{
                check =0;
                processmap[vect[0]] == 0;
              }
            }

          else{
                if(cycle < cyc){
                cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
                registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
                cout << "Registers: ";
                for(int i=0;i<32;i++){
                    //cout << "aa";
                    int k = registers[i];
                    decToHex(k) ;
                    if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
                }
                cout << "\n";
                processmap[vect[0]] = 0;
                check = 0;
                cycle = cyc +1;
              }else if(cycle == cyc){
                cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
                registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
                cout << "Registers: ";
                for(int i=0;i<32;i++){
                    //cout << "aa";
                    int k = registers[i];
                    decToHex(k) ;
                    if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
                }
                cout << "\n";
                processmap[vect[0]] = 0;
                check = 0;
                cycle = cyc +1;
              }else{
                check =0;
                processmap[vect[0]] == 0;
              }
            }
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
              check =1;
              sl =1;
              if(row==-1){

                cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  buffer[l] = dram[k][l];
                }
                up++;
                cyc = cycle + rad + cad;
                cycle++;
                processmap[vect[0]] =1;
                address = q;
                reg = vect[0];

              }else if(row == k){
                cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cyc = cycle + cad;
                cycle++;
                processmap[vect[0]] =1;
                address = q;
                reg = vect[0];

              }else{
                cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
                cout << "DRAM: request issued \n";
                cyc = cycle + 2*rad + cad;
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  dram[row][l] = buffer[l];
                }
                for(int l=0; l <(int)pow(2.0,10.0); l++){
                  buffer[l] = dram[k][l];
                }
                up++;
                cycle++;
                processmap[vect[0]] =1;
                address = q;
                reg = vect[0];

              }
            row = k;

            PC++;

          }else{

            r = s.substr(i+1, s.length()-i-2 );
            if((q)%4!=0){
              cout<<"Error: offset value not a factor of 4 at line"<<PC<<endl;
              error=2;
                break;
            }
            int  d = q + registers[registermap[r]];

           k = d/((int)pow(2.0,10.0));

           if((d)%4!=0){
             cout<<"Error: address value not a factor of 4 at line"<<PC<<endl;
             error=2;
               break;
           }
            check =1;
            sl=1;
            if(row==-1){
              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cyc = cycle + rad + cad;
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                buffer[l] = dram[k][l];
              }
              up++;
              cycle++;
              processmap[vect[0]] =1;
              address = d;
              reg = vect[0];

            }else if(row == k){
              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cyc = cycle + cad;
              cycle++;
              processmap[vect[0]] =1;
              address = d;
              reg = vect[0];

            }else{
              cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                dram[row][l] = buffer[l];
              }
              for(int l=0; l <(int)pow(2.0,10.0); l++){
                buffer[l] = dram[k][l];
              }
              up++;
              cyc = cycle + 2*rad + cad;
              cycle++;
              processmap[vect[0]] =1;
              address = d;
              reg = vect[0];

            }
          row = k;

          PC++;

          }

        }


/* addi instruction starts */

        else if(strcmp(c,"addi")==0){
            count_instruction[9]++;

            vector<string> vect  = instructions[PC].vect;

             if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }


    if(processmap[vect[0]]==1 || processmap[vect[1]]==1 || processmap[vect[2]]==1  ){
            if(sl == 1){
              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc+1 ;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
              cycle = cyc+1;
              check = 0;

            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }

        else{

              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc+1 ;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc +1;
            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }
        }


        if(cycle ==cyc){
            if(sl == 1){
              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              up++;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc  ;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
              buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
              up++;
              cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc ;
            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }

        else{

              if(cycle < cyc){
              cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;

              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc ;
            }else if(cycle == cyc){
              cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
              registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
              cout << "Registers: ";
              for(int i=0;i<32;i++){
                  //cout << "aa";
                  int k = registers[i];
                  decToHex(k) ;
                  if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
              }
              cout << "\n";
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;

              check = 0;
              cycle = cyc;
            }else{
              check =0;
              processmap[vect[0]] = 0;processmap[vect[1]] = 0;processmap[vect[2]] = 0;
            }
          }
        }

                //const char *d = vect.at(2).c_str();

                cout << "\nCycle "<<cycle << ": " <<"addi "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;
                if(check ==1){
                  if(sl==1){
                  cout << "DRAM: storing value from "<< reg<<" to address "<< address<<" .....in progress"<<endl;}
                  else{
                    cout << "DRAM: loading value to "<< reg<<" from address "<< address<<" .....in progress"<<endl;}
                }

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
            break;
        }

    }


    if(sl == 1){
      if(cycle < cyc){
      cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
      buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
      cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
      up++;
      check = 0;
      cycle = cyc +1;
    }else if(cycle == cyc){
      cout << "Cycle "<< cycle  << ": \nDRAM: stored value from "<< reg<<" to address "<< address<<endl;
      buffer[address%((int)pow(2.0,10.0))] = registers[registermap[reg]] ;
      cout<< "Memory: Address " << address <<" = "<< registers[registermap[reg]]<<endl;
      up++;
      check = 0;
      cycle = cyc +1;
    }else{
      check =0;

    }
  }

else{

      if(cycle < cyc){
      cout << "Cycle "<< cycle << "-" << cyc << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
      registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
      cout << "Registers: ";
      for(int i=0;i<32;i++){
          //cout << "aa";
          int k = registers[i];
          decToHex(k) ;
          if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
      }
      cout << "\n";
      check = 0;
      cycle = cyc +1;
    }else if(cycle == cyc){
      cout << "Cycle "<< cycle  << ": \nDRAM: loaded value to "<< reg<<" from address "<< address<<endl;
      registers[registermap[reg]] = buffer[address%((int)pow(2.0,10.0))] ;
      cout << "Registers: ";
      for(int i=0;i<32;i++){
          //cout << "aa";
          int k = registers[i];
          decToHex(k) ;
          if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
      }
      cout << "\n";
      check = 0;
      cycle = cyc +1;
    }else{
      check =0;

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
