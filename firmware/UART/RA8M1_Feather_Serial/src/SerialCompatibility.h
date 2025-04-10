#ifndef SerialCompatibility_h
#define SerialCompatibility_h

#define MAX_BUFF_SIZE             512
#define TRANSFER_LENGTH           (512u)
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                    UART_EVENT_ERR_PARITY)

#define ENABLE_SERIAL2

#ifdef ENABLE_SERIAL2
/* Serial definition
 * channel 2
 * uart_callback
 * g_uart2
 *
 *
 *
 */

static volatile uint8_t g_uart_event_0 = (0x00);

uint8_t  g_dest_0[TRANSFER_LENGTH];
uint8_t  g_out_of_band_received_0[TRANSFER_LENGTH];
static volatile uint32_t g_transfer_complete_0 = 0;
static volatile uint32_t g_receive_complete_0  = 0;
static volatile uint16_t g_out_of_band_index_0 = 0;

void uart_callback_0 (uart_callback_args_t * p_args);
void uart_callback_0 (uart_callback_args_t * p_args)
{
    g_uart_event_0 = (uint8_t)p_args->event;
    switch (p_args->event)
    {
        case UART_EVENT_RX_CHAR:
        {
            if (sizeof(g_out_of_band_received_0) > g_out_of_band_index_0)
            {
                if (UART_DATA_BITS_8 >= g_uart2_cfg.data_bits)
                {
                    g_out_of_band_received_0[g_out_of_band_index_0++] = (uint8_t) p_args->data;
                }
                else
                {
                    uint16_t * p_dest = (uint16_t *) &g_out_of_band_received_0[g_out_of_band_index_0];
                    *p_dest              = (uint16_t) p_args->data;
                    g_out_of_band_index_0 += 2;
                }
            }
            break;
        }
        /* Receive complete */
        case UART_EVENT_RX_COMPLETE:
        {
            g_receive_complete_0 = 1;
            break;
        }
        /* Transmit complete */
        case UART_EVENT_TX_COMPLETE:
        {
            g_transfer_complete_0 = 1;
            break;
        }
        default:
        {
        }
    }
}

class SerialCompatibilityLayer {
private:
    uint8_t buff[MAX_BUFF_SIZE], aux[MAX_BUFF_SIZE];
    uint16_t idx, fin;
    int16_t cnt;
    void fill_buff();

    fsp_err_t uart_read(uint8_t *rx, uint16_t *len);
    fsp_err_t uart_print(uint8_t *p_msg, uint16_t msg_len);
    void uart_init(uint32_t *baud);
    void uart_close(void);

public:
    SerialCompatibilityLayer();
    uint16_t available();
    uint8_t read();
    void write(uint8_t byte);
    void print(uint8_t *p_msg);
    void println(uint8_t *p_msg);
    void print(long long p_msg);
    void println(long long p_msg);
    uint8_t peek();
    void begin(uint32_t baud);
};

void SerialCompatibilityLayer::begin(uint32_t baud) {
    this->uart_init(&baud);
}

void SerialCompatibilityLayer::write(uint8_t byte) {
    this->uart_print(&byte, 1);
}

SerialCompatibilityLayer::SerialCompatibilityLayer() {
    memset(this->buff, 0, sizeof(this->buff));
    this->idx = 0;
    this->fin = 0;
    this->cnt = 0;
}

uint16_t SerialCompatibilityLayer::available() {
    this->fill_buff();
    return this->cnt;
}

uint8_t SerialCompatibilityLayer::read() {
    this->fill_buff();
    uint8_t ret = this->buff[this->idx++];
    this->cnt--;
    if (this->idx == MAX_BUFF_SIZE) {
        this->idx = 0;
    }
    if (this->cnt < 0) {
        assert(false);
    }
    return ret;
}

