// This file was derived from the Lightweight USB device Stack for STM32
// microcontrollers, see https://github.com/dmitrystu/libusb_stm32
//
// Copyright ©2016 Dmitry Filimonchuk <dmitrystu[at]gmail[dot]com>
// Reduced and adapted for JeeH and C++11 by Jean-Claude Wippler, April 2018.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License.  You may obtain a copy
// of the License at http://www.apache.org/licenses/LICENSE-2.0 Unless required
// by applicable law or agreed to in writing, software distributed under the
// License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, either express or implied.  See the License for the specific
// language governing permissions and limitations under the License.

constexpr uint8_t CDC_EP0_SIZE = 0x08;
constexpr uint8_t CDC_RXD_EP   = 0x01;
constexpr uint8_t CDC_TXD_EP   = 0x82;
constexpr uint8_t CDC_DATA_SZ  = 0x40;
constexpr uint8_t CDC_NTF_EP   = 0x83;
constexpr uint8_t CDC_NTF_SZ   = 0x08;

constexpr uint32_t PERIPH_BASE        = 0x40000000U;
constexpr uint32_t UID_BASE           = 0x1FFFF7E8U;

constexpr uint32_t APB1PERIPH_BASE    = PERIPH_BASE;
constexpr uint32_t USB_BASE           = (APB1PERIPH_BASE + 0x00005C00U);
constexpr uint32_t USB_PMAADDR        = (APB1PERIPH_BASE + 0x00006000U);

constexpr uint32_t AHBPERIPH_BASE     = (PERIPH_BASE + 0x00020000U);
constexpr uint32_t RCCBASE            = (AHBPERIPH_BASE + 0x00001000U);
constexpr uint32_t FLASH_R_BASE       = (AHBPERIPH_BASE + 0x00002000U);

constexpr uint32_t USB_EP_ISOCHRONOUS = 0x00000400U;
constexpr uint32_t USB_EP_TX_DIS      = 0x00000000U;
constexpr uint32_t USB_EP_TX_STALL    = 0x00000010U;
constexpr uint32_t USB_EP_BULK        = 0x00000000U;
constexpr uint32_t USB_EP_TX_VALID    = 0x00000030U;
constexpr uint32_t USB_EP_TX_NAK      = 0x00000020U;
constexpr uint32_t USB_EP_RX_DIS      = 0x00000000U;
constexpr uint32_t USB_EP_RX_STALL    = 0x00001000U;
constexpr uint32_t USB_EP_RX_VALID    = 0x00003000U;
constexpr uint32_t USB_EP_CONTROL     = 0x00000200U;
constexpr uint32_t USB_EP_INTERRUPT   = 0x00000600U;
constexpr uint32_t USB_EP_RX_NAK      = 0x00002000U;

#define USBDEV                ((USB_TypeDef *)USB_BASE)
#define RCC                   ((RCC_TypeDef *)RCCBASE)
#define FLASH                 ((FLASH_TypeDef *)FLASH_R_BASE)

constexpr uint32_t USB_EP_T_FIELD      = (3<<9);
constexpr uint32_t USB_EPTX_STAT       = (3<<4);
constexpr uint32_t USB_EP_KIND         = (1<<8);
constexpr uint32_t USB_CNTR_CTRM       = (1<<15);
constexpr uint32_t USB_CNTR_RESETM     = (1<<10);
constexpr uint32_t USB_CNTR_ERRM       = (1<<13);
constexpr uint32_t USB_CNTR_SOFM       = (1<<9);
constexpr uint32_t USB_CNTR_SUSPM      = (1<<11);
constexpr uint32_t USB_CNTR_WKUPM      = (1<<12);
constexpr uint32_t USB_DADDR_EF        = (1<<7);
constexpr uint32_t USB_FNR_FN          = (0x7FF<<0);
constexpr uint32_t USB_ISTR_EP_ID      = (0xF<<0);
constexpr uint32_t USB_ISTR_CTR        = (1<<15);
constexpr uint32_t USB_ISTR_RESET      = (1<<10);
constexpr uint32_t USB_ISTR_SOF        = (1<<9);
constexpr uint32_t USB_ISTR_WKUP       = (1<<12);
constexpr uint32_t USB_CNTR_FSUSP      = (1<<3);
constexpr uint32_t USB_ISTR_SUSP       = (1<<1);
constexpr uint32_t USB_ISTR_ERR        = (1<<13);
constexpr uint32_t USB_EP_CTR_RX       = (1<<15);
constexpr uint32_t USB_EP_DTOG_RX      = (1<<14);
constexpr uint32_t USB_EPRX_STAT       = (3<<12);
constexpr uint32_t USB_EP_SETUP        = (1<<11);
constexpr uint32_t USB_EP_CTR_TX       = (1<<7);
constexpr uint32_t USB_EP_DTOG_TX      = (1<<6);
constexpr uint32_t USB_EPADDR_FIELD    = (0xF<<0);

#define  USB_EPREG_MASK       (USB_EP_CTR_RX|USB_EP_SETUP|USB_EP_T_FIELD|USB_EP_KIND|USB_EP_CTR_TX|USB_EPADDR_FIELD)

struct RCC_TypeDef {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;

};

struct USB_TypeDef {
  volatile uint16_t EP0R;
  volatile uint16_t :16;
  volatile uint16_t EP1R;
  volatile uint16_t :16;
  volatile uint16_t EP2R;
  volatile uint16_t :16;
  volatile uint16_t EP3R;
  volatile uint16_t :16;
  volatile uint16_t EP4R;
  volatile uint16_t :16;
  volatile uint16_t EP5R;
  volatile uint16_t :16;
  volatile uint16_t EP6R;
  volatile uint16_t :16;
  volatile uint16_t EP7R;
  volatile uint16_t :16;
  volatile uint16_t RESERVED[16];
  volatile uint16_t CNTR;
  volatile uint16_t :16;
  volatile uint16_t ISTR;
  volatile uint16_t :16;
  volatile uint16_t FNR;
  volatile uint16_t :16;
  volatile uint16_t DADDR;
  volatile uint16_t :16;
  volatile uint16_t BTABLE;
  volatile uint16_t :16;
};

