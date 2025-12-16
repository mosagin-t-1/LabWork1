CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

OBJS = main.o bmpheader.o bmpimage.o filters.o

lab1: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o lab1

main.o: main.cpp bmpheader.h bmpimage.h filters.h
	$(CXX) $(CXXFLAGS) -c main.cpp

bmpheader.o: bmpheader.cpp bmpheader.h
	$(CXX) $(CXXFLAGS) -c bmpheader.cpp

bmpimage.o: bmpimage.cpp bmpimage.h bmpheader.h pixel.h
	$(CXX) $(CXXFLAGS) -c bmpimage.cpp

filters.o: filters.cpp filters.h bmpimage.h
	$(CXX) $(CXXFLAGS) -c filters.cpp

test: test_bmpimage.cpp test_filters.cpp bmpheader.cpp bmpimage.cpp filters.cpp
	$(CXX) $(CXXFLAGS) test_bmpimage.cpp test_filters.cpp bmpheader.cpp bmpimage.cpp filters.cpp -o runTests -lgtest -lgtest_main -lpthread
	./runTests

clean:
	rm -f *.o lab1 runTests

