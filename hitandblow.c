#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define TRUE 1  //判定結果わかりやすいように置き換え
#define FALSE 0 //判定結果わかりやすいように置き換え

int ketacheck(char*); ////桁数チェック関数のプロトタイプ宣言
int repecheck(char*); //重複チェック関数のプロトタイプ宣言
void ransu(char*); //乱数発生関数のプロトタイプ宣言
int blowcheck(char*,char*);
int hitcheck(char*,char*);
int digitcheck(char*);//数字チェック関数のプロトタイプ宣言


struct LIST{ //乱数取得のための構造体の宣言

	char number;
	struct LIST *next;//次のポインタ

};


void main(void){

	int incheck, i, r_check, *Pkey, check, blow, hit, in_judge;
	char in[10], *Pin, key[5]={"0000\0"};

	/* 乱数の種を初期化 */
	srand(time(NULL));

	printf("\t////////////////////////////////\n");
	printf("\n\t\tHit and Blow\n");
	printf("\n\t////////////////////////////////\n");

	ransu(key);//乱数をkey配列に格納
while(hit != 4){


	printf("\n4桁の値を入力してください\n->");
	scanf("%s",&in);
	Pin = in; //入力配列のアドレスを代入
	incheck = ketacheck(Pin); //入力配列アドレスを桁数チェックに渡す
	r_check = repecheck(Pin); //〃重複チェックに渡す
	in_judge = digitcheck(Pin); //〃ニューメリックチェックに渡す

while(incheck != 1 || r_check != 1 || in_judge == 0){
	while(incheck != 1){

		printf("桁数が4桁ではありません、もう一度入力してください。\n->");
		scanf("%s",&in);
		Pin = in; //入力配列のアドレスを代入
		incheck = ketacheck(Pin); //入力配列アドレスを桁数チェックに渡す]

		}

	
	while(r_check != 1){

		printf("入力値が重複しています、もう一度入力してください。\n->");
		scanf("%s",&in);
		Pin = in; //桁数チェック関数本体
		r_check = repecheck(Pin); //桁数が4桁の場合
		}
	
	while(in_judge == 0){
		printf("数字を入力してください\n->");
		scanf("%s",&in);
		Pin = in;
		in_judge = digitcheck(Pin);
	}
	incheck = ketacheck(Pin); //入力配列アドレスを桁数チェックに渡す
	r_check = repecheck(Pin); //〃重複チェックに渡す
	in_judge = digitcheck(Pin); //〃ニューメリックチェックに渡す
}

	hit = hitcheck(in, key);
	blow = blowcheck(in, key);
	printf("\n+++！判定！+++\n");
	printf("(^o^) < blow %d\n", (blow-hit));
	printf("(>o<) < hit %d\n",hit);
	if(hit == 3){
		printf("あとすこし！がんばって～\n");
	}
}
printf("おめでとうございます！せいかい！\n答えは\n");
for(i=0;i<4;i++){
	printf("%c",key[i]);
}
printf("でした！");
}


int ketacheck(char *p){ //桁数チェック関数本体

	int cnt;

	for(cnt = 1 ; *p != '\0' ;){

		if(cnt == 4 && *(p+1) == '\0'){
			return TRUE;//桁数が4桁の場合
		}

		p++;
		cnt++;
	}

return FALSE;//桁数が4桁以外の場合
}


int repecheck(char *p){ //重複チェック関数本体

	int flg[10]={0,0,0,0,0,0,0,0,0,0}, cnt, i;

	for(cnt = 0; cnt < 4; cnt++ , p++){
		i = *p - '0';
		flg[i]++;//出た数字の配列要素に加算していく
	}

	for(cnt = 0; cnt < 10; cnt++){

		if(flg[cnt] > 1){ //重複していた場合,一回以上でた
			return FALSE;
		}
	}
	return TRUE; //重複していない場合
}


void ransu(char *P_key){

	int r, i, key_cnt;
	char r_number;
	struct LIST *crr;
	struct LIST *head;
	struct LIST *prev;

	/*　staticなので配列の変更は保持される　*/
	static struct LIST data[10] = { //構造体の初期値設定

		{'0',&data[1]},
		{'1',&data[2]},
		{'2',&data[3]},
		{'3',&data[4]},
		{'4',&data[5]},
		{'5',&data[6]},
		{'6',&data[7]},
		{'7',&data[8]},
		{'8',&data[9]},
		{'9',&data[0]}//循環
	};

	head = &data[0]; // headにリスト構造体配列の先頭アドレスをセット


	for( key_cnt = 0; key_cnt < 4; key_cnt++ ){

		crr = head;
		data[9].next = head;

		r = rand() % 10; //乱数をとる処理

		for( i = 0; i < (r + 1); ++i ){

			prev = crr;
			crr = crr->next;

		}

		r_number = crr->number;
		*(P_key++) = r_number;//key配列に入れる処理

		if(head == crr){//先頭をとったとき
			head = crr->next;


		}else if(crr->next == head){//最後をとったとき

			prev->next = head; //循環するために前の次ポインタをheadに付け替える

		}
		else{//途中の時
			prev->next = crr->next;
		}


	}


}

int hitcheck(char *in,char *key){
	int hit,i;
	hit = 0;
	for(i = 0; i < 4; i++){
		
		if(in[i] == key[i]){
			hit++;
		
		}
	}
	return hit;
}

int blowcheck(char *in, char *key){
	int blow, k_check, i_check;
	blow = 0;
	for(k_check = 0; k_check < 4; k_check++){
		
		for(i_check = 0; i_check < 4; i_check++){

			if(key[k_check] == in[i_check]){
				blow++;
			
			}
		}
	}

return blow;
}


int digitcheck(char *in){
	int i = 0,num,judge;
	for(i = 0; i < 4; i++){
		
		num = *(in++);
		judge = isdigit(num);
		
		if(judge == 0){
			return FALSE;
		
		}
	
	}

return TRUE;

}