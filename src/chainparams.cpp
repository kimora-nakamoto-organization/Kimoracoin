// Copyright (c) 2013-2019 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Kimora Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"
#include "arith_uint256.h"

#include <assert.h>

#include "chainparamsseeds.h"

//TODO: Take these out
extern double algoHashTotal[16];
extern int algoHashHits[16];


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << CScriptNum(0) << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Kimora the official cryptocurrency of Kimora Exchange, July 2019";
    const CScript genesisOutputScript = CScript() << ParseHex("04d82a188a0b2bb60f1dce2f73d8953f3a88fb017f45339b2e49e50d37920de78be5af4f09903a65131facfeacdc00fe5f4104e4a000fb4ca4ccee6fd3befb8e4c") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

void CChainParams::TurnOffSegwit() {
    consensus.nSegwitEnabled = false;
}

void CChainParams::TurnOffCSV() {
    consensus.nCSVEnabled = false;
}

void CChainParams::TurnOffBIP34() {
    consensus.nBIP34Enabled = false;
}

void CChainParams::TurnOffBIP65() {
    consensus.nBIP65Enabled = false;
}

void CChainParams::TurnOffBIP66() {
    consensus.nBIP66Enabled = false;
}

bool CChainParams::BIP34() {
    return consensus.nBIP34Enabled;
}

bool CChainParams::BIP65() {
    return consensus.nBIP34Enabled;
}

bool CChainParams::BIP66() {
    return consensus.nBIP34Enabled;
}

bool CChainParams::CSVEnabled() const{
    return consensus.nCSVEnabled;
}


/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = false; // Enable later.
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1814; // Approx 90% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;  //Assets (RIP2)
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1564055209; // GMT: Thursday, July 25, 2019 11:46:49 AM
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1595677609; // GMT: Saturday, July 25, 2020 11:46:49 AM

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x4d; // M
        pchMessageStart[1] = 0x4b; // K
        pchMessageStart[2] = 0x4d; // M
        pchMessageStart[3] = 0x52; // R
        nDefaultPort = 20197;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1564055209, 5122506, 0x1e00ffff, 2, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0000000cce50bc506ec664e5e2d3200314c1a8160f8bc67fdaf77ca9d59cbf29"));
        assert(genesis.hashMerkleRoot == uint256S("1fe77455dbf46267957e3b1b81f794a16e2d8fad7e77cd2db647b530a7369e82"));

        vSeeds.push_back(CDNSSeedData("74.208.135.213", "74.208.135.213"));
        vSeeds.push_back(CDNSSeedData("108.175.14.64", "108.175.14.64"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,45); // Address Starts with K
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,145);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x08, 0x39, 0xE9, 0xDA};
        base58Prefixes[EXT_SECRET_KEY] = {0x08, 0x39, 0x9E, 0xAD};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {

            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Rito chain
            1564055209, // * UNIX timestamp of last known number of transactions
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

        /** KMR Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "KMRissueAssetBurnAddressxxxXWqdK6t";
        strReissueAssetBurnAddress = "KMRreissueAssetBurnAddressxxWpH1fK";
        strIssueSubAssetBurnAddress = "KMRissueSubAssetBurnAddressxYKwdTc";
        strIssueUniqueAssetBurnAddress = "KMRissueUniqAssetBurnAddressTSJg1Q";

        //Global Burn Address
        strGlobalBurnAddress = "KMRBurnAddressGLBLxxxxxxxxxxX64Fe9";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours
        /** KMR End **/
        // Build Genesis Block:
    }
};

