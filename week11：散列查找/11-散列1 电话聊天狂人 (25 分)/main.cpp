#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// �������ӷ�ʵ�� 


#define KEYLENGTH 11                   /* �ؼ����ַ�������󳤶� */
typedef char ElementType[KEYLENGTH+1]; /* �ؼ����������ַ��� */
typedef int Index;                     /* ɢ�е�ַ���� */
/******** �����ǵ�����Ķ��� ********/
typedef struct LNode *PtrToLNode;
struct LNode {
    ElementType Data;
    PtrToLNode Next;
    int Count; 
};
typedef PtrToLNode Position;
typedef PtrToLNode List;
/******** �����ǵ�����Ķ��� ********/
 
typedef struct TblNode *HashTable; /* ɢ�б����� */
struct TblNode {   /* ɢ�б��㶨�� */
    int TableSize; /* �����󳤶� */
    List Heads;    /* ָ������ͷ�������� */
};

Position Hash(ElementType Key, int Size);
HashTable CreateTable( int TableSize );
#define MAXD 5 
Position Find( HashTable H, ElementType Key );
bool Insert( HashTable H, ElementType Key );
void DestroyTable( HashTable H );


void ScanAndOutput(HashTable H);

#define MAXTABLESIZE 1000000
int NextPrime( int N );

int main(void){
	int N, i;
	ElementType Key;
	HashTable H;
	
	
	// creat hash table
	scanf("%d", &N);
	H = CreateTable(N*2);
	
	
	// get phone and insert into the hash table
	for(i = 0; i < N; i++){
		scanf("%s", Key);
		Insert(H, Key);
		scanf("%s", Key);
		Insert(H, Key);
		
	}
	
	
	// output
	ScanAndOutput(H);
	
	
	// destory
	DestroyTable(H);
	return 0;
}




int Hash(int Key, int Size) {
	return Key % Size;
}
 
HashTable CreateTable( int TableSize )
{
    HashTable H;
    int i;
 
    H = (HashTable)malloc(sizeof(struct TblNode));
    /* ��֤ɢ�б���󳤶������������������5.3 */
    H->TableSize = NextPrime(TableSize);
 
    /* ���·�������ͷ������� */
    H->Heads = (List)malloc(H->TableSize*sizeof(struct LNode));
    /* ��ʼ����ͷ��� */
    for( i=0; i<H->TableSize; i++ ) {
		H->Heads[i].Data[0] = '\0';
		H->Heads[i].Next = NULL;
		H->Heads[i].Count = 0;
    }
 
    return H;
}
 
Position Find( HashTable H, ElementType Key )
{
    Position P;
    Index Pos;
     
    Pos = Hash( atoi(Key + KEYLENGTH - MAXD), H->TableSize ); /* ��ʼɢ��λ�� */
    
	P = H->Heads[Pos].Next; /* �Ӹ�����ĵ�1����㿪ʼ */
    /* ��δ����β������Keyδ�ҵ�ʱ */ 
    while( P && strcmp(P->Data, Key) )
        P = P->Next;
 
    return P; /* ��ʱP����ָ���ҵ��Ľ�㣬����ΪNULL */
}
 
bool Insert( HashTable H, ElementType Key )
{
    Position P, NewCell;
    Index Pos;
     
    P = Find( H, Key );
    if ( !P ) { /* �ؼ���δ�ҵ������Բ��� */
        NewCell = (Position)malloc(sizeof(struct LNode));
        strcpy(NewCell->Data, Key);
        NewCell->Count = 1;
        Pos = Hash( atoi(Key + KEYLENGTH - MAXD), H->TableSize ); /* ��ʼɢ��λ�� */
        /* ��NewCell����ΪH->Heads[Pos]����ĵ�1����� */
        NewCell->Next = H->Heads[Pos].Next;
        H->Heads[Pos].Next = NewCell; 
        return true;
    }
    else { /* �ؼ����Ѵ��� */
        P->Count++;
        return false;
    }
}
 
void DestroyTable( HashTable H )
{
    int i;
    Position P, Tmp;
     
    /* �ͷ�ÿ������Ľ�� */
    for( i=0; i<H->TableSize; i++ ) {
        P = H->Heads[i].Next;
        while( P ) {
            Tmp = P->Next;
            free( P );
            P = Tmp;
        }
    }
    free( H->Heads ); /* �ͷ�ͷ������� */
    free( H );        /* �ͷ�ɢ�б��� */
}



void ScanAndOutput(HashTable H) {
	int i, MaxCnt = 0, PCnt = 0;
	ElementType MinPhone;
	List Ptr;
	MinPhone[0] = '\0';

	for ( i = 0; i < H->TableSize; i++) {
		Ptr = H->Heads[i].Next;
		while(Ptr) {
			if (Ptr->Count > MaxCnt) {
				MaxCnt = Ptr->Count;
				strcpy(MinPhone, Ptr->Data);
				PCnt = 1;
			}
			else if (Ptr->Count == MaxCnt) {
				PCnt++;
				if (strcmp(MinPhone, Ptr->Data)>0){
					strcpy(MinPhone, Ptr->Data);
				}
			}
			Ptr = Ptr->Next;
		}
	}
	printf("%s %d", MinPhone, MaxCnt);
	if (PCnt > 1) {
		printf(" %d", PCnt);
	}
	printf("\n");
}

int NextPrime( int N )
{ /* ���ش���N�Ҳ�����MAXTABLESIZE����С���� */
    int i, p = (N%2)? N+2 : N+1; /*�Ӵ���N����һ��������ʼ */
 
    while( p <= MAXTABLESIZE ) {
        for( i=(int)sqrt(p); i>2; i-- )
            if ( !(p%i) ) break; /* p�������� */
        if ( i==2 ) break; /* for����������˵��p������ */
        else  p += 2; /* ������̽��һ������ */
    }
    return p;
}








