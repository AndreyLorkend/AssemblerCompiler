#include "Compiler.h"
#include <iomanip>

bool Compiler::parseSourceFile()
{
	// Классификация команд
	string line;
	if (fin->is_open()) {
		while (!fin->eof()) {
			getline(*fin, line);
			handleStr(line);
			classifyCommand(line);
		}
	}
	// выводим классифицированную таблицу команд
	cout << "Command ID" << "\t" << "Instruction" << "\t" << "Instruction class\n";
	for (auto el : classifiedCommandList) {
		cout << el.first << "\t\t" << el.second.second << "\t\t" << el.second.first << endl;
	}
	// разбиение команд на части по его классу
	for (auto el : classifiedCommandList) {
		try {
			if (!splitInstruction(el)) {
				throw new CompilerException(-1, "Can't compile the line.");
			}
		}
		catch (CompilerException* exp) {
			exp->displayException();
			return false;
		}
	}
}

void Compiler::prepareSections()
{
	cout << "\n\nInstruction codes:\n";
	for (auto el : labelTable.getTable()) {
		cout << dec << el.first << "\t" << el.second.fromAddr << "\t" << el.second.toAddr << "\n";
		for (auto instr : instructionsList) {
			if (instr.first == el.second.fromAddr) {
				BYTE data = el.second.toAddr - el.second.fromAddr - 2;
				dynamic_cast<SingleOperandInstruction&>(*instr.second).setDisp(data);
			}
		}
	}
	for (auto el : instructionsList) {
		cout << dec << el.first << "\t";
		el.second->showInstructionCode();
		sections[CODE_SECTION]->addRawDataElement(el.second);
	}
	headerSection->setNumberOfSections(sectionsCount);
	addSection(headerSection);
	for (auto el : sections) {
		el.second->setVirtualSize(currentCommandSize);
		addSection(el.second);
	}
	sections[CODE_SECTION]->setPointerToRawData(sizeOfSections);
	sections[CODE_SECTION]->setSizeOfRawData(currentCommandSize);
	sections[CODE_SECTION]->setVirtualSize(0);
}

void Compiler::writeSections()
{
	for (auto el : sectionsList) {
		el->writeToFile(fout);
	}
	sections[CODE_SECTION]->writeRawData(fout);
	BYTE algn = 0x00;
	fout->write(reinterpret_cast<const char*>(&algn), sizeof(algn));
}

void Compiler::writeSymbolTable()
{
	for (auto el : symbolTableRecords) {
		el->writeToFile(fout);
	}
	DWORD32 smth = 0x0004;
	fout->write(reinterpret_cast<const char*>(&smth), sizeof(smth));
}

void Compiler::handleStr(string& str)
{
	for_each(str.begin(), str.end(), [](char& c) {
		c = tolower(c);
	});
	str = regex_replace(str, regex("(^[\\t\\s]*)|(;)([\\w\\s]*)|([\\t\\s]*$)"), "");
}

void Compiler::classifyCommand(string command)
{
	cmatch result;
	if (command != "") {
		for (auto el : patternList) {
			if (regex_match(command.c_str(), result, regex(el.second))) {
				classifiedCommandList.insert(make_pair(commandId, make_pair(el.first, command)));
			}
		}
		commandId++;
	}
}

void Compiler::prepareSymbolTable()
{
	//filename
	symbolTableRecords.push_back(new SymbolTableSection(".file", 0, IMAGE_SYM_DEBUG, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_FILE, 1, new AuxiliaryFileFormatRecord(fileNameIn_)));
	//compid
	symbolTableRecords.push_back(new SymbolTableSection("@comp.id", 0x001220FC, IMAGE_SYM_ABSOLUTE, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 0));
	//sections (e.g. sect1 - 3)
	WORD sectionNumber = 1;
	for (auto el : sections) {
		symbolTableRecords.push_back(new SymbolTableSection(el.second->getName(), 0, sectionNumber, IMAGE_SYM_TYPE_NULL, IMAGE_SYM_CLASS_STATIC, 1,
			new AuxiliarySectionFormatRecord(el.second->getSizeOfRawData(), el.second->getNumberOfRelocations(), el.second->getNumberOfLineNumber(), 0, 0, 0)));
	}
	//external function
	string name = "_";
	name.append(externalName);
	symbolTableRecords.push_back(new SymbolTableSection(name, 0, 1, 0x20, IMAGE_SYM_CLASS_EXTERNAL, 0));
	//string table?
	int numberOfSymbols = 0;
	for (auto el : symbolTableRecords) {
		numberOfSymbols++;
		numberOfSymbols += el->getNumberOfAuxSymbols();
		cout << el->getName() << "\n";
	}
	headerSection->setNumberOfSymbols(numberOfSymbols);
	headerSection->setPointerToSymbolTable(sizeOfSections + currentCommandSize);
}