struct FLASH_TypeDef {
  volatile uint32_t ACR;
  volatile uint32_t KEYR;
  volatile uint32_t OPTKEYR;
  volatile uint32_t SR;
  volatile uint32_t CR;
  volatile uint32_t AR;
  volatile uint32_t :16;
  volatile uint32_t OBR;
  volatile uint32_t WRPR;
};

constexpr int usbd_evt_reset    = 0;
constexpr int usbd_evt_sof      = 1;
constexpr int usbd_evt_susp     = 2;
constexpr int usbd_evt_wkup     = 3;
constexpr int usbd_evt_eptx     = 4;
constexpr int usbd_evt_eprx     = 5;
constexpr int usbd_evt_epsetup  = 6;
constexpr int usbd_evt_error    = 7;
constexpr int usbd_evt_count    = 8;

constexpr int USBD_HW_ADDRFST   = (1 << 0);
constexpr int USBD_HW_BC        = (1 << 1);
constexpr int USND_HW_HS        = (1 << 2);
constexpr int USBD_HW_ENABLED   = (1 << 3);
constexpr int USBD_HW_ENUMSPEED = (2 << 4);
constexpr int USBD_HW_SPEED_NC  = (0 << 4);
constexpr int USBD_HW_SPEED_LS  = (1 << 4);
constexpr int USBD_HW_SPEED_FS  = (2 << 4);
constexpr int USBD_HW_SPEED_HS  = (3 << 4);

constexpr int USB_REQ_DIRECTION = (1 << 7);
constexpr int USB_REQ_HOSTTODEV = (0 << 7);
constexpr int USB_REQ_DEVTOHOST = (1 << 7);
constexpr int USB_REQ_TYPE      = (3 << 5);
constexpr int USB_REQ_STANDARD  = (0 << 5);
constexpr int USB_REQ_CLASS     = (1 << 5);
constexpr int USB_REQ_VENDOR    = (2 << 5);
constexpr int USB_REQ_RECIPIENT = (3 << 0);
constexpr int USB_REQ_DEVICE    = (0 << 0);
constexpr int USB_REQ_INTERFACE = (1 << 0);
constexpr int USB_REQ_ENDPOINT  = (2 << 0);
constexpr int USB_REQ_OTHER     = (3 << 0);

enum usbd_machine_state {
    usbd_state_disabled,
    usbd_state_disconnected,
    usbd_state_default,
    usbd_state_addressed,
    usbd_state_configured,
};

enum usbd_ctl_state {
    usbd_ctl_idle,
    usbd_ctl_rxdata,
    usbd_ctl_txdata,
    usbd_ctl_ztxdata,
    usbd_ctl_lastdata,
    usbd_ctl_statusin,
    usbd_ctl_statusout,
};

enum usbd_respond {
    usbd_fail,
    usbd_ack,
    usbd_nak,
};

struct usbd_ctlreq {
    uint8_t     bmRequestType;
    uint8_t     bRequest;
    uint16_t    wValue;
    uint16_t    wIndex;
    uint16_t    wLength;
    uint8_t     data[];
};

struct usbd_status {
    void        *data_ptr;
    uint16_t    data_count;
    uint16_t    data_maxsize;
    uint8_t     device_cfg;
    uint8_t     device_state;
    uint8_t     control_state;
};

typedef void (*usbd_evt_callback)(uint8_t event, uint8_t ep);
typedef void (*usbd_rqc_callback)(usbd_ctlreq *req);

static int32_t ep_read(uint8_t ep, void *buf, uint16_t blen);
static int32_t ep_write(uint8_t ep, const void *buf, uint16_t blen);
static void usbd_process_ep0 (uint8_t event, uint8_t ep);

static usbd_evt_callback  endpoint[4];
static uint32_t ubuf [0x10];  // 64b XXX
static usbd_rqc_callback complete_callback;
static usbd_status ustat;
static uint8_t txBuf [CDC_DATA_SZ], txFill;

static RingBuffer<100> rxBuf;

static void cdc_rx (uint8_t event, uint8_t ep) {
    // there is room if less than 30 of 100 slots are used
    if (rxBuf.avail() < 30) {
        uint8_t tmpBuf [64];
        int n = ep_read(CDC_RXD_EP, tmpBuf, sizeof tmpBuf);
        for (int i = 0; i < n; ++i)
            rxBuf.put(tmpBuf[i]);
    }
}

static void cdc_tx (uint8_t event, uint8_t ep) {
    if (txFill > 0 && ep_write(CDC_TXD_EP, txBuf, txFill) > 0)
        txFill = 0;
}

static void usbd_init() {
    ustat.data_ptr = ubuf;
    ustat.data_maxsize = sizeof ubuf - __builtin_offsetof(usbd_ctlreq, data);
    endpoint[0] = usbd_process_ep0;
    endpoint[CDC_RXD_EP&3] = cdc_rx;
    endpoint[CDC_TXD_EP&3] = cdc_tx;

    RCC->APB1ENR |= (1<<23); // enable usb
    USBDEV->CNTR = USB_CNTR_CTRM | USB_CNTR_RESETM | USB_CNTR_ERRM |
                   USB_CNTR_SOFM | USB_CNTR_SUSPM | USB_CNTR_WKUPM;
}

static usbd_respond cdc_setconf (uint8_t cfg);
static usbd_respond cdc_getdesc (usbd_ctlreq *req, void **address, uint16_t *length);
static usbd_respond cdc_control(usbd_ctlreq *req, usbd_rqc_callback *callback);
static void usbd_process_evt(uint8_t evt, uint8_t ep);

#define VERSION_BCD(maj, min, rev)  (((maj & 0xFF) << 8) | ((min & 0x0F) << 4) | (rev & 0x0F))

