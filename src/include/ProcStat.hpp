#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>

using namespace std;
namespace fs = boost::filesystem;

class ProcStat
{
private:
	string procPath = "/proc";

	vector<string> getProcDirs()
	{
		vector<string> ret;
		fs::directory_iterator endIter;
		for (fs::directory_iterator directory(procPath); directory != endIter; ++directory)
		{
			bool isDir = fs::is_directory(directory->status());
			bool isNumericName = directory->path().filename().c_str()[0] > '0' && directory->path().filename().c_str()[0] < '9';
			if (isDir && isNumericName)
			{
				ret.push_back(directory->path().string());
			}
		}
		return ret;
	}

	string readProcStat(string path)
	{
		string ret;
		ifstream file(path + "/stat");
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				ret += line;
			}
			file.close();
			return ret;
		}
		cerr << "Unable to open file" << endl;
		return "";
	}

public:
	ProcStat(){};

	string get()
	{
		string ret;
		for (string path : getProcDirs())
		{
			ret += (readProcStat(path) + '\n');
		}
		return ret;
	}
};