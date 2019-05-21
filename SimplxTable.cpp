#include "SimplxTable.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

size_t ind_min(double* begin, size_t N) {
	size_t ind = 0;
	double min = *begin;
	for (size_t i  = 1; i < N; i++)
		if (begin[i] < min)
		{
			ind = i;
			min = begin[i];
		}

	return ind;
}

void SimplxTable::ObjFunc::parseStr(std::string line) {
	// ввод хуйни
	size_t rht, lft = 0;
	for (size_t i = 0; i < N; i++) {
		rht = line.find(' ', lft);
		koef[i] = stod(line.substr(lft, rht - lft + 1));
		lft = rht;
	}

	if (line.find("max") != -1)
		setMod(MAX);
	else
		setMod(MIN);
}

SimplxTable::SimplxTable()
{
	N = M = 0;
}

SimplxTable::SimplxTable(const SimplxTable& obj_)
	: N(obj_.N), M(obj_.M), m_matrx(new double*[N]),
	 m_limits(new double[N]), m_delta(new double[N])
{
	m_objFunc = new ObjFunc(*obj_.m_objFunc);
	for (size_t i = 0; i < N; i++)
		m_matrx[i] = new double[M];

	for (size_t i = 0; i < N; i++)
	{
		m_limits[i] = obj_.m_limits[i];
		m_delta[i] = obj_.m_delta[i];
		for (size_t j = 0; j < M; j++)
			m_matrx[i][j] = obj_.m_matrx[i][j];
	}
}

SimplxTable::SimplxTable(size_t test) {
	// TODO:
}

void SimplxTable::setupFile(const char* fname) {
	ifstream in(fname);
	if (!in.is_open())
		throw "File didn't open!";

	cout << "Setuping...\n";

	if (!(N * M)) clear();

	in >> M;
	if (M <= 0) throw "Argument must be > 0";

	string line; getline(in, line);

	m_objFunc = new ObjFunc(M);
	m_objFunc->parseStr(line);		// инициализировали вектор

	in >> N;
	if (N <= 0) throw "Argument must be > 0";

	m_limits = new double[N];
	m_delta = new double[N];

	m_matrx = new double*[N];
	for (size_t i = 0; i < N; i++)
		m_matrx[i] = new double[M];

	for (size_t i = 0; i < N; i++) {
		getline(in, line);
		parseLimit(line, i);
	}

	cout << "Setup was finished...\n";
	
/*
3
(10, 14, 12) max
3
1[4] + 2[2] + 3[1] < 180
1[3] + 2[1] + 3[3] < 210
1[1] + 2[2] + 3[5] < 244*/

	in.close();
}


void SimplxTable::print() const {
	
}


SimplxTable::~SimplxTable()
{
	clear();
}

void SimplxTable::setStrings() {
	m_bp = new string[M];
	m_fp = new string[N];

	for (size_t i = 0; i < N; i++)
		m_fp[i] = ("x" + to_string(i + 1));

	for (size_t i = 0; i < M; i++)
		m_bp[i] = ("x" + to_string(N + i + 1));
}

void SimplxTable::clear() {
	for (size_t i = 0; i < N; i++)
		delete[] m_matrx[i];

	delete[] m_matrx;
	delete[] m_limits;
	delete	 m_objFunc;
	delete[] m_delta;
	delete[] m_bp;
	delete[] m_fp;
	N = M = 0;
}

void SimplxTable::parseLimit(string line, size_t ind) {
	
}

SimplxTable::ObjFunc simplx_method(SimplxTable table) {
	while (!table.m_objFunc->isFinished()) {

		size_t ind_row = table.m_objFunc->indObjRow();
		size_t count = table.M;

		// заполняем дельта, деля значение limit на элементы
		// разрешающего столбца
		for (size_t i = 0; i < count; i++)
			table.m_delta[i] = table.m_limits[i] / table.m_matrx[i][ind_row];

		size_t ind_line = ind_min(table.m_delta, count);
		double obj_elem = table.m_matrx[ind_line][ind_row];	// разрешающий элемент


		for (size_t i = 0; i < table.N; i++)
			if (i != )
	}
}

