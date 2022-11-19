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


#	einstein.en.txt | listo

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



#	RL RUNS AP Y GMR

#	./$(EXEC) einstein.de.txt 200

#	./$(EXEC) einstein.de.txt 1000
#	./$(EXEC) einstein.de.txt 1001
#	./$(EXEC) einstein.de.txt 1002
#	./$(EXEC) einstein.de.txt 1003
#	./$(EXEC) einstein.de.txt 1004
#	./$(EXEC) einstein.de.txt 1005
#	./$(EXEC) einstein.de.txt 1006
#	./$(EXEC) einstein.de.txt 1007
#	./$(EXEC) einstein.de.txt 1008
#	./$(EXEC) einstein.de.txt 1009
#	./$(EXEC) einstein.de.txt 1010
#	./$(EXEC) einstein.de.txt 1011

#	./$(EXEC) coreutils 1000
#	./$(EXEC) coreutils 1001
#	./$(EXEC) coreutils 1002

#	./$(EXEC) coreutils 1003
#	./$(EXEC) coreutils 1004
#	./$(EXEC) coreutils 1005

	./$(EXEC) coreutils 1006
	./$(EXEC) coreutils 1007
	./$(EXEC) coreutils 1008

	./$(EXEC) coreutils 1009
	./$(EXEC) coreutils 1010
	./$(EXEC) coreutils 1011
#
#	./$(EXEC) english.001.2 1000
#	./$(EXEC) english.001.2 1001
#	./$(EXEC) english.001.2 1002
#	./$(EXEC) english.001.2 1003
#	./$(EXEC) english.001.2 1004
#	./$(EXEC) english.001.2 1005
#	./$(EXEC) english.001.2 1006
#	./$(EXEC) english.001.2 1007
#	./$(EXEC) english.001.2 1008
#	./$(EXEC) english.001.2 1009
#	./$(EXEC) english.001.2 1010
#	./$(EXEC) english.001.2 1011
#
#	./$(EXEC) world_leaders 1000
#	./$(EXEC) world_leaders 1001
#	./$(EXEC) world_leaders 1002
#	./$(EXEC) world_leaders 1003
#	./$(EXEC) world_leaders 1004
#	./$(EXEC) world_leaders 1005
#	./$(EXEC) world_leaders 1006
#	./$(EXEC) world_leaders 1007
#	./$(EXEC) world_leaders 1008
#	./$(EXEC) world_leaders 1009
#	./$(EXEC) world_leaders 1010
#	./$(EXEC) world_leaders 1011
#
#	./$(EXEC) einstein.en.txt 1000
#	./$(EXEC) einstein.en.txt 1001
#	./$(EXEC) einstein.en.txt 1002
#	./$(EXEC) einstein.en.txt 1003
#	./$(EXEC) einstein.en.txt 1004
#	./$(EXEC) einstein.en.txt 1005
#	./$(EXEC) einstein.en.txt 1006
#	./$(EXEC) einstein.en.txt 1007
#	./$(EXEC) einstein.en.txt 1008
#	./$(EXEC) einstein.en.txt 1009
#	./$(EXEC) einstein.en.txt 1010
#	./$(EXEC) einstein.en.txt 1011





#	./$(EXEC) einstein.de.txt 1000
#	./$(EXEC) einstein.de.txt 1001
#	./$(EXEC) einstein.de.txt 1002
#	./$(EXEC) einstein.de.txt 1003
#	./$(EXEC) einstein.de.txt 1004
#	./$(EXEC) einstein.de.txt 1005
#	./$(EXEC) einstein.de.txt 1006
#	./$(EXEC) einstein.de.txt 1007
#	./$(EXEC) einstein.de.txt 1008
#	./$(EXEC) einstein.de.txt 1009
#	./$(EXEC) einstein.de.txt 1010
#	./$(EXEC) einstein.de.txt 1011
