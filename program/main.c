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

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/
tU16 previousScore = 0;
#define MENU_DELAY 1000
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
 *    Sound arrays declaration
 *
 ****************************************************************************/

extern char wavSound[];

extern unsigned short arkanoid_menu_mirror[];
extern unsigned short arkanoid_settings_mirror[];
extern unsigned short arkanoid_success_mirror[];

tU32 wavSoundSize();
                                 
                                         /* TIMERS */
static void delayMs(tU16 delayInMs)
{
  /*
   * setup timer #1 for delay
   */
  T1TCR = 0x02;          //stop and reset timer
  T1PR  = 0x00;          //set prescaler to zero
  T1MR0 = delayInMs * (Fpclk / 1000);
  T1IR  = 0xff;          //reset all interrrupt flags
  T1MCR = 0x04;          //stop timer on match
  T1TCR = 0x01;          //start timer
  
  //wait until delay time has elapsed
  while (T1TCR & 0x01)
    ;
}
static void udelay( unsigned int delayInUs )
{
  /*
   * setup timer #1 for delay
   */
  T1TCR = 0x02;          //stop and reset timer
  T1PR  = 0x00;          //set prescaler to zero
  T1MR0 = (((long)delayInUs-1) * (long)Fpclk/1000) / 1000;
  T1IR  = 0xff;          //reset all interrrupt flags
  T1MCR = 0x04;          //stop timer on match
  T1TCR = 0x01;          //start timer
  
  //wait until delay time has elapsed
  while (T1TCR & 0x01)
    ;
}
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
short* pData = NULL;
  tU32 size = 0;
  tU32 cnt = 0;
  tU32 samples = 0;
  tU32 numSamples;
  tU32 sampleRate;
  tU16 usDelay;
  tU16 audioFlag = 1;
  short soundCounter = 0;
void audioPoint(){
        DACR = 0x7fc0;
        numSamples = 1200;
        cnt++;
        samples = 0;
        usDelay = 1000000/ 24000 + 1;
        samples = 0;
        cnt = 11 + pData[8]/2;
  
        while(samples++ < numSamples)
        {
          tS32 val;
      
          val = pData[cnt++];
          DACR = ((val + 0x7fff) & 0xffc0); // |  //actual value to output
  
          udelay(usDelay);
        }
}


void playAudioPoint(Game *inputGame){
  if(soundCounter==(inputGame->getScore(inputGame))-1){
  	audioPoint();
  	soundCounter++;
  }
}
void setRTC(unsigned long *rtcValue, tU16 isAdd){
	if(isAdd){
		(*rtcValue)++;
		printf("\n%d",*rtcValue);
	}
	else{
		(*rtcValue)--;
		printf("\n%d", *rtcValue);
	}
}
/*void showRTC(){
	lcd_putString(100, 160, "GAME OVER");
	RTC_HOUR RTC_MIN RTC_SEC
}*/
/*****************************************************************************
 *
 * Description:
 *    Functions representing logic of the game
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
tU16 ifScored(Game *game)
{
	if(game->getScore(game) != previousScore){
		previousScore = game->getScore(game);
		return 1;
	}
	return 0;
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
	playAudioPoint(game);
	setLed(5, 1);
	setLed(6, 1);
	setLed(7, 1);
	setLed(8, 1);
	setLed(5, 0);
	setLed(6, 0);
	setLed(7, 0);
	setLed(8, 0);
}
void playGame(Game* game){
	lcd_fillScreen(BLACK);
	tU16 flag = 0;
	refreshScreen(game);
    while(1)
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
void drawMenu(Game *game){
	lcdShowPicture(arkanoid_menu_mirror);
	int x,y,z = 0;
	mdelay(MENU_DELAY);
	while(1){
		touch_xyz(&x, &y, &z);
		if(25 < x && x < 210 && 170 < y && y < 225)
			break;
		if(26 < x && x < 208 && 256 < y && y < 288){
			drawSettings(game);
			continue;
		}
	}
}
void drawSettings(Game *game){
	lcdShowPicture(arkanoid_settings_mirror);
	int x,y,z = 0;
	mdelay(MENU_DELAY);
	while(1){
		touch_xyz(&x, &y, &z);
		if(30<x && x<211 && 67 < y && y < 120){
			drawSetTime();
			drawSuccess();
			continue;
		}
		if(54 < x && x < 73 && 208 < y && y < 227){
			game->racketPtr->setColor(game->racketPtr, RED);
			drawSuccess();
		}
		if(105 < x && x < 124 && 208 < y && y < 227){
			game->racketPtr->setColor(game->racketPtr, GREEN);
			drawSuccess();
		}
		if(158 < x && x < 177 && 208 < y && y < 227){
			game->racketPtr->setColor(game->racketPtr, BLUE);
			drawSuccess();
		}
		if(34 < x && x < 210 && 258 < y && y < 286){
			break;
		}
	}
	lcdShowPicture(arkanoid_menu_mirror);
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
void drawSetTime(){
	int x,y,z = 0;
	char rtcString[20];
	while(1){
		lcd_fillScreen(BLACK);
		snprintf(rtcString, 20, "%2ld:%2ld:%2ld", RTC_HOUR, RTC_MIN, RTC_SEC);
		lcd_putString(100, 160, rtcString);
		while(1){
			touch_xyz(&x, &y, &z);
			if(0<x && x<120 && 0<y && y<320){
			
				break;
			}
			if(180 < x && x < 240 && 0<y && y<320){
			
				break;
			}
		}
		mdelay(MENU_DELAY);
	}
}
/*****************************************************************************
 *
 * Description:
 *    The main-function. 
 *
 * Returns:
 *    Always 0, since return value is not used.
 *
 ****************************************************************************/
 
