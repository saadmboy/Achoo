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


const char * LOCATION_OF_ACHOO_FILE = "/Users/Saad/Desktop/achoo/Scraper/diseases.txt";


bool loadFromFile(const char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree);
template<class T>
void createPictureFromTree(char *, AVLtree<T> *);
void innerSearchTree(AVLnode<Symptom> *& root, string s, vector<Search *> * results, AVLnode<Symptom> *& node, int currentWordInInput, int numberOfWordsInInput);
vector<Search *> * searchTree(AVLnode<Symptom> *& root, string usersSearchQuery);
vector<Search *> * searchVector(vector<Search *> *, string);

int main(int argc, const char * argv[]) {
    AVLtree<Disease> * diseases;//create diseases tree
    AVLtree<Symptom> *symptoms;//create symptoms tree
    diseases = new AVLtree<Disease>();
    symptoms = new AVLtree<Symptom>();
    
    //populates the tree with the contents from the following file
    loadFromFile(LOCATION_OF_ACHOO_FILE, diseases, symptoms);
    
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
            
            vector<Search *> * searchResults;
            
            
            searchResults = searchTree(symptoms->root ,toS);
            
            if(searchResults->size() > 1){
                //http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
                sort(searchResults->begin(), searchResults->end(), isSearch1MoreThanSearch2());
                
                //for (auto s = searchResults->begin(); s != searchResults->end(); s++ ) {
                    //cout << (*s)->disease->name << ":\t" << (*s)->searchValue <<endl;
                //}
                cout << "Found " << searchResults->size()  << " symptoms\n\n\n\n\n\n\n\n\n\n";
                char areThereMoreSymptoms = 'y';
                while (areThereMoreSymptoms == 'y' && searchResults->size() > 1) {
                    cout << "Do you have any other symptoms? (y or n) "<<endl;
                    cin >> areThereMoreSymptoms;
                    if(areThereMoreSymptoms == 'y'){
                        cout << "Please type in your next symptom: " <<endl;
                        string newSymp = "";
                        cin >> newSymp;
                        
                        searchResults = searchVector(searchResults, newSymp);
                        cout << "Found " << searchResults->size()  << "\n";
                        for (auto s = searchResults->begin(); s != searchResults->end(); s++ ) {
                            cout << (*s)->disease->name << ":\t" << (*s)->searchValue <<endl;
                        }

                    }
                }
                
            }else{
                cout << "Sorry, not found\n";
            }
            
            
            delete searchResults;
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
bool loadFromFile(const char * fileName, AVLtree<Disease> * diseasesTree, AVLtree<Symptom> * symptomsTree){

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


//searches all symptoms for one word
//template <class T>
void innerSearchTree(AVLnode<Symptom> *& root, string s, vector<Search *> * results, AVLnode<Symptom> *& node, int currentWordInInput, int numberOfWordsInInput){
    
    transform(s.begin(),s.end(), s.begin(), ::tolower);//lowercase the search
    //inorder traversal
    
    stack<AVLnode<Symptom> *> stack;
    AVLnode<Symptom> *Tmp = root;
    while(1) {
        while(Tmp!=NULL) {
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
    
    
    for (int i = 0; i < wordsInQuery.size(); i++) {
        //cout << words[i] << "\n";
        innerSearchTree(root, wordsInQuery[i], toR, root, i, wordsInQuery.size());
    }
    
    return toR;
}


vector<Search *> * searchVector(vector<Search *> * originalResults, string newSymp){
    vector<Search *> *  toReturn;
    toReturn = new vector<Search *>;
    
    vector<string> wordsInQuery = Utilities::split(newSymp, ' ');
    
    
    for (auto s = originalResults->begin(); s != originalResults->end(); s++ ) {
        for (int i = 0; i < wordsInQuery.size(); i++) {
            for (int z = 0; z < (*s)->disease->symptoms.size(); z++) {
                Search * search;
                search = new Search;
                (*search).disease = (*s)->disease;
                (*search).searchValue = (*s)->disease->symptoms[z]->compare(newSymp, wordsInQuery.size());
                (*search).numElementInInput = i;
                if(!(*toReturn).empty()){
                    if((*toReturn).back()->numElementInInput == i - 1)//if the last element inserted
                        (*search).searchValue++;
                }
                
                if((*search).searchValue > 0)
                    (*toReturn).push_back(search);
                else
                    delete search;
            }
        }
    }
    delete originalResults;
    return toReturn;
}









