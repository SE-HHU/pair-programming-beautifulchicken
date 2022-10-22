#include <bits/stdc++.h>
using namespace std;
const int maxn=1000;

int tmp=0,ant=0,sf=0;
int ppp[maxn][2];
vector<int> correct,wrong;
string str[maxn],my[maxn],ques[maxn];
fstream f;

void filereading();
void judgingcorrect();
void judgingrepeat();

int main(){
    filereading();
    f.open("Grade.txt",ios::out);
    judgingcorrect();
    judgingrepeat();
    f.close();
    return 0;
}

void filereading(){
    /**
    * 分别打开题目、标准答案、用户答案三个文件并存入数组中方便后续操作
    */
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
}

void judgingcorrect(){
    /**
    * 判断用户答案的对错，将对错的题目都输出到文件中
    */
    for(int i=0;i<max(ant,tmp);i++){
        if(str[i]==my[i]){
            correct.push_back(i+1);
        }else	wrong.push_back(i+1);
    }

    f<<"Correct: "<<correct.size()<<" (";
    for(int i=0;i<correct.size();i++){
        f<<correct[i];
        if(i!=correct.size()-1)	f<<",";
    }
    f<<")"<<endl;

    f<<"Wrong: "<<wrong.size()<<" (";
    for(int i=0;i<wrong.size();i++){
        f<<wrong[i];
        if(i!=wrong.size()-1)	f<<",";
    }
    f<<")"<<endl;
}

void judgingrepeat(){
    /**
    * 输出所有题目中重复的题目
    */
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
    f<<"Repeat:"<<repe<<endl;
    if(repe!=0){
        f<<"RepeatDetail:"<<endl;
        for(int i=0;i<repe;i++){
            f<<"("<<i<<") "<<ppp[i][0]<<","<<ques[ppp[i][0]]<<" Repeat "<<ppp[i][1]<<","<<ques[ppp[i][1]]<<endl;
        }
    }
}