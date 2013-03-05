LEX=lex
YACC=yacc


CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =	main.o node.o scanner.o parser.o eval_context.o asm_context.o symbol_table.o quad_context.o quadruple.o

LIBS =

TARGET = calc

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	
eval_context.o:	
	$(CXX) $(CXXFLAGS) -c eval_context.cpp -o eval_context.o
asm_context.o:
	$(CXX) $(CXXFLAGS) -c asm_context.cpp -o asm_context.o
quadruple.o:
	$(CXX) $(CXXFLAGS) -c quadruple.cpp -o quadruple.o
quad_context.o:
	$(CXX) $(CXXFLAGS) -c quad_context.cpp -o quad_context.o
symbol_table.o:
	$(CXX) $(CXXFLAGS) -c symbol_table.cpp -o symbol_table.o
node.o:	
	$(CXX) $(CXXFLAGS) -c node.cpp -o node.o
main.o:	 parser.o scanner.o asm_context.o
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o
	
scanner.o:
	$(LEX) --prefix=cal -o scanner.cpp calculator.lex
parser.o: scanner.o
	$(YACC) --defines=parser.h -v -p cal -o parser.cpp calculator.yacc
	$(CXX) $(CXXFLAGS) -c parser.cpp -o parser.o
	$(CXX) $(CXXFLAGS) -c scanner.cpp -o scanner.o

all:	$(TARGET)
	./$(TARGET) input -o output.s
	gcc -o output -m32 -g output.s
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f output output.s output.o
