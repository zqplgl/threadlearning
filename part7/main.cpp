#include<thread>
#include<vector>
#include<iostream>
#include<list>
#include<mutex>
#include<condition_variable>
using namespace std;
class A {
public:
    void inMsgRecvQueue(){
        for(int i=0; i<10000; ++i){
            cout<<"push message "<<i<<endl;
            my_mutex1.lock();
            msgRecQueue.push_back(i);
            my_con.notify_one();
            my_mutex1.unlock();
        }
    }
    void outMsgRecvQueue(){
        for(int i=0; i<10000; ++i){
            std::unique_lock<mutex> lk_gd(my_mutex1);
            my_con.wait(lk_gd, [this]{
                    if(msgRecQueue.empty())
                        return false;
                    return true;
                    });
            int num = msgRecQueue.front();
            msgRecQueue.pop_front();
            cout<<"pop message "<<num<<endl;
        }
    }
private:
    list<int> msgRecQueue;
    mutex my_mutex1;
    std::condition_variable my_con;
};

int main(){
    A a;
    thread outMessageObj(&A::outMsgRecvQueue, &a);
    thread inMessageObj(&A::inMsgRecvQueue, &a);

    inMessageObj.join();
    outMessageObj.join();
}
