#include "SFE_CC3000.h"
#include "SFE_CC3000_Client.h"

class TestThing {
public:
    TestThing(SFE_CC3000 &wifi);
    void connectAll(int pointless);
    
private:
    SFE_CC3000 *_wifi;
    SFE_CC3000 _otherW;
    SFE_CC3000_Client _client;
};

