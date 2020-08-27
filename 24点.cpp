#include<iostream> 
#include<cmath>/*fabs()*/ 
#include<cstdlib>/*exit(),srand(),rand()*/ 
#include<vector>/*vector*/ 
#include<string>/*string*/ 
#include<ctime>/*time()*/ 
 
using namespace std; 
 
const double Precision=1e-10;/*比较的精度*/ 
const double M=24;/*凑数结果*/ 
const int N1=13,N2=4;/*4个从1到13的数*/ 
const int C1=5,C2=10,C3=15,C4=20;/*盘数*/ 
 
class Gamer;/*玩家的信息*/ 
class Four;/*把满足条件的四个数及其符号储存起来*/ 
ostream& operator<<(ostream& out,const Four &obj);/*输出Four类的对象*/ 
double count(double a1,int b,double a2,bool& abnormal);/*计算在运算符b(b==1时,
代表+;...)的作用下,数字a1与a2的运算结果*/ 
bool judge(double a1,int b1,double a2,int b2,double a3,int b3,double a4,int& 
code);/*判断是否能凑成M*/ 
bool judge1(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4);/*((a1@a2)@a3)@a4*/ 
bool judge2(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4);/*(a1@(a2@a3))@a4*/ 
bool judge3(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4);/*(a1@a2)@(a3@a4)*/ 
bool judge4(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4);/*a1@((a2@a3)@a4)*/ 
bool judge5(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4);/*a1@(a2@(a3@a4))*/ 
void print(ostream& out,int b);//打印算符 
void GameOn(); 
 
class Gamer 
{ 
private: 
        int score;/*得分*/ 
        int bout;/*盘数*/ 
        string name;/*姓名*/ 
public: 
       Gamer(string n,int b=C1);/*设置玩家姓名,初始化分数*/ 
       int getScore() const; 
       void setScore(char c);/*对玩家分数进行加减操作*/ 
       void print() const;/*打印玩家信息*/ 
}; 
 
Gamer::Gamer(string n,int b) 
{ 
       name=n; 
       bout=b; 
       score=bout;/*初始分数等于盘数*/ 
} 
 
int Gamer::getScore() const 
{ 
    return score; 
} 
 
void Gamer::setScore(char c) 
{ 
     switch(c)/*c='+'或'-'*/ 
   { 
     case '+':score++;break;/*回答正确,加分*/ 
     case '-':score--;break;/*回答错误,减分*/ 
     default:cout<<"参数错误!!!"<<endl; 
   } 
} 
 
void Gamer::print() const 
{ 
     cout<<"玩家"<<name<<"的得分情况:"<<endl; 
     cout<<"盘数:"<<bout<<"\t"<<"初始分:"<<bout<<"\t"<<"最后得分:"<<score<<endl; 
} 
 
class Four 
{ 
private: 
   int Sign[3];/*储存运算符*/ 
   int Q[N2];/*储存原始顺序,即未排序前的顺序,是输出函数的依据*/ 
   int method;/*方法的代号,记下由这四个数字得到24的一种方法(有可能有多种得到24
的方法,但只选最先找到的那种方法)*/ 
public: 
   Four(int a=0,int b=0,int c=0,int d=0,int m=0,int s1=0,int s2=0,int s3=0);/*构
造函数,初始化成员数据*/ 
   void reSet(int a,int b,int c,int d,int m,int s1,int s2,int s3); 
   friend ostream& operator<<(ostream& out,const Four &obj);/*友元函数*/ 
}; 
Four::Four(int a,int b,int c,int d,int m,int s1,int s2,int s3) 
{ 
    Q[0]=a; 
    Q[1]=b; 
    Q[2]=c; 
    Q[3]=d; 
    method=m; 
    Sign[0]=s1; 
    Sign[1]=s2; 
    Sign[2]=s3; 
} 
 
