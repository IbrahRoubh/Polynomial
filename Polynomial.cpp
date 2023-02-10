#include <iostream>
#include<memory>
#include<vector>
#include<string.h>
#include <sstream>
#include "Polynomial.h"
using namespace std;


#define S_Acii_Num 48
#define B_Acii_Num 57
#define S_Acii_Char1 65
#define B_Acii_Char1 90
#define S_Acii_Char2 97
#define B_Acii_Char2 122



bool isNumber(char c)
{
    if(c>=S_Acii_Num&&c<=B_Acii_Num)
    return true;
    else
    return false;

}
bool isLetter(char c)
{
    if((c>=S_Acii_Char1&&c<=B_Acii_Char1)||(c>=S_Acii_Char2&&c<=B_Acii_Char2))
        return true;
    else
        return false;
}
int convertNum(string s,int *index)
{
    int num;
    int i=*index,j=0;
    string str;
    while(1)
    {
        *index=*index+1;
        j++;
     if(!isNumber(s[*index]))
     {
         *index=*index-1;
         break;
     }
    }
    str=s.substr(i,j);
    num=stoi(str);
    return num;
}

string convertStr(string s,int *index)
{
    string str;
    int i=*index,j=0;
    while(1)
    {
        j++;
        *index=*index+1;
        if(!isLetter(s[*index]))
        {
            *index=*index-1;
            break;
        }
    }
    str=s.substr(i,j);
    return str;
}
bool isSign(char c)
{
    if(c=='-'||c=='+')
    return true;
        else
    return false;
}




    vector<int> v1;//to keep the coefficient العامل
    vector<int> v2;//to keep  the exponent الاس
    vector<string> v3;//to keep the variables المتغير

vector<int> Polynomial::getv1()
   {
       return v1;
   }
vector<int> Polynomial::getv2()
   {
       return v2;
   }
vector<string> Polynomial::getv3()
   {
       return v3;
   }
void Polynomial::setv1(vector<int> v)
   {
       v1=v;
   }
void Polynomial::setv2(vector<int> v)
   {
       v2=v;
   }
void Polynomial::setv3(vector<string> v)
   {
       v3=v;
   }



Polynomial::Polynomial(string s)
    {
     for(int i=0;i<s.length();i++)
     {
         bool ch1=false,ch2=false,ch3=false,sign=false;
         string variables;
         int coefficient,exponent;
         if(s[i]=='-')
         {
             sign=true;

         }
         if(isSign(s[i]))
         {
             i++;
         }

            while(1)
            {
                if(isSign(s[i])||i>=s.length())//to break while when s[i]= - or + (or when we reach the end of s)
                {
                    i--;
                    if(ch2==true)
                    {
                        if(exponent==0)
                            break;
                    }else
                    {
                       exponent=1;
                    }
                    if(ch3==true)
                    {
                        if(coefficient==0)
                            break;
                    }else
                    {
                        coefficient=1;
                    }
                    if(ch1==false)
                    {
                        variables="00";
                    }
                    if(sign)
                    {
                    coefficient=coefficient*(-1);
                    }

                    v1.insert(v1.end(),coefficient);
                    v2.insert(v2.end(),exponent);
                    v3.insert(v3.end(),variables);
                    break;
                }

                if(isLetter(s[i]))
                {
                    variables=convertStr(s,&i);
                    ch1=true;
                }
                 if(isNumber(s[i]))
                {
                    if(ch1)
                    {
                        exponent=convertNum(s,&i);
                        ch2=true;
                    }else
                    {
                        coefficient=convertNum(s,&i);
                        ch3=true;
                    }

                }
                i++;
            }
    }


        for(int i=0;i<v1.size()-1;i++)
        {
            int temp;
            string tempstr;
            int greatindex=i;
            for(int j=i+1;j<v1.size();j++)
            {
                if(v2[j]>v2[greatindex])
                {
                    greatindex=j;
                }
                if(v2[j]==v2[greatindex])
                {
                    if(v3[greatindex]=="00")
                    {
                        greatindex=j;
                    }
                }
            }
            if(greatindex!=i)
            {
                temp=v1[greatindex];
                v1[greatindex]=v1[i];
                v1[i]=temp;

                temp=v2[greatindex];
                v2[greatindex]=v2[i];
                v2[i]=temp;

                tempstr=v3[greatindex];
                v3[greatindex]=v3[i];
                v3[i]=tempstr;
            }
        }



};
Polynomial::Polynomial()
    {

    };
