#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define rep(i,n) for (int i = 0; i < (n); ++i)
using ll = long long;
using P = pair<int,int>;
using std::filesystem::directory_iterator;

ofstream out;

class parser_vm{
    ifstream in;//ファイル
    filesystem::path input;
    
public:
    parser_vm(filesystem::path input_){input=input_;in.open((string)input);};
    string inst;//コマンド
    string arg1="";
    string arg2="";
    string funcname="Sys.init";
    int commandtype;//0:arithmetic,1:push,2:pop,3:label,4:goto,5:if,6:func,7:return,8:call
    bool advance();
    void write();
};

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
        else if(inst.substr(0,5)=="label"){commandtype=3;arg1=inst.substr(6,inst.size()-6);int j=0;while(arg1[arg1.size()-1-j]==' '||(int)arg1[arg1.size()-1-j]<32){j++;}arg1=arg1.substr(0,arg1.size()-j);}
        else if(inst.substr(0,6)=="return")commandtype=7;
        else if(inst.substr(0,7)=="if-goto"){commandtype=5;arg1=inst.substr(8,inst.size()-8);int j=0;while(arg1[arg1.size()-1-j]==' '||(int)arg1[arg1.size()-1-j]<32){j++;}arg1=arg1.substr(0,arg1.size()-j);}
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

