#include <iostream>
#include <chrono>
using namespace std;

int efib(int n){
    if(n < 4 && n >-4){
        return n;
    }
    else if(n > 0){
        return efib(n-1) + efib(n - 2) + efib(n - 3);
    }
    else{
        return efib(n + 1) + efib(n + 2) + efib(n + 3);
    }
}
int test1(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i){
        ++sum;
    }
    return sum;
}
int test2(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j) {
            ++sum;
        }
    }
    return sum;
}
int test3(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n * n; ++j) {
            ++sum;
        }
    }
    return sum;
}
int test4(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < i; ++j) {
            ++sum;
        }
    }
    return sum;
}

/*
int efib(int n){
    if(n < 4 && n >-4){
        return n;
    }
    else if(n > 0){
        return efib(n-1) + efib(n - 2) + efib(n - 3);
    }
    else{
        return efib(n + 1) + efib(n + 2) + efib(n + 3);
    }
}
*/
int main() {

/*
    for( int i = 0; i < 20; ++i){
        cout << "efib(" << i << "): " << efib(i) << endl;
    }

    for( int i = 0; i > -25; --i){
        cout << "efib(" << i << "): " << efib(i) << endl;
    }


    int i = 25;

    cout << "efib(" << i << "): " << efib(i) << endl;
*/

    int n= 1500;
    auto begin = std::chrono::high_resolution_clock::now();

    cout << "Test 1: " << test1(n) << endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time 1: " << elapsed.count() << endl;

    begin = std::chrono::high_resolution_clock::now();
    cout << "Test 2: " << test2(n) << endl;
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time 2: " << elapsed.count()<< endl;

    begin = std::chrono::high_resolution_clock::now();
    cout << "Test 3: " << test3(n) << endl;
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time 3: " << elapsed.count() << endl;

    begin = std::chrono::high_resolution_clock::now();
    cout << "Test 4: " << test4(n) << endl;
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Time 4: " << elapsed.count() << endl;



    return 0;
}
