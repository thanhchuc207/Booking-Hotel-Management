#include <iostream>
#include "DangKi.h"
#include "HoaDon.h"
using namespace std;
#ifndef QLKH_H 
#define QLKH_H 
typedef class QLDK* qldk;

class QLDK
{
    protected:
        int c_KH;// số khách hàng của 1 đăng kí
        int c_HD;//số hóa đơn của 1 đăng kí
        static int c_MKH; // để tạo mã kh
        static int countKH;// tất cả số khách hàng lưu trú
        static int countHD;// tất cả số hóa đơn 
        DangKi data;
    public:
        DSKH* head_KH;    // tro den khach hang dau tien trong dslk khach hang
        QLDK* next_DK; //tro den dang ki tiep theo
        DSHD* head_HD;
        QLDK();
        //tao khach hang dang ki
        QLDK(string MaDK,string TenKH,string CCCD,int SDT, int SLP, int SLN, int GioDK,string NgayDK, Phong *p_dk,string DiaChi="");
        ~QLDK();   
        void XuatDK();// xuất 1 khách hàng đăng kí
        void XuatKH(int &i);// xuất danh sách khách hàng cùng 1 đk
        void XuatHD(int &i); //xuat danh sach hoa don cung 1 dk
        // thêm vào cuối dslk 1 khách hàng (dùng khi đọc và lưu thông tin khách hàng lưu trú từ file đầu vào khách hàng )
        void InsertLastKH(string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen,int GioDi,string NgayDi,string DiaChi,int MaPhong);
        void InsertLastHD(int MaPhong,string NgayDen,string NgayDi);// thêm vào cuối dslk 1 hóa đơn (dùng tạo hóa đơn )
        int getSLKH(){return countKH;}
        int getSLHD(){return countHD;}
        void getTenCacKH(string hoten[], int &i);
        void getNgayCacHD(int ngay[], int &i);
        void DisplayKHSX(string Hoten);// in ra kh theo sap xep
        void DisplayHDSX(int Ngay);// in ra kh theo sap xep
        void UpdatePhong(int NgDen,int GiDen);
        int TongTien(int&);//tong hoa don 1 đăng kí
        void DeleteKH(int &i,int vt);
        void DeleteHD(int MaPhong);

        friend class DSDK;
};
#endif
int QLDK::c_MKH = 0;
int QLDK::countHD=0;
int QLDK::countKH=0;
QLDK::QLDK(){
    head_KH=NULL;
    head_HD=NULL;
    next_DK = NULL;
}                           
QLDK::QLDK(string MaDK,string TenKH,string CCCD,int SDT, int SLP, int SLN,int GioDK,string NgayDK, Phong *p_dk,string DiaChi)
:data(MaDK,TenKH,CCCD,SDT,SLP,SLN,GioDK,NgayDK, p_dk,DiaChi)
{
    head_KH = NULL;
    head_HD=NULL;
    next_DK = NULL;
    c_HD = 0;
    c_KH = 0;
}
QLDK::~QLDK(){
    while (head_KH!=NULL){
        HuyKHfirst(head_KH);
        countKH--;
    }
    while (head_HD!=NULL)
    {
    	HuyHDfirst(head_HD);
    	countHD--;
	}
    delete head_KH;
    delete head_HD;
    delete next_DK;
}

void QLDK::XuatDK(){
    data.Display();
}
void QLDK::XuatKH(int &i){
    if(head_KH != NULL)
    {
        DSKH* p= head_KH;
        while(p!=NULL){
            cout << setw(3)<<i++;
            cout << setw(10)<<data.getMaDK();
            (*p).Display();
            p = (*p).next;
        }
    }
}