void SerialCompatibilityLayer::fill_buff() {
    uint16_t len = 0;
    fsp_err_t err = this->uart_read(this->aux, &len);
    if (err == FSP_SUCCESS) {
        this->cnt += (int16_t)len;
        for (int i = 0; i < len; i++) {
            this->buff[this->fin++] = this->aux[i];
            if (this->fin == MAX_BUFF_SIZE) {
                this->fin = 0;
            }
            if (this->fin == this->idx) {
                assert(false);
            }
        }
    }
}

uint8_t SerialCompatibilityLayer::peek() {
    this->fill_buff();
    return this->buff[this->idx];
}

fsp_err_t SerialCompatibilityLayer::uart_read(uint8_t *rx, uint16_t *len) {
    fsp_err_t err = FSP_SUCCESS;

    if (g_out_of_band_index_0) {
        g_receive_complete_0 = false;
        if (rx != NULL) {
            memcpy(rx, g_out_of_band_received_0, g_out_of_band_index_0);
        }
        *len = g_out_of_band_index_0;
        g_out_of_band_index_0 = 0;
        return FSP_SUCCESS;
    }
    else {
        return FSP_ERR_IP_CHANNEL_NOT_PRESENT;
    }
    return err;
}

fsp_err_t SerialCompatibilityLayer::uart_print(uint8_t *p_msg, uint16_t msg_len) {
    fsp_err_t err = FSP_SUCCESS;

    /* Reset callback capture variable */
    g_uart_event_0 = (0x00);

    /* Writing to terminal */
    err = R_SCI_B_UART_Write(&g_uart2_ctrl, p_msg, msg_len);
    assert(err == FSP_SUCCESS);

    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);

    return err;
}

void SerialCompatibilityLayer::uart_init(uint32_t *baud) {
    fsp_err_t err = R_SCI_B_UART_Open(&g_uart2_ctrl, &g_uart2_cfg);
    assert(err == FSP_SUCCESS);
    sci_b_baud_setting_t scif_baud_setting;
    uint32_t baud_rate = *baud;
    bool enable_bitrate_modulation = true;
    uint32_t error_rate_x_1000 = 5000;
    err = R_SCI_B_UART_BaudCalculate(baud_rate, enable_bitrate_modulation, error_rate_x_1000, &scif_baud_setting);
    assert(FSP_SUCCESS == err);
    err = R_SCI_B_UART_BaudSet(&g_uart2_ctrl, (void *) &scif_baud_setting);
}

void SerialCompatibilityLayer::uart_close(void) {
    fsp_err_t err = R_SCI_B_UART_Close (&g_uart2_ctrl);
    assert(err == FSP_SUCCESS);
}

void SerialCompatibilityLayer::print(uint8_t *p_msg) {
    uint16_t len = 0;
    while (p_msg[len]) {
        len++;
    }
    this->uart_print(p_msg, len);
}

void SerialCompatibilityLayer::println(uint8_t *p_msg) {
    uint16_t len = 0;
    while (p_msg[len]) {
        len++;
    }
    this->uart_print(p_msg, len);
    this->uart_print((uint8_t*)"\n", 1);
}

void SerialCompatibilityLayer::print(long long p_msg) {
    if (p_msg == 0) {
        this->uart_print((uint8_t*)"0", 1);
    }

    if (p_msg < 0) {
        this->uart_print((uint8_t*)"-", 1);
        p_msg *= -1;
    }

    uint16_t len = 0;
    uint8_t nr[20];
    while (p_msg) {
        nr[20 - len - 1] = (uint8_t)(p_msg % 10) + '0';
        len++;
        p_msg /= 10;
    }
    this->uart_print(nr + (20 - len), len);
}

void SerialCompatibilityLayer::println(long long p_msg) {
    this->print(p_msg);
    this->uart_print((uint8_t*)"\n", 1);
}

SerialCompatibilityLayer Serial;
#endif

