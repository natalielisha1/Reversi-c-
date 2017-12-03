SOURCES := $(wildcard src/*.cpp)
INCLUDES := "./include/"

SOURCES_NO_MAIN := $(filter-out src/main.cpp, $(SOURCES))
SOURCES_GTESTS := $(wildcard gtest_src/gtest/*.cc)
SOURCES_TESTS := $(wildcard test/*.cpp)
INCLUDES_GTESTS := "./gtest_src/"

OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)

OBJECTS_NO_MAIN := $(SOURCES_NO_MAIN:src/%.cpp=obj/%.o)
OBJECTS_GTESTS := $(SOURCES_GTESTS:gtest_src/gtest/%.cc=gtest_src/gtest/%.o)
OBJECTS_TESTS := $(SOURCES_TESTS:test/%.cpp=obj/%.o)

Client: clean $(OBJECTS)
	g++ $(OBJECTS) $(DEBUG) -o ../../exe/Client
	
test: clean $(OBJECTS_NO_MAIN) $(OBJECTS_GTESTS) $(OBJECTS_TESTS)
	g++ $(OBJECTS_NO_MAIN) $(OBJECTS_GTESTS) $(OBJECTS_TESTS) $(DEBUG) -o ../../exe/ClientTest -lpthread
	
testD: DEBUG = -g

testD: test

debugRun: DEBUG = -g

debugRun: clean Client
	@../../exe/Client

debugTest: DEBUG = -g

debugTest: clean test
	@../../exe/ClientTest
	
all: DEBUG = -g

all: Client

$(OBJECTS): obj/%.o : src/%.cpp
	g++ -I$(INCLUDES) $(DEBUG) -c $< -o $@
	
$(OBJECTS_GTESTS): gtest_src/gtest/%.o : gtest_src/gtest/%.cc
	g++ -I$(INCLUDES) -I$(INCLUDES_GTESTS) -c $< -o $@ -lpthread

$(OBJECTS_TESTS): obj/%.o : test/%.cpp
	g++ -I$(INCLUDES) -I$(INCLUDES_GTESTS) -c $< -o $@ -lpthread
	
clean: 
	@rm -f ../../exe/Client
	@rm -f ../../exe/ClientTest
	@rm -f -r obj
	@rm -f gtest_src/gtest/*.o
	@mkdir obj
	@mkdir -p ../../exe