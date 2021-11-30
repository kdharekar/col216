#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const std::string WHITESPACE = " \n\r\t\f\v";
int registers[32];   //rergisters 32 in total

queue<int> addq;   //for memory addresss
queue<string> regq;  //for storing registers
queue<string> ls;
int row=-1;
int dram[(int)pow(2.0,10.0)][(int)pow(2.0,10.0)] = {0,0} ;  //dra;m memory matrix
int buffer[(int)pow(2.0,10.0)] = {0};    //row buffer
int rad =0 ;
int cad =0;
int up = 0;  //row buffer updates
int cycle = 1;
int k =0;   //storing row number where value will be stored or loaded

unordered_map<string, int> processmap;
  unordered_map<string, int> registermap;


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
	 const char *c = name.c_str();
       if(strcmp(c,"aabb")!=0){
        stringstream check1(arr[1]);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
        vect.push_back(intermediate);
}

    }
else{
 const char *d = arr[1].c_str();
	if(strcmp(d,"")==0){
	name = "";
	}
	else{
	name = arr[1];
	stringstream check1(arr[2]);
        string intermediate;
        while(getline(check1, intermediate, ','))
        {
        vect.push_back(intermediate);
}

}

}

}
};

bool memcheck(queue<int> aq, int m){
  int t=0;

  //aq.pop();
  while(!aq.empty()){
    t = aq.front();
    aq.pop();
    if(t == m){
      return true;
    }
  }
  return false;
}



queue<struct instructions> q;
vector<struct instructions> instructions;

