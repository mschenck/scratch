
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

void
name_region (char* region_str, int index)
{
  char        prefix_str[PREFIX_LEN];

  strncpy(prefix_str, SERVERNAME, PREFIX_LEN);
  sprintf(region_str, "/%s-%d", prefix_str, index);
}

/*
  # Generate a shm_region string
    - Used per ring buffer segment
    - Leverages SERVERNAME
    - Format: REGION_LEN character string NAME-index
      - NAME: created from SERVERNAME (only first PREFIX_LEN char)
      - index: from passed integer 
*/
RingBuffer*
init_rb (size_t segment_size, int segment_count)
{
  RingBuffer  *current, *head, *last;
  int         shm_fd, segment_iter;
  char        shm_region[REGION_LEN];

  segment_iter = 0; 
  do {
    name_region(shm_region, segment_iter);
    printf("The shm_region is '%s' and the size is %d bytes\n", shm_region, sizeof(RingBuffer));

    shm_fd = shm_open(shm_region, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if (shm_fd == -1) {
      printf("FATAL: Unable to get file descriptor for segment %s\n", shm_region);
      return -1;
    } else {
      printf("DEBUG:\tshm_region: %s\tfd: %d\n", shm_region, (int)shm_fd);
    }

    if (ftruncate(shm_fd, sizeof(RingBuffer)) == -1) {
      printf("FATAL: Unable to truncate shm segment %s\n", shm_region);
      return -1;
    }

    current = mmap(0, sizeof(RingBuffer), PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (current == MAP_FAILED) {
      printf("FATAL: Unable to map shm segment %s\n", shm_region);
      return -1;
    }

    close(shm_fd); 

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

  return head;
}

void
free_rb (int segment_count)
{
  char        shm_region[REGION_LEN];
  int         segment_index;

  for (segment_index = 0; segment_index < segment_count; segment_index++) {
    name_region(shm_region, segment_index);
    shm_unlink(shm_region);
  }
}





int
main (void)
{
  int           seg_size, segments;
  RingBuffer    *rb;

  seg_size = 4096;
  segments = 12;

  // Create buffer
  rb = init_rb(seg_size, segments);

  // Release buffer memory
  free_rb(segments);

  return 0;
}
