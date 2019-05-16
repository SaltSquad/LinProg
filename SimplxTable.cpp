#include "SimplxTable.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

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


void SimplxTable::print() {
	
}


SimplxTable::~SimplxTable()
{
	clear();
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
	SimplxTable::ObjFunc a;
	return a;
}

