all: manualrw randomrw automaticrw reader writer cleanup

automaticrw: rwfunctions.o myfunctions.o myentry.o myclass.o automaticrw.o
	g++ -g -Wall automaticrw.o rwfunctions.o myfunctions.o myentry.o myclass.o -o automaticrw -lpthread

randomrw: rwfunctions.o myfunctions.o myentry.o myclass.o randomrw.o
	g++ -g -Wall randomrw.o rwfunctions.o myfunctions.o myentry.o myclass.o -o randomrw -lpthread

manualrw: rwfunctions.o myfunctions.o myentry.o manualrw.o 
	g++ -g -Wall manualrw.o rwfunctions.o myfunctions.o myentry.o -o manualrw -lpthread

reader: reader.o myentry.o myfunctions.o readerfunctions.o
	g++ -g -Wall reader.o myentry.o myfunctions.o readerfunctions.o -o reader -lpthread

writer: writer.o myentry.o myfunctions.o writerfunctions.o
	g++ -g -Wall writer.o myentry.o myfunctions.o writerfunctions.o -o writer -lpthread

cleanup: cleanup.o myfunctions.o
	g++ -g -Wall cleanup.o myfunctions.o -o cleanup -lpthread

automatic.o: automaticrw.cpp
	g++ -c automaticrw.cpp

randomrw.o: randomrw.cpp
	g++ -c randomrw.cpp

manualrw.o: manualrw.cpp
	g++ -c manualrw.cpp

rwfunctions.o: rwfunctions.cpp
	g++ -c rwfunctions.cpp

reader.o: reader.cpp
	g++ -c reader.cpp

writer.o: writer.cpp
	g++ -c writer.cpp

cleanup.o: cleanup.cpp
	g++ -c cleanup.cpp

myfunctions.o: myfunctions.cpp
	g++ -c myfunctions.cpp

readerfunctions.o: readerfunctions.cpp
	g++ -c readerfunctions.cpp

writerfunctions.o: writerfunctions.cpp
	g++ -c writerfunctions.cpp

myentry.o: myentry.cpp
	g++ -c myentry.cpp

myclass.o: myclass.cpp
	g++ -c myclass.cpp

clean:
	rm -rf *o manualrw reader writer cleanup

