ALL:helloworld
helloworld:task1 task2

task1:
	mpicc -o task1 Task1.c

task2:
	mpicc -o task2 Task2.c

clean:
	/bin/rm -f task*
