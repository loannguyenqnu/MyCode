#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 5 
//hello
typedef struct{
char ngay[3];
char thang[3];
char nam[5];
}NgaySinh;
typedef struct{
    char hoten[50];
    NgaySinh ngaySinh;
    int gioiTinh; //1. nam 0. nu
    double diemTB;
}QuanLySV;
typedef struct{
    QuanLySV *data;
    int capacity;
    int size;
}Vector;
void init_Vector(Vector *v){
    v->capacity=MAX_SIZE;
    v->size=0;
    v->data=(QuanLySV*)malloc(v->capacity*sizeof(QuanLySV));
    if(v->data==NULL){
        exit(1);
    }
}
void freeVector(Vector *v){
    free(v->data);
    v->data=NULL;
    v->capacity=0;
    v->size=0;
}
void resize_Vector(Vector *v){
    v->capacity*=2;
    QuanLySV *new_data=(QuanLySV*)realloc(v->data, v->capacity*sizeof(QuanLySV));
    v->data=new_data;
}
void push_Back_V(Vector *v, QuanLySV value){
    if(v->capacity==v->size){
        resize_Vector(v);
    }
    v->data[v->size]=value;
    v->size++;
}
void pop_Back_V(Vector *v){
        if(v->size>0){
            v->size--;
        }
}
void pop_index_V(Vector *v, int index){
    if(index<0 || index>=v->size){
        printf("Nhap sai index!\n");
        return;
    }
    if(index==v->size-1){
        pop_Back_V(v);
        return;
    }
    memmove(&v->data[index], &v->data[index+1], (v->size-index-1)*sizeof(QuanLySV));
    v->size--;
}
/*
void pop_index_V(Vector *v, int index){
    if(index < 0 || index >= v->size){
        printf("Nhap sai index!\n");
        return;
    }
    if(index == v->size - 1){
        pop_Back_V(v);
        return;
    }
    for(int i = index; i < v->size - 1; i++){
        v->data[i] = v->data[i + 1];
    }
    v->size--;
}
*/
void nhapNgaySinh(NgaySinh *ns){
    printf("Nhap ngay (dd): ");
    scanf("%2s", ns->ngay);
    printf("Nhap thang (mm): ");
    scanf("%2s", ns->thang);
    printf("Nhap nam (yyyy): ");
    scanf("%4s", ns->nam);
}
void hienThiNgaySinh(NgaySinh ns) {
    printf("%s/%s/%s", ns.ngay, ns.thang, ns.nam);
}
void nhapSinhVien(QuanLySV *sv){
    printf("Nhap ho ten: ");
    fgets(sv->hoten, 50, stdin);
    int len = strlen(sv->hoten);
    if (len > 0 && sv->hoten[len-1] == '\n') {
        sv->hoten[len-1] = '\0';
    }
    printf("Nhap ngay sinh:\n");
    nhapNgaySinh(&sv->ngaySinh);
    printf("Nhap gioi tinh (1-Nam, 0-Nu): ");
    scanf("%d", &sv->gioiTinh);
    printf("Nhap diem trung binh: ");
    scanf("%lf", &sv->diemTB);
    getchar();
}

void themSV(Vector *v){
    QuanLySV sv;
    nhapSinhVien(&sv);
    push_Back_V(v, sv);
    printf("Them sinh vien thanh cong!\n");
}

