LEX=lex
YACC=yacc


CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =	main.o scanner.o parser.o node.o

LIBS =

TARGET = pasc

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
node.o:  
	$(CXX) $(CXXFLAGS) -c node.cpp -o node.o
main.o:	 parser.o scanner.o node.o
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
	
scanner.o:
	$(LEX) --prefix=pas -o scanner.cpp pascal.lex
parser.o: scanner.o
	$(YACC) --defines=parser.h -v -p pas -o parser.cpp pascal.yacc
	$(CXX) $(CXXFLAGS) -c parser.cpp -o parser.o
	$(CXX) $(CXXFLAGS) -c scanner.cpp -o scanner.o

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
