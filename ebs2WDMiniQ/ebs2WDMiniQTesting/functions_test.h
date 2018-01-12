/**********************************************************************************************************************
FHNW - EMBEDDED SYSTEMS
**********************************************************************************************************************
/*  Program :: Functions.h	*/
/*	Revision:: 1.0	*/
/*	Author:: A. Gessler / B. H�rzeler	*/
/*	Date:: 2017-10-05	*/
/**********************************************************************************************************************/
/* Implementierung des Controllers
**********************************************************************************************************************/

#ifndef FUNCTIONS_TEST_H
#define FUNCTIONS_TEST_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/*----------------------------------------------------------------
Key enumerator
----------------------------------------------------------------*/
typedef enum tenKey
{
	enKey_undef = 0,                                // State - No key pressed
	enKey_1,                                        // State - Key 1 pressed
	enKey_2,                                        // State - Key 2 pressed
	enKey_3,                                        // State - Key 3 pressed
}tenKey;

/*----------------------------------------------------------------
User Interface enumerator
----------------------------------------------------------------*/
typedef enum tenUIState
{
	enUIState_undef = 0,                            // State - Undefined
	enUIState_Calibration,                          // State - Calibration
	enUIState_ManualMode,                           // State - Manual mode
	enUIState_AutomaticMode,                        // State - Automatic mode
	enUIState_Abort,                                // State - Aborting
	enUIState_StartUp,                              // State - After StartUp
	enUIState_Wait,                                 // State - Wait
}tenUIState;

/*----------------------------------------------------------------
Motor control structure
----------------------------------------------------------------*/
typedef struct tstMotor
{
	bool                bRun;                       // Start motors dynamic speed
	bool                bCalibRun;                  // Start motors static right turn
	bool                bCalibRunL;                 // Start motors static left turn
	bool                bCompassCalibrated;         // Compass calibration successfull
	unsigned int        uiSpeed;                    // Actual speed of motors
	unsigned int       *puiActAngle;                // Actual angle of compass
}tstMotor;

/*----------------------------------------------------------------
Lightsensor structure
----------------------------------------------------------------*/
typedef struct tstLightSensor
{
	float               flLightInVoltage;           // Voltage depend on Photodiode resistance
}tstLightSensor;

/*----------------------------------------------------------------
RGB-LED structure
----------------------------------------------------------------*/
typedef struct tstRgbLed
{
	unsigned int       *puiColor;                   // Actual color of LED
	unsigned long       ulCycle;                    // Cycle counter
}tstRgbLed;

/*----------------------------------------------------------------
Compass structure
----------------------------------------------------------------*/
typedef struct tstCompass
{
	bool                bCalibDone;                 // Calibration of compass done
	float               flDeclinationAngle;         // Factor for offset calculation
	signed int          iMagnet_x;                  // Compass magnitude X-Axis
	signed int          iMagnet_y;                  // Compass magnitude Y-Axis
	signed int          iMagnet_z;                  // Compass magnitude Z-Axis
	signed int          iMagOffset_x;               // Offset magnitude X-Axis
	signed int          iMagOffset_y;               // Offset magnitude Y-Axis
	unsigned int        uiAngle;                    // Actual angle of compass
}tstCompass;

/*----------------------------------------------------------------
User interface structure
----------------------------------------------------------------*/
typedef struct tstUI
{
	bool                bMenuSet;                   // For UI-Menu controll
	bool                bStartAuto;                 // Start automatic mode
	bool                bStartManual;               // Start manual mode
	bool                bModeAborted;               // Status boolean abort
	bool                bSetCursorFlag;             // Flag indication for LCD-cursor set
	tenKey              enKeyState;                 // Key states
	tenUIState          enUIState;                  // User Interface states
	float              *pflLightInVoltage;          // Voltage depend on Photodiode resistance
	char                szDisplayData[33];          // Data buffer
	unsigned int       *puiActAngle;                // Actual angle compass
	unsigned char       uchPrevState;               // Previous User Interface state
	unsigned char       uchDisplayIx;               // Index for data buffer read
	unsigned char       uchFirstDigit_SV;           // First char digit single value
	unsigned char       uchSecondDigit_SV;          // Second char digit single value
	unsigned char       uchThirdDigit_SV;           // Third char digit single value
	unsigned char       uchAngleFirstDigit_DV;      // First char digit (Angle) double value
	unsigned char       uchAngleSecondDigit_DV;     // Second char digit (Angle) double value
	unsigned char       uchAngleThirdDigit_DV;      // Third char digit (Angle) double value
	unsigned char       uchVoltageFirstDigit_DV;    // First char digit (Voltage) double value
	unsigned char       uchVoltageSecondDigit_DV;   // Second char digit (Voltage) double value
	unsigned char       uchVoltageThirdDigit_DV;    // Third char digit (Voltage) double value
	unsigned short      usKeyState;                 // Key state
	unsigned long       ulCycle;                    // Cycle counter
	unsigned long       ulTimeTextOnHold;           // Time delay for display hold (Text)
}tstUI;


/*----------------------------------------------------------------
Private structure
----------------------------------------------------------------*/
typedef struct tstPrvMain
{
	tstMotor            stMotor;                    // Motor structure
	tstLightSensor      stLight;                    // Lightsensor structure
	tstRgbLed           stRgbLed;                   // LED structure
	tstUI               stUI;                       // User Interface structure
	tstCompass          stCompass;                  // Compass structure
}tstPrvMain;


#endif // !FUNCTIONS_TEST_H
