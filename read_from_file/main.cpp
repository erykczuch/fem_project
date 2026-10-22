#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Node
{
    double x, y;
};

struct Element
{
    int ID[4];
};

struct Grid
{
    int nN;
    int nE;
    vector<Element> elements;
    vector<Node> nodes;
};

struct GlobalData
{
    int SimulationTime;
    int SimulationStepTime;
    int Conductivity;
    int Alfa;
    int Tot;
    int InitialTemp;
    int Density;
    int SpecificHeat;
    int nN;
    int nE;
};

int main()
{
	GlobalData gd;
    Grid grid;
    ifstream file("Test1_4_4.txt");
    string line;

    if (!file.is_open())
    {
        cout << "Could not open file!" << endl;
        return 1;
    }
    
    string word;
    while (file >> word)
    {
        if (word == "SimulationTime")
        {
            file >> word;
            gd.SimulationTime = stoi(word);
        }
        else if (word == "SimulationStepTime")
        {
            file >> word;
            gd.SimulationStepTime = stoi(word);
        }
        else if (word == "Conductivity")
        {
            file >> word;
            gd.Conductivity = stoi(word);
        }
        else if (word == "Alfa")
        {
            file >> word;
            gd.Alfa = stoi(word);
        }
        else if (word == "Tot")
        {
            file >> word;
            gd.Tot = stoi(word);
        }
        else if (word == "InitialTemp")
        {
            file >> word;
            gd.InitialTemp = stoi(word);
        }
        else if (word == "Density")
        {
            file >> word;
            gd.Density = stoi(word);
        }
        else if (word == "SpecificHeat")
        {
            file >> word;
            gd.SpecificHeat = stoi(word);
        }
        else if (word == "Nodes")
        {
            file >> word;
            if (word == "number")
            {
                file >> word;
                grid.nN = gd.nN = stoi(word);
                grid.nodes.resize(grid.nN);
            }
        }
        else if (word == "Elements")
        {
            file >> word;
            if (word == "number")
            {
                file >> word;
                grid.nE = gd.nE = stoi(word);
                grid.elements.resize(grid.nE);
            }
        }

        else if (word == "*Node")
        {
            for (int i = 0; i < grid.nN; i++)
            {
                string x_value, y_value;
                file >> word;
                file >> x_value;
                file >> y_value;

                Node node;
                node.x = stod(x_value);
                node.y = stod(y_value);

                grid.nodes[stoi(word) - 1] = node;
            }
        }

        else if (word == "*Element,")
        {
            file >> word;
            for (int i = 0; i < grid.nE; i++)
            {
                string ids[4];
                file >> word;
                file >> ids[0];
                file >> ids[1];
                file >> ids[2];
                file >> ids[3];

                Element element;
                element.ID[0] = stoi(ids[0]);
                element.ID[1] = stoi(ids[1]);
                element.ID[2] = stoi(ids[2]);
                element.ID[3] = stoi(ids[3]);

				grid.elements[stoi(word) - 1] = element;
            }
        }
    }


    cout << "SimulationTime: " << gd.SimulationTime << endl;
    cout << "SimulationStepTime: " << gd.SimulationStepTime << endl;
    cout << "Conductivity: " << gd.Conductivity << endl;
    cout << "Alfa: " << gd.Alfa << endl;
    cout << "Tot: " << gd.Tot << endl;
    cout << "InitialTemp: " << gd.InitialTemp << endl;
    cout << "Density: " << gd.Density << endl;
    cout << "SpecificHeat: " << gd.SpecificHeat << endl;
    cout << "Nodes number: " << gd.nN << endl;
    cout << "Elements number: " << gd.nE << endl << endl;;


    cout << "Nodes:" << endl;
    for (int i = 0; i < grid.nN; i++)
        cout << setw(2) << i + 1 << "," << setw(12) << grid.nodes[i].x << "," << setw(12) << grid.nodes[i].y << endl;
    cout << endl;

    cout << "Elements: " << endl;
    for (int i = 0; i < grid.nE; i++)
    {
        cout << i + 1 << "," << setw(5);
        for (int j = 0; j < 4; j++)
        {
            cout << grid.elements[i].ID[j] << ", ";
            if (j != 3)
                cout << setw(5);
        }
        cout << endl;
    }


    file.close();

    return 0;
}