/**
 * Testnet (v6)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 2100000;  //~ 4 yrs at 1 min block time
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;

        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1310; // Approx 65% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 5;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 1564057667; //GMT: Thursday, 25 July 2019, 12:27:47
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 1595680067; // GMT: Saturday, 25 July 2020, 12:27:47

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");


        pchMessageStart[0] = 0x54;  // T
        pchMessageStart[1] = 0x6b;  // k
        pchMessageStart[2] = 0x6d;  // m
        pchMessageStart[3] = 0x72;  // r
        nDefaultPort = 30197;
        nPruneAfterHeight = 1000;

        uint32_t nGenesisTime = 1564057667;
        genesis = CreateGenesisBlock(nGenesisTime, 5633186, 0x1e00ffff, 2, 50 * COIN);   
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000000abc643eef88120887d8e1a3d2c78f9b90dc39dd96d19cbe1e1897e0280"));
        assert(genesis.hashMerkleRoot == uint256S("1fe77455dbf46267957e3b1b81f794a16e2d8fad7e77cd2db647b530a7369e82"));

        vFixedSeeds.clear();
        vSeeds.clear();

        vSeeds.emplace_back("tn.s1.kimora.org", false);
        vSeeds.emplace_back("tn.s2.kimora.org", false);
        vSeeds.emplace_back("tn.s3.kimora.org", false);

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65); // Address Starts with T
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,194);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,237);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x07, 0x33, 0x77, 0xBF};
        base58Prefixes[EXT_SECRET_KEY] = {0x07, 0x33, 0x73, 0x96};

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fMiningRequiresPeers = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            // Update as we know more about the contents of the Rito chain
            1564057667, // * UNIX timestamp of last known number of transactions
            1,          // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            3.1         // * estimated number of transactions per second after that timestamp
        };

        /** KMR Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "TKMRissueAssetBurnAddressxxxTpYGDr";
        strReissueAssetBurnAddress = "TKMRreissueAssetBurnAddressxZHBWwt";
        strIssueSubAssetBurnAddress = "TKMRissueSubAssetBurnAddressTMoSby";
        strIssueUniqueAssetBurnAddress = "TKMRissueUnqAssetBurnAddressXfkcKh";

        // Global Burn Address
        strGlobalBurnAddress = "TKMRBurnAddressGLBLxxxxxxxxxUxMSz1";

        // DGW Activation
        nDGWActivationBlock = 1;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours
        /** KMR End **/


    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nBIP34Enabled = true;
        consensus.nBIP65Enabled = true; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.nBIP66Enabled = true;
        consensus.nSegwitEnabled = true;
        consensus.nCSVEnabled = true;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 2016 * 60; // 1.4 days
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].bit = 6;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_ASSETS].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0x52;  // R
        pchMessageStart[1] = 0x6b;  // k
        pchMessageStart[2] = 0x6d;  // m
        pchMessageStart[3] = 0x72;  // r
        nDefaultPort = 40197;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1564119053, 1, 0x207fffff, 4, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();

        assert(consensus.hashGenesisBlock == uint256S("0x7c4d2d77119e1a5c189efaffe2816bd814f1f79c5e78320216d79baae7754b5f "));
        assert(genesis.hashMerkleRoot == uint256S("0x1fe77455dbf46267957e3b1b81f794a16e2d8fad7e77cd2db647b530a7369e82"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData) {
            {
            }
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60); // Address Starts with R
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,195);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,245);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x06, 0x39, 0x93, 0xCA};
        base58Prefixes[EXT_SECRET_KEY] = {0x06, 0x39, 0x41, 0x89};


        /** KMR Start **/
        // Burn Amounts
        nIssueAssetBurnAmount = 500 * COIN;
        nReissueAssetBurnAmount = 100 * COIN;
        nIssueSubAssetBurnAmount = 100 * COIN;
        nIssueUniqueAssetBurnAmount = 5 * COIN;

        // Burn Addresses
        strIssueAssetBurnAddress = "RKMRissueAssetBurnAddressxxxXHiEtP";
        strReissueAssetBurnAddress = "RKMRreissueAssetBurnAddressxTbHxF2";
        strIssueSubAssetBurnAddress = "RKMRissueSubAssetBurnAddressW8Upkn";
        strIssueUniqueAssetBurnAddress = "RKMRissueUnqAssetBurnAddressZjyeZB";

        // Global Burn Address
        strGlobalBurnAddress = "RKMRBurnAddressGLBLxxxxxxxxxXB7qwq";

        // DGW Activation
        nDGWActivationBlock = 200;

        nMaxReorganizationDepth = 60; // 60 at 1 minute block timespan is +/- 60 minutes.
        nMinReorganizationPeers = 4;
        nMinReorganizationAge = 60 * 60 * 12; // 12 hours
        /** KMR End **/
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}

void TurnOffSegwit(){
    globalChainParams->TurnOffSegwit();
}

void TurnOffCSV() {
    globalChainParams->TurnOffCSV();
}

void TurnOffBIP34() {
    globalChainParams->TurnOffBIP34();
}

void TurnOffBIP65() {
    globalChainParams->TurnOffBIP65();
}

void TurnOffBIP66() {
    globalChainParams->TurnOffBIP66();
}