#include "video.h"

vbe_mode_info_t mode_info;
uint8_t *frame_buffer;
uint16_t width, height;

unsigned int frame_size;
unsigned bytesPerPixel;

int (set_graphic_mode)(uint16_t submode) {
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10;
    reg86.ah = 0x4F;
    reg86.al = 0x02;
    reg86.bx = submode | BIT(14);
    if (sys_int86(&reg86) != 0) {
        return 1;
    }
    return 0;
}

int (map_vmem)(uint16_t mode) {

    struct minix_mem_range mr;
    unsigned int vram_base;
    unsigned int vram_size;

    memset(&mode_info, 0, sizeof(mode_info));

    /* Use VBE function 0x01 to initialize vram_base and vram_size */
    if (vbe_get_mode_info(mode, &mode_info))
        return EXIT_FAILURE;

    int res;
    uint8_t* vm;
    bytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;
    width = mode_info.XResolution;
    height = mode_info.YResolution;
    vram_base = mode_info.PhysBasePtr;
    vram_size = (width * height * mode_info.BitsPerPixel) / 8;

    /* Allow memory mapping */
    mr.mr_base = (phys_bytes) vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    if( OK != (res = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) {
        return 1;
    }

    /* Map memory */
    vm = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
    if(vm == MAP_FAILED) {
        return 1;
    }

    baseAddress = vm;
    return 0;
}

int draw_pixel(uint16_t x, uint16_t y, uint32_t color) {

    if(x >= mode_info.XResolution || y >= mode_info.YResolution) return 1;

    unsigned int index = (mode_info.XResolution * y + x) * bytesPerPixel;
    memcpy(&frame_buffer[index], &color , bytesPerPixel);
    return 0;
}

int (draw_line)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
    for (unsigned i = 0 ; i < len ; i++)
        if (draw_pixel(x+i, y, color) != 0) return 1;
    return 0;
}

int (draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    for(unsigned i = 0; i < height ; i++)
        if (draw_line(x, y+i, width, color) != 0) {
            continue;
        }
    return 0;
}

void clearBuffer(){
    memset(frame_buffer, 0 ,width * height * bytesPerPixel);
}

void allocateSpaceBuffer(){
    frame_buffer = (uint8_t *)malloc(width * height * bytesPerPixel);
    memset(frame_buffer, 0xDDDDDD, width * height * bytesPerPixel);
}

void videoSet(){
    memcpy (baseAddress , frame_buffer, width * height * bytesPerPixel);
}
