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

void swap(string& a, string& b) {
	string c = a;
	a = b;
	b = c;
}

SimplxTable::ObjFunc::ObjFunc(const ObjFunc& obj_) 
	: N(obj_.N), koef(new double[N]), result(obj_.result),
		mod_func(obj_.mod_func), mod(obj_.mod)
{
	for (size_t i = 0; i < N; i++)
		koef[i] = obj_.koef[i];
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
	 m_limits(new double[N]), m_delta(new double[N]), m_bp(new string[M]),
	m_fp(new string[N])
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
	for (size_t i = 0; i < N; i++)
		m_fp[i] = obj_.m_fp[i];

	for (size_t i = 0; i < M; i++)
		m_bp[i] = obj_.m_bp[i];
}

SimplxTable::SimplxTable(size_t test)
	: N(3), M(3), m_matrx(new double*[M]),
	m_limits(new double[N]), m_delta(new double[N]),
	m_objFunc(new ObjFunc(3))
{

	m_bp = new string[M];
	m_fp = new string[N];

	for (size_t i = 0; i < M; i++)
		m_matrx[i] = new double[N];

	for (size_t i = 0; i < N; i++)
	{
		m_limits[i] = m_limits[i];
		m_delta[i] = m_delta[i];
		for (size_t j = 0; j < M; j++)
			m_matrx[i][j] = m_matrx[i][j];
	}

	m_limits[0] = 180;
	m_limits[1] = 210;
	m_limits[2] = 244;
	

	m_matrx[0][0] = 4;
	m_matrx[0][1] = 2;
	m_matrx[0][2] = 1;

	m_matrx[1][0] = 3;
	m_matrx[1][1] = 1;
	m_matrx[1][2] = 3;

	m_matrx[2][0] = 1;
	m_matrx[2][1] = 2;
	m_matrx[2][2] = 5;

	
	(*m_objFunc)[0] = -10;
	(*m_objFunc)[1] = -14;
	(*m_objFunc)[2] = -12;

	(*m_objFunc).setMod(MAX);

	setStrings();
	
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
	cout <<"BP\t" <<"1\t";
	for (size_t i = 0; i < N; i++)
		cout << m_fp[i] << '\t';
	cout << "delta\n";

	for(size_t i = 0; i < M; i++)
	{
		cout << m_bp[i] << '\t';
		cout << m_limits[i] << '\t';
		for (size_t j = 0; j < N; j++)
			cout << m_matrx[i][j] << '\t';
		cout << m_delta[i] << endl;
	}

	cout << m_objFunc->getResult() << '\t';
	for (size_t i = 0; i < N; i++)
		cout << (*m_objFunc)[i] << '\t';
	cout << endl;
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

void SimplxTable::madMax(pair<size_t, size_t> ind) {
	

	//auto ind = initDelta();
	double obj_elem = m_matrx[ind.first][ind.second];	// разрешающий элемент

	m_matrx[ind.first][ind.second] = 1.0 / obj_elem;
	m_limits[ind.first] /= obj_elem;


	for (size_t i = 0; i < N; i++)
		if (i != ind.second)
			m_matrx[ind.first][i] /= obj_elem;

	(*m_objFunc)[ind.second] /= -obj_elem;
	for (size_t i = 0; i < M; i++)
		if (i != ind.first)
			m_matrx[i][ind.second] /= -obj_elem;

	//return {ind.first, ind.second};
}

std::pair<size_t, size_t> SimplxTable::initDelta() {
	size_t ind_row = m_objFunc->indObjRow();
	size_t count = M;

	// заполняем дельта, деля значение limit на элементы
	// разрешающего столбца
	for (size_t i = 0; i < count; i++)
		m_delta[i] = m_limits[i] / m_matrx[i][ind_row];

	size_t ind_line = ind_min(m_delta, count);
	return { ind_line, ind_row };
}


void SimplxTable::kizaroo2(size_t indL, size_t indR) {
	swap<string>(m_bp[indL], m_fp[indR]);
	//swap(m_bp[indL], m_fp[indR]);

	double obj_elem = m_matrx[indL][indR];
	double obj_lim_el = m_limits[indL];

	double obj_row_el;
	for (size_t i = 0; i < M; i++)
		if (i != indL)
		{
			obj_row_el = m_matrx[i][indR];

			m_limits[i] = m_limits[i] - obj_lim_el * obj_row_el / obj_elem;
		}
	
	double rez = m_objFunc->getResult();
	m_objFunc->setResult(rez - obj_lim_el * (*m_objFunc)[indR] / obj_elem);

	for (size_t i = 0; i < N; i++)
	{
		obj_row_el = m_matrx[indL][i];
		if (i != indR) {
			for (size_t j = 0; j < M; j++)
				if (j != indL)
					m_matrx[j][i] -= obj_row_el * m_matrx[j][indR] / obj_elem;

			(*m_objFunc)[i] -= obj_row_el * (*m_objFunc)[indR] / obj_elem;
		}
	}
	
}

SimplxTable::ObjFunc simplx_method(SimplxTable table) {
	while (!table.m_objFunc->isFinished()) {
		
		auto ind = table.initDelta();
		double* objRow = new double[table.M + 1];

		for (size_t i = 0; i < table.M; i++)
			objRow[i] = table.m_matrx[i][ind.second];
		objRow[table.M] = (*table.m_objFunc)[ind.second];

		double* objLine = new double[table.N + 1];
		objLine[0] = table.m_limits[ind.first];
		for (size_t i = 0; i < table.N; i++)
			objLine[i + 1] = table.m_matrx[ind.first][i];
		
		table.kizaroo2(ind.first, ind.second);
		table.madMax(ind);
		table.print();

		cout << endl;
		// правило прямоугольника

	}
	return *table.m_objFunc;
}

