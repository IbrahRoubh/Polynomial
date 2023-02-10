#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED
using namespace std;
#include<vector>
#include<memory>

class Polynomial
{
private:
    vector<int> v1;
    vector<int> v2;
    vector<string> v3;

public:
    vector<int> getv1();
    vector<int> getv2();
    vector<string> getv3();
    void setv1(vector<int> v);
    void setv2(vector<int> v);
    void setv3(vector<string> v);
    Polynomial(string s);
    Polynomial();
    static unique_ptr<Polynomial> add(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2);
    static unique_ptr<Polynomial> subtract(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2);
    static unique_ptr<Polynomial> multiply(unique_ptr<Polynomial> &p1,unique_ptr<Polynomial> &p2);
    void print();
};

#endif // POLYNOMIAL_H_INCLUDED
