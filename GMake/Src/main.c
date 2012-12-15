#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "MathHelper.h"
int main(int arg, char **argv)
{
#if defined DEBUG
printf("Debug Build\n");
#endif

	pid_t mypid;
	pid_t myParentPid;
	gid_t myGid;
	uid_t myUid;
	mypid = getpid();
	myGid = getgid();
	myUid = getuid();
	printf("Mypid %d, My uid %d , my Gid %d \n", mypid, myUid, myGid);
	return 0;
}