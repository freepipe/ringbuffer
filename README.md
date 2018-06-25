# ringbuffer
ring buffer
一个环形缓存的实现,适合单片机数据缓存使用

# 操作说明
```c
typedef struct
{
	unsigned len:9;
	unsigned beg:8;
	unsigned end:8;
	unsigned mtx:1;
	char data[256];
}RingBuffer;
```
```c
typedef struct
{
	unsigned len:10;
	unsigned beg:9;
	unsigned end:9;
	unsigned mtx:1;
	char data[512];
}RingBuffer;
```
```c
typedef struct
{
	unsigned len:11;
	unsigned beg:10;
	unsigned end:10;
	unsigned mtx:1;
	char data[1024];
}RingBuffer;
```
用段位定义缓存的游标主要是为了方便处理缓存下标溢出，简化代码书写。
mtx字段用于临界区保护。