void QLDK::XuatHD(int &i){
    if(head_HD != NULL){
        DSHD* p = head_HD;
        while(p!=NULL){
            cout << setw(3)<<i++;
            cout << setw(12)<<data.getMaDK();
            (*p).Display();
            p = (*p).next;
        }
    }
}
int QLDK::TongTien(int &i){
    int sum=0;
    if(head_HD != NULL){
        DSHD* p = head_HD;
        while(p!=NULL){
            sum+=p->data->ThanhTien();
            p = (*p).next;
        }
    }
    return sum;
}
void QLDK::InsertLastKH(string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen,int GioDi,string NgayDi,string DiaChi,int MaPhong){
    if(ROOM->getSLK(MaPhong)>=ROOM->SLKmax(MaPhong) && ROOM->getSLK(MaPhong)!=0 ) {throw "So luong khach vuot qua so luong quy dinh cua phong";}
    //sai vi c_KH la slk cua ca 1 dk, ma 1 dk co nhieu phong
    if(c_KH>=data.getSLN()) throw "So luong khach vuot so luong da dang ky";
    int check=0;
    for(int i=0;i<data.getSLP();i++)
    {
        if(MaPhong== (data.PhongDK[i]).getMaPhong()) check=1;
    }
    if(check==0) {cout<<MaPhong;throw "Khong dung voi ma phong da dang ky";}
    KH p = new KhachHang(MaKH,TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong);
    DSKH* t=createKH(p);
    if (head_KH==NULL) { head_KH=t;}
    else {head_KH->Insert(t);}
    c_MKH++;
    c_KH++;
    countKH++;
    ROOM->TangGiamKhach(MaPhong,1);
}
void QLDK::InsertLastHD(int MaPhong,string NgayDen,string NgayDi){
    HD p=new HoaDon(MaPhong,NgayDen,NgayDi);
    DSHD* t = createHD(p);
    if(head_HD==NULL)
    {
        head_HD = t;
        c_HD++;
        countHD++;
    }                 //head_HD->Insert(t);
    else
    {
        DSHD* tmp = head_HD;
        while((*tmp).next!=NULL){//tim xem trong DSHD da tao hoa don cho phong do chua
            if(tmp->data->a.MaPhong != MaPhong) tmp = (*tmp).next; //
            else break; //neu phong do da co hoa don thi thoat khoi while
        }
        if((*tmp).next == NULL && tmp->data->a.MaPhong != MaPhong){//neu phong do chua co hoa don
            HD p = new HoaDon(MaPhong,NgayDen,NgayDi);//thi tao hoa don moi
            (*tmp).next=createHD(p);
            c_HD++;
            countHD++;
        }
    }
}
void QLDK::DeleteKH(int &i,int vt){
    DSKH*  p = head_KH;
    DSKH* before;
    while(p->next!=NULL && i<vt){
        before = p;
        p = p->next;    //tro den nodeKH can xoa
        i++;
    }
    (*p).Display();// in thong tin kh can xoa
    DSKH* p1=head_KH;
    int maPhongXoa = (*p).data->getMaPhong();
    ROOM->Update(maPhongXoa,1);
    int k=0;
    while(p1!=NULL){
        if((*p1).data->getMaPhong() == maPhongXoa && p1 != p){
            k = 1;
            break;
        }
        p1 = (*p1).next;
    }
    if(k == 0) DeleteHD(maPhongXoa);
    if(p == head_KH) head_KH = p->next; //nếu là kh dang ky đầu tiên trong dslk đk
    else (*before).next =(*p).next;
    p->HuyDSKH();
}
void QLDK::DeleteHD(int Maphong){
    DSHD* p = head_HD;
    DSHD* before;
    while(p!=NULL || p->data->a.getMaPhong() != Maphong){
    	if(p->data->a.getMaPhong()==Maphong) break;
        before = p;
        p = (*p).next;
    } 
    if(p == head_HD) {head_HD = (*p).next;}
    else {(*before).next =(*p).next; }
    c_HD--;
    p->HuyDSHD();
}
/*
void QLKH::KTPhong(int NgDen, int NgDi,int MP[60],int &i){
    DSHD* tmp = head_HD;
    while(tmp!=NULL){
        char NgayDi[100],NgayDen[100];
        string((*tmp).data->NgayDi).copy(NgayDi,2);
        string((*tmp).data->NgayDen).copy(NgayDen,2);
        NgayDi[2]='\0';
        NgayDen[2]='\0';
        if((NgDen >= atoi(NgayDen)&&NgDen <= atoi(NgayDi)) || (NgDi <=atoi(NgayDi)&&NgDi >=atoi(NgayDen))) {
            MP[i] = (*tmp).data->a.MaPhong;
            i++;
        }
        tmp = (*tmp).next;
    }
}
*/      
void QLDK::UpdatePhong(int NgDen,int GiDen)
{
    DSKH* tmp = head_KH;
    char NgayDi[3];
    while(tmp!=NULL)
    { 
        string((*tmp).data->NgayDi).copy(NgayDi,2);
        NgayDi[2]='\0';
        if(NgDen>atoi(NgayDi) || (NgDen=atoi(NgayDi) && tmp->data->getGioDi()<GiDen))      
        {   
            ROOM->Update(tmp->data->MaPhong,1); //Update trang thai phong va slk=0
        }
        else ROOM->Update(tmp->data->MaPhong,0);
        tmp = (*tmp).next;
    }
}     

