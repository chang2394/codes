///   CONVERSIONS  ..........

Conversion from DOUBLE TO INT :-
double f;
scanf("%lf",&f);
return (LL)((f+1e-9)*100.0);

Here DOUBLE val is multiplied by 100 and corresponding int returned .

Conversion from INT TO DOUBLE or Division of a DOUBLE :-

printf("%0.2lf\n",sum/100.0 + 1e-9);

Here divided by 100

Code :- http://ideone.com/GFaK0u 


///   SCANF WITH NEWLINE .......
scanf("%[^\n]%*c",str);


///   FAST INPUT AND OUTPUT ....

int scan_d()    {int ip=getchar_unlocked(),ret=0,flag=1;for(;ip<'0'||ip>'9';ip=getchar_unlocked())if(ip=='-'){flag=-1;ip=getchar_unlocked();break;}for(;ip>='0'&&ip<='9';ip=getchar_unlocked())ret=ret*10+ip-'0';return flag*ret;}

void print_d(int n)     {if(n<0){n=-n;putchar_unlocked('-');}int i=10;char output_buffer[10];do{output_buffer[--i]=(n%10)+'0';n/=10;}while(n);do{putchar_unlocked(output_buffer[i]);}while(++i<10);}
