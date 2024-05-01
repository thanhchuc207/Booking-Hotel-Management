#include <iostream>
#include "KhachHang.h"
#include "Phong.h"
#ifndef DANGKI_H
#define DANGKI_H 
class DangKi{ 
    protected: 
        string MaDK,NgayDK;
        int SLP,SLN,GioDK;
        P PhongDK;//quản lí phòng đk
        string CCCD,TenKH,DiaChi;
        int SDT;
    public:
        DangKi(){};
        DangKi(string MaDK,string TenKH,string CCCD,int SDT, int SLP, int SLN,int GioDK,string NgayDK, Phong *,string DiaChi="");
        ~DangKi();
        void Display();
        //để in ra file
        string getMaDK(){return MaDK;}
        string getNgayDK(){return NgayDK;}
        string getCCCD() const{return CCCD;}
        int getSDT()const{return SDT;}
        string getTenKH()const{return TenKH;}
        int getSLP(){return SLP;}
        int getSLN(){return SLN;}
        int getGioDK(){return GioDK;}      
        friend int getNgay(string);
        friend class QLKH;
        friend class QLDK;
        friend class DSDK;
};
#endif
DangKi::~DangKi(){
    delete [] PhongDK;
}
void DangKi::Display(){
    cout<<setw(12) <<MaDK<<setw(15)<<CCCD<<setw(25)<<TenKH;
    if(SDT>0) cout<<setw(5)<<"0"<<SDT;
    else cout << setw(14)<<SDT;
    cout<<setw(8)<<GioDK/100<<":";
    if(GioDK %100 <10) cout << "0"<<GioDK %100;
    else cout <<setw(2)<<GioDK%100;
    cout <<setw(16) <<NgayDK << setw(5) <<SLP<<setw(5)<<SLN<<"\t";
    for(int i=0; i<SLP; i++){
        cout<<PhongDK[i].getMaPhong()<<" ";
    }
    cout<<endl;

}
DangKi::DangKi(string MaDK,string TenKH,string CCCD,int SDT, int SLP, int SLN,int GioDK,string NgayDK, Phong *p_dk,string DiaChi)
:TenKH(TenKH),MaDK(MaDK),SLP(SLP),SLN(SLN),NgayDK(NgayDK),GioDK(GioDK),CCCD(CCCD),SDT(SDT),DiaChi(DiaChi)
{
    PhongDK = new Phong[SLP];
    for(int i=0; i<SLP; i++)    
        PhongDK[i]=p_dk[i];
}
/*
Khi có khách hàng đăng ký phòng:
- Mở file Phong.txt
- Xuất danh sách phòng trống
- Nhập phòng đăng ký
- Update dữ liệu vào file Phong.txt (trạng thái: 0-trống,1-đã đk)
*/
/*
- Khách tới đk, cập nhật vào ds đk và ds lưu trữ
- Khách thanh toán,nhập ngày thanh toán, xuất hóa đơn (hóa đơn k xóa mà để để thống kê), xóa khách khỏi ds đk và đk lưu trữ
- 
*/