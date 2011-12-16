PROJECT = dedebtifier
M1 = main
M2 = debts
M3 = debt_errors
M4 = utilities
M5 = ctest
M6 = test_suites
M7 = cui
MODULES = $(M1) $(M2) $(M3) $(M4) $(M5) $(M6) $(M7)
OBJECTS = $(addprefix $(OUT)/,$(addsuffix .o,$(MODULES)))

UT = $(SRC)/unittest.h
CC = gcc
CO = -ansi -std=c99 -pedantic-errors
LO =
SRC = src
TEST = $(SRC)/test
OUT = bin
EXT = c

$(OUT)/$(PROJECT): $(OBJECTS) 
	$(CC) $(LO) -o $@ $^

$(OUT)/$(M1).o: $(SRC)/$(M1).$(EXT) $(SRC)/$(M1).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M2).o: $(SRC)/$(M2).$(EXT) $(SRC)/$(M2).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M3).o: $(SRC)/$(M3).$(EXT) $(SRC)/$(M3).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M4).o: $(SRC)/$(M4).$(EXT) $(SRC)/$(M4).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M5).o: $(TEST)/$(M5).$(EXT) $(TEST)/$(M5).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M6).o: $(TEST)/$(M6).$(EXT) $(TEST)/$(M6).h $(UT)
	$(CC) $(CO) -c -o $@ $<

$(OUT)/$(M7).o: $(SRC)/$(M7).$(EXT) $(SRC)/$(M7).h $(UT)
	$(CC) $(CO) -c -o $@ $<

clean:
	(rm $(OUT)/*.o $(OUT)/$(PROJECT))
