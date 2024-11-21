#include <stdio.h>
int gcd(int a,int b) 
{
    int temp;
    while(b!=0) 
    {
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}
int modInverse(int a,int m) 
{
    a=a%m;
    for(int x=1;x<m;x++) 
    {
        if((a*x)%m==1) 
        {
            return x;
        }
    }
    return -1;
}
void decrypt_affine(char ciphertext[],int a,int b) 
{
    int m=26;
    int a_inv=modInverse(a,m);
    if(a_inv==-1) 
    {
        printf("\nInvalid key\n");
        return;
    }
    int i=0;
    while(ciphertext[i]) 
    {
        if (ciphertext[i]>='A'&&ciphertext[i]<='Z') 
        {
            char decrypted_char='A'+(a_inv*((ciphertext[i]-'A'-b+m)%m))%m;
            printf("%c",decrypted_char);
        }
        else 
        {
            printf("%c",ciphertext[i]);
        }
        i++;
    }
    printf("\n");
}
int main() 
{
    char ciphertext[]="BU";
    int a=19;
    int b=3;
    decrypt_affine(ciphertext,a,b);
}