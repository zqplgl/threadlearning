#include<thread>
#include<vector>
#include<iostream>
#include<list>
#include<mutex>
using namespace std;

std::mutex lock1;
std::once_flag g_flag;

class SingleTon {
public:
    static SingleTon *GetInstance(){
        //if (m_instance==NULL) {
        //    std::lock_guard<std::mutex> lg_gu(lock1);
        //    if (m_instance==NULL){
        //        m_instance = new SingleTon();
        //        cout<<"init instance success"<<endl;
        //    }
        //    //lock1.unlock();
        //}
        std::call_once(g_flag, CreateInstance);

        return m_instance;
    }

    void test(){
        cout<<"hello "<<std::this_thread::get_id()<<endl;
    }

private:
    static SingleTon *m_instance;
    SingleTon(){}
    static void CreateInstance(){
        m_instance = new SingleTon();
        cout<<"init instance success"<<endl;
    }


};

SingleTon *SingleTon::m_instance = NULL;

void MyFunc(){
    SingleTon *m_instance = SingleTon::GetInstance();
    m_instance->test();
}
int main(){
    thread obj1(MyFunc);
    thread obj2(MyFunc);
    thread obj3(MyFunc);
    thread obj4(MyFunc);
    thread obj5(MyFunc);

    obj1.join();
    obj2.join();
    obj3.join();
    obj4.join();
    obj5.join();
}
