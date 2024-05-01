#include <fstream>
#include "DSDK.h"
#include <cstdlib>

void KiemTraFilePhong();
void NhapFileDK(DSDK &dk);
void KiemTraFileDK();
void NhapFileKH(DSDK &dk);
void KiemTraFileKH(DSDK &dkp);
void DisplayTopic();
void DisplayMenu1();
void DisplayObject();
void DisplayObject2();
void DisplayObject3(); 
void ChooseDelete();
void ChooseOutput();

void Case1(DSDK &x);
void Case2(DSDK &x);
void Case3(DSDK &x);
void Case4(DSDK &x);
void Case5(DSDK &x);
void Case6(DSDK &x);

void Default();
static int choose=0;
static char c='c';

string DoiTen(string Ten);
int getNgay(string ngay);
int main(){
    try
    {
        KiemTraFilePhong();
    }
    catch(const char* msg)
    {
        cout<<endl<<"Loi du lieu file Phong.txt";
        cerr<<msg;
        exit(0);
    };
    ROOM=TaoDSPhong(ROOM); 
    DSDK dk;
    FILE *f_KH; 
    try
    {
        KiemTraFileDK();
    }
    catch(const char* msg)
    {
        cout<<"Loi du lieu file Dangky.txt"<<endl;
        cerr<<endl<<msg;
        exit(0);
    };
    NhapFileDK(dk);
    int kt=0;
    try
    {
        KiemTraFileKH(dk);//kiem tra co ton tai MaDK khong
        kt=1;
    }
    catch(const char* msg)
    {
        cout<<"Loi du lieu file Khachhang.txt"<<endl;
        cerr<<endl<<msg;
        exit(0);
    };
    
    if(kt==0) NhapFileKH(dk);
   
    while(c=='c'){
again:  system("cls");
        DisplayTopic();
        DisplayMenu1();
        cout<<"\tMoi ban chon: ";
        string t; cin>>t;
        choose=atoi(t.c_str());  
        switch(choose){
            case 7: 
                exit(0);
            case 1:
                Case1(dk);
                break;
            case 2:
                Case2(dk);
                break;
            case 3:
                Case3(dk);
                break;
            case 4:
                Case4(dk);
                break;
            case 5:
                Case5(dk);
                break;
            case 6:
                Case6(dk);
                system("pause");
                break;
            default:
                Default();
                goto again;
        }
    }
    //HuyDSPhong(x);
    return 0;
}
void KiemTraFilePhong()
{
    fstream f_phong;
    f_phong.open("Phong.txt",ios::in);
    string t;
    f_phong>>SLPhongMax;
    int A[SLPhongMax];
    for(int i=1;i<=SLPhongMax;i++)
    {
        f_phong>>A[i]; //kiem tra co trung MaPhong khong
        getline(f_phong,t,'\n');
    }
    string tm;
    getline(f_phong,tm,'\n');
        if(tm.length()!=0) throw "Du du lieu";
    f_phong.close();
    for(int i=1;i<SLPhongMax;i++)
    {
        for(int j=i+1;j<=SLPhongMax;j++)
        {
            if(A[i]==A[j]) throw "Trung Ma phong";
        }
    }
}
void KiemTraFileDK()
{
     ifstream f_dk;
    f_dk.open("DangKy.txt",ios::in);
    string MaDK,CCCD,TenKH,NgayDK,NgayDen;
    int SDT,SLN,SLP,SLDK,GioDK;
    f_dk>>SLDK;
    string A[SLDK+1], C[SLDK+1];
     f_dk.ignore();
    for(int i =1;i<=SLDK;i++)
    {   
        getline(f_dk,MaDK,'\t');
        if(MaDK.length()!=6) throw "Loi dinh dang MaDK";
        A[i]=MaDK;
    	getline(f_dk,CCCD,'\t');
        if(CCCD.length()!=12) throw "Loi dinh dang CCCD";
        C[i]=CCCD;
    	getline(f_dk,TenKH,'\t');
        f_dk>>SDT;
        if(999999999-SDT<0) throw "Loi dinh dang SDT";
    	f_dk>>GioDK;
        if (GioDK<0 || GioDK>2359) throw "Loi dinh dang GioDK";
    	f_dk.ignore();
    	getline(f_dk,NgayDK,'\t');
        if(NgayDK.length()!=10) throw "Loi dinh dang NgayDK";
    	f_dk>>SLP;
        if (SLP<1 || SLP >SLPhongMax) throw "Loi dinh dang So luong phong";
        int p_dk=0;
        for(int i=0; i<SLP; i++){
            int MaPhong;
            f_dk>>MaPhong;
            p_dk=p_dk+ROOM->SLKmax(MaPhong);
        }
        f_dk>>SLN;
        if (SLN<1) throw "Loi dinh dang So luong nguoi";
        if(p_dk<SLN) throw "So luong khach vuot so luong so luong quy dinh cua phong";
        f_dk.ignore();
    	getline(f_dk,NgayDen,'\n');
    }
    string tm;
    getline(f_dk,tm,'\n');
    if(tm.length()!=0) throw "Du du lieu";
    f_dk.close();
    for(int i=1;i<SLDK;i++)
        {
            for(int j=i+1;j<=SLDK;j++)
            {
                if(A[i]==A[j]) throw "Trung ma dang ky";
                if(C[i]==C[j]) throw"Trung CCCD";
            }
        }
}
void NhapFileDK(DSDK &dk){ 
    ifstream f_dk;
    f_dk.open("DangKy.txt",ios::in);
    string MaDK,CCCD,TenKH,NgayDK,NgayDen;
    int SDT,SLN,SLP,SLDK,GioDK;
    f_dk>>SLDK;
     f_dk.ignore();
    for(int i =1;i<=SLDK;i++){
        getline(f_dk,MaDK,'\t');
    	getline(f_dk,CCCD,'\t');
    	getline(f_dk,TenKH,'\t');
        f_dk>>SDT;
    	f_dk>>GioDK;
    	f_dk.ignore();
    	getline(f_dk,NgayDK,'\t');
    	f_dk>>SLP;
        P p_dk =new Phong[SLP];
        for(int i=0; i<SLP; i++){
            int MaPhong;
            f_dk>>MaPhong;
            p_dk[i].Nhap(MaPhong);
            ROOM->Update(MaPhong,0);
        }
        f_dk>>SLN;
        f_dk.ignore();
    	getline(f_dk,NgayDen,'\n');
        string TKH;
        TKH = DoiTen(TenKH);
        // lưu thông tin kh dk bằng cách thêm vào cuối dslk
        dk.ThemVaoViTriDK(MaDK,TKH,CCCD,SDT,SLP,SLN,GioDK,NgayDK, p_dk);
    }
    f_dk.close();
}
void KiemTraFileKH(DSDK &dkp)
{
    /*
    -Co ton tai madk khong
    -Co dung ma phong da dang ky khong
    -Co trung ma KH khong
    -Co dung so luong khach da dang ky khong
    */
    ifstream f_kh;
    f_kh.open("KhachHang.txt",ios::in);
    string MaDK,MaKH,CCCD,TenKH,DiaChi,NgayDen,NgayDi;
    int SDT,SLK,GioDen,GioDi,MaPhong;
    f_kh>>SLK;
    string A[SLK+1],B[SLK+1],C[SLK+1];
    f_kh.ignore();
    for(int i =1;i<=SLK;i++)
    {
        getline(f_kh,MaDK,'\t');
        if(MaDK.length()!=6) throw "Loi MaDK";
        A[i]=MaDK;
    	getline(f_kh,MaKH,'\t');
        if(MaKH.length()!=6) throw "Loi MaKH";
        B[i]=MaKH;
    	getline(f_kh,CCCD,'\t');
        if(CCCD.length()!=12) throw "Loi CCCD";
        C[i]=CCCD;
        getline(f_kh,TenKH,'\t');
        f_kh>>SDT;
        if(999999999-SDT<0) throw "Loi SDT";
    	f_kh>>GioDen;
        if (GioDen<0 || GioDen>2359) throw "Loi GioDen";
        f_kh.ignore();
    	getline(f_kh,NgayDen,'\t');
        if(NgayDen.length()!=10 ) throw "Loi NgayDen";
        char tt[3];
        strncpy(tt,NgayDen.c_str(),2);
        tt[2]='\0';
        if(atoi(tt)<1 || atoi(tt)>31) throw "Loi NgayDen";
        f_kh>>GioDi;
        if (GioDi<0 || GioDi>2359) throw "Loi GioDK";
        f_kh.ignore();
    	getline(f_kh,NgayDi,'\t');
        if(NgayDi.length()!=10 || atoi(NgayDi.c_str())<atoi(NgayDen.c_str()) ||   atoi(NgayDi.c_str())==atoi(NgayDen.c_str()) && (GioDi<=GioDen))
            throw "Loi NgayDi";
        strncpy(tt,NgayDi.c_str(),2);
        tt[2]='\0';
        if(atoi(tt)<1 || atoi(tt)>31) throw "Loi NgayDen";
        f_kh>>MaPhong;
        if(ROOM->TimPhong(MaPhong)==0) throw "Khong ton tai ma phong";
        f_kh.ignore();
    	getline(f_kh,DiaChi,'\n');
        string TKH,DC;
        TKH = DoiTen(TenKH);
        DC = DoiTen(DiaChi);
        dkp.TimVaThemKH(MaDK,MaKH,TKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DC,MaPhong,1);
        dkp.TimVaThemHD(MaDK,MaPhong,NgayDen,NgayDi);
    }
    string tm;
    getline(f_kh,tm,'\n');
    if(tm.length()!=0) throw "Du du lieu";
    f_kh.close();
    for(int i=1;i<SLK;i++)
    {
        for(int j=i+1;j<=SLK;j++)
        {
            if(B[i]==B[j]) throw "Trung Ma khach hang";
            if(C[i]!="0" && C[j]!="0" && C[i]==C[j]) throw "Trung CCCD";
        }
    }
}
void NhapFileKH(DSDK &dk){
     ifstream f_kh;
    f_kh.open("KhachHang.txt",ios::in);
    string MaDK,MaKH,CCCD,TenKH,DiaChi,NgayDen,NgayDi;
    int SDT,SLK,GioDen,GioDi,MaPhong;
    f_kh>>SLK;
    f_kh.ignore();
    for(int i =1;i<=SLK;i++){
        getline(f_kh,MaDK,'\t');
    	getline(f_kh,MaKH,'\t');
    	getline(f_kh,CCCD,'\t');
        getline(f_kh,TenKH,'\t');
        f_kh>>SDT;
    	f_kh>>GioDen;
        f_kh.ignore();
    	getline(f_kh,NgayDen,'\t');
        f_kh>>GioDi;
        f_kh.ignore();
    	getline(f_kh,NgayDi,'\t');
        f_kh>>MaPhong;
        f_kh.ignore();
    	getline(f_kh,DiaChi,'\n');
        string TKH,DC;
        TKH = DoiTen(TenKH);
        DC = DoiTen(DiaChi);
        //kiem tra file co ton tai madk khong
        dk.TimVaThemKH(MaDK,MaKH,TKH,NgayDen,SDT,CCCD,GioDen,GioDi,NgayDi,DC,MaPhong,0);
        dk.TimVaThemHD(MaDK,MaPhong,NgayDen,NgayDi);//tạo hóa đơn và lưu thông tin hóa đơn bằng cách thêm vào cuối dslk
    }
    f_kh.close();
}
void DisplayTopic(){

    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(13)<<"======="<<" DO AN CO SO LAP TRINH "<<"======="<<setw(6)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    cout<<setw(27)<<"|"<<"\tDE TAI:\t QUAN LI KHACH O KHACH SAN"<<setw(10)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(33)<<"TRONG 1 THANG"<<setw(16)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(43)<<"Giang vien huong dan: TS Le Thi My Hanh"<<setw(6)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(39)<<" Sinh vien thuc hien: Pham Tran Thanh Truc"<<setw(7)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(42)<<" Lop: 21TCLC_DT3"<<setw(7)<<"|"<<endl;
    
    cout<<setw(27)<<"|"<<setw(35)<<"Huynh Duy Tin"<<setw(14)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(42)<<" Lop: 21TCLC_DT1"<<setw(7)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(49)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl<<endl;
}
void DisplayMenu1(){
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(21)<<"~~~~~~~~"<<" MENU "<<"~~~~~~~~"<<setw(14)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"1) Hien thi danh sach hien thoi."<<setw(15)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(14)<<"2) Tim kiem."<<setw(35)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(23)<<"3) Sap xep danh sach."<<setw(26)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(32)<<"4) Xoa danh sach theo yeu cau."<<setw(17)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(21)<<"5) Them khach hang."<<setw(28)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(25)<<"6) Thong ke trong ngay."<<setw(24)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(11)<<"7) Thoat."<<setw(38)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void DisplayObject(){
    cout<<endl<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(16)<<""<<" DOI TUONG "<<""<<setw(22)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"1) Khach hang dang ki."<<setw(15)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"2) Khach hang luu tru."<<setw(15)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(23)<<"3) Hoa don."<<setw(26)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(24)<<"4) Quay lai."<<setw(25)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void DisplayObject2(){
    cout<<endl<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(16)<<""<<" DOI TUONG "<<""<<setw(22)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"1) Khach hang dang ki."<<setw(15)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"2) Khach hang luu tru."<<setw(15)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(24)<<"3) Quay lai."<<setw(25)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void DisplayObject3(){
    cout<<endl<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(16)<<""<<" DOI TUONG "<<""<<setw(22)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    //cout<<setw(27)<<"|"<<setw(29)<<"1) Dang ki da co."<<setw(20)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(24)<<"1) Quay lai."<<setw(25)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(31)<<"2) Tao dang ki moi."<<setw(18)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void ChooseOutput(){
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(10)<<""<<" PHUONG THUC XUAT KET QUA "<<""<<setw(13)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    cout<<setw(27)<<"|"<<setw(27)<<"1) Truc tiep."<<setw(22)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(22)<<"2) File."<<setw(27)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void ChooseDelete(){
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
    cout<<setw(27)<<"|"<<setw(30)<<" CACH THUC XOA "<<setw(19)<<"|"<<endl;
    cout<<setw(76)<<"|------------------------------------------------|"<<endl;
    cout<<setw(27)<<"|"<<setw(32)<<"1) Xoa theo vi tri."<<setw(17)<<"|"<<endl;
    cout<<setw(27)<<"|"<<setw(34)<<"2) Xoa theo tieu chi."<<setw(15)<<"|"<<endl;
    cout<<setw(76)<<"<------------------------------------------------>"<<endl;
}
void Default(){
    cout<<"\tNHAP LOI"<<endl;
    cout<<"\t1) Nhap lai."<<endl;
    cout<<"\t2) Thoat."<<endl;
    cout<<"\tMoi ban nhap: ";
    string t; cin>>t;
    choose=atoi(t.c_str());  
}
void Case1(DSDK &x){
    while(c=='c'){
again0:  DisplayObject();
        cout<<"\tMoi ban chon: "; cin>>choose;
        switch(choose){
            case 4:
                return;
            case 1:
again1:         ChooseOutput();
                cout<<"\tMoi ban chon: "; cin>>choose;
                if(choose==1) x.DisplayDK();
                else if(choose==2) x.fileOutDK();
                else{
df1:                Default();
                    if (choose==1) goto again1;
                    else if(choose == 2);
                    else goto df1;
                }
                break;
            case 2:
again2:         ChooseOutput();
                cout<<"\tMoi ban chon: "; cin>>choose;
                if (choose==1) x.DisplayKH(); 
                else if(choose==2) {
                    cout<<"\tNhap file OUT : ";
                    char TenFile[100];
                    cin>>TenFile;
                    strcat(TenFile, ".txt");
                    x.fileOutKH(TenFile);
                }
                else{ 
df2:                Default(); 
                    if (choose==1) goto again2;
                    else if(choose == 2);
                    else goto df2;
                }
                break;
            case 3:
again3:         ChooseOutput();
                cout<<"\tMoi ban chon: "; cin>>choose;
                if(choose==1) x.Display_DS_HD();
                else if(choose==2) x.fileOutHD();
                else{
df3:                Default();
                    if (choose==1) goto again3;
                    else if(choose == 2);
                    else goto df3;
                }
                break;
            default:
df:             Default();
                if (choose==1) goto again0;
                else if(choose == 2);
                else goto df;
        }
    }
}
void Case2(DSDK &x){
    while(c=='c'){
        string date;
again0: DisplayObject();
        cout<<"\tMoi ban chon: "; string t; cin>>t;
    choose=atoi(t.c_str());
        switch(choose){
            case 4:
                return ;
            case 1:
                x.DisplayDK_Condition();
                break;
            case 2:
                x.DisplayKH_Condition(); 
                break;
            case 3:
                cout<<"\tNhap ngay xuat Hoa don: "; cin>>date;
                x.Display_DS_HD(getNgay(date)); 
                break;
            default:
df:             Default();
                if (choose==1) goto again0;
                else if(choose == 2);
                else goto df;
        }
    }
}
void Case3(DSDK &x){
    while(c=='c'){
again0:  DisplayObject();
        cout<<"\tMoi ban chon: "; string t; cin>>t;
    choose=atoi(t.c_str()); 
        switch(choose){
            case 4:
                return ;
            case 1:
                x.SapXepKH(1);
                break;
            case 2:
                x.SapXepKH(2);
                break;
            case 3:
                x.SapXepHD();
                break;
            default:
df:             Default();
                if (choose==1) goto again0;
                else if(choose == 2);
                else goto df;
        }
    }
}
void Case4(DSDK &x){
    while(c=='c'){
again0:  DisplayObject2();
        cout<<"\tMoi ban chon: "; string t; cin>>t;
    choose=atoi(t.c_str()); 
        switch(choose){
            case 3:
                return ;
            case 1:
again1:         ChooseDelete();
                cout<<"\tMoi ban chon: "; cin>>choose;
                if(choose==1){
                    x.DisplayDK();
                    int vt;
                    cout << "Nhap vi tri can xoa: ";
                    cin >> vt;
                    cout << "Thong tin khach hang da xoa: "<<endl;
                    cout <<setw(12) << "Ma so DK"<<setw(20)<<"Ten KH DK"<<setw(14)<<"SDT"<<setw(13)<<"CCCD"<<setw(11)<<"Gio DK";
                    cout << setw(14) << "Ngay DK" << setw(5) << "SLP"<<setw(5)<<"SLN"<<"\tPhong thue"<<endl;
                    x.DeleteDK_vt(vt);
                } else if(choose == 2) x.DeleteDK_dk();
                else{
df1:                Default();
                    if (choose==1) goto again1;
                    else if(choose == 2);
                    else goto df1; 
                }
                break;
            case 2:
again2:         ChooseDelete();
                cout<<"\tMoi ban chon: "; cin>>choose;
                if(choose==1){
                    x.DisplayKH();
                    int vt;
                    cout << "Nhap vi tri can xoa: ";
                    cin >> vt;
                    cout << "Thong tin khach hang da xoa: "<<endl;
                    cout <<setw(12)<<"Ma KH"<<setw(18)<<"CCCD"<<setw(25)<<"Ten KH"<<setw(13)<<"SDT"<<setw(16)<<"Dia chi";
                    cout <<setw(11)<<"Gio den"<<setw(12)<< "Ngay den" << setw(11) <<" Gio di"<<setw(12)<<"Ngay di"<<setw(10)<<"Ma phong"<<endl; 
                    x.DeleteKH_vt(vt);
                }  else if(choose == 2) x.DeleteKH_dk();    
                else{
df2:                Default();
                    if (choose==1) goto again2;
                    else if(choose == 2);
                    else goto df2; 
                }          
                break;
            default:
df:             Default();
                if (choose==1) goto again0;
                else if (choose==2);
                else goto df;
        }
    }
}
void Case5(DSDK &x){
    while(c=='c'){
again0:  DisplayObject3();
        cout<<"\tMoi ban chon: "; string t; cin>>t;
    choose=atoi(t.c_str()); 
        switch(choose){
            case 1:
                return ;
        /*    case 1:
                {
                string MaDK;
again1:         x.DisplayDK();
                cout << "Nhap ma dang ki: ";
                cin >> MaDK;
                int i=x.KiemTraMaDK(MaDK);
                while(i==0){
                    cout << "Khong co ma dang ki nay."<<endl;
df1:                cout << "1) Nhap lai ma dang ki."<<endl;
                    cout << "2) Thoat."<<endl;
                    cin >> choose;
                    if(choose == 1) goto again1;
                    else if(choose ==2) goto df3;
                    else{
df2:                Default();
                    if(choose == 1) goto  df1;
                        else if(choose != 2) goto df2;
                        else if(choose == 2) goto df3;
                    }
                }
                try
                {
                    x.ThemKH(MaDK,0,ROOM);// -1: thêm vào cuối, 0: thêm kh vào đk đã có
                } 
                catch(const char* msg)
                {
                    cerr<<msg<<endl;
                    goto again0;
                };
                }*/
df3:            break;
            case 2:
            try
                {
                    x.ThemKH("0",1,ROOM);// -1: thêm vào cuối, 0: thêm kh vào đk đã có
                } 
                catch(const char* msg)
                {
                    cerr<<msg<<endl;
                    goto again0;
                };
                break;
            default:
df:             Default();
                if (choose==1) goto again0;
                else if(choose == 2);
                else goto df;
        }
    }
}
void Case6(DSDK &x){
    string d;
    cout<<endl<<"\tNhap ngay can thong ke:(dd/mm/yy): "; cin.ignore(); cin>>d;
    int day=getNgay(d);
    x.DisplayDK(day);//khdk
    cout<<endl;
    x.DisplayKH_Condition(day);//khlt
    cout<<endl;
    x.Display_DS_HD(day);//hóa đơn
    int MP[60];
    x.KiemTraPhong(d,0);
    int SoPhongFull = KTPhong(MP);
    cout << "\n- Tinh trang phong: ";
    // in phong da co nguoi thue
    if(SoPhongFull != 0){ 
        cout <<endl<< "So phong trong: "<< SLPhongMax - SoPhongFull<<endl;
        cout << "So phong da co nguoi thue: "<< SoPhongFull<<endl;
        cout << "Nhung phong da co nguoi thue: ";
        for(int i=0;i<SoPhongFull;i++){
            cout << MP[i] ;
            if(i==SoPhongFull-1) cout<< "."<<endl;
            else cout << ", ";
        }
    }else cout << "Khong co phong nao full.\n";
    cout<<endl;
}
string DoiTen(string Ten){
    int i=Ten.size();
    string T;
    for(int j =0;j<i-1;j++){
        if(Ten[j]!=' '|| (Ten[j]== ' ' && Ten[j+1]!=' ' )){
            T += Ten[j];
        }
    }
    T += Ten[i-1];
    return T;
}
