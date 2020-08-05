#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "process.h"
using namespace std;

//Check the validation of main parameters.
int checkValid(int argc, char* argv[], string& input, string& output, int& type) {
	if (argc < 4 || argc > 5) {
		cout << "Please input valid parameter!" << endl;
		return -1;
	}
	string _input(argv[1]), _output(argv[2]);
	if (_input.find(".txt", _input.size() - 4) == string::npos) {
		cout << "Please input valid input textfile!" << endl;
		return -1;
	}
	if (_output.find(".txt", _output.size() - 4) == string::npos) {
		cout << "Please input valid ouput textfile!" << endl;
		return -1;
	}
	int _type = stoi(string(argv[3]));
	if (_type < 1 || _type > 2) {
		cout << "Please input valid type!" << endl;
		return -1;
	}
	input = _input;
	output = _output;
	type = _type;
	return 0;
}


//Open input and output file for processing.
//Check that input file is valid.
int openFile(string input, string output, ifstream& inputFile, ofstream& outputFile) {
	inputFile.open(input, ios::in);
	outputFile.open(output, ios::trunc);
	if (!inputFile.is_open()) {
		cout << "Please input valid input textfile!";
		return -1;
	}
}

//Split string by token " " (blank space).
void stringTok(string line, string elements[], int& count) {
	int i = 0;
	count = 0;
	for (i = 0; i < line.size(); i++) {
		if (line[i] != ' ') {
			elements[count] += line[i];
		}
		else {
			count++;
		}
	}
	count++;
}
void processInt(ifstream& inputFile, ofstream& outputFile) {
	string line, result;
	string elements[4];
	int elementCount = 0;
	int c = 0;
	while (1) {
		c++;
		if (inputFile.eof()) return;
		//Get line of inputFile.
		getline(inputFile, line);
		//If cant read line or end of file.
		
		//Split string
		stringTok(line, elements, elementCount);
		//If there are too many or not enough elements.
		if (elementCount < 3 || elementCount > 4) continue;
		if (elementCount == 3) {
			if (elements[1] == "~") {
				int inp_type = 0;
				if (elements[0] == "2") inp_type = 0;
				else if (elements[0] == "10") inp_type = 1;
				else if (elements[0] == "16") inp_type = 2;
				result = process_IntUnaryOp(elements[2], 18, inp_type);
			}
			if (elements[0] == "2") {
				//Bin to Dec case.
				if (elements[1] == "10")
					result = process_IntUnaryOp(elements[2], 1, 0);
				//Bin to Hex case.
				else if (elements[1] == "16")
					result = process_IntUnaryOp(elements[2], 2, 0);
			}
			else if (elements[0] == "10") {
				//Dec to Bin case.
				if (elements[1] == "2")
					result = process_IntUnaryOp(elements[2], 0, 1);
				//Dec to Hex case.
				else if(elements[1] == "16")
					result = process_IntUnaryOp(elements[2], 3, 1);
			}
			else if (elements[0] == "16") {
				//Hex to Bin case.
				if (elements[1] == "2")
					result = process_IntUnaryOp(elements[2], 21, 1);
				//Hex to Dec case.
				else if (elements[1] == "10")
					result = process_IntUnaryOp(elements[2], 22, 1);
			}

		}
		else if (elementCount == 4) {
			int inp_type = 0;
			if (elements[0] == "2") inp_type = 0;
			else if (elements[0] == "10") inp_type = 1;
			else if (elements[0] == "16") inp_type = 2;
			if(elements[2] == "+"){
				result = process_IntBinaryOp(elements[1], elements[3], 4, inp_type);
			}
			else if (elements[2] == "-") {
				result = process_IntBinaryOp(elements[1], elements[3], 5, inp_type);
			}
			else if (elements[2] == "*") {
				result = process_IntBinaryOp(elements[1], elements[3], 6, inp_type);
			}
			else if (elements[2] == "/") {
				result = process_IntBinaryOp(elements[1], elements[3], 7, inp_type);
			}
			else if (elements[2] == "<") {
				result = process_IntBinaryOp(elements[1], elements[3], 8, inp_type);
			}
			else if (elements[2] == "<=") {
				result = process_IntBinaryOp(elements[1], elements[3], 9, inp_type);
			}
			else if (elements[2] == ">") {
				result = process_IntBinaryOp(elements[1], elements[3], 10, inp_type);
			}
			else if (elements[2] == ">=") {
				result = process_IntBinaryOp(elements[1], elements[3], 11, inp_type);
			}
			else if (elements[2] == "=") {
				result = process_IntBinaryOp(elements[1], elements[3], 12, inp_type);
			}
			else if (elements[2] == ">>") {
				result = process_IntBinaryOp(elements[1], elements[3], 13, inp_type);
			}
			else if (elements[2] == "<<") {
				result = process_IntBinaryOp(elements[1], elements[3], 14, inp_type);
			}
			else if (elements[2] == "&") {
				result = process_IntBinaryOp(elements[1], elements[3], 15, inp_type);
			}
			else if (elements[2] == "|") {
				result = process_IntBinaryOp(elements[1], elements[3], 16, inp_type);
			}
			else if (elements[2] == "^") {
				result = process_IntBinaryOp(elements[1], elements[3], 17, inp_type);
			}
			else if (elements[2] == "rol") {
				result = process_IntBinaryOp(elements[1], elements[3], 19, inp_type);
			}
			else if (elements[2] == "ror") {
				result = process_IntBinaryOp(elements[1], elements[3], 20, inp_type);
			}
			
		}
		outputFile << result << endl;
		result.clear();
		for (int i = 0; i < 4; i++) elements[i].clear();
	}
}

void processFlo(ifstream& inputFile, ofstream& outputFile) {
	string line, result;
	string elements[4];
	int elementCount = 0;
	while (1) {

		if (inputFile.eof()) return;
		//Get line of inputFile.
		getline(inputFile, line);
		//Split string
		stringTok(line, elements, elementCount);
		//If there are too many or not enough elements.
		if (elementCount < 3 || elementCount > 4) continue;
		if (elementCount == 3) {
			if (elements[0] == "2") {
				//Bin to Dec case.
				if (elements[1] == "10")
					result = process_FloUnaryOp(elements[2], 1);
			}
			else if (elements[0] == "10") {
				//Dec to Bin case.
				if (elements[1] == "2")
					result = process_FloUnaryOp(elements[2], 0);
			}
		}
		else if (elementCount == 4) {
			int inp_type = 0;
			if (elements[0] == "2") inp_type = 0;
			else if (elements[0] == "10") inp_type = 1;
			if (elements[2] == "+") {
				result = process_FloBinaryOp(elements[1], elements[3], 2, inp_type);
			}
			else if (elements[2] == "-") {
				result = process_FloBinaryOp(elements[1], elements[3], 3, inp_type);
			}
			else if (elements[2] == "*") {
				result = process_FloBinaryOp(elements[1], elements[3], 4, inp_type);
			}
			else if (elements[2] == "/") {
				result = process_FloBinaryOp(elements[1], elements[3], 5, inp_type);
			}

		}
		outputFile << result << endl;
		result.clear();
		for (int i = 0; i < 4; i++) elements[i].clear();
	}
}

int main(int argc, char* argv[]) {
	string input, output;
	int type = 0;
	ifstream inputFile;
	ofstream outputFile;
	if (checkValid(argc, argv, input, output, type) == -1) return -1;
	if (openFile(input, output, inputFile, outputFile) == -1) return -1;
	if (type == 1) processInt(inputFile, outputFile);
	else processFlo(inputFile, outputFile);
	inputFile.close();
	outputFile.close();
	return 1;
}