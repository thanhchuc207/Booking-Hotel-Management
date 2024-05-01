#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "QLDK.h"
#include <algorithm> 
using namespace std;
#ifndef DSDK_H 
#define DSDK_H
class DSDK{
    protected:
        int c_MDK; // để tạo mã dk
        int countKHDK;//số khách hàng đăng kí
        qldk head;    // con trỏ head trỏ đến đăng kí đầu tiên
    public:
        DSDK(int n=0);
        ~DSDK(); 
        // thêm 1 khách hàng đăng kí vào dslk quản lí đăng kí(dùng khi đọc và lưu thông tin khách hàng đk từ file đầu vào đăng kí)
        //void InsertLast(string MaDK, int SLP, int SLN, string MaKH,string TenKH,int GioDK,string NgayDK,string NgayDen,string CCCD,int SDT, Phong *p_dk);
        // tìm mã dk hợp lệ sau đó thêm khách hàng có mã đk đó vào dslk khách hàng(dùng khi đọc và lưu thông tin khách hàng đk từ file đầu vào đăng kí)
        // tìm mã đk và mã phòng hợp lệ sau đó thêm hóa đơn có mã đk và mã phòng đó vào dslk hóa đơn(dùng khi tạo hóa đơn)
        void TimVaThemHD(string MaDK,int MaPhong,string NgayDen,string NgayDi);
        void TimVaThemKH(string MaDK,string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen,int GioDi ,string NgayDi,string DiaChi,int MaPhong,int check);
        void ThemVaoViTriDK(string MaDK,string TenKH, string CCCD,int SDT,int SLP, int SLN, int GioDK,string NgayDK,Phong *p_dk);
        void DisplayDK(int n=0);// hiển thị danh sách khách hàng đăng kí
        void DisplayKH();// hiển thị danh sách tất cả khách hàng lưu trú
        void Display_DS_HD(int n=0);// hiển thị danh sách tất cả hóa đơn

        void fileOutDK();//xuất file KHDK
        void fileOutKH(char *x);//xuat file KH
        void fileOutHD();// XUẤT FILE HÓA ĐƠN

        void DeleteDK_vt(int vt, int dh=0); // xóa 1 đăng kí ở vị trí vt trong danh sách đăng kí => khách hàng của đăng kí đó cũng bị xóa
        void DeleteDK_dk(); // xóa 1 đăng kí có điều kiện trong danh sách đăng kí => khách hàng của đăng kí đó cũng bị xóa
        void DeleteKH_vt(int vt);// xóa 1 khách hàng lưu trú ở vị trí vt trong danh sách khách hàng lưu trú, nếu đó là khách hàng duy nhất của 1 đăng kí thì xóa luôn đăng kí đó.
        void DeleteKH_dk();// xóa 1 kh có điều kiện
        
        void KiemTraPhong(string NgDen, int GiDen);
        int KiemTraMaDK(string MaDK);// kiểm tra có mã kh này ko, nếu có thì lấy ra slp,sln luôn

        void ThemKH(string MaDK,int dh,DSP* ROOM); //dh = 1: them dk moi, dh =0: them kh vao dk cu
        
        void DisplayKH_Condition(int);//hiển thị ds KH CÓ ĐIỀU KIỆN 
        void DisplayKH_Condition();//hiển thị ds KH CÓ ĐIỀU KIỆN 
        void DisplayDK_Condition();//hiển thị ds DK CÓ ĐIỀU KIỆN

        void SapXepKH(int dh);
        void SapXepHD();

