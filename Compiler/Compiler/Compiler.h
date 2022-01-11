#pragma once
#include "CommandTypeTable.h"
#include "RegistersTable.h"
#include <iostream>
#include <regex>
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include "HeaderSection.h"
#include "SymbolTableSection.h"
#include "Section.h"
#include "RegistersTable.h"
#include "InstructionsTable.h"
#include "MemoryElementTable.h"
#include "Instruction.h"
#include "NoOperandInstruction.h"
#include "SingleOperandInstruction.h"
#include "TwoOperandInstruction.h"
#include "RegisterOperand.h"
#include "MemoryOperand.h"
#include "DataOperand.h"
#include "LabelTable.h"
#include "CompilerException.h"

using namespace std;

class Compiler
{
private:
	//containers
	map <CommandType, string> patternList;
	map <int, pair<CommandType, string>> classifiedCommandList;
	map <int, Instruction*> instructionsList;
	//another fields
	ofstream* fout;
	ifstream* fin;
	string fileNameIn_;
	string fileNameOut_;
	string externalName;
	int commandId;
	int sectionsCount;
	int sizeOfSections;
	int currentCommandSize;
	//Tables
	RegistersTable registersTable;
	InstructionsTable instructionsTable;
	MemoryElementTable memoryElementsTable;
	LabelTable labelTable;
	//Sections
	vector <Block*> sectionsList;
	HeaderSection* headerSection;
	map <SectionType, Section*> sections;
	vector <SymbolTableSection*> symbolTableRecords;
	//private methods
	bool parseSourceFile();
	void prepareSections();
	void writeSections();
	void writeSymbolTable();
	void handleStr(string& str);
	void classifyCommand(string command);
	void prepareSymbolTable();
	//split methods
	bool splitInstruction(pair<int, pair<CommandType, string>> el);
	bool splitHeaderInstructions(pair<int, pair <CommandType, string>> command);
	bool splitSegmentInstructions(pair<int, pair < CommandType, string>> command);
	bool splitSingleOperandInstructions(pair<int, pair < CommandType, string>> command);
	bool splitTwoOperandInstructions(pair<int, pair < CommandType, string>> command);
	bool splitNoOperandInstructions(pair<int, pair < CommandType, string>> command);
	bool splitLabeledInstructions(pair<int, pair < CommandType, string>> command);
	bool splitDirective(pair<int, pair < CommandType, string>> command);
	void addMemoryElements(string elements);
public:
	Compiler();
	~Compiler();
	void addSection(Block* section);
	void initRegexList();
	bool compileFile(string fileName);
};

