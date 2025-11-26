#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <syncstream>
#include <format>

using namespace std;

namespace variant11
{
    void perform_task(string name, int duration_sec)
    {
        this_thread::sleep_for(chrono::seconds(duration_sec));
        osyncstream(cout) << format("{} done in {}s", name, duration_sec) << endl;
    }

    void work()
    {
        cout << "Start computations (Variant 11)..." << endl;
        auto start_time = chrono::high_resolution_clock::now();

        auto futA2 = async(launch::async, [] { 
            perform_task("A2", 7); 
        });

        perform_task("A1", 7);

        futA2.get(); 

        auto futB1 = async(launch::async, [] { perform_task("B1", 1); });
        auto futB3 = async(launch::async, [] { perform_task("B3", 1); });
        
        perform_task("B2", 1);

        futB1.get();
        futB3.get();

        auto futD = async(launch::async, [] { perform_task("D", 1); });

        perform_task("C", 1);

        futD.get();

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration<double>(end_time - start_time).count();
        
        cout << format("Total time: {:.4f} seconds", duration) << endl;
        cout << "Work is done!" << endl;
    }
}

int main()
{
    variant11::work();
    return 0;
}