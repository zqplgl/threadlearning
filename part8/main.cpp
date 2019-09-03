#include<thread>
#include<vector>
#include<iostream>
#include<list>
#include<mutex>
#include<condition_variable>
#include<future>
using namespace std;

int MyPrint(){
    cout<<"MyPrint() function start "<<endl;

    return 5;
}
int main(){
    //std::future<int> result = std::async(std::launch::deferred, MyPrint);
    std::future<int> result = std::async(MyPrint);
    cout<<"continue***************"<<endl;

    std::packaged_task<int()> myfunc(MyPrint);
    std::thread obj(std::ref(myfunc));

    obj.join();
    std::future<int> result1 = myfunc.get_future();

    //cout<<"result "<<result.get()<<endl;
    cout<<"result "<<result1.get()<<endl;

}
