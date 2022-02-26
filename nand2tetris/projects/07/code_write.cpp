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
        if(inst.substr(0,3)=="add"||inst.substr(0,3)=="sub"||inst.substr(0,3)=="neg"||inst.substr(0,3)=="and"||inst.substr(0,3)=="not"){commandtype=0;arg1=inst.substr(0,3);}
        else if(inst.substr(0,2)=="eq"||inst.substr(0,2)=="gt"||inst.substr(0,2)=="lt"||inst.substr(0,2)=="or"){commandtype=0;arg1=inst.substr(0,2);}
        else if(inst.substr(0,3)=="pop"){commandtype=2;i=4;}
        else if(inst.substr(0,4)=="push"){commandtype=1;i=5;}
        else if(inst.substr(0,4)=="goto"){commandtype=4;arg1=inst.substr(5,inst.size()-5);}
        else if(inst.substr(0,4)=="call"){commandtype=8;i=5;}
        else if(inst.substr(0,5)=="label"){commandtype=3;arg1=inst.substr(6,inst.size()-6);}
        else if(inst.substr(0,6)=="return")commandtype=7;
        else if(inst.substr(0,7)=="if-goto"){commandtype=5;inst.substr(8,inst.size()-8);}
        else if(inst.substr(0,8)=="function"){commandtype=6;i=9;}
        else {cout<<"error\n";}
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



int main(){
    std::filesystem::path input="./MemoryAccess/StaticTest/StaticTest.vm";
    parser_vm v((string)input);
    string output=(string)input.stem()+".asm";
    ofstream out;
    out.open(output);
    int num=0;
    while(v.advance()){
        if(v.commandtype==0){
        if(v.arg1=="add")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D+M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(v.arg1=="sub")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(v.arg1=="neg")out<<"@SP\nA=M-1\nD=-M\n@SP\nA=M-1\nM=D\n";
        else if(v.arg1=="eq"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@True"+to_string(num)+"\nD;JEQ\n@False"+to_string(num)+"\n0;JEQ\n(l"+to_string(num)+")\n";
            num++;
            }
        else if(v.arg1=="gt"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@True"+to_string(num)+"\nD;JGT\n@False"+to_string(num)+"\n0;JEQ\n(l"+to_string(num)+")\n";
            num++;
            }
        else if(v.arg1=="lt"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@True"+to_string(num)+"\nD;JLT\n@False"+to_string(num)+"\n0;JEQ\n(l"+to_string(num)+")\n";
            num++;
            }
        else if(v.arg1=="and")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D&M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(v.arg1=="or")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D|M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(v.arg1=="not")out<<"@SP\nA=M-1\nD=!M\n@SP\nA=M-1\nM=D\n";
    }
    else if(v.commandtype==1){//push
        if(v.arg1=="constant"){
            out<<"@"<<v.arg2<<"\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="this"){
            out<<"@"<<v.arg2<<"\nD=A\n@THIS\nA=D+M\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="that"){
            out<<"@"<<v.arg2<<"\nD=A\n@THAT\nA=D+M\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="local"){
            out<<"@"<<v.arg2<<"\nD=A\n@LCL\nA=D+M\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="argument"){
            out<<"@"<<v.arg2<<"\nD=A\n@ARG\nA=D+M\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="pointer"){
            int add=3+stoi(v.arg2);
            out<<"@"+to_string(add)+"\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="temp"){
            int add=5+stoi(v.arg2);
            out<<"@"+to_string(add)+"\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
        else if(v.arg1=="static"){
            string add=(string)input.stem()+"."+v.arg2;
            out<<"@"+add+"\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
    }
    else if(v.commandtype==2){//pop
        if(v.arg1=="this"){
            out<<"@SP\nM=M-1\n@"+v.arg2+"\nD=A\n@THIS\nD=D+M\n@R13\nM=D\n@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n";
        }
        else if(v.arg1=="that"){
            out<<"@SP\nM=M-1\n@"+v.arg2+"\nD=A\n@THAT\nD=D+M\n@R13\nM=D\n@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n";
        }
        else if(v.arg1=="local"){
            out<<"@SP\nM=M-1\n@"+v.arg2+"\nD=A\n@LCL\nD=D+M\n@R13\nM=D\n@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n";
        }
        else if(v.arg1=="argument"){
            out<<"@SP\nM=M-1\n@"+v.arg2+"\nD=A\n@ARG\nD=D+M\n@R13\nM=D\n@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n";
        }
        else if(v.arg1=="pointer"){
            int add=3+stoi(v.arg2);
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+to_string(add)+"\nM=D\n";
        }
        else if(v.arg1=="temp"){
            int add=5+stoi(v.arg2);
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+to_string(add)+"\nM=D\n";
        }
        else if(v.arg1=="static"){
            string add=(string)input.stem()+"."+v.arg2;
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+add+"\nM=D\n";
        }

    }
    }
    out<<"@END\n0;JMP\n";
    rep(i,num){
        out<<"(True"+to_string(i)+")\n@SP\nA=M-1\nM=-1\n@l"+to_string(i)+"\n0;JEQ\n(False"+to_string(i)+")\n@SP\nA=M-1\nM=0\n@l"+to_string(i)+"\n0;JEQ\n";
    }
    out<<"(END)\n@END\n0;JMP\n";

}