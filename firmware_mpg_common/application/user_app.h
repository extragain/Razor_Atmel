/**********************************************************************************************************************
File: user_app.h                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app as a template:
1. Follow the instructions at the top of user_app.c
2. Use ctrl-h to find and replace all instances of "user_app" with "yournewtaskname"
3. Use ctrl-h to find and replace all instances of "UserApp" with "YourNewTaskName"
4. Use ctrl-h to find and replace all instances of "USER_APP" with "YOUR_NEW_TASK_NAME"
5. Add #include yournewtaskname.h" to configuration.h
6. Add/update any special configurations required in configuration.h (e.g. peripheral assignment and setup values)
7. Delete this text (between the dashed lines)
----------------------------------------------------------------------------------------------------------------------

Description:
Header file for yournewtaskname.c

**********************************************************************************************************************/

#ifndef __USER_APP_H
#define __USER_APP_H

/**********************************************************************************************************************
Type Definitions
**********************************************************************************************************************/
typedef struct 
{
  u8  u8Led;
  u16 u16PwmValue;
}LedContrlType;

typedef struct
{
  u8  u8Led;
  u32 u32OnTime;
  u32 u32OffTime;
  u32 u32Counter;
}LedOnOffTimeType;

/**********************************************************************************************************************
Constants / Definitions
**********************************************************************************************************************/
#define PROGRAMMINGG_COMPETITION  1

#define LED_NUM  8
#define LED_CONTRL_TYPE_INIT {{WHITE, 0}, \
                              {PURPLE, 0}, \
                              {BLUE, 0}, \
                              {CYAN, 0}, \
                              {GREEN, 0}, \
                              {YELLOW, 0}, \
                              {ORANGE, 0}, \
                              {RED, 0}}

#define LED_ON_OFF_TIME_INIT {{WHITE, 0, 0, 0}, \
                              {PURPLE, 0,0, 0}, \
                              {BLUE, 0, 0, 0}, \
                              {CYAN, 0, 0, 0}, \
                              {GREEN, 0, 0, 0}, \
                              {YELLOW, 0, 0, 0}, \
                              {ORANGE, 0, 0, 0}, \
                              {RED, 0, 0, 0}}

#define DEMO      0x00
#define USER      0x01
#define PAUSE     0x02
#define DARK      0x03  

/**********************************************************************************************************************
Function Declarations
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/
void UserAppInitialize(void);
void UserAppRunActiveState(void);


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/***********************************************************************************************************************
State Machine Declarations
***********************************************************************************************************************/
static void UserAppSM_Idle(void);             
static void UserAppSM_Error(void);         
static void UserAppSM_FailedInit(void);        

#if PROGRAMMINGG_COMPETITION
void LedAllOff(void);
static u8 UserAppSM_GetMode(void);
static void UserAppSM_DoDemoMode(void);
static void UserAppSM_DoUserMode(void);
static void UserAppSM_ConfigEfashion(void);
#endif

#endif /* __USER_APP_H */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
