UNAME := $(shell uname)

Sample: Sample.cpp
	$(CXX) -Wall -g -I../include Sample.cpp -o Sample ../lib/libLeap.dylib
ifeq ($(UNAME), Darwin)
	install_name_tool -change ../lib/libLeap.dylib @loader_path/libLeap.dylib Sample
endif

clean:
	rm -rf Sample Sample.dSYM
