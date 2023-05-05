// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#define IRQ_MOUSE 12;

// Any header files included below this line should have been created by you
int hook_id=0;
uint8_t byte; //byte mais recente
uint8_t bytes[3];
uint8_t index=0;
uint8_t hook_id=0;
uint8_t rb;
uint8_t lb;
uint8_t mb;
uint8_t x_of;
uint8_t y_of;
uint16_t delta_x;
uint16_t delta_y;

int main(int argc, char *argv[]) {
    // sets the language of LCF messages (can be either EN-US or PT-PT)
    lcf_set_language("EN-US");

    // enables to log function invocations that are being "wrapped" by LCF
    // [comment this out if you don't want/need/ it]
    lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

    // enables to save the output of printf function calls on a file
    // [comment this out if you don't want/need it]
    lcf_log_output("/home/lcom/labs/lab4/output.txt");

    // handles control over to LCF
    // [LCF handles command line arguments and invokes the right function]
    if (lcf_start(argc, argv))
        return 1;

    // LCF clean up tasks
    // [must be the last statement before return]
    lcf_cleanup();

    return 0;
}
int mouse_subscribe_int(uint8_t *bit_no){
    if(bit_no==NULL) return 1;
    *bit_no = hook_id;
    if(sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE|IRQ_EXCLUSIVE, &hook_id));
    return 0;
}

int mouse_unsubscribe_int(){
    if(sys_irqrmpolicy(&hook_id)) return 1;
    return 0;
}

void mouse_ih(){
    read_KBC_output(0x60,&byte,1);
}

void mouse_sync(){
    if(index=0 && (byte & BIT(3))){
        bytes[0] = byte; //byte de controlo
        index++;
    }
    else if (index>0){
        bytes[index]=byte;
        index++;
    }
}

void to_packet(){
    rb = bytes[0]&BIT(2);
    lb = bytes[0]&BIT(0);
    mb = bytes[0]&BIT(1);
    x_of = bytes[0]&BIT(2);
    y_of = bytes[0]&BIT(2);
    delta_x = (byte[0]&BIT(4)) ? 0xFF00 | byte[1] : byte[1];
    delta_y = (byte[0]&BIT(5)) ? 0xFF00 | byte[2] : byte[2];
}

int mouse_write(uint8_t command) {

    uint8_t attemps = 10;
    uint8_t mouse_response=0;

    do {
        attemps--;
        if (write_KBC_command(0x64, 0xD4)) return 1;
        if (write_KBC_command(0x60, command)) return 1;
        tickdelay(micros_to_ticks(20000));
        if (read_KBC_output(0x60, &mouse_response, 1)) return 1;
        if(mouse_response==0xFA) return 0;
    } while (mouse_response != 0xFA && attemps);

    return 1;
}







int (mouse_test_packet)(uint32_t cnt) {
    int ipc_status;
    message msg;
    uint8_t mouse;

    if (mouse_subscribe_int(&mouse) != 0) return 1;

    if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;

    while (cnt){
        if (driver_receive(ANY, &msg, &ipc_status) != 0){
            printf("Error");
            continue;
        }
        if(msg.m_notify & mouse){
            mouse_ih();
            mouse_sync();
            if(index==3){
                to_packet();
                print_packet(&mouse_packet);
                index=0;
                cnt--;
            }
        }
    }

    if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;

    if (mouse_unsubscribe_int() != 0) return 1;

    return 0;
}