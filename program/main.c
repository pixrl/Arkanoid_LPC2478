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
#include "sdram.h"
#include "game.h"
#include "i2c.h"
#include "pca9532.h"

/******************************************************************************
 * Defines and typedefs
 *****************************************************************************/

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
 *    Generate a random number.
 *
 ****************************************************************************/

/*****************************************************************************
 *
 * Description:
 *    Sound arrays declaration
 *
 ****************************************************************************/


extern char wavSound[];

tU32 wavSoundSize();

/*****************************************************************************
 *
 * Description:
 *    Demonstrates the use of simple line function.
 *
 ****************************************************************************/



/*****************************************************************************
 *
 * Description:
 *    Demonstrates the use of the draw rectangle function
 *
 ****************************************************************************/



/*****************************************************************************
 *
 * Description:
 *    Demonstrates the use of draw circle function
 *
 ****************************************************************************/


/*****************************************************************************
 * Implementation of public functions
 ****************************************************************************/

/*****************************************************************************
 *
 * Description:
 *    The main-function. 
 *
 * Returns:
 *    Always 0, since return value is not used.
 *
 ****************************************************************************/
                                          
                                          /* TIMERS */
 static void
delayMs(tU16 delayInMs)
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
  		lcd_fillRect(game->blockPtr[i]->getUpperRight(game->blockPtr[i]).x,
   					 game->blockPtr[i]->getUpperRight(game->blockPtr[i]).y,
    				 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).x,
    				 game->blockPtr[i]->getLowerLeft(game->blockPtr[i]).y,
    				 game->blockPtr[i]->getColor(game->blockPtr[i]));
}
void playGame(Game* game){
	int i = 0;
	tU16 flag = 0;
	refreshScreen(game);
    //printf("Wszystko init");
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
		switch(game->getScore(game))
		{
			case 1:
				setLed(1, 1);
        		playAudioPoint(game);
				break;
			case 2:
				setLed(2, 1);
        		playAudioPoint(game);
				break;
			case 3:
				setLed(3, 1);
        		playAudioPoint(game);
        		break;
			case 4:
				setLed(4, 1);
        		playAudioPoint(game);
				break;
			case 5:
				setLed(5, 1);
        		playAudioPoint(game);
        		break;
			case 6:
				setLed(6, 1);
       			playAudioPoint(game);
        		break;
			case 7:
				setLed(7, 1);
        		playAudioPoint(game);
				break;
			case 8:
				setLed(8, 1);
        		playAudioPoint(game);
				break;
			case 9:
				setLed(1, 0);
        		playAudioPoint(game);
        		delayMs(100);
				setLed(2, 0);
        		delayMs(100);
				setLed(3, 0);
        		delayMs(100);
				setLed(4, 0);
        		delayMs(100);
				setLed(5, 0);
        		delayMs(100);
				setLed(6, 0);
        		delayMs(100);
				setLed(7, 0);
        		delayMs(100);
				setLed(8, 0);
        		delayMs(100);
				setLed(1, 1);
        		delayMs(100);
				setLed(2, 1);
        		delayMs(100);
				setLed(3, 1);
        		delayMs(100);
				setLed(4, 1);
        		delayMs(100);
				setLed(5, 1);
        		delayMs(100);
				setLed(6, 1);
        		delayMs(100);
				setLed(7, 1);
        		delayMs(100);
				setLed(8, 1);
				delayMs(100);
				flag = 1;
				break;
		}
		if(flag)
			break;
	}
	lcd_fillScreen(BLACK);
	lcd_putString(100, 160, "GAME OVER");
}
int main(void)
{
  int test = 0;
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
  lcd_fillScreen(BLACK);
  Game *game = newGame(240, 320, 10);
  playGame(game);
  /*Game newGame = gameInit();
	printf("newGame init");
	tU16 i = 0;
	lcd_fillRect(newGame.racket.points[UPPERRIGHT].x, newGame.racket.points[UPPERRIGHT].y, newGame.racket.points[LOWERLEFT].x, newGame.racket.points[LOWERLEFT].y, newGame.racket.color);
	lcd_fillcircle(newGame.ball.center.x, newGame.ball.center.y, newGame.ball.radius, newGame.ball.color);
	for(i = 0; i < NUM_OF_BLOCKS; ++i)
	{
		lcd_fillRect(newGame.blocks[i].points[UPPERRIGHT].x, newGame.blocks[i].points[UPPERRIGHT].y, newGame.blocks[i].points[LOWERLEFT].x, newGame.blocks[i].points[LOWERLEFT].y, newGame.blocks[i].color);
	}
	printf("Wszystko init");
	while(1)
	{
		printf("WHILE");
		moveBall(&newGame);
		lcd_fillcircle(newGame.ball.center.x, newGame.ball.center.y, newGame.ball.radius + 5, BLACK);
		for(i = 0; i < NUM_OF_BLOCKS; ++i)
			lcd_fillRect(newGame.blocks[i].points[UPPERRIGHT].x, newGame.blocks[i].points[UPPERRIGHT].y, newGame.blocks[i].points[LOWERLEFT].x, newGame.blocks[i].points[LOWERLEFT].y, newGame.blocks[i].color);
		lcd_fillcircle(newGame.ball.center.x, newGame.ball.center.y, newGame.ball.radius, newGame.ball.color);
		mdelay(1);
		lcd_fillRect(newGame.racket.points[UPPERRIGHT].x, newGame.racket.points[UPPERRIGHT].y, newGame.racket.points[LOWERLEFT].x, newGame.racket.points[LOWERLEFT].y, newGame.racket.color);
		if(FIO2PIN & 0x00000400)
		{
			if ((FIO2PIN & 0x04000000) == 0)
			{
				printf("\nPrawo");
				moveRacket(&newGame, RACKET_MOVE_RIGHT);
				lcd_fillRect(newGame.racket.points[LOWERLEFT].x, newGame.racket.points[LOWERLEFT].y, 0, newGame.racket.points[UPPERRIGHT].y, BLACK);
			}

			if ((FIO2PIN & 0x00800000) == 0)
			{
				printf("\nLewo");
				moveRacket(&newGame, RACKET_MOVE_LEFT);
				lcd_fillRect(320, newGame.racket.points[UPPERRIGHT].y, newGame.racket.points[UPPERRIGHT].x, newGame.racket.points[LOWERLEFT].y, BLACK);		
			}
		}

		switch(newGame.player.score)
		{
			case 1:
				setLed(1, 1);
        playAudioPoint(&newGame);
				break;
			case 2:
				setLed(2, 1);
        playAudioPoint(&newGame);
				break;
			case 3:
				setLed(3, 1);
        playAudioPoint(&newGame);
        break;
			case 4:
				setLed(4, 1);
        playAudioPoint(&newGame);
				break;
			case 5:
				setLed(5, 1);
        playAudioPoint(&newGame);
        break;
			case 6:
				setLed(6, 1);
        playAudioPoint(&newGame);
        break;
			case 7:
				setLed(7, 1);
        playAudioPoint(&newGame);
				break;
			case 8:
				setLed(8, 1);
        playAudioPoint(&newGame);
				break;
			case 9:
				setLed(1, 0);
        playAudioPoint(&newGame);
        delayMs(100);
				setLed(2, 0);
        delayMs(100);
				setLed(3, 0);
        delayMs(100);
				setLed(4, 0);
        delayMs(100);
				setLed(5, 0);
        delayMs(100);
				setLed(6, 0);
        delayMs(100);
				setLed(7, 0);
        delayMs(100);
				setLed(8, 0);
        delayMs(100);
				setLed(1, 1);
        delayMs(100);
				setLed(2, 1);
        delayMs(100);
				setLed(3, 1);
        delayMs(100);
				setLed(4, 1);
        delayMs(100);
				setLed(5, 1);
        delayMs(100);
				setLed(6, 1);
        delayMs(100);
				setLed(7, 1);
        delayMs(100);
				setLed(8, 1);
				delayMs(100);
				flag = 1;
				break;
		}
		if(flag)
			break;
	}
	lcd_fillScreen(BLACK);
	lcd_putString(100, 160, "GAME OVER");*/
  return 0;
}
