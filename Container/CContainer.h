/*
 * CContainer.h
 *
 *  Created on: 6 sept. 2021
 *      Author: salim
 */

typedef void *(*t_ptfV)(void*);
typedef void *(*t_ptfVV)(void*, void*);

class CContainer {
private:
	class CNode{
	public:
		CNode* m_pPrev;
		CNode* m_pNext;
		void*  m_pElem;

	public:
		CNode(CNode*pPrev, CNode*pNext, void*pElem);
		~CNode();
	};
private:
	t_ptfV		m_pDeleteFunc;
	CNode*		m_pHead;
	CNode*		m_pTail;
	int			m_iCard;
public:
	enum e_parseMode{
		PARSE_BREAK = 0,
		PARSE_INTEGRAL = 1
	};
public:
	CContainer(t_ptfV pDeleteFunc);
	~CContainer();

	int   Card();
	void* Pushback(void*pElem);
	void* Getback();
	void* Parse(t_ptfVV pParseFunc, void*pParam, e_parseMode mode=PARSE_BREAK);
	void* ParseDelIf(t_ptfVV pParseFunc, void*pParam);
	void* IntersectDelIf(t_ptfVV pIntersectFunc, CContainer* pOthers);

};
