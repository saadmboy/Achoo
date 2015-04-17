//
//  main.cpp
//  Achoo
//
//  Created by Saad K on 3/8/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//
#pragma once

#include <stdio.h>
#include <time.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <numeric>
#include "Tree.h"
#include "Structs.cpp"


using namespace std;


bool loadFromFile(char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree);
template<class T>
void createPictureFromTree(char *, AVLtree<T> *);

int main(int argc, const char * argv[]) {
    AVLtree<Disease> * diseases;//create diseases tree
    AVLtree<Symptom> *symptoms;//create symptoms tree
    diseases = new AVLtree<Disease>();
    symptoms = new AVLtree<Symptom>();
    
    //populates the tree with the contents from the following file
    loadFromFile("/Users/Saad/Desktop/achoo/achoo/Scraper/diseases.txt", diseases, symptoms);
    
    //symptoms->display(symptoms->root, 1);
    
    //temporary menu for debugging
    string input = "";
    cout << "q to quit\ns to search symptoms\nd to search diseases\n";
    while (input != "q") {
        getline(cin,input);
        if(input == "s"){
            cout << "Please type the symptom term: "<<endl;
            string toS = "";
            getline(cin, toS);
            //AVLnode<Symptom> * search =symptoms->completeSearch(toS, symptoms->root);
            
            vector<Search*> * search;
            
            
            search = symptoms->search(toS);
            
            if(search->size() > 1){
                for (auto s = search->begin(); s != search->end(); s++ ) {
                    cout << (*s)->disease->name << ":\t" << (*s)->searchValue <<endl;
                }
            }else{
                cout << "Sorry, not found\n";
            }
            delete search;
        }else if(input == "d"){
            cout << "Please type the disease term: " <<endl;
            string toS = "";
            getline(cin, toS);
            AVLnode<Disease> * search =diseases->completeSearch(toS, diseases->root);
            if(search){
                cout << "Found " << search->key.name << " with "<< search->key.symptoms.size() << " symptoms: " << endl;
                for(Symptom * s: search->key.symptoms)
                    cout << "\t" << s->name<< endl;
            }else{
                cout << toS << " was not found\n";
            }
        }else{
            cout << "invalid command\n";
        }
    }
    
    
    
    
    
    delete diseases;
    delete symptoms;
    return 0;
}


/**
 * Loads the file from the scraper and adds the diseases and symptoms to the tree
 * @return bool : params == NULL || file is invalid;
**/
bool loadFromFile(char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree){

    if(symptomsTree == NULL || diseasesTree == NULL || fileName == NULL)
        return false;
    
    ifstream in;//declare ifstram object
    in.open(fileName);//open fhe file
    
    if(in.fail()){//check to see opening failed
        cout << "Error opening file\n";
        return false;
    }
    
    int dCount = 0, sCount = 0;//used to count
    clock_t t;
    t = clock();
    string temp;
    
    while (in.peek() != EOF) {
        dCount++;
        getline(in, temp, '\n');
        
        //FROM: http://stackoverflow.com/questions/236129/split-a-string-in-c
        istringstream iss(temp);
        
        vector<string> symptoms = Utilities::split(temp, '\t');
        
        Disease * d;
        d = new Disease;
        d->name = symptoms[0];
        vector<Symptom * > symptomsVector;
        for(int i = 1; i < symptoms.size(); i++){// i=0 == the disease name
            sCount++;
            Symptom * s;
            s = new Symptom;
            s->name = symptoms[i];
            s->disease = d;
            symptomsVector.push_back(s);//needed for diseasesTree
            symptomsTree->insert(*s);
        }
        d->symptoms = symptomsVector;
        diseasesTree->insert(*d);
    }
    
    //no delete d; because it's still store in the tree
    
    cout << "Imported " << dCount << " diseases and " << sCount <<" symptoms in " << float(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
    return true;
}

template <class T>
void createPictureFromTree(char * address, AVLtree<T> * t){
    FILE * pFile;
    pFile = fopen ("/Users/Saad/Desktop/diseases.gv" , "w+");
    t->print_DOT(pFile);
    fclose(pFile);
}

