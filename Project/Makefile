TARGET = test

all: $(TARGET)

$(TARGET) : faultparser.o readComp.o compare.o
	#You NEED to include all flags used previously
	g++ -o test compare.o readComp.o faultparser.o abc/libabc.a -lm -ldl -rdynamic -lreadline -ltermcap -lpthread -std=c++11


faultparser.o : faultparser.cpp
	g++ -c -o faultparser.o faultparser.cpp -std=c++11

#C++ File
compare.o : $(TESTER)
	g++ -c -o compare.o compare.cpp -std=c++11

#C File
readComp.o :$(COMPARATOR)
	gcc -c -o readComp.o readComp.c abc/libabc.a -lm -ldl -rdynamic -lreadline -ltermcap -lpthread

clean :
		rm $(TARGET) faultparser.o readComp.o compare.o
