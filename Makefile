CXX=g++
WT_BASE=/usr/local
CXXFLAGS=--std=c++14 -I$(WT_BASE)/include 
LDFLAGS=-L$(WT_BASE)/lib -Wl,-rpath,$(WT_BASE)/lib -lwthttp -lwt -lboost_thread -lboost_atomic -lboost_filesystem


DEPS = wordle.h
OBJS = main.o wordle.o

%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

wordle: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f wordle $(OBJS)