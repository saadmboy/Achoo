//
//  VectorContainer.cpp
//  Achoo
//
//  Created by Saad K on 4/22/15.
//  Copyright (c) 2015 Saad K. All rights reserved.
//

#include "VectorContainer.h"

using namespace std;


template <class T>
int VectorContainer<T>::size(){
    return innerVector->size();
}

template <class T>
bool VectorContainer<T>::insert(T toAdd){
    
    transform(toAdd->name.begin(),toAdd->name
              .end(), toAdd->name.begin(), ::tolower);//lowercase the search
    innerVector->push_back(toAdd);
    return true;
}

template <class T>
T VectorContainer<T>::get(int index){
    if(index > size() || index < 0)
        return NULL;
    return (*innerVector)[index];
}

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
**/
template <class T>
VectorContainer<Search *> * VectorContainer<T>::initialSearchVector(VectorContainer<Disease *> * diseases, string toSearch){
    VectorContainer<Search *> * toReturn;
    toReturn = new VectorContainer<Search *>;
    
    transform(toSearch.begin(),toSearch.end(), toSearch.begin(), ::tolower);//lowercase the search
    
    vector<string> wordsInQuery = Utilities::split(toSearch, ' ');
    
    
    for (auto s = diseases->innerVector->begin(); s != diseases->innerVector->end(); s++ ) {//go through each originalResult
        Search * search;
        search = new Search;
        (*search).disease = (*s);
        (*search).searchValue = 0;
        for (int i = 0; i < wordsInQuery.size(); i++) {
            for (int z = 0; z < (*s)->symptoms.size(); z++) {
                double compareResult = (*s)->symptoms[z]->compare(wordsInQuery[i], wordsInQuery.size());
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
**/
template <class T>
VectorContainer<Search *> * VectorContainer<T>::searchSearchVector(VectorContainer<Search *> * originalResults, string newSymp){
    VectorContainer<Search *> * toReturn;
    toReturn = new VectorContainer<Search *>;
    
    transform(newSymp.begin(),newSymp.end(), newSymp.begin(), ::tolower);//lowercase the search
    
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

//allow the VectorContainer to be used with Symptom *, Disease * and Search *
template class VectorContainer<Symptom *>;
template class VectorContainer<Disease *>;
template class VectorContainer<Search *>;