#define USB_ARRAY_DESC(...)  {.bLength = 2 + sizeof((uint16_t[]){__VA_ARGS__}),\
                                    .bDescriptorType = USB_DTYPE_STRING,\
                                    .wString = {__VA_ARGS__}}

#define USB_CFG_POWER_MA(mA)        ((mA) >> 1)

constexpr uint8_t USB_CFG_ATTR_RESERVED    = 0x80;
constexpr uint8_t USB_CFG_ATTR_SELFPOWERED = 0x40;

constexpr uint8_t USB_EPDIR_IN             = 0x00;
constexpr uint8_t USB_EPDIR_OUT            = 0x80;
constexpr uint8_t USB_EPTYPE_CONTROL       = 0x00;
constexpr uint8_t USB_EPTYPE_ISOCHRONUS    = 0x01;
constexpr uint8_t USB_EPTYPE_BULK          = 0x02;
constexpr uint8_t USB_EPTYPE_INTERRUPT     = 0x03;
constexpr uint8_t USB_EPATTR_NO_SYNC       = 0x00;
constexpr uint8_t USB_EPATTR_ASYNC         = 0x04;
constexpr uint8_t USB_EPATTR_ADAPTIVE      = 0x08;
constexpr uint8_t USB_EPATTR_SYNC          = 0x0C;
constexpr uint8_t USB_EPUSAGE_DATA         = 0x00;
constexpr uint8_t USB_EPUSAGE_FEEDBACK     = 0x10;
constexpr uint8_t USB_EPUSAGE_IMP_FEEDBACK = 0x20;

constexpr uint8_t NO_DESCRIPTOR            = 0x00;
constexpr uint8_t INTSERIALNO_DESC         = 0xFE;

constexpr uint8_t USB_CLASS_PER_INTERFACE  = 0x00;
constexpr uint8_t USB_SUBCLASS_NONE        = 0x00;
constexpr uint8_t USB_PROTO_NONE           = 0x00;
constexpr uint8_t USB_CLASS_AUDIO          = 0x01;
constexpr uint8_t USB_CLASS_PHYSICAL       = 0x05;
constexpr uint8_t USB_CLASS_STILL_IMAGE    = 0x06;
constexpr uint8_t USB_CLASS_PRINTER        = 0x07;
constexpr uint8_t USB_CLASS_MASS_STORAGE   = 0x08;
constexpr uint8_t USB_CLASS_HUB            = 0x09;
constexpr uint8_t USB_CLASS_CSCID          = 0x0B;
constexpr uint8_t USB_CLASS_CONTENT_SEC    = 0x0D;
constexpr uint8_t USB_CLASS_VIDEO          = 0x0E;
constexpr uint8_t USB_CLASS_HEALTHCARE     = 0x0F;
constexpr uint8_t USB_CLASS_AV             = 0x10;
constexpr uint8_t USB_CLASS_BILLBOARD      = 0x11;
constexpr uint8_t USB_CLASS_CBRIDGE        = 0x12;
constexpr uint8_t USB_CLASS_DIAGNOSTIC     = 0xDC;
constexpr uint8_t USB_CLASS_WIRELESS       = 0xE0;
constexpr uint8_t USB_CLASS_MISC           = 0xEF;
constexpr uint8_t USB_CLASS_APP_SPEC       = 0xFE;
constexpr uint8_t USB_CLASS_VENDOR         = 0xFF;
constexpr uint8_t USB_SUBCLASS_VENDOR      = 0xFF;
constexpr uint8_t USB_PROTO_VENDOR         = 0xFF;

constexpr uint8_t USB_DTYPE_DEVICE         = 0x01;
constexpr uint8_t USB_DTYPE_CONFIGURATION  = 0x02;
constexpr uint8_t USB_DTYPE_STRING         = 0x03;
constexpr uint8_t USB_DTYPE_INTERFACE      = 0x04;
constexpr uint8_t USB_DTYPE_ENDPOINT       = 0x05;
constexpr uint8_t USB_DTYPE_QUALIFIER      = 0x06;
constexpr uint8_t USB_DTYPE_OTHER          = 0x07;
constexpr uint8_t USB_DTYPE_INTERFACEPOWER = 0x08;
constexpr uint8_t USB_DTYPE_OTG            = 0x09;
constexpr uint8_t USB_DTYPE_DEBUG          = 0x0A;
constexpr uint8_t USB_DTYPE_INTERFASEASSOC = 0x0B;
constexpr uint8_t USB_DTYPE_CS_INTERFACE   = 0x24;
constexpr uint8_t USB_DTYPE_CS_ENDPOINT    = 0x25;

constexpr uint8_t USB_STD_GET_STATUS       = 0x00;
constexpr uint8_t USB_STD_CLEAR_FEATURE    = 0x01;
constexpr uint8_t USB_STD_SET_FEATURE      = 0x03;
constexpr uint8_t USB_STD_SET_ADDRESS      = 0x05;
constexpr uint8_t USB_STD_GET_DESCRIPTOR   = 0x06;
constexpr uint8_t USB_STD_SET_DESCRIPTOR   = 0x07;
constexpr uint8_t USB_STD_GET_CONFIG       = 0x08;
constexpr uint8_t USB_STD_SET_CONFIG       = 0x09;
constexpr uint8_t USB_STD_GET_INTERFACE    = 0x0A;
constexpr uint8_t USB_STD_SET_INTERFACE    = 0x0B;
constexpr uint8_t USB_STD_SYNCH_FRAME      = 0x0C;

constexpr uint8_t USB_FEAT_ENDPOINT_HALT   = 0x00;
constexpr uint8_t USB_FEAT_REMOTE_WKUP     = 0x01;
constexpr uint8_t USB_FEAT_TEST_MODE       = 0x02;
constexpr uint8_t USB_FEAT_DEBUG_MODE      = 0x06;

constexpr uint8_t USB_TEST_J               = 0x01;
constexpr uint8_t USB_TEST_K               = 0x02;
constexpr uint8_t USB_TEST_SE0_NAK         = 0x03;
constexpr uint8_t USB_TEST_PACKET          = 0x04;
constexpr uint8_t USB_TEST_FORCE_ENABLE    = 0x05;

