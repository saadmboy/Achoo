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
//#include "Tree.h"
#include "Structs.cpp"
#include "VectorContainer.h"

using namespace std;


const char * LOCATION_OF_ACHOO_FILE = "/Users/Saad/Desktop/achoo/Scraper/diseases.txt";

//------------Start Method Declarations

bool loadFromFile(const char * fileName, VectorContainer<Disease *> * diseases, VectorContainer<Symptom *> * symptoms);

//------------End Method Declarations

int main(int argc, const char * argv[]) {
    
    
    
    VectorContainer<Disease *> * diseases = new VectorContainer<Disease *>;
    VectorContainer<Symptom *> * symptoms = new VectorContainer<Symptom *>;
    
    
    
    //populates the tree with the contents from the following file
    loadFromFile(LOCATION_OF_ACHOO_FILE, diseases, symptoms);
    
    
    
    //temporary menu for debugging
    string input = "";
    cout << "q to quit\ns to search symptoms\nd to search diseases\n";
    while (input != "q") {
        getline(cin,input);
        if(input == "s"){
            cout << "Please type the symptom term: "<<endl;
            string toS = "";
            getline(cin, toS);
            
            VectorContainer<Search *> * searchResults;
            
            
            searchResults = searchResults->initialSearchVector(diseases, toS);
            
            
            
            if(searchResults->size() > 1){
                //http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
                
                
                string areThereMoreSymptoms = "y";
                while (areThereMoreSymptoms == "y" && searchResults->size() > 1) {
                    cout << "We found "<< searchResults->size() <<" diseases with that symptom.\n";
                    cout << "Would you like to narrow the search results down by adding more symptoms? (y or n) "<<endl;
                    getline(cin,areThereMoreSymptoms);//woud use cin >> but cin and getline don't play well togetehr
                    if(areThereMoreSymptoms == "y"){
                        cout << "Please type in your next symptom: " <<endl;
                        string newSymp = "";
                        getline(cin, newSymp);
                        
                        searchResults = searchResults->searchSearchVector(searchResults, newSymp);
                        //cout << "Found " << searchResults->size()  << "\n";
                        

                    }
                }
                if(searchResults->size() == 0){
                    cout << "Sorry no diseases found with those symptoms\n";
                }else if(searchResults->size() == 1){
                    
                    for (auto s = searchResults->innerVector->begin(); s != searchResults->innerVector->end(); s++ ) {
                        cout << (*s)->disease->name << ":\t" << (*s)->searchValue <<endl;
                    }
                    
                    if(searchResults->get(0) != NULL){
                        cout << "It seems that you have " << searchResults->get(0)->name << " with the following sympyoms: \n";
                        
                        for (auto s = searchResults->get(0)->disease->symptoms.begin(); s != searchResults->get(0)->disease->symptoms.end(); s++ ) {
                            cout << "\t" << (*s)->name <<"\n";
                        }
                    }else{
                        cout << "An error occured\n";
                    }
                }else{
                    cout << "I will now print out some symptoms from potential diseases you might have. These symptoms are in order of which seems most similiar to your given symptoms. If you think you have the majority of the symptoms, press y, if not press n to move on\n\n";
                    
                    sort(searchResults->innerVector->begin(), searchResults->innerVector->end(), isSearch1MoreThanSearch2());
                    
                    string isThisIt = "n";
                    int currIndex = 0;
                    while (isThisIt != "y" && currIndex < searchResults->size()) {
                        
                        cout << "Do you have any of the following sympyoms: \n";
                        
                        for (auto s = searchResults->get(currIndex)->disease->symptoms.begin(); s != searchResults->get(currIndex)->disease->symptoms.end(); s++ ) {
                            cout << "\t" << (*s)->name <<"\n";
                        }
                        cout << "y or n?: ";
                        cin >> isThisIt;
                        if(isThisIt != "y")
                            currIndex++;
                    }
                    
                    if(isThisIt == "y" && currIndex < searchResults->size()){
                        cout << "\n\nIt seems that you have " << searchResults->get(currIndex)->disease->name << "\n";
                        
                    }else{
                        cout << "Sorry, unfortunately we were unable to diagnose your symptoms\n";
                    }
                }
                
                
            }else{
                cout << "Sorry, not found\n";
            }
            
            delete searchResults;
        }else if(input == "d"){
            
            //no memory leaks here tested by searching 1 diseas 50 times
            
            cout << "Please type the disease term: " <<endl;
            string toS = "";
            getline(cin, toS);
            
            Disease * search =diseases->completeSearch(toS);
            if(search){
                cout << "Found " << search->name << " with "<< search->symptoms.size() << " symptoms: " << endl;
                for(Symptom * s: search->symptoms)
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
bool loadFromFile(const char * fileName, VectorContainer<Disease *> * diseasesContainer, VectorContainer<Symptom *> * symptomsContainer){

    if(symptomsContainer == NULL || diseasesContainer == NULL || fileName == NULL)
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
            
            //symptomsContainer->innerVector->push_back(s);
            
            symptomsContainer->insert(s);
            
        }
        d->symptoms = symptomsVector;
        diseasesContainer->insert(d);
        //diseasesContainer->innerVector->push_back(d);
    }
    
    //no delete d; because it's still store in the tree
    
    cout << "Imported " << dCount << " diseases and " << sCount <<" symptoms in " << float(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
    return true;
}
/*
//searches all symptoms for one word
//template <class T>
void innerSearchTree(AVLnode<Symptom> *& root, string s, vector<Search *> * results, AVLnode<Symptom> *& node, int currentWordInInput, int numberOfWordsInInput){
    
    transform(s.begin(),s.end(), s.begin(), ::tolower);//lowercase the search
    //inorder traversal
    
    stack<AVLnode<Symptom> *> stack;
    AVLnode<Symptom> *Tmp = root;
    while(1) {
        while(Tmp != NULL) {
            stack.push(Tmp);
            Tmp = Tmp->left;
        }
        if(stack.empty())
            return;
        Tmp = stack.top();stack.pop();
        
        Search * search;
        search = new Search;
        (*search).disease = Tmp->key.disease;
        (*search).searchValue = Tmp->key.compare(s, numberOfWordsInInput);
        
        //http://www.cplusplus.com/reference/vector/vector/back/
        //basically if the user types in 'back pain' and the symptom has back pain in that order, increase the search vlaue
        if(!(*results).empty()){
            if((*results).back()->numElementInInput == currentWordInInput - 1)//if the last element inserted
                (*search).searchValue++;
        }
        
        (*search).numElementInInput = currentWordInInput;
        
        
        if((*search).searchValue > 0)
            (*results).push_back(search);
        else
            delete search;
        
        Tmp = Tmp->right;
    }
    delete Tmp;
}

vector<Search *> * searchTree(AVLnode<Symptom> *& root, string usersSearchQuery){
    vector<Search*> * toR;
    toR = new vector<Search *>;
    
    vector<string> wordsInQuery = Utilities::split(usersSearchQuery, ' ');
    for (int i = 0; i < wordsInQuery.size(); i++) {//search the tree for each word in the users query
        innerSearchTree(root, wordsInQuery[i], toR, root, i, wordsInQuery.size());
    }
    
    return toR;
}
*/
/*
VectorContainer * searchVector(VectorContainer * originalResults, string newSymp){
    transform(newSymp.begin(),newSymp.end(), newSymp.begin(), ::tolower);//lowercase the search

    VectorContainer *  toReturn;
    toReturn = new VectorContainer;
    
    vector<string> wordsInQuery = Utilities::split(newSymp, ' ');
    
    
    for (auto s = originalResults->innerVector->begin(); s != originalResults->innerVector->end(); s++ ) {//go through each originalResult
        
        Search * search;
        search = new Search;
        (*search).disease = (*s)->disease;
        (*search).searchValue = (*s)->searchValue;
        for (int i = 0; i < wordsInQuery.size(); i++) {
            for (int z = 0; z < (*s)->disease->symptoms.size(); z++) {
                double compareResult = (*s)->disease->symptoms[z]->compare(newSymp, wordsInQuery.size());
                (*search).searchValue += compareResult;
                (*search).numElementInInput = i;
                if(!(*toReturn).innerVector->empty()){
                    if((*toReturn).innerVector->back()->numElementInInput == i - 1)//if the last element inserted
                        (*search).searchValue++;
                }
                if(compareResult > 0)
                    break;
            }
        }
        if((*search).searchValue > (*s)->searchValue){//only add the old result if it has the new symptom too
            (*toReturn).insert(search);
        }else{
            delete search;
        }
    }
    delete originalResults;
    return toReturn;
}
*/