void Four::reSet(int a,int b,int c,int d,int m,int s1,int s2,int s3) 
{ 
     Q[0]=a; 
     Q[1]=b; 
     Q[2]=c; 
     Q[3]=d; 
     method=m; 
     Sign[0]=s1; 
     Sign[1]=s2; 
     Sign[2]=s3; 
} 
 
ostream& operator<<(ostream& out,const Four &obj) 
{ 
         switch(obj.method) 
         { 
             case 1:/*((a1@a2)@a3)@a4*/ 
             { 
                  out<<"(("<<obj.Q[0]; 
                  print(out,obj.Sign[0]); 
                  out<<obj.Q[1]<<")"; 
                  print(out,obj.Sign[1]); 
                  out<<obj.Q[2]<<")"; 
                  print(out,obj.Sign[2]); 
                  out<<obj.Q[3]; 
                  break; 
             } 
             case 2:/*(a1@(a2@a3))@a4*/ 
             { 
                  out<<"("<<obj.Q[0]; 
                  print(out,obj.Sign[0]); 
                  out<<"("<<obj.Q[1];
                    print(out,obj.Sign[1]); 
                  out<<obj.Q[2]<<"))"; 
                  print(out,obj.Sign[2]); 
                  out<<obj.Q[3]; 
                  break; 
             } 
              
             case 3:/*(a1@a2)@(a3@a4)*/ 
             { 
                  out<<"("<<obj.Q[0]; 
                  print(out,obj.Sign[0]); 
                  out<<obj.Q[1]<<")"; 
                  print(out,obj.Sign[1]); 
                  out<<"("<<obj.Q[2]; 
                  print(out,obj.Sign[2]); 
                  out<<obj.Q[3]<<")"; 
                  break; 
             } 
              
             case 4:/*a1@((a2@a3)@a4)*/ 
             { 
                  out<<obj.Q[0]; 
                  print(out,obj.Sign[0]); 
                  out<<"(("<<obj.Q[1]; 
                  print(out,obj.Sign[1]); 
                  out<<obj.Q[2]<<")"; 
                  print(out,obj.Sign[2]); 
                  out<<obj.Q[3]<<")"; 
                  break; 
             } 
              
             case 5:/*a1@(a2@(a3@a4))*/ 
             { 
                  out<<obj.Q[0]; 
                  print(out,obj.Sign[0]); 
                  out<<"("<<obj.Q[1]; 
                  print(out,obj.Sign[1]); 
                  out<<"("<<obj.Q[2]; 
                  print(out,obj.Sign[2]); 
                  out<<obj.Q[3]<<"))"; 
                  break; 
             } 
             default:out<<"方法代码参数错误!!!"; 
         }
          out<<"="<<M; 
         return out; 
} 
 
double count(double a1,int b,double a2,bool& abnormal)/*最基本的运算单元*/ 
{ 
       switch(b) 
       { 
                case 1:return a1+a2; 
                case 2:return a1-a2; 
                case 3:return a1*a2; 
                case 4: 
                     { 
                       if(a2==0) 
                       { 
                                abnormal=true;/*被除数为0,出错了*/ 
                                return 0; 
                       } 
                       else 
                           return a1/a2; 
                     } 
                default:cout<<"代数运算符标志(参数b)错误!!!"<<endl;exit(1); 
       } 
} 
 
bool judge(double a1,int b1,double a2,int b2,double a3,int b3,double a4,int& code)/*
判断,统等各种可能*/ 
{ 
     if(judge1(a1,b1,a2,b2,a3,b3,a4)==true) 
     { 
         code=1;/*利用引用,获取方法信息*/ 
         return true;/*找到一种即退出*/ 
     } 
     if(judge2(a1,b1,a2,b2,a3,b3,a4)==true) 
     { 
         code=2; 
         return true; 
     } 
     if(judge3(a1,b1,a2,b2,a3,b3,a4)==true) 
     { 
         code=3; 
         return true; 
     } 
     if(judge4(a1,b1,a2,b2,a3,b3,a4)==true)     { 
         code=4; 
         return true; 
     } 
      
     if(judge5(a1,b1,a2,b2,a3,b3,a4)==true) 
     { 
         code=5; 
         return true; 
     } 
     return false; 
} 
 
