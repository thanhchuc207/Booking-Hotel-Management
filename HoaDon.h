#ifndef HOADON_H
#define HOADON_H
#include <iostream>
#include <string.h> 
#include <cstdlib> 
using namespace std;
#include"Phong.h"
#include <iomanip>
typedef class HoaDon* HD;
class HoaDon
{
private:
    string MaHD,NgayDen,NgayDi; //MaHD=CCCD
public:
    Phong a;
    HoaDon(int MaPhong,string NgayDen="",string NgayDi="");
    void Display();
    int SoNgayO();
    int ThanhTien();
    friend class QLKH;
    string getMaHD(){return MaHD;}
    string getNgayHD(){return NgayDi;}
    int getNgay(string);
};
class DSHD
{
    HoaDon* data;
    DSHD* next;
    public:
    friend DSHD* createHD(HoaDon*);
    friend void HuyHDfirst(DSHD*);
    void HuyDSHD();
    void Display();
    friend class QLDK;
    friend class DSDK;
};
DSHD* createHD(HoaDon*);
void HuyHDfirst(DSHD*);
#endif
HoaDon::HoaDon(int MaPhong,string NgayDen,string NgayDi):a(MaPhong),NgayDen(NgayDen),NgayDi(NgayDi){
    // tạo mã hóa đơn = HD<Mã phòng><Ngay đến><ngày đi>, ngày đên và ngày đi chỉ lấy ngày ko lấy tháng năm
    a.Nhap(MaPhong);
    char NgDen[3],NgDi[3];
    string(NgayDen).copy(NgDen,2);
    string(NgayDi).copy(NgDi,2);
    NgDen[2]='\0'; //Thêm ký tự kết thúc chuỗi 
    NgDi[2]='\0';
    if(MaPhong<10) MaHD = "HD0"+to_string(MaPhong)+NgDen+ NgDi;//mã hóa đơn = HD<Mã phòng><Ngay đến><ngày đi> 
    else MaHD = "HD"+to_string(MaPhong)+NgDen+ NgDi;//mã hóa đơn = HD<Mã phòng><Ngay đến><ngày đi> 
    
}
void HoaDon::Display(){
    cout <<setw(15)<<MaHD<<setw(10)<<a.getMaPhong()<< setw(20)<<NgayDi<<setw(13)<<a.getDonGia();
    cout <<setw(10)<<SoNgayO()<<setw(15)<<ThanhTien()<<endl;
}
int HoaDon::SoNgayO(){
    char NgDen[100],NgDi[100];
    string(NgayDen).copy(NgDen,2);
    string(NgayDi).copy(NgDi,2);
    NgDen[2]='\0'; //Thêm ký tự kết thúc chuỗi 
    NgDi[2]='\0';
    int j =atoi(NgDi)-atoi(NgDen);
    if(j>0) return j;
    else return 1;
}
int HoaDon::ThanhTien(){
    return (*this).SoNgayO()*a.getDonGia();
}
int HoaDon::getNgay(string ngay){
    char x[3];
    string(ngay).copy(x,2);
    x[3]='\0';
    return atoi(x);
}

void HuyHDfirst(DSHD* x)
{
    DSHD* temp=x;
    x=x->next;
    delete temp->data;
    delete temp;
}
DSHD* createHD(HoaDon* x)
{
    DSHD* temp=new DSHD;
    temp->data=x;
    temp->next=NULL;
    return temp;
}
void DSHD::HuyDSHD()
{
    delete data;
}
void DSHD::Display()
{
    data->Display();
}
