#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<bitset>
#include<vector>
using namespace std;


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
    dict["4"] = "000100";
    dict["1"] = "000001";
    dict["0"] = "000000";

}
string strip(const string& input) {
    // Find the position of the first non-whitespace character
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
string fetch(vector<string> ans,int i){
    
    string s = ans[i];
    //cout << "Fetch Cycle: " << s  << endl;
    return s;
}

void decode (string *s,string *rd,string *rt,string *rs ,string *op,int *imm,bool *branch,unordered_map<string,string> &dict,unordered_map<string,int> reg,int *rdv,int *rtv , int *rsv){
    
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
    //move 
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
    cout<< " " << "op: "<< *op << " " << "rs: " <<*rs << " " << "rt: " << *rt   << " " << "rd: "<<  *rd<< " "<< "imm: " << *imm  << " " << "branch: " << *branch << endl;

}

void exe(int *i,string op,bool branch,unordered_map<string,int> &reg,string rs,string rt ,string rd,int imm,int *alu,int *rdv,int rtv,int rsv){
    cout << *alu << endl;
    if(op == "less"){
        if(rsv < rtv){
            *alu = 1;
        }
        else{
            *alu = 0;
        }
    }
    if(branch){
        if(op == "bne"){
            if(rsv != rtv){
                *i = 0;
                *alu = 1;
            }
        }
        else if(op == "beq"){
            if(rsv == rtv){
                if(imm >= 0){
                    *i = *i + imm;
                }
                else{
                    *i = *i + imm-1;
                }
                *alu = 1;
            }
        }
        else if(op == "b"){
            *i = *i + imm - 1;
            *alu =1;
        }
    }
    if(op == "add"){
        *alu = rsv+rtv;
    }
    else if(op == "sub"){
        *alu = rsv-rtv;
    }
    else if(op == "addi"){
        *alu = rsv+imm;
    }
    else if(op == "mul"){
        *alu = rtv * rsv;
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
    cout << "ALU: " << *alu << endl;
    if(branch == true){
       cout  << endl << "Move to instruction i: " << *i  << endl;
    } 
    else{
        cout << endl;
    }
}

void mem(string op, vector<int> &inp, unordered_map<string, int> &reg, string rs, string rt, string rd, int imm,int *alu,int rtv) {
    int c=0;
    if (op == "store") {
        inp[*alu] = rtv;
        c=1;
    }
    else if (op == "load") {
        c=2;
        *alu = inp[*alu];  // Adjusted the indexing here
    }
    // cout << "MEM :" << endl;
    if(c == 1){
        cout <<"At Index " << reg[rs] << "+" << imm << " : " << inp[reg[rs] + imm] << endl;
    }
    else if(c == 2){
        cout << "Reading from memeory" << ": " << alu << endl;
    }
    else{
        cout << "Nothing to store or load from memory" << endl;
    }
}

void write(string op, vector<int> &inp, unordered_map<string, int> &reg, string rs, string rt, string rd, int imm,int alu){
    //cout << "WB" << endl;
    if(op == "load"){
        reg[rt] = alu;
        cout << rt << " : " << reg[rt] << endl;
        return;
    }
    if(op == "add"){
        reg[rd] = alu  ;
        cout <<  rd << " : " << reg[rd] << endl;
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
    else if(op == "less"){
        reg[rd] = alu;
    }
    cout << "Nothing to wb" << endl;

}
int main() {
    //reading from template.txt
    ifstream file("IMT2022067_binary.txt");
    //ifstream file("fa.txt");
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
    bool branch = false;
    //move 
    vector<int> inp(50,0) ;
    inp[0]=5;
     inp[4]=1;
     inp[8]=-2;
      inp[12] = 4;
    int m = 0, n = 24;
    unordered_map<string,int> reg;
    reg["$t0"] = 0;
    reg["$t1"] = 4;
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
    int prev = 0;
    int prev_prev = 0;
    int clk = 0;
    for(int i = 0 ; i < ans.size() ; i++){
        cout << clk << endl;
        cout << "PC : "  << i  << endl;
        string s = fetch(ans,i);
        cout << "FETCH " << s << endl;
        clk++;
        
    string rd="",rt="",rs = "";
    string op;
    int imm = 0,rdv=0,rtv=0,rsv=0;
    bool branch = false;
    cout << "DECODE" << endl;
    decode(&s,&rd,&rt,&rs,&op,&imm,&branch,dict,reg,&rdv,&rtv,&rsv);
    clk++;
    

    int alu=0;
    cout << "EXEC" << endl;
    exe(&i,op,branch,reg,rs,rt ,rd,imm, &alu,&rdv,rtv,rsv);
    clk++;
    
    //cout << "alu : "<<alu << endl;
    
    cout << "MEMORY" << endl;
    mem(op,inp,reg,rs,rt,rd,imm,&alu,rtv);
    clk++;
    
    cout << "WRITEBACK" << endl;
    write(op,inp,reg,rs,rt,rd,imm,alu);
    clk++;
   
   
    //cout << rs << " " << reg[rs] << " " <<rt << " " << reg[rt] << " " <<rd << " " << reg[rd] << endl;

    prev= reg["$at"];
    //cout << "rs: " <<rs << " " << "rt: " << rt   << " " << "rd: "<<  rd<< " "<< "imm: " << imm << " " << "op: "<< op  << endl;

    for(int i = 0 ; i < 51;i++){
        cout << inp[i] << " ";
    }
    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    if(prev_prev == 1){
        reg["$at"] = 0;
    }
    if(prev != 0){
        prev_prev = 1;
    }
    else{
        prev_prev = 0;
    }
    }
    cout << "Total clock cycle : " << clk << endl;
    return 0;
}
