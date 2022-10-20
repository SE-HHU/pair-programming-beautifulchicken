#include <bits/stdc++.h>
using namespace std;
const int maxn=1000;
string str[maxn],my[maxn],ques[maxn];
int ppp[maxn][2];
vector<int> correct,wrong;

void start(){
    int tmp=0,ant=0,sf=0;

    ifstream infile;
    infile.open("Answers.txt", ios::in);
    string buf;
    while (getline(infile,buf))
    {
        str[tmp]=buf;
        tmp++;
    }

    ifstream infileque;
    infileque.open("Exercises.txt", ios::in);
    string buff;
    while (getline(infileque,buff))
    {
        ques[sf]=buff;
        sf++;
    }

    ifstream infiledou;
    infiledou.open("Homework.txt", ios::in);
    string buffer;
    while (getline(infiledou,buffer))
    {
        my[ant]=buffer;
        ant++;
    }

    for(int i=0;i<max(ant,tmp);i++){
        if(str[i]==my[i]){
            correct.push_back(i+1);
        }else	wrong.push_back(i+1);
    }
    cout<<"Correct: "<<correct.size()<<" (";
    for(int i=0;i<correct.size();i++){
        cout<<correct[i];
        if(i!=correct.size()-1)	cout<<",";
    }
    cout<<")"<<endl;
    cout<<"Wrong: "<<wrong.size()<<" (";
    for(int i=0;i<wrong.size();i++){
        cout<<wrong[i];
        if(i!=wrong.size()-1)	cout<<",";
    }
    cout<<")"<<endl;

    int repe=0;
    for(int i=0;i<tmp;i++){
        for(int j=0;j<tmp;j++){
            bool flag=true;
            if(str[j]!=str[i])	continue;
            else{
                //判断i和j的运算数和运算符号是否一样
                string a="";
                for(int p=0;p<str[i].length();p++){
                    if(str[i][p]=='+'&&str[j].find("+")!=string::npos)	flag=false;
                    if(str[i][p]=='-'&&str[j].find("+")!=string::npos)	flag=false;
                    if(str[i][p]=='*'&&str[j].find("+")!=string::npos)	flag=false;
                    if(str[i][p]=='/'&&str[j].find("+")!=string::npos)	flag=false;
                    if(str[i][p]>='0'&&str[i][p]<='9'){
                        a+=str[i][p];
                        p++;
                        while(str[i][p]!=' '){
                            a+=str[i][p];
                            p++;
                        }
                        if(str[j].find(a)!=string::npos)	flag=false;
                    }
                }
            }
            if(flag==true){
                ppp[repe][0]=i;
                ppp[repe][1]=j;
                repe++;
            }
        }
    }
    cout<<"Repeat:"<<repe<<endl;
    if(repe!=0){
        cout<<"RepeatDetail:"<<endl;
        for(int i=0;i<repe;i++){
            cout<<"("<<i<<") "<<ppp[i][0]<<","<<ques[ppp[i][0]]<<" Repeat "<<ppp[i][1]<<","<<ques[ppp[i][1]]<<endl;
        }
    }
}
