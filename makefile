# CXX = g++
# CXXFLAGS_COMMON = -std=c++20 -Wall -Wpedantic -Wextra -fexceptions -fopenmp
# SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# # Change to debug to compile with debugging flags
# MODE = release

# # Detect Windows
# ifeq ($(OS),Windows_NT)
#     PLATFORM_FLAGS =
# else
#     PLATFORM_FLAGS = $(SFMLFLAGS)
# endif

# ifeq ($(MODE),release)
# 	CXXFLAGS = $(CXXFLAGS_COMMON) $(PLATFORM_FLAGS) -O3 -march=native -flto -mavx2 -DNDEBUG
# else
# 	CXXFLAGS = $(CXXFLAGS_COMMON) $(PLATFORM_FLAGS) -g
# endif

# CXXFLAGS += -MMD -MP
# -include $(OUT_OBJS:.o=.d)

# TARGET = aco

# BUILDDIR = build

# SRCDIR = src

# SOURCES := $(wildcard $(SRCDIR)/*.cpp) \
#            $(wildcard $(SRCDIR)/*/*.cpp)

# OUT_OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

# .PHONY: clean all

# all: $(TARGET)

# $(TARGET): $(OUT_OBJS)
# 	$(CXX) $(CXXFLAGS) $(OUT_OBJS) $(LDFLAGS) -o $(TARGET)

# $(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
# 	@mkdir -p results
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OUT_OBJS) $(TARGET)

CXX = g++

CXXFLAGS_COMMON = -std=c++20 -Wall -Wpedantic -Wextra -fexceptions -fopenmp
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Change to debug to compile with debugging flags
MODE = release

# Detect Windows
ifeq ($(OS),Windows_NT)
    PLATFORM_FLAGS =
else
    PLATFORM_FLAGS = $(SFMLFLAGS)
endif

# Compilation flags (NO libraries here)
ifeq ($(MODE),release)
	CXXFLAGS = $(CXXFLAGS_COMMON) -O3 -march=native -flto -mavx2 -DNDEBUG
else
	CXXFLAGS = $(CXXFLAGS_COMMON) -g
endif

# Dependency generation
CXXFLAGS += -MMD -MP

# Linker flags (libraries go here)
LDFLAGS = $(PLATFORM_FLAGS)

TARGET = aco
BUILDDIR = build
SRCDIR = src

SOURCES := $(wildcard $(SRCDIR)/*.cpp) \
           $(wildcard $(SRCDIR)/*/*.cpp)

OUT_OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

-include $(OUT_OBJS:.o=.d)

.PHONY: clean all

all: $(TARGET)

# Linking step (libraries AFTER objects)
$(TARGET): $(OUT_OBJS)
	$(CXX) $(OUT_OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation step
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p results
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OUT_OBJS) $(TARGET)