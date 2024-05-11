#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#define M 20
#define N 20

static const double epsilon = 1.0e-8;
int equal(double a, double b) { return fabs(a-b) < epsilon; }
#define MAX 10e8

typedef struct {
  int m, n; // m=rows, n=columns, linear[m x n]
  double linear[M][N];
  int sign[M];
} Tableau;


//Ham in mau
//void setcolor(int backgound_color, int text_color);

//Ham gioi thieu
void infor();
//Ham menu yeu cau dau vao
void menuin(float &com);
//Ham menu yeu cau file muon nhap
void menuFILE(float &v);
//Ham nhap file da chon
void Nhapfile(float *a, int &n, int v);
void print_tableau(Tableau *tab, const char* mes);
void read_tableau(Tableau *tab, const char * filename);
void pivot_on(Tableau *tab, int row, int col);
int find_pivot_column(Tableau *tab);
int find_pivot_row(Tableau *tab, int pivot_col);
void add_slack_variables(Tableau *tab);
void big_M(Tableau* tab);
int find_basis_variable(Tableau *tab, int col);
void print_optimal_vector(Tableau *tab, char *message);
void simplex(Tableau *tab);
void nl(int k);

Tableau tab  = { 3, 3, {                     
    {  0.0 , -3.0 , -2.0,   },  
    { 9.0 ,  2.0 ,  1.0 ,   }, 
    { 9.0 , 1.0 , 2.0 ,   }, 
  },
  { -1 , 1 , 1 }
//  0 : equal; -1 : smaller or equal; 1 : bigger or equal
};

int main(int argc, char *argv[]){
    infor(); //Gioi thieu
    if (argc > 1) { // usage: cmd datafile
       read_tableau(&tab, argv[1]);
    }
    print_tableau(&tab,"Initial");
    simplex(&tab);
    return 0;
} 
void nl(int k){ int j; for(j=0;j<k;j++) putchar('-'); putchar('\n'); }
void print_tableau(Tableau *tab, const char* mes) {
  static int counter=0;
  int i, j;
  printf("\n%d. Tableau %s:\n", ++counter, mes);
  nl(70);

  printf("%-6s%5s", "col:", "b[i]");
  for(j=1;j<tab->n; j++) { printf("    x%d,", j); } printf("\n");

  for(i=0;i<tab->m; i++) {
    if (i==0) printf("max:"); else
    printf("b%d: ", i);
    for(j=0;j<tab->n; j++) {
      if (equal((int)tab->linear[i][j], tab->linear[i][j]))
        printf(" %6d", (int)tab->linear[i][j]);
      else
        printf(" %6.2lf", tab->linear[i][j]);
      }
    printf("\n");
  }
  nl(70);
}

/* Example input file for read_tableau:
     4 5
      0   -0.5  -3 -1  -4 
     40    1     1  1   1 
     10   -2    -1  1   1 
     10    0     1  0  -1  
     0	   -1    0  1   0
*/
void read_tableau(Tableau *tab, const char * filename) {
  int err, i, j;
  FILE * fp;

  fp  = fopen(filename, "r" );
  if( !fp ) {
    printf("Cannot read %s\n", filename); exit(1);
  }
  memset(tab, 0, sizeof(*tab));
  err = fscanf(fp, "%d %d", &tab->m, &tab->n);
  if (err == 0 || err == EOF) {
    printf("Cannot read m or n\n"); exit(1);
  }
  for(i=0;i<tab->m; i++) {
    for(j=0;j<tab->n; j++) {
      err = fscanf(fp, "%lf", &tab->linear[i][j]);
      if (err == 0 || err == EOF) {
        printf("Cannot read A[%d][%d]\n", i, j); exit(1);
      }
    }
  }
  
  printf("Read tableau [%d rows x %d columns] from file '%s'.\n",
    tab->m, tab->n, filename);
  fclose(fp);
}

void pivot_on(Tableau *tab, int row, int col) {
  int i, j;
  double pivot;

  pivot = tab->linear[row][col];
  assert(pivot>0);
  for(j=0;j<tab->n;j++)
    tab->linear[row][j] /= pivot;
  assert( equal(tab->linear[row][col], 1. ));

  for(i=0; i<tab->m; i++) { // foreach remaining row i do
    double multiplier = tab->linear[i][col];
    if(i==row) continue;
    for(j=0; j<tab->n; j++) { // r[i] = r[i] - z * r[row];
      tab->linear[i][j] -= multiplier * tab->linear[row][j];
    }
  }
}

