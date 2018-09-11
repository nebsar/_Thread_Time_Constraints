/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Eagleye
 *
 * Created on September 11, 2018, 1:51 PM
 */

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

/*
 * 
 */

int factorial(int n) {
    int result = 1;

    for (int i = n; i > 1; i--) {
        result *= i;
    }
    return result;
}

int main() {
    /* Thread*/
    thread t1(factorial, 6);

    /* Mutex*/
    mutex mu;
    lock_guard<mutex> locker1(mu);
    unique_lock<mutex> locker2;
    locker2.lock();
    locker2.unlock();

    /* Condition Variable*/
    condition_variable cond;


    /* Future Promise*/
    promise<int> p;
    future<int> fu = p.get_future();


    /* async*/
    future<int> f = async(factorial, 6);
    
    
    /*packaged_task*/
    packaged_task<int(int)> pac(factorial);
    packaged_task<int()> p1(bind(factorial,6));

}

