CC = g++-7
SDSLFLAGS = -O3 -DNDEBUG -I ~/include
LFLAGS = -L ~/lib -lsdsl -ldivsufsort -ldivsufsort64 -lstdc++fs
CFLAGS = -c -std=c++17 -Wall -Wno-missing-braces $(SDSLFLAGS)
EXEC = main
OBJS = main.o
MWT = m_wt.o
#BITVECTORS = normal_bv.o sd_bv.o rrr_bv.o s18_bv.o
BITVECTORS = sd_bv.o 

$(EXEC): $(OBJS) $(BITVECTORS)
	$(CC) $^ -o $@ $(LFLAGS) $(SDSLFLAGS)


%.o: src/%.cpp
	$(CC) $< $(CFLAGS)

%.o: src/m_wt/%.cpp
	$(CC) $< $(CFLAGS)

%.o: src/bit_vectors/%.cpp
	$(CC) $< $(CFLAGS)

clean:
	find . -name '*.o' -type f -delete

cleanall:
	find . -name '*.o' -type f -delete
	rm -f $(EXEC)

run:

#########################
# 
#  X: BASELINES:
#  0 : AP
#  1 : RLMN
#  2 : RUNS
# 
# 
#  XX : BV + WT 
# 
#  - BV :
#  1:SD
#  2:S18
#  3:PEF 
# 
#  - WT : 
#  1:INT
#  2:AP
#  3:RLMN-INT
#  4:RLMN-AP
#  5:RUNS-AP
#  6:RUNS-RLMN
# 
##############################

#	./$(EXEC) coreutils

#	./$(EXEC) einstein.de.txt 1
#	./$(EXEC) einstein.de.txt 2
#	./$(EXEC) einstein.de.txt 3

#	./$(EXEC) einstein.en.txt

#	./$(EXEC) english.001.2 1
#	./$(EXEC) english.001.2 0
#	./$(EXEC) english.001.2 2
#	./$(EXEC) english.001.2 11
#	./$(EXEC) english.001.2 12
#	./$(EXEC) english.001.2 13
#	./$(EXEC) english.001.2 14
#	./$(EXEC) english.001.2 15
#	./$(EXEC) english.001.2 16
#	./$(EXEC) english.001.2 21
#	./$(EXEC) english.001.2 22
#	./$(EXEC) english.001.2 23
#	./$(EXEC) english.001.2 24
#	./$(EXEC) english.001.2 25
#	./$(EXEC) english.001.2 26

#	./$(EXEC) world_leaders

	./$(EXEC) world_leaders 11
	./$(EXEC) world_leaders 12
	./$(EXEC) world_leaders 13
	./$(EXEC) world_leaders 14
	./$(EXEC) world_leaders 15
	./$(EXEC) world_leaders 16
	./$(EXEC) world_leaders 21
	./$(EXEC) world_leaders 22
	./$(EXEC) world_leaders 23
	./$(EXEC) world_leaders 24
	./$(EXEC) world_leaders 25
	./$(EXEC) world_leaders 26
	./$(EXEC) world_leaders 31
	./$(EXEC) world_leaders 32
	./$(EXEC) world_leaders 33
	./$(EXEC) world_leaders 34
	./$(EXEC) world_leaders 35
	./$(EXEC) world_leaders 36

