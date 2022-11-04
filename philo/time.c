
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>




int main()
{
	struct timeval	time;

	gettimeofday(&time, 0);
	printf("%ld\n", (time.tv_sec * 1000 + time.tv_usec / 1000));
}