void QLDK::getTenCacKH(string hoten[], int &i){
    if(head_KH != NULL){
        DSKH* p= head_KH;
        while(p!=NULL){
            hoten[i] = (p->data)->getTenKH();
            p = (*p).next;
            i++;
        }
    }
}
void QLDK::DisplayKHSX(string Hoten){
    if(head_KH != NULL){
        DSKH* p= head_KH;
        while(p!=NULL){
            if(Hoten == p->data->getTenKH()){
                cout << setw(10)<<data.getMaDK();
                (*p).Display();
                break;
            }
            p = (*p).next;
        }
    }
}

void QLDK::getNgayCacHD(int ngay[], int &i){
    if(head_HD != NULL){
        DSHD* p= head_HD;
        int k=0;
        while(p!=NULL){
            char Ng[100];
            (*p).data->getNgayHD().copy(Ng,2);
            Ng[2]='\0';
            if(i>0){
                for(int j=0;j<=i;j++){
                    if(atoi(Ng) == ngay[j]) break;
                    else if(j==i) ngay[i] = atoi(Ng);
                }
            }
            p = (*p).next;
            i++;
        }
    }
}

void QLDK::DisplayHDSX(int Ngay){
    if(head_HD != NULL){
        DSHD* p= head_HD;
        while(p!=NULL){
            char Ng[100];
            (*p).data->getNgayHD().copy(Ng,2);
            Ng[2]='\0';
            if(Ngay == atoi(Ng)){
                cout << setw(12)<<data.getMaDK();
                (*p).Display();
            }
            p = (*p).next;
        }
    }
}
/*
int main()
{
	Phong* p=new Phong[1];
	p[0].Nhap(1);
	QLKH x("DK001","201870610","NguyenA",123456789,1,1,1212,"12112022","13112022",p);
	x.InsertLastKH("201720212","TranB","13112022",363614059,1512,"DaNang",1);
	int i=1;
	x.InsertLastKH("2001670212","NgoC","14022022",123456742,1502,"Vinh",1);
	x.InsertLastKH("201570612","TRuongD","15012022",972808337,1212,"Hau Giang",1);
	cout<<endl<<"Xuat lan 1"<<endl;
	x.XuatKH(i);
	int i1=1;
	x.DeleteKH(i1,3); //i1: vi tri can xoa
	i1=1;
	cout<<endl<<"Xuat lan 2"<<endl;
	x.XuatKH(i1);
	delete []p;
}
int main()
{
	Phong* p=new Phong[3];
	p[0].Nhap(1);
	p[1].Nhap(2);
	p[2].Nhap(3);
	QLKH x("DK001","201870610","NguyenA",123456789,1,1,1212,"12112022","13112022",p);
	x.InsertLastHD(1,"12/12/2021","14/12/2021");
	x.InsertLastHD(2,"12/12/2021","13/12/2021");
	x.InsertLastHD(3,"12/12/2021","13/12/2021");
	cout<<endl<<"Xuat lan 1"<<endl;
	int i=1;
	x.XuatHD(i);
	i=1;
	cout<<x.TongTien(i);
	x.DeleteHD(1);
	i=1;
	cout<<endl<<"Xuat lan 2"<<endl;
	x.XuatHD(i);
	i=1;
	cout<<x.TongTien(i);
	delete []p;
}
*/