#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define rep(i,n) for (int i = 0; i < (n); ++i)
using ll = long long;
using P = pair<int,int>;

class symbol_table{

    public:
        map<string,int> mp;
        symbol_table();
        void addEntry(string symbol,int address);
        bool contains(string symbol);
        int getAddress(string symbol);

};

class parser{
    ifstream in;//ファイル
    
    
public:
    parser(string input);
    string inst;//コマンド
    int commandtype;//0:A,1:L,2:C
    bool advance();
    string symbol();
    string dest();
    string comp();
    string jump();
    bitset<3> dest_to_code();
    bitset<7> comp_to_code();
    bitset<3> jump_to_code();

};

parser::parser(string input){in.open(input);}
//コンストラクター

bool parser::advance(){//入力コマンドが存在するかどうかを返し、instを変更
    if(getline(in,inst)){
        int i=0;
        if(inst[0]=='/'||inst.empty()||(int)inst[0]<32){return advance();}
        while(inst[i]==' ')i++;
        inst=inst.substr(i,inst.size()-i);
        if(inst[0]=='/'||inst.empty()||(int)inst[0]<32){return advance();}
        i=0;
        while(i<inst.size()&&inst[i]!=' '&&inst[i]!='/')i++;
        if(i<inst.size())inst=inst.substr(0,i+1);
        if(inst[0]=='/'||inst.empty()||(int)inst[0]<32){return advance();}
        if(inst[0]=='@')commandtype=0;
        else if(inst[0]=='(')commandtype=1;
        else {commandtype=2;}
        return true;
    }
    return false;
}

string parser::symbol(){//symbolを返す
    if(commandtype==0){return inst.substr(1,inst.length()-2);}
    else return inst.substr(1,inst.length()-2);
}

string parser::dest(){//destのニーモニックを返す
    int flag=-1;
    rep(i,inst.length())if(inst[i]=='='){flag=i;break;}
    if(flag==-1)return "null";
    return inst.substr(0,flag);
    
}

string parser::comp(){//compニーモニックを返す
    int flag=-1;
    rep(i,inst.length())if(inst[i]=='='){flag=i;break;}
    int flag2=inst.length()-1;
    rep(i,inst.length())if(inst[i]==';'){flag2=i;break;}
    return inst.substr(flag+1,flag2-flag-1);
}

string parser::jump(){
    int flag=-1;
    rep(i,inst.length())if(inst[i]==';'){
    flag=i;
    break;}
    if(flag==-1)return "null";
    return inst.substr(flag+1,inst.length()-flag-2);
}


bitset<3> parser::dest_to_code(){
    string s=dest();
    if(s=="null")return 0;
    if(s=="M")return 1;
    if(s=="D")return 2;
    if(s=="MD")return 3;
    if(s=="A")return 4;
    if(s=="AM")return 5;
    if(s=="AD")return 6;
    if(s=="AMD")return 7;
    else return -1;
}
    
bitset<7> parser::comp_to_code(){
    string s=comp();
    if(s=="0") return 42;
    if(s=="1") return 63;
    if(s=="-1") return 58;
    if(s=="D") return 12;
    if(s=="A") return 48;
    if(s=="!D") return 13;
    if(s=="!A") return 49;
    if(s=="-D") return 15;
    if(s=="-A") return 51;
    if(s=="D+1") return 31;
    if(s=="A+1") return 55;
    if(s=="D-1") return 14;
    if(s=="A-1") return 50;
    if(s=="D+A") return 2;
    if(s=="D-A") return 19;
    if(s=="A-D") return 7;
    if(s=="D&A") return 0;
    if(s=="D|A") return 21;
    if(s=="M") return 112;
    if(s=="!M") return 113;
    if(s=="-M") return 115;
    if(s=="M+1") return 119;
    if(s=="M-1") return 114;
    if(s=="D+M") return 66;
    if(s=="D-M") return 83;
    if(s=="M-D") return 71;
    if(s=="D&M") return 64;
    if(s=="D|M") return 85;
    else return -1;
}
    
bitset<3> parser::jump_to_code(){
    string s=jump();
    if(s=="null")return 0;
    if(s=="JGT")return 1;
    if(s=="JEQ")return 2;
    if(s=="JGE")return 3;
    if(s=="JLT")return 4;
    if(s=="JNE")return 5;
    if(s=="JLE")return 6;
    if(s=="JMP")return 7;
    else return -1;

}

symbol_table::symbol_table(){
    mp["SP"]=0;
    mp["LCL"]=1;
    mp["ARG"]=2;
    mp["THIS"]=3;
    mp["THAT"]=4;
    mp["R0"]=0;
    mp["R1"]=1;
    mp["R2"]=2;
    mp["R3"]=3;
    mp["R4"]=4;
    mp["R5"]=5;
    mp["R6"]=6;
    mp["R7"]=7;
    mp["R8"]=8;
    mp["R9"]=9;
    mp["R10"]=10;
    mp["R11"]=11;
    mp["R12"]=12;
    mp["R13"]=13;
    mp["R14"]=14;
    mp["R15"]=15;
    mp["SCREEN"]=16384;
    mp["KBD"]=24576;
}
void symbol_table::addEntry(string symbol,int address){
    mp[symbol]=address;
}
bool symbol_table::contains(string symbol){
    return mp.find(symbol)!=mp.end();
}
int symbol_table::getAddress(string symbol){
    return mp[symbol];
}

void assembler2(std::filesystem::path input){
    
    symbol_table s;
    parser p((string)input);
    int num=0;
    while(p.advance()){
        if(p.commandtype==1){
            string pos=p.symbol();
            s.addEntry(pos.substr(0,pos.length()-1),num);
        }
        else num++;
    }

    parser ass((string)input);
    ofstream out;
    string output=(string)input.stem()+"1.hack";
    out.open(output);

    int n=16;
    while(ass.advance()){
        if(ass.commandtype==1)continue;
        else if(ass.commandtype==2){
            out<<"111"<<ass.comp_to_code()<<ass.dest_to_code()<<ass.jump_to_code()<<endl;
        }
        else{
            string pos=ass.symbol();
            if(isdigit(pos[0])){
                bitset<16> ans(stoi(pos));
                out<<ans<<endl;
            }
            else if(s.contains(pos)){
                bitset<16> ans(s.getAddress(pos));
                out<<ans<<endl;
            }
            else{
                s.addEntry(pos,n);
                bitset<16> ans(n);
                out<<ans<<endl;
                n++;
            }
        }
    }
    cout<<"success\n";
    return;
}

int main(){
    std::filesystem::path input="./pong/Pong.asm";
    assembler2(input);
}