constexpr uint8_t USB_CLASS_CDC                  = 0x02;
constexpr uint8_t USB_CLASS_CDC_DATA             = 0x0A;
constexpr uint8_t USB_CDC_SUBCLASS_ACM           = 0x02;
constexpr uint8_t USB_CDC_PROTO_V25TER           = 0x01;

constexpr uint8_t USB_DTYPE_CDC_HEADER           = 0x00;
constexpr uint8_t USB_DTYPE_CDC_CALL_MANAGEMENT  = 0x01;
constexpr uint8_t USB_DTYPE_CDC_ACM              = 0x02;
constexpr uint8_t USB_DTYPE_CDC_UNION            = 0x06;
constexpr uint8_t USB_DTYPE_CDC_COUNTRY          = 0x07;

constexpr uint8_t USB_CDC_SET_LINE_CODING        = 0x20;
constexpr uint8_t USB_CDC_GET_LINE_CODING        = 0x21;
constexpr uint8_t USB_CDC_SET_CONTROL_LINE_STATE = 0x22;

constexpr uint8_t USB_CDC_1_STOP_BITS            = 0x00;
constexpr uint8_t USB_CDC_NO_PARITY              = 0x00;

constexpr uint16_t USB_LANGID_ENG_US = 0x0409;

struct usb_header_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
} __attribute__((packed));

struct usb_device_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t bcdUSB;
    uint8_t  bDeviceClass;
    uint8_t  bDeviceSubClass;
    uint8_t  bDeviceProtocol;
    uint8_t  bMaxPacketSize0;
    uint16_t idVendor;
    uint16_t idProduct;
    uint16_t bcdDevice;
    uint8_t  iManufacturer;
    uint8_t  iProduct;
    uint8_t  iSerialNumber;
    uint8_t  bNumConfigurations;
} __attribute__((packed));

struct usb_config_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wTotalLength;
    uint8_t  bNumInterfaces;
    uint8_t  bConfigurationValue;
    uint8_t  iConfiguration;
    uint8_t  bmAttributes;
    uint8_t  bMaxPower;
} __attribute__((packed));

struct usb_interface_descriptor {
    uint8_t bLength;
    uint8_t bDescriptorType;
    uint8_t bInterfaceNumber;
    uint8_t bAlternateSetting;
    uint8_t bNumEndpoints;
    uint8_t bInterfaceClass;
    uint8_t bInterfaceSubClass;
    uint8_t bInterfaceProtocol;
    uint8_t iInterface;
} __attribute__((packed));

struct usb_endpoint_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bEndpointAddress;
    uint8_t  bmAttributes;
    uint16_t wMaxPacketSize;
    uint8_t  bInterval;
} __attribute__((packed));

struct usb_string_descriptor {
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint16_t wString[];
} __attribute__((packed));

struct usb_cdc_header_desc {
    uint8_t     bFunctionLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint16_t    bcdCDC;
} __attribute__ ((packed));

struct usb_cdc_union_desc {
    uint8_t     bFunctionLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bMasterInterface0;
    uint8_t     bSlaveInterface0;
} __attribute__ ((packed));

struct usb_cdc_call_mgmt_desc {
    uint8_t     bFunctionLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bmCapabilities;
    uint8_t     bDataInterface;
} __attribute__ ((packed));

struct usb_cdc_acm_desc {
    uint8_t     bFunctionLength;
    uint8_t     bDescriptorType;
    uint8_t     bDescriptorSubType;
    uint8_t     bmCapabilities;
} __attribute__ ((packed));

struct usb_cdc_line_coding {
    uint32_t    dwDTERate;
    uint8_t     bCharFormat;
    uint8_t     bParityType;
    uint8_t     bDataBits;
} __attribute__ ((packed));

#define USB_EP_SWBUF_TX     USB_EP_DTOG_RX
#define USB_EP_SWBUF_RX     USB_EP_DTOG_TX

#define EP_TOGGLE_SET(epr, bits, mask) *(epr) = (*(epr) ^ (bits)) & (USB_EPREG_MASK | (mask))

#define EP_TX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_STALL,                   USB_EPTX_STAT)
#define EP_RX_STALL(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_STALL,                   USB_EPRX_STAT)
#define EP_TX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_TX_NAK,                     USB_EPTX_STAT | USB_EP_DTOG_TX)
#define EP_RX_UNSTALL(epr)  EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EPRX_STAT | USB_EP_DTOG_RX)
#define EP_TX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_TX_VALID,                   USB_EPTX_STAT)
#define EP_RX_VALID(epr)    EP_TOGGLE_SET((epr), USB_EP_RX_VALID,                   USB_EPRX_STAT)

#define USB_PMASIZE 0x200

typedef struct {
    uint16_t    addr;
    uint16_t    :16;
    uint16_t    cnt;
    uint16_t    :16;
} pma_rec;

union pma_table {
    struct {
        pma_rec     tx;
        pma_rec     rx;
    };
    struct {
        pma_rec     tx0;
        pma_rec     tx1;
    };
    struct {
        pma_rec     rx0;
        pma_rec     rx1;
    };
};

static pma_table *EPT(uint8_t ep) {
    return (pma_table*)((ep & 0x07) * 16 + USB_PMAADDR);
}

static uint16_t *PMA(uint16_t addr) {
    return (uint16_t*)(USB_PMAADDR + 2 * addr);
}

static volatile uint16_t *EPR(uint8_t ep) {
    return (uint16_t*)((ep & 0x07) * 4 + USB_BASE);
}

static uint16_t get_next_pma(uint16_t sz) {
    uint16_t _result = USB_PMASIZE;
    for (int i = 0; i < 8; i++) {
        pma_table *tbl = EPT(i);
        if ((tbl->tx.addr) && (tbl->tx.addr < _result)) _result = tbl->tx.addr;
        if ((tbl->rx.addr) && (tbl->rx.addr < _result)) _result = tbl->rx.addr;
    }
    return _result < 0x020 + sz ? 0 : (_result - sz);
}

