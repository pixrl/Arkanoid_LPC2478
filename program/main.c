/******************************************************************************
 *
 * Copyright:
 *    (C) 2008 Embedded Artists AB
 *
 * File:
 *    main.c
 *
 * Description:
 *    Sample application that demonstrates how to use the QVGA LCD
 *
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "general.h"
#include <stdio.h>
#include <printf_P.h>
#include <ea_init.h>
#include <stdlib.h>
#include <consol.h>
#include <lpc24xx.h>
//#include <stdio.h>
#include "ea_lcd/lcd_hw.h"
#include "ea_lcd/lcd_grph.h"
#include "delay.h"
#include "touch.h"
#include "sdram.h"
#include "game.h"
#include "i2c.h"
#include "pca9532.h"
#include "arkanoidTime.h"

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/
tU16 previousScore = 0;
#define MENU_DELAY 1000
#define INCREMENT 1
#define DECREMENT 0
/*
 * Enabled this define if you would like to test different values
 * for the LCD parameters. You will be able to input the values
 * from a console.
 */
//#define TEST_LCDPARAMS

/*****************************************************************************
 * Local variables
 ****************************************************************************/

/* EA QVGA portrait mode TFT display parameters */
static tLcdParams ea_QVGA_v2 =
{
    28,        /* Horizontal back porch */
    10,       /* Horizontal front porch */
    2,       /* HSYNC pulse width */
    240,      /* Pixels per line */
    3,        /* Vertical back porch */
    2,       /* Vertical front porch */
    2,        /* VSYNC pulse width */
    320,      /* Lines per panel */
    0,        /* Do not invert output enable */
    1,        /* Invert panel clock */
    1,        /* Invert HSYNC */
    1,        /* Invert VSYNC */
    1,        /* AC bias frequency (not used) */
    16,       /* Bits per pixel */
    LCD_ADTFT,    /* LCD panel type */
    0,        /* Single panel display */
};

lcd_color_t const COLORS_TAB[16] = {BLACK,
                             NAVY,
                             DARK_GREEN,
                             DARK_CYAN,
                             MAROON,
                             PURPLE,
                             OLIVE,
                             LIGHT_GRAY,
                             DARK_GRAY,
                             BLUE,
                             GREEN,
                             CYAN,
                             RED,
                             MAGENTA,
                             YELLOW,
                             WHITE
                            };

/*****************************************************************************
 * Implementation of local functions
 ****************************************************************************/
/*****************************************************************************
 *
 * Description:
 *    Images arrays declaration
 *
 ****************************************************************************/
/*extern unsigned short arkanoid_menu_mirror[];
extern unsigned short arkanoid_settings_mirror[];
extern unsigned short arkanoid_success_mirror[];*/
void lcdShowPicture(unsigned short *image){
	  unsigned short* buffer = (unsigned short*) LCD_FRAME_BUFFER;
	  int i, j, k=0;
	  for (i=239;i>-1;i--)
	  {
		  for (j=i;j<76800;j+=240)
		    {
		  	  buffer[j] = image[k];
		  	  k++;
		    }
	  }
}
/*****************************************************************************
 *
 * Description:
 *    Sound arrays declaration
 *
 ****************************************************************************/
extern unsigned short wavSound[];
tU32 wavSoundSize();
unsigned short* pData = NULL;
tU32 samples = 0;
tU32 numSamples;
unsigned short val;

void audio_init(){
	//Initialize DAC: AOUT = P0.26
	PINSEL1 &= ~0x00300000;
	PINSEL1 |=  0x00200000;
	pData = (unsigned short*)&wavSound[0];
	DACR = 0x7fc0;

	numSamples = 2640/2;
	//numSamples = 93;
}
void __attribute__((interrupt("IRQ"))) do_irq(){
	//irq service code
	if (samples <= numSamples)
	{
		val = wavSound[samples++];
		DACR = ((val + 0x7fff) & 0xffc0); // |  //actual value to output
	}
	// IRQ END
	T2IR = 0xff;        //reset all IRQ flags
	VICVectAddr = 0x00;        //dummy write to VIC to signal end of interrupt
}
void startTimer1(){
	//initialize VIC for Timer1 interrupts
	VICIntSelect &= ~0x4000000;           //Timer2 interrupt is assigned to IRQ (not FIQ)
	VICVectAddr26  = (tU32)do_irq; 		  //register ISR address
	VICIntEnable  = 0x4000000;            //enable timer1 interrupt

	//initialize and start Timer #0
	PCONP |= (1 << 22);						//Turn on Timer2
	T2TCR = 0x02;                           //disable and reset Timer2
	T2PR  = 0;           					// prescaler = 0
	T2MR0 = 1999;
	T2IR  = 0xff;                           //reset all flags before enable IRQs
	T2MCR = 0x03;                           //reset counter and generate IRQ on MR0 match
	T2TCR = 0x01;                           //start Timer2
}
/*****************************************************************************
 *
 * Description:
 *    LED functions
 *
 ****************************************************************************/
