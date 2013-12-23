#include "rmrf.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
	if (argc < 2)
		return -1;
	return rmrf(argv[1]);
}
