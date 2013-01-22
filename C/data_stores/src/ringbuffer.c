
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#include "ringbuffer.h"

#define TESTMSG "127.0.0.1:48175 [21/Jan/2013:09:55:38.596] mainfrontend tumblelogpool/p-blogs-3a262277 0/0/0/5/5 403 1869 - - ---- 0/0/0/0/0 0/0 {collectd/5.0.3|} \"GET /tumblr-server-status?auto HTTP/1.1\""


/*
  # Generate a shm_region string
    - Used per ring buffer segment
    - Leverages SERVERNAME
    - Format: 16 character string NAME-index
      - NAME: created from SERVERNAME (only first 11 char)
      - index: from passed integer 
*/
int
init_rb (RingBuffer* rb, size_t segment_size, int segment_count)
{
  RingBuffer  *current, *head, *last;
  char        shm_region[16], shm_prefix[11];
  int         shm_fd, segment_iter;

  segment_iter = 0; 
  do {
    // TODO: handle long SERVERNAME
    strncpy(shm_prefix, "1234123412341234", 11);
    sprintf(shm_region, "%s-%d", shm_prefix, segment_iter);
    printf("The shm_region is '%s'\n", shm_region);

    shm_fd = shm_open(shm_region, O_RDWR|O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (shm_fd == -1) {
      printf("FATAL: Unable to get file descriptor for segment %s\n", shm_region);
      return -1;
    } else {
      printf("DEBUG:\tshm_region: %s\tshm_fd: %d\n", shm_region, (int)shm_fd);
    }

    if (ftruncate(shm_fd, sizeof(struct RingBuffer)) == -1) {
      printf("FATAL: Unable to truncate shm segment %s\n", shm_region);
      return -1;
    }

    current = mmap(NULL, sizeof(struct RingBuffer),
      PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (current == MAP_FAILED) {
      printf("FATAL: Unable to map shm segment %s\n", shm_region);
      return -1;
    }

    if (segment_iter == 0) {
      head = current;
    } else {
      last->next = current;
    }
    last = current;

    segment_iter++;
  } while ( segment_iter < segment_count );

  if (last != NULL && head != NULL) {
    last->next = head;
  }

  return 0;
}

int
free_rb (RingBuffer* rb, int segment_count)
{
  char        shm_region[16];
  int         shm_fd, segment_iter;

  segment_iter = 0; 
  do {
    sprintf(shm_region, "%s-%d", SERVERNAME, segment_iter);
    segment_iter++;
  } while ( segment_iter < segment_count );
 
  return 0;
}

void
size_report (RingBuffer rb)
{
  int pageSize = getpagesize();
  printf ("Message size: %d bytes\n", BUFFERSIZE);
  printf ("Messages per segment: %d\n", MSG_PER_SEGM);
  printf ("Segment size: %d bytes\n", SEGSIZE);
  printf ("Segment count: %li\n", SEGCOUNT);
  printf ("Page size: %d\n", pageSize);
  printf ("RingBuffer segment: %lu\n", sizeof(rb));
}

void
write_log(RingBuffer* rb, char* entry)
{
  
}

int
main (void)
{
  int           result, segments;
  RingBuffer    rb;

  printf("Starting ... \n");
  result = 0;
  segments = 12;
  result = init_rb(&rb, 4096, segments);

  //size_report(rb);

  //result = free_rb(&rb, segments);

  return result;
}
