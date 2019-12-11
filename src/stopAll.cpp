#include "ros/ros.h"
#include "epos2/Velocity.h"
#include "wrap.h"
int main(int argc, char **argv)
{

int lResult = MMC_FAILED;
	unsigned int ulErrorCode = 0;
	int node; 
	// Set parameter for usb IO operation
	SetDefaultParameters();
	// open device
	if((lResult = OpenDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("OpenDevice", lResult, ulErrorCode);
		return lResult;
	}
	
	SetEnableState(g_pKeyHandle, 1, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 1, &ulErrorCode);

	SetEnableState(g_pKeyHandle, 2 , &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 2, &ulErrorCode);
	
	//disable epos
	SetDisableState(g_pKeyHandle, 1, &ulErrorCode);
	SetDisableState(g_pKeyHandle, 2, &ulErrorCode);
	//SetDisableState(g_pKeyHandle, 3, &ulErrorCode);
	//close device
	if((lResult = CloseDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("CloseDevice", lResult, ulErrorCode);
		return lResult;
	}
}
