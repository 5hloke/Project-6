// detect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include "treap_bst.hpp"
#include <fstream>
#include <string>
#include <vector>

// the function to  convert the character symbol into a string return the binary string 
std::string strToBinary(char symbol)
{
    // the empty binary string 
    std::string binStr = "";
    uint8_t val = uint8_t(symbol);
    std::string temp = ""; // temporary string
    while (val > 0) // if val is greater than 0
    {
        (val % 2) ? temp.push_back('1') : // check if the modulus of two is zero or 1 
            temp.push_back('0'); // and pushback to temp accordingly 
        val /= 2; // divide the val by 2
    }
    //reverse bin order
    reverse(temp.begin(), temp.end()); // reverse the temp string 

    while (temp.size() < 8) // if temp size is less than 8
    {
        temp = '0' + temp; // add 0 at the end of the string to make a byte
    }

    int length = binStr.length();

    binStr.insert(length, temp);
    //std::cout << "binary String returned: " << binStr << std::endl;
    return binStr;
}

// function to sort the virus vector according to the size of the vector stored in it 
std::vector<std::vector<std::string>> sort(std::vector<std::vector<std::string>> v)
{
    std::vector<std::vector<std::string>> st(v.size()); // create a vector of size of the origina; vector

    //setting the indexes which have not been visited to false
    std::vector<bool> isUsed(v.size(), false);

 
    for (int i = 0; i < v.size(); i++)
    {
        
        int min = v[i].size(); // minimum size of the vector 
        
        int temp = v[i].size() - 1;

         
        for (int k = 0; k < isUsed.size(); k++)
        {
            if (isUsed[k] == false)
            {
                min = v[k].size();
                temp = k;
                break;
            }
        }

        //loop to find the minimum size 
        for (int j = 0; j < v.size(); j++)
        {
            if (v[j].size() < min && isUsed[j] == false)
            {
                min = v[j].size();
                temp = j;
            }

        }

        isUsed[temp] = true;
        //set sorted to lowest value found
        st[i] = v[temp];

    }



    return st;
}
int main(int argc, char *argv[])
{
    if ((argc != 3)) { // if the number of arguments is not less than 3 then throw an error 
        throw std::logic_error("invalid input arguments");
    }
    std::string binfile = argv[2]; //  argv[2];
    std::string list = argv[1]; // argv[1]
    std::ifstream datFile(binfile, std::ios::binary | std::ios::in); // Make ifstream object and read the binary file
    std::ifstream listfile(list); // read the database for the viruses
    std::string line; // a string line to pass through every line of the file
    std::vector<std::vector<std::string>> virus; // a vetor virus to store all the virusses 
    if (!datFile.is_open()) { // if the file  does not open then throw an error
        throw std::logic_error("invalid input arguments");
    }
    
    if (listfile.is_open()) { // if file opens 

        while (std::getline(listfile, line))
        {
            int pos = 0; //begining bit of the virus

            std::vector<std::string> v; // vector to store a single virus string
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] == ' ' || i == line.size() - 1) {

                    std::string byte = line.substr(pos, 8); // get the substring into tbyte
                    v.push_back(byte); // pushback the byte just read fro mthe file
                    pos = i + 1;
                }
                
            }
            virus.push_back(v); // pushback the entire virus to the virus vector 
        }
    }
    else
    {
        throw std::logic_error("invalid file");
    }

    datFile.seekg(0, std::ios::end); // Move indexer to the end
    const int max_ind = datFile.tellg(); // store the last index
    datFile.seekg(0); // move indexer to the beginning
    char character[1]; // a char variable to read every character in the binary file
    std::vector<char> data_c;
    std::vector<std::string> data_s;
    TreapBST<int, std::string> datatree;
    bool flag = false;
    for (int i = 0; i <= max_ind; i++)
    {
        datFile.read(character, 1); // read the byte from the file 
        data_c.push_back(character[0]); // push_back the read character to the character vector  
    }
    for (int i = 0; i <= max_ind; i++)
    {
        data_s.push_back(strToBinary(data_c[i])); // convert the character to  a string and push it into the string vector 

    }
    for (int i = 0; i <= max_ind; i++) { 

        datatree.insert(i, data_s[i]); // insert the individual string into a datatree with consecutive keys
    }
   
    std::vector<std::vector<std::string>> virus_sorted = sort(virus); // sort the virus vector according to its size

    std::vector<std::vector<std::string>> virusFound; // vector to store all the virusses that were found in the binary file

    for (int i = 0; i < virus_sorted.size(); i++) { // for every virus in the virus vector 

       // int v_size = virus_sorted[i].size(); // size of the current virus we are searching for in the data set

        int count = 0; // counter variable 
        bool found = false;
        for (int j = 0; j <= max_ind; j++) { // for all the bytes in the binary file 
            if (virus_sorted[i].size() != 0) {
                if (virus_sorted[i][0] == datatree.search(j, flag)) { // check if the first byte of the virus matches any data value

                    found = true;
                    count = j; // set the counter value
                    for (int k = 1; k < virus_sorted[i].size(); k++) { // for the rest of the bytes in the virus 
                        count = count + 1;
                        if (virus_sorted[i][k] == datatree.search(count, flag)) { // check if the consecutive data values match
                            found = true; // if the values match set found to true 
                        }
                        else {
                            found = false; // if any of the consecutive values do not math set found equal to false
                            break; // break out of the loop
                        }
                    }

                    if (found) { // if found id trus push the virus to the virus found vector and break out of the loop
                        virusFound.push_back(virus_sorted[i]);
                        //std::cout << "pushed" << std::endl;
                        break;
                    }
                }
            }
            
        }
    }

    //print the viruses that were found (if anywere found)
    if (virusFound.size() == 0)
    {
        std::cout << "No viruses/malware found!" << std::endl;
    }
    else
    {
        std::cout << "Viruses/malware found:" << std::endl;
        for (int i = 0; i < virusFound.size(); i++) {
            for (int j = 0; j < virusFound[i].size(); j++) {
                std::cout << virusFound[i][j];
                if (j == virusFound[i].size() - 1) {
                    std::cout << std::endl;
                }
                else 
                {
                    std::cout << " ";
                    
                }
            }
        }
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
