#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#pragma once
const int DonGiaSingle=200;
const int DonGiaDouble=300;
const int DonGiaGroup=500;
const float DonGiaVip=1.5;

int SLPhongMax;
#ifndef PHONG_H
#define PHONG_H
int dem =1; 
FILE *f_phong;
typedef class Phong* P;
class Phong{ 
    protected:
        string  KieuPhong /*Single, Double, Group*/,LoaiPhong /*Standard, VIP*/;
        int MaPhong,DonGia;
    public:
        Phong(){};
        Phong(int );
        Phong(int,string,string);
        ~Phong(){};
        void Nhap(int Ma);
        void Display();
        int getDonGia(){return DonGia;}
        int getMaPhong(){return MaPhong;}
        string getKieuPhong(){return KieuPhong;}
        friend int KTPhong(int MP[60]);
        
        friend class QLDK;
        friend class DangKi;
        friend class DSP;
};
int Gia(string,string);
class DSP
{
    Phong* data;
    int TrangThai;
    int SLK;
    DSP* next;
    public:
    friend DSP* TaoDSPhong(DSP*);
    friend DSP* createP(Phong*);
    void Insert(DSP *);
    void Display();
    friend void DSPhong(DSP* );
    friend void HuyDSPhong(DSP*);
    friend int KTPhong(int MP[60]);
    void HuyPhong();
    void Update(int,int);
    void TangGiamKhach(int MaPhong,int cv);
    int getSLK(int MaPhong);
    friend class QLKH;
    int SLKmax(int);
    int SLKToiDa();
    int TimPhong(int MaPhong);
};
DSP* ROOM; 
DSP* TaoDSPhong(DSP*);
DSP* createP(Phong*);
void DSPhong(DSP* );
void HuyDSPhong(DSP*);
#endif
Phong::Phong(int Ma)
{
    ifstream f_phong;
    f_phong.open("Phong.txt",ios::in);
    int SLPhongMax,n;
    f_phong>>SLPhongMax;
    string t;
    for(int i=0;i<Ma;i++)
    {
    	getline(f_phong,t,'\n');
    }
    f_phong>>MaPhong;
    f_phong>>KieuPhong;
    f_phong>>LoaiPhong;
    f_phong.close();
    DonGia = Gia(KieuPhong,LoaiPhong);
}
Phong::Phong(int MaPhong,string KieuPhong, string LoaiPhong):MaPhong(MaPhong),KieuPhong(KieuPhong),LoaiPhong(LoaiPhong)
{
    DonGia=Gia(KieuPhong,LoaiPhong);
    
}
void Phong::Nhap(int Ma){
    ifstream f_phong;
    f_phong.open("Phong.txt",ios::in);
    int SLPhongMax,n;
    f_phong>>SLPhongMax;
    f_phong.ignore();
    string t;
    for(int i=1;i<Ma;i++)
    {
    	getline(f_phong,t,'\n');
    }
    f_phong>>MaPhong;
    f_phong>>KieuPhong;
    f_phong>>LoaiPhong;
    DonGia = Gia(KieuPhong,LoaiPhong);
    f_phong.close();
}

int Gia(string K,string L){
    int G;
    if(K == "Single") G = DonGiaSingle;
    else    if(K == "Double") G = DonGiaDouble;
            else if(K == "Group") G = DonGiaGroup;
    if(L == "VIP") G = G*DonGiaVip;
    return G;
}

void Phong::Display(){
    cout << setw(10)<<MaPhong;
    cout << setw(15)<<KieuPhong;
    cout << setw(15)<<LoaiPhong;
    
    cout << setw(10)<<DonGia;
   // cout << setw(3) <<TrangThai<<endl;
}


DSP* createP(Phong* x)
{
    DSP* temp=new DSP;
    temp->data=x;
    temp->TrangThai = 0;
    temp->next=NULL;
    string KieuPhong=temp->data->getKieuPhong();
    temp->SLK=0;
    return temp;
}
void DSP::Insert(DSP* x)
{
    DSP* temp=this;
	    while(temp->next!=NULL)
	    {
			temp = temp->next;
		}
	    temp->next=x;    
}
void DSP::Display()
{
    data->Display();
}
void DSPhong(DSP* x){
cout<<endl<<"Danh sach phong:"<<endl;
   if(x != NULL)
    {
        cout <<setw(10)<<"Ma Phong"<< setw(15)<<"Kieu Phong"<<setw(15)<<"Loai Phong";
        cout << setw(10)<<"Don Gia"<< setw(15)<<"Trang Thai"<<endl;
        DSP* p= x;
        while(p!=NULL){
            (*p).Display();
            if(p->TrangThai==0) cout<<setw(13)<<"Trong"<<endl;
            else cout<<setw(15)<<"Da thue"<<endl;
            p = (*p).next;
        }
    }
}
void DSP::HuyPhong()
{
    delete data;
}
void HuyDSPhong(DSP* x)
{
    while(x!=NULL)
    {
        DSP* p=x;
        x=x->next;
        p->HuyPhong();
    }
}
void DSP::Update(int MaPhong,int cv)
{
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->MaPhong==MaPhong) 
        {
            if(cv==0) 
            {
                temp->TrangThai=1;
            }
            else if(cv==1)
            {
                temp->TrangThai=0; temp->SLK=0;
            }
            break;
        }
        temp=temp->next;
    } 
}
DSP* TaoDSPhong(DSP* x)
{
    fstream f_phong;
    f_phong.open("Phong.txt",ios::in);
    int MaPhong;
    string KieuPhong,LoaiPhong;
    f_phong>>SLPhongMax;
    for(int i=1;i<=SLPhongMax;i++)
    {
        f_phong>>MaPhong; //kiem tra co trung MaPhong khong
        f_phong>>KieuPhong;
        f_phong>>LoaiPhong;
        Phong* p=new Phong(MaPhong,KieuPhong,LoaiPhong);
        DSP* t=createP(p);
        if(i==1) x=t;
        else x->Insert(t);
    }
    f_phong.close();
    return x;
}
int KTPhong(int MP[60]){
        DSP* p=ROOM;
        int i=0;
        while (p!=NULL)
         {  
            if(p->TrangThai ==1)  //neu phong co nguoi
            {   
                MP[i] = (*p).data->MaPhong;
                i++;
            }
            p=p->next;
         }
         return i;
}
int DSP::SLKmax(int MaPhong)
{
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->MaPhong==MaPhong)
        {
            if(temp->data->KieuPhong=="Single") return 1;
            else if(temp->data->KieuPhong=="Double") return 2;
                else return 5;
        }
        temp=temp->next;
    }
}
void DSP::TangGiamKhach(int MaPhong,int cv)
{
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->MaPhong==MaPhong)
        {   temp->SLK+=cv;
            break;
        }
        temp=temp->next;
    }
}
int DSP::getSLK(int MaPhong)
{
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->MaPhong==MaPhong)
        {
            return temp->SLK;
        }
        temp=temp->next;
    }
}
int DSP::TimPhong(int MaPhong)
{
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->MaPhong==MaPhong)
        {
            return 1;
        }
        temp=temp->next;
    }
    return 0;
}
int DSP::SLKToiDa()
{   int n=0;
    DSP* temp=this;
    while(temp!=NULL)
    {
        if(temp->data->KieuPhong=="Single") n+=1;
        else    if(temp->data->KieuPhong=="Double") n+=2;
                else n+=5;
        temp=temp->next;
    }
    return n;
}