unique_ptr<Polynomial> Polynomial::add(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2)
   {
     unique_ptr<Polynomial> p3(new Polynomial());
    int i=0,j=0;
    vector<int> pv1,pv2;
    vector<string> pv3;
    while(1)
    {
        if(i<p1->getv1().size()&&j<p2->getv1().size())
        {
            if((p1->getv2())[i]==(p2->getv2())[j])
            {
                if((p1->getv3())[i]==(p2->getv3())[j])
                {
                    int num=((p1->getv1())[i])+((p2->getv1())[j]);
                    if(num!=0)
                    {
                    pv1.insert(pv1.end(),num);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    }
                    i++;
                    j++;
                }else
                {
                    if((p1->getv3())[i]>(p2->getv3())[j])
                    {
                        pv1.insert(pv1.end(),(p1->getv1())[i]);
                        pv2.insert(pv2.end(),(p1->getv2())[i]);
                        pv3.insert(pv3.end(),(p1->getv3())[i]);
                        i++;
                    }else
                    {
                        pv1.insert(pv1.end(),(p2->getv1())[j]);
                        pv2.insert(pv2.end(),(p2->getv2())[j]);
                        pv3.insert(pv3.end(),(p2->getv3())[j]);
                        j++;
                    }
                }
            }else
            {
                if(((p1->getv2())[i])>((p2->getv2())[i]))
                {
                    pv1.insert(pv1.end(),(p1->getv1())[i]);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    i++;
                }else
                {
                    pv1.insert(pv1.end(),(p2->getv1())[j]);
                    pv2.insert(pv2.end(),(p2->getv2())[j]);
                    pv3.insert(pv3.end(),(p2->getv3())[j]);
                    j++;
                }
            }
        }else
        {
            if(j>=p2->getv1().size())
            {
                while(1)
                {
                    if(i>=p1->getv1().size())
                        break;
                    pv1.insert(pv1.end(),(p1->getv1())[i]);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    i++;
                }
            }else
            {
                 while(1)
                {
                    if(j>=p2->getv1().size())
                        break;
                    pv1.insert(pv1.end(),(p2->getv1())[j]);
                    pv2.insert(pv2.end(),(p2->getv2())[j]);
                    pv3.insert(pv3.end(),(p2->getv3())[j]);
                    j++;
                }
            }
            break;
        }
    }
      p3->setv1(pv1);
        p3->setv2(pv2);
        p3->setv3(pv3);
        return p3;
   }

unique_ptr<Polynomial>Polynomial::subtract(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2)
   {
     unique_ptr<Polynomial> p3(new Polynomial());
    int i=0,j=0;
    vector<int> pv1,pv2;
    vector<string> pv3;
    while(1)
    {
        if(i<p1->getv1().size()&&j<p2->getv1().size())
        {
            if((p1->getv2())[i]==(p2->getv2())[j])
            {
                if((p1->getv3())[i]==(p2->getv3())[j])
                {
                    int num=((p1->getv1())[i])-((p2->getv1())[j]);
                    if(num!=0)
                    {
                    pv1.insert(pv1.end(),num);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    }
                    i++;
                    j++;
                }else
                {
                    if((p1->getv3())[i]>(p2->getv3())[j])
                    {
                        pv1.insert(pv1.end(),(p1->getv1())[i]);
                        pv2.insert(pv2.end(),(p1->getv2())[i]);
                        pv3.insert(pv3.end(),(p1->getv3())[i]);
                        i++;
                    }else
                    {
                        pv1.insert(pv1.end(),((p2->getv1())[j])*(-1));
                        pv2.insert(pv2.end(),(p2->getv2())[j]);
                        pv3.insert(pv3.end(),(p2->getv3())[j]);
                        j++;
                    }
                }
            }else
            {
                if(((p1->getv2())[i])>((p2->getv2())[i]))
                {
                    pv1.insert(pv1.end(),(p1->getv1())[i]);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    i++;
                }else
                {
                    pv1.insert(pv1.end(),((p2->getv1())[j])*(-1));
                    pv2.insert(pv2.end(),(p2->getv2())[j]);
                    pv3.insert(pv3.end(),(p2->getv3())[j]);
                    j++;
                }
            }
        }else
        {
            if(j>=p2->getv1().size())
            {
                while(1)
                {
                    if(i>=p1->getv1().size())
                        break;
                    pv1.insert(pv1.end(),(p1->getv1())[i]);
                    pv2.insert(pv2.end(),(p1->getv2())[i]);
                    pv3.insert(pv3.end(),(p1->getv3())[i]);
                    i++;
                }
            }else
            {
                 while(1)
                {
                    if(j>=p2->getv1().size())
                        break;
                    pv1.insert(pv1.end(),((p2->getv1())[j])*(-1));
                    pv2.insert(pv2.end(),(p2->getv2())[j]);
                    pv3.insert(pv3.end(),(p2->getv3())[j]);
                    j++;
                }
            }
            break;
        }
    }
      p3->setv1(pv1);
        p3->setv2(pv2);
        p3->setv3(pv3);
        return p3;
   }

