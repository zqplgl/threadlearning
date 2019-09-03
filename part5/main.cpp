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
            std::unique_lock<std::mutex> uq_lock(my_mutex1, std::try_to_lock);
            if (uq_lock.owns_lock()){
                msgRecQueue.push_back(i);
            }else{

            }
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
