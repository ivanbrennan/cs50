# main: main.o util.o
# 	gcc -o main main.o util.o
# main.o: main.c util.h
# 	gcc -c -g main.c
# util.o: util.c util.h
# 	gcc -c -g util.c
stack_driver: stack_driver.o stack.o
	gcc -o stack_driver stack_driver.o stack.o
stack_driver.o: stack_driver.c stack.h
	gcc -c -g stack_driver.c
stack.o: stack.c stack.h
	gcc -c -g stack.c
