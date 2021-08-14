CC 			= g++
CFLAGS 		= -g -Wall
BOOSTDIR 	= /home/user/LLVM_STUFF/boost/boost_1_74_0 
BOOSTINC 	= -I $(BOOSTDIR)
GRAPHDIR 	= ./code
GRAPHINC 	= -I $(GRAPHDIR)
TESTDIR 	= ./test/unit_test
TEMPDIR 	= ./test/temporal
SPACEDIR	= ./test/spatial
BENCHINC    = -isystem ./benchmark/include -L ./benchmark/build/src -lbenchmark -lpthread
VALGRIND    = valgrind --tool=massif --stacks=yes --ignore-fn='generateRandomGraphPrecise(unsigned int)'

unit_test:
	$(CC) $(CFLAGS) $(BOOSTINC) $(GRAPHINC) $(GRAPHDIR)/*.cpp $(TESTDIR)/*.cpp -o $(TESTDIR)/out_files/unit_test ; \
	$(TESTDIR)/out_files/unit_test

temporal_fill:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(TEMPDIR)/fill_in_evaluation.cpp -o $(TEMPDIR)/out_files/fill_in_evaluation  $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; \
	$(TEMPDIR)/out_files/fill_in_evaluation

temporal_lex_p:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(TEMPDIR)/lex_p_evaluation.cpp -o $(TEMPDIR)/out_files/lex_p_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; \
	$(TEMPDIR)/out_files/lex_p_evaluation

temporal_lex_m:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(TEMPDIR)/lex_m_evaluation.cpp -o $(TEMPDIR)/out_files/lex_m_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC) ; \
	$(TEMPDIR)/out_files/lex_m_evaluation

spatial_fill:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/fill_in_evaluation.cpp -o $(SPACEDIR)/out_files/fill_in_evaluation $(GRAPHINC) $(BOOSTINC) ; \
	$(VALGRIND) $(SPACEDIR)/out_files/fill_in_evaluation $(NUM_ELEMENTS)

spatial_lex_p:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/lex_p_evaluation.cpp -o $(SPACEDIR)/out_files/lex_p_evaluation $(GRAPHINC) $(BOOSTINC) ; \
	$(VALGRIND) $(SPACEDIR)/out_files/lex_p_evaluation $(NUM_ELEMENTS)

spatial_lex_m:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(SPACEDIR)/lex_m_evaluation.cpp -o $(SPACEDIR)/out_files/lex_m_evaluation $(GRAPHINC) $(BOOSTINC) ; \
	$(VALGRIND) $(SPACEDIR)/out_files/lex_m_evaluation $(NUM_ELEMENTS)

clean:
	rm -r $(TESTDIR)/out_files/*
	rm -r $(TEMPDIR)/out_files/*
	rm -r $(SPACEDIR)/out_files/*