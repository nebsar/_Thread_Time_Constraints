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
#include <chrono>

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
    this_thread::sleep_for(chrono::milliseconds(3));
    chrono::steady_clock::time_point tp = chrono::steady_clock::now() + chrono::microseconds(4);
    this_thread::sleep_until(tp);

    /* Mutex*/
    mutex mu;
    lock_guard<mutex> locker(mu);
    unique_lock<mutex> ulocker(mu);
    ulocker.try_lock();
   // ulocker.try_lock_for(chrono::nanoseconds(500));
   // ulocker.try_lock_until(tp);
    ulocker.lock();
    ulocker.unlock();

    /* Condition Variable*/
    condition_variable cond;
    cond.wait_for(ulocker, chrono::microseconds(2));
    cond.wait_until(ulocker, tp);
    
    
    /* Future Promise*/
    promise<int> p;
    future<int> fu = p.get_future();
    fu.get();
    fu.wait();
    fu.wait_for(chrono::milliseconds(2));
    fu.wait_until(tp);


    /* async*/
    future<int> f = async(factorial, 6);


    /*packaged_task*/
    packaged_task<int(int) > pac(factorial);
    packaged_task<int() > p1(bind(factorial, 6));
    future<int> fu2 = pac.get_future();
    pac(6);

}

