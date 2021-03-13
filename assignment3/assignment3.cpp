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
      ar[i] = r + 48;
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
int main(){
    vector<struct instructions> instructions;
    int registers[32];
    ifstream file;
    int index  = 0;
    string val;
    //cout << "hello";
    file.open("file.txt");


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
    int memory[(int)pow(2.0,18.0) - instructions.size()];
    int cycles = 0;
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
    int count_instruction[10];
    for(int i=0;i<10;i++){
        count_instruction[i] = 0;
    }
    memory[0] = 0; memory[1] = 1; memory[2] = 2;
    memory[5] = 5;memory[4] = 4; memory[3] = 3;
    memory[6] = 6; memory[7] = 7; memory[8] = 8;
    memory[11] = 11; memory[10] = 10; memory[9] = 9;
    memory[12] = 12; memory[13] = 13; memory[14] = 14;
    int error = 0;
    while(PC<filesize){
        const char *c = instructions.at(PC).name.c_str();
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
            count_instruction[0]++;
            PC++;
        }
        else if(strcmp("",c)==0){
            PC++;
            continue;
        }
        else if(strcmp(c,"sub")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(2)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            count_instruction[1]++;
            registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] - registers[registermap[vect.at(2)]];
            PC++;
        }
        else if(strcmp(c,"mul")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(2)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            count_instruction[2]++;
            registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] * registers[registermap[vect.at(2)]];
            PC++;
        }
        else if(strcmp(c,"beq")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            if(isnumber(vect.at(2))==false){
                  error = 1;
                  break;
            }
            count_instruction[3]++;
            if(registers[registermap[vect.at(1)]] == registers[registermap[vect.at(0)]]){
                const char *d = vect.at(2).c_str();
                int ac = atoi(d);
                if(ac<1 || ac > filesize){
                    error = 2;
                    break;
                }
                PC = atoi(d)-1;
            }
            else{
                PC++;
            }
        }
        else if(strcmp(c,"bne")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(0)) !=1){
                error = 1;
                break;
            }
            if(isnumber(vect.at(2))==false){
                  error = 1;
                  break;
            }
            count_instruction[4]++;
            if(registers[registermap[vect.at(1)]] != registers[registermap[vect.at(0)]]){
                    const char *d = vect.at(2).c_str();
                    int ac = atoi(d);
                if(ac<1 || ac > filesize){
                    error = 2;
                    break;
                }
                PC = atoi(d)-1;
            }
            else{
                PC++;
            }
        }
        else if(strcmp(c,"slt")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=3){
                error = 1;
                break;
            }
            if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(0)) !=1 || registermap.count(vect.at(2)) !=1){
                error = 1;
                break;
            }
            count_instruction[5]++;
            if(registers[registermap[vect.at(1)]] < registers[registermap[vect.at(2)]]){
                registers[registermap[vect.at(0)]]  = 1;
            }
            else{
                registers[registermap[vect.at(0)]]  = 0;
            }
            PC++;
        }
        else if(strcmp(c,"j")==0){
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=1){
                error = 1;
                break;
            }
            if(isnumber(vect.at(0))==false){
                  error = 1;
                  break;
            }
                const char *d = vect.at(0).c_str();
                count_instruction[6]++;
                int ac = atoi(d);
                if(ac<1 || ac > filesize){
                    error = 2;
                    break;
                }
                PC = atoi(d)-1;
        }
        else if(strcmp(c,"lw")==0){
            count_instruction[7]++;
            vector<string> vect  = instructions[PC].vect;
            if(vect.size()!=2){
                error = 1;
                break;
            }
            if(isnumber(vect.at(1))==false){
                  error = 1;
                  break;
            }
            const char *d = vect.at(1).c_str();
            if(atoi(d)%4!=0){
                error =1;
                break;
            }
            registers[registermap[vect.at(0)]] = memory[atoi(d)/4];
            PC++;
        }
        else if(strcmp(c,"sw")==0){
            vector<string> vect  = instructions[PC].vect;
            count_instruction[8]++;
                if(vect.size()!=2){
                error = 1;
                break;
            }
            if(isnumber(vect.at(1))==false){
                  error = 1;
                  break;
            }

            const char *d = vect.at(1).c_str();
            memory[atoi(d)/4] = registers[registermap[vect.at(0)]] ;
            PC++;
        }
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
            if(isnumber(vect.at(2))==false){
                  error = 1;
                  break;
            }
                const char *d = vect.at(2).c_str();

            registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] + atoi(d);
            PC++;
        }
        else{
            error =1;
            break;
        }
        for(int i=0;i<32;i++){
            //cout << "aa";
            int k = registers[i];
            decToHex(k) ;
            cout << " ";
        }
        cout << "\n";
    }

    if(error == 0){
    for(int i=0;i<10;i++){
        switch(i){
            case 0:
                cout << "number of times  and clock cycles add executed is " << count_instruction[0];
                cout << "\n";
                break;
            case 1:
                cout << "number of times  and clock cycles sub executed is " << count_instruction[1];
                cout << "\n";
                break;
            case 2:
                cout << "number of times  and clock cycles mul executed is " << count_instruction[2];
                cout << "\n";
                break;
            case 3:
                cout << "number of times  and clock cycles beq executed is " << count_instruction[3];
                cout << "\n";
                break;
            case 4:
                cout << "number of times  and clock cycles bne executed is " << count_instruction[4];
                cout << "\n";
                break;
            case 5:
                cout << "number of times  and clock cycles slt executed is " << count_instruction[5];
                cout << "\n";
                break;
            case 6:
                cout << "number of times  and clock cycles j executed is " << count_instruction[6];
                cout << "\n";
                break;
            case 7:
                cout << "number of times  and clock cycles lw executed is " << count_instruction[7];
                cout << "\n";
                break;
            case 8:
                cout << "number of times  and clock cycles sw executed is " << count_instruction[8];
                cout << "\n";
                break;
            case 9:
                cout << "number of times  and clock cycles addi executed is " << count_instruction[9];
                cout << "\n";
                break;
        }
    }
    }
    else if(error == 1){
        cout << "syntax error at line: " << PC + 1<<endl;
    }
    else{
        cout << "jump not valid " << PC + 1<<endl;
    }

}
