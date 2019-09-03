#include<thread>
#include<vector>
#include<iostream>
using namespace std;

void MyPrint(int i) {
    cout<<"i = "<<i<<endl;
}

int main(){
    vector<thread> mythreads;

    for(int i=0; i<10; ++i){
        mythreads.push_back(thread(MyPrint,i));
    }

    for(auto iter=mythreads.begin(); iter!=mythreads.end(); ++iter){
        iter->join();
    }

}