bool Compiler::splitInstruction(pair<int, pair<CommandType, string>> el)
{
	//cout << "\n\n";
	switch (el.second.first)
	{
	case MACHINE_TYPE:
		return splitHeaderInstructions(el);
		break;
	case MEMORY_MODEL_TYPE:
		return splitHeaderInstructions(el);
		break;
	case SEGMENT_TYPE:
		return splitSegmentInstructions(el);
		break;
	case PROCEDURE:
		return splitDirective(el);
		break;
	case SINGLE_OPERAND_INSTRUCTION:
		return splitSingleOperandInstructions(el);
		break;
	case TWO_OPERAND_INSTRUCTION:
		return splitTwoOperandInstructions(el);
		break;
	case WITHOUT_OPERAND_INSTRUCTION:
		return splitNoOperandInstructions(el);
		break;
	case LABEL:
		return splitLabeledInstructions(el);
		break;
	default:
		return false;
		break;
	}
}

bool Compiler::splitHeaderInstructions(pair<int, pair<CommandType, string>> command)
{
	try {
		cmatch result;
//		cout << command.first << "\t";
		if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
			if (command.second.first == MACHINE_TYPE) {
				if (result[2] == "386") {
					headerSection = new HeaderSection();
					headerSection->initSection();
					headerSection->setMachine(IMAGE_FILE_MACHINE_I386);
					sizeOfSections += headerSection->getSize();
				} else {
					throw new CompilerException(-1, "Undefined machine type.");
				}
			}
			//if (command.second.first == MEMORY_MODEL_TYPE) {
			//	cout << result[4] << " " << result[6] << "\n";
			//}
			return true;
		}
	}
	catch (CompilerException* exp) {
		exp->displayException();
		return false;
	}

}

bool Compiler::splitSegmentInstructions(pair<int, pair<CommandType, string>> command)
{
	try {
		cmatch result;
		sectionsCount++;
		if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
			if (result[0] == ".code") {
				sections.insert(make_pair(CODE_SECTION, new Section(CODE_SECTION)));
				sections[CODE_SECTION]->initSection(
					".text",
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ | IMAGE_SCN_ALIGN_4BYTES | IMAGE_SCN_CNT_CODE);
				sizeOfSections += sections[CODE_SECTION]->getSize();
				return true;
			}
			if (result[0] == ".data") {
				sections.insert(make_pair(DATA_SECTION, new Section(DATA_SECTION)));
				sections[DATA_SECTION]->initSection(
					".data",
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ | IMAGE_SCN_ALIGN_4BYTES | IMAGE_SCN_CNT_INITIALIZED_DATA);
				sizeOfSections += sections[DATA_SECTION]->getSize();
				return true;
			}
			if (result[0] == ".stack") {
				sections.insert(make_pair(STACK_SECTION, new Section(STACK_SECTION)));
				sections[STACK_SECTION]->initSection(
					"STACK",
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ | IMAGE_SCN_ALIGN_4BYTES | IMAGE_SCN_CNT_INITIALIZED_DATA);
				sizeOfSections += sections[STACK_SECTION]->getSize();
				return true;
			}
			throw new CompilerException(-1, "Undefined section.");
		}
		return true;
	}
	catch (CompilerException* exp) {
		exp->displayException();
		return false;
	}
}

