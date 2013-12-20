#include <string>

#ifdef _MSC_VER
#include <windows.h>
#include <shellapi.h>


std::wstring u8towstring(const std::string& utf8)
{
	std::wstring wcs;
	
	int req = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.size(), NULL, 0);
	wcs.resize(req);
	MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.size(), &wcs[0], req);
	return wcs;
}

bool rmrf(const std::string& directory)
{
	std::wstring wdirectory = u8towstring(directory);
	wdirectory.push_back(0);
	wdirectory.push_back(0);

	SHFILEOPSTRUCT fileop;
	fileop.hwnd = NULL;    // no status display
	fileop.wFunc = FO_DELETE;  // delete operation
	fileop.pFrom = &wdirectory[0];  // source file name as double null terminated string
	fileop.pTo = NULL;    // no destination needed
	fileop.fFlags = FOF_NOCONFIRMATION | FOF_SILENT;  // do not prompt the user
	fileop.fAnyOperationsAborted = FALSE;
	fileop.lpszProgressTitle = NULL;
	fileop.hNameMappings = NULL;

	return SHFileOperation(&fileop) == 0;
}

#else
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>


bool rmrf(const std::string& directory)
{
	DIR *d = opendir(directory.data());
	if (!d)
		return false;

	struct dirent *p;
	while ((p=readdir(d)) != NULL)
	{
		/* Skip the names "." and ".." as we don't want to recurse on them. */
		if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
			continue;

		std::string entity(directory + "/" + p->d_name);

		struct stat info;
		if (stat(entity, &info) != 0)
			return false;
		int rv = (S_ISDIR(info.st_mode)) ? rmrf(entity) : unlink(entity.data());
		if (rv != 0)
			return false;
	}

	closedir(d);
	return rmdir(path) == 0;
}

#endif