        void getMDKMKH(string &MaDK,string &MaKH);// lấy mã đk
        int getSL_KHDK(){return countKHDK;}
        friend string getTen(string);   //lấy tên từ họ tên
};
void hoanvi(string &a, string &b);
void hoanvi(int &a, int &b);
string TaoMa(int count,int dh); //dh 1:tạo mã đk, 2: tạo mã kh
string getHo(string);   //lấy họ từ họ tên
#endif
string TaoMa(int count,int dh){
    ++count;
    string Ma;
    if(dh==1) Ma = "DK";
    else Ma = " KH";
    char t[20];
    itoa(count,t,10);
    if(count <10) Ma = Ma+"000"+ t;
    else if(count <100) Ma = Ma + "00"+t;
    else if(count <1000) Ma = Ma + "0"+t;
    return Ma;
}
DSDK::DSDK(int n){
    head = NULL;
    countKHDK = 0;
    c_MDK = 0;
}
DSDK::~DSDK(){
    while (head!=NULL)
    {
        qldk tmp=head;
        head=head->next_DK;
        tmp->next_DK=NULL;
        (*tmp).~QLDK();

    }
    delete head;
}
void DSDK::DisplayDK(int n){
    if(head == NULL) cout <<endl<< "\tDanh sach rong"<<endl;
    else{
        int i = 1;
        qldk tmp = head;
        if(n==0){
            cout <<"- Danh sach khach hang dang ki: "<<endl;
            cout <<setw(5)<<"STT"<< setw(12) << "Ma so DK"<<setw(12)<<"CCCD"<<setw(25)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(16)<<"Gio DK";
            cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<"\tPhong thue"<<endl;
            while(tmp!=NULL){
                cout << setw(5)<<i++;(*tmp).XuatDK();
                tmp = (*tmp).next_DK;
            }
            cout <<"- So luong: "<<--i<<endl;

        }
        else{
            while(tmp!=NULL && i==1){
                if(getNgay(tmp->data.getNgayDK())==n) i++;
                tmp = (*tmp).next_DK;
            }
            if(i!=1){
                qldk tmp = head;
                i=1;
                cout <<"- Danh sach khach hang dang ki: "<<endl;
                cout <<setw(5)<<"STT"<< setw(12) << "Ma so DK"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(11)<<"Gio DK";
                cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<setw(14)<<"Ngay den"<<"\tPhong thue"<<endl;
                while(tmp!=NULL){
                    if(getNgay(tmp->data.getNgayDK())==n){
                        cout << setw(5)<<i++;
                        (*tmp).XuatDK();
                    }
                    tmp = (*tmp).next_DK;
                }
                cout <<"\t- So luong: "<<--i<<endl;
            }
            else cout<<endl<<"- Khong co khach hang dang ki nao trong ngay."<<endl;
        }

    }
}
string getTen(string x){
    reverse(x.begin(), x.end());
    int n=x.size();
    char tmp[n];
    for(int i=0; i<n; i++){tmp[i]=x[i];}
    char *name=strtok(tmp, " ");
    x=name;
    reverse(x.begin(), x.end());
    return x;
}
string getHo(string x){
    char ho[10]={0};
    for(int i=0;i<x.size();i++){
        if(x[i]!=' ') ho[i] = x[i]; 
        else break;
    }
    return ho;
}                                  
void DSDK::TimVaThemKH(string MaDK,string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen,int GioDi ,string NgayDi,string DiaChi,int MaPhong,int check){
    qldk p;
    p = head;
    while(p!=NULL && p->data.getMaDK() != MaDK)  p=(*p).next_DK;
    if(p!=NULL)
    { 
        if(MaKH == "0") MaKH = TaoMa((*p).c_MKH,2);
        if(check==0)
        {
            try     {p->InsertLastKH(MaKH,TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong);}
            catch (const char* msg) 
            {   cerr << msg << endl;
                throw 1;
            };
        }
        else p->InsertLastKH(MaKH,TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong);   
    }
    else
    {
        cout<<MaDK;
        throw "Khong ton tai Ma dang ky";
    }		
}
void DSDK::DisplayKH(){
    int i=1;
    cout << "- Danh sach khach hang luu tru: "<<endl;
    cout<<"So luong: "<<head->getSLKH()<<endl;
    cout << setw(3)<<"STT";
    cout <<setw(10)<<"Ma DK"<<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl; 
    qldk tmp = head;
    while(tmp!=NULL){
        (*tmp).XuatKH(i);
        tmp = (*tmp).next_DK;
    }
}
void DSDK::TimVaThemHD(string MaDK,int MaPhong,string NgayDen,string NgayDi){
    qldk p;
    p = head;
    while(p!=NULL && p->data.getMaDK() != MaDK)  p=(*p).next_DK;
    if(p!=NULL){
        p->InsertLastHD(MaPhong,NgayDen,NgayDi);
    }	
}
void DSDK::Display_DS_HD(int n){
    if(head==NULL|| head->head_HD==NULL){
        cout<<"- Khong co hoa don nao."<<endl;
        return;
    }
    int i=1;
    int sum=0;
    if(n==0){
        cout << "- Danh sach hoa don: "<<endl;
        cout<<"So luong: "<<head->getSLHD()<<endl;
        cout << setw(3)<<"STT";
        cout << setw(12)<<"Ma DK";
        cout <<setw(15)<<"Ma HD"<<setw(13)<<"Ma phong"<< setw(17)<<"Ngay HD"<<setw(13)<<"Don gia";
        cout <<setw(13)<<"So ngay o"<<setw(15)<<"Thanh Tien"<<endl;
        qldk tmp = head;
        while(tmp!=NULL){
            (*tmp).XuatHD(i);
            sum+=tmp->TongTien(i);
            tmp = (*tmp).next_DK;
        }
        cout<<"- Tong so tien phong: "<<sum<<endl;
    }
    else{
        qldk p=head;
        while(p!=NULL && i==1){
            DSHD* h=p->head_HD;
            while (h!=NULL && i==1)
            {
                if(n==h->data->getNgay(h->data->getNgayHD()))    i++;
                h=h->next;
            }
            p=p->next_DK;
        }
        if(i==1){
            cout<<"- Khong co hoa don nao trong ngay."<<endl;
        }
        else{
            p=head;
            i=1;
            cout << "- Danh sach hoa don cua thang: "<<endl;
            cout << setw(3)<<"STT";
            cout << setw(12)<<"Ma DK";
            cout <<setw(15)<<"Ma HD"<<setw(10)<<"Ma phong"<< setw(20)<<"Ngay HD"<<setw(15)<<"Don gia phong";
            cout <<setw(10)<<"So ngay o"<<setw(15)<<"Thanh Tien"<<endl;
            while(p!=NULL){
                DSHD* h=p->head_HD;
                while (h!=NULL)
                {
                    if(n==h->data->getNgay(h->data->getNgayHD())) {
                        cout<<i;
                        cout<<setw(14)<<p->data.getMaDK();
                        h->Display();
                        sum+=h->data->ThanhTien();
                        i++;
                    }
                    h=h->next;
                }
                p=p->next_DK;
            }
            cout<<endl<<"- So luong hoa don: "<<--i<<endl;
            cout<<"- Tong so tien: "<<sum<<endl;
        }
    }
}
void DSDK::fileOutDK(){
    if(head==NULL){
        cout<<"\tDanh sach trong";
        return;
    }
    fstream f;
    string MaDK,CCCD,TenKH,NgayDK;
    int SDT,SLN,SLP,SLDK,GioDK;
    qldk tmp=head;

	cout<<"\tNhap file OUT : ";
	char x[100];
	cin>>x;
	strcat(x, ".txt");
    //ghi file
	f.open(x, ios::out);
    f<<setw(76)<<"<------------------------------------------------>"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(38)<<"HIEN THI FILE THEO YEU CAU"<<setw(11)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(76)<<"<------------------------------------------------>"<<endl<<endl;
    //
    SLDK=getSL_KHDK();
    f<<"\tSo Luong: "<<SLDK<<endl;
    int stt=1;
    
    f<<setw(5)<<"STT"<< setw(12) << "Ma so DK"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(10)<<"Gio DK";
    f<< setw(14) << "Ngay DK" << setw(7) << "SLP"<<setw(7)<<"SLN"<<"\t\tPhong thue"<<endl;
    for(int i=1; i<=SLDK; i++){
        f<<setw(5)<<stt;
        stt++;
        MaDK=tmp->data.getMaDK();       f<<setw(12)<<MaDK;
        CCCD=tmp->data.getCCCD();       f<<setw(18)<<CCCD;
        TenKH=tmp->data.getTenKH();     f<<setw(25)<<TenKH;
        SDT=tmp->data.getSDT();         f<<setw(7)<<"0"<<SDT;
        GioDK=tmp->data.getGioDK();     f<<setw(8)<<GioDK;
        NgayDK=tmp->data.getNgayDK();   f<<setw(14)<<NgayDK;
        SLP=tmp->data.getSLP();         f<<setw(7)<<SLP;
        SLN=tmp->data.getSLN();         f<<setw(7)<<SLN;
        f<<"\t\t";
        for(int i=0; i<SLP; i++)   f<<tmp->data.PhongDK[i].getMaPhong()<<" ";
        f<<endl;
        tmp=tmp->next_DK;
    }
    f.close();
    cout<<setw(20)<<"\tMo file de xem!";
}
void DSDK::fileOutKH(char *x){//hiển thị khách hàng theo 4 yêu cầu/ hiển thị tất cả
    fstream f;
    string MaDK, MaKH,CCCD,TenKH,NgayDen,NgayDi,DiaChi;
    int SDT,SLK,GioDen,GioDi,MaPhong;
    //ghi file
	f.open(x, ios::out);
    f<<setw(76)<<"<------------------------------------------------>"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(38)<<"HIEN THI FILE THEO YEU CAU"<<setw(11)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(76)<<"<------------------------------------------------>"<<endl<<endl;
    //in danh sách khách hàng hiện thời
    
        qldk pDK=head;
        int stt=1;
        f<<setw(5)<<"STT"<< setw(10) << "Ma so DK"<<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH DK"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
        f<< setw(11) << "Gio den" <<setw(12)<<"Ngay den"<< setw(11) << "Gio di"<<setw(12)<<"Ngay di"<<setw(11)<<"Ma Phong"<<endl;

        while(pDK!=NULL){
            DSKH* pKH=pDK->head_KH;
            while (pKH!=NULL)
            {       
                    if(pKH->data->getCCCD()!="0"){
                        f<<setw(5)<<stt;
                        stt++;
                        MaDK=pDK->data.getMaDK();       f<<setw(10)<<MaDK;
                        MaKH=pKH->data->getMaKH();       f<<setw(12)<<MaKH;
                        CCCD=pKH->data->getCCCD();       f<<setw(18)<<CCCD;
                        TenKH=pKH->data->getTenKH();     f<<setw(25)<<TenKH;
                        SDT=pKH->data->getSDT();         f<<setw(3)<<"0"<<SDT;
                        
                        DiaChi=pKH->data->getDiaChi();   f<<setw(16)<<DiaChi;
                        GioDen=pKH->data->getGioDen();   
                        f<<setw(8)<<GioDen/100 << ":";
                        if(GioDen %100 <10) f<< "0"<<GioDen %100;
                        else f<<setw(2)<<GioDen%100;
                        NgayDen=pKH->data->getNgayDen(); f<<setw(12)<<NgayDen;
                        GioDi=pKH->data->getGioDi();     
                        f<<setw(8)<<GioDi/100 << ":";
                        if(GioDi %100 <10) f<< "0"<<GioDi %100;
                        else f<<setw(2)<<GioDi%100;
                        NgayDi=pKH->data->getNgayDi();  f<<setw(12)<<NgayDi;
                        MaPhong=pKH->data->getMaPhong(); f<<setw(10)<<MaPhong;
                        f<<endl;
                    }
                    pKH=pKH->next;

            }
            pDK=pDK->next_DK;
            
        }
        f<<endl<<"\tSo Luong: "<<--stt<<endl;
    f.close();
    cout<<"\tMo file de xem!"<<endl;
}
void DSDK::fileOutHD(){//hiển thị khách hàng theo 4 yêu cầu/ hiển thị tất cả
    if(head==NULL){ 
        cout<<"\tDanh sach trong";
        return;
    }
    fstream f;
    string MaDK, MaHD,NgayHD;
    int SoNgayO, DonGia,ThanhTien, MaPhong, SLHD;

	cout<<"\tNhap file OUT : ";
	char x[100];
	cin>>x;
	strcat(x, ".txt");
    //ghi file
	f.open(x, ios::out);
    //chỗ ni t làm màu
    f<<setw(76)<<"<------------------------------------------------>"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(38)<<"HIEN THI FILE THEO YEU CAU"<<setw(11)<<"|"<<endl;
    f<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    f<<setw(76)<<"<------------------------------------------------>"<<endl<<endl;
    //in danh sách hóa đơn hiện thời
    
        qldk pDK=head;
        SLHD=pDK->getSLHD();
        f<<setw(25)<<"So Luong: "<<SLHD<<endl<<endl;
        int stt=1;
        f<<setw(20)<<"STT"<< setw(11) << "Ma so DK"<<setw(10)<<"Ma HD"<< setw(20)<<"Ngay HD"<<setw(18)<<"Ma Phong"<<setw(10)<<"Don Gia"<< setw(12) << "So Ngay O"<<setw(13)<<"Thanh Tien"<<endl;

        while(pDK!=NULL){
            DSHD* pHD=pDK->head_HD;
            while (pHD!=NULL)
            {
                f<<setw(19)<<stt;
                stt++;
                MaDK=pDK->data.getMaDK();            f<<setw(12)<<MaDK;
                MaHD=pHD->data->getMaHD();            f<<setw(15)<<MaHD;
                NgayHD = pHD->data->getNgayHD();      f<<setw(18)<<NgayHD;
                MaPhong=pHD->data->a.getMaPhong();    f<<setw(11)<<MaPhong;
                DonGia=pHD->data->a.getDonGia();      f<<setw(10)<<DonGia;
                SoNgayO=pHD->data->SoNgayO();         f<<setw(8)<<SoNgayO;
                ThanhTien=pHD->data->ThanhTien();     f<<setw(15)<<ThanhTien;
                                                f<<endl;

                pHD=pHD->next;

            }
            pDK=pDK->next_DK;  
        }
    f.close();
    cout<<setw(20)<<"Mo file de xem!";

}