int main(void)
{
	//joystick
	IODIR1 |= 0x38000000;
	IOCLR1 |= 0x38000000;
	PINSEL3 = 0;

	//i2c
	//IODIR0  |= 0x000F8000; 
	//IODIR1  |= 0xFFF00000;
	//FIO2DIR |= 0x0000FFFF;

	//Sound

	PINSEL1 &= ~0x00300000;
	PINSEL1 |=  0x00200000;

	pData = (short*)&wavSound[0];
	size = wavSoundSize();

	eaInit();
	i2cInit();
	//initialize PCA9532
	tU8 initCommand[] = {0x12, 0x97, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};
	pca9532(initCommand, sizeof(initCommand), NULL, 0);
	//initialize printf()-functionality
	// initialize external SDRAM
	sdramInit();
  
	//print welcome message
	printf("\n*********************************************************");
	printf("\n*");
	printf("\n* (C) 2008 Embedded Artists AB");
	printf("\n*");
	printf("\n* Welcome to this program that demonstrates how to use the");
	printf("\n* LCD QVGA.");
	printf("\n*");
	printf("\n*********************************************************\n\n");

#if 0  
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
#endif

  
#ifdef TEST_LCDPARAMS
  
	printf("Horizontal back porch (%d):\t", ea_QVGA_v2.hbp);
	ea_QVGA_v2.hbp = consolGetIntNum();
  
	printf("Horizontal front porch (%d):\t", ea_QVGA_v2.hfp);
	ea_QVGA_v2.hfp = consolGetIntNum();  
  
	printf("HSYNC pulse width (%d):\t\t", ea_QVGA_v2.hsw);
	ea_QVGA_v2.hsw = consolGetIntNum();    
  
	printf("Pixels per line (%d):\t\t", ea_QVGA_v2.ppl);
	ea_QVGA_v2.ppl = consolGetIntNum();      
  
	printf("Vertical back porch (%d):\t", ea_QVGA_v2.vbp);
	ea_QVGA_v2.vbp = consolGetIntNum();        
  
	printf("Vertical front porch (%d):\t", ea_QVGA_v2.vfp);
	ea_QVGA_v2.vfp = consolGetIntNum();  
  
	printf("VSYNC pulse width (%d):\t\t", ea_QVGA_v2.vsw);
	ea_QVGA_v2.vsw = consolGetIntNum();    
  
	printf("Lines per panel (%d):\t\t", ea_QVGA_v2.lpp);
	ea_QVGA_v2.lpp = consolGetIntNum();     
  
	printf("Invert ouput enable (%d):\t", ea_QVGA_v2.ioe);
	ea_QVGA_v2.ioe = consolGetIntNum();       
  
	printf("Invert panel clock (%d):\t\t", ea_QVGA_v2.ipc);
	ea_QVGA_v2.ipc = consolGetIntNum();   
  
	printf("Invert HSYNC (%d):\t\t", ea_QVGA_v2.ihs);
	ea_QVGA_v2.ihs = consolGetIntNum();   
  
	printf("Invert VSYNC (%d):\t\t", ea_QVGA_v2.ivs);
	ea_QVGA_v2.ivs = consolGetIntNum();   
  
  
	printf("\n\nThe display will be initialized with the following values\n\n");  
  
	printf("Horizontal back porch:\t%d\n", ea_QVGA_v2.hbp);  
	printf("Horizontal front porch:\t%d\n", ea_QVGA_v2.hfp); 
	printf("HSYNC pulse width:\t%d\n", ea_QVGA_v2.hsw);  
	printf("Pixels per line:\t%d\n", ea_QVGA_v2.ppl);
	printf("Vertical back porch:\t%d\n", ea_QVGA_v2.vbp);
	printf("Vertical front porch:\t%d\n", ea_QVGA_v2.vfp);
	printf("VSYNC pulse width:\t%d\n", ea_QVGA_v2.vsw); 
	printf("Lines per panel:\t%d\n", ea_QVGA_v2.lpp);
	printf("Invert ouput enable:\t%d\n", ea_QVGA_v2.ioe);  
	printf("Invert panel clock:\t%d\n", ea_QVGA_v2.ipc);
	printf("Invert HSYNC:\t\t%d\n", ea_QVGA_v2.ihs); 
	printf("Invert VSYNC:\t\t%d\n", ea_QVGA_v2.ivs);
  
#endif
	//initialize LCD  

	lcdInit(&ea_QVGA_v2); 
	lcdTurnOn();
	touch_init();
	calibrateStart();
	srand(RTC_SEC);
	tU16 numOfBlocks = 9 + rand() % 5;
	Game *game = newGame(240, 320, numOfBlocks);
	drawMenu(game);
	playGame(game);
	deleteGame(game);
	return 0;
}
