#include "TestThing.h"

TestThing::TestThing(SFE_CC3000 &wifi) : _wifi(&wifi), _otherW(2, 7, 10), _client(_otherW) {
    _wifi->connect("asdf", WLAN_SEC_WPA2, "asdf");
    _otherW.connect("asdf", WLAN_SEC_WPA2, "asdf");
    _client.connect("google.com");
}

void TestThing::connectAll(int pointless) {
        _wifi->connect("", 3, "");
        _otherW.connect("", 3, "");
        _client.connect("");
    }
