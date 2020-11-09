#include <iostream>

using namespace std;


int main()
{
    short int tran_amt;
    char msg[10];
    char Card_ID[10] = "test001";                   //needs to be changed
    short int balance = 499;
    cout<<"Card_ID: "<< Card_ID <<endl;
    cout<<"Initial Balance: "; cout << balance<<endl;
    cout<<"Received message(10 digit):";
    cin>> msg;
    //decoding msg
    if(msg[4]=='1'&& msg[5]=='2'&& msg[6]=='3')     //5th 6th and 7th digit act as password;
    {                                                 //1st-4th digits don't care;
        tran_amt= (msg[7]-48)*10+(msg[8]-48);       // 8th and 9th digit contain the transaction amount
        if(msg[9]=='1')                           //1: Recharge and 0: pay in the 10th digit
            balance+=tran_amt;
        else
            balance-=tran_amt;
        cout<<"Transaction successful"<<endl;
        cout<<"Current Balance: " << balance;
    }
    else
        cout<<"Authentication faild: Check password";
    return 0;
}
