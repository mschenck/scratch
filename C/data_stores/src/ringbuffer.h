
#define SERVERNAME  "testname"

// TODO: make easy to adjust for PAGE_SIZE 
#define BUFFERSIZE 4096

// 4 GB allocated for log data
#define LOGSIZE    4294967296

// 4096 messages per segment
#define MSG_PER_SEGM 4096

// region name length
#define PREFIX_LEN 11
#define REGION_LEN 16

/*
  # ring segment size
    - In Bytes - 16 MB segments
    - With a 4 KB * 4096 message
 (shrink segment size to 
*/
#define SEGSIZE    ( BUFFERSIZE * MSG_PER_SEGM )

#define SEGCOUNT   ( LOGSIZE / SEGSIZE ) 

#define RBSUCCESS 0
#define RBFAILURE 1 

typedef struct RingBuffer {
  struct RingBuffer*  next;
  char                data[SEGSIZE - 8];
} RingBuffer;

/*
void
write_log(RingBuffer* rb, char* entry);

*/
