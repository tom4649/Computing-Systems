#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define rep(i,n) for (int i = 0; i < (n); ++i)
using ll = long long;
using P = pair<int,int>;

class parser_vm{
    ifstream in;//ファイル
    
    
public:
    parser_vm(string input);
    string inst;//コマンド
    string arg1="";
    string arg2="";
    int commandtype;//0:arithmetic,1:push,2:pop,3:label,4:goto,5:if,6:func,7:return,8:call
    bool advance();
};

parser_vm::parser_vm(string input){in.open(input);}
//コンストラクター

bool parser_vm::advance(){//入力コマンドが存在するかどうかを返し、instを変更
    if(getline(in,inst)){
        int i=0;
        if(inst[0]=='/'||inst.empty()||(int)inst[0]<32){return advance();}
        while(inst[i]==' ')i++;
        inst=inst.substr(i,inst.size()-i);
        if(inst[0]=='/'||inst.empty()||(int)inst[0]<32){return advance();}
        i=0;
        while(inst[inst.size()-1-i]==' ')i++;
        inst=inst.substr(0,inst.size()-i);
        int comment=inst.find("//");
        if(comment!=string::npos)inst=inst.substr(0,comment);
        if(inst.substr(0,3)=="add"||inst.substr(0,3)=="sub"||inst.substr(0,3)=="neg"){commandtype=0;arg1=inst.substr(0,3);}
        else if(inst.substr(0,3)=="pop"){commandtype=2;i=4;}
        else if(inst.substr(0,4)=="push"){commandtype=1;i=5;}
        else if(inst.substr(0,4)=="goto"){commandtype=4;arg1=inst.substr(5,inst.size()-5);}
        else if(inst.substr(0,4)=="call"){commandtype=8;i=5;}
        else if(inst.substr(0,5)=="label"){commandtype=3;arg1=inst.substr(6,inst.size()-6);}
        else if(inst.substr(0,6)=="return")commandtype=7;
        else if(inst.substr(0,7)=="if-goto"){commandtype=5;inst.substr(8,inst.size()-8);}
        else if(inst.substr(0,8)=="function"){commandtype=6;i=9;}
        else {cout<<"error\n";return false;}
        if(commandtype==1||commandtype==2||commandtype==6||commandtype==8){
            int j=0;
            while(inst[i+j]!=' ')j++;
            arg1=inst.substr(i,j);
            arg2=inst.substr(i+j+1,inst.size()-i-j-1);
        }
        return true;
    }
    return false;
}

/*int main(){
    parser_vm v("./test.vm");
    while(v.advance()){
        cout<<v.arg1<<"/"<<v.arg2<<"/"<<endl;
    }
}*/