bool judge1(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4)/*((a1@a2)@a3)@a4*/ 
{ 
     bool abnormal=false;/*接收出错信息若abnormal==true,一票否决*/ 
     double result; 
     result=count(a1,b1,a2,abnormal);/*按括号的位置,决定运算顺序*/ 
     result=count(result,b2,a3,abnormal); 
     result=count(result,b3,a4,abnormal); 
     if(abnormal==false&&fabs(result-M)<Precision)/*不要用result==M作条件因为
二者为浮点型*/ 
         return true; 
     else 
         return false; 
} 
 
bool judge2(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4)/*(a1@(a2@a3))@a4*/ 
{ 
     bool abnormal=false; 
     double result; 
     result=count(a2,b2,a3,abnormal); 
     result=count(a1,b1,result,abnormal); 
     result=count(result,b3,a4,abnormal); 
     if(abnormal==false&&fabs(result-M)<Precision) 
        return true; 
     else 
        return false; 
} 
 
bool judge3(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4)/*(a1@a2)@(a3@a4)*/ 
{ 
     bool abnormal=false; 
     double result1,result2; 
     result1=count(a1,b1,a2,abnormal); 
     result2=count(a3,b3,a4,abnormal); 
     result2=count(result1,b2,result2,abnormal); 
     if(abnormal==false&&fabs(result2-M)<Precision) 
        return true; 
     else 
        return false;; 
} 
 
bool judge4(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4)/*a1@((a2@a3)@a4)*/ 
{ 
     bool abnormal=false; 
     double result; 
     result=count(a2,b2,a3,abnormal); 
     result=count(result,b3,a4,abnormal); 
     result=count(a1,b1,result,abnormal); 
     if(abnormal==false&&fabs(result-M)<Precision) 
        return true; 
     else 
        return false; 
} 
 
bool judge5(double a1,int b1,double a2,int b2,double a3,int b3,double 
a4)/*a1@(a2@(a3@a4))*/ 
{ 
     bool abnormal=false; 
     double result; 
     result=count(a3,b3,a4,abnormal); 
     result=count(a2,b2,result,abnormal); 
     result=count(a1,b1,result,abnormal); 
     if(abnormal==false&&fabs(result-M)<Precision) 
        return true; 
     else 
        return false; 
} 
 
void print(ostream& out,int b) 
{ 
     switch(b)/*b=1,2,3,4*/ 
     { 
     case 1:out<<"+";break; 
          case 2:out<<"-";break; 
          case 3:out<<"*";break; 
          case 4:out<<"/";break; 
          default:cerr<<"算符参数错误!"<<endl; 
     } 
} 
 