void DSDK::DisplayDK_Condition(){
    string HoTen,Ten,Ngay_DK;
    if(head == NULL)    cout <<setw(20)<< "Danh sach hien thoi dang rong"<<endl;
    else{
        DSDK dout;
        qldk tmp=head;
        cout<<endl<<"\tNhap cac thong tin nguoi dang ki (nhap 0 de bo qua): "<<endl;
        cout<<"\t-Nhap ho ten: "; fflush(stdin);
        getline(cin,HoTen); //hoặc nhập tên hoặc nhập họ tên, nếu nhập cả 2 thì ưu tiên họ tên
        cout<<"\t-Nhap ten: "; cin>>Ten;
        cout<<"\t-Nhap ngay dang ki: "; cin>>Ngay_DK;
        if(HoTen!="0"){ //nhập họ tên
            if(Ngay_DK!="0"){//xét ngày
                while(tmp!=NULL){
                    string HT=tmp->data.getTenKH();
                    string date=tmp->data.getNgayDK();
                    if(HoTen == HT && Ngay_DK==date){
                        dout.ThemVaoViTriDK(tmp->data.getMaDK(), HT, tmp->data.getCCCD(), tmp->data.getSDT(),tmp->data.getSLP(), tmp->data.getSLN(),  tmp->data.getGioDK(), date, tmp->data.PhongDK);
                    }//string MaDK,string TenKH, string CCCD,int SDT,int SLP, int SLN, int GioDK,string NgayDK,Phong *p_dk,int vt
                    tmp=tmp->next_DK;
                }
            }
            else{
                while(tmp!=NULL){
                    string HT=tmp->data.getTenKH();
                    if(HT==HoTen){
                        dout.ThemVaoViTriDK(tmp->data.getMaDK(), HT, tmp->data.getCCCD(),tmp->data.getSDT(),tmp->data.getSLP(), tmp->data.getSLN(),  tmp->data.getGioDK(), tmp->data.getNgayDK(),  tmp->data.PhongDK);
                    }
                    tmp=tmp->next_DK;
                }
            }
        }
        else if(Ten!="0"){   //không nhập họ tên, có nhập tên
            if(Ngay_DK!="0"){   
                while (tmp!=NULL)
                {
                    string date=tmp->data.getNgayDK();
                    string HT=tmp->data.getTenKH();
                    if(Ngay_DK==date && Ten==getTen(HT)){
                        dout.ThemVaoViTriDK(tmp->data.getMaDK(), HT,tmp->data.getCCCD(), tmp->data.getSDT(),tmp->data.getSLP(), tmp->data.getSLN(),  tmp->data.getGioDK(), date,  tmp->data.PhongDK);
                    }
                    tmp=tmp->next_DK;
                }
            }
            else{
                 while (tmp!=NULL)
                {
                    
                    string HT=tmp->data.getTenKH();
                    if(Ten==getTen(HT)){
                        dout.ThemVaoViTriDK(tmp->data.getMaDK(), HT,tmp->data.getCCCD(), tmp->data.getSDT(),tmp->data.getSLP(), tmp->data.getSLN(),  tmp->data.getGioDK(), tmp->data.getNgayDK(),  tmp->data.PhongDK);
                    }
                    tmp=tmp->next_DK;

                }
            }
        }
        else{//chỉ nhập ngày đk
            while (tmp!=NULL)
                {
                    string date=tmp->data.getNgayDK();
                    if(Ngay_DK==date){
                        dout.ThemVaoViTriDK(tmp->data.getMaDK(), tmp->data.getTenKH(),tmp->data.getCCCD(), tmp->data.getSDT(),tmp->data.getSLP(), tmp->data.getSLN(),   tmp->data.getGioDK(), date, tmp->data.PhongDK);
                    }
                    tmp=tmp->next_DK;
                }
        }
        if(dout.head==NULL) cout << "\tKhong tim thay khach hang phu hop."<<endl;
        else dout.DisplayDK();
    }   
}
void DSDK::DisplayKH_Condition(){
    if(head == NULL) {
        cout<<"Danh sach rong";
        return;
    }
    else{
        int sum=0;
        string HoTen,Ten,NgayDen;
            cout<<endl<<"\tNhap cac thong tin khach hang (nhap 0 de bo qua): "<<endl;
            cout<<"\t-Nhap ho ten: "; fflush(stdin);
            getline(cin,HoTen); //hoặc nhập tên hoặc nhập họ tên, nếu nhập cả 2 thì ưu tiên họ tên
            cout<<"\t-Nhap ten: "; cin>>Ten;
            cout<<"\t-Nhap ngay den: "; cin>>NgayDen;
            qldk k=head;
            while (k!=NULL){
                DSKH* tmp=k->head_KH;
                if(HoTen!="0"){
                    if(NgayDen!="0"){
                        while(tmp!=NULL){
                            if(tmp->data->getTenKH()!=HoTen && tmp->data->getNgayDen()==NgayDen)    {
                                sum++;
                                if(sum == 1){
                                    cout << "- Danh sach khach hang luu tru: "<<endl;
                                     
                                    cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
                                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                                }
                                tmp->Display();}
                            tmp=tmp->next;
                        }
                    }
                    else{
                        while (tmp!=NULL)
                        {
                            if(tmp->data->getTenKH()==HoTen) {
                                sum++;
                                if(sum == 1){
                                    cout << "- Danh sach khach hang luu tru: "<<endl;
                                    cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
                                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                                }
                                tmp->Display();}
                            tmp=tmp->next;
                        }
                        
                    }
                }
                else if(Ten!="0"){
                    if(NgayDen!="0"){
                        while (tmp!=NULL)
                        {
                            if(tmp->data->getNgayDen()==NgayDen && Ten==getTen(tmp->data->getTenKH())) {
                                sum++;
                                if(sum == 1){
                                    cout << "- Danh sach khach hang luu tru: "<<endl;
                                   cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
                                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                                }
                                tmp->Display();}
                            tmp=tmp->next;
                        }
                    }
                    else{
                        while (tmp!=NULL)
                        {
                            if(Ten==getTen(tmp->data->getTenKH())) {
                                sum++;
                                if(sum == 1){
                                    cout << "- Danh sach khach hang luu tru: "<<endl;
                                    cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
                                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                                }
                                tmp->Display();}
                            tmp=tmp->next;
                        }
                    }
                }
                else{
                    while (tmp!=NULL)
                        {
                            if(tmp->data->getNgayDen()==NgayDen) {
                                sum++;
                                if(sum == 1){
                                    cout << "- Danh sach khach hang luu tru: "<<endl;
                                  cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(17)<<"Dia chi";
                                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                                }
                                tmp->Display();}
                            tmp=tmp->next;
                        }
                }
                k=k->next_DK;
            }
        
        if(sum==0) cout<<"-Khong tim thay khach hang phu hop"<<endl;
        
        else cout<<endl<<"-So luong: "<<sum<<endl;
    }
}
void DSDK::DisplayKH_Condition(int NgayDen){
    if(head == NULL || head->head_KH==NULL) {
        cout<<"- Danh sach rong";
        return;
    }
    else{
        int i=1;
        qldk k=head;
        while (k!=NULL && i==1) {
            DSKH* tmp=k->head_KH;
                while (tmp!=NULL && i==1)
                    {
                        if(getNgay(tmp->data->getNgayDen())<=NgayDen && getNgay(tmp->data->getNgayDi())>=NgayDen ) i++;
                        tmp=tmp->next;
                    }
            k=k->next_DK;
        }
        if(i==1)   cout<<"- Khong co khach hang luu tru trong ngay"<<endl;
        else{
            i=1;
            cout << "- Danh sach khach hang luu tru: "<<endl;
            cout << setw(3)<<"STT";
            cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(12)<<"SDT"<<setw(15)<<"Dia chi";
            cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
            k=head;
            while (k!=NULL){
                DSKH* tmp=k->head_KH;
                    while (tmp!=NULL )
                        {   
                            if(getNgay(tmp->data->getNgayDen())<=NgayDen &&getNgay(tmp->data->getNgayDi())>=NgayDen ) {
                                cout<<setw(3)<<i++;
                                tmp->Display();
                            }
                            tmp=tmp->next;
                        }
                k=k->next_DK;
            }
            cout<<"- So luong: "<<--i<<endl;
        }
    
    }
}
void DSDK::DeleteDK_vt(int vt,int dh){//dh=1 xoa kh duy nhat cua dk, dh=0 xoa dk
    if(vt>this->countKHDK) vt = this->countKHDK;
    if(head == NULL) cout << "Danh sach dang rong!"<<endl;
    else{
        int i=1;
        qldk tmp = head;
        qldk before;
        while(tmp!=NULL && i<vt){// chạy đến đăng kí cần xóa
            before = tmp;
		    tmp = (*tmp).next_DK;
            i++;
        }
        if(dh == 0 ) tmp->XuatDK();
        else (*tmp).head_KH->Display();
        
        tmp->countHD -= tmp->c_HD; // điều chỉnh số lượng tất cả hóa đơn
        tmp->countKH -= tmp->c_KH;//  điều chỉnh số lượng tất cả khách hàng 
        if(tmp == head ) head = (*tmp).next_DK;//nếu là kh đầu tiên của đk
        else (*before).next_DK =(*tmp).next_DK;
        this->countKHDK--;
    } 
}
void DSDK::DeleteKH_vt(int vt){
    if(vt > head->getSLKH()) vt = head->getSLKH();
    if(head == NULL) cout << "Danh sach dang rong!"<<endl;
    else{
        // tìm đăng kí có chức khách hàng cần xóa
        int j=1;//vị trí của đăng kí
        qldk tmp = head;
        int i=(*tmp).c_KH; 
        while(tmp!=NULL && i<vt){// tìm cái đăng kí có khách hàng cần xóa
            tmp = (*tmp).next_DK;
            i+=(*tmp).c_KH;
            j++;
        }
        i=i-(*tmp).c_KH+1;// vị trí kh đầu tiên của đk có kh cần xóa (vị trí dựa trên tổng ds kh lưu trú)
        // xóa khách hàng
        if((*tmp).head_KH->next == NULL){// khach hang can xoa la khach hang cua dang ki chi co 1 khách hàng
            this->DeleteDK_vt(j,i);
        }else{
            (*tmp).DeleteKH(i,vt);
            (*tmp).c_KH--;// điều chỉnh số lượng kh của 1 đk
            (*tmp).countKH--;// điều chỉnh số lượng tất cả khách hàng
        } 
    }
}
void DSDK::DeleteDK_dk(){
    int i=1;//lay vi tri cua dk can xoa
    int j=0;// j=0=> ko co kh can xoa, j=1: co kh can xoa
    string HoTen,Ten,Ngay_DK;
    qldk tmp = head;
    if(head == NULL)    cout <<setw(20)<< "Danh sach hien thoi dang rong"<<endl;
    else{
        cout<<endl<<"\tNhap cac thong tin khach hang luu tru (nhap 0 de bo qua): "<<endl;
        cout<<"\t-Nhap ho ten: "; fflush(stdin);
        getline(cin,HoTen); //hoặc nhập tên hoặc nhập họ tên, nếu nhập cả 2 thì ưu tiên họ tên
        cout<<"\t-Nhap ten: "; cin>>Ten;
        cout<<"\t-Nhap ngay dang ki: "; cin>>Ngay_DK;
        if(HoTen != "0"){
            while(tmp!=NULL){
                if(HoTen == tmp->data.getTenKH()) {j++;
                if(j==1){
                cout << "Thong tin khach hang da xoa: "<<endl;
                cout << setw(12) << "Ma so DK"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(13)<<"CCCD"<<setw(11)<<"Gio DK";
                cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<"\tPhong thue"<<endl;
                }
                DeleteDK_vt(i,0);i--;} 
                i++;
                tmp =tmp->next_DK;
            }
        }else if(Ten != "0"){
            while(tmp!=NULL) {
                if(Ten == getTen(tmp->data.getTenKH())) {j++;
                if(j==1){
                cout << "Thong tin khach hang da xoa: "<<endl;
                cout << setw(12) << "Ma so DK"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(13)<<"CCCD"<<setw(11)<<"Gio DK";
                cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<"\tPhong thue"<<endl;
                }
                DeleteDK_vt(i,0);i--;} 
                i++;
                tmp =tmp->next_DK;
            }
        }else if(Ngay_DK != "0"){
            while(tmp!=NULL) {
                if(Ngay_DK == tmp->data.getNgayDK()) {j++;
                if(j==1){
                cout << "Thong tin khach hang da xoa: "<<endl;
                cout << setw(12) << "Ma so DK"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(13)<<"CCCD"<<setw(11)<<"Gio DK";
                cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<"\tPhong thue"<<endl;
                }
                DeleteDK_vt(i,0);i--;} 
                i++;
                 tmp =tmp->next_DK;
            }
        }
        if(j==0) cout << "\tKhong tim thay khach hang co tieu chi phu hop."<<endl;
    }
}
void DSDK::DeleteKH_dk(){
    int i=1;//lay vi tri cua kh can xoa
    int j=0;
    string HoTen,Ten,NgayDen;
    qldk tmp = head;
    if(head == NULL)    cout <<setw(20)<< "Danh sach hien thoi dang rong"<<endl;
    else{
        cout<<endl<<"\tNhap cac thong tin nguoi dang ki (nhap 0 de bo qua): "<<endl;
        cout<<"\t-Nhap ho ten: "; fflush(stdin);
        getline(cin,HoTen); //hoặc nhập tên hoặc nhập họ tên, nếu nhập cả 2 thì ưu tiên họ tên
        cout<<"\t-Nhap ten: "; cin>>Ten;
        cout<<"\t-Nhap ngay den: "; cin>>NgayDen;
        if(HoTen != "0"){
            while(tmp!=NULL){
                if(tmp-> head_KH != NULL){
                DSKH* p= tmp->head_KH;
                while(p!=NULL){
                    if(HoTen == p->data->getTenKH()) {j++;
                    if(j==1){
                    cout << "Thong tin khach hang da xoa: "<<endl;
                    cout <<setw(12) <<"Ma KH"<<setw(18)<<"Ten KH"<<setw(12)<<"SDT"<<setw(11)<<"CCCD"<<setw(15)<<"Dia chi";
                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                    }
                DeleteKH_vt(i);i--;}
                    i++;
                    p = (*p).next;
                }
            }   
            tmp =tmp->next_DK;
            }
        }else if(Ten != "0"){
            while(tmp!=NULL){
                if(tmp-> head_KH != NULL){
                DSKH* p= tmp->head_KH;
                while(p!=NULL){
                    if(Ten == getTen(p->data->getTenKH())) {j++;
                    if(j==1){
                    cout << "Thong tin khach hang da xoa: "<<endl;
                    cout <<setw(12) <<"Ma KH"<<setw(18)<<"Ten KH"<<setw(12)<<"SDT"<<setw(11)<<"CCCD"<<setw(15)<<"Dia chi";
                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                    }
                    DeleteKH_vt(i);i--;}
                    i++;
                    p = (*p).next;
                }
            }   
            tmp =tmp->next_DK;
            }
        }else if(NgayDen != "0"){
            while(tmp!=NULL){
                if(tmp-> head_KH != NULL){
                DSKH* p= tmp->head_KH;
                while(p!=NULL){
                    if(NgayDen == p->data->getNgayDen()) {j++;
                    if(j==1){
                    cout << "Thong tin khach hang da xoa: "<<endl;
                    cout <<setw(12) <<"Ma KH"<<setw(18)<<"Ten KH"<<setw(12)<<"SDT"<<setw(11)<<"CCCD"<<setw(15)<<"Dia chi";
                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl;
                    }
                    DeleteKH_vt(i);i--;}
                    i++;
                    p = (*p).next;
                }
            }   
            tmp =tmp->next_DK;
            }
        }
        if(j==0) cout << "\tKhong tim thay khach hang co tieu chi phu hop."<<endl;
    }
}
int DSDK::KiemTraMaDK(string MaDK){
    qldk p;
    p = head;
    while(p!=NULL && p->data.getMaDK()!= MaDK)  p=(*p).next_DK;
    if(p==NULL) return 0;
    else return 1;
    	
}                           
void DSDK::ThemVaoViTriDK(string MaDK,string TenKH, string CCCD,int SDT,int SLP, int SLN, int GioDK,string NgayDK,Phong *p_dk){
    if(MaDK == "0" )    MaDK = TaoMa(c_MDK,1);// tạo mã đk
    qldk p = new QLDK(MaDK,TenKH,CCCD,SDT,SLP,SLN,GioDK,NgayDK,p_dk);
    if(head == NULL) head = p;
    else
    {
        qldk tmp = head;
        while(tmp->next_DK!=NULL)// chạy đến vi tri đăng kí 
            {
                tmp = (*tmp).next_DK;
            }
        tmp->next_DK = p;
    }
    countKHDK++;
    c_MDK++;
}

