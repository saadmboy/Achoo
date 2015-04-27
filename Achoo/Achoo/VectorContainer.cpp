//
//  VectorContainer.cpp
//  Achoo
//
//  Created by Saad K on 4/22/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include "VectorContainer.h"

using namespace std;

/**
 * Innervector is private, and so a method is needed to return the last element of the vector
 **/
template <class T>
T VectorContainer<T>::getBack(){
    return innerVector->back();
}

/**
 * Innervector is private, and so a method is needed to return the size of the vector
 **/
template <class T>
int VectorContainer<T>::size(){
    return innerVector->size();
}

/**
 * Innervector is private, and so a method is needed to inser an object to the vector
 **/
template <class T>
bool VectorContainer<T>::insert(T toAdd){
    transform(toAdd->name.begin(),toAdd->name
              .end(), toAdd->name.begin(), ::tolower);//lowercase the addition
    innerVector->push_back(toAdd);
    return true;
}

/**
 * Innervector is private, and so a method is needed to return an object from the vector
**/
template <class T>
T VectorContainer<T>::get(int index){
    if(index > size() || index < 0)
        return NULL;
    return (*innerVector)[index];
}

/**
 * Complete search means that it compares the full user input with the full text in disease/symptom.
 * Used to search diseases
**/
template <class T>
T VectorContainer<T>::completeSearch(string toSearch){
    transform(toSearch.begin(),toSearch.end(), toSearch.begin(), ::tolower);//lowercase the search
    for (auto s = innerVector->begin(); s != innerVector->end(); s++ ) {//go through each originalResult
        if((*s)->name == toSearch){
            return (*s);
        }
    }
    return NULL;
}


/**
 * Initially goes through a disease vector and finds and matches to the users given symptom
 * Theoretically speaking I don't need the originalResults, the method is being called on originalResults; but I have to include it b/c of tempate<class T>. If this funtction was called on this (e.g object itself), the template prevents it from compiling b/c the template can work with Symptom and Disease and Symptom and Disease don't have certain instance variables such as searchValue
**/
template <class T>
VectorContainer<Search *> * VectorContainer<T>::initialSearchVector(VectorContainer<Disease *> * diseases, string toSearch){
    //toSearch = formatString(toSearch);
    
    VectorContainer<Search *> * toReturn;
    toReturn = new VectorContainer<Search *>;
    
    transform(toSearch.begin(),toSearch.end(), toSearch.begin(), ::tolower);//lowercase the search
    
    vector<string> wordsInQuery = Utilities::split(toSearch, ' ');
    
    
    for (auto s = diseases->getBeginningIterator(); s != diseases->getEndingIterator(); s++ ) {//go through each originalResult
        Search * search;
        search = new Search;
        (*search).disease = (*s);
        (*search).searchValue = 0;
        for (int i = 0; i < wordsInQuery.size(); i++) {
            if(isValid(wordsInQuery[i])){
                for (int z = 0; z < (*s)->symptoms.size(); z++) {
                    double compareResult = (*s)->symptoms[z]->compare(wordsInQuery[i], wordsInQuery.size());
                    (*search).searchValue += compareResult;
                    (*search).numElementInInput = i;
                    if((toReturn)->size() > 0){
                        if((toReturn)->getBack()->numElementInInput == i - 1)//if the last element inserted
                            (*search).searchValue++;
                    }
                    if(compareResult > 0)
                        break;
                }
            }
            
        }
        if((*search).searchValue > 0){//only add the old result if it has the new symptom too
            (*toReturn).insert(search);
        }else{
            delete search;
        }
    }
    
    return toReturn;
}

/**
 * Searches a vector containing search objects. Used to narrow down the search
 * Theoretically speaking I don't need the originalResults, the method is being called on originalResults; but I have to include it b/c of tempate<class T>. If this funtction was called on this (e.g object itself), the template prevents it from compiling b/c the template can work with Symptom and Disease and Symptom and Disease don't have certain instance variables such as searchValue
**/
template <class T>
VectorContainer<Search *> * VectorContainer<T>::searchSearchVector(VectorContainer<Search *> * originalResults, string newSymp){
    VectorContainer<Search *> * toReturn;
    toReturn = new VectorContainer<Search *>;
    
    transform(newSymp.begin(),newSymp.end(), newSymp.begin(), ::tolower);//lowercase the search
    
    vector<string> wordsInQuery = Utilities::split(newSymp, ' ');
    
    
    for (auto s = originalResults->getBeginningIterator(); s != originalResults->getEndingIterator(); s++ ) {//go through each originalResult
        // //Users//Saad//Desktop//achoo//Scraper//diseases.txt
        Search * search;
        search = new Search;
        (*search).disease = (*s)->disease;
        (*search).searchValue = (*s)->searchValue;
        for (int i = 0; i < wordsInQuery.size(); i++) {
            
            if(isValid(wordsInQuery[i])){
                for (int z = 0; z < (*s)->disease->symptoms.size(); z++) {
                    double compareResult = (*s)->disease->symptoms[z]->compare(wordsInQuery[i], wordsInQuery.size());
                    (*search).searchValue += compareResult;
                    (*search).numElementInInput = i;
                    if((toReturn)->size() > 0){
                        if((toReturn)->getBack()->numElementInInput == i - 1)//if the last element inserted
                            (*search).searchValue++;
                    }
                    if(compareResult > 0)
                        break;
                }
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

/**
 * Checks if the @param input is valid or not
 * @pre-condition @param input must be 1 word
 * @return true if valid, false otherwise
**/
template <class T>
bool VectorContainer<T>::isValid(string input){
    
    //checks user input for words to remove from search.
    string toRemove[] = {"i", "me", "a", "have", "had", "since", "days", "my", "am"};
    
    for (string s : toRemove){
        if(input == s)
            return false;
    }
    
    
    
    return true;
}

//returns the beginning iterator, needed to loop through vector and for sort/transform fucntions
template <class T>
typename vector<T>::iterator VectorContainer<T>::getBeginningIterator(){
    return innerVector->begin();
}

//returns the ending iterator, needed to loop through vector and for sort/transform fucntions
template <class T>
typename vector<T>::iterator VectorContainer<T>::getEndingIterator(){
    return innerVector->end();
}

//allow the VectorContainer to be used with Symptom *, Disease * and Search *
template class VectorContainer<Symptom *>;
template class VectorContainer<Disease *>;
template class VectorContainer<Search *>;