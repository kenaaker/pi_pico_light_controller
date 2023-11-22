#ifndef TRANSPORT_RECORD_H
#define TRANSPORT_RECORD_H
#include "fixedendian.h"
#include "var_st_xport.h"
#include "light_state_determiner.h"


static const uint8_t light_controller_remote_transport_type = 'L';
static const uint8_t light_controller_remote_transport_version = 2;
static const uint16_t light_controller_remote_transport_biggest_body = 4096;

#pragma pack(push,1)
typedef struct light_controller_remote_hdr {
    uint8_t type;
    uint8_t len;
    uint8_t version;
    BigEndian<uint16_t> b_len;

    light_controller_remote_hdr(unsigned int in_len=0) {
        type = 'L';
        len = sizeof(struct light_controller_remote_hdr);
        version = 4;
        b_len = in_len;
    }
} light_controller_remote_hdr_t;

typedef enum {
    command_opcode_nop,
    command_opcode_get_light_state,
    command_opcode_toggle_on_off,
    command_opcode_dimmer_setting,
    command_opcode_reset_to_default,
    command_opcode_MAX
} command_opcode_enum_t;

typedef struct transported_light_controller_values {
    BigEndian<unsigned int> light_intensity;
    BigEndian<unsigned int> dimmer_setting;
    BigEndian<unsigned int> power_supply_voltage;
    BigEndian<light_states> physical_light_state;
    BigEndian<light_states> user_set_light_state;
    bool PIR_detected_presence;
} transported_light_controller_values_t;

typedef struct light_controller_remote_transport_body {
    BigEndian<command_opcode_enum_t> command_opcode;
    transported_light_controller_values_t remote_values;
} light_controller_remote_transport_body_t;

typedef struct light_controller_remote_transport_struct {
    light_controller_remote_hdr_t light_controller_remote_transport_hdr;
    light_controller_remote_transport_body_t light_controller_remote_transport_body;
    void init(void) {
        light_controller_remote_transport_hdr.b_len = sizeof(light_controller_remote_transport_body);
    }
    light_controller_remote_transport_struct(void) {
        init();
    }
} light_controller_remote_transport_struct_t;
#pragma pack(pop)

static const uint8_t light_controller_remote_transport_hdr_len = sizeof(light_controller_remote_hdr_t);
static const uint16_t light_controller_remote_transport_body_len_empty = sizeof(light_controller_remote_transport_body_t);

#endif // TRANSPORT_RECORD_H
