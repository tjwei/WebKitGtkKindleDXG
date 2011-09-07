#include <iostream>
extern "C"{
#include "include/chewingio.h"
#include "include/chewing.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
}
using namespace std;
static int selKey_define[ 11 ] = {'a','s','d','f','g','h','j','k','l',';',0};
main(){
	char str[]="nefhwfmys\n";
	cout << "test" <<endl;
	chewing_Init("data/", "mt/");
	ChewingContext *ctx=chewing_new();
	chewing_set_KBType(ctx, chewing_KBStr2Num((char *)"KB_HSU"));
	chewing_set_candPerPage(ctx,9);
	chewing_set_maxChiSymbolLen(ctx, 16);
	chewing_set_addPhraseDirection(ctx,1);
	chewing_set_selKey(ctx, selKey_define, 10);
	chewing_set_spaceAsSelection(ctx, 1);
	for(int i=0;i<strlen(str);i++){
		printf("%c\n",str[i]);
		chewing_handle_Default(ctx, str[i]);
		if(chewing_commit_Check(ctx)){
			char *s=chewing_commit_String(ctx);
			printf("%s\n",s);
			free(s);			
		}
	}

	chewing_handle_Enter( ctx );
	if(chewing_commit_Check(ctx)){
			char *s=chewing_commit_String(ctx);
			printf("%s\n",s);
			free(s);			
		}
	chewing_delete(ctx);
	chewing_Terminate();
}