void setLed(int led, int on)
{
	tU8 commandString[] = {0x08, 0x00};
	tU8 reg;
	//adjudt address if LED >= 5
	if (led >= 5)
		commandString[0] = 0x09;

	//read current register value
	pca9532(commandString, 1, &reg, 1);
	//update for new register value
	switch (led)
	{
	case 1:
	case 5:
		reg &= ~0x03;
		if (on == 1)
			reg |= 0x01;
		break;
	case 2:
	case 6:
		reg &= ~0x0c;
		if (on == 1)
			reg |= 0x04;
		break;
	case 3:
	case 7:
		reg &= ~0x30;
		if (on == 1)
			reg |= 0x10;
		break;
	case 4:
	case 8:
		reg &= ~0xc0;
		if (on == 1)
			reg |= 0x40;
		break;
	default:
		break;
	}
	commandString[1] = reg;
	pca9532(commandString, sizeof(commandString), NULL, 0);
}
void setLedScore(Game *game){
	switch(game->getScore(game))
	{
	case 1:
		setLed(1, 1);
		setLed(2, 0);
		setLed(3, 0);
		setLed(4, 0);
		break;
	case 2:
		setLed(1, 0);
		setLed(2, 1);
		setLed(3, 0);
		setLed(4, 0);
		break;
	case 3:
		setLed(1, 1);
		setLed(2, 1);
		setLed(3, 0);
		setLed(4, 0);
		break;
	case 4:
		setLed(1, 0);
		setLed(2, 0);
		setLed(3, 1);
		setLed(4, 0);
		break;
	case 5:
		setLed(1, 1);
		setLed(2, 0);
		setLed(3, 1);
		setLed(4, 0);
		break;
	case 6:
		setLed(1, 0);
		setLed(2, 1);
		setLed(3, 1);
		setLed(4, 0);
		break;
	case 7:
		setLed(1, 1);
		setLed(2, 1);
		setLed(3, 1);
		setLed(4, 0);
		break;
	case 8:
		setLed(1, 0);
		setLed(2, 0);
		setLed(3, 0);
		setLed(4, 1);
		break;
	case 9:
		setLed(1, 1);
		setLed(2, 0);
		setLed(3, 0);
		setLed(4, 1);
		break;
	case 10:
		setLed(1, 0);
		setLed(2, 1);
		setLed(3, 0);
		setLed(4, 1);
		break;
	case 11:
		setLed(1, 1);
		setLed(2, 1);
		setLed(3, 0);
		setLed(4, 1);
		break;
	case 12:
		setLed(1, 0);
		setLed(2, 0);
		setLed(3, 1);
		setLed(4, 1);
		break;
	case 13:
		setLed(1, 1);
		setLed(2, 0);
		setLed(3, 1);
		setLed(4, 1);
		break;
	case 14:
		setLed(1, 0);
		setLed(2, 1);
		setLed(3, 1);
		setLed(4, 1);
		break;
	case 15:
		setLed(1, 1);
		setLed(2, 1);
		setLed(3, 1);
		setLed(4, 1);
		break;
	default:
		setLed(1, 0);
		setLed(2, 0);
		setLed(3, 0);
		setLed(4, 0);
		break;
	}
	samples = 0;
	setLed(5, 1);
	setLed(6, 1);
	setLed(7, 1);
	setLed(8, 1);
	setLed(5, 0);
	setLed(6, 0);
	setLed(7, 0);
	setLed(8, 0);
}
/*****************************************************************************
 *
 * Description:
 *    RTC functions
 *
 ****************************************************************************/
