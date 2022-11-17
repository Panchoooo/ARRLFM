CC = g++-7
SDSLFLAGS = -O3 -msse4.2 -DNDEBUG -I ~/include
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

#	coreutils | listo


#	./$(EXEC) coreutils 204
#	./$(EXEC) coreutils 205
#	./$(EXEC) coreutils 206
#	./$(EXEC) coreutils 207
#	./$(EXEC) coreutils 208
#	./$(EXEC) coreutils 209
#	./$(EXEC) coreutils 210
#	./$(EXEC) coreutils 211
#	./$(EXEC) coreutils 212

#	./$(EXEC) coreutils -1
#	./$(EXEC) coreutils 0
#	./$(EXEC) coreutils 1
#	./$(EXEC) coreutils 2
#	./$(EXEC) coreutils 11
#	./$(EXEC) coreutils 12
#	./$(EXEC) coreutils 13
#	./$(EXEC) coreutils 14
#	./$(EXEC) coreutils 15
#	./$(EXEC) coreutils 16
#	./$(EXEC) coreutils 21
#	./$(EXEC) coreutils 22
#	./$(EXEC) coreutils 23
#	./$(EXEC) coreutils 24
#	./$(EXEC) coreutils 25
#	./$(EXEC) coreutils 26
#	./$(EXEC) coreutils 31
#	./$(EXEC) coreutils 32
#	./$(EXEC) coreutils 33
#	./$(EXEC) coreutils 34
#	./$(EXEC) coreutils 35
#	./$(EXEC) coreutils 36


#	english.001.2 | listo
#	./$(EXEC) english.001.2 200
#	./$(EXEC) english.001.2 201
#	./$(EXEC) english.001.2 202
#	./$(EXEC) english.001.2 203
#	./$(EXEC) english.001.2 204
#	./$(EXEC) english.001.2 205
#	./$(EXEC) english.001.2 206
#	./$(EXEC) english.001.2 207
#	./$(EXEC) english.001.2 208
#	./$(EXEC) english.001.2 209
#	./$(EXEC) english.001.2 210
#	./$(EXEC) english.001.2 211
#	./$(EXEC) english.001.2 212

#	./$(EXEC) english.001.2 100
#	./$(EXEC) english.001.2 101
#	./$(EXEC) english.001.2 102
#	./$(EXEC) english.001.2 103
#	./$(EXEC) english.001.2 104

#	./$(EXEC) english.001.2 300

#	./$(EXEC) english.001.2 -1
#	./$(EXEC) english.001.2 0
#	./$(EXEC) english.001.2 1
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
#	./$(EXEC) english.001.2 31
#	./$(EXEC) english.001.2 32
#	./$(EXEC) english.001.2 33
#	./$(EXEC) english.001.2 34
#	./$(EXEC) english.001.2 35
#	./$(EXEC) english.001.2 36


#	world_leaders | 

#	./$(EXEC) world_leaders 204
#	./$(EXEC) world_leaders 205
#	./$(EXEC) world_leaders 206
#	./$(EXEC) world_leaders 207
#	./$(EXEC) world_leaders 208
#	./$(EXEC) world_leaders 209
#	./$(EXEC) world_leaders 210
#	./$(EXEC) world_leaders 211
#	./$(EXEC) world_leaders 212

#	./$(EXEC) world_leaders -1
#	./$(EXEC) world_leaders 0
#	./$(EXEC) world_leaders 1
#	./$(EXEC) world_leaders 2
#	./$(EXEC) world_leaders 11
#	./$(EXEC) world_leaders 12
#	./$(EXEC) world_leaders 13
#	./$(EXEC) world_leaders 14
#	./$(EXEC) world_leaders 15
#	./$(EXEC) world_leaders 16
#	./$(EXEC) world_leaders 21
#	./$(EXEC) world_leaders 22
#	./$(EXEC) world_leaders 23
#	./$(EXEC) world_leaders 24
#	./$(EXEC) world_leaders 25
#	./$(EXEC) world_leaders 26
#	./$(EXEC) world_leaders 31
#	./$(EXEC) world_leaders 32
#	./$(EXEC) world_leaders 33
#	./$(EXEC) world_leaders 34
#	./$(EXEC) world_leaders 35
#	./$(EXEC) world_leaders 36


#	einstein.de.txt

#	./$(EXEC) einstein.de.txt 204
#	./$(EXEC) einstein.de.txt 205
#	./$(EXEC) einstein.de.txt 206
#	./$(EXEC) einstein.de.txt 207
#	./$(EXEC) einstein.de.txt 208
#	./$(EXEC) einstein.de.txt 209
#	./$(EXEC) einstein.de.txt 210
#	./$(EXEC) einstein.de.txt 211
#	./$(EXEC) einstein.de.txt 212
#	./$(EXEC) einstein.de.txt -1
#	./$(EXEC) einstein.de.txt 0
#	./$(EXEC) einstein.de.txt 1
#	./$(EXEC) einstein.de.txt 2
#	./$(EXEC) einstein.de.txt 11
#	./$(EXEC) einstein.de.txt 12
#	./$(EXEC) einstein.de.txt 13
#	./$(EXEC) einstein.de.txt 14
#	./$(EXEC) einstein.de.txt 15
#	./$(EXEC) einstein.de.txt 16
#	./$(EXEC) einstein.de.txt 21
#	./$(EXEC) einstein.de.txt 22
#	./$(EXEC) einstein.de.txt 23
#	./$(EXEC) einstein.de.txt 24
#	./$(EXEC) einstein.de.txt 25
#	./$(EXEC) einstein.de.txt 26
#	./$(EXEC) einstein.de.txt 31
#	./$(EXEC) einstein.de.txt 32
#	./$(EXEC) einstein.de.txt 33
#	./$(EXEC) einstein.de.txt 34
#	./$(EXEC) einstein.de.txt 35
#	./$(EXEC) einstein.de.txt 36


#	einstein.en.txt

#	./$(EXEC) einstein.en.txt 204
#	./$(EXEC) einstein.en.txt 205
#	./$(EXEC) einstein.en.txt 206
	./$(EXEC) einstein.en.txt 207
#	./$(EXEC) einstein.en.txt 208
#	./$(EXEC) einstein.en.txt 209
#	./$(EXEC) einstein.en.txt 210
#	./$(EXEC) einstein.en.txt 211
#	./$(EXEC) einstein.en.txt 212
#	./$(EXEC) einstein.en.txt -1
#	./$(EXEC) einstein.en.txt 0
#	./$(EXEC) einstein.en.txt 1
#	./$(EXEC) einstein.en.txt 2
#	./$(EXEC) einstein.en.txt 11
#	./$(EXEC) einstein.en.txt 12
#	./$(EXEC) einstein.en.txt 13
#	./$(EXEC) einstein.en.txt 14
#	./$(EXEC) einstein.en.txt 15
#	./$(EXEC) einstein.en.txt 16
#	./$(EXEC) einstein.en.txt 21
#	./$(EXEC) einstein.en.txt 22
#	./$(EXEC) einstein.en.txt 23
#	./$(EXEC) einstein.en.txt 24
#	./$(EXEC) einstein.en.txt 25
#	./$(EXEC) einstein.en.txt 26
#	./$(EXEC) einstein.en.txt 31
#	./$(EXEC) einstein.en.txt 32
#	./$(EXEC) einstein.en.txt 33
#	./$(EXEC) einstein.en.txt 34
#	./$(EXEC) einstein.en.txt 35
#	./$(EXEC) einstein.en.txt 36

