#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

template<typename T>
bool CompareLess(T P1, T P2)
{
	if (P1 < P2) return true;
	return false;
}

template<typename T>
bool CompareMore(T P1, T P2)
{
	if (P1 > P2) return true;
	return false;
}


template <typename Ty1, typename Ty2, class Fun>
Ty2 sort(Ty2 x, Fun comparison)
{
	int i, j;
	for (i = 0, j = 0; i < x.size(); i++)
	{
		Ty1 Key = x[i];
		j = i - 1;
		while (j >= 0 && comparison(x[j], Key))
		{
			swap(x[j], x[j + 1]);
			j--;
		}
		x[j + 1] = Key;
	}
	return x;
}

template <typename T>
class Data
{
public:
	Data(string InputFileName);
	vector<T> get_KidData();
	void set_KidData(vector<T> & P1);
	void out(string OutputFileName);
private:
	vector<T> KitData;
	void input(string & InputFileName);
};

template <typename T>
Data<T>::Data(string InputFileName)
{
	input(InputFileName);
}

template<typename T>
void Data<T>::input(string & InputFileName)
{
	ifstream InputFile(InputFileName);
	if (InputFile.is_open())
	{
		T a;
		while (InputFile >> a)
		{
			KitData.push_back(a);
		}
	}
	else throw "Error opening file";
}

template<typename T>
vector<T> Data<T>::get_KidData()
{
	return this->KitData;
}

template<typename T>
void Data<T>::set_KidData(vector<T> & P1)
{
	this->KitData = P1;
}

template<typename T>
void Data<T>::out(string OutputFileName)
{
	ofstream OutFile(OutputFileName);
	if(OutFile.is_open())
	for (size_t i = 0; i < KitData.size(); i++)
	{
		OutFile << KitData[i] << endl;
	}
	else throw "Error opening file";
}

int main(int argc, char **argv)
{
	try
	{
		if (argc != 5)throw "Input parametr error";
		switch (argv[3][1])
		{
		case 'i':
		{
			Data<int> a(argv[1]);
			switch (argv[4][1])
			{
			case 'a':
				a.set_KidData(sort<int>(a.get_KidData(), &CompareMore<int>));
				break;
			case 'd':
				a.set_KidData(sort<int>(a.get_KidData(), &CompareLess<int>));
				break;
			default:
				throw "Error compare type parametr";
				break;
			}
			a.out(argv[2]);
			break;
		}
		case 's':
		{
			Data<string> a(argv[1]);
			switch (argv[4][1])
			{
			case 'a':
				a.set_KidData(sort<string>(a.get_KidData(), &CompareMore<string>));
				break;
			case 'd':
				a.set_KidData(sort<string>(a.get_KidData(), &CompareLess<string>));
				break;
			default:
				throw "Error compare type parametr";
				break;
			}
			a.out(argv[2]);
			break;
		}
		default:
			throw "Error data type parametr";
			break;
		}
		return 0;
	}
	catch (char e[])
	{
		cout << e << endl;
	}
	return 0;
}