#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class detector
{
private:
	vector<string> picture;
	vector<int> counts;
	int firstLine = 0;
	int lastLine = 0;
	bool unknownFigure = 0;
	bool trySqrt();
	bool tryCircul();
public:
	detector(vector<string> picture) :picture(picture)
	{
		counts.resize(15);
		for (int i = 0; i < this->counts.size(); ++i)
		{
			counts[i] = std::count(picture[i].begin(), picture[i].end(), '1');
		}
		for (int i = 0; i < counts.size(); ++i)
		{
			if (counts[i] != 0)
			{
				firstLine = i;
				break;
			}
		}
		for (int i = counts.size() - 1; i >= 0; --i)
		{
			if (counts[i] != 0)
			{
				lastLine = i;
				break;
			}
		}
		for (int i = firstLine; i <= lastLine; ++i)
		{
			if (counts[i] == 0)
			{
				unknownFigure = 1;
				break;
			}
		}
		for (int i = firstLine; i <= lastLine; ++i)
		{
			int firstOne = 0;
			int lastOne = 0;
			for (int j = 0; j < 15; ++j)
				if (picture[i][j] == '1')
				{
					firstOne = j;
					break;
				}
			for (int j = 14; j >= 0; --j)
				if (picture[i][j] == '1')
				{
					lastOne = j;
					break;
				}
			for (int j = firstOne; j <= lastOne; ++j)
				if (picture[i][j] == '0')
				{
					unknownFigure = 1;
					break;
				}
		}
	}
	void tryDetect();
};

void detector::tryDetect()
{
	if (trySqrt() && !unknownFigure)
		return;
	else if (tryCircul() && !unknownFigure)
		return;
	else
		cout << "неизвестная фигура\n";
}

bool detector::trySqrt()
{
	bool isSqrt = 1;
	for (int i = firstLine; i < lastLine; ++i)
	{
		if (picture[i] == picture[i + 1])
			continue;
		else
		{
			isSqrt = 0;
			break;
		}
	}
	int lnegthOfSqrt = *std::max_element(counts.begin(), counts.end());
	if (lastLine - firstLine + 1 != lnegthOfSqrt)
		isSqrt = 0;
	if (isSqrt)
	{
		int X = std::find(picture[firstLine].begin(), picture[firstLine].end(), '1') - picture[firstLine].begin();
		int Y = 14 - firstLine;
		cout << "квадрат\n";
		cout << "координата угла: (" << X << ", " << Y << ")\n";
		cout << "длина стороны: "<< lnegthOfSqrt;
	}
	return isSqrt;
}

bool detector::tryCircul()
{
	bool isCircul = 1;
	for (int i = firstLine, k = 0; i <= (firstLine + lastLine) / 2 - 1; ++i, ++k)
	{
		if (picture[i] == picture[lastLine - k] && counts[i + 1] - counts[i] < 4 && counts[i + 1] - counts[i] >= 1)
		{
			continue;
		}
		else
		{
			isCircul = 0;
			break;
		}
	}
	if (isCircul)
	{
		int Y = 14 - (firstLine + lastLine) / 2;
		int X = (lastLine - firstLine) / 2 + (std::find(picture[14-Y].begin(), picture[14-Y].end(), '1') - picture[14-Y].begin());
		cout << "круг\n";
		cout << "диаметр: " << *std::max_element(counts.begin(), counts.end())<< endl;
		cout << "координаты центра: (" << X << ", " << Y << ")\n";
	}
	return isCircul;
}

int main(int argc, char **argv)
{
	setlocale(0, "RU");
	std::ifstream fin(argv[1]);
	if (!fin)
	{
		cout << "fail\n";
		exit(1);
	}
	vector<string> picture(15);
	for (auto &el : picture)
		fin >> el;
	detector obj(picture);
	obj.tryDetect();
	return 0;
}
