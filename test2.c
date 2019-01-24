#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ON 1
#define OFF 0

//  配列の最大の大きさ
#define MAX_LENGTH  100
 
typedef struct{
    //  データを格納数る配列
    int array[MAX_LENGTH];
    //  現在の位置
    int current;
}STACK;

//  スタックの初期化
void init(STACK*);
//  値のプッシュ
int push(STACK*,int);
//  値のポップ
int pop(STACK*,int*);


int main(void){

	char s[80];
	STACK sta;
	int i=0;
	int j=0;
	int flag=0;
	int a,b,value;
	char ch[80];
	char *p;
  	int space;  /* 文字がスペースかそうでないか */
  	char c;
  	size_t length;
	
	init(&sta);   //  スタックを初期化

	printf("条件\n *式は一行に一つとする\n *一行は80文字以内とし、行末には改行文字がある\n *符号の付いた数は考えないことにする\n *数値と数値、数値と演算子、演算子と演算子の間には１個以上の空白を置くこととする\n");
	printf("入力 : ");

    fgets(s, sizeof(s), stdin);



    space = OFF;

    while(s[i]){
    	if (space == OFF && s[i] == ' ') { /* cがスペースであり、かつ、直前がスペースでない */
	      	//printf(" ");                  /* スペースを出力する */
	      	space = ON;                   /* spaceをONに。「スペースが続いている」 */
    		ch[j]=' ';
    		j++;
	    } else if (s[i] != ' ') {          /* 今までスペースだった、かつ、文字の時 */
	      	space = OFF;                  /* spaceをOFFに。「スペースは続いてない」 */
	      	//printf("%c", s[i]);              /* 文字を出力する */
	      	ch[j]=s[i];
    		j++;
	    }
	    i++;
    }
    i = strlen(s);
    while(i!=0){
    	if(s[i]==' '){
    		s[i]='\n';
    	}else{
    		break;
    	}
    	i--;
    }

    p = strtok(ch," ");
   	if(isdigit(*p)){
   		push(&sta,atoi(p));
   	}else if(*p=='\n'){
   		printf("エンター押したの？なんも入力してないのに？無能なの？？wwwww	\n");
   		flag=1;
   	}else{
   		printf("文字列先頭にきとるぞ？おかしいな？\n");	
   		flag=1;
   	}

    while(p!=NULL){
    	p = strtok(NULL," ");
    	if(p!=NULL){
    		if(isdigit(*p)){
   				push(&sta,atoi(p));
   			}else{ 				
   				switch(*p) {
   					case '+': 			
                        pop(&sta,&value);
                        b = value;
                        pop(&sta,&value);
                        a = value;
                        push(&sta,a+b);
                        break;
                    case '-':
                        pop(&sta,&value);
                        b = value;
                       	pop(&sta,&value);
                       	a = value;
                   		push(&sta,a-b);
             			break;
               		case '*':
                  		pop(&sta,&value);
                  		b = value;
           				pop(&sta,&value);
           				a = value;
                   		push(&sta,a*b);
                        break;
                    case '/':
                 		pop(&sta,&value);
                 		b = value;
               			pop(&sta,&value);
               			a = value;
         				push(&sta,a/b);
     					break;
                   	case ' ':
                        break;
                    case '\n':
                        break;
                    default:
                    	printf("おいおい演算子入力ミスか？1文字以上の空白開けろよぉ〜\n");
                    	flag=1;
                    	break;

                }

   			}
		}
	}

	if(flag==1){
		printf("もう一回やり直せよ。\n");
	}else{
		pop(&sta,&value);
    	printf("結果 : %d\n",value);
    }

    return 0;

}

//  スタックの初期化
void init(STACK* pStack)
{
    int i;
    for(i = 0; i < MAX_LENGTH; i++){
        pStack->array[i] = 0;
    }
    //  カレントの値を0に。
    pStack->current = 0;
}
//  値のプッシュ
int push(STACK* pStack,int value)
{
    if(pStack->current < MAX_LENGTH){
        //  まだデータが格納できるのなら、データを格納し、一つずらす。
        pStack->array[pStack->current] = value;
        pStack->current++;
        return 1;
    }
    //  データを格納しきれなかった
    return 0;
}
//  値のポップ
int pop(STACK* pStack,int* pValue)
{
    if(pStack->current > 0){
        //  まだデータが格納できるのなら、データを格納し、一つずらす。
        pStack->current--;
        *pValue = pStack->array[pStack->current];
        return 1;
    }
    return 0;
}