void inDSSinhvien(Vector v){
    if(v.size==0){
        printf("Danh sach sinh vien rong\n");
        return;
    }
    printf("---Danh sach sinh vien---\n");
    for(int i=0; i<v.size; i++){
        printf("%d. %s\n", i+1, v.data[i].hoten);
        hienThiNgaySinh(v.data[i].ngaySinh);
        printf("Gioi tinh: %s\n", v.data[i].gioiTinh ? "Nam\n":"Nu\n");
        printf("Diem trung binh: %.2f\n", v.data[i].diemTB);
        printf("-------------------------------------------\n");
    }
}
void xoaSV_theoIndex(Vector *v, int index){
    if(index < 0 || index >= v->size){
        printf("Index khong hop le!\n");
        return;
    }
    printf("Da xoa sinh vien: %s\n", v->data[index].hoten);
    pop_index_V(v, index);
}
void xoaSV_theoTen(Vector *v, char ten[]){
    int found = 0;
    for(int i = 0; i < v->size; i++){
        if(strcmp(v->data[i].hoten, ten) == 0){
            printf("Da xoa sinh vien: %s\n", v->data[i].hoten);
            pop_index_V(v, i);
            i--;
            found = 1;
        }
    }
    if(!found){
        printf("Khong tim thay sinh vien co ten: %s\n", ten);
    }
}
void suaSV_theoIndex(Vector *v, int index){
    if(index < 0 || index >= v->size){
        printf("Index khong hop le!\n");
        return;
    }
    printf("Sua thong tin sinh vien: %s\n", v->data[index].hoten);
    nhapSinhVien(&v->data[index]);
    printf("Sua thong tin thanh cong!\n");
}
void suaSV_theoTen(Vector *v, char ten[]){
    int found = 0;
    for(int i = 0; i < v->size; i++){
        if(strcmp(v->data[i].hoten, ten) == 0){
            printf("Tim thay sinh vien: %s\n", v->data[i].hoten);
            nhapSinhVien(&v->data[i]);
            printf("Sua thong tin thanh cong!\n");
            found = 1;
        }
    }
    if(!found){
        printf("Khong tim thay sinh vien co ten: %s\n", ten);
    }
}
void timKiem_theoTen(Vector *v, char ten[]){
    int found = 0;
    printf("\n=== KET QUA TIM KIEM THEO TEN: %s ===\n", ten);
    for(int i = 0; i < v->size; i++){
        if(strcmp(v->data[i].hoten, ten) == 0){
            printf("%d. %s - ", i + 1, v->data[i].hoten);
            hienThiNgaySinh(v->data[i].ngaySinh);
            printf(" - %s - %.2lf\n",
                   v->data[i].gioiTinh ? "Nam" : "Nu",
                   v->data[i].diemTB);
            found = 1;
        }
    }
    if(!found){
        printf("Khong tim thay sinh vien co ten: %s\n", ten);
    }
}
void timKiem_theoDiem(Vector *v, double min, double max){
    int found = 0;
    printf("\n=== KET QUA TIM KIEM THEO DIEM (%.1lf - %.1lf) ===\n", min, max);
    for(int i = 0; i < v->size; i++){
        if(v->data[i].diemTB >= min && v->data[i].diemTB <= max){
            printf("%d. %s - ", i + 1, v->data[i].hoten);
            hienThiNgaySinh(v->data[i].ngaySinh);
            printf(" - %s - %.2lf\n",
                   v->data[i].gioiTinh ? "Nam" : "Nu",
                   v->data[i].diemTB);
            found = 1;
        }
    }
    if(!found){
        printf("Khong tim thay sinh vien trong khoang diem %.1lf - %.1lf\n", min, max);
    }
}
void sapXepTheoDiem(Vector *v){
    for(int i = 0; i < v->size - 1; i++){
        for(int j = 0; j < v->size - i - 1; j++){
            if(v->data[j].diemTB < v->data[j + 1].diemTB){
                QuanLySV temp = v->data[j];
                v->data[j] = v->data[j + 1];
                v->data[j + 1] = temp;
            }
        }
    }
    printf("Da sap xep theo diem trung binh giam dan!\n");
}
void layTen(char *hoten, char *ten) {
    int len = strlen(hoten);
    int vitriTen = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (hoten[i] == ' ') {
            vitriTen = i + 1;
            break;
        }
    }
    strcpy(ten, &hoten[vitriTen]);
}
void sapXepTheoTen(Vector *v){
    for(int i = 0; i < v->size - 1; i++){
        for(int j = 0; j < v->size - i - 1; j++){
            char ten1[50], ten2[50];
            layTen(v->data[j].hoten, ten1);
            layTen(v->data[j + 1].hoten, ten2);

            if(strcmp(ten1, ten2) > 0){
                QuanLySV temp = v->data[j];
                v->data[j] = v->data[j + 1];
                v->data[j + 1] = temp;
            }
        }
    }
    printf("Da sap xep theo ten A-Z!\n");
}
void displayMenu(){
    printf("\n=== QUAN LY SINH VIEN ===\n");
    printf("1. Them sinh vien\n");
    printf("2. Hien thi danh sach\n");
    printf("3. Xoa sinh vien theo index\n");
    printf("4. Xoa sinh vien theo ten\n");
    printf("5. Sua sinh vien theo index\n");
    printf("6. Sua sinh vien theo ten\n");
    printf("7. Tim kiem theo ten\n");
    printf("8. Tim kiem theo khoang diem\n");
    printf("9. Sap xep theo diem\n");
    printf("10. Sap xep theo ten\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

int main(){
    Vector danhSachSV;
    init_Vector(&danhSachSV);
    int choice;
    do{
        displayMenu();
        scanf("%d", &choice);
        getchar();

        switch(choice){
            case 1:
                themSV(&danhSachSV);
                break;
            case 2:
                inDSSinhvien(danhSachSV);
                break;
            case 3:{
                int index;
                printf("Nhap index can xoa: ");
                scanf("%d", &index);
                getchar();
                xoaSV_theoIndex(&danhSachSV, index - 1);
                break;
            }
            case 4:{
                char ten[50];
                printf("Nhap ten can xoa: ");
                fgets(ten, 50, stdin);
                ten[strcspn(ten, "\n")] = 0;
                xoaSV_theoTen(&danhSachSV, ten);
                break;
            }
            case 5:{
                int index;
                printf("Nhap index can sua: ");
                scanf("%d", &index);
                getchar();
                suaSV_theoIndex(&danhSachSV, index - 1);
                break;
            }
            case 6:{
                char ten[50];
                printf("Nhap ten can sua: ");
                fgets(ten, 50, stdin);
                ten[strcspn(ten, "\n")] = 0;
                suaSV_theoTen(&danhSachSV, ten);
                break;
            }
            case 7:{
                char ten[50];
                printf("Nhap ten can tim: ");
                fgets(ten, 50, stdin);
                ten[strcspn(ten, "\n")] = 0;
                timKiem_theoTen(&danhSachSV, ten);
                break;
            }
            case 8:{
                double min, max;
                printf("Nhap diem toi thieu: ");
                scanf("%lf", &min);
                printf("Nhap diem toi da: ");
                scanf("%lf", &max);
                getchar();
                timKiem_theoDiem(&danhSachSV, min, max);
                break;
            }
            case 9:
                sapXepTheoDiem(&danhSachSV);
                break;
            case 10:
                sapXepTheoTen(&danhSachSV);
                break;
            case 0:
                printf("Thoat chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }while(choice != 0);

    freeVector(&danhSachSV);
    return 0;
}

