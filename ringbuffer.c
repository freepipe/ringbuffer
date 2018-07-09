#include <stdio.h>
#include "ringbuffer.h"

int main(int argc, char **argv)
{
	//ringbuffer256 buffer;
	//ringbuffer512 buffer;
	ringbuffer1024 buffer;

	ringbuffer_init(buffer);
	for(int i = 0; i < ringbuffer_size(buffer) * 2; i++)
	{
		ringbuffer_pushback(buffer, i);
	}
	printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);
	for(int i = 0; i < ringbuffer_size(buffer) * 2; i++)
	{
		if( i % 90 == 89 )
		{
			printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);
			ringbuffer_popbackl(buffer, 1);
			ringbuffer_popfrontl(buffer, 1);
		}
	}
	printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);

	return 0;
}
