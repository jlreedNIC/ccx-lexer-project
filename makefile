# Macros
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -pedantic-errors

# Files
EXEC = dest/parser_exc
SRC_FILES = src/main.cpp src/lexer.cpp
OBJ_FILES = obj
DEST_FILES = dest

# Pattern for building .o files
$(OBJ_FILES)/%.o : src/%.cpp
	mkdir -p $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build Dependencies
$(EXEC) : $(OBJ_FILES)/main.o $(OBJ_FILES)/lexer.o
	mkdir -p $(DEST_FILES)
	$(CXX) $(CXXFLAGS) $< $(OBJ_FILES)/lexer.o -o $@

$(OBJ_FILES)/main.o : src/lexer.h

$(OBJ_FILES)/lexer.o : src/lexer.h


# Test
IN_DIR = ccx

# Pattern rule for running program and checking differences
$(IN_DIR)/%.test.lexer.out : $(IN_DIR)/%
	$(EXEC) $<
	diff $<.lexer.out $@ -s
	mv $@ $(DEST_FILES)

test: $(IN_DIR)/complex.cci.test.lexer.out\
	$(IN_DIR)/complex.ccx.test.lexer.out\
	$(IN_DIR)/date.cci.test.lexer.out\
	$(IN_DIR)/date.ccx.test.lexer.out\
	$(IN_DIR)/hello_world.ccx.test.lexer.out\
	$(IN_DIR)/list.cci.test.lexer.out\
	$(IN_DIR)/list.ccx.test.lexer.out\
	$(IN_DIR)/natural.cci.test.lexer.out\
	$(IN_DIR)/natural.ccx.test.lexer.out\
	$(IN_DIR)/trie.cci.test.lexer.out\
	$(IN_DIR)/trie.ccx.test.lexer.out\
	$(IN_DIR)/widget.cci.test.lexer.out\
	$(IN_DIR)/widget.ccx.test.lexer.out\

# the following is my testing code
run_all:
	$(EXEC) ccx/complex.cci
	mv ccx/complex.cci.test.lexer.out $(DEST_FILES)

	$(EXEC) ccx/complex.ccx
	mv ccx/complex.ccx.test.lexer.out $(DEST_FILES)

	$(EXEC) ccx/date.cci
	mv ccx/date.cci.test.lexer.out $(DEST_FILES)

	$(EXEC) ccx/date.ccx
	mv ccx/date.ccx.test.lexer.out $(DEST_FILES)

	$(EXEC) ccx/hello_world.ccx
	mv ccx/hello_world.ccx.test.lexer.out $(DEST_FILES)

check :
	diff ccx/complex.cci.lexer.out dest/complex.cci.test.lexer.out -y
	diff ccx/complex.ccx.lexer.out dest/complex.ccx.test.lexer.out -s
	diff ccx/date.cci.lexer.out dest/date.cci.test.lexer.out -s
	diff ccx/date.ccx.lexer.out dest/date.ccx.test.lexer.out -s
	diff ccx/hello_world.ccx.lexer.out dest/hello_world.ccx.test.lexer.out -s

# remove everything!
clean : cleanLexer
	rm -fr $(OBJ_FILES)
	rm -fr $(DEST_FILES)

cleanLexer:
	rm -f ccx/complex.cci.test.lexer.out
	rm -f ccx/complex.ccx.test.lexer.out
	rm -f ccx/date.cci.test.lexer.out
	rm -f ccx/date.ccx.test.lexer.out
	rm -f ccx/hello_world.ccx.test.lexer.out
	rm -f ccx/list.cci.test.lexer.out
	rm -f ccx/list.ccx.test.lexer.out
	rm -f ccx/natural.cci.test.lexer.out
	rm -f ccx/natural.ccx.test.lexer.out
	rm -f ccx/trie.cci.test.lexer.out
	rm -f ccx/trie.ccx.test.lexer.out
	rm -f ccx/widget.cci.test.lexer.out
	rm -f ccx/widget.ccx.test.lexer.out