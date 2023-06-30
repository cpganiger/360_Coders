APP_NAME = Packet

SRC=packet.cc\
crc/src/crc16.c

TEST_SRC=test_packet.cc

INC = -Icrc/include

build:
	g++ $(SRC) $(INC) -o $(APP_NAME).out -lgtest -lgtest_main -lpthread 

run: build
	./$(APP_NAME).out

test_build:
	g++ $(SRC) $(TEST_SRC) $(INC) -o $(APP_NAME).out -lgtest -lgtest_main -lpthread 

test_run: test_build
	./$(APP_NAME).out

analyze: staticcheck memcheck

staticcheck:
	cppcheck --enable=all packet.cc

sanitize_check:
	g++ -fsanitize=address -fno-omit-frame-pointer $(SRC) $(TEST_SRC) $(INC) -o $(TEST_OUTPUT) $(INCLUDE_LIBS)
	./$(APP_NAME).out

coverage:
	g++ $(SRC) $(TEST_SRC) $(INC) -fprofile-arcs -ftest-coverage -o $(APP_NAME).out -lpthread -lgtest -lgtest_main
	./$(APP_NAME).out
	gcov -a packet.cc

memcheck: build
	valgrind ./$(APP_NAME).out

clean:
	rm -rf *.o *.out *.exe