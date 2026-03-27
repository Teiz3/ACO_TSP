CXX = g++
CXXFLAGS_COMMON = -std=c++17 -Wall -Wpedantic -Wextra -fexceptions -fopenmp

# Change to debug to compile with debugging flags
MODE = debug

ifeq ($(MODE),release)
	CXXFLAGS = $(CXXFLAGS_COMMON) -O3 -march=native -flto -mavx2 -DNDEBUG
else
	CXXFLAGS = $(CXXFLAGS_COMMON) -g
endif

TARGET = aco

BUILDDIR = build

SRCDIR = src

SOURCES = aco.cpp problem_instance.cpp ant.cpp

OBJS = $(SOURCES:.cpp=.o)

OUT_OBJS = $(addprefix $(BUILDDIR)/,$(OBJS))

.PHONY: clean all

all: $(TARGET)

$(TARGET): $(OUT_OBJS)
	$(CXX) $(CXXFLAGS) $(OUT_OBJS) $(LDFLAGS) -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p results
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT_OBJS) $(TARGET)