/*void setRTC(volatile unsigned long *rtcValue, tU16 value){
	if(value)
		(*rtcValue)++;
	else
		(*rtcValue)--;
}*/
void setRtcHour(tU16 addValue){
	if(addValue){
		setHour(&RTC_HOUR, INCREMENT);
	}
	else{
		setHour(&RTC_HOUR, DECREMENT);
	}
}
void setRtcMin(tU16 addValue){
	if(addValue){
		if(RTC_MIN == 59){
			setRtcHour(INCREMENT);
			setMinuteOrSecond(&RTC_MIN, INCREMENT);
		}
		else
			setMinuteOrSecond(&RTC_MIN, INCREMENT);
	}
	else{
		if(RTC_MIN == 0){
			setRtcHour(DECREMENT);
			setMinuteOrSecond(&RTC_MIN, DECREMENT);
		}
		else
			setMinuteOrSecond(&RTC_MIN, DECREMENT);
	}
}
void setRtcSec(tU16 addValue){
	if(addValue){
		if(RTC_SEC == 59){
			setRtcMin(INCREMENT);
			setMinuteOrSecond(&RTC_SEC, INCREMENT);
		}
		else
			setMinuteOrSecond(&RTC_SEC, INCREMENT);
	}
	else{
		if(RTC_SEC == 0){
			setRtcMin(DECREMENT);
			setMinuteOrSecond(&RTC_SEC, DECREMENT);
		}
		else
			setMinuteOrSecond(&RTC_SEC, DECREMENT);
	}
}
/*****************************************************************************
 *
 * Description:
 *    Functions drawing the program on the screen
 *
 ****************************************************************************/
