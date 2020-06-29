TARGET = zilinjak
BUILD_DIR = build
CXX = g++
CXX_FLAGS = -Wall -pedantic --std=c++17 -g
CXX_LIBS = -lstdc++fs

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/CSymlink.o $(BUILD_DIR)/CFile.o $(BUILD_DIR)/CBrowser.o $(BUILD_DIR)/CCopy.o $(BUILD_DIR)/CData.o $(BUILD_DIR)/CDelete.o $(BUILD_DIR)/CFolder.o $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CMove.o $(BUILD_DIR)/COperations.o $(BUILD_DIR)/CRegExp.o
	mkdir -p $(BUILD_DIR);	$(CXX) $^ -o $@ $(CXX_LIBS)

$(BUILD_DIR)/%.o: src/%.cpp
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -c -o $@ $(CXX_LIBS)

.PHONY: all
all: compile

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY:doc
doc:

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET) 2>/dev/null


#Dependencies
$(BUILD_DIR)/CSymlink.o: src/CSymlink.cpp src/CSymlink.h src/CData.h
$(BUILD_DIR)/CFile.o: src/CFile.cpp src/CFile.h src/CData.h
$(BUILD_DIR)/CBrowser.o: src/CBrowser.cpp src/CBrowser.h src/CFolder.h src/CFile.h src/CData.h src/CDelete.h src/COperations.h src/CMove.h src/CCopy.h
$(BUILD_DIR)/CCopy.o: src/CCopy.cpp src/CCopy.h src/COperations.h src/CFolder.h src/CFile.h src/CData.h
$(BUILD_DIR)/CData.o: src/CData.cpp src/CData.h
$(BUILD_DIR)/CDelete.o: src/CDelete.cpp src/CDelete.h src/CFolder.h src/CFile.h src/CData.h src/COperations.h
$(BUILD_DIR)/CFolder.o: src/CFolder.cpp src/CFolder.h src/CFile.h src/CData.h
$(BUILD_DIR)/CInterface.o: src/CInterface.cpp src/CInterface.h src/CBrowser.h src/CFolder.h src/CFile.h src/CData.h src/CDelete.h src/COperations.h src/CMove.h src/CCopy.h src/CRegExp.h
$(BUILD_DIR)/CMove.o: src/CMove.cpp src/CMove.h src/COperations.h src/CFolder.h src/CFile.h src/CData.h
$(BUILD_DIR)/COperations.o: src/COperations.cpp src/COperations.h
$(BUILD_DIR)/CRegExp.o: src/CRegExp.cpp src/CRegExp.h src/CData.h src/CDelete.h src/CFolder.h src/COperations.h src/CMove.h src/CCopy.h
$(BUILD_DIR)/main.o: src/main.cpp src/CInterface.h src/CBrowser.h src/CFolder.h src/CFile.h src/CData.h src/CDelete.h src/COperations.h src/CMove.h src/CCopy.h src/CRegExp.h