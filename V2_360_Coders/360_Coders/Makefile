PROJECT_NAME =360_linux_app_V1_15062023

SRC = app/app_main.c\
app/timed_activity.c\
common/mqtt_handlers.c\
common/packetiser.c\
ext_libraries/libcrc/src/crc16.c

INC = -Icommon\
-Iapp\
-Iext_libraries/libcrc/include

LIBRARY_NAME = paho-mqtt3a

build: 
	gcc $(INC) $(SRC) -o $(PROJECT_NAME).out -l paho-mqtt3c

debug: 
	gcc -ggdb $(INC) $(SRC) -o $(PROJECT_NAME).out -l paho-mqtt3c
	gdb ./$(PROJECT_NAME).out

run:build
	./$(PROJECT_NAME).out

test:

memory_analysis: 
	valgrind ./$(PROJECT_NAME).out

clean:
	rm -rf *.o *.out *.bin *.exe