/**********************************************************************************************************************
File: user_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
 1. Copy both user_app.c and user_app.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserAppFlags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp_StateMachine;            /* The state machine function pointer */
static u32 UserApp_u32Timeout;                      /* Timeout counter used across states */

#if PROGRAMMINGG_COMPETITION
static u8  u8Counter  = 0;
static u8  u8Configed = 0;
//static u16 u16Counter = 0;
static u16 u16Pwm     = 0;

static LedContrlType    UserApp_LedContrlType[LED_NUM]    = LED_CONTRL_TYPE_INIT;
static LedOnOffTimeType UserApp_LedOnOffTimeType[LED_NUM] = LED_ON_OFF_TIME_INIT;
#endif


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/
#if PROGRAMMINGG_COMPETITION
/*--------------------------------------------------------------------------------------------------------------------
Function: LedAllOff

Description:
All Led off

Requires:
  -

Promises:
  - 
*/
void LedAllOff(void)
{
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
}
#endif

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserAppInitialize(void)
{

  /* If good initialization, set state to Idle */
  if( 1 /* Add condition for good init */)
  {
    UserApp_StateMachine = UserAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp_StateMachine = UserAppSM_FailedInit;
  }

} /* end UserAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function UserAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserAppRunActiveState(void)
{
  UserApp_StateMachine();

} /* end UserAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void UserAppSM_Idle(void)
{
#if PROGRAMMINGG_COMPETITION
  
  u8 u8String[] = "You have not config your efashion ";
  static u8  u8Mode;
  
  /*Key Value---Mode*/
  u8Mode = UserAppSM_GetMode();
  
  /*config user data*/
  UserAppSM_ConfigEfashion();
  
  /*Deal Every Mode*/
  switch(u8Mode)
  {
  case DEMO:  
    UserAppSM_DoDemoMode();
    for(u8 u8Index=0; u8Index < LED_NUM; u8Index++)
    {
      UserApp_LedOnOffTimeType[u8Index].u32Counter = 0;
    }
    break;
    
  case USER:
    if(0 == u8Configed)
    {
      DebugPrintf(u8String);
    }
    else
    {
      UserAppSM_DoUserMode();
      u8Counter = 0;
    }
    break;
    
  case PAUSE:
    break;
    
  case DARK:
    for(u8 u8Index=0; u8Index < LED_NUM; u8Index++)
    {
      UserApp_LedContrlType[u8Index].u16PwmValue = 0;
    }
    break;
    
  }
  
  /*Led Action*/
  for(u8 u8Index=0; u8Index < LED_NUM; u8Index++)
  {
    LedPWM(UserApp_LedContrlType[u8Index].u8Led, UserApp_LedContrlType[u8Index].u16PwmValue);
  }
 
#endif
} /* end UserAppSM_Idle() */


#if PROGRAMMINGG_COMPETITION
/*-------------------------------------------------------------------------------------------------------------------*/
/* UserAppSM_ConfigEfashion */
static void UserAppSM_ConfigEfashion(void)
{
  ;//receive the cmd
}


/*-------------------------------------------------------------------------------------------------------------------*/
/* UserAppSM_DoUserMode */
static void UserAppSM_DoUserMode(void)
{
  for(u8 u8Index=0; u8Index < LED_NUM; u8Index++)
  {
    UserApp_LedOnOffTimeType[u8Index].u32Counter++;
    
    if(UserApp_LedOnOffTimeType[u8Index].u32Counter < UserApp_LedOnOffTimeType[u8Index].u32OnTime)
    {
      UserApp_LedContrlType[u8Index].u16PwmValue = 0;
    }
    else if(UserApp_LedOnOffTimeType[u8Index].u32Counter <= UserApp_LedOnOffTimeType[u8Index].u32OffTime)
    {
      UserApp_LedContrlType[u8Index].u16PwmValue = 100;
    }
    else
    {
      UserApp_LedOnOffTimeType[u8Index].u32Counter = 0;
    }
  }
}

/*-------------------------------------------------------------------------------------------------------------------*/
/* UserAppSM_DoDemoMode */
static void UserAppSM_DoDemoMode(void)
{
  static u8  u8NextLed  = WHITE;
  
  u8Counter++;
  if(u8NextLed == LED_NUM)
  {
    u8NextLed = 0;
  }
  else
  {
    if(0 == (u8Counter % 100))
    {
      u16Pwm += 10;

      if(u16Pwm >= 100)
      {
        u16Pwm = 0;
        u8NextLed++;
      }
    }
  }
  
   /*Led Pwm Value*/
  for(u8 u8Index=0; u8Index < LED_NUM; u8Index++)
  {
    if(u8Index == u8NextLed)
    {
      UserApp_LedContrlType[u8Index].u16PwmValue = u16Pwm;
    }
    else
    {
      UserApp_LedContrlType[u8Index].u16PwmValue = 0;
    }
  }
}
/*-------------------------------------------------------------------------------------------------------------------*/
/* UserAppSM_GetMode */
static u8 UserAppSM_GetMode(void)
{
  u8  u8Mode;
  u8  u8Verify = 0;
  static u8 u8ModePre  = DEMO;
  static u8 u8ModePre2 = DEMO;
  static u8 u8Button2Flag = 0; 
  static u8 u8Button3Flag = 0;
   
  /*DEMO*/
  if(IsButtonPressed(BUTTON0))
  {
    u8Verify++;
    u8Mode = DEMO;
    u8ModePre = u8Mode;
  }
  
  /*USER*/
  if(IsButtonPressed(BUTTON1))
  {
    u8Verify++;
    u8Mode = USER;
    u8ModePre = u8Mode;
  }
     
  /*PAUSE*/
  if(IsButtonPressed(BUTTON2))
  {
      u8Verify++;
      u8Button2Flag++;
      if(1 == u8Button2Flag)      /*BUTTON3 is Fist time to press*/
      {
        u8Mode = PAUSE;
      }
      else if(2 == u8Button2Flag) /*BUTTON3 is second time to press*/
      {
        u8Button2Flag = 0;
        u8Mode = u8ModePre;
      }
  }
  
  /*DARK*/
  if(IsButtonPressed(BUTTON3))
  {
    if(0 == u8Button2Flag)        /*if the mode is PAUSE, button4 is not used*/
    {
      u8Verify++;
      u8Button3Flag++;
      
      if(1 == u8Button3Flag)      /*BUTTON3 is Fist time to press*/
      {
        u8Mode = PAUSE;
      }
      else if(2 == u8Button3Flag) /*BUTTON3 is second time to press*/
      {
        u8Button3Flag = 0;
        u8Mode = u8ModePre;
      }
    }
  }
  
  if(u8Verify > 1)
  {
    u8Mode = u8ModePre2;          /*error*/
  }
  
  u8ModePre2 = u8Mode;
  
  return u8Mode;
}
#endif


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserAppSM_Error(void)          
{
  UserApp_StateMachine = UserAppSM_Idle;
  
} /* end UserAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void UserAppSM_FailedInit(void)          
{
    
} /* end UserAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