bool Compiler::splitSingleOperandInstructions(pair<int, pair<CommandType, string>> command)
{
	try {
		cmatch result;
		if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
			string cmd;
			cmd = result[1].str();
			handleStr(cmd);
			//cout << result[1] << " " << result[3];
			SingleOperandInstruction* instruction = NULL;
			if (instructionsTable.findElementByKey(cmd, ONE_OPERAND_TABLE)) {
				string label = result[3].str();
				handleStr(label);
				if (labelTable.findElementByKey(label)) {
					labelTable.setFromAddrByKey(label, currentCommandSize);
					instruction = instructionsTable.getSingleOperandInstructionByKey(cmd, NO_SOURCE_RECIVER)->clone();
					instructionsList.insert(make_pair(currentCommandSize, instruction));
					cout << dec << currentCommandSize << " ";
					instruction->showInstructionCode();
					currentCommandSize += instruction->getInstructionSize();
				}
				else {
					labelTable.addElement(label, currentCommandSize, 0);
					instruction = instructionsTable.getSingleOperandInstructionByKey(cmd, NO_SOURCE_RECIVER)->clone();
					instructionsList.insert(make_pair(currentCommandSize, instruction));
					cout << dec << currentCommandSize << " ";
					instruction->showInstructionCode();
					currentCommandSize += instruction->getInstructionSize();
				}
			} else {
				throw new CompilerException(-1, "Undefined one operand instruction: "+cmd);
			}
		}
		return true;
	} 
	catch (CompilerException* exp) {
		exp->displayException();
		return false;
	}
}

bool Compiler::splitTwoOperandInstructions(pair<int, pair<CommandType, string>> command)
{
	cmatch result;
	try {
		if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
			string cmd = result[1].str();
			string firstOperand = result[2];
			string secondOperand = result[4];
			handleStr(firstOperand);
			handleStr(secondOperand);
			handleStr(cmd);
			Operand* fop = NULL;
			Operand* sop = NULL;
			int firstOperandKey;
			int secondOperandKey;
			bool prefix16Flag = false;
			bool isDataFlag = false;
			int data = 0;
			int dFlag = 0;
			int sFlag = 0;
			int wFlag = 1;
			int modFlag = 0;
			TwoOperandInstruction* instruction = NULL;
			if (instructionsTable.findElementByKey(cmd, TWO_OPERAND_TABLE)) {
				// define the first operand (the first operand can be only register)
				if (registersTable.findRegisterElementByKey(firstOperand)) {
					fop = new RegisterOperand(firstOperand, registersTable.getCodeByKey(firstOperand), registersTable.getLengthByKey(firstOperand));
					firstOperandKey = REG_RECIVER;
					dFlag = 1;
					if (registersTable.getLengthByKey(firstOperand) == 8) {
						wFlag = 0;
					}
					if (registersTable.getLengthByKey(firstOperand) == 16) {
						prefix16Flag = true;
					}
				}
				else {
					throw new CompilerException(-1, "Undefined first operand: " + result[0].str());
				}
				////define the second operand (the second operand can be register/memory/data)
				if (registersTable.findRegisterElementByKey(secondOperand) && sop == NULL) {
					sop = new RegisterOperand(secondOperand, registersTable.getCodeByKey(secondOperand), registersTable.getLengthByKey(secondOperand));
					secondOperandKey = REG_SOURCE;
					if (registersTable.getLengthByKey(secondOperand) == 16) {
						prefix16Flag = true;
					}
				}
				if (memoryElementsTable.findElementByKey(secondOperand) && sop == NULL) {
					sop = new MemoryOperand(secondOperand, registersTable.getCodeByKey("ebp"), memoryElementsTable.getLengthByKey(secondOperand), memoryElementsTable.getOffsetByKey(secondOperand));
					secondOperandKey = MEM_SOURCE;
					modFlag = 1;
					if (memoryElementsTable.getLengthByKey(secondOperand) == 16) {
						prefix16Flag = true;
					}
				}
				if (sop == NULL){
					int data = atoi(secondOperand.c_str());
					if (data <= 0xFF && sop == NULL) {
						sop = new DataOperand((BYTE)data);
					}
					if (data <= 0xFFFF && sop == NULL) {
						sop = new DataOperand((WORD)data);
					}
					if (data <= 0xFFFFFFFF && sop == NULL) {
						sop = new DataOperand((DWORD32)data);
					}
					modFlag = 3;
					secondOperandKey = DATA_SOURCE;
					if (wFlag == 1) {
						sFlag = 1;
					}
				}
				//define source-reciver instruction
				SourceReciver sr = SourceReciver(firstOperandKey + secondOperandKey);
				instruction = instructionsTable.getTwoOperandInstructionByKey(cmd, sr)->clone();
				if (instruction == NULL) {
					throw new CompilerException(-1, "Undefined two operand instruction: " + result[0].str());
				}
				instruction->setFlagMod(modFlag);
				instruction->setFlagS(sFlag);
				instruction->setFlagD(dFlag);
				instruction->setFlagW(wFlag);
				instruction->setPrefixFlag(prefix16Flag);
				instruction->setFirstOperand(fop);
				instruction->setSecondOperand(sop);
				instructionsList.insert(make_pair(currentCommandSize, instruction));
				cout << dec << currentCommandSize << " ";
				instruction->showInstructionCode();
				currentCommandSize += instruction->getInstructionSize();
			} else {
				throw new CompilerException(-1, "Undefined two operand instruction: " + result[0].str());
			}
		}
		return true;
	}
	catch (CompilerException* exp) {
		exp->displayException();
		return false;
	}
}

