#include<thread>
#include<iostream>
using namespace std;

class A{
public:
    int m_a;
    A(int a):m_a(a){
        cout<<"A(int a)<< running "<<this<<"  thread_id: "<<this_thread::get_id()<<endl;
    }

    A(const A &a):m_a(a.m_a){
        cout<<"A(const A &a)<< running "<<this<<"  thread_id: "<<this_thread::get_id()<<endl;
    }
    ~A(){
        cout<<"~A() running"<<this<<"  thread_id: "<<this_thread::get_id()<<endl;
    }

    void test1(int num){
        cout <<"work test "<<num<<endl;
    }
};

void MyPrint(const int &i, const A &a) {
    cout<<"i = "<<i<<endl;
    cout<<"thread start runing6"<<endl;
}

int main(){
    int myvar = 1;
    int &myvar1 = myvar;
    char mybuf[]="this is a test!";
    int a = 5;

    cout<<"main thread id: "<<this_thread::get_id()<<endl;

    thread myobj(MyPrint, myvar, A(a));
    myobj.detach();

    A a1(2);
    thread myobj1(&A::test1, a1, 5);
    myobj1.join();
}
