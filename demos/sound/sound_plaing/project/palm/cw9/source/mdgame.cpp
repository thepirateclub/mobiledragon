/**
 * mdgame.cpp Palm OS 68k entry point.
 */

#include <PalmOS.h>

#include "mdgamersc.h"
#include "..\..\..\mdconfig.h"


/**
 * Define the minimum OS version we support (5.0 for now).
 */
#define kOurMinVersion sysMakeROMVersion(5, 0, 0, sysROMStageDevelopment, 0)
#define kPalmOS10Version sysMakeROMVersion(1, 0, 0,sysROMStageRelease, 0)


/**
 *	RomVersionCompatible() checks if ROM version meet minimum requirement.
 *	@param requiredVersion minimum ROM version required.
 *	@param launchFlags flags that indicate if the application UI is initialized.
 *	@return Error code or errNone if ROM is compatible.
 */
static Err RomVersionCompatible( UInt32 requiredVersion, UInt16 launchFlags )
{
	UInt32 romVersion;
	FtrGet( sysFtrCreator, sysFtrNumROMVersion, &romVersion );

	if( romVersion < requiredVersion )
	{
		if( (launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp) )
		{
			FrmAlert( RomIncompatibleAlert );

			if( romVersion <= kPalmOS10Version )
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
		}

		return sysErrRomIncompatible;
	}

	return errNone;
}

extern UInt32 MDLaunch68k( UInt32 creator_id );

/**
 *	PilotMain() is application main entry point.
 *	@param cmd value specifying the application launch code.
 *	@param cmdPBP pointer to a structure that is associated with the launch code.
 *	@param launchFlags value providing extra information about the launch.
 *	@return Result of launch.
 */
UInt32 PilotMain( UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	if( ( cmd != sysAppLaunchCmdNormalLaunch ) )
		return errNone;

	// Check if ROM version meets minimum requirements. If not, exit.
	Err error = RomVersionCompatible ( kOurMinVersion, launchFlags );
	if( error != errNone )
		return error;

	// Transfer control to MobileDragon 
	return MDLaunch68k( MD_PALM_CREATOR_ID );
}