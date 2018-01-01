#variable CXX is the C++ compiler to use
CXX=clang++40
#DEBUG is the variable containing flags passed for debugging
DEBUG = -g
#CXXFLAGS are the options to pass to the C++ compiler
CXXFLAGS= -Wall -I/usr/local/include -std=c++11 $(DEBUG)
#LDLIBS is the variable for library flags passed to the compiler
LDLIBS = -lxerces-c -L/usr/local/lib

#variable objects is for object files used to make program executable
objects = musicxml-parse-main.o \
SAX2HandlerMusicXML.o \
note.o notebinaryconverter.o \
MusicXMLEntityResolver.o

#to dereference variables just use the dereference operator $(VAR)

#executable: dereferenced objects variable
#TAB# dereferenced compiler #space# dereferenced compiler flags #space# dereferenced library flags

#create executable which depends on objects variable
musicxml-parse: $(objects)
	$(CXX) -o musicxml-parse $(objects) $(LDLIBS)

#object file: cpp file used to make object file #space# cpp dependencies for main cpp file
#TAB# Compiler Compiler Flags -c main cpp file object file is made from

#create main object file
musicxml-parse-main.o: musicxml-parse-main.cpp 
	$(CXX) $(CXXFLAGS) -c musicxml-parse-main.cpp 

#create SAX2HandlerMusicXML object file
SAX2HandlerMusicXML.o: SAX2HandlerMusicXML.cpp SAX2HandlerMusicXML.hpp note.h
	$(CXX) $(CXXFLAGS) -c SAX2HandlerMusicXML.cpp

#create Note object file
note.o: note.cpp note.h
	$(CXX) $(CXXFLAGS) -c note.cpp 

#create Note binary converter object file
notebinaryconverter.o: notebinaryconverter.cpp notebinaryconverter.h
	$(CXX) $(CXXFLAGS) -c notebinaryconverter.cpp

#create Music XML Entity Resolver object file
MusicXMLEntityResolver.o: MusicXMLEntityResolver.cpp MusicXMLEntityResolver.hpp
	$(CXX) $(CXXFLAGS) -c MusicXMLEntityResolver.cpp

#remove executable file and its object file dependencies
clean:
	rm musicxml-parse $(objects)
