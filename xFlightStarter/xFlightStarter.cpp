// Basic XPL skeleton

#include <XPLMUtilities.h>
#include <XPLMProcessing.h>
#include <cstring>

#if IBM
	#include <Windows.h>
#endif // IBM

// Deferred initialization to do actions on first simulation loop
float deferredStart(float ellapsedMe, float ellapsedFlight, int counter, void* refcon) {
#if _DEBUG
	XPLMDebugString("***** Starting xFlightStarter plugin *****\n");
#endif

	// Open the aircraft door
	XPLMCommandRef openDoor = XPLMFindCommand("sim/flight_controls/door_open_1");
	XPLMCommandOnce(openDoor);

	// Go to external view
	XPLMCommandRef externalView = XPLMFindCommand("sim/view/circle");
	XPLMCommandRef freeCam = XPLMFindCommand("sim/view/free_camera");
	XPLMCommandRef moveLeft = XPLMFindCommand("sim/general/left");
	XPLMCommandRef moveDown = XPLMFindCommand("sim/general/down");
	XPLMCommandOnce(externalView);
	XPLMCommandOnce(moveLeft);
	XPLMCommandOnce(moveDown);

#if _DEBUG
	XPLMDebugString("Aircraft door should be open\n");
#endif

	return 0;
}

/**********************************************
	REQUIRED CALLBACKS
**********************************************/

// Called by XPlane when DLL is loaded - Returns 1 when successfully loaded
PLUGIN_API int XPluginStart(char *name, char *signature, char *description) {
	std::strcpy(name, "xFlight Starter");
	std::strcpy(signature, "net.jazbelt.xflightstarter");
	std::strcpy(description, "Flight initialization stuff");

	XPLMRegisterFlightLoopCallback(deferredStart, -1, NULL);

	return 1;
}

// Called before the DLL is unloaded
PLUGIN_API void XPluginStop(void) {}

// Called before the plugin is enabled - Returns 1 when successfully starts
PLUGIN_API int XPluginEnable(void) {
	return 1;
}

// Called before the plugin is disabled
PLUGIN_API void XPluginDisable(void) {}

//Called by Plugin Manager when message is sent to us
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID from, int message, void *param) {}
