#ifndef COMMON_H
	#include "../common.h"
#endif


#define START_ROW 145

Shivam_TXT free_heap_txt = Shivam_TXT(130, START_ROW, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT used_heap_txt = Shivam_TXT(130, START_ROW+40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
Shivam_TXT  pct_heap_txt = Shivam_TXT(130, START_ROW+40+40+40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);


void scr_mem_info_per_second(uint TimeStamp) {
	// LOG_DEBUG(String(rp2040.getFreeHeap())+" / "+String(rp2040.getUsedHeap())+" / "+String(rp2040.getTotalHeap())+" / "+String(100.0 * rp2040.getUsedHeap()/rp2040.getTotalHeap())+"%");
	int free_heap=rp2040.getFreeHeap();
	int used_heap=rp2040.getUsedHeap();
	int total_heap=rp2040.getTotalHeap();
	float pct_heap = 100.0 * used_heap/total_heap;
	free_heap_txt.print_tft(printfcomma(free_heap)+" bytes");
	used_heap_txt.print_tft(printfcomma(used_heap)+" bytes");
	pct_heap_txt.print_tft(String(pct_heap)+"%");
}


void scr_mem_info_on_enter(uint TimeStamp){
	myTFT.clear_screen(BG_COLOR);
	Shivam_TXT title = Shivam_TXT(5, 105, FreeMonoBold12pt7b, 1, TERTIARY_TXT_COLOR, BG_COLOR);
	title.begin(myTFT.tft);
	title.print_tft("MEMORY INFO");

	// scr_mem_info_per_minute(TimeStamp);

	Shivam_TXT label_txt = Shivam_TXT(5, START_ROW, FreeMonoBold9pt7b,  1, CYAN, BG_COLOR);
	label_txt.begin(myTFT.tft);

	label_txt.print_tft_no_prev_bg("FREE HEAP: ");

	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("USED HEAP: ");

	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("TOTAL HEAP: ");

	label_txt.increment_y_pos(40);
	label_txt.print_tft_no_prev_bg("\% FULL: ");

	// Show total heap
	Shivam_TXT heap_txt   = Shivam_TXT(130, START_ROW+40+40, FreeMonoBold14pt7b, 1, TXT_COLOR, BG_COLOR);
	heap_txt.begin(myTFT.tft);
	heap_txt.print_tft(printfcomma(rp2040.getTotalHeap())+" bytes");
}

void scr_mem_info_initialize(Screen* S){
	S->set_func_per_second(scr_mem_info_per_second);
	S->set_func_per_minute(do_nothing);
	S->set_func_per_hour(do_nothing);
	S->set_func_on_enter(scr_mem_info_on_enter);
	S->set_func_on_exit(do_nothing);
	S->set_func_on_touch(do_nothing);
	
	free_heap_txt.begin(myTFT.tft);
	used_heap_txt.begin(myTFT.tft);
	pct_heap_txt.begin(myTFT.tft);
}