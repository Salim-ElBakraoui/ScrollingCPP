/*
 * CContainer.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: salim */

#include <cassert>
#include <iostream>
using namespace std;
#include "CContainer.h"

CContainer::CNode::CNode(CNode* pPrev, CNode* pNext, void* pElem){
	cout << "Constructor CContainer::CNode" << endl;
	m_pPrev = pPrev;
	m_pNext = pNext;
	m_pElem = pElem;

	if(m_pPrev) m_pPrev->m_pNext = this;
	if(m_pNext)	m_pNext->m_pPrev = this;
}

CContainer::CNode::~CNode(){
	cout << "Destructor CContainer::CNode" << endl;
	if(m_pNext)m_pNext->m_pPrev = m_pPrev;
	if(m_pPrev)m_pPrev->m_pNext = m_pNext;
}

CContainer::CContainer(t_ptfV pDeleteFunc) {
	cout << "Constructor CContainer::CContainer" << endl;
	m_pDeleteFunc = pDeleteFunc;
	m_iCard = 0;
	m_pHead = nullptr;
	m_pTail = nullptr;

}

CContainer::~CContainer() {
	 cout << "Destructor CContainer::CContainer" << endl;
	while(m_pTail){
#define _pDelete		m_pHead
		_pDelete=m_pTail;
		m_pTail=m_pTail->m_pPrev;
		m_pDeleteFunc(_pDelete->m_pElem);
		delete _pDelete;
		m_iCard--;
#undef	_pDelete
	}
	m_pDeleteFunc = nullptr;
	assert(m_iCard==0);
}

int CContainer::Card(){ return m_iCard; }

void* CContainer::Pushback(void* pElem){
	if(!m_iCard){
		assert(m_pHead==nullptr);
		assert(m_pTail==nullptr);
		m_pHead = m_pTail = new CContainer::CNode(nullptr, nullptr, pElem);
	}
	else{
		m_pTail = new CContainer::CNode(m_pTail, nullptr, pElem);
	}
	assert(m_pTail->m_pElem == pElem);
	m_iCard++;
	return m_pTail->m_pElem;
}

void* CContainer::Getback(){return m_pTail->m_pElem;}

//void* CContainer::Getfront(){return m_pHead->m_pElem;}

void* CContainer::Parse(t_ptfVV pParseFunc, void*pParam, e_parseMode mode){

	CNode* pScan = m_pHead;
	int match = 0;
	long int iRet = 0;
	while(pScan){
		if( (iRet=reinterpret_cast<long int>(pParseFunc(pScan->m_pElem, pParam))) ){
			if(mode==PARSE_BREAK) return pScan->m_pElem;
			match |= reinterpret_cast<long int>(iRet);
		}

		pScan = pScan->m_pNext;
	}
	return reinterpret_cast<void*>(match);
}

//void* CContainer::Popfront(){
//	CNode* pNCache = m_pHead;
//	void* pElem = m_pHead->m_pElem;
//	m_pHead = m_pHead->m_pNext;
//	delete pNCache;
//	m_iCard--;
//	return pElem;
//#undef _pCache
//}

//Deletes Node if pParseFunc sends 1, lets Node live if it's 0
void* CContainer::ParseDelIf(t_ptfVV pParseFunc, void*pParam){
	if(!m_iCard)
		return nullptr;

	CNode* pScan = m_pHead;

	while(pScan){
		if(pParseFunc(pScan->m_pElem, pParam)){
			if(pScan==m_pHead)m_pHead=m_pHead->m_pNext;
			if(pScan==m_pTail)m_pTail=m_pTail->m_pPrev;
			m_iCard--;
			m_pDeleteFunc(pScan->m_pElem);
			delete pScan;
			return nullptr;
		}
		else pScan=pScan->m_pNext;
	}
	return nullptr;
}

void* CContainer::IntersectDelIf(t_ptfVV pIntersectFunc, CContainer* pOthers){
	CNode* pScan=m_pHead;
	CNode* pOther;
	CNode* pDelete;
	while(pScan){
		pOther=pOthers->m_pHead;
		while(pScan && pOther){
			if(pIntersectFunc(pScan->m_pElem, pOther->m_pElem)){
				pOthers->m_pDeleteFunc(pOther->m_pElem);
				if(pOther==pOthers->m_pHead)pOthers->m_pHead=pOthers->m_pHead->m_pNext;
				if(pOther==pOthers->m_pTail)pOthers->m_pTail=pOthers->m_pTail->m_pPrev;
				pDelete = pOther;
				pOther=pOther->m_pNext;
				delete pDelete;
				pOthers->m_iCard--;

				m_pDeleteFunc(pScan->m_pElem);
				if(pScan==m_pHead)m_pHead=m_pHead->m_pNext;
				if(pScan==m_pTail)m_pTail=m_pTail->m_pPrev;
				pDelete = pScan;
				pScan=pScan->m_pNext;
				delete pDelete;
				m_iCard--;
			}
			if(pOther)pOther=pOther->m_pNext;
		}
		if(pScan)pScan=pScan->m_pNext;
	}
	return nullptr;
}
