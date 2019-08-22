// ���ŵ�ַ�� -> ƽ��̽�ⷨ
// "with positive increments only"

#include <stdio.h>
#include <stdlib.h>
#include <cmath> 


#define MAXTABLESIZE 100000 /* �����ٵ����ɢ�б��� */
typedef int ElementType;    /* �ؼ������������� */
typedef int Index;          /* ɢ�е�ַ���� */
typedef Index Position;     /* ��������λ����ɢ�е�ַ��ͬһ���� */
/* ɢ�е�Ԫ״̬���ͣ��ֱ��Ӧ���кϷ�Ԫ�ء��յ�Ԫ������ɾ��Ԫ�� */
typedef enum { Legitimate, Empty, Deleted } EntryType;
 
typedef struct HashEntry Cell; /* ɢ�б�Ԫ���� */
struct HashEntry{
    ElementType Data; /* ���Ԫ�� */
    EntryType Info;   /* ��Ԫ״̬ */
};
 
typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    Cell *Cells;   /* ���ɢ�е�Ԫ���ݵ����� */
};

int NextPrime( int N );
HashTable CreateTable( int TableSize );
Position Hash(ElementType Key, int Size);
Position Find( HashTable H, ElementType Key, int i, int M);
bool Insert( HashTable H, ElementType Key, int i, int M);
void DestroyTable( HashTable H );

int main(void){
	int N, M, i;
	ElementType Key;
	ElementType Arr[MAXTABLESIZE];
	HashTable H;
	
	// create
	scanf("%d", &N);
	H = CreateTable(N);
	
	// get data
	scanf("%d", &M);
	
	for (i = 0; i < M; i++){
		scanf("%d", &Key);
		Insert(H, Key, i, M);
	}
	
	
	return 0;
}

int NextPrime( int N )
{ /* ���ش���N�Ҳ�����MAXTABLESIZE����С���� */
	if (N == 1){
		return 2;
	} else {
		int i, p = (N%2)? N+2 : N+1; /*�Ӵ���N����һ��������ʼ */
 
	    while( p <= MAXTABLESIZE ) {
	        for( i=(int)sqrt(p); i>2; i-- )
	            if ( !(p%i) ) break; /* p�������� */
	        if ( i==2 ) break; /* for����������˵��p������ */
	        else  p += 2; /* ������̽��һ������ */
	    }
	    return p;
	}
}
 
HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������� */
    H->TableSize = NextPrime(TableSize);
    /* ������Ԫ���� */
    H->Cells = (Cell *)malloc(H->TableSize*sizeof(Cell));
    /* ��ʼ����Ԫ״̬Ϊ���յ�Ԫ�� */
    for( i=0; i<H->TableSize; i++ )
        H->Cells[i].Info = Empty;
 
    return H;
}

Position Hash(ElementType Key, int Size) {
	return Key % Size;
}
Position Find( HashTable H, ElementType Key, int i, int M )
{
    Position CurrentPos, NewPos;
    
    int k = 0;
 
    NewPos = CurrentPos = Hash( Key, H->TableSize ); /* ��ʼɢ��λ�� */
    /* ����λ�õĵ�Ԫ�ǿգ����Ҳ���Ҫ�ҵ�Ԫ��ʱ��������ͻ */
    while( H->Cells[NewPos].Info!=Empty && H->Cells[NewPos].Data!=Key ) {
        k++;
        NewPos = (CurrentPos + k * k) % H->TableSize;
        if (k > H->TableSize) {
        	break;
		}
    }
    if (k > H->TableSize) {
        printf("-");
	} else {
		printf("%d", NewPos);
	}
	if (i < M-1) {
		printf(" ");
	}
    return NewPos; /* ��ʱNewPos������Key��λ�ã�������һ���յ�Ԫ��λ�ã���ʾ�Ҳ�����*/
}
bool Insert( HashTable H, ElementType Key, int i, int M)
{
    Position Pos = Find( H, Key, i, M ); /* �ȼ��Key�Ƿ��Ѿ����� */
 
    if( H->Cells[Pos].Info != Legitimate ) { /* ��������Ԫû�б�ռ��˵��Key���Բ����ڴ� */
        H->Cells[Pos].Info = Legitimate;
        H->Cells[Pos].Data = Key;
        /*�ַ������͵Ĺؼ�����Ҫ strcpy ����!! */
        return true;
    }
    else {
        return false;
    }
}

