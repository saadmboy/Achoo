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
#include "Structs.cpp"
#include "VectorContainer.h"

using namespace std;


const char * LOCATION_OF_ACHOO_FILE = "/Users/Saad/Desktop/achoo/Scraper/diseases.txt";

//------------Start Method Declarations

bool loadFromFile(const char * fileName, VectorContainer<Disease *> * diseases, VectorContainer<Symptom *> * symptoms);
void manageMainMenu(VectorContainer<Disease *> *, VectorContainer<Symptom *> *);
void manageAdditionalSearch(VectorContainer<Search *> * initialSearchResults);

//------------End Method Declarations

int main(int argc, const char * argv[]) {
    VectorContainer<Disease *> * diseases = new VectorContainer<Disease *>;
    VectorContainer<Symptom *> * symptoms = new VectorContainer<Symptom *>;
    
    //populates the tree with the contents from the following file
    if(!loadFromFile(LOCATION_OF_ACHOO_FILE, diseases, symptoms)){
        cout << "Unable to load the file\nExiting now...";
        return 1;//non successful execution
    }
        
    
    manageMainMenu(diseases, symptoms);
    
    
    
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
            symptomsVector.push_back(s);
            
            symptomsContainer->insert(s);
            
        }
        d->symptoms = symptomsVector;
        diseasesContainer->insert(d);
    }
    
    //no delete d; because it's still store in the tree
    
    cout << "Imported " << dCount << " diseases and " << sCount <<" symptoms in " << float(clock() - t)/CLOCKS_PER_SEC << " seconds\n";
    return true;
}


void manageMainMenu(VectorContainer<Disease *> * diseases, VectorContainer<Symptom *> * symptoms){
    //temporary menu for debugging
    string input = "";
    while (input != "q") {
        cout << "q to quit\ns to search symptoms\nd to search diseases\n";
        getline(cin,input);
        if(input == "s"){
            cout << "Please type the symptom term: "<<endl;
            string toS = "";
            getline(cin, toS);
            
            VectorContainer<Search *> * searchResults;
            searchResults = searchResults->initialSearchVector(diseases, toS);
            
            if(searchResults->size() == 1){//rarely the case.
                cout << "It seems that you have " << searchResults->get(0)->disease->name << " with the following sympyoms: \n";
                for (auto s = searchResults->get(0)->disease->symptoms.begin(); s != searchResults->get(0)->disease->symptoms.end(); s++ ) {
                    cout << "\t" << (*s)->name <<"\n";
                }
            }else if(searchResults->size() > 0){//most likely scenarios
                manageAdditionalSearch(searchResults);//need to narrow down more
            }else{
                cout << "Sorry, no diseases found with that search term.\n";
            }
            
            //delete searchResults;
        }else if(input == "d"){
            
            //no memory leaks here tested by searching 1 diseas 50 times
            
            cout << "Please type the disease term: " <<endl;
            string toS = "";
            getline(cin, toS);
            
            Disease * search = diseases->completeSearch(toS);
            if(search){
                cout << "Found " << search->name << " with "<< search->symptoms.size() << " symptoms: " << endl;
                for(Symptom * s: search->symptoms)
                    cout << "\t" << s->name<< endl;
            }else{
                cout << toS << " was not found\n";
            }
        }else if(input == "q"){
        }else{
            cout << "invalid command\n";
        }
    }
}

/**
 * Manages the search results.
 * Either tells users the diagnosis, gives him a list of possibilities or helps him narrow it down
 @PreCondition: searchResults->size() > 1 (not really but makes it flow better)
**/
void manageAdditionalSearch(VectorContainer<Search *> * searchResults){
    //ideally we would want to have only 1 disease to have a clear diagnosis
    //because of this if the search results based on the users input is big (e.g search input is too broad)
    //we will attempt to narrow it down.
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
    //while loop ended.
    //3 Possibilities:
    
    if(searchResults->size() == 0){//Possibility 1: the searchResults is size 0, meaning the user either gave too much info or the input didn't match any diseases
        cout << "Sorry no diseases found with those symptoms\n";
    }else if(searchResults->size() == 1){//Possibility 2: Ideal scenario, clear diagnosos.
        
        for (auto s = searchResults->innerVector->begin(); s != searchResults->innerVector->end(); s++ ) {
            cout << (*s)->disease->name << ":\t" << (*s)->searchValue <<endl;
        }
        
        if(searchResults->get(0) != NULL){
            cout << "It seems that you have " << searchResults->get(0)->disease->name << " with the following sympyoms: \n";
            
            for (auto s = searchResults->get(0)->disease->symptoms.begin(); s != searchResults->get(0)->disease->symptoms.end(); s++ ) {
                cout << "\t" << (*s)->name <<"\n";
            }
        }else{
            cout << "An error occured\n";
        }
    }else{//Possibility 3: We have more than 1 disease (the user pressed 'n') and we have to sort it out
        cout << "I will now print out some symptoms from potential diseases you might have. These symptoms are in order of which seems most similiar to your given symptoms. If you think you have the majority of the symptoms, press y, if not press n to move on\n\n";
        
        //sort the vector based on the search value
        sort(searchResults->innerVector->begin(), searchResults->innerVector->end(), isSearch1MoreThanSearch2());
        
        //go through and ask the user if he has the following symptoms (that match the disease in the searchResults)
        string isThisIt = "n";
        int currIndex = 0;
        while (isThisIt != "y" && currIndex < searchResults->size()) {
            
            cout << "Do you have any of the following sympyoms: \n";
            
            for (auto s = searchResults->get(currIndex)->disease->symptoms.begin(); s != searchResults->get(currIndex)->disease->symptoms.end(); s++ ) {
                cout << "\t" << (*s)->name <<"\n";
            }
            cout << "y or n?: ";
            cin >> isThisIt;
            if(isThisIt != "y")//move on the index only if the user didn't say yes, if yes then we need the index to print out the disease name
                currIndex++;
        }
        
        if(isThisIt == "y" && currIndex < searchResults->size()){
            cout << "\n\nIt seems that you have " << searchResults->get(currIndex)->disease->name << "\n";
        }else{
            cout << "Sorry, unfortunately we were unable to diagnose your symptoms\n";
        }
    }//end possibility 3
}


//----------Credits:
//http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
//http://stackoverflow.com/questions/236129/split-a-string-in-c


