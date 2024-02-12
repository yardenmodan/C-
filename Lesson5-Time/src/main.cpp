#include <iostream>
#include <tuple>

class Time{
    private:
    static const int HOURS_INDEX{0}, MINUTES_INDEX{1},SECONDS_INDEX{2};
    int * time_arr=0;
    public:
    //constructor
    /*
    Time(int hours, int minutes, int seconds){
        time_arr=new int[3];
        setTime(hours,minutes,seconds);
    }

    ~Time(){
        delete[] time_arr;
    }
    //copy assignmetn ctor
    Time& operator=(const Time& other){
        if (this!=&other){
            time_arr= new int[3];
             for (auto i=0;i<3;i++){
                 time_arr[i]=other.time_arr[i];
             }
        }
        
        return *this;
    }
    //copy ctor
    Time(const Time& other){
        
        time_arr = new int[3];
        for (auto i=0;i<3;i++){
            time_arr[i]=other.time_arr[i];
        }

    }

    Time(Time&& other) noexcept {
        time_arr = other.time_arr;
        other.time_arr = nullptr;
    }

    // Move Assignment Operator
    Time& operator=(Time&& other) noexcept {
        if (this != &other) {
            delete[] time_arr;
            time_arr = other.time_arr;
            other.time_arr = nullptr;
        }
        return *this;
    }
    //ctor
*/  Time(int seconds=0, int minutes=0, int hours=0){
    time_arr=new int[3];
    setTime(hours,minutes,seconds);
    }
    //dtor
    ~Time(){
        delete[] time_arr;
    } 
    //copy ctor
    Time (const Time& other){
        time_arr=new int[3];
        
        time_arr[MINUTES_INDEX]=other.time_arr[MINUTES_INDEX];
        time_arr[HOURS_INDEX]=other.time_arr[HOURS_INDEX];
        time_arr[SECONDS_INDEX]=other.time_arr[SECONDS_INDEX];
        
    }
    // move ctor
    Time( Time&& other){
        time_arr=new int[3];
         time_arr[MINUTES_INDEX]=other.time_arr[MINUTES_INDEX];
        time_arr[HOURS_INDEX]=other.time_arr[HOURS_INDEX];
        time_arr[SECONDS_INDEX]=other.time_arr[SECONDS_INDEX];
        delete[] other.time_arr;
        other.time_arr=nullptr;
    }
    //copy assignment
    Time& operator=(const Time& other){
        if (this!=&other){
            delete[] time_arr;
            time_arr[MINUTES_INDEX]=other.time_arr[MINUTES_INDEX];
            time_arr[HOURS_INDEX]=other.time_arr[HOURS_INDEX];
            time_arr[SECONDS_INDEX]=other.time_arr[SECONDS_INDEX];
        }
        return *this;
    }
    Time& operator=(Time&& other){
        if (this!=&other){
            delete[] time_arr;
            time_arr[MINUTES_INDEX]=other.time_arr[MINUTES_INDEX];
            time_arr[HOURS_INDEX]=other.time_arr[HOURS_INDEX];
            time_arr[SECONDS_INDEX]=other.time_arr[SECONDS_INDEX];
            delete[] other.time_arr;
            other.time_arr=nullptr;
        }
        return *this;
    }

    void setTime(int hours,int minutes, int seconds){
        setHours(hours);
        setMinutes(minutes);
        setSeconds(seconds);
        
    }
    
    void setHours(int hours){
        if (hours>=0){
            time_arr[HOURS_INDEX]=hours;
        }
        else{
            std::cerr << "Error" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    void setMinutes(int minutes){
        if (minutes>=0 && minutes <60){
            time_arr[MINUTES_INDEX]=minutes;
        }
        else{
            std::cerr << "Error" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    void setSeconds(int seconds){
        if (seconds>=0 && seconds <60){
            time_arr[SECONDS_INDEX]=seconds;
        }
        else{
            std::cerr << "Error" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    int getMinutes() const{
        return time_arr[MINUTES_INDEX];
    }

    int getSeconds() const{
        return time_arr[SECONDS_INDEX];
    }

    int getHours() const{
        return time_arr[HOURS_INDEX];
    }



     // Operator Overloads
    Time operator+(int seconds) const {
        Time result(*this);
        result.time_arr[SECONDS_INDEX]=(result.time_arr[SECONDS_INDEX] + seconds);
        result.normalizeTime();
        return result;
    }
    //
    friend Time operator+(int seconds, const Time& t) {
        return t + seconds;
    }

    Time operator+(const Time& other) const {
        Time result(*this);
        result.time_arr[SECONDS_INDEX]=(result.time_arr[SECONDS_INDEX] + other.time_arr[SECONDS_INDEX]);
        result.time_arr[MINUTES_INDEX]=(result.time_arr[MINUTES_INDEX] + other.time_arr[MINUTES_INDEX]);
        result.time_arr[HOURS_INDEX]=(result.time_arr[HOURS_INDEX] + other.time_arr[HOURS_INDEX]);
        result.normalizeTime();
        return result;
    }

    // Comparison Operators
    bool operator<(const Time& other) const {
        return std::tie(time_arr[HOURS_INDEX], time_arr[MINUTES_INDEX], time_arr[SECONDS_INDEX]) <
               std::tie(other.time_arr[HOURS_INDEX], other.time_arr[MINUTES_INDEX], other.time_arr[SECONDS_INDEX]);
    }

    bool operator==(const Time& other) const {
        return std::tie(time_arr[HOURS_INDEX], time_arr[MINUTES_INDEX], time_arr[SECONDS_INDEX]) ==
               std::tie(other.time_arr[HOURS_INDEX], other.time_arr[MINUTES_INDEX], other.time_arr[SECONDS_INDEX]);
    }

    bool operator>(const Time& other) const {
        return other < *this;
    }

    bool operator<=(const Time& other) const {
        return !(*this > other);
    }

    bool operator>=(const Time& other) const {
        return !(*this < other);
    }

    bool operator!=(const Time& other) const {
        return !(*this == other);
    }

    // Output Operator
    friend std::ostream& operator<<(std::ostream& os, const Time& t)  {
        os << t.getHours() << " hours, " << t.getMinutes() << " minutes, " << t.getSeconds() << " seconds";
        return os;
    }

private:
    // Helper function to normalize time
    void normalizeTime() {
        int carryMinutes = time_arr[SECONDS_INDEX] / 60;
        time_arr[SECONDS_INDEX] %= 60;

        time_arr[MINUTES_INDEX] += carryMinutes;
        int carryHours = time_arr[MINUTES_INDEX] / 60;
        time_arr[MINUTES_INDEX] %= 60;

        time_arr[HOURS_INDEX] += carryHours;
    }
};


