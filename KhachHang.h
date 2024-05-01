#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;
 
#ifndef KHACHHANG_H  
#define KHACHHANG_H
typedef class KhachHang* KH;
class KhachHang{
    protected:
        string MaKH,CCCD,TenKH,DiaChi,NgayDen,NgayDi;
        int SDT,GioDen,GioDi;
        int MaPhong;
    public:
        KhachHang();
        KhachHang(string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen=0,int GioDi=0,string NgayDi="",string DiaChi="",int MaPhong=0);
        ~KhachHang(){};
        void Display(); 
        string getNgayDen() const {return NgayDen;}
        string getCCCD() const{return CCCD;}
        int getSDT()const{return SDT;}
        string getTenKH()const{return TenKH;}
        string getMaKH()const{return MaKH;}
        int getMaPhong() const{return MaPhong;}
        int getGioDen()const{return GioDen;}
        int getGioDi()const{return GioDi;}
        string getNgayDi()const{return NgayDi;}
        string getDiaChi()const{return DiaChi;}
        friend int getNgay(string);
        friend class QLDK;
};

class DSKH
{
    KhachHang *data;
    DSKH* next;
    public:
    friend DSKH* createKH(KhachHang*);
    void HuyDSKH();
    void Insert( DSKH*);
    friend void HuyKHfirst(DSKH* x);
    void Display();
    friend class QLDK;
    friend class DSDK;
};
DSKH* createKH(KhachHang*);
void HuyKHfirst(DSKH* x);
#endif
KhachHang::KhachHang(string MaKH,string TenKH,string NgayDen,int SDT,string CCCD,int GioDen,int GioDi, string NgayDi,string DiaChi,int MaPhong)
:MaKH(MaKH),CCCD(CCCD),TenKH(TenKH),SDT(SDT),GioDen(GioDen),NgayDen(NgayDen),GioDi(GioDi),NgayDi(NgayDi),DiaChi(DiaChi),MaPhong(MaPhong) {}
KhachHang::KhachHang(){}
int getNgay(string ngay){
    char x[3];
    string(ngay).copy(x,2);
    x[3]='\0';
    return atoi(x);
}

void KhachHang::Display(){
    cout <<setw(12)<<MaKH;
    cout <<setw(18)<<CCCD<<setw(25)<<TenKH;
    if(SDT>0) cout<<setw(5)<<"0"<<SDT;
    else cout << setw(14)<<SDT;
    cout<<setw(15)<<DiaChi<<setw(8)<<GioDen/100 << ":";
    if(GioDen %100 <10) cout << "0"<<GioDen %100;
    else cout <<setw(2)<<GioDen%100;
    cout <<setw(12)<< NgayDen;
    cout<<setw(8)<<GioDi/100<<":";
    if(GioDi %100 <10) cout << "0"<<GioDi %100;
    else cout <<setw(2)<<GioDi%100;
    cout <<setw(12)<< NgayDi;
    cout <<setw(10)<<MaPhong<<endl; 
}

void DSKH::HuyDSKH()
{
	delete data;
}
DSKH* createKH(KhachHang* p)
{
    DSKH* temp=new DSKH;
    temp->data=p;
    temp->next=NULL;
    return temp;
}
void DSKH::Insert(DSKH* x)
{
		DSKH* temp=this;
	    while(temp->next!=NULL)
	    {
			temp = temp->next;
		}
	    temp->next=x;    
}
void HuyKHfirst(DSKH* x)
{
    DSKH* temp=x;
    x=x->next;
    delete temp->data;
    delete temp;
}
void DSKH::Display()
{
    data->Display();

}
