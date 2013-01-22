for i in `ls /proc/sys/kernel/shm*`; do printf "$i: " ; cat $i ; done 
