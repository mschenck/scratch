#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>

int
main (void)
{
  struct passwd *user_entry;
  user_entry = getpwnam ("daemon");

  printf ("The UID for the 'daemon' user is: %d\n", user_entry->pw_uid);
  printf ("The GID for the 'daemon' user is: %d\n", user_entry->pw_gid);

  return 0;
}
