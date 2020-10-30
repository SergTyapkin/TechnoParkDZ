target:
	cd src && gcc curl_main.c String.c Meta.c -Wall -o main.out
test:
	cd src && \
	cppcheck --error-exitcode=1 *.c *.h && \
	gcc curl_main.c String.c Meta.c -lcheck -lm -lpthread -lrt -lsubunit && \
	./test.out && \
	valgrind --leak-check=yes --error-exitcode=1 ./main.out ./PUT
run:
	cd src && ./main.out ./PUT
