#include<thread>
#include<iostream>
using namespace std;

class TA {
public:
    int &m_i;
    TA(int &i):m_i(i){}
    void operator()(){
        cout<<"TA thread running"<<endl;
        cout<<"m_i1="<<m_i<<endl;
        cout<<"m_i2="<<m_i<<endl;
        cout<<"m_i3="<<m_i<<endl;
        cout<<"m_i4="<<m_i<<endl;
        cout<<"m_i5="<<m_i<<endl;
        cout<<"m_i6="<<m_i<<endl;
    }
};

void MyPrint() {
    cout<<"thread start runing1"<<endl;
    cout<<"thread start runing2"<<endl;
    cout<<"thread start runing3"<<endl;
    cout<<"thread start runing4"<<endl;
    cout<<"thread start runing5"<<endl;
    cout<<"thread start runing6"<<endl;
}

int main(){
    thread myobj(MyPrint);
    if (myobj.joinable()) {
        cout<<"1: joinable==true"<<endl;
    }else {
        cout<<"1: joinable=false"<<endl;
    }
    //myobj.join();
    myobj.detach();
    if (myobj.joinable()) {
        cout<<"2: joinable==true"<<endl;
    }else {
        cout<<"2: joinable=false"<<endl;
    }

    int a = 6;
    TA ta(a);
    thread myobj1(ta);
    myobj1.detach();

    cout<<"I Love China"<<endl;
    return 0;
}
