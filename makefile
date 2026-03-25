CXX = g++
CXXFLAGS_COMMON = -std=c++17 -Wall -Wpedantic -Wextra -fexceptions -fopenmp

CXXFLAGS = $(CXXFLAGS_COMMON) -O3 -march=native -flto -mavx2 -DNDEBUG

TARGET = aco

BUILDDIR = build

SRCDIR = src

SOURCES = aco.cpp problem_instance.cpp

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
