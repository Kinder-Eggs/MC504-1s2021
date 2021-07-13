#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Please pass 2 parameters, uid and weight\n");
		return -1;
	}
	int d;
	d = syscall(447, atoi(argv[1]));
	if(d == -1) {
		printf("Error, errno = %d\n", errno);
		return -1;
	}
	printf("The old weight of the user %d was: %d\n", atoi(argv[1]), d);
	if(syscall(448, atoi(argv[1]), atoi(argv[2])) == -1) {
		printf("Error, errno = %d\n", errno);
		return -1;
	}
	d = syscall(447, atoi(argv[1]));
	if(d == -1) {
		printf("Error, errno = %d\n", errno);
		return -1;
	}
	printf("The new weight of the user %d is: %d\n", atoi(argv[1]), d);
	return 0;
}
