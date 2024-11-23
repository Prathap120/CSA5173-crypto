#include<stdio.h>
#include<math.h>
int main(){
	int q=11,g=2;
	int xa,xb;
	int ya,yb;
	int ka,kb;
	printf("enter sender private  key \n");
	scanf("%d",&xa);
	printf("enter receiver private  key \n");
	scanf("%d",&xb);
	int a = pow(g,xa);
	ya = a % q ;
	int b = pow(g,xb);
	yb = b % q;
	printf("public key of sender is %d",ya);
	printf("public key of reciver is %d",yb);
	int c = pow(ya,xb);
	int d = pow(yb,xa);
	ka = c % q;
	kb = d % q;
	if(ka == kb){
		printf("passes");
	}else{
		printf("failed");
	}
	return 0;
}
