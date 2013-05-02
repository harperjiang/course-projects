LEX=lex
YACC=yacc


CXXFLAGS =	-O0 -g -Wall -fmessage-length=0

OBJS =	main.o scanner.o parser.o node.o exception.o eval_context.o asm_context.o acc_hist.o act_record.o memory_pool.o quadruple.o quad_context.o

LIBS =

TARGET = pasc

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
quadruple.o:
	$(CXX) $(CXXFLAGS) -c quadruple.cpp -o quadruple.o
quad_context.o:
	$(CXX) $(CXXFLAGS) -c quad_context.cpp -o quad_context.o
memory_pool.o:
	$(CXX) $(CXXFLAGS) -c memory_pool.cpp -o memory_pool.o
asm_context.o:
	$(CXX) $(CXXFLAGS) -c asm_context.cpp -o asm_context.o
acc_hist.o:
	$(CXX) $(CXXFLAGS) -c acc_hist.cpp -o acc_hist.o	
act_record.o:
	$(CXX) $(CXXFLAGS) -c act_record.cpp -o act_record.o
eval_context.o:
	$(CXX) $(CXXFLAGS) -c eval_context.cpp -o eval_context.o
exception.o:
	$(CXX) $(CXXFLAGS) -c exception.cpp -o exception.o
node.o:  
	$(CXX) $(CXXFLAGS) -c node.cpp -o node.o
main.o:
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
