#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<bitset>
#include<queue>
#include<vector>
using namespace std;
// code that converts 2s complement binary to decimal
int binaryToInt(string binaryString) {
    int result = 0;
    int length = binaryString.length();
    bool isNegative = (binaryString[0] == '1');

    for (int i = length - 1; i >= 0; i--) {
        if (binaryString[i] == '1' && !isNegative) {
            result += pow(2, length - 1 - i);
        } else if (binaryString[i] == '0' && isNegative) {
            result -= pow(2, length - 1 - i);
        }
    }

    return result;
}

//to convert binary to appropriate registers
void data(unordered_map<string,string> &dict){
    dict["100011"] = "lw";
    dict["101011"]= "sw";
    dict["001000"] = "addi";
    dict["100010"] = "subi";
    dict["011100"] = "mul";
    dict["000000"] = "arith";
    dict["100010"] = "sub-func";
    dict["100010"] = "add-func";
    dict["01000"] = "$t0";
    dict["01001"] = "$t1";
    dict["01010"] = "$t2";
    dict["01011"] = "$t3";
    dict["01100"] = "$t4";
    dict["01101"] = "$t5";
    dict["01110"] = "$t6";
    dict["01111"] = "$t7";
    dict["11000"] = "$t8";
    dict["11001"] = "$t9";
    dict["10000"] = "$s0";
    dict["10001"] = "$s1";
    dict["10010"] = "$s2";
    dict["10011"] = "$s3";
    dict["10100"] = "$s4";
    dict["10101"] = "$s5";
    dict["10110"] = "$s6";
    dict["10111"] = "$s7";
    dict["00001"] = "$at";
    dict["00000"] = "$zero";
}
// to strip the string
string strip(const string& input) {
    size_t firstCharPos = input.find_first_not_of(" \t\r\n");
    if (firstCharPos != string::npos) {
        // Find the position of the last non-whitespace character
        size_t lastCharPos = input.find_last_not_of(" \t\r\n");
        // Extract the substring from the first non-whitespace character to the last non-whitespace character
        return input.substr(firstCharPos, lastCharPos - firstCharPos + 1);
    }
     else {
        // If the string is all whitespace, return an empty string
        return "";
    }
}
//fetching a instruction by reading from a vector
string fetch(vector<string> ans,int i){
    string s = ans[i];
    cout << "Fetch Instruction "<< i << " : " << s  << endl;
    return s;
}

