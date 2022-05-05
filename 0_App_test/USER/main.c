#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#include "common.h"
#include "lcd.h"
#include "led.h"
#include "beep.h"
#include "gui_log_console.h"


enum
{
	LA =262,
	LB =294,
	LC =330,
	LD =349,
	LE =392,
	LF =440,
	LG =494,
	
	MA =523,
	MB =578,
	MC =659,
	MD =698,
	ME =784,
	MF =880,
	MG =988,
	
	HA =1064,
	HB =1175,
	HC =1318,
	HD =1397,
	HE =1568,
	HF =1760,
	HG =1976
};


const uint32_t STAY[]={

	//5353
	ME<<16 | 250,
	MC<<16 | 250,
	ME<<16 | 250,
	MC<<16 | 250,
	//222321
	MB<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	MA<<16 | 250,
	//7115
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//177777111
	MA<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	//1715
	MA<<16 | 125,
	LG<<16 | 125,
	MA<<16 | 125,
	ME<<16 | 500,
	//71275
	LG<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MG<<16 | 125,
	ME<<16 | 500,
	
	
	
	TONE_REPEAT

};  //旋律


const uint32_t TUNE[]={
	
	
	LF<<16 | 250,
	LC<<16 | 250,
	HF<<16 | 250,
	MC<<16 | 250,
	
	LD<<16 | 250,
	MA<<16 | 250,
	MD<<16 | 250,
	MA<<16 | 250,
	
	LE<<16 | 250,
	MB<<16 | 250,
	ME<<16 | 250,
	MB<<16 | 250,
	
	MA<<16 | 250,
	ME<<16 | 250,
	HA<<16 | 250,
	ME<<16 | 250,
	
	LF<<16 | 250,
	LC<<16 | 250,
	HF<<16 | 250,
	MC<<16 | 250,
	
	LD<<16 | 250,
	MA<<16 | 250,
	MD<<16 | 250,
	MA<<16 | 250,
	
	LE<<16 | 250,
	MB<<16 | 250,
	ME<<16 | 250,
	MB<<16 | 250,
	//1 5123
	MA<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//212253
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	ME<<16 | 250,
	MC<<16 | 125,
	
	//334
	MC<<16 | 500,
	MC<<16 | 250,
	MD<<16 | 250,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//366321
	MC<<16 | 250,
	LF<<16 | 250,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	LA<<16 | 250,
	
	//20
	MB<<16 | 500,
	TONE_PAUSE<<16 | 125,
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//212253
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	ME<<16 | 250,
	MC<<16 | 125,
	
	
	
	//334
	MC<<16 | 500,
	MC<<16 | 250,
	MD<<16 | 250,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//363216
	MC<<16 | 500,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	MA<<16 | 125,
	LF<<16 | 125,
	
	//10
	MA<<16 | 500,
	TONE_PAUSE<<16 | 250,
	//0
	//TONE_PAUSE<<16 | 3000,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	
	//531134
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 125,
	MC<<16 | 250,
	MD<<16 | 125,
	
	//55555
	ME<<16 | 250,
	ME<<16 | 125,
	ME<<16 | 125,
	ME<<16 | 250,
	ME<<16 | 250,
	//531 112
	ME<<16 | 250,
	MC<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	
	
	
	//33333
	MC<<16 | 250,
	MC<<16 | 125,
	MC<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 250,
	//366321
	MC<<16 | 250,
	LF<<16 | 250,
	MF<<16 | 125,
	MC<<16 | 125,
	MB<<16 | 125,
	LA<<16 | 250,
	
	//20
	MB<<16 | 500,
	TONE_PAUSE<<16 | 125,
	
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	//05123
	TONE_PAUSE<<16 | 125,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//212233
	MB<<16 | 250,
	MA<<16 | 125,
	MB<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 250,
	MC<<16 | 125,
	
	//35123
	MC<<16 | 500,
	LE<<16 | 125,
	MA<<16 | 125,
	MB<<16 | 125,
	MC<<16 | 125,
	
	//2111
	MB<<16 | 250,
	MA<<16 | 125,
	MA<<16 | 125,
	MA<<16 | 500,
	
	TONE_PAUSE<<16 | 2000,
	
	TONE_REPEAT

};  //旋律