void DSDK::getMDKMKH(string &MaDK, string &MaKH){
    qldk tmp = head;
    while(tmp->next_DK!=NULL)
        {// chạy đến vi tri đăng kí 
            tmp = (*tmp).next_DK;
        }
    MaDK = (*tmp).data.getMaDK();
    MaKH=TaoMa((*tmp).c_MKH,2);
}

void DSDK::KiemTraPhong(string NgDen, int GiDen){
    char NgayDen[3];
    string(NgDen).copy(NgayDen,2);
    NgayDen[2]='\0';
    int NDen = atoi(NgayDen);
    qldk p = head;
    while(p!=NULL){
        (*p).UpdatePhong(NDen,GiDen);
        p=(*p).next_DK;
    }
}
void DSDK::ThemKH(string MaDK,int dh,DSP* ROOM){//dh = 1: them dk moi, dh =0: them kh vao dk cu
    string TenKH,CCCD,NgayDi,NgayDen,DiaChi,MaKHDK,MaKH;
    int SDT,SLN,SLP,GioDen,GioDi,MaPhong;
    int MP[60];
    P p_dk;
    int SLKhachMax = ROOM->SLKToiDa();
again5:    cout << "So luong khach: ";string pt; cin >> pt; SLN=atoi(pt.c_str());
    if(SLN<1)
    {
        cout<<"Vui long nhap lai."<<endl;
        goto again5;
    }
    if(SLN>SLKhachMax)
    {
        cout<<"So luong khach toi da: "<<SLKhachMax<<endl;
        throw "Khong du suc chua.";
    }
    do
    {
        cout<< endl<< "Gio Den(hhmm): ";cin >> GioDen;
    }
    while(GioDen<0 || GioDen>2359);
    char tt[3];
    do
    {
        cout <<endl<< "Ngay den(dd/mm/yy): ";cin >> NgayDen;
        strncpy(tt,NgayDen.c_str(),2);
        tt[2]='\0';
        
    }
    while(NgayDen.length()!=10||atoi(tt)<1 || atoi(tt)>31);

    do
    {
        cout <<endl<< "Gio Di(hhmm): ";cin >> GioDi;
    }
    while(GioDi<0||GioDi>2359  ); 

    do
    {
        cout <<endl<< "Ngay di(dd/mm/yy): ";cin >> NgayDi;
        strncpy(tt,NgayDen.c_str(),2);
        tt[2]='\0';
    }
    while(NgayDi.length()!=10 || atoi(tt)<1 || atoi(tt)>31 || atoi(NgayDi.c_str())<atoi(NgayDen.c_str()) ||   atoi(NgayDi.c_str())==atoi(NgayDen.c_str()) && (GioDi<=GioDen));

    KiemTraPhong(NgayDen,GioDen);
    int SoPhongFull = KTPhong(MP);
    DSPhong(ROOM);
    if(SoPhongFull != 0) cout <<endl<<endl<< "Nhung phong da co nguoi thue. Vui long khong chon nhung phong nay: ";
    for(int i=0;i<SoPhongFull;i++){
        cout << MP[i] ;
        if(i==SoPhongFull-1) cout<< "."<<endl;
        else cout << ", ";
    }

 again:   cout << "So luong phong: ";cin >> SLP;
    if(SLP>SLN) 
    {
        cout<<"So luong phong vuot qua so luong khach luu tru. Vui long nhap lai."<<endl;
        goto again;
    }
    if(SLP<1 || SLP>SLPhongMax-SoPhongFull)
    {   if(SLP>SLPhongMax-SoPhongFull) cout<<"So phong trong toi da: "<<SLPhongMax-SoPhongFull<<endl;
        cout<<"Vui long nhap lai."<<endl;
        goto again;
    }
    int A[SLP+1],ph=0;
    p_dk = new Phong[SLP];
    // nhap ma phong thue cua dang ki
    for(int i = 0;i<SLP;i++)
    {
again1: cout << "Nhap ma phong thue thu "<<i+1<<" : ";
        cin >> A[i];
                for(int j=0;j<SoPhongFull;j++)
                {
                    if(MP[j] == A[i])
                    {
                        cout << "Ma phong nay da co nguoi o. Vui long chon ma phong khac."<<endl;
                        goto again1;
                    }
                    else if(MP[j]==0) break;
                }
                for(int j=0;j<i;j++)
                    if(A[j]==A[i])
                        {
                            cout<<"Chon trung ma phong. Vui long chon ma phong khac."<<endl;
                            goto again1;
                        }
                if(ROOM->TimPhong(A[i])==0) 
                {
                    cout<<"Khong ton tai ma phong nay. Vui long nhap lai."<<endl;
                    goto again1;
                }
                ph+=ROOM->SLKmax(A[i]);//tinh tong sl khach hang toi da     
    }
        if(ph<SLN)
        {
            cout<<"Khong the chua du so luong khach. Vui long nhap lai."<<endl;
            goto again;
        }
    for(int i=0;i<SLP;i++)
    {
        MaPhong=A[i];
        p_dk[i].Nhap(MaPhong);
        ROOM->Update(MaPhong,0);
    }
    // Nhap thong tin khach hang
    int SLN2=SLN,SLP2=SLP;
    int PHONG[SLP]={};
    for(int i=1;i<=SLN;i++)
    {
        cout <<endl<<endl<< "Nhap thong tin khach hang thu "<<i<<" : "<<endl;
        cout << "Ten KH: ";fflush(stdin);getline(cin,TenKH);
        do
        {
            cout << "CCCD: ";cin >> CCCD;
        }
        while(CCCD.length()!=12);
        do
        {
            cout << "SDT: ";cin>>SDT;
        }
        while(999999999-SDT<0);
        cout << "Dia Chi: ";fflush(stdin);getline(cin,DiaChi);
again2: cout << "Vui long chon 1 trong so cac phong sau: ";
        if(i!=1 && SLN2==SLP2) 
        {   
            for(int j=0;j<SLP;j++)
            {   int kt=0;
                for(int t=1;t<=SLP;t++)
                    if(p_dk[j].getMaPhong()==PHONG[t]) kt=1;
                if(kt==0) cout << p_dk[j].getMaPhong()<<"    ";
            }
            cout <<endl<< "Ma phong :"; cin >> MaPhong;
            for(int j=0;j<SLP;j++)
            {   if( p_dk[j].getMaPhong()==MaPhong) break;
                if(p_dk[j].getMaPhong()!=MaPhong && j == SLP-1)
                {
                    cout << "Ma phong khong hop le. Vui long nhap lai."<<endl;
                    goto again2;
                }
            }
            for(int j=1;j<=SLP;j++)
                {
                    if(MaPhong==PHONG[j]) 
                    {
                        cout << "Ma phong khong hop le. Vui long nhap lai."<<endl;
                        goto again2;
                    }
                }
        }
        else
        {
            for(int j=0;j<SLP;j++)
            {
                cout << p_dk[j].getMaPhong()<<"    ";
            }
            cout <<endl<< "Ma phong :"; cin >> MaPhong;
        
        // kiem tra ma phong
            for(int j=0;j<SLP;j++)
            {
                if( p_dk[j].getMaPhong()==MaPhong) break;
                if(p_dk[j].getMaPhong()!=MaPhong && j == SLP-1){
                    cout << "Ma phong khong hop le. Vui long nhap lai."<<endl;
                    goto again2;
                } 
            }
        }
        
        PHONG[i]=MaPhong;
        // them
        if(i==1 && dh == 1)// them dk moi
        {
            ThemVaoViTriDK("0",TenKH,CCCD,SDT,SLP,SLN,GioDen,NgayDen,p_dk);
            getMDKMKH(MaKHDK,MaKH);// hàm lấy mã đk của đk vừa thêm

            try             {TimVaThemKH(MaKHDK,MaKH,TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong,0);}
            catch(int x)    {goto again2;};

            TimVaThemHD(MaKHDK,MaPhong,NgayDen,NgayDi);
        }
        else   
            if(dh == 1)     
            {   try             {TimVaThemKH(MaKHDK,"0",TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong,0);}
                catch(int x)    {goto again2;};
                TimVaThemHD(MaKHDK,MaPhong,NgayDen,NgayDi);
            }
            else    
                if(dh == 0)    
                {   try             {TimVaThemKH(MaDK,"0",TenKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DiaChi,MaPhong,0);}
                    catch(int x)    {goto again2;};     
                    TimVaThemHD(MaDK,MaPhong,NgayDen,NgayDi);
                } 
        SLN2--;SLP2--;
    }
}
void hoanvi(string &a, string &b)
{
    string c = a;
    a = b;
    b = c;
}
void hoanvi(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}
void DSDK::SapXepKH(int dh){
    // lấy ho tên
    qldk p = head;
    int n;
    if(dh == 2)  n= (*p).getSLKH();
    else if(dh ==1) n= countKHDK;
    int i=0,h=0;
    string hoten[n];
    while(p!=NULL){
        if(dh == 2)  (*p).getTenCacKH(hoten,i);
        else if(dh ==1) hoten[h++] = (*p).data.getTenKH();
        p = (*p).next_DK;
    }
    // sap xep theo selection sort
    int vt;
    for (int k = 0; k < n - 1; k++)
    {
        vt = k;
        for (int j = k + 1; j < n; j++)
            if (getTen(hoten[vt]) > getTen(hoten[j]))
                vt = j;
            else if(getTen(hoten[vt]) == getTen(hoten[j])){
                if (getHo(hoten[vt]) > getHo(hoten[j])) vt = j;
            }
        hoanvi(hoten[vt], hoten[k]);
    }
    // in ra
    if(dh==2){
        cout << "- Danh sach khach hang luu tru: "<<endl;
    cout<<"So luong: "<<head->getSLKH()<<endl;
    cout << setw(3)<<"STT";
    cout <<setw(10)<<"Ma DK"<<setw(12)<<"Ma KH"<<setw(18)<<"Ten KH"<<setw(12)<<"SDT"<<setw(11)<<"CCCD"<<setw(15)<<"Dia chi";
    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl; 
    }else{
        cout <<endl<< "\t- Danh sach khach hang dang ki: "<<endl;
        cout <<setw(3)<<"STT"<< setw(12) << "Ma so DK"<<setw(12)<<"Ma KH"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(13)<<"CCCD"<<setw(11)<<"Gio DK";
        cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<setw(14)<<"Ngay den"<<"\tPhong thue"<<endl;
    }
    for(int j=0;j<n;j++){
        p = head;
        cout << setw(3)<<j+1;
        while(p!=NULL){
            if(dh==2)(*p).DisplayKHSX(hoten[j]);
            else if(hoten[j] == (*p).data.getTenKH()) (*p).XuatDK();
            p = (*p).next_DK;
        }
    }   
}
void DSDK::SapXepHD(){
    if(head == NULL) cout << "Danh sach rong."<<endl;
    else{
        qldk p = head;
        int n =(*p).getSLHD(),i=0;
        cout <<"So luong: "<< n<<endl;
        int ngay[n];
        while(p!=NULL){
            (*p).getNgayCacHD(ngay,i);
            p = (*p).next_DK;
        }
        // sap xep theo selection sort
        int vt;
        for (int k = 0; k <=i; k++)
        {
            vt = k;
            for (int j = k + 1; j < n; j++)
                if (ngay[vt] > ngay[j])
                    vt = j;
                else if(ngay[vt] == ngay[j]){
                    if (ngay[vt] > ngay[j]) vt = j;
                }
            hoanvi(ngay[vt], ngay[k]);
        }
        for(int j=0;j<=i;j++){
            p = head;
            while(p!=NULL){ 
                (*p).DisplayHDSX(ngay[j]);
                p = (*p).next_DK;
            }
        }   
    }
}