static void ep_setstall(uint8_t ep, bool stall) {
    volatile uint16_t *reg = EPR(ep);
    /* If it's an IN endpoint */
    if (ep & 0x80) {
        /* DISABLED endpoint can't be stalled or unstalled */
        if (USB_EP_TX_DIS == (*reg & USB_EPTX_STAT))
            return;
        if (stall)
            EP_TX_STALL(reg);
        else
            EP_TX_UNSTALL(reg);
    } else {
        if (USB_EP_RX_DIS == (*reg & USB_EPRX_STAT))
            return;
        if (stall)
            EP_RX_STALL(reg);
        else
            EP_RX_UNSTALL(reg);
    }
}

static bool ep_isstalled(uint8_t ep) {
    if (ep & 0x80)
        return (USB_EP_TX_STALL == (USB_EPTX_STAT & *EPR(ep)));
    else
        return (USB_EP_RX_STALL == (USB_EPRX_STAT & *EPR(ep)));
}

static bool ep_config(uint8_t ep, uint8_t eptype, uint16_t epsize) {
    volatile uint16_t *reg = EPR(ep);
    pma_table *tbl = EPT(ep);
    epsize += epsize & 1; // epsize should be 16-bit aligned

    switch (eptype) {
    case USB_EPTYPE_CONTROL: *reg = USB_EP_CONTROL   | (ep & 0x07); break;
    case USB_EPTYPE_BULK:    *reg = USB_EP_BULK      | (ep & 0x07); break;
    default:                 *reg = USB_EP_INTERRUPT | (ep & 0x07); break;
    }
    /* if it TX or CONTROL endpoint */
    if ((ep & 0x80) || (eptype == USB_EPTYPE_CONTROL)) {
        uint16_t _pma;
        _pma = get_next_pma(epsize);
        if (_pma == 0)
            return false;
        tbl->tx.addr = _pma;
        tbl->tx.cnt  = 0;
        EP_TX_UNSTALL(reg);
    }
    if (!(ep & 0x80)) {
        uint16_t _rxcnt;
        uint16_t _pma;
        if (epsize > 62) {
            if (epsize & 0x1F)
                epsize &= 0x1F;
            else
                epsize -= 0x20;
            _rxcnt = 0x8000 | (epsize << 5);
            epsize += 0x20;
        } else
            _rxcnt = epsize << 9;
        _pma = get_next_pma(epsize);
        if (_pma == 0) return false;
        tbl->rx.addr = _pma;
        tbl->rx.cnt  = _rxcnt;
        EP_RX_UNSTALL(reg);
    }
    return true;
}

static void ep_deconfig(uint8_t ep) {
    pma_table *ept = EPT(ep);
    *EPR(ep) &= ~USB_EPREG_MASK;
    ept->rx.addr = 0;
    ept->rx.cnt  = 0;
    ept->tx.addr = 0;
    ept->tx.cnt  = 0;
}

static uint16_t pma_read (void* ptr, uint16_t blen, pma_rec *rx) {
    uint8_t *buf = (uint8_t*) ptr;
    uint16_t *pma = PMA(rx->addr);
    uint16_t rxcnt = rx->cnt & 0x03FF;
    rx->cnt &= ~0x3FF;
    if (blen > rxcnt)
        blen = rxcnt;
    rxcnt = blen;
    while (blen) {
        uint16_t _t = *pma;
        *buf++ = _t & 0xFF;
        if (--blen) {
            *buf++ = _t >> 8;
            pma += 2;
            blen--;
        } else break;
    }
    return rxcnt;
}

static int32_t ep_read(uint8_t ep, void *buf, uint16_t blen) {
    pma_table *tbl = EPT(ep);
    volatile uint16_t *reg = EPR(ep);
    switch (*reg & (USB_EPRX_STAT | USB_EP_T_FIELD | USB_EP_KIND)) {
    /* regular endpoint */
    case (USB_EP_RX_NAK | USB_EP_BULK):
    case (USB_EP_RX_NAK | USB_EP_CONTROL):
    case (USB_EP_RX_NAK | USB_EP_INTERRUPT):
        {
        int32_t res = pma_read(buf, blen, &tbl->rx);
        /* setting endpoint to VALID state */
        EP_RX_VALID(reg);
        return res;
        }
    /* invalid or not ready */
    default:
        //return -1;
        return 0;
    }
}

static void pma_write(const void* ptr, uint16_t blen, pma_rec *tx) {
    const uint8_t *buf = (const uint8_t*) ptr;
    uint16_t *pma = PMA(tx->addr);
    tx->cnt = blen;
    while (blen > 1) {
        *pma = buf[1] << 8 | buf[0];
        pma += 2;
        buf += 2;
        blen -= 2;
    }
    if (blen) *pma = *buf;
}

static int32_t ep_write(uint8_t ep, const void *buf, uint16_t blen) {
    pma_table *tbl = EPT(ep);
    volatile uint16_t *reg = EPR(ep);
    switch (*reg & (USB_EPTX_STAT | USB_EP_T_FIELD | USB_EP_KIND)) {
    /* regular endpoint */
    case (USB_EP_TX_NAK | USB_EP_BULK):
    case (USB_EP_TX_NAK | USB_EP_CONTROL):
    case (USB_EP_TX_NAK | USB_EP_INTERRUPT):
        pma_write((uint8_t*) buf, blen, &tbl->tx);
        EP_TX_VALID(reg);
        break;
    /* invalid or not ready */
    default:
        return -1;
    }
    return blen;
}

