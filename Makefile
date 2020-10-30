target:
	cd src && gcc main.c String.c Array.c WildMatch.c -Wall -o main.out
test:
	cd src && \
	cppcheck --error-exitcode=1 *.c *.h && \
	gcc test.c -o test.out String.c Array.c WildMatch.c -lcheck -lm -lpthread -lrt -lsubunit && \
	./test.out && \
	valgrind --leak-check=yes --error-exitcode=1 ./main.out test_data.txt
run:
	cd src && ./main.out
