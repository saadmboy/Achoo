//
//  main.cpp
//  Achoo
//
//  Created by Saad K on 3/8/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include <stdio.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Tree.h"

#include "Structs.cpp"


using namespace std;


bool loadFromFile(char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree);
vector<string> &split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);

/*
 Store diesases as roots and symptoms as children
 AND
 Store symtoms as roots and diseases as children
 */

/*
    Sample Run:
        Enter symptom: i have a headace
        0 *remove I, have, etc from input
        1 *loop through symtoms tree and find the symtom that contains input*
        2 *get disease name from tree*
        3 *find disease in symtoms array*
        4 *ask user if he displays other symptoms from that disease*
            if yes: diagnose
            if not: find next symtom from tree. (1)
*/


int main(int argc, const char * argv[]) {
    AVLtree<Disease> * diseases;
    AVLtree<Symptom> *symptoms;
    
    diseases = new AVLtree<Disease>();
    symptoms = new AVLtree<Symptom>();
    
    loadFromFile("/Users/Saad/Desktop/achoo/Scraper/diseases.txt", diseases, symptoms);
    
    string input = "";
    cout << "q to quit\ns to search symptoms\nd to search diseases\n";
    while (input != "q") {
        getline(cin,input);
        if(input == "s"){
            cout << "Please type the search term: "<<endl;
            string toS = "";
            getline(cin, toS);
            AVLnode<Symptom> * search =symptoms->search(toS, symptoms->root);
            if(search)
                cout << search->key.disease << endl;
            else
                cout << toS << " was not found\n";
        }else if(input == "d"){
            cout << "Please type the search term: " <<endl;
            string toS = "";
            getline(cin, toS);
            AVLnode<Disease> * search =diseases->search(toS, diseases->root);
            if(search)
                cout << search->key.symptoms.size() << endl;
            else
                cout << toS << " was not found\n";
        }else{
            cout << "invalid command\n";
        }
    }
    
    
    //diseases->display(diseases->root, 1);
    FILE * pFile;
    pFile = fopen ("/Users/Saad/Desktop/diseases.gv" , "w+");
    diseases->print_DOT(pFile);
    //system("dot -Tpng /Users/Saad/Desktop/diseases.gv -o /Users/Saad/Desktop/diseases.png");
    fclose(pFile);
    
    pFile = fopen ("/Users/Saad/Desktop/symptoms.gv" , "w+");
    symptoms->print_DOT(pFile);
    //system("dot -Tpng /Users/Saad/Desktop/symptoms.gv -o /Users/Saad/Desktop/symptoms.png");
    fclose(pFile);
    
    delete diseases;
    delete symptoms;
    return 0;
}



bool loadFromFile(char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree){

    if(symptomsTree == NULL || diseasesTree == NULL || fileName == NULL)
        return false;
    
    ifstream in;//declare ifstram object
    in.open(fileName);//open fhe file
    
    if(in.fail()){//check to see opening failed
        cout << "Error opening file\n";
        return false;
    }
    int count = 0;
    
    long start = time(0);
    string temp;
    
    while (in.peek() != EOF) {
        count++;
        getline(in, temp, '\n');
        
        //FROM: http://stackoverflow.com/questions/236129/split-a-string-in-c
        istringstream iss(temp);
        
        vector<string> symptoms = split(temp, '\t');
        Disease * d;
        d = new Disease;
        d->name = symptoms[0];
        //cout << endl << count << ": " << d->name << endl;
        vector<Symptom * > symptomsVector;
        for(int i = 1; i < symptoms.size(); i++){// i=0 == the disease name
            //cout << symptoms[i] << endl;
            Symptom * s;
            s = new Symptom;
            s->name = symptoms[i];
            s->disease = d;
            symptomsVector.push_back(s);
            symptomsTree->insert(*s);
        }
        d->symptoms = symptomsVector;
        diseasesTree->insert(*d);

            
    }
    
    cout << "Imported " << count << " diseases in " << (time(0) - start) << " seconds\n";
    return true;
}


vector<string> &split(const string &s, char delim, vector<string> &elems){
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim){
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}




