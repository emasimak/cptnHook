// cptnHook.cpp
// Use of: PIN, ROOT

#include "cptnHook.h"
#include "interceptorGen.h"
//#include "cctlibFunctions.h"

/* ========================================================================= */
/* File and Trees (Initialize and Fill)                                      */
/* ========================================================================= */
static void initializeTree (void)
{
        cout << "Initialising globals" << endl;

	// Make branches of TTrees: 'values' and 'hash'
	// exp
	treeExpPntr->Branch("valExp", &valExp, "valExp/F");
	treeExpPntr->Branch("hashExp", &hashExp, "hashExp/l");
	// sqrt
	treeSqrtPntr->Branch("valSqrt", &valSqrt, "valSqrt/F");
	treeSqrtPntr->Branch("hashSqrt", &hashSqrt, "hashSqrt/l");
	// sin
	treeSinPntr->Branch("valSin", &valSin, "valSin/F");
	treeSinPntr->Branch("hashSin", &hashSin, "hashSin/l");
	// cos
	treeCosPntr->Branch("valCos", &valCos, "valCos/F");
	treeCosPntr->Branch("hashCos", &hashCos, "hashCos/l");
	// tan
	treeTanPntr->Branch("valTan", &valTan, "valTan/F");
	treeTanPntr->Branch("hashTan", &hashTan, "hashTan/l");
	// asin
	treeAsinPntr->Branch("valAsin", &valAsin, "valAsin/F");
	treeAsinPntr->Branch("hashAsin", &hashAsin, "hashAsin/l");
	// acos
	treeAcosPntr->Branch("valAcos", &valAcos, "valAcos/F");
	treeAcosPntr->Branch("hashAcos", &hashAcos, "hashAcos/l");
	// atan
	treeAtanPntr->Branch("valAtan", &valAtan, "valAtan/F");
	treeAtanPntr->Branch("hashAtan", &hashAtan, "hashAtan/l");

	myExpMap = {{"begin", -15}};
	mySqrtMap = {{"begin", -15}};
	mySinMap = {{"begin", -15}};
	myCosMap = {{"begin", -15}};
	myTanMap = {{"begin", -15}};
	myAsinMap = {{"begin", -15}};
	myAcosMap = {{"begin", -15}};
	myAtanMap = {{"begin", -15}};
}

//Tree
void treeFill(double x, int rtnID, int rtnEnum)//, ADDRINT addr, std::vector<Float_t> *IntercExpVal)
{
	//TFile *fPntr = new TFile("dataTree.root");
   	//TTree *treeExpPntr = (TTree*)fPntr->Get("treeExp");
	
	std::string rtnStack = rtnStackVector[rtnID][rtnEnum];
	//cout << "Routine ID: " << rtnID << " #: " << rtnEnum << endl;
	switch (rtnID)
	{
		case 0:  //exp
			valExp = x;
			hashExp = myHash(rtnStack, myExpMap, ihExp);
			treeExpPntr->Fill();
			cout << "loading... exp TTree" << "\t val: " << valExp << "\t hash: " << 			hashExp << endl;
			break;
		case 1:  //sqrt
			valSqrt = x;
			//dummyStr = std::to_string(stackRtn);
			hashSqrt = myHash(rtnStack, mySqrtMap, ihSqrt);
			treeSqrtPntr->Fill();
			cout << "loading... sqrt TTree" << "\t val: " << valSqrt << "\t hash: " << 			hashSqrt << endl;
			break;
		case 2:  //sin
			valSin = x;
			hashSin = myHash(rtnStack, mySinMap, ihSin);
			treeSinPntr->Fill();
			cout << "loading... sin TTree" << "\t val: " << valSin << "\t hash: " << 			hashSin << endl;
			break;
		case 3:  //cos
			valCos = x;
			hashCos = myHash(rtnStack, myCosMap, ihCos);
			treeCosPntr->Fill();
			cout << "loading... cos TTree" << "\t val: " << valCos << "\t hash: " << 			hashCos << endl;			break;
		case 4:  //tan
			valTan = x;
			hashTan = myHash(rtnStack, myTanMap, ihTan);
			treeTanPntr->Fill();
			cout << "loading... tan TTree" << "\t val: " << valTan << "\t hash: " << 			hashTan << endl;
			break;
		case 5:  //asin
			valAsin = x;
			hashAsin = myHash(rtnStack, myAsinMap, ihAsin);
			treeAsinPntr->Fill();
			cout << "loading... asin TTree" << "\t val: " << valAsin << "\t hash: " << 			hashAsin << endl;
			break;
		case 6:  //acos
			valAcos = x;
			hashAcos = myHash(rtnStack, myAcosMap, ihAcos);
			treeAcosPntr->Fill();
			cout << "loading... acos TTree" << "\t val: " << valAcos << "\t hash: " << 			hashAcos << endl;
			break;
		case 7:  //atan
			valAtan = x;
			hashAtan = myHash(rtnStack, myAtanMap, ihAtan);
			treeAtanPntr->Fill();
			cout << "loading... atan TTree" << "\t val: " << valAtan << "\t hash: " << 			hashAtan << endl;
			break;
	}
}

/* ========================================================================= */
/* Hashing Function			                                     */
/* ========================================================================= */
ULong64_t myHash(const std::string& s, std::map <string, ULong64_t>& myMap, ULong64_t& ih)
{
	//auto hashPosition = myMap.find(s);
	std::map<string, ULong64_t>::iterator iter = myMap.find(s);
        cout << s <<endl;
        if (iter != myMap.end()){ 
                cout << "existing string: " << s << " " << iter->second << endl;
        }
	if(iter == myMap.end())	
	{
		ih++;
   		//Element NOT found in map
		myMap[s] = ih;	
		stackVector.emplace_back(s);
		return ih;
	}
	cout << "string: " << s << " hash: " << myMap[s] << endl;
        return iter->second; //Element already exists. Return value.
}

/* ========================================================================= */
/* Main                                                                      */
/* ========================================================================= */
int main(int argc, char *argv[])
{
	//signal(SIGSEGV, handler);   // Install handler
	// Initialize Root Tree Branches.
	initializeTree();
	// Initialize pin & symbol manager
    	PIN_InitSymbols();

    	if( PIN_Init(argc,argv) )
    	{
    	    return Usage();
    	}

    	// Write to a file since cout and cerr maybe closed by the application
    	TraceFile.open(KnobOutputFile.Value().c_str());
    	TraceFile << hex;
    	TraceFile.setf(ios::showbase);

   	// Register Image to be called to instrument functions.
    	IMG_AddInstrumentFunction(Image, 0);
    	PIN_AddFiniFunction(Fini, 0);
	
	// For future additions.
	// Init Client
    	//ClientInit(argc, argv);
    	// Intialize CCTLib
    	//PinCCTLib::PinCCTLibInit(INTERESTING_INS_ALL, cctlibOutputFile, InstrumentInsCallback, 0);

    	// Never returns
    	PIN_StartProgram();

	return 0;
}

/* ========================================================================= */
/* eof                                                                       */
/* ========================================================================= */
