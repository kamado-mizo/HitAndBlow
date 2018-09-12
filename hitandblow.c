#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#define TRUE 1  //���茋�ʂ킩��₷���悤�ɒu������
#define FALSE 0 //���茋�ʂ킩��₷���悤�ɒu������

int ketacheck(char*); ////�����`�F�b�N�֐��̃v���g�^�C�v�錾
int repecheck(char*); //�d���`�F�b�N�֐��̃v���g�^�C�v�錾
void ransu(char*); //���������֐��̃v���g�^�C�v�錾
int blowcheck(char*,char*);
int hitcheck(char*,char*);
int digitcheck(char*);//�����`�F�b�N�֐��̃v���g�^�C�v�錾


struct LIST{ //�����擾�̂��߂̍\���̂̐錾

	char number;
	struct LIST *next;//���̃|�C���^

};


void main(void){

	int incheck, i, r_check, *Pkey, check, blow, hit, in_judge;
	char in[10], *Pin, key[5]={"0000\0"};

	/* �����̎�������� */
	srand(time(NULL));

	printf("\t////////////////////////////////\n");
	printf("\n\t\tHit and Blow\n");
	printf("\n\t////////////////////////////////\n");

	ransu(key);//������key�z��Ɋi�[
while(hit != 4){


	printf("\n4���̒l����͂��Ă�������\n->");
	scanf("%s",&in);
	Pin = in; //���͔z��̃A�h���X����
	incheck = ketacheck(Pin); //���͔z��A�h���X�������`�F�b�N�ɓn��
	r_check = repecheck(Pin); //�V�d���`�F�b�N�ɓn��
	in_judge = digitcheck(Pin); //�V�j���[�����b�N�`�F�b�N�ɓn��

while(incheck != 1 || r_check != 1 || in_judge == 0){
	while(incheck != 1){

		printf("������4���ł͂���܂���A������x���͂��Ă��������B\n->");
		scanf("%s",&in);
		Pin = in; //���͔z��̃A�h���X����
		incheck = ketacheck(Pin); //���͔z��A�h���X�������`�F�b�N�ɓn��]

		}

	
	while(r_check != 1){

		printf("���͒l���d�����Ă��܂��A������x���͂��Ă��������B\n->");
		scanf("%s",&in);
		Pin = in; //�����`�F�b�N�֐��{��
		r_check = repecheck(Pin); //������4���̏ꍇ
		}
	
	while(in_judge == 0){
		printf("��������͂��Ă�������\n->");
		scanf("%s",&in);
		Pin = in;
		in_judge = digitcheck(Pin);
	}
	incheck = ketacheck(Pin); //���͔z��A�h���X�������`�F�b�N�ɓn��
	r_check = repecheck(Pin); //�V�d���`�F�b�N�ɓn��
	in_judge = digitcheck(Pin); //�V�j���[�����b�N�`�F�b�N�ɓn��
}

	hit = hitcheck(in, key);
	blow = blowcheck(in, key);
	printf("\n+++�I����I+++\n");
	printf("(^o^) < blow %d\n", (blow-hit));
	printf("(>o<) < hit %d\n",hit);
	if(hit == 3){
		printf("���Ƃ������I����΂��ā`\n");
	}
}
printf("���߂łƂ��������܂��I���������I\n������\n");
for(i=0;i<4;i++){
	printf("%c",key[i]);
}
printf("�ł����I");
}


int ketacheck(char *p){ //�����`�F�b�N�֐��{��

	int cnt;

	for(cnt = 1 ; *p != '\0' ;){

		if(cnt == 4 && *(p+1) == '\0'){
			return TRUE;//������4���̏ꍇ
		}

		p++;
		cnt++;
	}

return FALSE;//������4���ȊO�̏ꍇ
}


int repecheck(char *p){ //�d���`�F�b�N�֐��{��

	int flg[10]={0,0,0,0,0,0,0,0,0,0}, cnt, i;

	for(cnt = 0; cnt < 4; cnt++ , p++){
		i = *p - '0';
		flg[i]++;//�o�������̔z��v�f�ɉ��Z���Ă���
	}

	for(cnt = 0; cnt < 10; cnt++){

		if(flg[cnt] > 1){ //�d�����Ă����ꍇ,���ȏ�ł�
			return FALSE;
		}
	}
	return TRUE; //�d�����Ă��Ȃ��ꍇ
}


void ransu(char *P_key){

	int r, i, key_cnt;
	char r_number;
	struct LIST *crr;
	struct LIST *head;
	struct LIST *prev;

	/*�@static�Ȃ̂Ŕz��̕ύX�͕ێ������@*/
	static struct LIST data[10] = { //�\���̂̏����l�ݒ�

		{'0',&data[1]},
		{'1',&data[2]},
		{'2',&data[3]},
		{'3',&data[4]},
		{'4',&data[5]},
		{'5',&data[6]},
		{'6',&data[7]},
		{'7',&data[8]},
		{'8',&data[9]},
		{'9',&data[0]}//�z��
	};

	head = &data[0]; // head�Ƀ��X�g�\���̔z��̐擪�A�h���X���Z�b�g


	for( key_cnt = 0; key_cnt < 4; key_cnt++ ){

		crr = head;
		data[9].next = head;

		r = rand() % 10; //�������Ƃ鏈��

		for( i = 0; i < (r + 1); ++i ){

			prev = crr;
			crr = crr->next;

		}

		r_number = crr->number;
		*(P_key++) = r_number;//key�z��ɓ���鏈��

		if(head == crr){//�擪���Ƃ����Ƃ�
			head = crr->next;


		}else if(crr->next == head){//�Ō���Ƃ����Ƃ�

			prev->next = head; //�z���邽�߂ɑO�̎��|�C���^��head�ɕt���ւ���

		}
		else{//�r���̎�
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