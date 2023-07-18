CXX=clang++
CXXFLAGS=--std=c++20 -Wall -Wextra -Wpedantic -Werror -O0 -glldb -DPHASE1
LDFLAGS=

EXE=encode

SRC=src
INCLUDE=include
BUILD=build

SOURCES=$(shell find $(SRC) -name '*.cc')
OBJECTS=$(patsubst $(SRC)/%.cc,$(BUILD)/%.o,$(SOURCES))
DEPS=$(OBJECTS:.o=.d)

$(EXE): $(BUILD)/Encode.o
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o: $(SRC)/%.cc
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) -MMD -c $< -o $@

.PHONY: clean
clean:
	rm -fr $(BUILD) $(EXE)

-include $(DEPS)
