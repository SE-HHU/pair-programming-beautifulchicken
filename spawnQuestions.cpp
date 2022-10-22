#include <bits/stdc++.h>
using namespace std;

/**
* 变量说明
* 习题数量
* 整数最小值、整数最大值、真分数分母最大值
* 运算符个数、是否允许加法、是否允许减法、是否允许乘法、是否允许除法
* 是否允许括号、是否允许分数
* 已生成的题目数量
*/
int QuesNum;
int MinNatuNum,MaxNatuNum,TruFracDeno;
int OpeNum,addi,subtrac,multip,divi;
int bracket,fraction;
int ActuQuan=1;
fstream f;

struct fractionclass{
    int molecule=0,denominator=0;
};

struct FractionClassDemo{
    int molecule,denominator;
};

void gentxt();
void init();
int gcd(int a,int b);
void generate();
void operatorsBuilding(int operater[]);
void caculate(string s);
void mutiCaculate(string str,stack<struct FractionClassDemo> stt);

int main(){
    srand((int)time(0));
    init();
    while(ActuQuan<=QuesNum){
        generate();
        ActuQuan++;
    }
    return 0;
}

void gentxt(){
    //创建Exercises和Answers文件
    f.open("Exercises.txt",ios::out);
    f.close();
    f.open("Answers.txt",ios::out);
    f.close();
}

void init(){
    /**
    * 初始化函数
    * 输入需要的习题数量
    * 输入整数范围以及真分数分母范围
    * 输入运算符个数
    * 确定是否出现加减运算运算符及是否出现括号、分数
    */
    cout<<"请输入您需要生成的习题数量: ";
    cin>>QuesNum;
    cout<<"请输入整数最小值: ";
    cin>>MinNatuNum;
    cout<<"请输入整数最大值: ";
    cin>>MaxNatuNum;
    cout<<"请输入真分数分母最大值: ";
    cin>>TruFracDeno;
    cout<<"请输入运算符个数(不超过3): ";
    while(cin>>OpeNum){
        if(OpeNum>3)
            cout<<"请输入1-3之间的整数！"<<endl<<"请输入运算符个数(不超过3): ";
        else	break;
    }
    cout<<"是否允许加法(1-允许,0-不允许)? ";
    cin>>addi;
    cout<<"是否允许减法(1-允许,0-不允许)? ";
    cin>>subtrac;
    cout<<"是否允许乘法(1-允许,0-不允许)? ";
    cin>>multip;
    cout<<"是否允许除法(1-允许,0-不允许)? ";
    cin>>divi;
    cout<<"是否允许括号(1-允许,0-不允许)? ";
    cin>>bracket;
    cout<<"是否允许分数(1-允许,0-不允许)? ";
    cin>>fraction;
    cout<<endl;
    return ;
}

int gcd(int a,int b){
    return b>0 ? gcd(b,a%b):a;
}