void c_setup()
{

	buttons_init();
 	//Yaogan_Init();
	LCD_Init();               //初始化OLED接口
	
	
	console_log(200,"TEST:");
	console_log(200,"1\r\n23\r\n456\n789a\nbcdef\nghijkl\nmnopqrs\ntuvwxyz~\n!@#$^&*()\n`-=_+[]\\|/");
	console_log(200,"\n");
	console_log(120,"--- welcome !---");
	console_log(10,"  _   _    _    ");
	console_log(10," | | | |  |_|   ");
	console_log(10," | |_| |   _    ");
	console_log(10," |  _  |  | |   ");
	console_log(10," | | | |  | |   ");
	console_log(10," |_| |_|  |_|   ");
	console_log(10,"--press button--");
	//while(KEY0);
	console_log(1,"reset wifi");
	// // RESET_IO(0);                                    //复位IO拉低电平
	// // delay_ms(500);                                  //延时500ms
	// // RESET_IO(1);   
	// // delay_ms(1000);
	// // WiFi_send("AT\r\n"); 
	// console_log(1,"send AT ");
	// delay_ms(500);
	// WiFi_send("AT+CWJAP=\"%s\",\"%s\"\r\n",SSID,PASS); 
	// console_log(1,"%s",Usart2_RxBuff);
	// console_log(1,"%s",&Data_buff[2]);

	
	// char i=0;
	// i=MPU_Init();
	// printf("init1:%d",i);
	// console_log(1,"init1:%d",i);

	// i=mpu_dmp_init();
	// printf("init2:%d",i);
	// console_log(1,"init2:%d",i);
	
	// console_log(500,"start !");
	milliseconds=0;
	
	memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);
	
	appconfig_init();
	// led_init();               //初始化LED
	// buzzer_init();	
	//global_init();
	
	alarm_init();             //无法储存闹钟，每次重启以后需要自定义

	
	
	time_init();
	//rtc_init();
	pwrmgr_init();
	// Set watchface
	display_set(watchface_normal);

	display_load();//启动表盘

  
}




void c_loop()
{


	milliseconds++;
	//printf("millis: %d",milliseconds);
    time_update();
	
	if(pwrmgr_userActive())
	{
		//battery_update();
		buttons_update();
	}
  

  	buzzer_update();
    led_update();
	
	
#if COMPILE_STOPWATCH
	stopwatch_update();
#endif
//  global_update();

	if(pwrmgr_userActive())
	{
		alarm_update();
		display_update();
	}

	pwrmgr_update();


//显示完成后清除缓冲区
	memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);

}

int fd, retvalue;
char *filename;

extern u8 KEY0;
extern u8 KEY1;
extern u8 KEY2;

int fd_uart;

int main(int argc, char *argv[])
{



	if(argc != 3){
		printf("Error Usage!\r\n");
		return -1;
	}

	filename = argv[1];

	/* 打开OLED驱动 */
	fd = open(filename, O_RDWR);
	if(fd < 0){
		printf("file %s open failed!\r\n", argv[1]);
		return -1;
	}

	fd_uart = open("/dev/tty", O_RDWR|O_NOCTTY|O_NDELAY|O_NONBLOCK);
	if(fd_uart < 0){
		printf("uart open failed!\r\n");
		return -1;
	}
	else
	{
		printf("uart open!");
	}
	

	//printf("begin>>>\r\n");
	
	c_setup();	    //初始化

	system("stty raw -echo -F" "/dev/tty");
	while(1)
	{
		
		c_loop(); //循环
		
	}
	return 0;
}


