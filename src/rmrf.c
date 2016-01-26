#include "rmrf.h"
#ifdef _MSC_VER
#define UNICODE
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shellapi.h>

#pragma comment(lib, "shell32.lib")

wchar_t* u8towstring(const char* utf8)
{
	wchar_t* wcs;
	int req = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wcs = malloc(sizeof(*wcs)*(req+1));
	if (!wcs)
		return NULL;

	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wcs, req);
	wcs[req] = L'\0'; // extra zero is needed by SHFileOperation.

	return wcs;
}

int rmrf(const char* directory)
{
    int rv;
	wchar_t* wdirectory = u8towstring(directory);

	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;    // no status display
	fileop.wFunc = FO_DELETE;  // delete operation
	fileop.pFrom = wdirectory;  // source file name as double null terminated string
	fileop.pTo = NULL;    // no destination needed
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;  // do not prompt the user
	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;

	rv = SHFileOperation(&fileop);
	free(wdirectory);

	return rv;
}

#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


int rmrf(const char* directory)
{
	size_t dirlen;
	char* child;
	struct stat info;
	int rv;
	DIR *d = opendir(directory);

	if (!d)
		return 1;

	dirlen = strlen(directory);
	child = (char*)malloc(dirlen + 1024);
	strncpy(child, directory, dirlen+1);

	if (child[dirlen-1] != '/')
	{
		child[dirlen] = '/';
		++dirlen;
	}


	struct dirent *p;
	rv = 0;
	while ((p=readdir(d)) != NULL)
	{
		if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
			continue;

		strcpy(child + dirlen, p->d_name);

		rv = stat(child, &info);
		if (rv == 0)
			rv = S_ISDIR(info.st_mode) ? rmrf(child) : unlink(child);
		if (rv != 0)
			break;
	}
	free(child);
	closedir(d);

	return rv != 0 ? rv : rmdir(directory);
}

#endif
