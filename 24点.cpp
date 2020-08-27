#include<iostream> 
#include<cmath>/*fabs()*/ 
#include<cstdlib>/*exit(),srand(),rand()*/ 
#include<vector>/*vector*/ 
#include<string>/*string*/ 
#include<ctime>/*time()*/ 
 
using namespace std; 
 
const double Precision=1e-10;/*�Ƚϵľ���*/ 
const double M=24;/*�������*/ 
const int N1=13,N2=4;/*4����1��13����*/ 
const int C1=5,C2=10,C3=15,C4=20;/*����*/ 
 
class Gamer;/*��ҵ���Ϣ*/ 
class Four;/*�������������ĸ���������Ŵ�������*/ 
ostream& operator<<(ostream& out,const Four &obj);/*���Four��Ķ���*/ 
double count(double a1,int b,double a2,bool& abnormal);/*�����������b(b==1ʱ,
����+;...)��������,����a1��a2��������*/ 
bool judge(double a1,int b1,double a2,int b2,double a3,int b3,double a4,int& 
code);/*�ж��Ƿ��ܴճ�M*/ 
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
void print(ostream& out,int b);//��ӡ��� 
void GameOn(); 
 
class Gamer 
{ 
private: 
        int score;/*�÷�*/ 
        int bout;/*����*/ 
        string name;/*����*/ 
public: 
       Gamer(string n,int b=C1);/*�����������,��ʼ������*/ 
       int getScore() const; 
       void setScore(char c);/*����ҷ������мӼ�����*/ 
       void print() const;/*��ӡ�����Ϣ*/ 
}; 
 
Gamer::Gamer(string n,int b) 
{ 
       name=n; 
       bout=b; 
       score=bout;/*��ʼ������������*/ 
} 
 
int Gamer::getScore() const 
{ 
    return score; 
} 
 
void Gamer::setScore(char c) 
{ 
     switch(c)/*c='+'��'-'*/ 
   { 
     case '+':score++;break;/*�ش���ȷ,�ӷ�*/ 
     case '-':score--;break;/*�ش����,����*/ 
     default:cout<<"��������!!!"<<endl; 
   } 
} 
 
void Gamer::print() const 
{ 
     cout<<"���"<<name<<"�ĵ÷����:"<<endl; 
     cout<<"����:"<<bout<<"\t"<<"��ʼ��:"<<bout<<"\t"<<"���÷�:"<<score<<endl; 
} 
 
class Four 
{ 
private: 
   int Sign[3];/*���������*/ 
   int Q[N2];/*����ԭʼ˳��,��δ����ǰ��˳��,���������������*/ 
   int method;/*�����Ĵ���,���������ĸ����ֵõ�24��һ�ַ���(�п����ж��ֵõ�24
�ķ���,��ֻѡ�����ҵ������ַ���)*/ 
public: 
   Four(int a=0,int b=0,int c=0,int d=0,int m=0,int s1=0,int s2=0,int s3=0);/*��
�캯��,��ʼ����Ա����*/ 
   void reSet(int a,int b,int c,int d,int m,int s1,int s2,int s3); 
   friend ostream& operator<<(ostream& out,const Four &obj);/*��Ԫ����*/ 
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
             default:out<<"���������������!!!"; 
         }
          out<<"="<<M; 
         return out; 
} 
 
double count(double a1,int b,double a2,bool& abnormal)/*����������㵥Ԫ*/ 
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
                                abnormal=true;/*������Ϊ0,������*/ 
                                return 0; 
                       } 
                       else 
                           return a1/a2; 
                     } 
                default:cout<<"�����������־(����b)����!!!"<<endl;exit(1); 
       } 
} 
 
bool judge(double a1,int b1,double a2,int b2,double a3,int b3,double a4,int& code)/*
�ж�,ͳ�ȸ��ֿ���*/ 
{ 
     if(judge1(a1,b1,a2,b2,a3,b3,a4)==true) 
     { 
         code=1;/*��������,��ȡ������Ϣ*/ 
         return true;/*�ҵ�һ�ּ��˳�*/ 
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
     bool abnormal=false;/*���ճ�����Ϣ����abnormal==true,һƱ���*/ 
     double result; 
     result=count(a1,b1,a2,abnormal);/*�����ŵ�λ��,��������˳��*/ 
     result=count(result,b2,a3,abnormal); 
     result=count(result,b3,a4,abnormal); 
     if(abnormal==false&&fabs(result-M)<Precision)/*��Ҫ��result==M����������Ϊ
����Ϊ������*/ 
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
          default:cerr<<"�����������!"<<endl; 
     } 
} 
 
