#pragma once
#include <algorithm>
#include <functional>
/*������ ����� ������:
 * 1) ���.-�� ���������� � F
 * 2) f1 f2 ... fn min\max
 * 3) ���.-�� ����������� - N
 * 4) N ����� �����:
 *		
 *		A[Ka] + B[Kb] + ... + Z[Kz] ������ ������ ���������
 *
 *		//A, B, ... , Z - ������ �����
 *		//Ka, Kb, ..., Kz - ����. ����� ������
 *		
 */
enum Mod {MIN, MAX};
size_t ind_min(double*, size_t);
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
		
		bool isFinished() const {
			return std::all_of(koef, koef + N, [](double x) {return x >= 0; });
		}
		size_t indObjRow() const	// ������ ������. �������
		{
			// min: ����������� <0
			// max: ���� >0
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
		void setMod(Mod mod_) {
			if (mod == MAX)
				mod_func = [](double x, double y) {return x > y; };
			else
				mod_func = [](double x, double y) {return x < y; };
		}
		friend std::ostream& operator << (std::ostream& out, ObjFunc obj_) {
			// TODO:

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
	void print() const;	// TODO:
	friend ObjFunc simplx_method(SimplxTable table); // TODO: ����� ������� �� ���������
	~SimplxTable();
private:
	void setStrings();	// ����. bp, fp
	void clear();
	void parseLimit(std::string line, size_t ind);	// TODO: ��������� ������� � ������ ���� �� ���� �� ������
	void madMax();
private:
	size_t N;	// ���.-�� ��������� ����������
	size_t M;	// ���.-�� ��������\�����������

	double**	m_matrx;	// ������� ����.[NxM]
	double*		m_limits;	// �����������[N]

	ObjFunc*	m_objFunc;	// ����. ������� �.-��[M + 1]
	double*		m_delta;	// ����� �����-��[N]
	// �������������� ��� 
	std::string* m_bp;		// ���. �����.[M]
	std::string* m_fp;		// ����. �����.[N]
};

