#include<thread>
#include<vector>
#include<iostream>
#include<list>
#include<mutex>
#include<atomic>
using namespace std;

//std::atomic<int> g_count(0);
int g_count = 0;

class A {
public:
    void in(){
        for(int i=0; i<10000; ++i){
            //my_lock.lock();
            g_count++;
            //my_lock.unlock();
        }

    }

    void out(){
        for(int i=0; i<10000; ++i){
            //my_lock.lock();
            g_count--;
            //my_lock.unlock();
        }
    }

private:
    std::mutex my_lock;
};
int main(){
    A a;
    thread inMessageObj(&A::in, &a);
    thread outMessageObj(&A::out, &a);

    inMessageObj.join();
    outMessageObj.join();

    cout<<"g_count  "<< g_count<<endl;
}
