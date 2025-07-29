#ifndef UTILS_H
  #define UTILS_H
#endif

#ifndef Shivam_PicoW_TFT_H
    #include <Shivam_PicoW_TFT.h>
#endif

#ifndef TIME_FUNCS_H
    #include "DateTime/time_funcs.h"
#endif

#ifndef STRING_DEFS_H
    #include "string_defs.h"
#endif

#ifndef GLOBALS_H
    #include "globals.h"
#endif

// -------------------------------------------------------------------------------- //
// double round(double x);
void display_large_HH_MM(time_t TS);
void display_large_ss(time_t TS);
void display_day_date(time_t inTime);
void display_day_date_small(time_t inTime);
void print_mem_stats();
String printfcomma (int n);
void draw_dotted_hline(Adafruit_HX8357 tft, uint gap_len, uint segment_len, uint start_x, uint end_x, uint y_pos, int color);
void draw_dotted_vline(Adafruit_HX8357 tft, uint gap_len, uint segment_len, uint start_y, uint end_y, uint x_pos, int color);

// // -------------------------------------------------------------------------------- //
// double round(double x)
// /* this is how the BSD round() function is written */
// {
//     double t;

//     if (!isfinite(x))
//         return (x);

//     if (x >= 0.0) {
//         t = floor(x);
//         if (t - x <= -0.5) t += 1.0;
//         return (t);
//     }

//     else {
//         t = floor(-x);
//         if (t + x <= -0.5) t += 1.0;
//         return (-t);
//     }
// }

// -------------------------------------------------------------------------------- //
void display_large_HH_MM(time_t TS)
/* Show current hours and minutes */
{
    LOG_TRACE("");
    // These vars save current time vals
    uint16_t _DD=1;
    uint8_t _HH, _MM, _ss;
    char _am_pm;
    bool _AM=false;

    get_individual_time(TS, _DD, _HH, _MM, _ss, _AM);

    // Print current time
    char buf[40];
    // sprintf(buf, "%02d:%02d:%02d %cM\n",HH,MM,ss,am_pm);
    sprintf(buf, "%02d:%02d\n",_HH,_MM);

    String tmptxt=String(buf);
    tmptxt.trim();
    timestr.print_tft(tmptxt);

    if (_AM)
        am_pm_str.print_tft_ralign("AM");
    else
        am_pm_str.print_tft_ralign("PM");

    LOG_TRACE("END");
}

void display_large_ss(time_t TS)
/* Shows seconds */
{
    char ss_str[20];
    sprintf(ss_str, "%02d",get_curr_seconds(TS));
    sec_str.print_tft_ralign(ss_str);
}

void display_day_date(time_t inTime)
/* Show day+date on top left of screen */
{
    LOG_TRACE("");
    day_str.print_tft_no_prev_bg(get_readable_day(inTime));
    date_str.print_tft_no_prev_bg(get_readable_date(inTime));
    LOG_TRACE("END");
}

void display_day_date_small(time_t inTime)
/* Show small day+date on top left of screen */
{
    LOG_TRACE("");
    String now_day=get_readable_day(inTime);
    String now_date=get_readable_date(inTime);
    now_day.toUpperCase();
    now_date.toUpperCase();
    daydate_small.print_tft(now_day +", "+now_date);
    LOG_TRACE("END");
}

// -------------------------------------------------------------------------------- //
void print_mem_stats(){
  LOG_DEBUG("\n----------------------------------------");
  LOG_DEBUG("rp2040.getFreeHeap(): "+String(rp2040.getFreeHeap()));
  LOG_DEBUG("rp2040.getUsedHeap(): "+String(rp2040.getUsedHeap()));
  LOG_DEBUG("rp2040.getTotalHeap(): "+String(rp2040.getTotalHeap()));
  LOG_DEBUG("----------------------------------------\n");
}

// Can't use built-in map function. some compilation errror.
long custom_map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// -------------------------------------- Helpers -------------------------------------- //
String printfcomma (int n)
/* Add commas to numbers for better readability. */
{
  String outstr="";
    int n2 = 0;
    int scale = 1;
    if (n < 0) {
        // printf ("-");
        outstr+=("-");
        n = -n;
    }
    while (n >= 1000) {
        n2 = n2 + scale * (n % 1000);
        n /= 1000;
        scale *= 1000;
    }
    // printf ("%d", n);
    outstr+=(int)n;
    while (scale != 1) {
        scale /= 1000;
        n = n2 / scale;
        n2 = n2  % scale;
        // printf (",%03d", n);

    char buf6[10];
        sprintf(buf6,",%03d", n%1000);
        outstr+=buf6;
    }
    return outstr;
}

// ----------------------------------------------------------------------------- //
void draw_dotted_hline(Adafruit_HX8357 tft, uint gap_len, uint segment_len, uint start_x, uint end_x, uint y_pos, int color)
/* For drawing dotted/dashed horizontal lines */
{
    uint xpos=start_x;
    while (xpos<=end_x){
        for (uint x=xpos;x<xpos+segment_len;x++){
            tft.drawPixel(x, y_pos, color);
            if (x>=end_x)
                return; // So we dont overshoot
        }
        xpos+=segment_len+gap_len;
    }
}

void draw_dotted_vline(Adafruit_HX8357 tft, uint gap_len, uint segment_len, uint start_y, uint end_y, uint x_pos, int color)
/* For drawing dotted/dashed vertical lines */
{
    uint ypos=start_y;
    while (ypos<=end_y){
        for (uint y=ypos;y<ypos+segment_len;y++){
            tft.drawPixel(x_pos, y, color);
            if (y>=end_y)
                return; // So we dont overshoot
        }
        ypos+=segment_len+gap_len;
    }
}