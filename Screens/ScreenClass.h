
#ifndef SCREEN_CLASS_H
    #define SCREEN_CLASS_H
#endif

#ifndef COMMON_H
    #include "common.h"
#endif

#ifndef ARX_DEBUGLOG_H
    #include <DebugLog.h>
#endif

#include <iostream>
#include <functional>

enum SCR_TIME_DISP_TYPE{LARGE,MEDIUM,SMALL,NONE};

void do_nothing(uint TimeStamp){
    return;
}

// ----------------------------------------------------------- //
class Screen {

    std::function<void(uint)> on_minute_change_func;
    std::function<void(uint)> on_second_change_func;
    std::function<void(uint)> on_hour_change_func;
    std::function<void(uint)> on_enter_func;
    std::function<void(uint)> on_exit_func;
    std::function<void(uint)> on_touch_func;
    std::function<void(void)> init;

public:
    String name;
    SCR_TIME_DISP_TYPE time_disp;

    bool show_power_info=true;
    bool show_backlight_info=true;
    bool show_scr_num=true;

    bool show_mw_icon=true;
    bool show_icons=true;

    Screen(String name,SCR_TIME_DISP_TYPE time_disp){
        this->name=name;
        this->time_disp=time_disp;
    }

    Screen(String name,SCR_TIME_DISP_TYPE time_disp,std::function<void(void)> init){
        this->name=name;
        this->time_disp=time_disp;
        this->init=init;
    }

    // ------------------------------------------------------------------ //
    void set_func_per_minute(std::function<void(uint)> on_minute_change_func){
        this->on_minute_change_func=on_minute_change_func;
    }

    void set_func_per_second(std::function<void(uint)> on_second_change_func){
        this->on_second_change_func=on_second_change_func;
    }

    void set_func_per_hour(std::function<void(uint)> on_hour_change_func){
        this->on_hour_change_func=on_hour_change_func;
    }

    void set_func_on_enter(std::function<void(uint)> on_enter_func){
        this->on_enter_func=on_enter_func;
    }
    void set_func_on_exit(std::function<void(uint)> on_exit_func){
        this->on_exit_func=on_exit_func;
    }
    void set_func_on_touch(std::function<void(uint)> on_touch_func){
        this->on_touch_func=on_touch_func;
    }

    void set_func_init(std::function<void(void)> init){
        this->init=init;
    }

    // ------------------------------------------------------------------ //
    void func_per_minute(uint TimeStamp){
        this->on_minute_change_func(TimeStamp);
    }

    void func_per_second(uint TimeStamp){
        this->on_second_change_func(TimeStamp);
    }
    void func_per_hour(uint TimeStamp){
        this->on_hour_change_func(TimeStamp);
    }

    void func_on_enter(uint TimeStamp){
        this->on_enter_func(TimeStamp);
    }

    void func_on_exit(uint TimeStamp){
        this->on_exit_func(TimeStamp);
    }

    // For interactive screens
    void func_on_touch(uint TimeStamp){
        this->on_touch_func(TimeStamp);
    }

    void func_init(){
        this->init();
    }

   // ------------------------------------------------------------------ //
    void print_name(){
        LOG_INFO("screen name: "+this->name);
    }
};