static void evt_poll() {
    uint8_t _ev, _ep;
    uint16_t _istr = USBDEV->ISTR;
    _ep = _istr & USB_ISTR_EP_ID;

    if (_istr & USB_ISTR_CTR) {
        volatile uint16_t *reg = EPR(_ep);
        if (*reg & USB_EP_CTR_TX) {
            *reg &= USB_EPREG_MASK ^ USB_EP_CTR_TX;
            _ep |= 0x80;
            _ev = usbd_evt_eptx;
        } else {
            *reg &= USB_EPREG_MASK ^ USB_EP_CTR_RX;
            _ev = *reg & USB_EP_SETUP ? usbd_evt_epsetup : usbd_evt_eprx;
        }
    } else if (_istr & USB_ISTR_RESET) {
        USBDEV->ISTR &= ~USB_ISTR_RESET;
        USBDEV->BTABLE = 0;
        for (int i = 0; i < 8; i++)
            ep_deconfig(i);
        _ev = usbd_evt_reset;
    } else if (_istr & USB_ISTR_SOF) {
        _ev = usbd_evt_sof;
        USBDEV->ISTR &= ~USB_ISTR_SOF;
    } else if (_istr & USB_ISTR_WKUP) {
        _ev = usbd_evt_wkup;
        USBDEV->CNTR &= ~USB_CNTR_FSUSP;
        USBDEV->ISTR &= ~USB_ISTR_WKUP;
    } else if (_istr & USB_ISTR_SUSP) {
        _ev = usbd_evt_susp;
        USBDEV->CNTR |= USB_CNTR_FSUSP;
        USBDEV->ISTR &= ~USB_ISTR_SUSP;
    } else if (_istr & USB_ISTR_ERR) {
        USBDEV->ISTR &= ~USB_ISTR_ERR;
        _ev = usbd_evt_error;
    } else
        return;
    usbd_process_evt(_ev, _ep);
}

static uint16_t get_serialno_desc(void *buffer) {
    struct  usb_string_descriptor *dsc = (usb_string_descriptor*) buffer;
    uint16_t *str = dsc->wString;
    uint32_t fnv = *(uint32_t*)(UID_BASE + 0x00) ^
                   *(uint32_t*)(UID_BASE + 0x04) ^
                   *(uint32_t*)(UID_BASE + 0x08);
    for (int i = 28; i >= 0; i -= 4 ) {
        uint16_t c = (fnv >> i) & 0x0F;
        c += c < 10 ? '0' : ('A' - 10);
        *str++ = c;
    }
    dsc->bDescriptorType = USB_DTYPE_STRING;
    dsc->bLength = 18;
    return 18;
}

static void usbd_process_reset() {
    ustat.device_state = usbd_state_default;
    ustat.control_state = usbd_ctl_idle;
    ustat.device_cfg = 0;
    ep_config(0, USB_EPTYPE_CONTROL, CDC_EP0_SIZE);
    USBDEV->DADDR = USB_DADDR_EF;
}

static void usbd_set_address (usbd_ctlreq *req) {
    USBDEV->DADDR = USB_DADDR_EF | req->wValue;
    ustat.device_state = req->wValue ? usbd_state_addressed
                                     : usbd_state_default;
}

static void usbd_process_callback () {
    if (complete_callback) {
        complete_callback((usbd_ctlreq*) ubuf);
        complete_callback = 0;
    }
}

static usbd_respond usbd_configure(uint8_t config) {
    if (cdc_setconf(config) == usbd_ack) {
        ustat.device_cfg = config;
        ustat.device_state = config ? usbd_state_configured
                                    : usbd_state_addressed;
        return usbd_ack;
    }
    return usbd_fail;
}

static usbd_respond usbd_process_request(usbd_ctlreq *req) {
    /* processing control request by callback */
    usbd_respond r = cdc_control(req, &complete_callback);
    if (r != usbd_fail)
        return r;

    switch (req->bmRequestType & (USB_REQ_TYPE | USB_REQ_RECIPIENT)) {

    case USB_REQ_STANDARD | USB_REQ_DEVICE:
        switch (req->bRequest) {
        case USB_STD_GET_CONFIG:
            req->data[0] = ustat.device_cfg;
            return usbd_ack;
        case USB_STD_GET_DESCRIPTOR:
            if (req->wValue == ((USB_DTYPE_STRING << 8) | INTSERIALNO_DESC)) {
                ustat.data_count = get_serialno_desc(req->data);
                return usbd_ack;
            }
            return cdc_getdesc(req, &ustat.data_ptr, &ustat.data_count);
        case USB_STD_GET_STATUS:
            req->data[0] = 0;
            req->data[1] = 0;
            return usbd_ack;
        case USB_STD_SET_ADDRESS:
            complete_callback = usbd_set_address;
            return usbd_ack;
        case USB_STD_SET_CONFIG:
            return usbd_configure(req->wValue);
        }
        break;

    case USB_REQ_STANDARD | USB_REQ_INTERFACE:
        switch (req->bRequest) {
        case USB_STD_GET_STATUS:
            req->data[0] = 0;
            req->data[1] = 0;
            return usbd_ack;
        }
        break;

    case USB_REQ_STANDARD | USB_REQ_ENDPOINT:
        switch (req->bRequest) {
        case USB_STD_SET_FEATURE:
            ep_setstall(req->wIndex, 1);
            return usbd_ack;
        case USB_STD_CLEAR_FEATURE:
            ep_setstall(req->wIndex, 0);
            return usbd_ack;
        case USB_STD_GET_STATUS:
            req->data[0] = ep_isstalled(req->wIndex) ? 1 : 0;
            req->data[1] = 0;
            return usbd_ack;
        }
        break;
    }
    return usbd_fail;
}

static void usbd_stall_pid(uint8_t ep) {
    ep_setstall(ep & 0x7F, 1);
    ep_setstall(ep | 0x80, 1);
    ustat.control_state = usbd_ctl_idle;
}

