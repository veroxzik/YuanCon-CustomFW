#include <HID.h>

typedef struct HIDCallback_ {
    bool (*callback)(uint16_t length);
    uint8_t report_id;
    struct HIDCallback_* next;
} HIDCallback;

class CustomHID_ : public PluggableUSBModule {
   public:
    CustomHID_(void);
    int begin(void);
    int SendReport(uint8_t id, const void* data, int len);
    void AppendDescriptor(HIDSubDescriptor* node);
    void AppendCallback(HIDCallback* callback);
    uint8_t getShortName(char* name);

   protected:
    int getInterface(uint8_t* interfaceCount);
    int getDescriptor(USBSetup& setup);
    bool setup(USBSetup& setup);

   private:
    unsigned int epType[1];

    HIDCallback_* rootCallback;
    HIDSubDescriptor* rootNode;
    uint16_t descriptorSize;

    uint8_t protocol;
    uint8_t idle;
};
CustomHID_& CustomHID();
