
V := 0
M_0 := @
M_1 :=
M = $(M_$(V)

OUTDIR ?= ./build
CXXFLAGS := -std=gnu++11
CPPFLAGS := -Wall -pedantic -O0 -ggdb

.PHONY: clean

all: proto main

rebuild: clean all ;

clean:
	rm ./src/Proto.cpp $(OUTDIR) -fr || true

proto: src/Proto.cpp src/Proto.hpp

src/Proto.cpp src/Proto.hpp: lib/proto/mindspy.proto lib/proto/mindspy.options
	$(MAKE) -C lib/proto Proto.cpp
	mv lib/proto/Proto.[ch]pp src/

build: $(OUTDIR)
	$Mmkdir $(OUTDIR)

%.cpp.o: src/%.cpp build
	@echo "Compiling <" `basename $<`
	$Mmkdir -p $(dir $@)
	$M$(COMPILE.cpp) -o $(OUTDIR)/$@ $<

main: main.cpp.o Subprocess.cpp.o CodedStream.cpp.o MatchingStream.cpp.o Proto.cpp.o
	@echo "Linking" `basename $@` "<" $?
	$M$(CXX) $? -o $(OUTDIR)/$@ -lstdc++ -lgcc -lprotobuf -libusb 