//
//#ifdef ENABLE_SERIAL1
///* Serial1 definition
// * channel 1
// * uart_callback_1
// * g_uart1
// *
// *
// *
// */
//
//static volatile uint8_t g_uart_event_1 = (0x00);
//
//uint8_t  g_dest_1[TRANSFER_LENGTH];
//uint8_t  g_out_of_band_received_1[TRANSFER_LENGTH];
//static volatile uint32_t g_transfer_complete_1 = 0;
//static volatile uint32_t g_receive_complete_1  = 0;
//static volatile uint16_t g_out_of_band_index_1 = 0;
//
//void uart_callback_1 (uart_callback_args_t * p_args);
//void uart_callback_1 (uart_callback_args_t * p_args)
//{
//    g_uart_event_1 = (uint8_t)p_args->event;
//    switch (p_args->event)
//    {
//        case UART_EVENT_RX_CHAR:
//        {
//            if (sizeof(g_out_of_band_received_1) > g_out_of_band_index_1)
//            {
//                if (UART_DATA_BITS_8 >= g_uart1_cfg.data_bits)
//                {
//                    g_out_of_band_received_1[g_out_of_band_index_1++] = (uint8_t) p_args->data;
//                }
//                else
//                {
//                    uint16_t * p_dest = (uint16_t *) &g_out_of_band_received_1[g_out_of_band_index_1];
//                    *p_dest              = (uint16_t) p_args->data;
//                    g_out_of_band_index_1 += 2;
//                }
//            }
//            break;
//        }
//        /* Receive complete */
//        case UART_EVENT_RX_COMPLETE:
//        {
//            g_receive_complete_1 = 1;
//            break;
//        }
//        /* Transmit complete */
//        case UART_EVENT_TX_COMPLETE:
//        {
//            g_transfer_complete_1 = 1;
//            break;
//        }
//        default:
//        {
//        }
//    }
//}
//
//class SerialCompatibilityLayer_1 {
//private:
//    uint8_t buff[MAX_BUFF_SIZE], aux[MAX_BUFF_SIZE];
//    uint16_t idx, fin;
//    int16_t cnt;
//    void fill_buff();
//
//    fsp_err_t uart_read(uint8_t *rx, uint16_t *len);
//    fsp_err_t uart_print(uint8_t *p_msg, uint16_t msg_len);
//    void uart_init(uint32_t *baud);
//    void uart_close(void);
//
//public:
//    SerialCompatibilityLayer_1();
//    uint16_t available();
//    uint8_t read();
//    void write(uint8_t byte);
//    void print(uint8_t *p_msg);
//    void println(uint8_t *p_msg);
//    void print(long long p_msg);
//    void println(long long p_msg);
//    uint8_t peek();
//    void begin(uint32_t baud);
//};
//
//void SerialCompatibilityLayer_1::begin(uint32_t baud) {
//    this->uart_init(&baud);
//}
//
//void SerialCompatibilityLayer_1::write(uint8_t byte) {
//    this->uart_print(&byte, 1);
//}
//
//SerialCompatibilityLayer_1::SerialCompatibilityLayer_1() {
//    memset(this->buff, 0, sizeof(this->buff));
//    this->idx = 0;
//    this->fin = 0;
//    this->cnt = 0;
//}
//
//uint16_t SerialCompatibilityLayer_1::available() {
//    this->fill_buff();
//    return this->cnt;
//}
//
//uint8_t SerialCompatibilityLayer_1::read() {
//    this->fill_buff();
//    uint8_t ret = this->buff[this->idx++];
//    this->cnt--;
//    if (this->idx == MAX_BUFF_SIZE) {
//        this->idx = 0;
//    }
//    if (this->cnt < 0) {
//        assert(false);
//    }
//    return ret;
//}
//
//void SerialCompatibilityLayer_1::fill_buff() {
//    uint16_t len = 0;
//    fsp_err_t err = this->uart_read(this->aux, &len);
//    if (err == FSP_SUCCESS) {
//        this->cnt += (int16_t)len;
//        for (int i = 0; i < len; i++) {
//            this->buff[this->fin++] = this->aux[i];
//            if (this->fin == MAX_BUFF_SIZE) {
//                this->fin = 0;
//            }
//            if (this->fin == this->idx) {
//                assert(false);
//            }
//        }
//    }
//}
//
//uint8_t SerialCompatibilityLayer_1::peek() {
//    this->fill_buff();
//    return this->buff[this->idx];
//}
//
//fsp_err_t SerialCompatibilityLayer_1::uart_read(uint8_t *rx, uint16_t *len) {
//    fsp_err_t err = FSP_SUCCESS;
//
//    if (g_out_of_band_index_1) {
//        g_receive_complete_1 = false;
//        if (rx != NULL) {
//            memcpy(rx, g_out_of_band_received_1, g_out_of_band_index_1);
//        }
//        *len = g_out_of_band_index_1;
//        g_out_of_band_index_1 = 0;
//        return FSP_SUCCESS;
//    }
//    else {
//        return FSP_ERR_IP_CHANNEL_NOT_PRESENT;
//    }
//    return err;
//}
//
//fsp_err_t SerialCompatibilityLayer_1::uart_print(uint8_t *p_msg, uint16_t msg_len) {
//    fsp_err_t err = FSP_SUCCESS;
//
//    /* Reset callback capture variable */
//    g_uart_event_1 = (0x00);
//
//    /* Writing to terminal */
//    err = R_SCI_B_UART_Write(&g_uart1_ctrl, p_msg, msg_len);
//    assert(err == FSP_SUCCESS);
//
//    R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MILLISECONDS);
//
//    return err;
//}
//
//void SerialCompatibilityLayer_1::uart_init(uint32_t *baud) {
//    fsp_err_t err = R_SCI_B_UART_Open(&g_uart1_ctrl, &g_uart1_cfg);
//    assert(err == FSP_SUCCESS);
//    baud_setting_t scif_baud_setting;
//    uint32_t baud_rate = *baud;
//    bool enable_bitrate_modulation = true;
//    uint32_t error_rate_x_1000 = 5000;
//    err = R_SCI_B_UART_BaudCalculate(baud_rate, enable_bitrate_modulation, error_rate_x_1000, &scif_baud_setting);
//    assert(FSP_SUCCESS == err);
//    err = R_SCI_B_UART_BaudSet(&g_uart1_ctrl, (void *) &scif_baud_setting);
//}
//
//void SerialCompatibilityLayer_1::uart_close(void) {
//    fsp_err_t err = R_SCI_B_UART_Close (&g_uart1_ctrl);
//    assert(err == FSP_SUCCESS);
//}
//
//void SerialCompatibilityLayer_1::print(uint8_t *p_msg) {
//    uint16_t len = 0;
//    while (p_msg[len]) {
//        len++;
//    }
//    this->uart_print(p_msg, len);
//}
//
//void SerialCompatibilityLayer_1::println(uint8_t *p_msg) {
//    uint16_t len = 0;
//    while (p_msg[len]) {
//        len++;
//    }
//    this->uart_print(p_msg, len);
//    this->uart_print((uint8_t*)"\n", 1);
//}
//
//void SerialCompatibilityLayer_1::print(long long p_msg) {
//    if (p_msg == 0) {
//        this->uart_print((uint8_t*)"0", 1);
//    }
//
//    if (p_msg < 0) {
//        this->uart_print((uint8_t*)"-", 1);
//        p_msg *= -1;
//    }
//
//    uint16_t len = 0;
//    uint8_t nr[20];
//    while (p_msg) {
//        nr[20 - len - 1] = (uint8_t)(p_msg % 10) + '0';
//        len++;
//        p_msg /= 10;
//    }
//    this->uart_print(nr + (20 - len), len);
//}
//
//void SerialCompatibilityLayer_1::println(long long p_msg) {
//    this->print(p_msg);
//    this->uart_print((uint8_t*)"\n", 1);
//}
//
//SerialCompatibilityLayer_1 Serial1;
//#endif

#endif //SerialCompatibility_h
