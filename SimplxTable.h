#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
/*ФОРМАТ ВВОДА ДАННЫХ:
 * 1) кол.-во переменных в F
 * 2) f1 f2 ... fn min\max
 * 3) кол.-во ограничений - N
 * 4) N строк ввида:
 *		
 *		A[Ka] + B[Kb] + ... + Z[Kz] первый символ отношения
 *
 *		//A, B, ... , Z - номера иксов
 *		//Ka, Kb, ..., Kz - коэф. перед иксами
 *		
 */
enum Mod {MIN, MAX};
size_t ind_min(double*, size_t);
void swap(std::string&, std::string&);
class SimplxTable
{
	class ObjFunc
	{
	public:
		ObjFunc(size_t n = 0)
			: N(n), koef(new double[n])
		{
			for (size_t i = 0; i < N; i++)
				koef[i] = 0;

			result = 0;
		}
		ObjFunc(const ObjFunc& obj_);	// TODO:
		~ObjFunc() { delete[] koef; N = result = 0; }

		void parseStr(std::string line);
		double& operator [](const size_t i) { return koef[i]; }
		const double& operator [](const size_t i) const  { return koef[i]; }
		
		bool isFinished() const {
			return std::all_of(koef, koef + N, [](double x) {return x >= 0; });
		}
		size_t indObjRow() const	// индекс разреш. столбца
		{
			// min: минимальный <0
			// max: макс >0
			int ind = -1;
			double cmprtr = 0.0;

			for (size_t i = 0; i < N; i++)
				if (mod_func(koef[i], cmprtr))
				{
					cmprtr = koef[i]; ind = i;
				}
				
			return ind;
		}

		double getResult() const { return result; }
		void setResult(double d) { result = d; }
		void setMod(Mod mod_) {
			if (mod == MAX)
				mod_func = [](double x, double y) {return x > y; };
			else
				mod_func = [](double x, double y) {return x < y; };
		}


		friend std::ostream& operator << (std::ostream& out, ObjFunc obj_) {
			// TODO:
			for (size_t i = 0; i < obj_.N; i++)
				out <<"\t[" << i+1 << "]:\t" << obj_.koef[i] << '\n';
			out << "\tF(";
			for (size_t i = 0; i < obj_.N; i++)
				out << "x_" << i + 1 << ' ';
			out << ") = " << obj_.result << std::endl;
			return out;
		}
	private:
		size_t	N;
		double* koef;
		double	result;
		std::function<bool(double, double)> mod_func;
		Mod mod;
	};

public:
	SimplxTable();
	SimplxTable(const SimplxTable& obj_);
	SimplxTable(size_t test);

	void setupFile(const char* fname);
	void print() const;
	friend ObjFunc simplx_method(SimplxTable table);
	~SimplxTable();
private:
	void setStrings();	// иниц. bp, fp
	void clear();
	void parseLimit(std::string line, size_t ind);	// TODO: заполнить матрицу и другие поля по инфе из строки
	void madMax(std::pair<size_t, size_t>);
	std::pair<size_t, size_t> initDelta();
	void kizaroo2(size_t indL, size_t indR);
private:
	size_t N;	// кол.-во свободных переменных
	size_t M;	// кол.-во базисных\ограничений

	double**	m_matrx;	// матрица коэф.[NxM]
	double*		m_limits;	// ограничения[N]

	ObjFunc*	m_objFunc;	// коэф. целевой ф.-ии[M + 1]
	double*		m_delta;	// хуйня какая-то[N]
	// идентификаторы для 
	std::string* m_bp;		// баз. перем.[M]
	std::string* m_fp;		// своб. перем.[N]
};