// Find pivot_col = most negative column in linear[0][1..n]
int find_pivot_column(Tableau *tab) {
  int j, pivot_col = 1;
  double lowest = tab->linear[0][pivot_col];
  // 1 -> n col max
  for(j=1; j<tab->n; j++) {
    if (tab->linear[0][j] < lowest) {
      lowest = tab->linear[0][j];
      pivot_col = j;
    }
  }
//  printf("Most negative column in row[0] is col %d = %g.\n", pivot_col, lowest);
  if( lowest >= 0 ) {
    return -1; // All positive columns in row[0], this is optimal.
  }
  return pivot_col;
}

// Find the pivot_row, with smallest positive ratio = col[0] / col[pivot]
int find_pivot_row(Tableau *tab, int pivot_col) {
  int i, pivot_row = 0;
  double min_ratio = -1;
// printf("Ratios = [",pivot_col);
// devide tab->linear[i][0] to tab->linear[i][pivot_col]
  for(i=1;i<tab->m;i++){
  	if (i>1) printf(", ");
    double ratio = tab->linear[i][0] / tab->linear[i][pivot_col];
    printf("%3.2lf", ratio);
    if ( (ratio > 0  && ratio < min_ratio ) || min_ratio < 0 ) {
      min_ratio = ratio;
      pivot_row = i;
    }
  }
  printf("].\n");
  if (min_ratio == -1)
    return -1; // Unbounded.
//  printf("Found pivot A[%d,%d], min positive ratio=%g in row=%d.\n",
//      pivot_row, pivot_col, min_ratio, pivot_row);
  return pivot_row;
}

void add_slack_variables(Tableau *tab) {
    int i, j;
    int row, count = 0;
    long long max = -MAX;
    for (i=1; i<=tab->m; i++ ){
    	if (tab->sign[i] == 1){
    		count++;
    		if(tab->linear[i][0] > max){
    			max = tab->linear[i][0];
    			row = i;
			}
		}
	}
    for(i=1; i<tab->m; i++) {
        for(j=1; j<tab->m; j++)	{
    	   if (tab->sign[i] == 0) continue;
		   if (tab->sign[i] == 1 && (i==j)) tab->linear[0][j+tab->n-1] = MAX;
		   tab->linear[i][j + tab->n -1] = (i==j);
	    }
    }
	count > 0? tab->n += tab->m : tab->n += tab->m -1;
    if (count > 0) for (i = 1; i < tab->m; i++){
    	if (i!=row) tab->linear[i][tab->n-1] = 0;
    	else if (row == i) tab->linear[i][tab->n-1] = -1;
	}
}

void big_M(Tableau* tab){
	int count = 0 ;
	for (int i = 1; i < tab->m; i++){if (tab->sign[i] == 1) count++;};
	if (count == 0) return;
	for (int i = tab->n-tab->m; i < tab->n-1; i++){
		if (tab->linear[0][i] == MAX){
			for (int j = 1; j < tab->m; j++){
				if (tab->linear[j][i]==1){
					for (int k = 1; k<tab->n; k++){
						tab->linear[0][k] += (-1)*MAX*tab->linear[j][k];
					}
				}
			}
		}
	}
	print_tableau(tab,"a");
}

void check_b_positive(Tableau *tab) {
  int i;
  for(i=1; i<tab->m; i++)
    assert(tab->linear[i][0] >= 0);
}

// Given a column of identity linearrix, find the row containing 1.
// return -1, if the column as not from an identity linearrix.
int find_basis_variable(Tableau *tab, int col) {
  int i, xi=-1;
  for(i=1; i < tab->m; i++) {
    if (equal( tab->linear[i][col],1) ) {
      if (xi == -1)
        xi=i;   // found first '1', save this row number.
      else
        return -1; // found second '1', not an identity linearrix.

    } else if (!equal( tab->linear[i][col],0) ) {
      return -1; // not an identity linearrix column.
    }
  }
  return xi;
}

void print_optimal_vector(Tableau *tab, char *message) {
  int j, xi;
  printf("%s at ", message);
  for(j=1;j<tab->n;j++) { // for each column.
    xi = find_basis_variable(tab, j);
    if (xi != -1)
      printf("x%d=%3.2lf, ", j, tab->linear[xi][0] );
    else
      printf("x%d=0, ", j);
  }
  printf("\n");
} 

void simplex(Tableau *tab) {
  int loop=0;
  add_slack_variables(tab);
  check_b_positive(tab);
  print_tableau(tab,"Padded with slack variables");
  big_M(tab);
  while( ++loop ) {
    int pivot_col, pivot_row;

    pivot_col = find_pivot_column(tab);
    if( pivot_col < 0 ) {
//      printf("Found optimal value=A[0,0]=%3.2lf (no negatives in row 0).\n",
//        tab->linear[0][0]);
      print_optimal_vector(tab, "Optimal vector");
      break;
    }
//    printf("Entering variable x%d to be made basic, so pivot_col=%d.\n",
//      pivot_col, pivot_col);

    pivot_row = find_pivot_row(tab, pivot_col);
    if (pivot_row < 0) {
      printf("unbounded (no pivot_row).\n");
      break;
    }
//    printf("Leaving variable x%d, so pivot_row=%d\n", pivot_row, pivot_row);

    pivot_on(tab, pivot_row, pivot_col);
    print_tableau(tab,"After pivoting");
//    print_optimal_vector(tab, "Basic feasible solution");

    if(loop > 20) {
      printf("Too many iterations > %d.\n", loop);
      break;
    }
  }
}

