# unix-utilities
A Simple Unix Utilities for process and filesystem management
mytree is similar to tree linux command
mytime is similar to time linux command
mymtimes is to list file counts modified in last 24 hours in every 1 hour interval

To compile the code run below commands -

1. To compile mytree.c 
	$make mytree

2. To compile mytime.c
	$make mytime

3. To compile mymtimes.c
	$make mymtimes


To run the code - 

4. Run mytree with relative path to the directory from current directory.
	$./mytree ../project1/

5. Run mytree for current directory
	$./mytree


6. Run mytime <command>
	$./mytime /bin/ls


7. Run mymtimes on current directory
	$./mymtimes

8. Run mymtimes with relative path to the directory from current directory.
	$./mytimes ../project1/
