/**********************************************************************************************************************
File: efashion_app.c                                                                

----------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------

Description:
This is a efashion_app.c file, used to code the efashion product. 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void EfashionAppInitialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void EfashionAppRunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32EfashionAppFlags;                    /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "EfashionApp_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type EfashionApp_StateMachine;        /* The state machine function pointer */
static u32 EfashionApp_u32Timeout;                  /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: EfashionAppInitialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void EfashionAppInitialize(void)
{

  /* If good initialization, set state to Idle */
  if( 1 /* Add condition for good init */)
  {
    EfashionApp_StateMachine = EfashionAppSM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    EfashionApp_StateMachine = EfashionAppSM_FailedInit;
  }

} /* end EfashionAppInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function EfashionAppRunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void EfashionAppRunActiveState(void)
{
  EfashionApp_StateMachine();

} /* end EfashionAppRunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for a message to be queued */
static void EfashionAppSM_Idle(void)
{

} /* end EfashionAppSM_Idle() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void EfashionAppSM_Error(void)          
{
  EfashionApp_StateMachine = EfashionAppSM_Idle;
  
} /* end EfashionAppSM_Error() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* State to sit in if init failed */
static void EfashionAppSM_FailedInit(void)          
{
    
} /* end EfashionAppSM_FailedInit() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
