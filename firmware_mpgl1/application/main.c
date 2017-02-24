/***********************************************************************************************************************
File: main.c                                                                

Description:
Container for the MPG firmware.  
***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32SystemFlags = 0;                     /* Global system flags */
volatile u32 G_u32ApplicationFlags = 0;                /* Global applications flags: set when application is successfully initialized */

/*--------------------------------------------------------------------------------------------------------------------*/
/* External global variables defined in other files (must indicate which file they are defined in) */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Main_" and be declared as static.
***********************************************************************************************************************/

/* 2. Write a type definition for an enumerated (enum) type called TestType with the 
      values, TEST_PASS, TEST_FAIL, and TEST_EMPTY. */
typedef enum {TEST_PASS = 0, TEST_FAIL, TEST_EMPTY} TestType;

/* 7. Write a typedef for a struct called TestStructType with the following members:
      - Unsigned 8-bit Count
      - Pointer to another TestStructType */
typedef struct
{
    UCHAR ucCount;                // Unsigned 8-bit Count
    TestStructType * psOtherTst; // Pointer to another TestStructType
}TestStructType;

void C_Level_test(void)
{
    ULONG ulLoopCnt = 0;  // a loop counter used in 'for'
    ULONG ulTempVarA=0, ulTempVarB=0;  // temp variable A & B might be need

    /* 1. Declare four variables: */
    /* a. signed and unsigned 8-bit counters initialized to 0 */
    CHAR cExampC = 0;
    UCHAR ucExampUc = 0;

    /* b. unsigned, uninitialized 32-bit counter */
    LONG lExampL = 0;
    ULONG  ulExampUl = 0;

    /* c. boolean (bool) status variable initialized to FALSE. */
    BOOL bExampB = FALSE;

    /* 3. Declare an uninitialized 10 byte array of unsigned 8-bit numbers. Then set the 4th element 
          to the value 5 and the last element to the value 500. */
    UCHAR ucExampUcArray[10] = {0};

    ucExampUcArray[3] = 5;   // the 4th element to the value 5
    ucExampUcArray[9] = 500; // the last element to the value 500

    /* 4. Write a loop to set all elements of u8ExampleArray[] to 0. You do not have any 
          information about the array¡¯s declaration. */
    UCHAR u8ExampleArray[] = "i do not have any information about the array¡¯s declaration";  // i need a definition

    ulTempVarA = sizeof(u8ExampleArray) / sizeof(u8ExampleArray[0]);  // get element of u8ExampleArray

    // do my task, loop must be used
    for(ulLoopCnt=0; ulLoopCnt<(ulTempVarA-1); ulLoopCnt++)
    {
        u8ExampleArray[ulLoopCnt] = 0;
    }

    /* 5. Declare a C-string ¡°HELLO EIE¡±. What is the size of this array in bytes? */
    UCHAR ucSrArray[] = "HELLO EIE";

    ulTempVarA = sizeof(ucSrArray) / sizeof(ucSrArray[0]);  // get element of ucSrArray

    /* 6. Use a pointer to parse the unknown string au8String[] and count the number of times the letter ¡®E¡¯ appears. */
    UCHAR au8String[] = "the unknown string au8String";  // i need a definition

    UCHAR * pucStringCursor = au8String;    // pointer to string au8String
    ulTempVarA = sizeof(au8String) / sizeof(au8String[0]);  // get element of au8String

    ulTempVarB = 0;  // clear ulTempVarB counter
    for(ulLoopCnt=0; ulLoopCnt<(ulTempVarA-1); ulLoopCnt++)
    {
        if('E' == (* pucStringCursor))
        {
            ulTempVarB++;  // ulTempVarB is the amount of letter 'E' appearred in au8String
        }

        pucStringCursor++;
    }

    /* 8. Create two variables of type TestStructType. Initialize the first Count member 
          to 1 and the second Count member to 2. Initialize the first TestStructType member 
          pointer to point at the second struct. Initialize the second TestStructType member to NULL. */
    TestStructType psExampStA, psExampStB;

    psExampStA.Count = 1;
    psExampStA.psOtherTst = &psExampStB;

    psExampStB.Count = 2;
    psExampStB.psOtherTst = NULL;
}

/***********************************************************************************************************************
Main Program
Main has two sections:

1. Initialization which is run once on power-up or reset.  All drivers and applications are setup here without timing
contraints but must complete execution regardless of success or failure of starting the application. 

2. Super loop which runs infinitely giving processor time to each application.  The total loop time should not exceed
1ms of execution time counting all application execution.  SystemSleep() will execute to complete the remaining time in
the 1ms period.
***********************************************************************************************************************/

void main(void)
{
  G_u32SystemFlags |= _SYSTEM_INITIALIZING;
  // Check for watch dog restarts

  /* Low level initialization */
  WatchDogSetup(); /* During development, set to not reset processor if timeout */
  GpioSetup();
  ClockSetup();
  InterruptSetup();
  SysTickSetup();

  /* Driver initialization */
  MessagingInitialize();
  UartInitialize();
  DebugInitialize();

  /* Debug messages through DebugPrintf() are available from here */

  SspInitialize();
  TWIInitialize();

  LedInitialize();
  ButtonInitialize();

#ifndef SIMULATOR_MODE
  LcdInitialize();
  AntInitialize();
  SdCardInitialize();
#endif /* SIMULATOR_MODE */

  /* Application initialization */
//  BoardTestInitialize();
//  AudioTestInitialize();
    UserAppInitialize();
  
  /* Exit initialization */
  SystemStatusReport();
  G_u32SystemFlags &= ~_SYSTEM_INITIALIZING;
  
  /* Super loop */  
  while(1)
  {
    WATCHDOG_BONE();
    
    /* Drivers */
    LedUpdate();
    ButtonRunActiveState();
    UartRunActiveState();
    SspRunActiveState();
    TWIRunActiveState();
    MessagingRunActiveState();
    DebugRunActiveState();
    
#ifndef SIMULATOR_MODE
    LcdRunActiveState();
    AntRunActiveState();
    SdCardRunActiveState();
#endif /* SIMULATOR_MODE */

    /* Applications */
    //BoardTestRunActiveState();
    //AudioTestRunActiveState();
    UserAppRunActiveState();

    // c level test
    C_Level_test();
    
    /* System sleep*/
    HEARTBEAT_OFF();
    SystemSleep();
    HEARTBEAT_ON();
    
  } /* end while(1) main super loop */
  
} /* end main() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