void execute(int cycles){

  while(!ls.empty()){

    queue<struct instructions> myq;
    queue<int> myaddq;
    queue<string> myregq;
    queue<string> myldstq;
    queue<int> maq;
    int l = ls.size();

    if(row == -1 || row != int(addq.front()/1024) ){
      row = int(addq.front()/1024);
      cout<<"\nCycle " << cycle << "-" << cycle+rad-1<<": \nDRAM: activate row "<< row  <<endl;
      for(int l=0; l <(int)pow(2.0,10.0); l++){
        buffer[l] = dram[row][l];
      }
      cycle += rad;
      up++;
    }

    for(int i=0 ; i<l ;i++){

      string atr = regq.front();
      //cout << regq.size() << ls.size() << addq.size() <<endl ;

      string ldst = ls.front();

      int adres = addq.front();
      //cout << "adddressss "<< adres << endl;

//processmap[regq.front()]!=1 && !memcheck(myaddq , adres) &&

      if(processmap[regq.front()] !=1 && !memcheck(myaddq , adres) && (adres/1024) == row ){

        addq.pop(); regq.pop(); ls.pop();

        cout << "\nCompleting DRAM request of instruction:  " << ldst << " " << atr << " " << q.front().vect[1] << endl;
        q.pop();

        if(ldst == "lw"){
          cout<<"\nCycle " << cycle << "-" << cycle+cad-1<<": \nDRAM: read column "<< adres%((int)pow(2.0,10.0)) <<" row "<<row<<endl;
          registers[registermap[atr]] =  buffer[adres%((int)pow(2.0,10.0))]  ;
          cycle += cad;
          //processmap[atr] = 1;   
            cout << "Registers: ";
            for(int i=0;i<32;i++){
                //cout << "aa";
                int k = registers[i];
                decToHex(k) ;
                if(i==15 || i==7 || i==23){ cout<< "    ";}else{cout << " ";}
            }
            cout << "\n";
        }else{
          cout<<"\nCycle " << cycle << "-" << cycle+cad-1<<": \nDRAM: read column "<< adres%((int)pow(2.0,10.0)) <<" row "<<row<<endl;
          buffer[adres%((int)pow(2.0,10.0))] = registers[registermap[atr]]   ;
          cycle += cad;

          up++;
          cout<< "Memory: Address " << adres <<" = ";
          decToHex(registers[registermap[atr]]);
          cout<<endl;
        }
      }else{


        myq.push(q.front());
        q.pop();
        myaddq.push(addq.front());
        addq.pop();
        myregq.push(regq.front());
        regq.pop();
        myldstq.push(ls.front());
        ls.pop();

      }

    }

    q = myq;
    addq = myaddq;
    regq = myregq;
    ls = myldstq;

    cout<<"\nCycle " << cycle << "-" << cycle+rad-1<<": \nDRAM: write back row "<< row <<endl;
    for(int l=0; l <(int)pow(2.0,10.0); l++){
      dram[row][l] = buffer[l];
    }
    cycle += rad;

  }

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


}

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
    rad = atoi(argv[2]);
    cad = atoi(argv[3]);


    ifstream file;
    int index  = 0;
    string val="";
    //cout << "hello";
    file.open(f);
	int error = 0;
     int no;

        unordered_set<string> functions;
        unordered_map<string,int> labels;
        //add, sub,mul, beq, bne, slt, j, lw, sw, addi.
        functions.insert("add");functions.insert("mul");functions.insert("j");functions.insert("bne");
        functions.insert("sub");functions.insert("beq");functions.insert("slt");functions.insert("addi");functions.insert("lw");
        functions.insert("sw");
        int lineno = 0;

    while(getline(file, val)) {
       //if(val == ""){continue;}
	lineno++;
	int inlabel = 0;
         int count = 0;
string arr[3];
        arr[2] ="" ;
         arr[1]  = "";
        stringstream check1(val);
        string intermediate;
        while(check1>>intermediate){
            if(count==0){
                arr[0] = intermediate;
                count++;
		if(functions.find(intermediate)==functions.end() && intermediate[intermediate.size()-1]==':'){
                  inlabel = 1;
		//cout << "help" << "\n";
string label_name;
                  label_name = intermediate.substr(0,intermediate.size()-1);
		//cout << label_name << "\n";
                  labels.insert(make_pair(label_name,lineno));
                  arr[0] = "aabb";
                }
            }
	else if(inlabel == 1){
		arr[1]	= intermediate;
		inlabel = 2;
}
	else if(inlabel == 2){
		arr[2] =arr[2] + intermediate; }
            else{
                arr[1]  = arr[1] + intermediate;
            }
        }
		instructions.push_back(arr);
      // cout << arr[0]<<" ";
        // cout << arr[1]<<" ";
	//cout << arr[2] << "\n";
	}


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



    while(PC<filesize){
        const char *c = instructions.at(PC).name.c_str();


/* add instruction starts */


        if(strcmp("add",c)==0){
            vector<string> vect  = instructions[PC].vect;

            if(!ls.empty()){
            execute(cycle);}

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


/* sub */


	else if(strcmp(c,"sub")==0){
		vector<string> vect  = instructions[PC].vect;

    if(!ls.empty()){
    execute(cycle);}

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

		registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] - registers[registermap[vect.at(2)]];

		cout << "\nCycle "<<cycle << ": " <<"sub "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

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


/* mul */


	else if(strcmp(c,"mul")==0){
		vector<string> vect  = instructions[PC].vect;
		if(vect.size()!=3){
				error = 1;
				break;
		}

    if(!ls.empty()){
    execute(cycle);}


		if(registermap.count(vect.at(0)) !=1){
				error = 1;
				break;
		}
		if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(2)) !=1){
				error = 1;
				break;
		}

		registers[registermap[vect.at(0)]] = registers[registermap[vect.at(1)]] * registers[registermap[vect.at(2)]];

		cout << "\nCycle "<<cycle << ": " <<"mul "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

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


/* beq */


	else if(strcmp(c,"beq")==0){
		vector<string> vect  = instructions[PC].vect;
		if(vect.size()!=3){
				error = 1;
				break;
		}
    if(!ls.empty()){
    execute(cycle);}
		if(registermap.count(vect.at(0)) !=1){
				error = 1;
				break;
		}
		if(registermap.count(vect.at(1)) !=1){
				error = 1;
				break;
		}

		if(labels.count(vect.at(2))==0){
					error = 1;
					break;
		}

		if(registers[registermap[vect.at(1)]] == registers[registermap[vect.at(0)]]){

				int ac = labels[vect.at(2)];
				if(ac<1 || ac > filesize){
						error = 2;
						break;
				}
				PC = ac-1;
		}
		else{
				PC++;
		}


		cout << "\nCycle "<<cycle << ": " <<"beq "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

		cycle++;

	}


/* bne */


	else if(strcmp(c,"bne")==0){
		vector<string> vect  = instructions[PC].vect;
		if(vect.size()!=3){
				error = 1;
				break;
		}

    if(!ls.empty()){
    execute(cycle);}
		if(registermap.count(vect.at(0)) !=1){
				error = 1;
				break;
		}
		if(registermap.count(vect.at(1)) !=1){
				error = 1;
				break;
		}
		if(labels.count(vect.at(2))==0){
					error = 1;
					break;
		}

		if(registers[registermap[vect.at(1)]] != registers[registermap[vect.at(0)]]){
				int ac = labels[vect.at(2)];
				if(ac<1 || ac > filesize){
						error = 2;
						break;
				}
				PC = ac-1;
		}
		else{
				PC++;
		}


		cout << "\nCycle "<<cycle << ": " <<"bne "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

		cycle++;

	}


/* slt */


	else if(strcmp(c,"slt")==0){
		vector<string> vect  = instructions[PC].vect;
		if(vect.size()!=3){
				error = 1;
				break;
		}

    if(!ls.empty()){
    execute(cycle);}
		if(registermap.count(vect.at(0)) !=1){
				error = 1;
				break;
		}
		if(registermap.count(vect.at(1)) !=1 || registermap.count(vect.at(2)) !=1){
				error = 1;
				break;
		}

		if(registers[registermap[vect.at(1)]] < registers[registermap[vect.at(2)]]){
				registers[registermap[vect.at(0)]]  = 1;
		}
		else{
				registers[registermap[vect.at(0)]]  = 0;
		}

		cout << "\nCycle "<<cycle << ": " <<"slt "<< vect.at(0) <<", "<<vect.at(1)<<", "<<vect.at(2)<<endl;

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


/* j */


	else if(strcmp(c,"j")==0){
		vector<string> vect  = instructions[PC].vect;
		if(vect.size()!=1){
				error = 1;
				break;
		}

    if(!ls.empty()){
    execute(cycle);}

		if(labels.count(vect.at(0))==0){
					error = 1;
					break;
		}

				int ac = labels[vect.at(0)];
				if(ac<1 || ac > filesize){
						error = 2;
						break;
				}
				PC = ac-1;

		cout << "\nCycle "<<cycle << ": " <<"j "<< vect.at(0) <<endl;

		cycle++;
	}


/* lw instruction starts*/


  else if(strcmp(c,"lw")==0){

            vector<string> vect  = instructions[PC].vect;

            q.push(instructions[PC]);

            if(vect.size()!=2){
                error = 1;
                //cout << "hell";
                break;
            }
            if(registermap.count(vect.at(0)) !=1){
                error = 1;
                //cout << "he";
                break;
            }
            //processmap[vect[0]] = 1


            string s =  vect.at(1).c_str();
            if(isnumber(s) == true){
              error = 1;
              break;
            }

            string t = "";
            string r = "";
            int i=0;
            int offset = 0;
            while(true){
              if(isdigit(s[i])){
                t = t+s[i]; i++;
              }else {break;}

            }
            if(t == ""){
              offset = 0;
            }else{
              offset = stoi(t);
            }

            r += s.substr(i+1, s.length()-i-2 );
            if(registermap.count(r) !=1){
                error = 1;
                //cout<<"hell2";
                break;
              }

              int addresss = offset + registers[registermap[r]];
              cout << "\nCycle "<<cycle << ": " <<"lw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
              cout << "DRAM: request issued \n";
              cycle++;
              PC++;

              addq.push(addresss);
              regq.push(vect[0]);
              ls.push("lw");

        }


/* sw instruction starts */


        else if(strcmp(c,"sw")==0){

          vector<string> vect  = instructions[PC].vect;

          q.push(instructions[PC]);

          if(vect.size()!=2){
              error = 1;
             cout << "hell"<<endl;
              break;
          }
          if(registermap.count(vect.at(0)) !=1){
              error = 1;
             cout << "he"<<endl;
              break;
          }
          //processmap[vect[0]] = 1


          string s =  vect.at(1).c_str();


          string t = "";
          string r = "";
          int i=0;
          int offset = 0;
          while(true){
            if(isdigit(s[i])){
              t = t+s[i]; i++;
            }else {break;}

          }
          if(t == ""){
            offset = 0;
          }else{
            offset = stoi(t);
          }
          //cout << "offsetttt"<< offset<<endl;
          r += s.substr(i+1, s.length()-i-2 );
          if(registermap.count(r) !=1){
              error = 1;
              //cout<<"hell2";
              break;
            }

            int addresss = offset + registers[registermap[r]];
            //cout << "oftt"<< addresss<<endl;
            cout << "\nCycle "<<cycle << ": " <<"sw "<< vect.at(0) <<", "<<vect.at(1)<<endl;
            cout << "DRAM: request issued \n";
            cycle++;
            PC++;

            addq.push(addresss);
            regq.push(vect[0]);
            ls.push("sw");
        }


/* addi instruction starts */

        else if(strcmp(c,"addi")==0){


            vector<string> vect  = instructions[PC].vect;

            if(!ls.empty()){
            execute(cycle);}

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

    if(!ls.empty()){
    execute(cycle);}

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
