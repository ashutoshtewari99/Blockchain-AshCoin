#include <ctime>
#include <vector>
#include "/Users/mac/stdc++.h"
#include "sha256.h"
using namespace std;

//-------------------------------------------------Transaction data
struct TransactionData
{
    double amount;
    string senderKey;
    string recieverKey;
    time_t timestamp;
};

//-------------------------------------------------Block Class
class Block
{
private:
    int index;
    string blockHash;
    string previousHash;
    string generateHash();

public:
    Block(int indx, TransactionData d, string prevHash);

    //Get Original Hash
    string getHash();

    //Get Previous Hash
    string getPreviousHash();

    //Transaction Data
    TransactionData data;

    //Validate Hash
    bool isHashValid();
};

Block::Block(int indx, TransactionData d, string prevHash)
{
    index = indx;
    data = d;
    previousHash = prevHash;
    blockHash = generateHash();
    //cout<<blockHash<<endl;
}
//Private functions
string Block::generateHash()
{
    // hash<string> hash1;
    // hash<size_t> hash2;
    // hash<size_t> finalHash;
    string toHash = to_string(data.amount) + data.recieverKey + data.senderKey + to_string(data.timestamp);
    
    // return finalHash(hash1(toHash) + hash2(previousHash));
    return sha256(toHash);
}

//Public Functions
string Block::getHash()
{
    return blockHash;
}
string Block::getPreviousHash()
{
    return previousHash;
}

bool Block::isHashValid()
{
    return generateHash() == blockHash;
}

//-------------------------------------------------Blockchain
class Blockchain
{
private:
    Block createGensisBlock();

public:
    //Public chain
    vector<Block> chain;
    Blockchain();

    //Public Functions
    void addBlock(TransactionData data);
    bool isChainValid();

    //Contrived Example for demo Only!!
    Block *getLatestBlock();
};

Blockchain::Blockchain()
{
    Block genesis = createGensisBlock();
    chain.push_back(genesis);
}

Block Blockchain::createGensisBlock()
{
    time_t current;
    TransactionData d;
    d.amount = 0;
    d.recieverKey = "None";
    d.senderKey = "None";
    d.timestamp = time(&current);

    //hash<int> hash1;
    Block genesis(0, d, "0");
    return genesis;
}

//Only for demo!!!!!!!!!!
Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

void Blockchain::addBlock(TransactionData d)
{
    int index = (int)chain.size() - 1;
    Block newBlock(index, d, getLatestBlock()->getHash());
}

bool Blockchain::isChainValid()
{
    vector<Block>::iterator it;
    int chainLen = (int)chain.size();
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHashValid())
        {
            //INVALID!!!
            return false;
        }
        if (chainLen > 1)
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                //INVALID!!!
                return false;
            }
        }
    }
    return true;
}

int main()
{
    //Start Blockchain
    Blockchain AshCoin;
    //Data for first added block
    TransactionData data1;
    time_t data1Time;
    data1.amount = 1.5;
    data1.recieverKey = "Ashutosh";
    data1.senderKey = "Mayank";
    data1.timestamp = time(&data1Time);

    AshCoin.addBlock(data1);

    cout << "Is chain valid?" << endl
         << AshCoin.isChainValid() << endl;

    TransactionData data2;
    time_t data2Time;
    data2.amount = 4;
    data2.recieverKey = "Ashutosh";
    data2.senderKey = "Amandeep";
    data2.timestamp = time(&data2Time);

    AshCoin.addBlock(data2);

    cout << "Now is chain valid?" << endl
         << AshCoin.isChainValid() << endl;

    //Hacking a Block
    Block *hackBlock = AshCoin.getLatestBlock();
    hackBlock->data.amount = 100000;
    hackBlock->data.recieverKey = "Hacker";
    cout << "Now is chain valid?" << endl
         << AshCoin.isChainValid() << endl;
}
