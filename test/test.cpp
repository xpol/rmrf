#include <rmrf.hpp>

int main(int argc, char const *argv[])
{
	if (argc < 1)
		return -1;
	return rmrf(argv[1]) ? 0 : 1;
}
