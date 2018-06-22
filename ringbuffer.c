#include <stdio.h>
#include "ringbuffer.h"

int main(int argc, char **argv)
{
	RingBuffer buffer;

	RingBuffer_Init(buffer);
	for(int i = 0; i < 300; i++)
	{
		RingBuffer_PushBack(buffer, i);
	}
	printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);
	for(int i = 0; i < 300; i++)
	{
		if( i % 40 == 39 )
		{
			printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);
			RingBuffer_PopBackL(buffer, 1);
		}
		RingBuffer_PopFrontL(buffer, 1);
	}
	printf("buffer:{len=%d, beg=%d, end=%d}\n", buffer.len, buffer.beg, buffer.end);

	return 0;
}
