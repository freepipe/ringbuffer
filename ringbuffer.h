#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))

#define RingBuffer_Length(x)        (x.len)
#define RingBuffer_Size(x)          (sizeof(x.data))
#define RingBuffer_Free(x)          (sizeof(x.data) - x.len)
#define RingBuffer_Data(x,i)        (x.data[x.beg + (i)])

#define RingBuffer_Init(x)          (x.len = x.beg = x.end = 0)
#define RingBuffer_PopBack(x)       (RingBuffer_Length(x) > 0 ? (x.end--, x.len--) : 0)
#define RingBuffer_PopFront(x)      (RingBuffer_Length(x) > 0 ? (x.beg++, x.len--) : 0)
#define RingBuffer_PushBack(x, c)   (RingBuffer_Free(x)   > 0 ? ((x.data[x.end++] = (char)c), x.len++) : 0)
#define RingBuffer_PushFront(x, c)  (RingBuffer_Free(x)   > 0 ? ((x.data[--x.beg] = (char)c), x.len++) : 0)
#define RingBuffer_PopBackL(x, l)   do{int len = MIN(x.len, l); x.end -= len; x.len -= len;}while(0)
#define RingBuffer_PopFrontL(x, l)  do{int len = MIN(x.len, l); x.beg += len; x.len -= len;}while(0)

#define RingBuffer_PeekData(x, d, l) \
do{\
	int i = 0;\
	int len = MIN(x.len, l);\
	unsigned char beg = x.beg;\
	for(i = 0; i < len; i++)\
	{\
		d[i] = x.data[beg++];\
	}\
}while(0)

#define RingBuffer_GetData(x, d, l) \
do{\
	int i = 0;\
	int len = MIN(x.len, l);\
	for(i = 0; i < len; i++)\
	{\
		d[i] = x.data[x.beg++];\
	}\
	x.len -= len;\
}while(0)


typedef struct
{
	unsigned len:9;
	unsigned beg:8;
	unsigned end:8;
	unsigned mtx:1;
	char data[256];
}RingBuffer;


#endif//__RING_BUFFER_H__

