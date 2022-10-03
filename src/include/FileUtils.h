#include <iostream>
#include <fstream> // lib de file stream
#include <sstream> // lib de string stream

using namespace std;

string readFile(string filename, string fileExt)
{
  ifstream inFile;
  string line, value, fileContent = "";

  inFile.open(filename + fileExt, ios::in);

  if (!inFile.is_open())
  {
    cout << "Error opening file: " << filename << fileExt << endl;
    return;
  }

  while (!inFile.eof())
  {
    getline(inFile, line);
    istringstream iss(line); // separa os valores da linha
                             // lida com os valores:
    while (iss >> value)
    {
      fileContent += value;
    }
  }

  inFile.close();

  return fileContent;
}

void writeFile(string filename, string content, string fileExt)
{
  ofstream outFile;

  outFile.open(filename + fileExt, ios::out);

  if (!outFile.is_open())
  {
    cout << "Error opening file: " << filename << fileExt << endl;
    return;
  }

  if (fileExt.compare(".dot") == 0)
  {
    formatDotFile(content);
  }

  outFile.write(content.c_str(), content.length());

  outFile.close();
}

string formatDotFile(string content)
{}