void GameOn() 
{ 
     string name;/*�������*/ 
     cout<<"�������������:"; 
     cin>>name; 
     int frequence=0;/*���������*/ 
     int Max=C1;/*������*/ 
     char request='A';/*����������Ϣ*/ 
     cout<<"ѡ����Ϸ����:A."<<C1<<"     B."<<C2<<"     C."<<C3<<"     D."<<C4<<":"; 
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
          default:cout<<"����ѡ�����!��ΪĬ��ֵ:A.5"<<endl;Max=5; 
     } 
     Gamer gamer(name,Max);/*���������Ϣ*/ 
     int i,j,k,l,i1,j1,k1;/*������*/ 
     int code=0;/*�������*/ 
     //int itag,jtag,ktag,ltag;/*��һ�������µĸ������*/ 
     double P[N2];/*�������*/ 
     int tag=0;/*����ѭ�����Ƿ��н�ı�־*/ 
     char answer1='N';/*��ҵĴ�*/ 
     bool answer2=false;/*��ҵĴ�(answer1���߼���)*/ 
     while(frequence<Max) 
     { 
        cout<<"��ǰ����/������:"<<frequence+1<<"/"<<Max<<"       ��ǰ����/��ʼ����:"<<gamer.getScore()<<"/"<<Max<<endl;/*��ǰ������������*/ 
 srand((unsigned)time(NULL));/*���������*/ 
        for(i=0;i<N2;i++) 
        { 
              P[i]=double(rand()%N1+1);/*����1~N1֮��������*/ 
              cout<<P[i]<<"\t"; 
        } 
        cout<<"������Ƿ����ܹ��������㼰���ŵõ�24?"<<endl; 
        cout<<"Y.��      N.����      :"; 
        cin>>answer1; 
        switch(answer1) 
        { 
             case 'Y': 
             case 'y':answer2=true;break; 
             case 'N': 
             case 'n':answer2=false;break; 
             default:cout<<"����ѡ�����!��ΪĬ��ֵN.����A"<<endl;answer2=false; 
        } 
        for(i=0;i<N2;i++) 
        { 
              if(tag==1)/*һ��һ�������,Ҳ����ֱ����goto�﷨*/ 
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
                          if((i!=j)&&(i!=k)&&(j!=k))/*ע��������д��!!!*/ 
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
static_cast<int>(P[l]),code,i1,j1,k1);/*��װ����*/ 
                                                             tag=1; 
                                                             break;/*����*/ 
                                                  } 
                                            } 
                                      } 
                                } 
                          } 
                    } 
              } 
        } 
        if(tag==0)/*�޽�*/ 
        { 
              if(answer2==false) 
              { 
                    cout<<"��ȷ!����ϲ��ܵõ�24."<<endl; 
                    gamer.setScore('+'); 
              } 
              else 
              { 
                    cout<<"����!����ϲ��ܵõ�24!!!"<<endl; 
                    gamer.setScore('-'); 
              } 
        } 
        else/*�н�*/ 
        { 
              if(answer2==true) 
              { 
                    cout<<"��ȷ!������ܵõ�24."<<endl; 
                    gamer.setScore('+'); 
                    cout<<"����:"<<temp<<endl; 
              } 
              else 
              { 
                    cout<<"����!������ܵõ�24!!!"<<endl; 
                    gamer.setScore('-'); 
                    cout<<"����:"<<temp<<endl; 
              } 
        } 
        tag=0;/*����*/ 
         cout<<endl; 
        frequence++;/*������һ��*/ 
     } 
     gamer.print();/*��ӡ�����Ϣ*/ 
} 
 
int main() 
{ 
GameOn(); 
system("pause"); 
    
return 0; 
}

