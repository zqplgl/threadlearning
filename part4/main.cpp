#include<thread>
#include<vector>
#include<iostream>
#include<list>
#include<mutex>
using namespace std;
class A {
public:
    void inMsgRecvQueue(){
        for(int i=0; i<10000; ++i){
            cout<<"push message "<<i<<endl;
            //my_mutex1.lock();
            //my_mutex2.lock();
            std::lock(my_mutex1,my_mutex2);
            msgRecQueue.push_back(i);
            my_mutex2.unlock();
            my_mutex1.unlock();
        }
    }
    void outMsgRecvQueue(){

        for(int i=0; i<10000; ++i){
            std::lock_guard<mutex> lk_gd(my_mutex1);
            if(!msgRecQueue.empty()){
                int num = msgRecQueue.front();
                msgRecQueue.pop_front();
                cout<<"pop message "<<num<<endl;
            }else{
                cout<<"message is empty"<<endl;
            }
        }
    }
private:
    list<int> msgRecQueue;
    mutex my_mutex1;
    mutex my_mutex2;
};

int main(){
    A a;
    thread inMessageObj(&A::inMsgRecvQueue, &a);
    thread outMessageObj(&A::outMsgRecvQueue, &a);

    inMessageObj.join();
    outMessageObj.join();
}
