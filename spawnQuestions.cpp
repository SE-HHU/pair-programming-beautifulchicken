#include <bits/stdc++.h>
using namespace std;

/**
* ����˵��
* ϰ������
* ������Сֵ���������ֵ���������ĸ���ֵ
* ������������Ƿ�����ӷ����Ƿ�����������Ƿ�����˷����Ƿ��������
* �Ƿ��������š��Ƿ��������
* �����ɵ���Ŀ����
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
    //����Exercises��Answers�ļ�
    f.open("Exercises.txt",ios::out);
    f.close();
    f.open("Answers.txt",ios::out);
    f.close();
}

void init(){
    /**
    * ��ʼ������
    * ������Ҫ��ϰ������
    * ����������Χ�Լ��������ĸ��Χ
    * �������������
    * ȷ���Ƿ���ּӼ�������������Ƿ�������š�����
    */
    cout<<"����������Ҫ���ɵ�ϰ������: ";
    cin>>QuesNum;
    cout<<"������������Сֵ: ";
    cin>>MinNatuNum;
    cout<<"�������������ֵ: ";
    cin>>MaxNatuNum;
    cout<<"�������������ĸ���ֵ: ";
    cin>>TruFracDeno;
    cout<<"���������������(������3): ";
    while(cin>>OpeNum){
        if(OpeNum>3)
            cout<<"������1-3֮���������"<<endl<<"���������������(������3): ";
        else	break;
    }
    cout<<"�Ƿ�����ӷ�(1-����,0-������)? ";
    cin>>addi;
    cout<<"�Ƿ��������(1-����,0-������)? ";
    cin>>subtrac;
    cout<<"�Ƿ�����˷�(1-����,0-������)? ";
    cin>>multip;
    cout<<"�Ƿ��������(1-����,0-������)? ";
    cin>>divi;
    cout<<"�Ƿ���������(1-����,0-������)? ";
    cin>>bracket;
    cout<<"�Ƿ��������(1-����,0-������)? ";
    cin>>fraction;
    cout<<endl;
    return ;
}

int gcd(int a,int b){
    return b>0 ? gcd(b,a%b):a;
}

void generate(){
    /**
    * ���������û��������Ŀ
    * �����������3�������,�������û�������ڵ������
    * ������������(���ڼӼ����˳����ֵ�����²Ż��������)
    * �������ɷ���(��������ߴ�����)
    */
    f.open("Exercises.txt",ios::out|ios::app);
    f<<ActuQuan<<": ";

    int operater[10];
    /**
    * ������������
    * �ж����ɵ�������Ƿ������û�����
    */
    memset(operater,0,sizeof(operater));
    operatorsBuilding(operater);


    /**
    * �����a�����������Ҫ����a+1�����ֲ�������
    * �����л�Ҫ�м������ɷ�������������� ���� ����� ������
    * ���������������������������֣�Ȼ�������ɷ������֣�����һ��С�ڷ�ĸ
    * fl���������ɷ����ļ���
    * br�������������ŵļ���
    * ������ѭ��Ƕ�׵����
    * wdr�����������ŵĵط���������a����������ʹ���a���ط���������
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
                    f<<" �� ";
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
                    f<<" �� ";
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
    * ������������
    * �ж����ɵ�������Ƿ������û�����
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
    * �����׺���ʽ�Ĵ�
    * ����𰸵��ļ���
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
    * ���崦���׺���ʽ�������г�������
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