bool Compiler::splitNoOperandInstructions(pair<int, pair<CommandType, string>> command)
{
	try {
		cmatch result;
		if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
			string cmd;
			cmd = result[0].str();
			handleStr(cmd);
			NoOperandInstruction* instruction = NULL;
			if (instructionsTable.findElementByKey(cmd, NO_OPERAND_TABLE)) {
				instruction = instructionsTable.getNoOperandInstructionByKey(cmd, NO_SOURCE_RECIVER)->clone();
				instructionsList.insert(make_pair(currentCommandSize, instruction));
				cout << dec << currentCommandSize << " ";
				instruction->showInstructionCode();
				currentCommandSize += instruction->getInstructionSize();
			} else {
				throw new CompilerException(-1, "Undefined no operand instruction: " + cmd);
			}
		}
		return true;
	}
	catch (CompilerException* exp) {
		exp->displayException();
		return false;
	}
}

bool Compiler::splitLabeledInstructions(pair<int, pair<CommandType, string>> command)
{
	cmatch result;
	//cout << command.first << "\t";
	if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
		//cout << result[1] << " " << result[4] << "\n";
		if (result[4].str() != "") {
			cmatch commandRes;
			if (result[4].str() != "") {
				for (auto el : patternList) {
					if (regex_match(result[4].str().c_str(), commandRes, regex(el.second))) {
						if (!labelTable.findElementByKey(result[1].str())) {
							labelTable.addElement(result[1].str(), 0, currentCommandSize);
							splitInstruction(make_pair(command.first, make_pair(el.first, result[4].str())));
						} else {
							if (labelTable.getToAddrByKey(result[1].str()) == 0) {
								labelTable.setToAddrByKey(result[1].str(), currentCommandSize);
							}
						}
					}
				}
			}
		} else {
			if (!labelTable.findElementByKey(result[1].str())) {
				labelTable.addElement(result[1].str(), 0, currentCommandSize);
			} else {
				if (labelTable.getToAddrByKey(result[1].str()) == 0) {
					labelTable.setToAddrByKey(result[1].str(), currentCommandSize);
				}
			}
		}
	}
	return true;
}

bool Compiler::splitDirective(pair<int, pair<CommandType, string>> command)
{
	cmatch result;
	//cout << command.first << "\t";
	if (regex_search(command.second.second.c_str(), result, regex(patternList[command.second.first]))) {
		if (result[0] == "end") {
		//	cout << result[0] << "\n";
		} else {
		//	cout << result[1] << " " << result[2] << " " << result[3] << "\n";
		}
		if (result[2] == "proc") {
			externalName = result[1].str();
			handleStr(externalName);
			Operand* fop = NULL;
			Operand* sop = NULL;
			string elements = result[3].str();
			addMemoryElements(elements);
			SingleOperandInstruction* soi = instructionsTable.getSingleOperandInstructionByKey("push", NO_SOURCE_RECIVER)->clone();
			TwoOperandInstruction* toi = instructionsTable.getTwoOperandInstructionByKey("mov", REG_REG)->clone();
			fop = new RegisterOperand("ebp", registersTable.getCodeByKey("ebp"), registersTable.getLengthByKey("ebp"));
			sop = new RegisterOperand("esp", registersTable.getCodeByKey("esp"), registersTable.getLengthByKey("esp"));
			soi->setOperand(fop);
			toi->setFirstOperand(fop);
			toi->setSecondOperand(sop);
			toi->setFlagD(1);
			toi->setFlagW(1);
			instructionsList.insert(make_pair(currentCommandSize, soi));
			currentCommandSize += soi->getInstructionSize();
			instructionsList.insert(make_pair(currentCommandSize, toi));
			currentCommandSize += toi->getInstructionSize();
		}
	}
	return true;
}