void refreshScreen(Game* game){
	int i = 0;
	lcd_fillRect(game->racketPtr->getUpperRight(game->racketPtr).x, 
				 game->racketPtr->getUpperRight(game->racketPtr).y,
				 game->racketPtr->getLowerLeft(game->racketPtr).x, 
				 game->racketPtr->getLowerLeft(game->racketPtr).y,
				 game->racketPtr->getColor(game->racketPtr));
    lcd_fillcircle(game->ballPtr->getCenter(game->ballPtr).x, 
    			   game->ballPtr->getCenter(game->ballPtr).y, 
    			   game->ballPtr->getRadius(game->ballPtr) + 5, 
    			   BLACK);
  	lcd_fillcircle(game->ballPtr->getCenter(game->ballPtr).x, game->ballPtr->getCenter(game->ballPtr).y, 
  				   game->ballPtr->getRadius(game->ballPtr), game->ballPtr->getColor(game->ballPtr));
  	for(i = 0; i < game->getNumOfBlocks(game); ++i)
  	{
  		if(game->blockPtr[i]->getIsDestroyed(game->blockPtr[i])){
  			lcd_fillRect(game->blockPtr[i]->getUpperRight(game->blockPtr[i]).x,
   						 game->blockPtr[i]->getUpperRight(game->blockPtr[i]).y,
    					 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).x,
    					 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).y,
    					 BLACK);
  		}
  		else{
  			lcd_fillRect(game->blockPtr[i]->getUpperRight(game->blockPtr[i]).x,
   						 game->blockPtr[i]->getUpperRight(game->blockPtr[i]).y,
    					 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).x,
    					 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).y,
    					 game->blockPtr[i]->getColor(game->blockPtr[i]));
    	}
    }
}
tU16 ifScored(Game *game){
	if(game->getScore(game) != previousScore){
		previousScore = game->getScore(game);
		return 1;
	}
	return 0;
}
void playGame(Game* game){
	lcd_fillScreen(BLACK);
	refreshScreen(game);
    while(!game->isLost(game))
	{
		game->moveBall(game);
		mdelay(1);
		refreshScreen(game);
		if(FIO2PIN & 0x00000400)
		{
			if ((FIO2PIN & 0x04000000) == 0)
			{
				printf("\nPrawo");
				game->racketPtr->moveRight(game->racketPtr);
				lcd_fillRect(game->racketPtr->getLowerLeft(game->racketPtr).x, 
							 game->racketPtr->getLowerLeft(game->racketPtr).y, 
							 0, 
							 game->racketPtr->getUpperRight(game->racketPtr).y, 
							 BLACK);
			}

			if ((FIO2PIN & 0x00800000) == 0)
			{
				printf("\nLewo");
				game->racketPtr->moveLeft(game->racketPtr);
				lcd_fillRect(320, 
							 game->racketPtr->getUpperRight(game->racketPtr).y, 
							 game->racketPtr->getUpperRight(game->racketPtr).x, 
							 game->racketPtr->getLowerLeft(game->racketPtr).y, 
							 BLACK);		
			}
		}
		if(ifScored(game))
		{
			setLedScore(game);
		}
		if(game->getNumOfBlocks(game) == game->getScore(game))
			break;
	}
	lcd_fillScreen(BLACK);
	lcd_putString(100, 160, "GAME OVER");
}
/*void drawSetTime(){
	int x,y,z = 0;
	tU16 getOut = 0;
	char rtcString[20];
	mdelay(MENU_DELAY);
	while(1){
		lcd_fillScreen(BLACK);
		snprintf(rtcString, 20, "%2lu:%2lu:%2lu", RTC_HOUR, RTC_MIN, RTC_SEC);
		lcd_putString(100, 160, rtcString);
		while(1){
			touch_xyz(&x, &y, &z);
			if(0<x && x<120 && 0<y && y<200){
				setRtcSec(INCREMENT);
				break;
			}
			if(180 < x && x < 240 && 0<y && y<200){
				setRtcSec(DECREMENT);
				break;
			}
			if(0<x && x<240 && 200<y && y<320){
				getOut = 1;
				break;
			}
		}
		if(getOut)
			break;
	}
}
void drawSuccess(){
	lcdShowPicture(arkanoid_success_mirror);
	int x,y,z = 0;
	mdelay(MENU_DELAY);
	while(1){
		touch_xyz(&x, &y, &z);
		if(0<x && x<240 && 0<y && y<320)
			break;
	}
	lcdShowPicture(arkanoid_settings_mirror);
}
void drawSettings(tU16 *chosenColor){
	lcdShowPicture(arkanoid_settings_mirror);
	int x,y,z = 0;
	mdelay(MENU_DELAY);
	while(1){
		touch_xyz(&x, &y, &z);
		if(30<x && x<211 && 67 < y && y < 120){
			drawSetTime();
			drawSuccess();
			mdelay(MENU_DELAY);
			continue;
		}
		if(54 < x && x < 73 && 208 < y && y < 227){
			*chosenColor = RED;
			drawSuccess();
		}
		if(105 < x && x < 124 && 208 < y && y < 227){
			*chosenColor = GREEN;
			drawSuccess();
		}
		if(158 < x && x < 177 && 208 < y && y < 227){
			*chosenColor = BLUE;
			drawSuccess();
		}
		if(34 < x && x < 210 && 258 < y && y < 286){
			break;
		}
	}
	lcdShowPicture(arkanoid_menu_mirror);
}
void drawMenu(tU16 *chosenColor){
	lcdShowPicture(arkanoid_menu_mirror);
	int x,y,z = 0;
	mdelay(MENU_DELAY);
	while(1){
		touch_xyz(&x, &y, &z);
		if(25 < x && x < 210 && 170 < y && y < 225)
			break;
		if(26 < x && x < 208 && 256 < y && y < 288){
			drawSettings(chosenColor);
			mdelay(MENU_DELAY);
			continue;
		}
	}
}*/
/*****************************************************************************
 *
 * Description:
 *    The main-function. 
 *
 * Returns:
 *    Always 0, since return value is not used.
 *
 ****************************************************************************/
int main(void){
	//joystick
	IODIR1 |= 0x38000000;
	IOCLR1 |= 0x38000000;
	PINSEL3 = 0;

	eaInit();
	i2cInit();
	//initialize PCA9532
	tU8 initCommand[] = {0x12, 0x97, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};
	pca9532(initCommand, sizeof(initCommand), NULL, 0);
	//initialize printf()-functionality
	//initialize external SDRAM
	sdramInit();
  
	//print welcome message
	printf("\n*********************************************************");
	printf("\n*");
	printf("\n* (C) 2017 Arkanoid - The Game");
	printf("\n*");
	printf("\n* Welcome to this program that demonstrates simple game.");
	printf("\n*");
	printf("\n*********************************************************\n\n");

	//initialize LCD  

	lcdInit(&ea_QVGA_v2); 
	lcdTurnOn();
	touch_init();
	calibrateStart();
	
	tU16 chosenColor = RED;
	//drawMenu(&chosenColor);
	//audio init
	audio_init();
	startTimer1();
	srand(RTC_CTIME0);
	tU16 numOfBlocks = 9 + rand() % 5;
	Game *game = newGame(240, 320, numOfBlocks);
	game->racketPtr->setColor(game->racketPtr, chosenColor);
	playGame(game);
	deleteGame(game);
	return 0;
}