unique_ptr<Polynomial> Polynomial::multiply(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2)
   {
    unique_ptr<Polynomial> p3(new Polynomial());
    vector<int> pv1,pv2;
    vector<string> pv3;
    for(int i=0;i<(p1->getv1()).size();i++)
    {
        for(int j=0;j<(p2->getv1()).size();j++)
        {
            int num=((p1->getv1())[i])*((p2->getv1())[j]);

            pv1.insert(pv1.end(),num);

            if(((p1->getv3())[i])==((p2->getv3())[j])&&((p1->getv3())[i])!="00")
            {
                pv3.insert(pv3.end(),((p1->getv3())[i]));
                int n=((p1->getv2())[i])+((p2->getv2())[j]);
                pv2.insert(pv2.end(),n);
            }else
            {
                if(((p1->getv3())[i])==((p2->getv3())[j]))
                {
                    pv3.insert(pv3.end(),((p1->getv3())[i]));
                    pv2.insert(pv2.end(),1);
                }else if(((p1->getv3())[i])=="00")
                {
                    pv3.insert(pv3.end(),((p2->getv3())[j]));
                    pv2.insert(pv2.end(),((p2->getv2())[j]));
                }else if(((p2->getv3())[j])=="00")
                {
                    pv3.insert(pv3.end(),((p1->getv3())[i]));
                    pv2.insert(pv2.end(),((p1->getv2())[i]));
                }else
                {
                 string s=((p1->getv3())[i])+((p2->getv3())[j]);
                 int a=((p1->getv2())[i])+((p2->getv2())[j]);
                 pv3.insert(pv3.end(),s);
                 pv2.insert(pv2.end(),a);
                }
            }
        }
    }

        auto d1=pv1.begin();
        auto d2=pv2.begin();
        auto d3=pv3.begin();
   for(int i=0;i<pv1.size();i++)
    {
        auto r1=d1;
        auto r2=d2;
        auto r3=d3;

        for(int j=i+1;j<pv1.size();j++)
        {
         r1++;
         r2++;
         r3++;
         if(pv2[i]==pv2[j]&&pv3[i]==pv3[j])
         {
             pv1[i]=pv1[i]+pv1[j];
             pv1.erase(r1);
             pv2.erase(r2);
             pv3.erase(r3);
             r1--;
             r2--;
             r3--;

         }
        }
        if(pv1[i]==0)
        {
            pv1.erase(d1);
            pv2.erase(d2);
            pv3.erase(d3);
            d1--;
            d2--;
            d3--;
        }
        d1++;
        d2++;
        d3++;
    }

       for(int i=0;i<pv1.size()-1;i++)
        {
            int temp;
            string tempstr;
            int greatindex=i;
            for(int j=i+1;j<pv1.size();j++)
            {
                if(pv2[j]>pv2[greatindex])
                {
                    greatindex=j;
                }
                if(pv2[j]==pv2[greatindex])
                {
                    if(pv3[greatindex]=="00")
                    {
                        greatindex=j;
                    }
                }
            }
            if(greatindex!=i)
            {
                temp=pv1[greatindex];
                pv1[greatindex]=pv1[i];
                pv1[i]=temp;

                temp=pv2[greatindex];
                pv2[greatindex]=pv2[i];
                pv2[i]=temp;

                tempstr=pv3[greatindex];
                pv3[greatindex]=pv3[i];
                pv3[i]=tempstr;
            }
        }

        p3->setv1(pv1);
        p3->setv2(pv2);
        p3->setv3(pv3);
        return p3;
   }

void Polynomial::print()
    {
        cout<<endl;
        for(int i=0;i<v1.size();i++)
        {
            bool b=false;

            if(v1[i]!=1&&v1[i]!=(-1))
            {
                cout<<v1[i];
                b=true;
            }
            if(v1[i]==(-1))
            {
                cout<<"-";
            }
            if(v3[i]!="00")
            {
                if(b)
                {
                    cout<<"*";
                }
                cout<<v3[i];
                if(v2[i]!=1)
                {
                    cout<<"^"<<v2[i];
                }
            }else
            {
                if(v1[i]==1||v1[i]==(-1))
                    cout<<"1";
            }
            cout<<" ";
            if(v1[i+1]>0&&i+1<v1.size())
            {
                cout<<"+ ";
            }
        }
        cout<<endl;
    }