void Nhapfile(float *a, int &n, int v){
	FILE *fi;
    if(v==1)fi=fopen("TEST1.txt","r");
    if(v==2)fi=fopen("TEST2.txt","r");
	if(v==3)fi=fopen("TEST3.txt","r");
	if(v==4)fi=fopen("TEST4.txt","r");
	if(v==5)fi=fopen("TEST5.txt","r");
	if(v==6)fi=fopen("TEST6.txt","r");
	if(v==7)fi=fopen("TEST7.txt","r");
	if(v==8)fi=fopen("TEST8.txt","r");
	if(v==9)fi=fopen("TEST9.txt","r");
	if(v==10)fi=fopen("TEST10.txt","r");
    printf("\nBac phuong trinh: ");
    fscanf(fi,"%d", &n);
    printf("%d", n);
    printf("\nCac he so cua phuong trinh bac %d: ", n);
    for(int i = 0 ; i <= n ; i++){
        fscanf(fi,"%f", a+i);
        if(*(a+i)==(int)(*(a+i))){
            printf("%d ",(int)(*(a+i)));
        }else printf("%f ",*(a+i));
    }
}
//Ham menu yeu cau file muon nhap
void menuFILE(float &v){
//	setcolor(0,2);
 	printf("\n                                  %c   CHON FILE DE LAY DU LIEU    %c\n",16,17);
 	printf("\n                           Nhan 1 : TEST1                 Nhan 2: TEST2 ");
	printf("\n                           Nhan 3 : TEST3                 Nhan 4: TEST4 ");
	printf("\n                           Nhan 5 : TEST5                 Nhan 6: TEST6 ");
	printf("\n                           Nhan 7 : TEST7                 Nhan 8: TEST8 ");
	printf("\n                           Nhan 9 : TEST9                 Nhan 10: TEST10");
	printf("\n                                             -------\n");
//	setcolor(0,8);
	printf("\n          Nhap file test (1-10): ");
	do{
		scanf("%f", &v);
		if(v!=1 && v!=2 && v!=3 && v!=4 && v!=5 && v!=6 && v!=7 && v!=8 && v!=9 && v!=10) printf("\nMoi ban nhap lai so thu tu file: ");
	}while(v!=1 && v!=2 && v!=3 && v!=4 && v!=5 && v!=6 && v!=7 && v!=8 && v!=9 && v!=10);
}

void infor(){
 	int i;
// 	setcolor(0,9);
 	printf("\n%9c",201);
 	for (i=0;i<=85;i++) printf("%c",205);
 	printf("%c",187);
 	printf("\n        %c %86c",4,4);
 	printf("\n        %c                             DO AN LAP TRINH TINH TOAN                                %c",4,4);
 	printf("\n        %c                     DE TAI: Toi uu tuyen tinh Simplex - Big_M              %c",4,4);
 	printf("\n        %c %86c",4,4);
 	printf("\n        %c       Sinh vien thuc hien:                       Giao vien huong dan:                %c",4,4);
 	printf("\n        %c           %c Nguyen Dinh Duy                       %c Phan Thanh Tao                 %c",4,45,45,4);
 	printf("\n        %c           %c Tran Van Minh Tri  %60c",4,45,4);
 	printf("\n        %c %86c",4,4);
 	printf("\n        %c",200);
 	for (i=0;i<=85;i++) printf("%c",205);
 	printf("%c\n",188);
}

////Ham in mau
//void setcolor(int backgound_color, int text_color){
//    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//    int color_code = backgound_color * 16 + text_color;
//    SetConsoleTextAttribute(hStdout, color_code);
//}

void menuin(float &com){
//    setcolor(0,14);
 	printf("\n                                  %c   CHON CACH NHAP DU LIEU   %c\n",16,17);
 	printf("\n                                        Nhap 1: Tu ban phim");
	printf("\n                                        Nhap 2: Tu file");
	printf("\n                                    Nhan phim bat ky de Ket thuc");
	printf("\n                                             -------\n");
//	setcolor(0,8);
	printf("\n          Nhap yeu cau: ");
	do{
		scanf("%f", &com);
		if(com != 1 && com != 2) printf("\nMoi ban nhap lai: ");
	}while(com != 1 && com != 2);
}


