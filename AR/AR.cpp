#include <stdint.h>

struct Node 
{
  struct Node * pNext;
  uint8_t value;
};

struct Node n3 = { 0, 4 };
struct Node n2 = { 0, 2 };
struct Node n1 = { 0, 5 };

struct Node **f(struct Node **ppn, struct Node *pn)
{
  struct Node **result;                       // ppn pointer to a pointer to a node(struct), pn is a pointer to a node(struct)
  if ((!*ppn) || ((*ppn)->value > pn->value)) //evaluate left hand side if it is true you dont have to do right hand side
  {                                           //if left side is false then check right side
    pn->pNext = *ppn;
    *ppn = pn;
    result = ppn;
  }
  else
  {
    result = f(&((*ppn)->pNext), pn);
  }
  return result;
}

int main()
{
  struct Node *pFirst;
  pFirst = 0;
  f(&pFirst, &n1);//&pFirst null pointer
  f(&pFirst, &n2);
  f(&pFirst, &n3);
  return 0;
}
