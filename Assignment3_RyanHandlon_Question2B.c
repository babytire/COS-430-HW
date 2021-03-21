#include <stdio.h>
#include <string.h>




int copy_buf(char *to, int pos, char *from) {

	int i;

	for (i=0; i<strlen(&from); i++) {
		if(pos > strlen(&to)) {
			break;
		}
		to[pos] = from[i];
		pos++;
	}
	return pos;



}