//decoding an instruction 
void decode (string *s,string *rd,string *rt,string *rs ,string *op,int *imm,bool *branch,unordered_map<string,string> &dict,unordered_map<string,int> reg,int *rdv,int *rtv,int * rsv){
    
    string move_func = "100001";
    string op_load = "100011";
    string op_store = "101011";
    string op_addi = "001000";
    string op_subi = "100010";
    string op_arith = "000000";
    string add_func = "100000";
    string sub_func = "100010";
    string op_b = "000001";
    string op_beq = "000100";
    string op_bne = "000101";
    string op_mul = "011100";
    string mul_func = "000010";
    string less_func = "101010";
    //bool branch = false;
    
    //to store the respective values
    if ((*s).substr((*s).length() - move_func.length()) == move_func){
        *op = "move";
        *rs = dict[(*s).substr(11,5)];
        *rt = dict[(*s).substr(16,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
    }
    else if((*s).substr(0,6) == op_load){
        *op = "load";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
    }
    else if((*s).substr(0,6) == op_store){
        *op = "store";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
    }
    else if((*s).substr(0,6) == op_addi){
        *op = "addi";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
    }
    else if((*s).substr(0,6) == op_subi){
        *op = "subi";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
    }
    else if((*s).substr(0,6) == op_arith && (*s).substr((*s).length() - add_func.length()) == add_func){
        *op = "add";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rd = dict[(*s).substr(16,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *rdv = reg[*rd];
    }
    else if((*s).substr(0,6) == op_arith && (*s).substr((*s).length() - sub_func.length()) == sub_func){
        *op = "sub";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rd = dict[(*s).substr(16,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *rdv = reg[*rd];
    }
    else if((*s).substr(0,6) == op_bne ){
        *op = "bne";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
        *branch = true;
    }
    else if((*s).substr(0,6) == op_mul && (*s).substr((*s).length() - mul_func.length()) == mul_func){
        *op = "mul";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rd = dict[(*s).substr(16,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *rdv = reg[*rd];
    }
    else if((*s).substr(0,6) == op_beq ){
        *op = "beq";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
        *branch = true;
    }
    else if((*s).substr(0,6) == op_b ){
        *op = "b";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *imm = binaryToInt((*s).substr(16,16));
        *branch = true;
    }
    else if((*s).substr(0,6) == op_arith && (*s).substr((*s).length() - sub_func.length()) == less_func){
        *op = "less";
        *rs = dict[(*s).substr(6,5)];
        *rt = dict[(*s).substr(11,5)];
        *rd = dict[(*s).substr(16,5)];
        *rsv = reg[*rs];
        *rtv = reg[*rt];
        *rdv = reg[*rd];
    }
    else {
        *op = "";
        *rs = "";
        *rt = "";
        *imm = 0;
    }
}
//execute the instruction

//In these I have used various if else function , which acts for forwarding
void exe(int *i,string op,bool branch,unordered_map<string,int> &reg,string rs,string rt ,string rd,int imm,int *alu,int cas,int t,int *rdv,int rtv , int rsv){
cout << "op_code: " << op << endl;
    //it's for less than op code , if yes than it stores 1 in $at , else 0
    if(op == "less"){
        if(t == 1){
            cout << rsv << " 1 " << cas << endl;
            if(rsv < cas){
            *rdv = 1;
        }
        else{
            *rdv = 0;
        }
        }
        else if(t == 3){

            cout << rsv << " 3 " << cas << endl;
            if(rsv < cas){
            *rdv = 1;
        }
        else{
            *rdv = 0;
        }
        }
        else if(t == 4){

            cout << cas << " 4 " << rtv << endl;
                if(cas <rtv){
            *rdv = 1;
        }
        else{
            *rdv = 0;
        }
        }
        else{

            cout << rsv << " " << rtv << endl;
            if(rsv < rtv){
            *rdv = 1;
        }
        else{
            *rdv = 0;
        }
        }
        
    }
    //used branch control signal, 
    if(branch){
        if(op == "bne"){
            if(t == 2){
                if(cas != rtv){
                    cout << "HEllo" << endl;
                *i = 2;
                } 
            }
            else if(t == 3){
                if(rsv != cas){
                *i = 2;
            }    
            }
            else{
            if( rsv !=  rtv){
                *i = 2;
            }
            }
        }
        else if(op == "beq"){
            if(t == 1){
                cout << rs <<" " << rsv << endl;
            cout << rt <<" " <<cas << endl;
            if(cas == rsv){
                if(imm >= 0){
            *i = *i + imm;
                }
                //imm if is 2s complement
                else{
                    *i = *i + imm - 1;
                }
            }
            }
            else if (t == 3){
                cout << rs <<" " <<rsv << endl;
            cout << rt <<" " <<cas << endl;
            if(rsv == cas){
                if(imm >= 0){
            *i = *i + imm;
                }
                //imm if is 2s complement
                else{
                    *i = *i + imm - 1;
                }
            }
            }
            else{
                cout << rs <<" " <<rsv << endl;
            cout << rt <<" " <<rtv << endl;
            if(rsv == rtv){
                if(imm >= 0){
            *i = *i + imm;
                }
                //imm if is 2s complement
                else{
                    *i = *i + imm - 1;
                }
            }
            }
            
        }
        else if(op == "b"){
            if(imm < 0){
                *i = *i + imm - 1;
                //cout << "main" << endl;
            }
            else{
                *i = *i + imm;
            }
        }
    }
    //normal arithmetic function
    if(op == "add"){
        if(t == 1){
            *alu = rsv+cas;
        }
        else if(t == 3){
            *alu = rsv+cas;
        }
        else{
            *alu = rsv+rtv;
        }
        
    }
    else if(op == "sub"){
        if(t == 1){
            *alu = rsv-cas;
        }
        else if(t == 3){
            *alu = rsv-cas;
        }
        else{
            *alu = rsv-rtv;
        }
        
    }
    else if(op == "addi"){
        *alu = rsv+imm;
    }
    else if(op == "mul"){
        if(t == 1){
            *alu = cas * rsv;
        }
        else if(t == 3){
            *alu = cas * rsv;
        }
        else{
            *alu = rtv * rsv;
        }
        
    }
    else if(op == "load"){
        *alu = rsv+imm;
    }
    else if(op == "store"){
        *alu = rsv+imm;
    }
    else if(op == "move"){
        *alu = rsv+imm;
    }
    //cout << "EXE" << endl;
    cout << "ALU: " << *alu ;
    if(branch == true){
       cout  << endl << "Move to instruction i: " << *i  << endl;
    } 
    else{
        cout << endl;
    }
}
//I have assumed that all the changed value is stored in alu
//to use memory , to write or load from it
void mem(string op, vector<int> &inp, unordered_map<string, int> &reg, string rs, string rt, string rd, int imm,int *alu,int rtv) {
    
    cout << "MEM :" << endl;
    if (op == "store") {
        inp[*alu] = rtv;
        cout << "store inp[" <<reg[rs] << "+" << imm << "] : " << inp[reg[rs] + imm] << endl;
    }
    else if (op == "load") {
         *alu = inp[*alu];  // Adjusted the indexing here
        cout  << "load " <<  *alu << " to " << rt <<endl;
    }
    else{
        cout << "Nothing" << endl;
    }
}
//to write to the registers
void write(string op, vector<int> &inp, unordered_map<string, int> &reg, string rs, string rt, string rd, int imm,int alu){
    cout << "WB" << endl;
    if(op == "load"){
        reg[rt] = alu;
        cout << rt << " : " << reg[rt] << endl;
        return;
    }
    if(op == "add"){
        reg[rd] = alu  ;
        cout << rd << " : " << reg[rd] << endl;
        return;
    }
    else if(op == "sub"){
        reg[rd] = alu;
        cout << rd << " : " << reg[rd] << endl;
        return;
    }
    else if(op == "addi"){
        reg[rt] = alu;
        cout << rt << " : " << reg[rt] << endl;
        return;
    }
    else if(op == "move"){
        reg[rt] = alu;
        cout << rt << " : " << reg[rt] << endl;
        return;
    }
    else if(op == "mul"){
        reg[rd] = alu;
        cout << rd << " : " << reg[rd] << endl;
        return;
    }
    cout << "Nothing" << endl;
}
//used an instruction class to store all the values of function
class instruction {
    public:
    string s,rd,rt,rs,op;
    int imm,pc,alu,rdv,rtv,rsv;
    bool branch;
    
    instruction(string s,string rd,string rt,string rs,string op,int alu,int imm,bool branch,int pc,int rdv,int rtv,int rsv){
        this->op = op;
        this->rd = rd;
        this->rs = rs;
        this->rt = rt;
        this->s=s;
        this->imm=imm;
        this->branch = branch;
        this->alu = alu;
        this->pc = pc;
        this->rdv = rdv;
        this->rtv = rtv;
        this->rsv = rsv;

    }

};
int main() {
    //reading from template.txt
    //ifstream file("IMT2022067_binary.txt");
    ifstream file("fa.txt");
    //ifstream file("niranjan.txt");
    //dict used to store instruction, address, registers to its binary value
    unordered_map<string,string> dict ;
     data(dict);    
     //if unable to use file print an error message
    if (!file.is_open()) {
        cerr << "Unable to open the file." << endl;
        return 1;
    }

    string line;
    //ans vector is used to store the binary code required for output
    vector<string> ans;
    //while loop used to read all lines of file
    while (getline(file, line)) {
        //removing any whitespace from left and right and 
        //adding whitespace at last to read the registers properly
        line = strip(line);
        ans.push_back(line);
    }
    //closing the file
    file.close();
    
    
    vector<int> inp(50,0) ;
    inp[0]=5;
    // inp[4]=1;
    // inp[8]=-2;
    // inp[12] = 4;
    int m = 0, n = 24;
    unordered_map<string,int> reg;
    reg["$t0"] = 0;
    reg["$t1"] = 1;
    reg["$t2"] = m;
    reg["$t3"] = n;
    reg["$t4"] = 0;
    reg["$t5"] = 0;
    reg["$t6"] = 0;
    reg["$t7"] = 0;
    reg["$t8"] = 0;
    reg["$t9"] = 0;
    reg["$s0"] = 0;
    reg["$s1"] = 0;
    reg["$s2"] = 0;
    reg["$s3"] = 0;
    reg["$s4"] = 0;
    reg["$s5"] = 0;
    reg["$s6"] = 0;
    reg["$s7"] = 0;
    reg["$at"] = 0;
    reg["$zero"] = 0;
    //these two variables are used to change value of $at reg , as it's always 0
    int prev = 0;
    int prev_prev = 0;
    //used as an interface b/w different stages
    queue<pair < bool ,pair<int,instruction> > > dec;
    queue<pair < bool ,pair<int,string> > > fet;
    queue<pair < bool ,pair<int,instruction> > > exec;
    queue<pair < bool ,pair<int,instruction> > > memo;
     //stall is used to stall a stage
    int stall = 0;
    int cas = 0;
    int clock = 0;
    //fl acts as a structural hazard flag
    //and cas is used to overcome it 
    int fl = 0;
    //ju is used for control hazard 
    //such that it does not decode and fetch next instruction
    int ju = 0;
    int g = 0;
    for(int i = 0 ; i < ans.size()+ 4 ; i++){
        cout << "------------------------------------------" << endl;
        clock ++;
        cout << "clock " << clock << endl;
         if(prev_prev == 1){
            reg["$at"] = 0;
        }
        if(prev != 0){
            prev_prev = 1;
        }
        else{
            prev_prev = 0;
        }
        //if branch instruction changes the pc into another position, rather than usual flow , then flush the instructions and also complete any mem or wb left
        //this is used to flush instructions after b branch instruction
        if(g > 0){
            cout << "FLUSH" << endl <<"FLUSH" << endl;
            cout << "Is branched to some other location" << endl << endl;
            while(!dec.empty()){
                    dec.pop();
                    }
                    while(!exec.empty()){
                    exec.pop();
                    }
                    while(!fet.empty()){
                        fet.pop();
                    }
                    while(!memo.empty()){
                        pair<int,instruction>  t = memo.front().second;
                        write(t.second.op,inp,reg,t.second.rs,t.second.rt,t.second.rd,t.second.imm,t.second.alu);
                        //cout << "writtten";
                        memo.pop();
                    }
                    cout << endl;
                    reg["$at"] = 0;
                    prev_prev = 0;
                    prev=0;
                    i = g-1;
                    g = 0;
        }
        //to write back
        cout << "i " << i << endl; 
        if((i-4 >= 0  && i < ans.size()+4 ) || !memo.empty()){
            if(!memo.empty()){
                auto j = memo.front();
                memo.pop();
                cout << "INST" << j.second.first << endl;
                write(j.second.second.op,inp,reg,j.second.second.rs,j.second.second.rt,j.second.second.rd,j.second.second.imm,j.second.second.alu);
                }
            else{
                cout << "WB" << endl;
                cout << "Nothing to write back" << endl;
            }
            
        }
        //to store or load from memory
        if(i-3 >= 0 && i < ans.size()+3){
            if(!exec.empty()){
                auto j = exec.front();
                exec.pop();
                cout << "INST" << j.second.first << endl; 
                mem(j.second.second.op,inp,reg,j.second.second.rs,j.second.second.rt,j.second.second.rd,j.second.second.imm,&j.second.second.alu,j.second.second.rtv);
                memo.push(make_pair(false, make_pair(j.second.first,j.second.second)));
            }
            else{
                cout << "MEM" << endl;
                cout << "Nothing to write or load from memory" << endl;
            }
           
        }
        //its the exe stage
        if(i-2 >=0 && i < ans.size()+2){
            cout << "EXE" << endl;
            auto j = dec.front();
            cout << j.second.second.rdv << " rdv "<< j.second.second.rtv << " rtv "<< j.second.second.rsv << " rsv " << endl; 
            //if only one instruction is there to decode
            if(dec.size()-1 == 0){
                //l is used to note the current pc , if pc is changed then we can know , and change the pc
                //if not then i can be recovered from l to go with normal flow
                int l = i;
                cout << "INST" << j.second.first << " " << j.second.second.op << endl;
                //t is used to help in forwarding
                int t = 0;
                //structural hazard
                // if there's a stall , such that values of registers at execute stage is required, before they have been changed 
                //to handle all branch instruction
                //after fl flag is used , then changed it to zero for further use
                if(fl == 1){
                    
                    if(j.second.second.op != "bne"  ){
                        cout << "b instruction" << endl;
                        cout << cas  <<  " " <<j.second.second.rt << reg[j.second.second.rt]<< endl;
                        t= 1;
                    }
                    else if (j.second.second.op == "bne"){
                        cout << cas  <<  " " <<j.second.second.rs << reg[j.second.second.rs]<< endl;
                        t = 2;
                    }
                    exe(&i,j.second.second.op,j.second.second.branch,reg,j.second.second.rs,j.second.second.rt ,j.second.second.rd,j.second.second.imm, &j.second.second.alu,cas,t,&j.second.second.rdv,j.second.second.rtv,j.second.second.rsv);
                    fl = 0;
                    cout << "ALU " <<j.second.second.alu << endl;  
                }
                //to handle load forwarding from memory to execute for rt
                else if(fl == 3){
                    int cas = memo.front().second.second.alu;
                    t = 3;
                    exe(&i,j.second.second.op,j.second.second.branch,reg,j.second.second.rs,j.second.second.rt ,j.second.second.rd,j.second.second.imm, &j.second.second.alu,cas,t,&j.second.second.rdv,j.second.second.rtv,j.second.second.rsv);
                    fl = 0;
                }

                //to handle load forwarding from memory to execute for rs
                else if(fl == 4){
                    int cas = memo.front().second.second.alu;
                    t = 0;
                    exe(&i,j.second.second.op,j.second.second.branch,reg,j.second.second.rs,j.second.second.rt ,j.second.second.rd,j.second.second.imm, &j.second.second.alu,cas,t,&j.second.second.rdv,j.second.second.rtv,j.second.second.rsv);
                    fl = 0;
                }
                //if no stalls normally execute 
                else{
                    exe(&i,j.second.second.op,j.second.second.branch,reg,j.second.second.rs,j.second.second.rt ,j.second.second.rd,j.second.second.imm, &j.second.second.alu,cas,t,&j.second.second.rdv,j.second.second.rtv,j.second.second.rsv);
                }
                exec.push(make_pair(false,make_pair(j.second.first,j.second.second)));
                //if there is control hazard
                // then one needs to flush all the instruction, and fetch new instruction at next stage
                if(((j.second.second.op == "bne" &&j.second.second.alu == 0 )|| j.second.second.op == "beq" || j.second.second.op == "b" ) ){
                    if(l != i){
                        g = i;
                        i = l;
                    }
                    else{
                        ju = 0;
                    }        
                }  
            }
            //if there is nothing to decode
            else if(dec.empty()) {
                
                cout << "Nothing to execute" << endl;
            }
            // if there are multiple decodes , means it's stalls , so just pop out 
            else{
                cout << "STALL" << endl;
                dec.pop();
            }
          
        }
        
        //decode stage
        if(i-1>=0 && i < ans.size()+1){
            if(!fet.empty()){

                auto j = fet.front();
                fet.pop();
                cout << "INST" << j.second.first << endl;
                string rd="",rt="",rs = "";
                string op;
                int imm = 0,alu=0,cnt=0,rtv = 0,rdv=0,rsv=0;
                bool branch = false;
                cout << "mew " << endl;
                if(dec.size()-1 == 0){
                    // h is used to know if there is a data hazard or dependency
                    
                    auto h = dec.front();
                    dec.pop();
                    cout << "mew1 " << endl;
                    
                    decode(&j.second.second,&rd,&rt,&rs,&op,&imm,&branch,dict,reg,&rdv,&rtv,&rsv);
                    //if any hazards
                    //rt == previous rd
                    if(rt == h.second.second.rd  && rt == "$t7" && op == "sub"){
                        cnt = 0;
                        cas = exec.front().second.second.alu;
                        cout << "cas: "<<cas << endl;
                        fl = 1;
                    }
                    //if beq, fl is used to know the branch 
                    if(op == "beq"){
                        cnt = 0;
                        fl = 0;
                    }
                    //if rs == prev rd
                    if(rs == h.second.second.rd){
                        rsv = exec.front().second.second.rdv;
                        cout << "kinaaer" << endl;
                    }
                    //if rs == prev rt
                    if(rs == h.second.second.rt && rs =="$at" && op == "bne"){
                        cnt = 0;
                        cas = exec.front().second.second.alu;
                        rtv = memo.front().second.second.alu;
                        fl = 1;
                    }
                    // rt ==prev  rt
                    if(rt == h.second.second.rt && rt =="$at"){
                        cnt = 0;
                        cas = exec.front().second.second.alu;
                        cout << cas << endl;
                        fl = 1;
                    }
                    //to handle load forwarding from memory to execute for rt
                    //rt == prev rt
                    if(rt == h.second.second.rt && h.second.second.op == "load" ){
                    
                        fl = 3;
                        cnt = 1;
                        fet.push(j);
                        i--;
                        continue;
                        
                    }
                    
                    //to handle load forwarding from memory to execute for rs
                    //rs == prev rt
                    if(h.second.second.op=="load" && rs == h.second.second.rt){
                        fl = 4;
                        cnt = 1;
                        fet.push(j);
                        i--;
                        continue;
                    }
                    // this is used when there is dependency from previous to previous instruction
                    
                    if(!memo.empty()){
                        auto q = memo.front().second.second;
                        if( q.rd == rs){
                            rsv = q.alu;
                        }
                        if(q.rd == rt){
                            rtv = q.alu;
                        }
                        if(q.rt == rs && q.op != "less" && q.branch == false) {
                            cout << "FUCK" << endl;
                            cout << q.alu << endl;
                            rsv = q.alu;
                        }
                        if(q.rt == rt && q.op != "less" && q.branch == false){
                             cout << q.alu << endl;
                            rtv = q.alu;
                            cout << q.op<< "CHUTIYA" << endl;
                        }
                    }
                    instruction *inst = new instruction(j.second.second,rd,rt,rs,op,alu,imm,branch,i,rdv,rtv,rsv);
                    cout << "Decode: " << endl;
                    cout<< " " << "op: "<< inst->op << " " << "rs: " <<inst->rs << " " << "rt: " << inst->rt   << " " << "rd: "<<  inst->rd<< " "<< "imm: " << inst->imm  << " " << "branch: " << inst->branch << endl;
                    //to manage control hazard , ju is used 
                    if(op == "bne" || op == "beq" || op == "b"){
                        ju = 1;
                        dec.push(make_pair(false,make_pair(j.second.first,*inst)));
                    }
                    else{
                    //if there is structural hazard then add it more times , in order to handle structural hazard
                    for(int k = 0 ; k <= cnt ;k++){ 
                        dec.push(make_pair(false,make_pair(j.second.first,*inst)));
                    }
                    }
                }
                else{
                    decode(&j.second.second,&rd,&rt,&rs,&op,&imm,&branch,dict,reg,&rdv,&rtv,&rsv);
                    //dependency from previous to previous instruction 
                    if(op == "store" && (rt == memo.front().second.second.rt) ){
                        cout << "Inside floor 3" << endl;
                        rtv = memo.front().second.second.alu;
                    }
                    if(!memo.empty()){
                    if(rs == memo.front().second.second.rt){
                        rsv = memo.front().second.second.alu;
                    }
                    }
                    instruction *inst = new instruction(j.second.second,rd,rt,rs,op,alu,imm,branch,i,rdv,rtv,rsv);
                    cout << "DECODE" << endl;
                    cout<< " " << "op: "<< inst->op << " " << "rs: " <<inst->rs << " " << "rt: " << inst->rt   << " " << "rd: "<<  inst->rd<< " "<< "imm: " << inst->imm  << " " << "branch: " << inst->branch << endl;
                    dec.push(make_pair(false,make_pair(j.second.first,*inst)));
                    if(op == "beq"){
                        ju = 1;
                    }
                }
            stall = cnt-1;
            }
            else{
                cout << "DECODE" << endl;
                cout << "Nothing" << endl;
            }
        }
        if(stall >= 0){  
            stall--;
            i--;
            continue;
        }
        //to fetch the instruction
        if(i>=0 && i < ans.size()){
            string s = fetch(ans,i);
            fet.push(make_pair(false,make_pair(i,s)));   
        }
        //in order to break from the loop
        if(i >= ans.size()+4){
            break;
        }
        //prev and prev_prev is used so that if $at is used , then we can automatically save it to zero after it's use
        prev= reg["$at"];
        //to printing the output array
        for(int i = 0 ; i < 51;i++){
            cout << inp[i] << " ";
        }
        cout << endl;
        cout << "------------------------------------------" << endl;
       
    }
    return 0;
}
