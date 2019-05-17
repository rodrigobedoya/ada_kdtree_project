#include <iostream>
#include <chrono>
#include <iomanip>
#include "kdtree.h"
#include <unistd.h>
#include <python3.6m/Python.h>
#include <string>

using namespace std;


int main(int argc, char **argv)
{
	string fileName(argv[1]);
	KdTree<int> tree;
	tree.load(fileName);
	tree.build();
	tree.print();	
	tree.write();
	string cmd = "python3 draw.py " + fileName;
	system(cmd.c_str());

    Node<int> *nodo = new Node<int>({6, 8});
    (tree.search(nodo))? cout << "Existe nodo\n" : cout << "No existe nodo\n";
    (tree.searchKK(nodo))? cout << "Existe nodo kk\n" : cout << "No existe nodo kk\n";
	
    chrono::time_point<chrono::high_resolution_clock> start, end;

    start = chrono::high_resolution_clock::now();
    tree.search(nodo);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> runtime = end - start;
    cout << "Bucar nodo gotto: "<< fixed << setprecision(10) << runtime.count() << " secs" << endl;
    
    start = chrono::high_resolution_clock::now();
    tree.searchKK(nodo);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> runtime2 = end - start;
    cout << "Buscar nodo kk: "<< fixed << setprecision(10) << runtime2.count() << " secs" << endl;
    


    string line; 
	
	while(true) 
	{ 
		 vector<int> user_point; 

		 stringstream sstream; 
		 cout << "Find nearest neighbor of point: "; 
		 getline(cin,line); 
		 sstream << line; 
		 string cmd = "python3 draw.py " + fileName; 
		 int inputPos, i = 0; 
		 while(sstream >> inputPos) 
		 { 
		 	user_point.push_back(inputPos); 
		 	cmd += " " + to_string(user_point[i++]); 
		 } 

		 if(user_point.size() < tree.k) 
		 	cout << "ERROR: too few point coordinates. Insert new coordinates (k="<<tree.k<<")"<<endl; 
		

		 else if(user_point.size() > tree.k) 
		 	cout << "ERROR: too many point coordinates. Insert new coordinates (k="<<tree.k<<")"<<endl; 
		
		 else 
		 { 
		 	//find nearest point 

		 	Node<int> *nodo = new Node<int>(user_point);
   
		    cout << endl;
		    nodo->print();
		    (tree.search(nodo))? cout << "Existe nodo\n" : cout << "No existe\n";

            start = chrono::high_resolution_clock::now();
		    tree.buscarVecinoskk(nodo);
            end = chrono::high_resolution_clock::now();
            chrono::duration<double> runtime3 = end - start;
            cout << "Buscar vecino kk: "<< fixed << setprecision(10) << runtime3.count() << " secs" << endl;


		 	system(cmd.c_str()); 
		 } 

	 } 
	
}
