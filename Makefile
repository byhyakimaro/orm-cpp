# Variáveis de Compilação
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I./includes -I.
LDFLAGS  := -lpq

# Diretórios
CORE_DIR     := core
DIALECTS_DIR := dialects/postgres
OBJ_DIR      := build

# Arquivos Fonte
SRCS := orm.cpp \
        $(wildcard $(CORE_DIR)/*.cpp) \
        $(wildcard $(DIALECTS_DIR)/*.cpp)

# Objetos
OBJS := $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Nome do Executável
TARGET := build/orm_app.exe

# Comandos Universais (Funcionam no Git Bash e PowerShell moderno)
MKDIR = mkdir -p $(1)
RM    = rm -rf $(1)

all: prepare $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking $(TARGET)...
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo Verifying...
	@test -f $(TARGET) && echo "File generated: $(TARGET)" || echo "File NOT found"

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling $<...
	@$(call MKDIR,$(dir $@))
	$(CXX) $(CXXFLAGS) -c $< -o $@

prepare:
	@$(call MKDIR,$(OBJ_DIR))

clean:
	@echo Cleaning up...
	@$(RM) $(OBJ_DIR)
	@$(RM) $(TARGET)

.PHONY: all clean prepare
