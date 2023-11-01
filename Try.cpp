#include <vector>
#include <iostream>

class Timer
{
private:
    static Timer* s_instance;
    Timer();
    ~Timer();
public:
    static Timer* timer();
    static Timer* Create_timer();
    static void Destroy_timer();
    void Start_timer();
    void End_timer();
};

Timer* Timer::Create_timer()
{
    if(timer == nullptr)
    {
        Timer* timer = new Timer();
        return timer;
    }
    return nullptr;
}

void Timer::Destroy_timer()
{
    delete s_instance;
}

Timer* Timer::timer()
{
    return s_instance;
}

int main()
{
    Timer::Create_timer();
    Timer::timer()->Start_timer();
    Timer::timer()->End_timer();
    Timer::Destroy_timer();
}