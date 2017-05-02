# LambLexer
# by James 2017/04/06

CXX = g++
CXXFLAGS = -g -Wall -O2 -std=c++11
BIN = bin
SRC = src
OBJ = obj
COMPILER = $(BIN)/compiler
LEXER = $(BIN)/lexer

LEX_CONFIG_H = $(SRC)/lex_config.h
LEX_H = $(SRC)/lex.h
UTIL_H = $(SRC)/util.h
TOKEN_H = $(SRC)/token.h
TEST_H = $(SRC)/test.h
ERROR_H = $(SRC)/error.h
SYMSEG_H = $(SRC)/symseg.h
AST_H = $(SRC)/AST.h
COMPILER_H = $(SRC)/compiler.h
PARSER_H = $(SRC)/parser.h
PARSER_CONFIG_H = $(SRC)/parser_config.h

LEX_CPP = $(SRC)/lex.cpp
UTIL_CPP = $(SRC)/util.cpp
TOKEN_CPP = $(SRC)/token.cpp
MAIN_CPP = $(SRC)/main.cpp
TEST_CPP = $(SRC)/test.cpp
PARSER_CPP = $(SRC)/parser.cpp
COMPILER_CPP = $(SRC)/compiler.cpp
LEX_MAIN_CPP = $(SRC)/lex_main.cpp

COMPILER_OBJS = parser.o compiler.o test.o token.o lex.o util.o main.o 
LEXER_OBJS = test.o token.o lex.o util.o lex_main.o 

dir_guard=@mkdir -p $(OBJ)

# for compiler
compiler: $(COMPILER_OBJS)
	$(CXX) $(CXXFLAGS) -o $(COMPILER) $(OBJ)/lex.o $(OBJ)/compiler.o $(OBJ)/parser.o $(OBJ)/test.o $(OBJ)/token.o $(OBJ)/util.o $(OBJ)/main.o 

# for lexer
lexer: $(LEXER_OBJS)
	$(CXX) $(CXXFLAGS) -o $(LEXER) $(OBJ)/lex.o $(OBJ)/test.o $(OBJ)/token.o $(OBJ)/util.o $(OBJ)/main.o 

# main.o is only for compiler
main.o:
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o -c $(MAIN_CPP)
# lex_main.o is only for lexer
lex_main.o:
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/main.o -c $(LEX_MAIN_CPP)
lex.o: 
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/lex.o -c $(LEX_CPP)
util.o: 
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/util.o -c $(UTIL_CPP)
token.o: 
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/token.o -c $(TOKEN_CPP)
test.o:
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/test.o -c $(TEST_CPP)
compiler.o:
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/compiler.o -c $(COMPILER_CPP)
parser.o:
	$(dir_guard)
	$(CXX) $(CXXFLAGS) -o $(OBJ)/parser.o -c $(PARSER_CPP)


	
clean:
	rm $(OBJ)/*.o
