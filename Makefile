CC 			= g++
CFLAGS 		= -g -Wall
# Fix that variable to include boost libraries (VERSION USED: 1.74.0)
BOOSTDIR 	= /home/user/LLVM_STUFF/boost/boost_1_74_0 
BOOSTINC 	= -I $(BOOSTDIR)
GRAPHDIR 	= ./code
GRAPHINC 	= -I $(GRAPHDIR)
TESTDIR 	= ./test/unit_test
TEMPDIR 	= ./test/temporal
SPACEDIR	= ./test/spatial
# Fix that variable to include google benchmark libraries
BENCHINC    = -isystem ./benchmark/include -L ./benchmark/build/src -lbenchmark -lpthread
VALGRIND    = valgrind --tool=massif --stacks=yes --ignore-fn='generateRandomGraphPrecise(unsigned int)'

# Execute all the tests to check the correctness of the project
unit_test:
	$(CC) $(CFLAGS) $(BOOSTINC) $(GRAPHINC) $(GRAPHDIR)/*.cpp $(TESTDIR)/*.cpp -o $(TESTDIR)/out_files/unit_test ;
	$(TESTDIR)/out_files/unit_test

# Assess the temporal complexity of the function fill_in
temporal_fill:
	$(CC) $(GRAPHDIR)/*.cpp $(TEMPDIR)/fill_in_evaluation.cpp -o $(TEMPDIR)/out_files/fill_in_evaluation  $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; 
	$(TEMPDIR)/out_files/fill_in_evaluation

# Assess the temporal complexity of the function lex_p
temporal_lex_p:
	$(CC) $(GRAPHDIR)/*.cpp $(TEMPDIR)/lex_p_evaluation.cpp -o $(TEMPDIR)/out_files/lex_p_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; 
	$(TEMPDIR)/out_files/lex_p_evaluation

# Assess the temporal complexity of the function lex_m
temporal_lex_m:
	$(CC) $(GRAPHDIR)/*.cpp $(TEMPDIR)/lex_m_evaluation.cpp -o $(TEMPDIR)/out_files/lex_m_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; 
	$(TEMPDIR)/out_files/lex_m_evaluation

# Profile the memory consumption of the function fill_in (Use NUM_ELEMENTS = x to insert the number of elements in the graph, x positive integer)
spatial_fill:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/fill_in_evaluation.cpp -o $(SPACEDIR)/out_files/fill_in_evaluation $(GRAPHINC) $(BOOSTINC) ; 
	$(VALGRIND) $(SPACEDIR)/out_files/fill_in_evaluation $(NUM_ELEMENTS)

# Profile the memory consumption of the function lex_p (Use NUM_ELEMENTS = x to insert the number of elements in the graph, x positive integer)
spatial_lex_p:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/lex_p_evaluation.cpp -o $(SPACEDIR)/out_files/lex_p_evaluation $(GRAPHINC) $(BOOSTINC) ; 
	$(VALGRIND) $(SPACEDIR)/out_files/lex_p_evaluation $(NUM_ELEMENTS)

# Profile the memory consumption of the function lex_m (Use NUM_ELEMENTS = x to insert the number of elements in the graph, x positive integer)
spatial_lex_m:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/lex_m_evaluation.cpp -o $(SPACEDIR)/out_files/lex_m_evaluation $(GRAPHINC) $(BOOSTINC) ; 
	$(VALGRIND) $(SPACEDIR)/out_files/lex_m_evaluation $(NUM_ELEMENTS)

# Clean the out files produced by the previous commmands
clean:
	rm -r $(TESTDIR)/out_files/*
	rm -r $(TEMPDIR)/out_files/*
	rm -r $(SPACEDIR)/out_files/*