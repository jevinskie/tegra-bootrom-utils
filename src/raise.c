#include <signal.h>

int raise(int sig) {
	(void)sig;
	return 0;
}