void GameOn() 
{ 
     string name;/*玩家姓名*/ 
     cout<<"请输入玩家姓名:"; 
     cin>>name; 
     int frequence=0;/*已玩的盘数*/ 
     int Max=C1;/*总盘数*/ 
     char request='A';/*盘数设置信息*/ 
     cout<<"选择游戏盘数:A."<<C1<<"     B."<<C2<<"     C."<<C3<<"     D."<<C4<<":"; 
     cin>>request; 
     Four temp; 
     switch(request) 
     { 
          case 'A': 
          case 'a':Max=5;break; 
          case 'B': 
          case 'b':Max=10;break; 
          case 'C': 
          case 'c':Max=15;break; 
          case 'D': 
          case 'd':Max=20;break; 
          default:cout<<"输入选项不存在!设为默认值:A.5"<<endl;Max=5; 
     } 
     Gamer gamer(name,Max);/*设置玩家信息*/ 
     int i,j,k,l,i1,j1,k1;/*计数器*/ 
     int code=0;/*方法标记*/ 
     //int itag,jtag,ktag,ltag;/*在一定运算下的各数标记*/ 
     double P[N2];/*储存组合*/ 
     int tag=0;/*跳出循环及是否有解的标志*/ 
     char answer1='N';/*玩家的答案*/ 
     bool answer2=false;/*玩家的答案(answer1的逻辑化)*/ 
     while(frequence<Max) 
     { 
        cout<<"当前盘数/总盘数:"<<frequence+1<<"/"<<Max<<"       当前积分/初始积分:"<<gamer.getScore()<<"/"<<Max<<endl;/*当前盘数与总盘数*/ 
 srand((unsigned)time(NULL));/*随机数种子*/ 
        for(i=0;i<N2;i++) 
        { 
              P[i]=double(rand()%N1+1);/*产生1~N1之间的随机数*/ 
              cout<<P[i]<<"\t"; 
        } 
        cout<<"此组合是否能能过四则运算及括号得到24?"<<endl; 
        cout<<"Y.能      N.不能      :"; 
        cin>>answer1; 
        switch(answer1) 
        { 
             case 'Y': 
             case 'y':answer2=true;break; 
             case 'N': 
             case 'n':answer2=false;break; 
             default:cout<<"输入选项不存在!设为默认值N.不能A"<<endl;answer2=false; 
        } 
        for(i=0;i<N2;i++) 
        { 
              if(tag==1)/*一层一层地跳出,也可以直接用goto语法*/ 
               break; 
              for(j=0;j<N2;j++) 
              { 
                    if(tag==1) 
                      break; 
                    for(k=0;k<N2;k++) 
                    { 
                          if(tag==1) 
                                break; 
                          l=(0+N2-1)*N2/2-(i+j+k);/*i+j+k+l=0+1+...+N2*/ 
                          if((i!=j)&&(i!=k)&&(j!=k))/*注意条件的写法!!!*/ 
                          { 
                                for(i1=1;i1<=N2;i1++) 
                                { 
                                      if(tag==1) 
                                            break; 
                                      for(j1=1;j1<=N2;j1++) 
                                      { 
                                            if(tag==1) 
                                                  break; 
                                            for(k1=1;k1<=N2;k1++) 
                                            { 
if(judge(P[i],i1,P[j],j1,P[k],k1,P[l],code)==true) 
                                                  {   
                                                             
temp.reSet(static_cast<int>(P[i]),static_cast<int>(P[j]),static_cast<int>(P[k]),
static_cast<int>(P[l]),code,i1,j1,k1);/*封装数据*/ 
                                                             tag=1; 
                                                             break;/*跳出*/ 
                                                  } 
                                            } 
                                      } 
                                } 
                          } 
                    } 
              } 
        } 
        if(tag==0)/*无解*/ 
        { 
              if(answer2==false) 
              { 
                    cout<<"正确!此组合不能得到24."<<endl; 
                    gamer.setScore('+'); 
              } 
              else 
              { 
                    cout<<"错误!此组合不能得到24!!!"<<endl; 
                    gamer.setScore('-'); 
              } 
        } 
        else/*有解*/ 
        { 
              if(answer2==true) 
              { 
                    cout<<"正确!此组合能得到24."<<endl; 
                    gamer.setScore('+'); 
                    cout<<"比如:"<<temp<<endl; 
              } 
              else 
              { 
                    cout<<"错误!此组合能得到24!!!"<<endl; 
                    gamer.setScore('-'); 
                    cout<<"比如:"<<temp<<endl; 
              } 
        } 
        tag=0;/*清零*/ 
         cout<<endl; 
        frequence++;/*进入下一盘*/ 
     } 
     gamer.print();/*打印玩家信息*/ 
} 
 
int main() 
{ 
GameOn(); 
system("pause"); 
    
return 0; 
}