void Compiler::addMemoryElements(string elements)
{
	cmatch result;
	regex pattern = regex("([\\s]*)([\\w]+)([\\s]*)(:)([\\s]*)([\\w]+)([\\s]*)");
	regex patternForSubStr = regex("([\\s]*)([\\w]+)(:)([\\w\\s]+)");
	sregex_iterator beg{ elements.cbegin(), elements.cend(), pattern };
	sregex_iterator end{};
	BYTE offset = 8;
	for (auto el = beg; el != end; el++) {
		if (regex_match(el->str().c_str(), result, patternForSubStr)) {
			size_t pos = result[4].str().find("dword");
			if (pos != string::npos) {
				memoryElementsTable.addElement(result[2].str(), offset, 32);
			}
			pos = result[4].str().find("word");
			if (pos != string::npos) {
				memoryElementsTable.addElement(result[2].str(), offset, 16);
			}
			pos = result[4].str().find("byte");
			if (pos != string::npos) {
				memoryElementsTable.addElement(result[2].str(), offset, 8);
			}
		}
		else {
			cout << "not found!\n";
		}
		offset += 4;
	}
}

Compiler::Compiler()
{
	commandId = 0;
	currentCommandSize = 0;
	initRegexList();
	fin = NULL;
	fout = NULL;
}

Compiler::~Compiler()
{
	if (fout != NULL) {
		fout->close();
		delete fout;
	}

	if (fin != NULL) {
		fin->close();
		delete fin;
	}
}

void Compiler::addSection(Block* section)
{
	sectionsList.push_back(section);
}

void Compiler::initRegexList()
{
	patternList.insert(make_pair(MACHINE_TYPE, "(\\.)([0-9]{1,})([a-z]*)"));
	patternList.insert(make_pair(MEMORY_MODEL_TYPE, "(\\.)(model)([\\s]{1,})([\\w\\s]{1,})(,)([\\w\\s]{1,})"));
	patternList.insert(make_pair(SEGMENT_TYPE, "(\\.)([a-z]{1,})"));
	patternList.insert(make_pair(PROCEDURE, "([\\w\\s]{1,})(endp|proc)([\\w\\s:,]*)|(end)"));
	patternList.insert(make_pair(SINGLE_OPERAND_INSTRUCTION, "([a-z]{1,})([\\s]{1,})([\\w\\s]{1,})"));
	patternList.insert(make_pair(TWO_OPERAND_INSTRUCTION, "([a-z]{1,})([\\w\\s]{1,})(,)([\\w\\s]{1,})"));
	patternList.insert(make_pair(WITHOUT_OPERAND_INSTRUCTION, "([a-z]{1,})"));
	patternList.insert(make_pair(LABEL, "([\\w@]{1,})(:)([\\s]*)([\\w\\s,]*)"));
}

bool Compiler::compileFile(string fileName)
{
	fileNameIn_ = fileName;
	if (fileNameIn_ != "") {
		fin = new ifstream(fileNameIn_);
		if (fin->is_open()) {
			if (!parseSourceFile()) {
				return false;
			}
			prepareSections();
			prepareSymbolTable();
			fileNameOut_ = externalName + ".obj";
			fout = new ofstream(fileNameOut_, ios::binary);
			if (fout->is_open()) {
				writeSections();
				writeSymbolTable();
			} else {
				return false;
			}
			return true;
		}
		else {
			return false;
		}
	}
}