void generate(){
    /**
    * 生成满足用户需求的题目
    * 考虑最多生成3个运算符,并且是用户允许存在的运算符
    * 考虑生成括号(仅在加减、乘除出现的情况下才会出现括号)
    * 考虑生成分数(真分数或者带分数)
    */
    f.open("Exercises.txt",ios::out|ios::app);
    f<<ActuQuan<<": ";

    int operater[10];
    /**
    * 随机生成运算符
    * 判断生成的运算符是否满足用户需求
    */
    memset(operater,0,sizeof(operater));
    operatorsBuilding(operater);


    /**
    * 如果是a个运算符，就要生成a+1个数字参与运算
    * 数字中还要有几率生成分数，即随机生成 数字 真分数 带分数
    * 可以先生成满足条件的整数部分，然后再生成分数部分，分子一定小于分母
    * fl控制着生成分数的几率
    * br控制着生成括号的几率
    * 不考虑循环嵌套的情况
    * wdr控制生成括号的地方，当存在a个运算符，就存在a个地方生成括号
    */
    string str="";


    int br=rand()%100+1,wdr=0;
    if(bracket==1&&br<=25&&OpeNum!=1)	wdr=rand()%OpeNum+1;
    int opeNum[10];
    int fract[10][5];
    memset(opeNum,0,sizeof(opeNum));
    memset(fract,0,sizeof(fract));

    struct fractionclass fracti[10];
    stack<int> st;

    for(int i=1;i<=OpeNum+1;i++){
        if(wdr!=0&&i==wdr){
            f<<"( ";
            st.push(0);
        }
        opeNum[i]=rand()%MaxNatuNum+MinNatuNum;
        if(operater[i-1]==4){
            while(opeNum[i]==0){
                opeNum[i]=rand()%MaxNatuNum+MinNatuNum;
            }
        }
        int tmp=opeNum[i];

        int fl=rand()%100+1;
        if(fl<=25&&opeNum[i]==0)	;
        else{
            f<<opeNum[i];
            if(fl>25)	str=str+to_string(opeNum[i])+",1.";
        }
        if(fl<=25){
            fract[i][2]=rand()%TruFracDeno+2;
            fract[i][1]=rand()%(fract[i][2]-1)+1;
            int gcdNum=gcd(fract[i][2],fract[i][1]);
            fract[i][2]/=gcdNum,fract[i][1]/=gcdNum;

            fracti[i].denominator=fract[i][2];
            fracti[i].molecule=fract[i][1]+tmp*fracti[i].denominator;

            if(opeNum==0)	f<<fract[i][1]<<"/"<<fract[i][2];
            else if(opeNum!=0)	f<<"U"<<fract[i][1]<<"/"<<fract[i][2];

            str=str+to_string(fracti[i].molecule)+","+to_string(fracti[i].denominator)+".";
            if(wdr!=0&&i==wdr+1){
                f<<" )";
                while(!st.empty()&&st.top()!=0){
                    if(st.top()==1)		str+="+.";
                    if(st.top()==2)		str+="-.";
                    if(st.top()==3)		str+="*.";
                    if(st.top()==4)		str+="/.";
                    st.pop();
                }
                st.pop();
            }
            if(i!=OpeNum+1){
                if(operater[i]==1){
                    f<<" + ";
                    while(!st.empty()&&(st.top()==3||st.top()==4||st.top()==1||st.top()==2)){
                        if(st.top()==1)		str+="+.";
                        if(st.top()==2)		str+="-.";
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(1);

                }
                else if(operater[i]==2){
                    f<<" - ";
                    while(!st.empty()&&(st.top()==3||st.top()==4||st.top()==1||st.top()==2)){
                        if(st.top()==1)		str+="+.";
                        if(st.top()==2)		str+="-.";
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(2);

                }
                else if(operater[i]==3){
                    f<<" * ";
                    while(!st.empty()&&(st.top()==3||st.top()==4)){
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(3);

                }
                else if(operater[i]==4){
                    f<<" ÷ ";
                    while(!st.empty()&&(st.top()==3||st.top()==4)){
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(4);

                }
            }
        }else{
            if(wdr!=0&&i==wdr+1){
                f<<" )";
                while(!st.empty()&&st.top()!=0){
                    if(st.top()==1)		str+="+.";
                    if(st.top()==2)		str+="-.";
                    if(st.top()==3)		str+="*.";
                    if(st.top()==4)		str+="/.";
                    st.pop();
                }
                st.pop();
            }
            if(i!=OpeNum+1){
                if(operater[i]==1){
                    f<<" + ";
                    while(!st.empty()&&(st.top()==3||st.top()==4||st.top()==1||st.top()==2)){
                        if(st.top()==1)		str+="+.";
                        if(st.top()==2)		str+="-.";
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(1);

                }
                else if(operater[i]==2){
                    f<<" - ";
                    while(!st.empty()&&(st.top()==3||st.top()==4||st.top()==1||st.top()==2)){
                        if(st.top()==1)		str+="+.";
                        if(st.top()==2)		str+="-.";
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(2);

                }
                else if(operater[i]==3){
                    f<<" * ";
                    while(!st.empty()&&(st.top()==3||st.top()==4)){
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(3);

                }
                else if(operater[i]==4){
                    f<<" ÷ ";
                    while(!st.empty()&&(st.top()==3||st.top()==4)){
                        if(st.top()==3)		str+="*.";
                        if(st.top()==4)		str+="/.";
                        st.pop();
                    }
                    st.push(4);

                }
            }
            continue;
        }
    }
    while(!st.empty()){
        if(st.top()==1)		str+="+.";
        if(st.top()==2)		str+="-.";
        if(st.top()==3)		str+="*.";
        if(st.top()==4)		str+="/.";
        st.pop();
    }
    str+="@";
    f<<" ="<<endl;


    f.close();
    caculate(str);
    return ;
}

void operatorsBuilding(int operater[]){
    /**
    * 随机生成运算符
    * 判断生成的运算符是否满足用户需求
    */
    for(int i=1;i<=OpeNum;i++){
        bool flag=false;
        operater[i]=rand()%4+1;
        while(flag==false){
            if(operater[i]==1&&addi==1)		flag=true;
            if(operater[i]==2&&subtrac==1)	flag=true;
            if(operater[i]==3&&multip==1)	flag=true;
            if(operater[i]==4&&divi==1)		flag=true;
            operater[i]=rand()%4+1;
        }
    }
}

void caculate(string str){
    /**
    * 计算后缀表达式的答案
    * 输出答案到文件中
    */

    stack<struct FractionClassDemo> stt;

    int ansInt=0,ansMole=0,ansDeno=0;
    f.open("Answers.txt",ios::out|ios::app);

    f<<ActuQuan<<": ";

    mutiCaculate(str,stt);

    ansMole=stt.top().molecule;
    ansDeno=stt.top().denominator;

    ansInt=ansMole/ansDeno;
    ansMole=ansMole%ansDeno;

    int p=gcd(ansMole,ansDeno);
    ansMole/=p;
    ansDeno/=p;

    if(ansInt==0&&ansMole!=0&&ansDeno!=0)	f<<ansMole<<"/"<<ansDeno;
    else{
        f<<ansInt;
        if(ansMole!=0&&ansDeno!=0)	f<<"U"<<ansMole<<"/"<<ansDeno;
    }

    f<<endl;
    f.close();
}

void mutiCaculate(string str,stack<struct FractionClassDemo> stt){
    /**
    * 具体处理后缀表达式，并进行初步运算
    */
    for(int i=0;i<str.length();i++){
        if(str[i]=='@')		break;
        if(str[i]=='.')		continue;
        if(str[i]>='0'&&str[i]<='9'){
            string Numz="",Numm="";
            int numz,numm;
            if(str[i]>='0'&&str[i]<='9'){
                Numz+=str[i];
                i++;
                while(str[i]>='0'&&str[i]<='9'){
                    Numz+=str[i];
                    i++;
                }
                if(str[i]==','){
                    numz=stoi(Numz);
                    i++;
                }
            }

            if(str[i]>='0'&&str[i]<='9'){
                Numm+=str[i];
                i++;
                while(str[i]>='0'&&str[i]<='9'){
                    Numm+=str[i];
                    i++;
                }
                if(str[i]=='.'){
                    numm=stoi(Numm);

                }
            }
            struct FractionClassDemo a;
            a.molecule=numz;
            a.denominator=numm;
            stt.push(a);
        }
        if(str[i]=='+'){
            struct FractionClassDemo ope1=stt.top();
            stt.pop();
            struct FractionClassDemo ope2=stt.top();
            stt.pop();


            struct FractionClassDemo answer;
            answer.molecule=ope1.molecule*ope2.denominator+ope2.molecule*ope1.denominator;
            answer.denominator=ope1.denominator*ope2.denominator;
            stt.push(answer);
        }
        if(str[i]=='-'){
            struct FractionClassDemo ope2=stt.top();
            stt.pop();
            struct FractionClassDemo ope1=stt.top();
            stt.pop();


            struct FractionClassDemo answer;
            answer.molecule=ope1.molecule*ope2.denominator-ope2.molecule*ope1.denominator;
            answer.denominator=ope1.denominator*ope2.denominator;
            stt.push(answer);
        }
        if(str[i]=='*'){
            struct FractionClassDemo ope1=stt.top();
            stt.pop();
            struct FractionClassDemo ope2=stt.top();
            stt.pop();

            struct FractionClassDemo answer;
            answer.molecule=ope1.molecule*ope2.molecule;
            answer.denominator=ope1.denominator*ope2.denominator;
            stt.push(answer);
        }
        if(str[i]=='/'){
            struct FractionClassDemo ope2=stt.top();
            stt.pop();
            struct FractionClassDemo ope1=stt.top();
            stt.pop();

            struct FractionClassDemo answer;
            answer.molecule=ope1.molecule*ope2.denominator;
            answer.denominator=ope1.denominator*ope2.molecule;
            stt.push(answer);
        }
    }
}