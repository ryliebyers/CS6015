INCS = catch.h cmdline.hpp expr.h
OBJS = main.o cmdline.o expr.o
CXXFLAGS = -O2 -g –std=c++11
msdscript: $(OBJS)
c++ -o msdscript $(OBJS)

.phony: test
test: msdscript
./msdscript --test

main.o: cmdline.h
cmdline.o: catch.h cmdline.h
expr.o: $(INCS)


