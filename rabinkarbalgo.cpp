#include<iostream>
#include<string>
using namespace std;

class hashing{
    public:

    hashing(){

    }
    void match(string pattern , string text , int val){
        //initially calculating the length
        int patlength = pattern.length();
        int txtlength = text.length();

        //now will calc the initial hash value upto the length of the pattern
        int phash = 0;
        int thash = 0;
        for(int i=0;i<patlength;i++){
            phash = (phash + pattern[i])%val;
            thash = (thash + text[i])%val;
        }
        bool flag = true;
        //searching loop
        for(int i=0;i<txtlength-patlength+1;i++){
            cout<<"thash: "<<thash<<" "<<"phash: "<<phash<<" "<<endl;
            //if the hashvalues are same
            if(thash == phash){
                //now we will run a loop and check if the character match or not
                //int j=0;
                for(int k=0;k<patlength;k++){
                    flag = true;
                    if(pattern[k] != text[k+i]){
                        flag = false;
                        break;
                    }
                }
                if(flag == true){
                    cout<<"The pattern is found at: "<<i<<endl;
                }
                if(i < txtlength-patlength+1){
                    	thash = ((thash - text[i]) + text[i+patlength])%val;
                	}
            }
            //if the hash value are not same so we will move one character ahead and will calc the hashvalue again
            else{
                //chechking is the value of i is small enough to check the check the substring
                if(i < txtlength-patlength+1){
                    thash = ((thash - text[i]) + text[i+patlength])%val;
                }
            }
        }
    }
};

int main(){
    string pattern = "bda";
    string text= "abcdefgbdaeqsbadbda";
    hashing h;
    h.match(pattern,text,256);
}