void write_push(string x){//x="M"or"A"
    out<<"D="+x+"\n@SP\nM=M+1\nA=M-1\nM=D\n";
}
void write_pop(string num,string where){
    out<<"@SP\nM=M-1\n@"+num+"\nD=A\n@"+where+"\nD=D+M\n@R13\nM=D\n@SP\nA=M\nD=M\n@R13\nA=M\nM=D\n";
}
void parser_vm::write(){
    int num=0,num2=0;
    while(advance()){
    if(commandtype==0){//arithmetic
    out<<"//arithmetic"+arg1+"\n";
        if(arg1=="add")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D+M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(arg1=="sub")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(arg1=="neg")out<<"@SP\nA=M-1\nD=-M\n@SP\nA=M-1\nM=D\n";
        else if(arg1=="eq"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@"+funcname+"$True"+to_string(num)+"\nD;JEQ\n@"+funcname+"$False"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$True"+to_string(num)+")\n@SP\nA=M-1\nM=-1\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n("+funcname+"$False"+to_string(num)+")\n@SP\nA=M-1\nM=0\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$l"+to_string(num)+")\n";
            num++;
            }
        else if(arg1=="gt"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@"+funcname+"$True"+to_string(num)+"\nD;JGT\n@"+funcname+"$False"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$True"+to_string(num)+")\n@SP\nA=M-1\nM=-1\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n("+funcname+"$False"+to_string(num)+")\n@SP\nA=M-1\nM=0\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$l"+to_string(num)+")\n";
            num++;
            }
        else if(arg1=="lt"){
            out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=M-D\n@SP\nM=M-1\n@"+funcname+"$True"+to_string(num)+"\nD;JLT\n@"+funcname+"$False"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$True"+to_string(num)+")\n@SP\nA=M-1\nM=-1\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n("+funcname+"$False"+to_string(num)+")\n@SP\nA=M-1\nM=0\n@"+funcname+"$l"+to_string(num)+"\n0;JEQ\n";
            out<<"("+funcname+"$l"+to_string(num)+")\n";
            num++;
            }
        else if(arg1=="and")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D&M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(arg1=="or")out<<"@SP\nA=M-1\nD=M\nA=A-1\nD=D|M\n@SP\nM=M-1\n@SP\nA=M-1\nM=D\n";
        else if(arg1=="not")out<<"@SP\nA=M-1\nD=!M\n@SP\nA=M-1\nM=D\n";
    }
    else if(commandtype==1){//push
    out<<"//push"+arg1+"\n";
        if(arg1=="constant"){
            out<<"@"<<arg2<<"\n";write_push("A");
        }
        else if(arg1=="this"){
            out<<"@"<<arg2<<"\nD=A\n@THIS\nA=D+M\n";write_push("M");
        }
        else if(arg1=="that"){
            out<<"@"<<arg2<<"\nD=A\n@THAT\nA=D+M\n";write_push("M");
        }
        else if(arg1=="local"){
            out<<"@"<<arg2<<"\nD=A\n@LCL\nA=D+M\n";write_push("M");
        }
        else if(arg1=="argument"){
            out<<"@"<<arg2<<"\nD=A\n@ARG\nA=D+M\n";write_push("M");
        }
        else if(arg1=="pointer"){
            int add=3+stoi(arg2);
            out<<"@"+to_string(add)+"\n";write_push("M");
        }
        else if(arg1=="temp"){
            int add=5+stoi(arg2);
            out<<"@"+to_string(add)+"\n";write_push("M");
        }
        else if(arg1=="static"){
            string add=(string)input.stem()+"."+arg2;
            out<<"@"+add+"\n";write_push("M");
        }
    }
    else if(commandtype==2){//pop
    out<<"//pop"+arg1+"\n";
        if(arg1=="this"){
            write_pop(arg2,"THIS");
        }
        else if(arg1=="that"){
            write_pop(arg2,"THAT");
        }
        else if(arg1=="local"){
            write_pop(arg2,"LCL");
        }
        else if(arg1=="argument"){
            write_pop(arg2,"ARG");
        }
        else if(arg1=="pointer"){
            int add=3+stoi(arg2);
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+to_string(add)+"\nM=D\n";
        }
        else if(arg1=="temp"){
            int add=5+stoi(arg2);
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+to_string(add)+"\nM=D\n";
        }
        else if(arg1=="static"){
            string add=(string)input.stem()+"."+arg2;
            out<<"@SP\nM=M-1\nA=M\nD=M\n@"+add+"\nM=D\n";
        }
    }
    else if(commandtype==4){//goto
        out<<"//goto\n";
        out<<"@"+funcname+"$"+arg1+"\n0;JEQ\n";
    }
    else if(commandtype==5){//if
        out<<"//if\n";
        out<<"@SP\nAM=M-1\nD=M\n@"+funcname+"$"+arg1+"\nD;JNE\n";
    }
    else if(commandtype==3){//label
        out<<"("+funcname+"$"+arg1+")\n";
    }
    else if(commandtype==6){//func
        funcname=arg1;
        out<<"//func"+funcname+"\n";
        out<<"("+arg1+")\n";
        rep(i,stoi(arg2)){
            out<<"@0\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n";
        }
    }
    else if(commandtype==8){//call
        out<<"//call"+funcname+" "+arg1+"\n";
        out<<"@"+funcname+"$"+to_string(num2)+"\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n";
        out<<"@LCL\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        out<<"@ARG\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        out<<"@THIS\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        out<<"@THAT\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
        out<<"@SP\nD=M\n@"+arg2+"\nD=D-A\n@5\nD=D-A\n@ARG\nM=D\n";
        out<<"@SP\nD=M\n@LCL\nM=D\n";
        out<<"@"+arg1+"\n";
        out<<"0;JMP\n";
        out<<"("+funcname+"$"+to_string(num2)+")\n";
        num2++;
    }
    else if(commandtype==7){//return
        out<<"//return\n";
        out<<"@LCL\nD=M\n@R13\nM=D\n";
        out<<"@5\nA=D-A\nD=M\n@R14\nM=D\n";//戻り値アドレス
        out<<"@SP\nM=M-1\nA=M\nD=M\n@ARG\nA=M\nM=D\n";//ARG
        out<<"@ARG\nD=M\n@SP\nM=D+1\n";
        out<<"@R13\nAM=M-1\nD=M\n@THAT\nM=D\n";
        out<<"@R13\nAM=M-1\nD=M\n@THIS\nM=D\n";
        out<<"@R13\nAM=M-1\nD=M\n@ARG\nM=D\n";
        out<<"@R13\nAM=M-1\nD=M\n@LCL\nM=D\n";
        out<<"@R14\nA=M\n0;JMP\n";
    }}
    /*rep(i,num){
        out<<"("+funcname+"$True"+to_string(i)+")\n@SP\nA=M-1\nM=-1\n@"+funcname+"$l"+to_string(i)+"\n0;JEQ\n("+funcname+"$False"+to_string(i)+")\n@SP\nA=M-1\nM=0\n@"+funcname+"$l"+to_string(i)+"\n0;JEQ\n";
    }*/
}

void solver(filesystem::path name_in,string name_out){
    out.open(name_out);
    out<<"@256\nD=A\n@SP\nM=D\n";
    out<<"@777\nD=A\n@SP\nM=M+1\nA=M-1\nM=D\n";
    out<<"@LCL\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
    out<<"@ARG\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
    out<<"@THIS\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
    out<<"@THAT\nD=M\n@SP\nM=M+1\nA=M-1\nM=D\n";
    out<<"@SP\nD=M\n@0\nD=D-A\n@5\nD=D-A\n@ARG\nM=D\n";
    out<<"@SP\nD=M\n@LCL\nM=D\n";
    out<<"@Sys.init\n0;JMP\n";
    out<<"//first step\n";
    
    
    for (const auto & file : directory_iterator(name_in)){
        if(file.path().extension()==".vm"){
            parser_vm sub(file.path());sub.write();
        }
    }
    out.close();
    cout<<"success\n";
return;
}

int main(){
    filesystem::path name="/Users/tomy/computing-systems/nand2tetris/projects/08/FunctionCalls/NestedCall";
    solver(name,"NestedCall.asm");

}