static void usbd_process_eptx(uint8_t ep) {
    int32_t _t;
    switch (ustat.control_state) {
    case usbd_ctl_ztxdata:
    case usbd_ctl_txdata:
        _t = ustat.data_count < CDC_EP0_SIZE ? ustat.data_count : CDC_EP0_SIZE;
        ep_write(ep, ustat.data_ptr, _t);
        ustat.data_ptr = (uint8_t*) ustat.data_ptr + _t;
        ustat.data_count -= _t;
        /* if all data is not sent */
        if (0 != ustat.data_count)
            break;
        /* if last packet has a EP0 size and host awaiting for the more data ZLP should be sent*/
        /* if ZLP required, control state will be unchanged, therefore next TX event sends ZLP */
        if ( usbd_ctl_txdata == ustat.control_state || _t != CDC_EP0_SIZE) {
            ustat.control_state = usbd_ctl_lastdata; /* no ZLP required */
        }
        break;
    case usbd_ctl_lastdata:
        ustat.control_state = usbd_ctl_statusout;
        break;
    case usbd_ctl_statusin:
        ustat.control_state = usbd_ctl_idle;
        return usbd_process_callback();
    }
}

static void usbd_process_eprx(uint8_t ep) {
    uint16_t _t;
    usbd_ctlreq *const req = (usbd_ctlreq*) ubuf;
    switch (ustat.control_state) {
    case usbd_ctl_idle:
        /* read SETUP packet, send STALL_PID if incorrect packet length */
        if (0x08 !=  ep_read(ep, req, ustat.data_maxsize)) {
            usbd_stall_pid(ep);
            return;
        }
        ustat.data_ptr = req->data;
        ustat.data_count = req->wLength;
        /* processing request with no payload data*/
        if ((req->bmRequestType & USB_REQ_DEVTOHOST) || (0 == req->wLength))
            break;
        /* checking available memory for DATA OUT stage */
        if (req->wLength > ustat.data_maxsize) {
            usbd_stall_pid(ep);
            return;
        }
        /* continue DATA OUT stage */
        ustat.control_state = usbd_ctl_rxdata;
        return;
    case usbd_ctl_rxdata:
        /*receive DATA OUT packet(s) */
        _t = ep_read(ep, ustat.data_ptr, ustat.data_count);
        if (ustat.data_count < _t) {
        /* if received packet is large than expected */
        /* Must be error. Let's drop this request */
            return usbd_stall_pid(ep);
        } else if (ustat.data_count != _t) {
        /* if all data payload was not received yet */
            ustat.data_count -= _t;
            ustat.data_ptr = (uint8_t*) ustat.data_ptr + _t;
            return;
        }
        break;
    case usbd_ctl_statusout:
        /* reading STATUS OUT data to buffer */
        ep_read(ep, ustat.data_ptr, ustat.data_maxsize);
        ustat.control_state = usbd_ctl_idle;
        usbd_process_callback();
        return;
    default:
        /* unexpected RX packet */
        usbd_stall_pid(ep);
        return;
    }
    /* usb request received. let's handle it */
    ustat.data_ptr = req->data;
    ustat.data_count = /*req->wLength;*/ustat.data_maxsize;
    switch (usbd_process_request(req)) {
    case usbd_ack:
        if (req->bmRequestType & USB_REQ_DEVTOHOST) {
            /* return data from function */
            if (ustat.data_count >= req->wLength) {
                ustat.data_count = req->wLength;
                ustat.control_state = usbd_ctl_txdata;
            } else {
                /* DATA IN packet smaller than requested */
                /* ZLP maybe wanted */
                ustat.control_state = usbd_ctl_ztxdata;
            }
            usbd_process_eptx(ep | 0x80);
            return;

        } else {
            /* confirming by ZLP in STATUS_IN stage */
            ep_write(ep | 0x80, 0, 0);
            ustat.control_state = usbd_ctl_statusin;
        }
        break;
    case usbd_nak:
        ustat.control_state = usbd_ctl_statusin;
        break;
    default:
        usbd_stall_pid(ep);
    }
}

static void usbd_process_ep0 (uint8_t event, uint8_t ep) {
    switch (event) {
    case usbd_evt_epsetup:
        /* force switch to setup state */
        ustat.control_state = usbd_ctl_idle;
        complete_callback = 0;
    case usbd_evt_eprx:
        usbd_process_eprx(ep);
        return;
    case usbd_evt_eptx:
        usbd_process_eptx(ep);
        return;
    }
}

static void usbd_process_evt(uint8_t evt, uint8_t ep) {
    switch (evt) {
    case usbd_evt_reset:
        usbd_process_reset();
        break;
    case usbd_evt_eprx:
    case usbd_evt_eptx:
    case usbd_evt_epsetup:
        if (endpoint[ep & 0x03])
            endpoint[ep & 0x03](evt, ep);
        break;
    default:
        break;
    }
}

struct cdc_config {
    struct usb_config_descriptor        config;
    struct usb_interface_descriptor     comm;
    struct usb_cdc_header_desc          cdc_hdr;
    struct usb_cdc_call_mgmt_desc       cdc_mgmt;
    struct usb_cdc_acm_desc             cdc_acm;
    struct usb_cdc_union_desc           cdc_union;
    struct usb_endpoint_descriptor      comm_ep;
    struct usb_interface_descriptor     data;
    struct usb_endpoint_descriptor      data_eprx;
    struct usb_endpoint_descriptor      data_eptx;
} __attribute__((packed));

