#include<iostream>
#include<memory>
#include "Polynomial.h"
using namespace std;


int main()
{
    string x1;
    string x2;
    cout<<"enter the first Polynomial: ";
    cin>>x1;
    cout<<"enter the secound Polynomial: ";
    cin>>x2;


    unique_ptr<Polynomial> p(new Polynomial(x1));
    unique_ptr<Polynomial> p2(new Polynomial(x2));
    cout<<endl<<"p:";
    p->print();
    cout<<endl<<"p2:";
    p2->print();

    unique_ptr<Polynomial> p3(new Polynomial());
    p3=p3->add(p,p2);
    cout<<endl<<"p3=p+p2";
    p3->print();

    unique_ptr<Polynomial> p4(new Polynomial());
    p4=p4->subtract(p,p2);
    cout<<endl<<"p4=p-p2";
    p4->print();

    unique_ptr<Polynomial> p5(new Polynomial());
    p5=p5->multiply(p,p2);
    cout<<"p5=p*p2";
    p5->print();

    return 0;
}



