#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

#define min(x, y)	((x) > (y) ? (y) : (x))
#define max(x, y)	((x) > (y) ? (x) : (y))

#define ringbuffer_length(x)        ((x).len)
#define ringbuffer_size(x)          (sizeof((x).data))
#define ringbuffer_free(x)          (sizeof((x).data) - (x).len)
#define ringbuffer_data(x,i)        ((x).data[((x).beg + (i)) % sizeof((x).data)])

#define ringbuffer_init(x)          ((x).len = (x).beg = (x).end = 0)
#define ringbuffer_popback(x)       (ringbuffer_length(x) > 0 ? ((x).end--, (x).len--) : 0)
#define ringbuffer_popfront(x)      (ringbuffer_length(x) > 0 ? ((x).beg++, (x).len--) : 0)
#define ringbuffer_pushback(x, c)   (ringbuffer_free(x)   > 0 ? (((x).data[(x).end++] = (char)(c)), (x).len++) : 0)
#define ringbuffer_pushfront(x, c)  (ringbuffer_free(x)   > 0 ? (((x).data[--(x).beg] = (char)(c)), (x).len++) : 0)
#define ringbuffer_popbackl(x, l)   do{int len = min((x).len, l); (x).end -= len; (x).len -= len;}while(0)
#define ringbuffer_popfrontl(x, l)  do{int len = min((x).len, l); (x).beg += len; (x).len -= len;}while(0)

#define ringbuffer_peekdata(x, d, l) \
do{\
	int i = 0;\
	int len = min((x).len, l);\
	unsigned char beg = (x).beg;\
	for(i = 0; i < len; i++)\
	{\
		(d)[i] = (x).data[beg++];\
	}\
}while(0)

#define ringbuffer_getdata(x, d, l) \
do{\
	int i = 0;\
	int len = min((x).len, (l));\
	for(i = 0; i < len; i++)\
	{\
		(d)[i] = (x).data[(x).beg++];\
	}\
	(x).len -= len;\
}while(0)

typedef struct
{
	unsigned len:9;
	unsigned beg:8;
	unsigned end:8;
	unsigned mtx:1;
	char data[256];
}ringbuffer256;

typedef struct
{
	unsigned len:10;
	unsigned beg:9;
	unsigned end:9;
	unsigned mtx:1;
	char data[512];
}ringbuffer512;

typedef struct
{
	unsigned len:11;
	unsigned beg:10;
	unsigned end:10;
	unsigned mtx:1;
	char data[1024];
}ringbuffer1024;

typedef ringbuffer256 ringbuffer;


#endif//__RING_BUFFER_H__