static const struct cdc_config config_desc = {
    .config = {
        .bLength                = sizeof(struct usb_config_descriptor),
        .bDescriptorType        = USB_DTYPE_CONFIGURATION,
        .wTotalLength           = sizeof(struct cdc_config),
        .bNumInterfaces         = 2,
        .bConfigurationValue    = 1,
        .iConfiguration         = NO_DESCRIPTOR,
        .bmAttributes           = USB_CFG_ATTR_RESERVED | USB_CFG_ATTR_SELFPOWERED,
        .bMaxPower              = USB_CFG_POWER_MA(100),
    },
    .comm = {
        .bLength                = sizeof(struct usb_interface_descriptor),
        .bDescriptorType        = USB_DTYPE_INTERFACE,
        .bInterfaceNumber       = 0,
        .bAlternateSetting      = 0,
        .bNumEndpoints          = 1,
        .bInterfaceClass        = USB_CLASS_CDC,
        .bInterfaceSubClass     = USB_CDC_SUBCLASS_ACM,
        .bInterfaceProtocol     = USB_CDC_PROTO_V25TER,
        .iInterface             = NO_DESCRIPTOR,
    },
    .cdc_hdr = {
        .bFunctionLength        = sizeof(struct usb_cdc_header_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_HEADER,
        .bcdCDC                 = VERSION_BCD(1,1,0),
    },
    .cdc_mgmt = {
        .bFunctionLength        = sizeof(struct usb_cdc_call_mgmt_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_CALL_MANAGEMENT,
        .bmCapabilities         = 0,
        .bDataInterface         = 1,

    },
    .cdc_acm = {
        .bFunctionLength        = sizeof(struct usb_cdc_acm_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_ACM,
        .bmCapabilities         = 0,
    },
    .cdc_union = {
        .bFunctionLength        = sizeof(struct usb_cdc_union_desc),
        .bDescriptorType        = USB_DTYPE_CS_INTERFACE,
        .bDescriptorSubType     = USB_DTYPE_CDC_UNION,
        .bMasterInterface0      = 0,
        .bSlaveInterface0       = 1,
    },
    .comm_ep = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_NTF_EP,
        .bmAttributes           = USB_EPTYPE_INTERRUPT,
        .wMaxPacketSize         = CDC_NTF_SZ,
        .bInterval              = 0xFF,
    },
    .data = {
        .bLength                = sizeof(struct usb_interface_descriptor),
        .bDescriptorType        = USB_DTYPE_INTERFACE,
        .bInterfaceNumber       = 1,
        .bAlternateSetting      = 0,
        .bNumEndpoints          = 2,
        .bInterfaceClass        = USB_CLASS_CDC_DATA,
        .bInterfaceSubClass     = USB_SUBCLASS_NONE,
        .bInterfaceProtocol     = USB_PROTO_NONE,
        .iInterface             = NO_DESCRIPTOR,
    },
    .data_eprx = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_RXD_EP,
        .bmAttributes           = USB_EPTYPE_BULK,
        .wMaxPacketSize         = CDC_DATA_SZ,
        .bInterval              = 0x01,
    },
    .data_eptx = {
        .bLength                = sizeof(struct usb_endpoint_descriptor),
        .bDescriptorType        = USB_DTYPE_ENDPOINT,
        .bEndpointAddress       = CDC_TXD_EP,
        .bmAttributes           = USB_EPTYPE_BULK,
        .wMaxPacketSize         = CDC_DATA_SZ,
        .bInterval              = 0x01,
    },
};

static const struct usb_device_descriptor device_desc = {
    .bLength            = sizeof(struct usb_device_descriptor),
    .bDescriptorType    = USB_DTYPE_DEVICE,
    .bcdUSB             = VERSION_BCD(2,0,0),
    .bDeviceClass       = USB_CLASS_CDC,
    .bDeviceSubClass    = USB_SUBCLASS_NONE,
    .bDeviceProtocol    = USB_PROTO_NONE,
    .bMaxPacketSize0    = CDC_EP0_SIZE,
    .idVendor           = 0x0483,
    .idProduct          = 0x5740,
    .bcdDevice          = VERSION_BCD(1,0,0),
    .iManufacturer      = 1,
    .iProduct           = 2,
    .iSerialNumber      = INTSERIALNO_DESC,
    .bNumConfigurations = 1,
};

static const struct usb_string_descriptor lang_desc =
    USB_ARRAY_DESC(USB_LANGID_ENG_US);

static const struct usb_string_descriptor manuf_desc_en =
    USB_ARRAY_DESC('F','1','0','3','-','O','S','S');

static const struct usb_string_descriptor prod_desc_en  =
    USB_ARRAY_DESC('J','e','e','H',' ','c','o','n','s','o','l','e');

static const struct usb_string_descriptor *const dtable[] = {
    &lang_desc,
    &manuf_desc_en,
    &prod_desc_en,
};

static usbd_respond cdc_getdesc (usbd_ctlreq *req, void **address, uint16_t *length) {
    const uint8_t dtype = req->wValue >> 8;
    const uint8_t dnumber = req->wValue & 0xFF;
    const void* desc;
    uint16_t len = 0;
    switch (dtype) {
    case USB_DTYPE_DEVICE:
        desc = &device_desc;
        break;
    case USB_DTYPE_CONFIGURATION:
        desc = &config_desc;
        len = sizeof(config_desc);
        break;
    case USB_DTYPE_STRING:
        if (dnumber < 3)
            desc = dtable[dnumber];
        else
            return usbd_fail;
        break;
    default:
        return usbd_fail;
    }
    if (len == 0) {
        len = ((struct usb_header_descriptor*)desc)->bLength;
    }
    *address = (void*)desc;
    *length = len;
    return usbd_ack;
};

static usbd_respond cdc_control(usbd_ctlreq *req, usbd_rqc_callback *callback) {
    if (((USB_REQ_RECIPIENT | USB_REQ_TYPE) & req->bmRequestType) == (USB_REQ_INTERFACE | USB_REQ_CLASS))
        switch (req->bRequest) {
        case USB_CDC_SET_CONTROL_LINE_STATE:
        case USB_CDC_SET_LINE_CODING:
            return usbd_ack;
        }
    return usbd_fail;
}

static usbd_respond cdc_setconf (uint8_t cfg) {
    switch (cfg) {
    case 1:
        ep_config(CDC_RXD_EP, USB_EPTYPE_BULK, CDC_DATA_SZ);
        ep_config(CDC_TXD_EP, USB_EPTYPE_BULK, CDC_DATA_SZ);
        ep_config(CDC_NTF_EP, USB_EPTYPE_INTERRUPT, CDC_NTF_SZ);
        ep_write(CDC_TXD_EP, 0, 0);
        return usbd_ack;
    }
    return usbd_fail;
}
