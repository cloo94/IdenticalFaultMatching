#Compiler
CC = g++

#TARGET EXECUTABLE
TARGET = test
FILE = testDesign.cpp

all: $(TARGET)

$(TARGET): $(FILE)
	$(CC) -o $(TARGET)  $(FILE) -I"libLCS/" -L"libLCS/lib" -l LCS

clean:
	$(RM) $(TARGET)
