#include<Python.h>
#include<iostream>
#include<math.h>
#include<sstream>
using namespace std;

static char module_docstring[] = "A spam module";

string bet[] = {"hundred","thousand","million","billion","trillion","Quadrillion","Quintillion","Sextillion","Septillion","Octillion",""};
string oh[] = {"ten","twenty","thirty","fourty","fifty","sixty","seventy","eighty","ninty"};
string teen[] = {"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","ninteen"};
string num_string[] = {"","one","two","three","four","five","six","seven","eight","nine"};



template <typename T>
string NumToString(T pNum) {
	ostringstream str_stream;
	str_stream << pNum;
	return str_stream.str();
}

string sayTwoDig(int *num_buffer) {
	string n_word;
	if(num_buffer[1] != 1 || num_buffer[0] == 0) {
		if(num_buffer[1] != 0 )
			n_word = oh[num_buffer[1]-1] + " ";
		if(num_buffer[0] != 0) {
			n_word.append(num_string[num_buffer[0]] + " ");
		}
	}
	
	else {
		n_word = teen[num_buffer[0]-1];
	}
	
	return n_word;
}


string sayWord(int *num_buffer,int length, int cursor) {
	string n_word;
	int bet_index = ceil(cursor/3);
	if(length == 1) {
		n_word.append(num_string[num_buffer[0]] + " ");
		if(cursor >= 2 && num_buffer[0] > 0)
			n_word.append(bet[bet_index] + " ");
	}
	if(length == 2) {
		n_word.append(sayTwoDig(num_buffer) + " ");
		if(cursor >= 2 && num_buffer[1] > 0)
			n_word.append(bet[bet_index] + " ");
	}
	if(length==3) {
		//we need to find the leading digit
		n_word.append(num_string[num_buffer[2]] + " ");
		if(num_buffer[2] != 0)
			n_word.append(bet[0] + " ");	
		n_word.append(sayTwoDig(num_buffer) + " ");
		if(cursor >= 4 && (num_buffer[0] > 0 || num_buffer[1] > 0 || num_buffer[2] > 0)) 
			n_word.append(bet[bet_index] + " ");
	}
	
	return n_word;
}

/*
inline string readNum(int iw,int *bet) {
	return bet[iw];
}

*/
void getBlock(int num, int *num_array) {
	int length,x = 0;
	length = NumToString(num).length();
	for(int i=0;i<length;i++) {
		x = num % 10;
		num_array[i] = x;
		num  = (int) floor(num/10);
	}
		
}

static PyObject *read_number(PyObject *self, PyObject *args) {
	
	int num,length;
	int *num_array, *num_buffer;
	string n_word;
	

	//parse python arguments to c types
	if(!PyArg_ParseTuple(args,"i",&num)) {
		return NULL;
	}

	length = NumToString(num).length();
	num_array = new int[length];

	getBlock(num, num_array);

	int cursor = 0;
	while(length-cursor >= 3) {
			num_buffer = new int[3];
			for(int p=0;p < 3;p++) {
					num_buffer[p] = num_array[cursor];
					cursor++;
			}
			n_word.insert(0,sayWord(num_buffer,3,cursor-1) + " ");
	}

	int blocks_left = length-cursor;
	if(blocks_left>0){
			num_buffer = new int[blocks_left];
	}

	for(int p=0;p<blocks_left;p++) {
			num_buffer[p] = num_array[cursor];
			cursor++;

	}

	if(blocks_left>0){
			n_word.insert(0,sayWord(num_buffer,blocks_left,cursor-1) + " ");
	}


	char *n_word_char = new char[255];
	strncpy(n_word_char,n_word.c_str(),255);
	PyObject *rObj = Py_BuildValue("s", n_word_char);

	delete(n_word_char);
	delete(num_array);
	delete(num_buffer);	
	return rObj;
}


struct PyMethodDef module_methods[] = {
	{"read_number", read_number,METH_VARARGS, NULL},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC inithafiz_num_reader() {
	Py_InitModule3("hafiz_num_reader",module_methods,module_docstring);
}

