
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int	main( int argc, char * argv[]) {
	int	msgNr = 1;
	int	r;

	printf("msg %d/%d: I am process %d named '%s'. My parent process = %d.\n", getpid(), msgNr++, getpid(), argv[0], getppid());
	fflush(stdout);

	if ( argc < 2 ) {
		fprintf(stderr, "msg %d/%d: please call me with at least one argument, the name of the program which I must exececute.\n", getpid(), msgNr++);
		fflush(stderr);
		return EXIT_FAILURE;
	}


	printf("msg %d/%d: I will now execv(%s, [%s, %s, ...]\n", getpid(), msgNr++, argv[1], argv[1], argv[2]);
	fflush(stdout);

	r = execv(argv[1], argv+1);
	// A call to exec*() should not return! if it does, something is seriously wrong:

	perror(argv[1]);
	fflush(stderr);
	printf("msg %d/%d: execv(%s,...) returned %d!. Errno = %d.\n", getpid(), msgNr++, argv[1], r, errno);
	fflush(stdout);

	printf("msg %d/%d: So, let's try execvp(%s, [%s, %s, ...]\n", getpid(), msgNr++, argv[1], argv[1], argv[2]);
	fflush(stdout);

	// execv failed. execvp will search for argv[1] in your $PATH
	r = execvp(argv[1], argv+1);

	perror(argv[1]);
	fflush(stderr);
	printf("msg %d/%d: execvp(%s,...) returned %d!. Errno = %d.\n", getpid(), msgNr++, argv[1], r, errno);
	fflush(stdout);

	return EXIT_SUCCESS;
}

	
