LDFLAGS = -L. -lglfw -lGL -ldl # -lpthread
CXXFLAGS = -g -Wall -Wno-write-strings -Wno-parentheses -DLINUX #-pthread

OBJS = linalg.o ll.o world.o lander.o landscape.o gpuProgram.o strokefont.o fg_stroke.o glad/src/glad.o
EXEC = lunar

ifeq ($(PREFIX),)
	PREFIX := /usr/local/bin
endif

all:    $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lunar:	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

install: all
	install -D lunar $(DESTDIR)$(PREFIX)/lunar
	#install -m 111 --owner=root --group=root lunar $(PREFIX)/

depend:
	makedepend -Y *.h *.cpp 2> /dev/null

.PHONY : all install depend clean

# DO NOT DELETE
# Must remake when these header changes
gpuProgram.o: headers.h glad/include/glad/glad.h linalg.h
headers.o: glad/include/glad/glad.h linalg.h
lander.o: headers.h glad/include/glad/glad.h linalg.h
landscape.o: headers.h glad/include/glad/glad.h linalg.h
strokefont.o: headers.h glad/include/glad/glad.h linalg.h
world.o: headers.h glad/include/glad/glad.h linalg.h landscape.h lander.h
world.o: ll.h
fg_stroke.o: strokefont.h headers.h glad/include/glad/glad.h linalg.h
gpuProgram.o: gpuProgram.h headers.h glad/include/glad/glad.h linalg.h
lander.o: headers.h glad/include/glad/glad.h linalg.h lander.h world.h
lander.o: landscape.h ll.h gpuProgram.h
landscape.o: headers.h glad/include/glad/glad.h linalg.h landscape.h
landscape.o: gpuProgram.h ll.h
linalg.o: linalg.h
ll.o: headers.h glad/include/glad/glad.h linalg.h gpuProgram.h world.h
ll.o: landscape.h lander.h ll.h
strokefont.o: strokefont.h headers.h glad/include/glad/glad.h linalg.h
strokefont.o: fg_stroke.h
world.o: world.h headers.h glad/include/glad/glad.h linalg.h landscape.h
world.o: lander.h ll.h gpuProgram.h strokefont.h
