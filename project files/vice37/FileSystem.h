#pragma once

#include <rtfsyst.h>
#include "CPatch.h"

#define MAX_NB_FILES_PER_FS    20

struct FileFunctions
{
	void *rwfexist;
	void *rwfopen;
	void *rwfclose;
	void *rwfread;
	void *rwfwrite;
	void *rwfgets;
	void *rwfputs;
	void *rwfeof;
	void *rwfseek;
	void *rwfflush;
	void *rwftell;
};

FileFunctions fileFunctions;

FileFunctions *RwOsGetFileInterface()
{
	return &fileFunctions;
}

void MakeFileFunctionsHook()
{
	fileFunctions.rwfexist = &RwFexist;
	fileFunctions.rwfopen  = (void *)0x6526B0;
	fileFunctions.rwfclose = (void *)0x652540;
	fileFunctions.rwfread  = (void *)0x652EC0;
	fileFunctions.rwfwrite = (void *)0x6531B0;
	fileFunctions.rwfgets  = (void *)0x652A30;
	fileFunctions.rwfputs  = (void *)0x652C20;
	fileFunctions.rwfeof   = (void *)0x672EA0;
	fileFunctions.rwfseek  = (void *)0x652E60;
	fileFunctions.rwfflush = (void *)0x6525D0;
	fileFunctions.rwftell  = (void *)0x652D50;
	CPatch::RedirectJump(0x663580, RwOsGetFileInterface);
	CPatch::RedirectJump(0x663650, RwFexist);
}

RwBool psInstallFileSystem(void)
{
#ifdef RTFSYST_H
	RwChar  curDirBuffer[_MAX_PATH];
	RtFileSystem * wfs, *unc;

	RwUInt32 retValue = GetCurrentDirectory(_MAX_PATH, curDirBuffer);
	if (0 == retValue || retValue > _MAX_PATH)
	{
		return false;
	}

	rwstrcat(curDirBuffer, "\\");

	if (unc = RtWinFSystemInit(MAX_NB_FILES_PER_FS, curDirBuffer, "unc"))
	{
		if (!RtFSManagerRegister(unc))
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	CharUpper(curDirBuffer);

	RwUInt32 drivesMask = GetLogicalDrives();
	drivesMask >>= 1;

	for (RwInt32 drive = 2; drivesMask != 0; drive++, drivesMask >>= 1)
	{
		if (drivesMask & 0x01)
		{
			RwChar  deviceName[4] = { 0 };

			deviceName[0] = drive + 'A' - 1;
			deviceName[1] = ':';
			deviceName[2] = '\\';

			RwInt32 ret = GetDriveType(deviceName);

			if (ret != DRIVE_UNKNOWN && ret != DRIVE_NO_ROOT_DIR)
			{
				deviceName[2] = '\0';

				RwChar fsName[2] = { 0 };
				fsName[0] = deviceName[0];

				if (wfs = RtWinFSystemInit(MAX_NB_FILES_PER_FS, deviceName, fsName))
				{
					if (!RtFSManagerRegister(wfs))
					{
						return false;
					}
					else
					{
						if (curDirBuffer[1] != ':')
						{
							RtFSManagerSetDefaultFileSystem(unc);
						}
						else if (deviceName[0] == curDirBuffer[0])
						{
							RtFSManagerSetDefaultFileSystem(wfs);
						}
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
# endif
	return true;
}